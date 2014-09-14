![daydream logo](http://imon.nu/daydream/daydream.gif)

A general purpose engine written in C++, made by students at [Blekinge Insitute of Technology](http://www.bth.se/eng) for learning purposes.

## Design Goals
* **Purely component based** Provides a pure, component based entity system where a *Component* contains only data and all logic resides in *Systems*, and where *Systems* communicate through *Events*.
* **Modular and extensible** Every *System* is packaged with its relevant *Components* and *Events*. A non-critical *System* could easily be loaded dynamically. 
* **Cross-platform** Using only open source, cross-platform libraries the engine strives for complete platform freedom. 

## Roadmap
https://trello.com/b/PJo9tRDa/daydream

## Documentation
http://link.to.doxygen.goes.here

### Building
The source code is heavily dependent on new features of C++11 and builds using CMake 2.8.x.
Project files are also available for Visual Studio 2012/2013, compiled using Visual C++ 2013 along with pre-built binaries for bundled libraries.

### Dependencies

#### Bundled libraries
Libraries bundled along with binaries for Windows, available in the *libs* directory of the source tree.

| Project                                                       | Version      | License                                                                                                                                                                            |
| ------------------------------------------------------------- | ------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **[GLFW](http://www.glfw.org)**                               | 3.0.4        | [zlib/libpng License](http://www.glfw.org/license.html)                                                                                                                            |
| **[GLM](http://glm.g-truc.net/0.9.5/index.html)**             | 0.9.5.4      | [MIT License](http://glm.g-truc.net/copying.txt)                                                                                                                                   |
| **[GLEW](http://glew.sourceforge.net)**                       | 1.11.0       | [Modified BSD License](http://glew.sourceforge.net/glew.txt), [Mesa 3-D License](http://glew.sourceforge.net/mesa.txt), [Khronos License](http://glew.sourceforge.net/khronos.txt) |
| **[Assimp](http://assimp.sourceforge.net)**                   | 3.1.1        | [BSD 3-Clause License](http://assimp.sourceforge.net/main_license.html)                                                                                                            |
| **[libpng](http://www.libpng.org/pub/png/libpng.html)**       | 1.6.12       | [libpng License](http://www.libpng.org/pub/png/src/libpng-LICENSE.txt)                                                                                                             |
| ~~**[SOIL](http://www.lonesock.net/soil.html)**~~             | July 7, 2008 | Public Domain                                                                                                                                                                      |

#### External libraries
Libraries that are too big to be bundled with the project.

| Project                                                    | Version     | License                                                                     | Root folder environment variable (Windows) |
| ---------------------------------------------------------- | ----------- | --------------------------------------------------------------------------- | ------------------------------------------ |
| **[Boost](http://www.boost.org)**                          | 1.55.0+     | [Boost Software License, Version 1.0](http://www.boost.org/LICENSE_1_0.txt) | BOOST_1_55_0_ROOT                          |

#### Proprietary libraries
Libraries only available under non-free licences. This list should eventually be empty!

| Project                                                    | Version     | License                                                                     | Root folder environment variable (Windows) |
| ---------------------------------------------------------- | ----------- | --------------------------------------------------------------------------- | ------------------------------------------ |
| ~~**[Havok Physics](http://havok.com/products/physics)**~~ | 2013-1-0-r1 | Havok Limited Use License Agreement for PC XS 03-20-2013                    | HAVOK_2013_1_0_r1_ROOT                     |
| ~~**[FMOD](http://www.fmod.com)**~~                        | 4.44.42     | [FMOD Non-Commercial License](http://www.fmod.com/files/public/LICENSE.TXT) |                                            |

## Authors
* [Adam *"Stiffly"* Byléhn](https://github.com/Stiffly)
* [Tobias *"Tleety"* Dahl](https://github.com/Tleety)
* [Simon *"Sippeangelo"* Holmberg](https://github.com/sippeangelo)
* [Viktor Ljung](https://github.com/ViktorLjung)