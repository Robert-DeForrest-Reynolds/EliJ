ECHO "Run MSYS2 and install MinGW64 toolchain"
START /B /WAIT msys64\usr\bin\bash -l -c "yes | Pacman -Syu && printf '3\ny' | Pacman -S --needed base-devel mingw-w64-x86_64-toolchain"
START /B /WAIT msys64\usr\bin\bash -l -c "yes | Pacman -S mingw-w64-x86_64-python"

EXIT 0