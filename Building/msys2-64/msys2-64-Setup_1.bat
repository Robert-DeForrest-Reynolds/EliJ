ECHO "Executing Phase 1/4 of Setup"

ECHO "Downloading msys-x86_64 self-extracting archive"
curl -LO https://github.com/msys2/msys2-installer/releases/download/2024-07-27/msys2-base-x86_64-20240727.sfx.exe

ECHO "Running MSYS2 Installer"
msys2-base-x86_64-20240727.sfx.exe

ECHO "Run MSYS2 for First-Run Initialization"
@REM `-c` Referes to the command to run 
START /WAIT msys64\usr\bin\bash -l -c "exit"

EXIT 0