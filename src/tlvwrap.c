#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <limits.h>

#include "common.h"

int encode(unsigned int type, int lenient, int forward, FILE *in, FILE *out) {
	int res = GT_UNKNOWN_ERROR;
	unsigned char buf[0xffff];
	unsigned char hdr[4];
	size_t len;
	int count = 0;

	if (in == NULL) in = stdin;
	if (out == NULL) out = stdout;

	while (1) {
		len = fread(buf, 1, sizeof(buf), in);

		if (len == 0 && count > 0) break;
		count++;

		if (len >> 8 > UCHAR_MAX) {
			res = GT_INVALID_ARGUMENT;
			fprintf(stderr, "Len is too great: '%llu'.\n", (unsigned long long)len);
			goto cleanup;
		}

		/* TLV 18? */
		if (type > 0x1f || len > 0xff) {
			*hdr = 0x80 | (lenient * 0x40) | (forward * 0x20) | (type >> 8);
			*(hdr + 1) = type & 0xff;
			*(hdr + 2) = (unsigned char)(len >> 8);
			*(hdr + 3) = len & 0xff;
			if (fwrite(hdr, 1, 4, out) != 4) {
				fprintf(stderr, "Failed to write to stream.");
			}
		} else {
			*hdr = 0x00 | (lenient * 0x40) | (forward * 0x20) | (type);
			*(hdr + 1) = len & 0xff;
			if (fwrite(hdr, 1, 2, out) != 2) {
				fprintf(stderr, "Failed to write to stream.");
			}
		}

		if (fwrite(buf, 1, len, out) != len) {
			fprintf(stderr, "Failed to write to stream.");
		}
	}

	res = GT_OK;

cleanup:

	return res;
}

void printHelp(FILE *f) {
	fprintf(f,
		"Usage:\n"
		"  gttlvwrap <options>\n\n"
		"Options:\n"
		"  -N         Set the TLV non-critical flag.\n"
		"  -F         Set the TLV forward flag.\n"
		"  -t <tag>   Set the TLV tag (type).\n"
		"  -i <fn>    Input file.\n"
		"  -o <fn>    Output file.\n"
		"  -h         Print this help.\n"
		"  -v         TLV utility package version.\n"
		"\n");
}

int main(int argc, char **argv) {
	int res = GT_UNKNOWN_ERROR;
	int c;
	int lenient = 0;
	int forward = 0;
	FILE *in = NULL;
	FILE *out = NULL;
	int type = -1;
	char *tail = NULL;

	while ((c = getopt(argc, argv, "LNFt:i:o:hv")) != -1) {
		switch (c) {
			case 'L':
				fprintf(stderr, "Warning: -L is deprecated, use -N instead for Non-Critical flag.\n");
			case 'N':
				lenient = 1;
				break;
			case 'F':
				forward = 1;
				break;
			case 't':
				type = strtol(optarg, &tail, 16);
				if (*tail != 0) {
					fprintf(stderr, "Bad tag value: '%s'.", optarg);
					res = GT_INVALID_FORMAT;
					goto cleanup;
				}
				if (type <= 0 || type > 0x1fff) {
					fprintf(stderr, "Tag value out of range.");
					res = GT_INVALID_FORMAT;
					goto cleanup;
				}
				break;
			case 'i':
				in = fopen(optarg, "rb");
				if (in == NULL) {
					fprintf(stderr, "Unable to open input file '%s'.\n", optarg);
					res = GT_IO_ERROR;
					goto cleanup;
				}
				break;
			case 'o':
				out = fopen(optarg, "wb");
				if (out == NULL) {
					fprintf(stderr, "Unable to open output file '%s'.\n", optarg);
					res = GT_IO_ERROR;
					goto cleanup;
				}
				break;
			case 'h':
				printHelp(stdout);
				res = GT_OK;
				goto cleanup;
			case 'v':
				printf("%s\n", TLV_UTIL_VERSION_STRING);
				res = GT_OK;
				goto cleanup;
			default:
				fprintf(stderr, "Unknown parameter, try -h.\n");
				res = GT_INVALID_CMD_PARAM;
				goto cleanup;
		}
	}

	if (type < 0) {
		fprintf(stderr, "Tlv tag (-t) must be specified.\n");
		res = GT_INVALID_FORMAT;
		goto cleanup;
	}

	res = encode((unsigned)type, lenient, forward, in, out);

cleanup:

	if (in != NULL) fclose(in);
	if (out != NULL) fclose(out);

	return res;
}
