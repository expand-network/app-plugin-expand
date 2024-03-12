#include "plugin_utils.h"
#include "plugin.h"

void handle_init_contract(ethPluginInitContract_t *msg) {
    PRINTF("Expand pulgin handle_init_contract");
    if (msg->interfaceVersion != ETH_PLUGIN_INTERFACE_VERSION_LATEST) {
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }

    // checking `context_t` struct size 
    // (defined by `msg->pluginContextLength`).
    if (msg->pluginContextLength < sizeof(context_t)) {
        PRINTF("Plugin parameters structure is bigger than allowed size\n");
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    context_t *context = (context_t *) msg->pluginContext;

    // Initialize the context (to 0).
    memset(context, 0, sizeof(*context));

    size_t index;
    if (!find_selector(U4BE(msg->selector, 0), SELECTORS, SELECTOR_COUNT, &index)) {
        PRINTF("Error: selector not found!\n");
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }
    context->selectorIndex = index;
    // check for overflow
    if ((size_t) context->selectorIndex != index) {
        PRINTF("Error: overflow detected on selector index!\n");
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    // Set `next_param` to be the first field we expect to parse.
    // to parse.
    switch (context->selectorIndex) {
        case SWAP_EXACT_ETH_FOR_TOKENS:
            context->next_param = MIN_AMOUNT_RECEIVED;
            break;
        case SWAP_EXACT_TOKENS_FOR_ETH:
        case SWAP_EXACT_TOKENS_FOR_TOKENS:
        case UNWRAP:
            context->next_param = AMOUNT_SENT;
            break;
        case APPROVE:
        case TRANSFER:
            context->next_param = BENEFICIARY;
            break;
        case WRAP:
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        case CURVE_EXCHANGE:
            if (memcmp(CURVE_OETH_POOL_ADDRESS,
                       msg->pluginSharedRO->txContent->destination,
                       ADDRESS_LENGTH) == 0 ||
                memcmp(CURVE_OUSD_POOL_ADDRESS,
                       msg->pluginSharedRO->txContent->destination,
                       ADDRESS_LENGTH) == 0 ||
                memcmp(CURVE_STETH_POOL_ADDRESS,
                       msg->pluginSharedRO->txContent->destination,
                       ADDRESS_LENGTH) == 0 ||
                memcmp(CURVE_THREE_POOL_ADDRESS,
                       msg->pluginSharedRO->txContent->destination,
                       ADDRESS_LENGTH) == 0 
                       ) {
                context->next_param = TOKEN_SENT;
                break;
            }
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
        case BATCH_SWAP:
            context->next_param = KIND;
            break;
        default:
            PRINTF("Missing selectorIndex: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    // Return valid status.
    msg->result = ETH_PLUGIN_RESULT_OK;
}
