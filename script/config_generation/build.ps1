# activate virtual environment
.\.venv\Scripts\Activate.ps1

# build executable generation tool


# build GUI
pyinstaller --onedir --specpath "./" --workpath "./temp" --distpath "./build" --name CfgGenerateTool `
--add-data="./ui/icons;./ui/icons" `
--add-data="./templates" --paths "./src:./ui/src" --icon="./ui/icons/icon-app.ico" `
--windowed --clean --noconfirm main.py

Copy-Item -Recurse -Path ".venv\Lib\site-packages\PySide6\plugins" -Destination "build\CfgGenerateTool\PySide6"
Copy-Item -Recurse -Path ".venv\Lib\site-packages\PySide6\translations" -Destination "build\CfgGenerateTool\PySide6"
Copy-Item -Recurse -Path ".venv\Lib\site-packages\PySide6\qt.conf" -Destination "build\CfgGenerateTool\PySide6"

