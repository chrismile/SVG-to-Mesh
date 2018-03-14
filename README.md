## SVG-to-Mesh

Converts SVG vector graphics files to a format usable as assets in a 2D game engine.

## Usage

WIP


## Compilation

The program has three dependencies - libpng, Boost Filesystem and TinyXML2. On Ubuntu 17.10 for example, you can install all necessary packages with this command:

```
sudo apt-get install git cmake libpng-dev libboost-filesystem-dev libtinyxml2-dev
```

Similar packages should also be available on other distributions.

To start the compilation, launch the following commands in the directory of the project:

```
mkdir build
cd build
rm -rf *
cmake ..
make
```

To install the program to /usr/local, optionally run 

```
sudo make install
```

If doxygen is installed on your system, you can call

```
doxygen doxygen.conf
```

in the main directory to generate the documentation for this project.


## License

Copyright (c) 2018, Christoph Neuhauser

GNU GPLv3 (for more details see LICENSE file)
