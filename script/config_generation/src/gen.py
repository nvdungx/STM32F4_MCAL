import os
import argparse
import pathlib
import string
import xml
import json
import yaml
import cerberus
from jinja2 import Environment, FileSystemLoader

if __name__ == "__main__":
    # parse arguments <module>, <CDF.arxml>, <output>
    parser = argparse.ArgumentParser(prog="CfgGenerateExe",
        description = "Generate AUTOSAR MCAL configured source code from\
 Module's configured parameters definition arxml(CDF)", add_help=True, exit_on_error=True)

    parser.add_argument("module", type=string, help="name of target MCAL module")
    parser.add_argument("cdf", type=string, help="module's CDF file")
    parser.add_argument("output", type=string, help="output directory to store\
 generated configuration source")
    

    # load arxml file

    # validate arxml content - module

    # load template environment

    # validate output path

    # generate configuration source from CDF to output path

    os.exit(0)
