# System

**System** is a sort of simulated OS that eventually might end up in a game
or otherwise remains a neat tech demo that I have thought about for many years.

## Idea

Inspired by Introversion Software's [Uplink (2001)](http://store.steampowered.com/app/1510/Uplink/), Exosyphen Studios' [Hacker Evolution (2007)](http://store.steampowered.com/app/70100/Hacker_Evolution/), as well as a game that was started many, many years ago with Visual Basic, the idea behind System is very basic, to have a sort of simulated OS with which you can do all sorts of things Starting out with a basic terminal and later on also focusing on GUI elements.

The technical idea is, to have a all applications on the OS written in Lua, while providing a backend APIs from C++ for interaction with OS layers (filesystem, window manager, graphics, networking, etc.). Not only allows this setup to easily write applications for the System, but it will even allow users to edit or extend applications from within the System.

## Goals

### Short term

* [X] Proof of concept with [Sol 2](https://github.com/ThePhD/sol2) and `std::cout` / `std::cin`
* [X] Setup source structure and repository
* [ ] Basic architecture for locating, loading and executing Lua scripts in a terminal
* [ ] Filesystem backend API with real files but a virtualized environment

### Future

* [ ] SFML integration for 2D rendering
* [ ] SFGUI integration for window management
* [ ] Window manager backend API, move all GUI code to Lua
* [ ] Basic rendering backend API (check out [Luna](https://github.com/XyronLabs/Luna/))
* [ ] Networking backend API
* [ ] Researching good ways to simulate networking
* [ ] Researching how much realism should exist in such a project
* [ ] ???

## License

This software is dual licensed under the Public Domain and the MIT license, choose whichever you prefer. See the LICENSE.md file for more details.

## Credits

* [Lukas Dürrenberger](https://twitter.com/DarkCisum) - Author
* [Elias Daler](https://twitter.com/EliasDaler) - Recommending the awesome library Sol 2
* [Sol v2.0](https://github.com/ThePhD/sol2) - Awesome C++ <-> Lua API wrapper library
