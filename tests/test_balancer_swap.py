from pathlib import Path
import json
import os
from web3 import Web3
from eth_typing import ChainId
from ledger_app_clients.ethereum.client import EthAppClient, StatusWord
from ledger_app_clients.ethereum.utils import get_selector_from_data
from ragger.navigator import NavInsID
from .utils import get_appname_from_makefile

ROOT_SCREENSHOT_PATH = Path(__file__).parent
ABIS_FOLDER = "%s/abis" % (os.path.dirname(__file__))
PLUGIN_NAME = get_appname_from_makefile()

with open("%s/balancer.abi.json" % (ABIS_FOLDER)) as file:
    contract = Web3().eth.contract(
        abi = json.load(file),
        address=bytes.fromhex("BA12222222228d8Ba445958a75a0704d566BF2C8")
    )

def test_balancer_swap(backend, firmware, navigator, test_name):
    client = EthAppClient(backend)

    params = [
        0,  # uint8 parameter
        [  # Array of swaps
            {  # First swap
                "poolId": "0x6f0ed6f346007563d3266de350d174a831bde0ca0001000000000000000005db",
                "assetInIndex": 0,
                "assetOutIndex": 1,
                "amount": 1200000000,
                "userData": "0x"
            },
            {  # Second swap
                "poolId": "0x9232a548dd9e81bac65500b5e0d918f8ba93675c000200000000000000000423",
                "assetInIndex": 1,
                "assetOutIndex": 2,
                "amount": 0,
                "userData": "0x"
            }
        ],
        [
            "0xA0b86991c6218b36c1d19D4a2e9Eb0cE3606eB48",  # Address 1
            "0xC02aaA39b223FE8D0A0e5C4F27eAD9083C756Cc2",  # Address 2
            "0xfd0205066521550D7d7AB19DA8F72bb004b4C341"   # Address 3
        ],
        (  # Tuple of address, bool, address, bool
            "0x817C48bB59e866d5baefC9A90d04a0CE4e7D543b",  # Sender address
            False,  # FromInternalBalance
            "0x817C48bB59e866d5baefC9A90d04a0CE4e7D543b",  # Recipient address
            False   # ToInternalBalance
        ),
        [
            1200000000,  # int256 parameter
            0,            # int256 parameter
            -39616218905472636815920  # int256 parameter
        ],
        1708935859  # uint256 parameter
        ]



    data = contract.encodeABI("batchSwap",params)
    print(data)
    print(get_selector_from_data(data))


    with client.set_external_plugin(PLUGIN_NAME,
                                    contract.address,
                                    get_selector_from_data(data)):
        pass
    
    with client.sign("m/44'/60'/1'/0/0",{
        "nonce": 30,
        "maxFeePerGas": Web3.to_wei(145,"gwei"),
        "maxPriorityFeePerGas": Web3.to_wei(1.5,"gwei"),
        "gas": 180000,
        "to": contract.address,
        "value": 1,
        "chainId": ChainId.ETH,
        "data": data
    }):
        return
        
        # if firmware.device.startswith("nano"):
        #     navigator.navigate_until_text_and_compare(NavInsID.RIGHT_CLICK,
        #                                               [NavInsID.BOTH_CLICK],
        #                                               "Accept",
        #                                               ROOT_SCREENSHOT_PATH,
        #                                               test_name)
        # else:
        #     navigator.navigate_until_text_and_compare(NavInsID.USE_CASE_REVIEW_TAP,
        #                                               [NavInsID.USE_CASE_REVIEW_CONFIRM,
        #                                                NavInsID.USE_CASE_STATUS_DISMISS],
        #                                                "Hold to Sign",
        #                                                ROOT_SCREENSHOT_PATH,
        #                                                test_name)