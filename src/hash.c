/*
 * Copyright 2013-2016 Guardtime, Inc.
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

#include "hash.h"

#include <string.h>

const struct GT_Hash_AlgorithmInfo {
	GT_Hash_AlgorithmId id;
	char *name;
	size_t lenght;
	size_t blockSize;
} hshAlgoInfo[] = {
		{GT_HASHALG_SHA1,       "sha1",   160, 512},
		{GT_HASHALG_SHA2_256,   "sha256", 256, 512},
		{GT_HASHALG_RIPEMD160,  "rmd160", 160, 512},
		{GT_HASHALG_UNKNOWN_03, NULL,     0,   0  },
		{GT_HASHALG_SHA2_384,   "sha384", 384, 1024},
		{GT_HASHALG_SHA2_512,   "sha512", 512, 1024}
};

int GT_Hash_getAlgorithmId(char *arg, GT_Hash_AlgorithmId *id) {
	int i;
	for (i = 0; i < sizeof(hshAlgoInfo) / sizeof(hshAlgoInfo[0]); i++) {
		if (hshAlgoInfo[i].name != NULL && strstr(arg, hshAlgoInfo[i].name)) {
			*id = hshAlgoInfo[i].id;
			return GT_OK;
		}
	}
	return GT_CRYPTO_FAILURE;
}

size_t GT_Hash_getAlgorithmLenght(GT_Hash_AlgorithmId id) {
	if (id < GT_NOF_HASHALGS && id == hshAlgoInfo[id].id) {
		return hshAlgoInfo[id].lenght / 8;
	}
	return 0;
}

size_t GT_Hash_getAlgorithmBlockSize(GT_Hash_AlgorithmId id) {
	if (id < GT_NOF_HASHALGS && id == hshAlgoInfo[id].id) {
		return hshAlgoInfo[id].blockSize / 8;
	}
	return 0;
}

char* GT_Hash_getAlgorithmName(GT_Hash_AlgorithmId id) {
	if (id < GT_NOF_HASHALGS && id == hshAlgoInfo[id].id) {
		return hshAlgoInfo[id].name;
	}
	return NULL;
}
