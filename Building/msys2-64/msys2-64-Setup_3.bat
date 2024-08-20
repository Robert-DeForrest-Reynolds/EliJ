ECHO "Executing Phase 3/4 of Setup"
ECHO "Run MSYS2 and install MinGW64 toolchain"
START /B /WAIT msys64\usr\bin\bash -l -c "yes | Pacman -Syu"
START /B /WAIT msys64\usr\bin\bash -l -c "Printf '\n yes' | Pacman -S --needed base-devel mingw-w64-x86_64-clang"

ECHO "Run MSYS2 and install MinGW64 Python
START /B /WAIT msys64\usr\bin\bash -l -c "Printf '\n yes' | Pacman -S --needed mingw-w64-x86_64-python"

EXIT 0