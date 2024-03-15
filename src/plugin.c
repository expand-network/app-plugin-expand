/*******************************************************************************
 *   Expand Plugin
 *   (c) 2023 Ledger
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#include <stdint.h>
#include "plugin.h"

// This array will be automatically expanded to map all selector_t names with the correct value.
// Do not modify !
const uint32_t SELECTORS[SELECTOR_COUNT] = { SELECTORS_LIST(TO_VALUE) };

const uint8_t NULL_ETH_ADDRESS[ADDRESS_LENGTH] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t WETH_ADDRESS[ADDRESS_LENGTH] = {0xc0, 0x2a, 0xaa, 0x39, 0xb2, 0x23, 0xfe,
                                              0x8d, 0x0a, 0x0e, 0x5c, 0x4f, 0x27, 0xea,
                                              0xd9, 0x08, 0x3c, 0x75, 0x6c, 0xc2};

const uint8_t OETH_ADDRESS[ADDRESS_LENGTH] = {0x85, 0x6c, 0x4e, 0xfb, 0x76, 0xc1, 0xd1,
                                              0xae, 0x02, 0xe2, 0x0c, 0xeb, 0x03, 0xa2,
                                              0xa6, 0xa0, 0x8b, 0x0b, 0x8d, 0xc3};

const uint8_t FRXETH_ADDRESS[ADDRESS_LENGTH] = {0x5e, 0x84, 0x22, 0x34, 0x52, 0x38, 0xf3,
                                                0x42, 0x75, 0x88, 0x80, 0x49, 0x02, 0x18,
                                                0x21, 0xe8, 0xe0, 0x8c, 0xaa, 0x1f};

const uint8_t RETH_ADDRESS[ADDRESS_LENGTH] = {0xae, 0x78, 0x73, 0x6c, 0xd6, 0x15, 0xf3,
                                              0x74, 0xd3, 0x08, 0x51, 0x23, 0xa2, 0x10,
                                              0x44, 0x8e, 0x74, 0xfc, 0x63, 0x93};

const uint8_t STETH_ADDRESS[ADDRESS_LENGTH] = {0xae, 0x7a, 0xb9, 0x65, 0x20, 0xde, 0x3a,
                                               0x18, 0xe5, 0xe1, 0x11, 0xb5, 0xea, 0xab,
                                               0x09, 0x53, 0x12, 0xd7, 0xfe, 0x84};

const uint8_t OUSD_ADDRESS[ADDRESS_LENGTH] = {0x2a, 0x8e, 0x1e, 0x67, 0x6e, 0xc2, 0x38,
                                              0xd8, 0xa9, 0x92, 0x30, 0x7b, 0x49, 0x5b,
                                              0x45, 0xb3, 0xfe, 0xaa, 0x5e, 0x86};

const uint8_t DAI_ADDRESS[ADDRESS_LENGTH] = {0x6b, 0x17, 0x54, 0x74, 0xe8, 0x90, 0x94,
                                             0xc4, 0x4d, 0xa9, 0x8b, 0x95, 0x4e, 0xed,
                                             0xea, 0xc4, 0x95, 0x27, 0x1d, 0x0f};

const uint8_t USDC_ADDRESS[ADDRESS_LENGTH] = {0xa0, 0xb8, 0x69, 0x91, 0xc6, 0x21, 0x8b,
                                              0x36, 0xc1, 0xd1, 0x9d, 0x4a, 0x2e, 0x9e,
                                              0xb0, 0xce, 0x36, 0x06, 0xeb, 0x48};

const uint8_t USDT_ADDRESS[ADDRESS_LENGTH] = {0xda, 0xc1, 0x7f, 0x95, 0x8d, 0x2e, 0xe5,
                                              0x23, 0xa2, 0x20, 0x62, 0x06, 0x99, 0x45,
                                              0x97, 0xc1, 0x3d, 0x83, 0x1e, 0xc7};

const uint8_t OETH_VAULT_ADDRESS[ADDRESS_LENGTH] = {0x39, 0x25, 0x40, 0x33, 0x94, 0x5a, 0xa2,
                                                    0xe4, 0x80, 0x9c, 0xc2, 0x97, 0x7e, 0x70,
                                                    0x87, 0xbe, 0xe4, 0x8b, 0xd7, 0xab};

const uint8_t WOETH_ADDRESS[ADDRESS_LENGTH] = {0xdc, 0xee, 0x70, 0x65, 0x42, 0x61, 0xaf,
                                               0x21, 0xc4, 0x4c, 0x09, 0x3c, 0x30, 0x0e,
                                               0xd3, 0xbb, 0x97, 0xb7, 0x81, 0x92};

const uint8_t CURVE_OUSD_POOL_ADDRESS[ADDRESS_LENGTH] = {0x87, 0x65, 0x0d, 0x7b, 0xbf, 0xc3, 0xa9,
                                                         0xf1, 0x05, 0x87, 0xd7, 0x77, 0x82, 0x06,
                                                         0x67, 0x17, 0x19, 0xd9, 0x91, 0x0d};

const uint8_t CURVE_POOL_ETH_ADDRESS[ADDRESS_LENGTH] = {0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
                                                        0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
                                                        0xee, 0xee, 0xee, 0xee, 0xee, 0xee};

// const uint8_t LIT_ADDRESS[ADDRESS_LENGTH] = { 0xb, 0x05, 0x06, 0x65, 0x21, 0x55, 0x0d, 
//                                               0x7d, 0x7a, 0xb1, 0x9d, 0xa8, 0xf7, 0x2b, 
//                                               0xb0, 0x04, 0xb4, 0xc3, 0x41 };


const uint8_t LINK_ADDRESS[ADDRESS_LENGTH] =  { 0x51, 0x49, 0x10, 0x77, 0x1a, 0xf9, 0xca, 0x65, 0x6a, 0xf8, 0x40, 0xdf, 0xf8, 0x3e, 0x82, 0x64, 0xec, 0xf9, 0x86, 0xca };

const uint8_t SUSHI_ADDRESS[ADDRESS_LENGTH] = { 0x6b, 0x35, 0x95, 0x06, 0x87, 0x78, 0xdd, 0x59, 0x2e, 0x39, 0xa1, 0x22, 0xf4, 0xf5, 0xa5, 0xcf, 0x09, 0xc9, 0x0f, 0xe2 };

const uint8_t SYNTHETIC_ADDRESS[ADDRESS_LENGTH] = { 0x57, 0xab, 0x1e, 0xc2, 0x8d, 0x12, 0x97, 0x07, 0x05, 0x2d, 0xf4, 0xdf, 0x41, 0x8d, 0x58, 0xa2, 0xd4, 0x6d, 0x5f, 0x51 };

const uint8_t UNI_ADDRESS[ADDRESS_LENGTH] = { 0x1f, 0x98, 0x40, 0xa8, 0x5d, 0x5a, 0xf5, 0xbf, 0x1d, 0x17, 0x62, 0xf9, 0x25, 0xbd, 0xad, 0xdc, 0x42, 0x01, 0xf9, 0x84 };

const uint8_t TUSD_ADDRESS[ADDRESS_LENGTH] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x5d, 0x47, 0x80, 0xb7, 0x31, 0x19, 0xb6, 0x44, 0xae, 0x5e, 0xcd, 0x22, 0xb3, 0x76 };

const uint8_t USDP_ADDRESS[ADDRESS_LENGTH] = { 0x8e, 0x87, 0x0d, 0x67, 0xf6, 0x60, 0xd9, 0x5d, 0x5b, 0xe5, 0x30, 0x38, 0x0d, 0x0e, 0xc0, 0xbd, 0x38, 0x82, 0x89, 0xe1 };

const uint8_t WBTC_ADDRESS[ADDRESS_LENGTH] = { 0x22, 0x60, 0xfa, 0xc5, 0xe5, 0x54, 0x2a, 0x77, 0x3a, 0xa4, 0x4f, 0xbc, 0xfe, 0xdf, 0x7c, 0x19, 0x3b, 0xc2, 0xc5, 0x99 };

const uint8_t CURVE_OETH_POOL_ADDRESS[ADDRESS_LENGTH] = {0x94, 0xb1, 0x74, 0x76, 0xa9, 0x3b, 0x32,
                                                         0x62, 0xd8, 0x7b, 0x9a, 0x32, 0x69, 0x65,
                                                         0xd1, 0xe9, 0x1f, 0x9c, 0x13, 0xe7};

const uint8_t CURVE_STETH_POOL_ADDRESS[ADDRESS_LENGTH] = { 0xdc, 0x24, 0x31, 0x6b, 0x9a, 0xe0, 0x28, 0xf1, 0x49, 0x7c, 0x27, 0x5e, 0xb9, 0x19, 0x2a, 0x3e, 0xa0, 0xf6, 0x70, 0x22 };

const uint8_t CURVE_THREE_POOL_ADDRESS[ADDRESS_LENGTH] = { 0xbe, 0xbc, 0x44, 0x78, 0x2c, 0x7d, 0xb0, 0xa1, 0xa6, 0x0c, 0xb6, 0xfe, 0x97, 0xd0, 0xb4, 0x83, 0x03, 0x2f, 0xf1, 0xc7 };

const uint8_t CURVE_FRAXSDAI_POOL_ADDRESS[ADDRESS_LENGTH] = { 0xce, 0x64, 0x31, 0xd2, 0x1e, 0x3f, 0xb1, 0x03, 0x6c, 0xe9, 0x97, 0x3a, 0x33, 0x12, 0x36, 0x8e, 0xd9, 0x6f, 0x5c, 0xe7 };

const uint8_t FRAX_ADDRESS[ADDRESS_LENGTH] = { 0x85, 0x3d, 0x95, 0x5a, 0xce, 0xf8, 0x22, 0xdb, 0x05, 0x8e, 0xb8, 0x50, 0x59, 0x11, 0xed, 0x77, 0xf1, 0x75, 0xb9, 0x9e };

const uint8_t SDAI_ADDRESS[ADDRESS_LENGTH] = { 0x83, 0xf2, 0x0f, 0x44, 0x97, 0x5d, 0x03, 0xb1, 0xb0, 0x9e, 0x64, 0x80, 0x9b, 0x75, 0x7c, 0x47, 0xf9, 0x42, 0xbe, 0xea };

const uint8_t PAYPOOL_ADDRESS[ADDRESS_LENGTH] = { 0x38, 0x3e, 0x6b, 0x44, 0x37, 0xb5, 0x9f, 0xff, 0x47, 0xb6, 0x19, 0xcb, 0xa8, 0x55, 0xca, 0x29, 0x34, 0x2a, 0x85, 0x59 };

const uint8_t PYUSD_ADDRESS[ADDRESS_LENGTH] = { 0x6c, 0x3e, 0xa9, 0x03, 0x64, 0x06, 0x85, 0x20, 0x06, 0x29, 0x07, 0x70, 0xbe, 0xdf, 0xca, 0xba, 0x0e, 0x23, 0xa0, 0xe8 };

const uint8_t FRAX_PYUSD_POOL_ADDRESS[ADDRESS_LENGTH] = { 0xa5, 0x58, 0x8f, 0x7c, 0xdf, 0x56, 0x08, 0x11, 0x71, 0x0a, 0x2d, 0x82, 0xd3, 0xc9, 0xc9, 0x97, 0x69, 0xdb, 0x1d, 0xcb };

const uint8_t TRI_CRYPTO_USDC_ADDRESS[ADDRESS_LENGTH] = { 0x7f, 0x86, 0xbf, 0x17, 0x7d, 0xd4, 0xf3, 0x49, 0x4b, 0x84, 0x1a, 0x37, 0xe8, 0x10, 0xa3, 0x4d, 0xd5, 0x6c, 0x82, 0x9b };