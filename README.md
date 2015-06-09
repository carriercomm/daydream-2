![daydream logo](http://imon.nu/daydream/daydream.gif)

A general purpose engine written in C++, for learning purposes, by students at [Blekinge Insitute of Technology](http://www.bth.se/eng).

[![linux build status badge](http://jenkins.daydreamengine.org:2323/job/daydream-linux-gcc/lastBuild)](http://jenkins.daydreamengine.org/job/daydream-linux-gcc/lastBuild) [![windows build status badge](http://jenkins.daydreamengine.org:2323/job/daydream-windows-msvc/lastBuild)](http://jenkins.daydreamengine.org/job/daydream-windows-msvc/lastBuild) [![tests badge](http://jenkins.daydreamengine.org:2323/job/daydream-linux-gcc/lastBuild/testReport?text=tests)](http://jenkins.daydreamengine.org/job/daydream-linux-gcc/lastBuild/testReport)
## Design Goals
* **Purely component based** Provides a pure, component based entity system where a *Component* contains only data and all logic resides in *Systems*, and where *Systems* communicate through *Events*.
* **Modular and extensible** Every *System* is packaged with its relevant *Components* and *Events*. A non-critical *System* could easily be loaded dynamically. 
* **Cross-platform** Using only open source, cross-platform libraries the engine strives for complete platform freedom. 

## Roadmap
https://trello.com/b/PJo9tRDa/daydream

## Documentation
http://daydreamengine.org

### Building
The source code is heavily dependent on new features of C++11 and builds using CMake 2.8.x.
Project files are also available for Visual Studio 2012/2013, compiled using Visual C++ 2013 along with pre-built binaries for bundled libraries.

### Dependencies

#### Bundled libraries
See [daydream-deps](https://github.com/sippeangelo/daydream-deps) submodule.

#### External libraries
Libraries that are too big to be bundled with the project.

| Project                                                    | Version     | License                                                                     | Root folder environment variable (Windows) |
| ---------------------------------------------------------- | ----------- | --------------------------------------------------------------------------- | ------------------------------------------ |
| **[Boost](http://www.boost.org)**                          | 1.57.0+     | [Boost Software License, Version 1.0](http://www.boost.org/LICENSE_1_0.txt) | BOOST_1_55_0_ROOT                          |

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

## License
Daydream Engine is licensed under the [GNU Lesser General Public License](https://github.com/sippeangelo/daydream/blob/master/COPYING.LESSER)
