# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

* IFileSystem interface
* Added mount function to the FileSystem

### Changed

* Updated Lua from 5.1 to 5.3.4
* Restructured source files
* Don't allow the FileSystem to be copied
* Mount filesystem externally

## [0.0.2] - 2018-02-11

### Added

* PhysicsFS is used for a virtual filesystem abstraction
* spdlog logging library is used for logging
* Basic layout of FileSystem class
* Implemented ls, mkdir and rmdir

### Changed

* The file listing function now uses PhysicsFS

## [0.0.1] - 2018-02-09

### Added

* Initial prototype with C++, Sol 2 and Lua
* Initial directory structure and repository setup
