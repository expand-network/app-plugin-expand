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

with open("%s/fraxsdai_pool.json" % (ABIS_FOLDER)) as file:
    contract = Web3().eth.contract(
        abi = json.load(file),
        address=bytes.fromhex("cE6431D21E3fb1036CE9973a3312368ED96F5CE7")
    )

def test_curve_fraxsdai(backend, firmware, navigator, test_name):
    client = EthAppClient(backend)

    data = contract.encodeABI("exchange",[
        0,
        1,
        10039684262590636607929,
        9478816521072598208434
    ])
    print(data)
    print(get_selector_from_data(data))

    # return

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
        
        # return
        
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
            

