#ifndef DESC_H_
#define DESC_H_

#include "common.h"

enum {
	/** Composite payload. */
	TLV_COMPOSITE,
	/** Unsigned integer value. */
	TLV_INT,
	/** Raw, uninterpreded value. */
	TLV_RAW,
	/** Utf-8 string value. */
	TLV_STR,
	/** Time in seconds. */
	TLV_TIME,
	/** Time in milli seconds. */
	TLV_MTIME,
	/** Time in micro seconds. */
	TLV_UTIME,
	/** Imprint value. */
	TLV_IMPRINT,
	/** Composite value, that is not parsable. */
	TLV_NOT_A_COMPOSITE,
};

/**
 * Container for nested structure descriptions.
 */
struct desc_st {
	/** Textual value. */
	char *val;

	/** Key value */
	unsigned key;

	/** Type of the tlv. */
	int type;

	/** Sparse table of pointers. */
	struct desc_st *map[0xff];
};


/**
 * Initialize the description with the contents of the file.
 */
int desc_add_file(struct desc_st *desc, const char *descFile, bool override);

/**
 * Find the given key in the description.
 */
int desc_find(struct desc_st *in, unsigned tag, struct desc_st **out);

/**
 * Pefrorms a cleanup of the object, but won't free it.
 */
void desc_cleanup(struct desc_st *desc);

#endif
