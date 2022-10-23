ECHO "Executing 1_setup.bat"

ECHO "Download msys-x86_64 self-extracting archive"
curl -LO https://github.com/msys2/msys2-installer/releases/download/2022-05-03/msys2-base-x86_64-20220503.sfx.exe

ECHO "Running MSYS2 Installer"
msys2-base-x86_64-20220503.sfx.exe

ECHO "Run MSYS2 for First-Run Initialization"
@REM `-c` Referes to the command to run 
START /WAIT msys64\usr\bin\bash -l -c "exit"

EXIT 0