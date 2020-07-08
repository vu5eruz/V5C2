![V5C2 Logo](https://raw.githubusercontent.com/vu5eruz/V5C2/master/data/images/V5c2Logo.png)

# Vu5eruz's Chess For Two
> Small and simple chess editor

V5C2 is a desktop application that allows you to edit a chess board through commands or algebraic notation (WIP), this way you can play chess with your peers using nothing but plain text messages.

## Building

To build V5C2 from the repository you will need git, a C++17 compiler and CMake.  The only dependency (SFML) is included in the repository as a submodule.

If you are on Linux, you should install the dependencies and their respective development files for SFML: `freetype`, `x11`, `xrandr`, `udev`, `opengl`, `flac`, `ogg`, `vorbis`, `vorbisenc`, `vorbisfile`, `openal` and `pthread`.  The exact name of the packages may vary in your distribution.

If you are on Windows, you can use Visual Studio 2019 Developer Command Prompt along with Git for Windows.

```shell
# Ubuntu: Install dependencies
sudo apt-get install build-essential cmake libflac-dev libgl1-mesa-dev libopenal-dev libudev-dev libvorbis-dev libxrandr-dev

# Get the source code
git clone --recurse-submodules -- https://github.com/vu5eruz/V5C2.git
cd V5C2

# Windows: You should use "md" instead of "mkdir"
mkdir build
cd build

# Build V5C2
# You can use Release instead of Debug
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=output
cmake --build . --config Debug
cmake --build . --config Debug --target install
```

If everything went fine, you should have all the necesary file and a ready to run executable in the `V5C2/build/output/V5C2` folder.

## Licensing

```
Copyright (C) 2020 vu5eruz (undefined@disroot.org)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
```
