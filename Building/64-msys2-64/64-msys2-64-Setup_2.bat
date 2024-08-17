ECHO "Removing MSYS2 Installer"
del msys2-base-x86_64-20220503.sfx.exe
ECHO "Run MSYS2 for Package Updating"
START /WAIT msys64\usr\bin\bash -l -c "yes | Pacman -Syu && exit"

EXIT 0