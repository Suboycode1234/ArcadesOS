This is the repo used to store an OS im trying to build, ArcadeOS. WINDOWS ONLY
This project is in its early stages and currently can only boot into bios with no graphics or GUI.
QEMU (https://www.qemu.org/download/), MSYS2 (https://www.msys2.org/), and Vscode (optional if you want to make changes) ARE REQUIRED to launch this program! ALL COMMANDS ARE RUN IN MSYS2 UCRT64 TERMINAL. REMOVE SPEECH MARKS (" ") THEN COPY PASTE
To use msys2 ucrt64 to open this OS you must first install qemu and add it to your windows PATH.
Then run the command in msys2 : 
"export PATH=$PATH:/c/i686-elf-tools-windows/bin"
  then test
"i686-elf-gcc --version"
   afterward, navigate to your project folder using "cd". a list of possible loctions i provided below (replce %userprofile% with your userprofile:
"cd /c/Users/%USERPROFILE%/ArcadeOS"
"cd /c/Users/%USERPROFILE%/Desktop/ArcadeOS"
"cd /c/Users/%USERPROFILE%/Downloads/ArcadeOS"
"cd /c/Users/%USERPROFILE%/Documents/ArcadeOS"

  To clean up and run the program run:
"make clean"
"make"
"make run"

