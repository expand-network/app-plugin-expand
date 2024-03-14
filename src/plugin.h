/*******************************************************************************
 *   Plugin Expand
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

#pragma once

#include <string.h>
#include "eth_internals.h"
#include "eth_plugin_interface.h"


// Xmacro helpers to define the enum and map
#define TO_ENUM(selector_name, selector_id)  selector_name,
#define TO_VALUE(selector_name, selector_id) selector_id,


// All possible selectors of plugin.
#define SELECTORS_LIST(X)                           \
    X(SWAP_EXACT_ETH_FOR_TOKENS, 0x7ff36ab5)         \
    X(SWAP_EXACT_TOKENS_FOR_ETH, 0x18cbafe5)          \
    X(SWAP_EXACT_TOKENS_FOR_TOKENS, 0x38ed1739)        \
    X(APPROVE, 0x095ea7b3)                              \
    X(WRAP, 0xd0e30db0 )                                 \
    X(UNWRAP, 0x2e1a7d4d)                                 \
    X(CURVE_EXCHANGE, 0x3df02124)                          \
    X(BATCH_SWAP, 0x945bcec9)                               \
    X(TRANSFER, 0xa9059cbb)                                  \

// This enum will be automatically expanded to hold all selector names.
typedef enum selector_e {
    SELECTORS_LIST(TO_ENUM) SELECTOR_COUNT,
} selector_t;

// This array will be automatically expanded to map all selector_t names with the correct value.
extern const uint32_t SELECTORS[SELECTOR_COUNT];

// Enumeration used to parse the smart contract data.
typedef enum {
    AMOUNT_SENT,
    MIN_AMOUNT_RECEIVED,
    TOKEN_SENT,
    TOKEN_RECEIVED,
    BENEFICIARY,
    KIND,
    PATH_OFFSET,
    PATH_LENGTH,
    UNEXPECTED_PARAMETER,
} parameter;

// Shared global memory with Ethereum app
typedef struct context_s {
    uint8_t amount_sent[INT256_LENGTH];
    uint8_t amount_received[INT256_LENGTH];
    uint8_t beneficiary[ADDRESS_LENGTH];
    uint8_t token_sent[ADDRESS_LENGTH];
    uint8_t token_received[ADDRESS_LENGTH];
    uint8_t decimals_sent;
    uint8_t decimals_received;
    bool token_sent_found;
    bool token_received_found;
    bool kind;
    uint8_t skip;
    char ticker_sent[MAX_TICKER_LEN];
    char ticker_received[MAX_TICKER_LEN];



    uint8_t next_param;  // Set to be the next param we expect to parse.
    uint16_t offset;     // Offset at which the array or struct starts.
    bool go_to_offset;   // If set, will force the parsing to iterate through parameters until
                         // `offset` is reached.

    selector_t selectorIndex;
} context_t;



#define DEFAULT_TICKER ""

#define ETH_TICKER "ETH"
#define WETH_TICKER "WETH"
#define OETH_TICKER   "OETH"


#define DAI_TICKER "DAI"
#define DAI_DECIMALS WEI_TO_ETHER

#define SDAI_TICKER "sDAI"
#define SDAI_DECIMALS WEI_TO_ETHER

#define USDC_TICKER "USDC"
#define USDC_DECIMALS 6

#define USDT_TICKER "USDT"
#define USDT_DECIMALS 6

// #define LIT_TICKER "LIT"
#define LINK_TICKER "LINK" //18
#define SUSHI_TICKER "SHUSHI" // 18
#define SYNTHETIC_TICKER "SUSD" // 18
#define UNI_TICKER "UNI"  // 18
#define TUSD_TICKER "TUSD" // 18
#define USDP_TICKER "USDP"  // 18
#define WBTC_TICKER "WBTC" // 8
#define STETH_TICKER   "STETH"
#define STETH_DECIMALS WEI_TO_ETHER

#define RETH_TICKER   "RETH"
#define RETH_DECIMALS WEI_TO_ETHER

#define FRXETH_TICKER   "FRXETH"
#define FRXETH_DECIMALS WEI_TO_ETHER
#define SFRXETH_TICKER "sfrxETH"


#define OUSD_TICKER   "OUSD"
#define OUSD_DECIMALS WEI_TO_ETHER

#define WOETH_TICKER "WOETH"
#define WOUSD_TICKER "WOUSD"

#define FRAX_TICKER "FRAX"
#define FRAX_DECIMALS WEI_TO_ETHER

#define PYUSD_TICKER "PYUSD"


extern const uint8_t NULL_ETH_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t WETH_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t FRXETH_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t RETH_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t STETH_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t OETH_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t OUSD_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t DAI_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t USDC_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t USDT_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t CURVE_OETH_POOL_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t CURVE_OUSD_POOL_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t CURVE_POOL_ETH_ADDRESS[ADDRESS_LENGTH];
// extern const uint8_t LIT_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t LINK_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t SUSHI_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t SYNTHETIC_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t UNI_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t TUSD_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t USDP_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t WBTC_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t FRAX_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t CURVE_STETH_POOL_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t CURVE_THREE_POOL_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t CURVE_FRAXSDAI_POOL_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t SDAI_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t PAYPOOL_ADDRESS[ADDRESS_LENGTH];
extern const uint8_t PYUSD_ADDRESS[ADDRESS_LENGTH];





#define ADDRESS_IS_NETWORK_TOKEN(_addr)                  \
    (!memcmp(_addr, NULL_ETH_ADDRESS, ADDRESS_LENGTH) || \
     !memcmp(_addr, CURVE_POOL_ETH_ADDRESS, ADDRESS_LENGTH))
#define ADDRESS_IS_OETH(_addr)   (!memcmp(_addr, OETH_ADDRESS, ADDRESS_LENGTH))
#define ADDRESS_IS_WETH(_addr)   (!memcmp(_addr, WETH_ADDRESS, ADDRESS_LENGTH))
#define ADDRESS_IS_STETH(_addr)  (!memcmp(_addr, STETH_ADDRESS, ADDRESS_LENGTH))
#define ADDRESS_IS_RETH(_addr)   (!memcmp(_addr, RETH_ADDRESS, ADDRESS_LENGTH))
#define ADDRESS_IS_FRXETH(_addr) (!memcmp(_addr, FRXETH_ADDRESS, ADDRESS_LENGTH))
#define ADDRESS_IS_OUSD(_addr)   (!memcmp(_addr, OUSD_ADDRESS, ADDRESS_LENGTH))
#define ADDRESS_IS_DAI(_addr)    (!memcmp(_addr, DAI_ADDRESS, ADDRESS_LENGTH))
#define ADDRESS_IS_USDC(_addr)   (!memcmp(_addr, USDC_ADDRESS, ADDRESS_LENGTH))
#define ADDRESS_IS_USDT(_addr)   (!memcmp(_addr, USDT_ADDRESS, ADDRESS_LENGTH))
// #define ADDRESS_IS_LIT(_addr)    (!memcmp(_addr, LIT_ADDRESS, ADDRESS_LENGTH))
#define ADDRESS_IS_LINK(_addr)    (!memcmp(_addr, LINK_ADDRESS, ADDRESS_LENGTH))
#define ADDRESS_IS_SUSHI(_addr)    (!memcmp(_addr, SUSHI_ADDRESS, ADDRESS_LENGTH))
#define ADDRESS_IS_SYNTHETIC(_addr)    (!memcmp(_addr, SYNTHETIC_ADDRESS, ADDRESS_LENGTH))
#define ADDRESS_IS_UNI(_addr)    (!memcmp(_addr, UNI_ADDRESS, ADDRESS_LENGTH))
#define ADDRESS_IS_TUSD(_addr)    (!memcmp(_addr, TUSD_ADDRESS, ADDRESS_LENGTH))
#define ADDRESS_IS_USDP(_addr)    (!memcmp(_addr, USDP_ADDRESS, ADDRESS_LENGTH))
#define ADDRESS_IS_WBTC(_addr)    (!memcmp(_addr, WBTC_ADDRESS, ADDRESS_LENGTH))
#define ADDRESS_IS_FRAX(_addr)     (!memcmp(_addr, FRAX_ADDRESS, ADDRESS_LENGTH))
#define ADDRESS_IS_SDAI(_addr)     (!memcmp(_addr, SDAI_ADDRESS, ADDRESS_LENGTH))
#define ADDRESS_IS_PYUSD(_addr)     (!memcmp(_addr, PYUSD_ADDRESS, ADDRESS_LENGTH))

// Check if the context structure will fit in the RAM
ASSERT_SIZEOF_PLUGIN_CONTEXT(context_t);


static inline const char *get_ticker_for_address(uint8_t address[ADDRESS_LENGTH]) {
    if(ADDRESS_IS_NETWORK_TOKEN(address) ) {
        return ETH_TICKER;
    } else if (ADDRESS_IS_WETH(address)) {
        return WETH_TICKER;
    } else if (ADDRESS_IS_DAI(address)) {
        return DAI_TICKER; 
    } else if (ADDRESS_IS_USDC(address)) {
        return USDC_TICKER;
    } else if (ADDRESS_IS_OETH(address)) {
        return OETH_TICKER;
    } else if (ADDRESS_IS_LINK(address)) {
        return LINK_TICKER;
    } else if (ADDRESS_IS_FRXETH(address)) {
        return FRXETH_TICKER;
    } else if (ADDRESS_IS_RETH(address)) {
        return RETH_TICKER;
    } else if (ADDRESS_IS_STETH(address)) {
        return STETH_TICKER;
    } else if (ADDRESS_IS_OUSD(address)) {
        return OUSD_TICKER;
    } else if (ADDRESS_IS_USDT(address)) {
        return USDT_TICKER;
    } else if (ADDRESS_IS_SUSHI(address)) {
        return SUSHI_TICKER;
    } else if (ADDRESS_IS_SYNTHETIC(address)) {
        return SYNTHETIC_TICKER;
    } else if(ADDRESS_IS_UNI(address)) {
        return UNI_TICKER;
    } else if(ADDRESS_IS_TUSD(address)) {
        return TUSD_TICKER;
    } else if(ADDRESS_IS_USDP(address)) {
        return USDP_TICKER;
    } else if(ADDRESS_IS_WBTC(address)) {
        return WBTC_TICKER;
    } else if(ADDRESS_IS_FRAX(address)) {
        return FRAX_TICKER;
    } else if (ADDRESS_IS_SDAI(address)) {
        return SDAI_TICKER; 
    } else if (ADDRESS_IS_PYUSD(address)) {
        return PYUSD_TICKER; 
    }
    else {
        return DEFAULT_TICKER;
    } 
}

static inline void printf_hex_array(const char *title __attribute__((unused)),
                                    size_t len __attribute__((unused)),
                                    const uint8_t *data __attribute__((unused))) {
        PRINTF(title);
        for (size_t i = 0; i < len; ++i){
            PRINTF("%02x", data[i]);
        }
        PRINTF("\n");
}
                    
static inline const uint8_t get_decimals_for_ticker(const char *ticker __attribute__((unused))) {
    if(strcmp(ticker, USDC_TICKER)== 0 
              || strcmp(ticker, USDT_TICKER)== 0
              || strcmp(ticker, PYUSD_TICKER)== 0 ) {
        return USDC_DECIMALS;
    } else if(strcmp(ticker, WETH_TICKER) == 0 
             || strcmp(ticker, DAI_TICKER) == 0
             || strcmp(ticker, LINK_TICKER) == 0
             ) {
        return WEI_TO_ETHER;
    } else {
        return WEI_TO_ETHER;
    }
}