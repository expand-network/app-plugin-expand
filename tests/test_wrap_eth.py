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

with open("%s/WETH.json" % (ABIS_FOLDER)) as file:
    contract = Web3().eth.contract(
        abi = json.load(file),
        address=bytes.fromhex("C02aaA39b223FE8D0A0e5C4F27eAD9083C756Cc2")
    )

def test_wrap_eth(backend, firmware, navigator, test_name):
    client = EthAppClient(backend)

    data = contract.encodeABI("deposit",[

    ])
    print(data)
    print(get_selector_from_data(data))

    # return

    with client.set_external_plugin(PLUGIN_NAME,
                                    contract.address,
                                    get_selector_from_data(data)):
        pass
    
    with client.sign("m/44'/60'/1'/0/0",{
        "nonce": 25,
        "maxFeePerGas": Web3.to_wei(145,"gwei"),
        "maxPriorityFeePerGas": Web3.to_wei(1.5,"gwei"),
        "gas": 180000,
        "to": contract.address,
        "value": Web3.to_wei(6,"ether"),
        "chainId": ChainId.ETH,
        "data": data
    }):
        
        if firmware.device.startswith("nano"):
            navigator.navigate_until_text_and_compare(NavInsID.RIGHT_CLICK,
                                                      [NavInsID.BOTH_CLICK],
                                                      "Accept",
                                                      ROOT_SCREENSHOT_PATH,
                                                      test_name)
        else:
            navigator.navigate_until_text_and_compare(NavInsID.USE_CASE_REVIEW_TAP,
                                                      [NavInsID.USE_CASE_REVIEW_CONFIRM,
                                                       NavInsID.USE_CASE_STATUS_DISMISS],
                                                       "Hold to Sign",
                                                       ROOT_SCREENSHOT_PATH,
                                                       test_name)