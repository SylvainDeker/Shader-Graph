# Shader-Graph
Software aimed at GLSL code generation


### Purpose

Shader-Graph is a project developpement, suggested by Mathias Paulin a member of STORM team at IRIT (www.irit.fr). This software is a GUI node editor prototype aimed at GLSL code generation.


### Platforms

* OSX (Apple Clang - LLVM 3.6), Linux (x64, gcc-8.0): [![Build Status](https://travis-ci.com/sylvaindeker/Shader-Graph.svg?branch=master)](https://travis-ci.com/sylvaindeker/Shader-Graph)

<!-- * Windows (Win32, x64, msvc2017, MinGW 5.3):  -->

### Dependencies

* gcc >= 8
* Qt >= 5.2
* CMake >= 3.10
* Catch2
* nodeeditor


### Functionnalities


### Building
#### Linux

~~~
git clone https://github.com/sylvaindeker/Shader-Graph.git
cd Shader-Graph
mkdir build
cd build
cmake ..
make -j
~~~
