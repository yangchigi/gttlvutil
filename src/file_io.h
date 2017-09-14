/*
 * Copyright 2013-2015 Guardtime, Inc.
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

#ifndef FILE_IO_H_
#define FILE_IO_H_

#include <stdio.h>

#include "common.h"
#include "encoding.h"

/**
 * This function reads binary data to a buffer from the stream. The contents of the internal
 * buffer is shifted \c consume elements to the right and if the stream is not closed reads
 * as many bytes as possible to populate the remaining empty space on the right.
 * \param buf		Output buffer - do not free.
 * \param consumed	Number of bytes to shift the buffer to the left.
 * \param file		Stream to read from.
 */
long GT_consume_raw(unsigned char **buf, size_t consumed, FILE *file);

/**
 * Same as #GT_consume_raw, but interprets the input as a hex string. It will
 * fail if the input does contain anything that is not a whitespace or hex character.
 * If the input consists of an uneven number of hex characters the last byte is
 * interpreted as it was followed by a zero.
 */
long GT_consume_hex(unsigned char **buf, size_t consumed, FILE *file);

/**
 * Same as #GT_consume_raw, but it interprets the input as one or more base64 strings.
 */
long GT_consume_b64(unsigned char **buf, size_t consumed, FILE *file);

/**
 * Read file stream. The stream is buffered till eof is reached.
 * \param enc	File stream data encoding.
 * \param raw	Buffer containing content of the \c file stream.
 * \param size	Buffer size.
 * \param file	File stream.
 * \return	Status code (#GT_OK, when operation succeeded, otherwise an error code).
 */
int GT_fread(GT_Encoding enc, unsigned char **raw, size_t *size, FILE *file);

/**
 * File size in bytes.
 * \param file	File stream.
 * \return Number of bytes in the file, or -1 in case of an error.
 */
long GT_fsize(FILE *file);

#endif /* FILE_IO_H_ */
