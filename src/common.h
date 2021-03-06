/*
 * Copyright 2013-2017 Guardtime, Inc.
 *
 * This file is part of the Guardtime client SDK.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *     http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES, CONDITIONS, OR OTHER LICENSES OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 * "Guardtime" and "KSI" are trademarks or registered trademarks of
 * Guardtime, Inc., and no license to trademarks is granted; Guardtime
 * reserves and retains all trademark rights.
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>
#include "compatibility.h"

#define GT_TLV_MASK_TLV16 0x80u
#define GT_TLV_MASK_NON_CRITICAL 0x40u
#define GT_TLV_MASK_FORWARD 0x20u

#define GT_TLV_TYPE_1ST_BYTE_MASK 0x1fu

#define TLV_UTIL_VERSION_STRING (PACKAGE_NAME" "VERSION)

#define IS_EOL(c) ((c) == '\n' || (c) == '\r')
#define IS_SPACE(c) ((c) == ' ' || (c) == '\t')
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')
#define IS_CHAR(c) ((toupper(c) >= 'A' && toupper(c) <= 'Z'))
#define IS_HEX(c) (IS_DIGIT(c) || (toupper(c) >= 'A' && toupper(c) <= 'F'))
#define DECCHAR_TO_DEC(c) ((c) - '0')
#define HEXCHAR_TO_DEC(c) (IS_DIGIT(c) ? DECCHAR_TO_DEC(c) : (toupper((c)) - 'A' + 10))

#define GROUPING_CHAR '-'
#define PADDING_CHAR  '='
#define IS_GROUPING_CHAR(c) ((c) == GROUPING_CHAR)
#define IS_PADDING_CHAR(c)  ((c) == PADDING_CHAR)

#define IS_BASE64(c) (IS_CHAR(c) || IS_DIGIT(c) || (c) == '+' || (c) == '/' || IS_PADDING_CHAR(c))


/**
 * Crypto implementations.
 */
#define HASH_OPENSSL   1
#define HASH_CRYPTOAPI 2

/**
* Default implementation for data hashing.
*/
#ifndef CRYPTO_IMPL
#	define CRYPTO_IMPL HASH_OPENSSL
#endif

#define GT_TLV_BUF_SIZE (0xffff + 4)

#ifdef _WIN32
#  define setBinaryMode(f) _setmode(_fileno(f), _O_BINARY);
#else
#  define setBinaryMode(f)
#endif

typedef enum {
	false = 0, true = !false
} bool;

/**
 * Flushes stdout and prints the message to stderr stream.
 */
int print_error(const char *fmt, ...);
int tlvutil_ErrToExitcode(int error_code);

enum StatusCodes {
	/**
	 * Everything is OK!
	 */
	GT_OK = 0,

	/**
	 * Invalid or unknown command-line parameter or its argument.
	 */
	GT_INVALID_CMD_PARAM,

	/**
	 * Memory allocation failed. Possibly system out of memory.
	 */
	GT_OUT_OF_MEMORY,

	/**
	 * Not used.
	 */
	GT_ERR_RESERVED_0,

	/**
	 * Input/Output error. May be caused by invalid paths, restricted access to
	 * files or when resource is locked.
	 */
	GT_IO_ERROR,

	/**
	 * Invalid function argument. May be caused by NULL pointers, empty strings,
	 * invalid argument combination and invalid or out of ranges values.
	 */
	GT_INVALID_ARGUMENT,

	/**
	 * Data stream has correct syntax but something is wrong with the format, e.g.
	 * bad HMAC TLV order, value is too large or unknown or not suitable value.
	 */
	GT_INVALID_FORMAT,

	/**
	 * Buffer too small to perform operation.
	 */
	GT_BUFFER_OVERFLOW,

	/**
	 * Parser error is used when it is not possible to perform any further parsing
	 * of a data stream due to unexpected context. Note that when parser detects
	 * a token in expected location that has unknown value and it is theoretically
	 * possible to continue parsing, then it is a format error instead. E.g.
	 * unexpected end of file or unexpected syntax.
	 */
	GT_PARSER_ERROR,

	/**
	 * Cryptographic operation could not be performed. Likely causes are
	 * unsupported or unknown cryptographic algorithms. Is related with HMAC.
	 */
	GT_CRYPTO_FAILURE,

	/**
	 * Description file contains duplicated records.
	 */
	GT_DUPLICATE_ERROR,

	/**
	 * Expected End of data stream.
	 */
	GT_END_OF_STREAM,

	/**
	 * Unknown error occurred.
	 */
	GT_UNKNOWN_ERROR = 0xffff
};
enum TlvUtil_exit {
//	EXIT_SUCCESS 0
//	EXIT_FAILURE 1
//	EXIT_RESERVED_0 = 2,

	/**
	 * The content or format of a command-line parameter is invalid or a parameter is missing.
	 */
	EXIT_INVALID_CL_PARAMETERS = 3,

	/**
	 * Input data can not be parsed or data format is invalid.
	 */
	EXIT_INVALID_FORMAT = 4,

//	EXIT_RESERVED_1 = 5,
//	EXIT_RESERVED_2 = 6,
//	EXIT_RESERVED_3 = 7,
//	EXIT_RESERVED_4 = 8,
	/**
	 * Unable to read or write file or stream.
	 */
	EXIT_IO_ERROR = 9,

	/**
	 * Cryptographic operation could not be performed. Likely causes are
	 * unsupported or unknown cryptographic algorithms during HMAC calculation.
	 */
	EXIT_CRYPTO_ERROR = 10,

//	EXIT_RESERVED_5 = 11,
//	EXIT_RESERVED_6 = 12,

	/**
	 * System out of memory.
	 */
	EXIT_OUT_OF_MEMORY = 13

//	EXIT_RESERVED_7 = 14,
//	EXIT_RESERVED_8 = 15,
//	EXIT_RESERVED_9 = 16,
};

#endif /* COMMON_H_ */


