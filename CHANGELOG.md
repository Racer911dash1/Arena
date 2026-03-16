# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/).

This project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

Everything under the Unreleased section are planned features, but may not be guaranteed.

### Added

- Added new functions:
	- arena_strgenerate
		- Return a randomly generated ascii string of specified characters with specified length.

### Changed

- Update the unit tests to use the Unity test framework.

## [1.3.2] - 2026-03-16

### Changed

- When running install or install-local, it will also compile the code if it wasn't done beforehand.

## [1.3.1] - 2026-03-15

### Added

- Added new Makefile rules:
	- install-local
		- Install the headers and libraries locally inside ~/.local.
		- Does not require sudo permissions.
	- uninstall-local
		- Remove the locally installed headers and libraries.
		- Does not require sudo permissions.
- Added shell scripts to assist with installing and uninstalling the libraries.

### Changed

- Update README.md
	- Noteworthy since it was missing important info.

### Fixed

- Renamed project name: arena -> libarena
	- Apparently it's not optional to exclude the lib prefix, as it is needed for the linker flag
	- But include directories will still retain their name.

- Changed permissions of the .so file from 644 to 755

## [1.3.0] - 2026-03-11

### Added

- Added new functions:
	- arena_merge
		- Merge two arenas together, with one getting ownership of all pointers while the other one has theirs invalidated.
	- arena_strnjoin
		- Join two strings together, but only appending a specified amount of bytes.
	- arena_getnextline
		- Return a single line from the specified file descriptor, returning the following line in the next function call.

### Changed

- Changed the directory layout of the unit tests to be in line with other project layouts.
- Makefile has those changes applied approapriately, also added the -g compiler flag to CFLAGS

## [1.2.1] - 2026-03-09

### Added

- Added an assert for calloc and added a check for most other asserts to make debugging easier.

### Removed

- Removed a unit test that just straight up segfaults.

## [1.2.0] - 2026-03-09

### Added

- Added a new function:
	- arena_strreplace
		- Search and replace parts of a string with another string.

### Changed

- Reworked Unit tests. The function name will be printed out when a test fails.

## [1.1.1] - 2026-03-08

### Added

- Added -fsanitize=address for the unit tests to check for memory leaks.

### Changed

- Replaced the hardcoded ARENA_BUFFER_SIZE with sysconf(_SC_PAGESIZE).
- Moved most headers to the files that actually need them.
- arena_calloc checks are more thorough by actually checking if the allocated range is initialized to 0.

### Removed

- Unnecessary header inclusions in the unit tests.

## [1.1.0] - 2026-03-07

### Added

- Added new functions:
	- arena_substr
		- Create a substring from another string.
	- arena_strjoin
		- Create a new string by joining two strings together.

- Added a new Makefile rule:
	- help
		- Prints out all rules and what each one does.
		- Currently set as the default, so running make without a target operand will run this rule.

### Changed

- Changed a variable modifier to be consistent with the rest of the codebase.

### Fixed

- Fixed Doxygen errors.

## [1.0.1] - 2026-03-06

### Added

- Added a few more unit tests.

### Changed

- Changed default definition of ARENA_BUFFER_SIZE from 64 bytes to 4096 bytes
- arena_strdup
	- Replaced arena_calloc with arena_malloc
- arena_strndup
	- Replaced arena_calloc with arena_malloc
- arena_strsplit_collapse
	- Replaced arena_calloc with arena_malloc
- arena_strsplit_preserve
	- Replaced arena_calloc with arena_malloc
- arena_strtrim
	- Replaced arena_calloc with arena_malloc if the resulting string is not empty.

### Fixed

- Fixed Doxygen errors.

## [1.0.0] - 2026-03-06

### Added

- changelog.md