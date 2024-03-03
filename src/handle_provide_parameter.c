#include "plugin.h"

static void handle_swap_exact_eth_for_tokens(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }

    switch (context->next_param) {
        case MIN_AMOUNT_RECEIVED:
            copy_parameter( context->amount_received,
                            msg->parameter,
                            sizeof(context->amount_received)
                            );
            // printf_hex_array("amount_rec: ", ADDRESS_LENGTH, context->amount_received);
            context->next_param = PATH_OFFSET;
            break;
        case PATH_OFFSET:
            context->offset = U2BE(msg->parameter, PARAMETER_LENGTH - 2);
            context->next_param = BENEFICIARY;
            break;
        case BENEFICIARY:  // to
            copy_address(context->beneficiary, msg->parameter, sizeof(context->beneficiary));
            context->next_param = PATH_LENGTH;
            context->go_to_offset = true;
            break;
        case PATH_LENGTH:
            context->offset = msg->parameterOffset - SELECTOR_SIZE + PARAMETER_LENGTH * 2;
            context->go_to_offset = true;
            context->next_param = TOKEN_RECEIVED;
            break;
        case TOKEN_RECEIVED:  // path[1] -> contract address of token received
            copy_address(context->token_received, msg->parameter, sizeof(context->token_received));
            // printf_hex_array("TOKEN RECEIVED: ", ADDRESS_LENGTH, context->token_received);
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_swap_exact_tokens_for_eth (ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }

    switch (context->next_param) {
        case AMOUNT_SENT:
            copy_parameter(context->amount_sent,
                           msg->parameter,
                           sizeof(context->amount_sent));
            context->next_param = MIN_AMOUNT_RECEIVED;
            break;
        case MIN_AMOUNT_RECEIVED:
            copy_parameter(context->amount_received, 
                            msg->parameter,
                            sizeof(context->amount_received));
            context->next_param = PATH_OFFSET;
            break;
        case PATH_OFFSET:  // path
            context->offset = U2BE(msg->parameter, PARAMETER_LENGTH - 2);
            context->next_param = BENEFICIARY;
            break;
        case BENEFICIARY:  // to
            copy_address(context->beneficiary, msg->parameter, sizeof(context->beneficiary));
            context->next_param = PATH_LENGTH;
            context->go_to_offset = true;
            break;
        case PATH_LENGTH:
            // context->offset = msg->parameterOffset - SELECTOR_SIZE + PARAMETER_LENGTH;
            // context->go_to_offset = true;
            // context->skip += 1;
            context->next_param = TOKEN_SENT;
            break;
        case TOKEN_SENT:
            copy_address(context->token_sent, msg->parameter, sizeof(context->token_sent));
            context->next_param = TOKEN_RECEIVED;
            printf_hex_array("TOKEN_SENT: ", ADDRESS_LENGTH, context->token_sent);
            if(context->selectorIndex == SWAP_EXACT_TOKENS_FOR_TOKENS){
                context->skip += 1;
            }
            break;
        case TOKEN_RECEIVED:  // path[1] -> contract address of token received
            copy_address(context->token_received, msg->parameter, sizeof(context->token_received));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_approve_erc20 (ethPluginProvideParameter_t *msg, context_t *context) {

    switch (context->next_param) {
        case BENEFICIARY: 
            copy_address(context->beneficiary, msg->parameter, sizeof(context->beneficiary));
            // printf_hex_array("BENEFICIARY: ", ADDRESS_LENGTH, context->beneficiary);
            context->next_param = AMOUNT_SENT;
            break;
        case AMOUNT_SENT:
            copy_parameter(context->amount_sent, msg->parameter, sizeof(context->amount_sent));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

// static void handle_transfer_erc20 (ethPluginProvideParameter_t *msg, context_t *context) {

//     switch (context->next_param) {
//         case BENEFICIARY: 
//             copy_address(context->beneficiary, msg->parameter, sizeof(context->beneficiary));
//             // printf_hex_array("BENEFICIARY: ", ADDRESS_LENGTH, context->beneficiary);
//             context->next_param = AMOUNT_SENT;
//             break;
//         case AMOUNT_SENT:
//             copy_parameter(context->amount_sent, msg->parameter, sizeof(context->amount_sent));
//             context->next_param = UNEXPECTED_PARAMETER;
//             break;
//         default:
//             PRINTF("Param not supported: %d\n", context->next_param);
//             msg->result = ETH_PLUGIN_RESULT_ERROR;
//             break;
//     }
// }

static void handle_wrap_unwrap_WETH (ethPluginProvideParameter_t *msg, context_t *context) {

    switch(context->next_param) {
        case AMOUNT_SENT:
            copy_parameter(context->amount_sent, msg->parameter, sizeof(context->amount_sent));
            // printf_hex_array("AMOUNT_SENT:", ADDRESS_LENGTH, msg->parameter);
            // PRINTF("amount wrap..%d\n", context->amount_sent);
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_token_sent_curve_pool(ethPluginProvideParameter_t *msg, context_t *context) {
    memset(context->token_sent, 0, sizeof(context->token_sent));
    PRINTF("\n inside handle \n");

    bool is_oeth = memcmp(CURVE_OETH_POOL_ADDRESS,
                          msg->pluginSharedRO->txContent->destination,
                          ADDRESS_LENGTH) == 0;    
    // bool is_oeth = true;
    PRINTF("\n Its is_oeth: \n");

    if (is_oeth) {
        switch (U2BE(msg->parameter, PARAMETER_LENGTH - 2)) {
            case 0:
                // printf_hex_array()
                memcpy(context->token_sent, NULL_ETH_ADDRESS, ADDRESS_LENGTH);
                break;
            case 1:
                memcpy(context->token_sent, OETH_ADDRESS, ADDRESS_LENGTH);
                break;
            default:
                PRINTF("Param not supported\n");
                break;
        }
    } else {
        switch (U2BE(msg->parameter, PARAMETER_LENGTH - 2)) {
            case 0:
                memcpy(context->token_sent, OUSD_ADDRESS, ADDRESS_LENGTH);
                break;
            case 1:
                memcpy(context->token_sent, DAI_ADDRESS, ADDRESS_LENGTH);
                break;
            case 2:
                memcpy(context->token_sent, USDC_ADDRESS, ADDRESS_LENGTH);
                break;
            case 3:
                memcpy(context->token_sent, USDT_ADDRESS, ADDRESS_LENGTH);
                break;
            default:
                PRINTF("Param not supported\n");
                break;
        }
    }

    printf_hex_array("TOKEN SENT:__ ", ADDRESS_LENGTH, context->token_sent);
}

static void handle_token_received_curve_pool(ethPluginProvideParameter_t *msg, context_t *context) {
    memset(context->token_received, 0, sizeof(context->token_received));

    bool is_oeth = memcmp(CURVE_OETH_POOL_ADDRESS,
                          msg->pluginSharedRO->txContent->destination,
                          ADDRESS_LENGTH) == 0;
    PRINTF("Inside rec\n");
    // determine token addresses of curve pools based on contract address and
    // value of i/j params
    if (is_oeth) {
        switch (U2BE(msg->parameter, PARAMETER_LENGTH - 2)) {
            case 0:
                memcpy(context->token_received, NULL_ETH_ADDRESS, ADDRESS_LENGTH);
                break;
            case 1:
                memcpy(context->token_received, OETH_ADDRESS, ADDRESS_LENGTH);
                break;
            default:
                PRINTF("Param not supported\n");
                break;
        }
    } else {
        switch (U2BE(msg->parameter, PARAMETER_LENGTH - 2)) {
            case 0:
                memcpy(context->token_received, OUSD_ADDRESS, ADDRESS_LENGTH);
                break;
            case 1:
                memcpy(context->token_received, DAI_ADDRESS, ADDRESS_LENGTH);
                break;
            case 2:
                memcpy(context->token_received, USDC_ADDRESS, ADDRESS_LENGTH);
                break;
            case 3:
                memcpy(context->token_received, USDT_ADDRESS, ADDRESS_LENGTH);
                break;
            default:
                PRINTF("Param not supported\n");
                break;
        }
    }
    printf_hex_array("TOKEN RECEIVED: ", ADDRESS_LENGTH, context->token_received);
}



static void handle_curve_swap(ethPluginProvideParameter_t *msg, context_t *context) {
    PRINTF("\n Inside curve swap \n");
    switch (context->next_param) {
        case TOKEN_SENT:
            PRINTF("Inside TOKEN_SENT\n");
            handle_token_sent_curve_pool(msg, context);
            context->next_param = TOKEN_RECEIVED;
            break;
        case TOKEN_RECEIVED:
            handle_token_received_curve_pool(msg, context);
            context->next_param = AMOUNT_SENT;
            break;
        case AMOUNT_SENT:
            memcpy(context->amount_sent, msg->parameter, INT256_LENGTH);
            context->next_param = MIN_AMOUNT_RECEIVED;
            break;
        case MIN_AMOUNT_RECEIVED:
            memcpy(context->amount_received, msg->parameter, PARAMETER_LENGTH);
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        default:
            PRINTF("Param not supported\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_batch_swap(ethPluginProvideParameter_t *msg, context_t *context) {
    PRINTF("\n Inside HandleBatch Swap\n");
    switch (context->next_param) {
        case KIND:
            context->kind = msg->parameter;
            PRINTF("Kind: %d\n", context->kind);
            context->skip += 4;
            context->next_param = BENEFICIARY;
            break;
        case BENEFICIARY:
            copy_address(context->beneficiary, msg->parameter, sizeof(context->beneficiary));
            printf_hex_array("BENEFICIARY: ", ADDRESS_LENGTH, context->beneficiary);
            context->skip += 9;
            context->next_param = AMOUNT_SENT;
            break;
        case AMOUNT_SENT:
            if(context->kind)
                copy_parameter(context->amount_received,
                            msg->parameter,
                            sizeof(context->amount_received));
            else
                 copy_parameter(context->amount_sent,
                            msg->parameter,
                            sizeof(context->amount_sent));
            printf_hex_array("AMOUNT SENT: ", ADDRESS_LENGTH, msg->parameter);
            context->skip += 9;
            context->next_param = TOKEN_SENT;
            break;
        case TOKEN_SENT:
            copy_address(context->token_sent, msg->parameter, sizeof(context->token_sent));
            context->skip += 1;
            printf_hex_array("TOKEN SENT: ", ADDRESS_LENGTH, context->token_sent);
            context->next_param = TOKEN_RECEIVED;
            break;
        case TOKEN_RECEIVED:
            copy_address(context->token_received, msg->parameter, sizeof(context->token_received));
            printf_hex_array("TOKEN RECEIVED: ", ADDRESS_LENGTH, context->token_received);
            context->skip += 1;
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        // case MIN_AMOUNT_RECEIVED:
        //     if(context->kind)
        //         copy_parameter(context->amount_sent,
        //                     msg->parameter,
        //                     sizeof(context->amount_sent));
        //     else
        //         copy_parameter(context->amount_received,
        //                     msg->parameter,
        //                     sizeof(context->amount_received));
        //     context->next_param = UNEXPECTED_PARAMETER;
        //     break;
            
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }

}

void handle_provide_parameter(ethPluginProvideParameter_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    // We use `%.*H`: it's a utility function to print bytes. You first give
    // the number of bytes you wish to print (in this case, `PARAMETER_LENGTH`) and then
    // the address (here `msg->parameter`).
    PRINTF("expand plugin provide parameter: offset %d\nBytes: %.*H\n",
           msg->parameterOffset,
           PARAMETER_LENGTH,
           msg->parameter);

    msg->result = ETH_PLUGIN_RESULT_OK;

    if (context->skip) {
        context->skip--;
        return;
    }
    PRINTF("RUNNIG PROVIDE PARAM %d\n", context->selectorIndex);
    PRINTF("U2B....%d\n", U2BE(msg->parameter, PARAMETER_LENGTH - 2));
    printf_hex_array("destination: ", ADDRESS_LENGTH, msg->pluginSharedRO->txContent->destination);

    // EDIT THIS: adapt the cases and the names of the functions.
    switch (context->selectorIndex) {
        case SWAP_EXACT_ETH_FOR_TOKENS:
            handle_swap_exact_eth_for_tokens(msg, context);
            break;
        case SWAP_EXACT_TOKENS_FOR_ETH:
        case SWAP_EXACT_TOKENS_FOR_TOKENS:
            handle_swap_exact_tokens_for_eth(msg, context);
            break;
        case APPROVE:
        case TRANSFER:
            PRINTF("Running Approve\n");
            handle_approve_erc20(msg, context);
            break;
        case UNWRAP:
            PRINTF("Running UnWrap.....\n");
            handle_wrap_unwrap_WETH(msg, context);
            break;
        case CURVE_EXCHANGE:
            PRINTF("Running Curve....\n");
            handle_curve_swap(msg, context);
            break;
        case BATCH_SWAP:
            PRINTF("Running Balancer.....");
            handle_batch_swap(msg, context);
            break;
        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
