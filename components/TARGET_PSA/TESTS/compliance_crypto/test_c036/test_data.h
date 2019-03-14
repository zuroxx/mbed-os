/** @file
 * Copyright (c) 2019, Arm Limited or its affiliates. All rights reserved.
 * SPDX-License-Identifier : Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
**/

#include "val_crypto.h"

typedef struct {
    char                    test_desc[75];
    psa_key_handle_t        key_handle;
    psa_key_type_t          key_type;
    uint8_t                 key_data[32];
    uint32_t                key_length;
    psa_key_usage_t         usage;
    psa_algorithm_t         key_alg;
    uint8_t                 iv[16];
    size_t                  iv_size;
    uint8_t                 input[32];
    size_t                  input_length;
    size_t                  output_size;
    uint8_t                 expected_output[32];
    size_t                  expected_output_length;
    psa_status_t            expected_status;
} test_data;

static test_data check1[] = {
#ifdef ARCH_TEST_AES_128
#ifdef ARCH_TEST_CBC_NO_PADDING
{"Test psa_cipher_update - Encrypt - AES CBC_NO_PADDING\n", 1, PSA_KEY_TYPE_AES,
{0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09,
 0xcf, 0x4f, 0x3c}, AES_16B_KEY_SIZE,
 PSA_KEY_USAGE_ENCRYPT, PSA_ALG_CBC_NO_PADDING,
{0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
 0x2a, 0x2a, 0x2a}, 16,
{0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73,
 0x93, 0x17, 0x2a}, 16, 16,
{0xA0, 0x76, 0xEC, 0x9D, 0xFB, 0xE4, 0x7D, 0x52, 0xAF, 0xC3, 0x57, 0x33, 0x6F,
 0x20, 0x74, 0x3B}, 16, PSA_SUCCESS
},

{"Test psa_cipher_update - Encrypt - AES CBC_NO_PADDING (Short input)\n", 2, PSA_KEY_TYPE_AES,
{0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09,
 0xcf, 0x4f, 0x3c}, AES_16B_KEY_SIZE,
 PSA_KEY_USAGE_ENCRYPT, PSA_ALG_CBC_NO_PADDING,
{0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
 0x2a, 0x2a, 0x2a}, 16,
{0x6b, 0xc1, 0xbe, 0xe2, 0x23}, 5, 16,
{0x6b, 0xc1, 0xbe, 0xe2, 0x23}, 0, PSA_SUCCESS
},
#endif

#ifdef ARCH_TEST_CBC_PKCS7
{"Test psa_cipher_update - Encrypt - AES CBC_PKCS7\n", 3, PSA_KEY_TYPE_AES,
{0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09,
 0xcf, 0x4f, 0x3c}, AES_16B_KEY_SIZE,
 PSA_KEY_USAGE_ENCRYPT, PSA_ALG_CBC_PKCS7,
{0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
 0x2a, 0x2a, 0x2a}, 16,
{0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73,
 0x93, 0x17, 0x2a}, 16, 16,
{0xa0, 0x76, 0xec, 0x9d, 0xfb, 0xe4, 0x7d, 0x52, 0xaf, 0xc3, 0x57, 0x33, 0x6f,
 0x20, 0x74, 0x3b}, 16, PSA_SUCCESS
},

{"Test psa_cipher_update - Encrypt - AES CBC_PKCS7 (Short input)\n", 4, PSA_KEY_TYPE_AES,
{0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09,
 0xcf, 0x4f, 0x3c}, AES_16B_KEY_SIZE,
 PSA_KEY_USAGE_ENCRYPT, PSA_ALG_CBC_PKCS7,
{0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
 0x2a, 0x2a, 0x2a}, 16,
{0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73,
 0x93, 0x17}, 15, 16,
{0}, 0, PSA_SUCCESS
},
#endif

#ifdef ARCH_TEST_CIPER_MODE_CTR
{"Test psa_cipher_update - Encrypt - AES CTR\n", 5, PSA_KEY_TYPE_AES,
{0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09,
 0xcf, 0x4f, 0x3c}, AES_16B_KEY_SIZE,
 PSA_KEY_USAGE_ENCRYPT, PSA_ALG_CTR,
{0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
 0x2a, 0x2a, 0x2a}, 16,
{0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73,
 0x93, 0x17, 0x2a}, 16, 16,
{0x8f, 0x94, 0x08, 0xfe, 0x80, 0xa8, 0x1d, 0x3e, 0x81, 0x3d, 0xa3, 0xc7, 0xb0,
 0xb2, 0xbd, 0x32}, 16, PSA_SUCCESS
},
#endif

#ifdef ARCH_TEST_CBC_NO_PADDING
#ifdef ARCH_TEST_DES_1KEY
{"Test psa_cipher_update - Encrypt - DES CBC (nopad)\n", 6, PSA_KEY_TYPE_DES,
{0x01, 0x02, 0x04, 0x07, 0x08, 0x0b, 0x0d, 0x0e}, DES_8B_KEY_SIZE,
 PSA_KEY_USAGE_ENCRYPT, PSA_ALG_CBC_NO_PADDING,
{0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a}, 8,
{0xed, 0xa4, 0x01, 0x12, 0x39, 0xbc, 0x3a, 0xc9}, 8, 8,
{0x64, 0xf9, 0x17, 0xb0, 0x15, 0x2f, 0x8f, 0x05}, 8, PSA_SUCCESS
},
#endif
#endif
#endif

#ifdef ARCH_TEST_CBC_NO_PADDING
#ifdef ARCH_TEST_DES_2KEY
{"Test psa_cipher_update - Encrypt - 2-key 3DE -CBC (nopad)\n", 7, PSA_KEY_TYPE_DES,
{0x01, 0x02, 0x04, 0x07, 0x08, 0x0b, 0x0d, 0x0e, 0xc1, 0xc2, 0xc4, 0xc7, 0xc8,
 0xcb, 0xcd, 0xce}, DES3_2KEY_SIZE,
 PSA_KEY_USAGE_ENCRYPT, PSA_ALG_CBC_NO_PADDING,
{0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a}, 8,
{0xed, 0xa4, 0x01, 0x12, 0x39, 0xbc, 0x3a, 0xc9}, 8, 8,
{0x5d, 0x06, 0x52, 0x42, 0x9c, 0x5b, 0x0a, 0xc7}, 8, PSA_SUCCESS
},
#endif

#ifdef ARCH_TEST_DES_3KEY
{"Test psa_cipher_update - Encrypt - 3-key 3DE -CBC (nopad)\n", 8, PSA_KEY_TYPE_DES,
{0x01, 0x02, 0x04, 0x07, 0x08, 0x0b, 0x0d, 0x0e, 0xc1, 0xc2, 0xc4, 0xc7, 0xc8,
 0xcb, 0xcd, 0xce, 0x31, 0x32, 0x34, 0x37, 0x38, 0x3b, 0x3d, 0x3e}, DES3_3KEY_SIZE,
 PSA_KEY_USAGE_ENCRYPT, PSA_ALG_CBC_NO_PADDING,
{0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a}, 8,
{0xed, 0xa4, 0x01, 0x12, 0x39, 0xbc, 0x3a, 0xc9}, 8, 8,
{0x81, 0x7c, 0xa7, 0xd6, 0x9b, 0x80, 0xd8, 0x6a}, 8, PSA_SUCCESS
},
#endif

#ifdef ARCH_TEST_AES_128
{"Test psa_cipher_update - small output buffer size\n", 9, PSA_KEY_TYPE_AES,
{0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09,
 0xcf, 0x4f, 0x3c}, AES_16B_KEY_SIZE,
 PSA_KEY_USAGE_ENCRYPT, PSA_ALG_CBC_NO_PADDING,
{0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
 0x2a, 0x2a, 0x2a}, 16,
{0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73,
 0x93, 0x17, 0x2a}, 16, 15,
{0xA0, 0x76, 0xEC, 0x9D, 0xFB, 0xE4, 0x7D, 0x52, 0xAF, 0xC3, 0x57, 0x33, 0x6F,
 0x20, 0x74, 0x3B}, 16, PSA_ERROR_BUFFER_TOO_SMALL
},

{"Test psa_cipher_update - Decrypt - AES CBC_NO_PADDING\n", 10, PSA_KEY_TYPE_AES,
{0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09,
 0xcf, 0x4f, 0x3c}, AES_16B_KEY_SIZE,
 PSA_KEY_USAGE_DECRYPT, PSA_ALG_CBC_NO_PADDING,
{0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
 0x2a, 0x2a, 0x2a}, 16,
{0xA0, 0x76, 0xEC, 0x9D, 0xFB, 0xE4, 0x7D, 0x52, 0xAF, 0xC3, 0x57, 0x33, 0x6F,
 0x20, 0x74, 0x3B}, 16, 16,
{0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73,
 0x93, 0x17, 0x2a}, 16, PSA_SUCCESS
},

{"Test psa_cipher_update - Decrypt - AES CBC_NO_PADDING (Short input)\n", 11, PSA_KEY_TYPE_AES,
{0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09,
 0xcf, 0x4f, 0x3c}, AES_16B_KEY_SIZE,
 PSA_KEY_USAGE_DECRYPT, PSA_ALG_CBC_NO_PADDING,
{0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
 0x2a, 0x2a, 0x2a}, 16,
{0x6b, 0xc1, 0xbe, 0xe2, 0x23}, 5, 16,
{0x6b, 0xc1, 0xbe, 0xe2, 0x23}, 0, PSA_SUCCESS
},
#endif
#endif

#ifdef ARCH_TEST_AES_128
#ifdef ARCH_TEST_CBC_PKCS7
{"Test psa_cipher_update - Decrypt - AES CBC_PKCS7\n", 12, PSA_KEY_TYPE_AES,
{0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09,
 0xcf, 0x4f, 0x3c}, AES_16B_KEY_SIZE,
 PSA_KEY_USAGE_DECRYPT, PSA_ALG_CBC_PKCS7,
{0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
 0x2a, 0x2a, 0x2a}, 16,
{0xa0, 0x76, 0xec, 0x9d, 0xfb, 0xe4, 0x7d, 0x52, 0xaf, 0xc3, 0x57, 0x33, 0x6f,
 0x20, 0x74, 0x3b}, 16, 16,
{0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73,
 0x93, 0x17, 0x2a}, 0, PSA_SUCCESS
},

{"Test psa_cipher_update - Decrypt - AES CBC_PKCS7 (Short input)\n", 13, PSA_KEY_TYPE_AES,
{0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09,
 0xcf, 0x4f, 0x3c}, AES_16B_KEY_SIZE,
 PSA_KEY_USAGE_DECRYPT, PSA_ALG_CBC_PKCS7,
{0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
 0x2a, 0x2a, 0x2a}, 16,
{0xa0, 0x76, 0xec, 0x9d, 0xfb, 0xe4, 0x7d, 0x52, 0xaf, 0xc3, 0x57, 0x33, 0x6f,
 0x20, 0x74, 0x3b, 0xca, 0x7e, 0x8a, 0x15, 0xdc, 0x3c, 0x77, 0x64, 0x36, 0x31,
 0x42, 0x93, 0x03, 0x1c, 0xd4, 0xf3}, 32, 32,
{0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73,
 0x93, 0x17, 0x2a}, 16, PSA_SUCCESS
},
#endif

#ifdef ARCH_TEST_CIPER_MODE_CTR
{"Test psa_cipher_update - Decrypt - AES CTR\n", 14, PSA_KEY_TYPE_AES,
{0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09,
 0xcf, 0x4f, 0x3c}, AES_16B_KEY_SIZE,
 PSA_KEY_USAGE_DECRYPT, PSA_ALG_CTR,
{0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
 0x2a, 0x2a, 0x2a}, 16,
{0x8f, 0x94, 0x08, 0xfe, 0x80, 0xa8, 0x1d, 0x3e, 0x81, 0x3d, 0xa3, 0xc7, 0xb0,
 0xb2, 0xbd, 0x32}, 16, 16,
{0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73,
 0x93, 0x17, 0x2a}, 16, PSA_SUCCESS
},
#endif
#endif

#ifdef ARCH_TEST_CBC_NO_PADDING
#ifdef ARCH_TEST_DES_1KEY
{"Test psa_cipher_update - Decrypt - DES CBC (nopad)\n", 15, PSA_KEY_TYPE_DES,
{0x01, 0x02, 0x04, 0x07, 0x08, 0x0b, 0x0d, 0x0e}, DES_8B_KEY_SIZE,
 PSA_KEY_USAGE_DECRYPT, PSA_ALG_CBC_NO_PADDING,
{0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a}, 8,
{0x64, 0xf9, 0x17, 0xb0, 0x15, 0x2f, 0x8f, 0x05}, 8, 8,
{0xed, 0xa4, 0x01, 0x12, 0x39, 0xbc, 0x3a, 0xc9}, 8, PSA_SUCCESS
},
#endif

#ifdef ARCH_TEST_DES_2KEY
{"Test psa_cipher_update - Decrypt - 2-key 3DE -CBC (nopad)\n", 16, PSA_KEY_TYPE_DES,
{0x01, 0x02, 0x04, 0x07, 0x08, 0x0b, 0x0d, 0x0e, 0xc1, 0xc2, 0xc4, 0xc7, 0xc8,
 0xcb, 0xcd, 0xce}, DES3_2KEY_SIZE,
 PSA_KEY_USAGE_DECRYPT, PSA_ALG_CBC_NO_PADDING,
{0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a}, 8,
{0x5d, 0x06, 0x52, 0x42, 0x9c, 0x5b, 0x0a, 0xc7}, 8, 8,
{0xed, 0xa4, 0x01, 0x12, 0x39, 0xbc, 0x3a, 0xc9}, 8, PSA_SUCCESS
},
#endif

#ifdef ARCH_TEST_DES_3KEY
{"Test psa_cipher_update - Decrypt - 3-key 3DE -CBC (nopad)\n", 17, PSA_KEY_TYPE_DES,
{0x01, 0x02, 0x04, 0x07, 0x08, 0x0b, 0x0d, 0x0e, 0xc1, 0xc2, 0xc4, 0xc7, 0xc8,
 0xcb, 0xcd, 0xce, 0x31, 0x32, 0x34, 0x37, 0x38, 0x3b, 0x3d, 0x3e}, DES3_3KEY_SIZE,
 PSA_KEY_USAGE_DECRYPT, PSA_ALG_CBC_NO_PADDING,
{0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a}, 8,
{0x81, 0x7c, 0xa7, 0xd6, 0x9b, 0x80, 0xd8, 0x6a}, 8, 8,
{0xed, 0xa4, 0x01, 0x12, 0x39, 0xbc, 0x3a, 0xc9}, 8, PSA_SUCCESS
},
#endif
#endif
};