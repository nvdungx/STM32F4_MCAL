from dataclasses import dataclass
from enum import Enum
import argparse
import os, pathlib, logging

class LayerType(Enum):
    UC_DRIV = "Microcontroller Drivers"
    ON_BOARD_DEV_ABST = "On-board Device Abstraction"
    SYS_SERV = "System Services"
    MEM_DRIV = "Memory Drivers"
    MEM_HWABST = "Memory HW Abstraction"
    MEM_SERV = "Memory Services"
    CRYPT_DRIV = "Crypto Drivers"
    CRYPT_HWABST = "Crypto HW Abstraction"
    CRYPT_SERV = "Crypto Services"
    WLCOM_DRIV = "Wireless Comm. Drivers"
    WLCOM_HWABST = "Wireless Comm. HW Abstraction"
    OFF_BOARD_COM_SERV = "Off-board Comm. Services"
    COM_DRIV = "Communication Drivers"
    COM_HWABST = "Communication HW Abstraction"
    COM_SERV = "Communication Services"
    IO_DRIV = "I/O Drivers"
    IO_HWABST = "I/O HW Abstraction"
    CMPLX_DRIV = "Complex Drivers"
    LIB = "Libraries"
    COMMON = "Common components"
    RTE = "Runtime Environment"
    APP = "Application Layer"

@dataclass
class BswModule:
    shortName : str
    abbr : str
    id : int
    layer : LayerType
    def __str__(self) -> str:
        return f"{self.abbr}: {self.shortName}"
    def __eq__(self, __o: object) -> bool:
        return self.abbr.capitalize() == str(__o).capitalize()

BswModuleList : list[BswModule] = [
    BswModule("GPT Driver", "Gpt", 100, LayerType.UC_DRIV),
    BswModule("MCU Driver", "Mcu", 101, LayerType.UC_DRIV),
    BswModule("CAN Driver", "Can", 80, LayerType.COM_DRIV),
]

class ValidateModule(argparse.Action):
    def __init__(self, option_strings, dest, nargs=None, **kwargs):
        if nargs is not None:
            raise ValueError("nargs not allowed")
        super().__init__(option_strings, dest, **kwargs)
    def __call__(self, parser, namespace, values, option_string=None):
        # validate module
        if (values not in BswModuleList):
            logging.error(f"Module \"{values}\" does not existed")
            print("---- List of valid BswModule ----:")
            for module in BswModuleList:
                print(module)
            os._exit(0)
        else:
            setattr(namespace, self.dest, values)

class ValidateFile(argparse.Action):
    def __init__(self, option_strings, dest, nargs=None, **kwargs):
        if nargs is not None:
            raise ValueError("nargs not allowed")
        super().__init__(option_strings, dest, **kwargs)
    def __call__(self, parser, namespace, values, option_string=None):
        # validate file
        temp = pathlib.Path(str(values))
        if (temp.is_dir()):
            setattr(namespace, self.dest, values)
            if (not temp.exists()):
                os.makedirs(temp)
        elif (temp.is_file() and temp.exists()):
            setattr(namespace, self.dest, str(temp.absolute()))
        else:
            logging.error(f"Invalid input: \"{values}\" is not valid for {self.dest}")