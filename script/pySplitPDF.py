import sys
import os
import re

# read input text file to str var
File = open(sys.argv[1],"rt")
str = File.read()

File.close()

headerStr = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://autosar.org/schema/r4.0 AUTOSAR_00046.xsd">
  <!-- AUTOSAR CAN Configuration Parameter Definition -->
  <!--
    Document Owner:                 AUTOSAR
    Document Responsibility:        AUTOSAR
    Document Identification Number: 289
    Document Status:                Final
    Part of AUTOSAR Standard:       Classic Platform
    Part of AUTOSAR Release:        4.4.0
  -->
  <ADMIN-DATA>
    <DOC-REVISIONS>
      <DOC-REVISION>
        <REVISION-LABEL>4.4.0</REVISION-LABEL>
        <ISSUED-BY>AUTOSAR</ISSUED-BY>
      </DOC-REVISION>
    </DOC-REVISIONS>
  </ADMIN-DATA>
  <AR-PACKAGES>
    <!-- AR-Package: AUTOSAR -->
    <AR-PACKAGE UUID="ECUC:AUTOSAR">
      <SHORT-NAME>AUTOSAR</SHORT-NAME>
      <AR-PACKAGES>
        <!-- AR-Package: AUTOSAR -->
        <AR-PACKAGE UUID="ECUC:ECUCDEFS">
          <SHORT-NAME>EcucDefs</SHORT-NAME>
          <ELEMENTS>
            <ECUC-DEFINITION-COLLECTION UUID="ECUC:4c30de73-30fc-43b3-a1b3-e74211eedff3">
              <SHORT-NAME>AUTOSARParameterDefinition</SHORT-NAME>
              <MODULE-REFS>
                <MODULE-REF DEST="ECUC-MODULE-DEF">/AUTOSAR/EcucDefs/<OUTPUTMODULE></MODULE-REF>
              </MODULE-REFS>
            </ECUC-DEFINITION-COLLECTION>
"""
footerStr = """
          </ELEMENTS>
        </AR-PACKAGE>
      </AR-PACKAGES>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
"""

# find all string match pattern
for matchStr in re.findall( \
    r'(^\s+<!-- Module Definition: \w+ -->[\s\S]+?(</ECUC-MODULE-DEF>))', \
    str,re.M|re.S):
    # print (matchStr[0])
    # print (matchStr[1])
    # input()
    module = re.match(r'^.+<!-- Module Definition: (\w+) -->', matchStr[0], \
    re.M|re.S)
    if module:
        # Get file name
        path = "./modules/"+module.group(1).upper()+"/PDF"
        os.makedirs(path)
        f = open(os.path.join(path,"AUTOSAR_MCAL_" + module.group(1).upper() \
        + "_PDF.arxml"), "x")
        f.seek(0, 2)
        f.write(headerStr.replace("<OUTPUTMODULE>", module.group(1)))
        f.seek(0, 2)
        f.write(matchStr[0])
        f.seek(0, 2)
        f.write(footerStr)
        print ("Output module PDF file: ", module.group(1).upper())
        f.close()
    else:
        print ("No match")
    # input()
# print (str)