from enum import Enum
import os, logging
import argparse, pathlib
from typing import Any, Callable, Iterable, Sequence, Generic, TypeVar
import json, yaml
import xml.etree.ElementTree as ET
import xml.parsers
import cerberus
from jinja2 import Environment, FileSystemLoader

from validate_input import ValidateModule, ValidateFile

logging.basicConfig(format="%(levelname)s: %(message)s", level=logging.DEBUG)

if __name__ == "__main__":
    # parse arguments <module>, <CDF.arxml>, <output>
    parser = argparse.ArgumentParser(prog="CfgGenerateExe",
    description = "Generate AUTOSAR MCAL configured source code from Module's configured parameters definition arxml(CDF)",
    add_help=True, exit_on_error=True)

    parser.add_argument("module", type=str, help="name of target MCAL module", action=ValidateModule)
    parser.add_argument("CDF", type=str, help="module's CDF file", action=ValidateFile)
    parser.add_argument("output_dir", type=str, help="output directory to store generated configuration source", action=ValidateFile)
    args = parser.parse_args()

    # load arxml file
    tree = ET.parse(args.CDF)
    root = tree.getroot()
    # validate arxml content - module

    # load template environment

    # generate configuration source from CDF to output path

    os._exit(0)
