import os
import sys
import zipfile

dir_name = sys.argv[1]

zipFileName = sys.argv[2] + ".zip"

filePaths = []

for root, directories, files in os.walk(dir_name):
  # print(root)
  # print (directories)
  # print (files)
  # print ("next")
  for filename in files:
    # print (filename)
    filePath = os.path.join(root, filename)
    filePaths.append(filePath)

# input()
print (filePaths)

zip_file = zipfile.ZipFile(zipFileName, 'w')
for file in filePaths:
  zip_file.write(file)
