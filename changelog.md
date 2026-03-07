# Changelog

All notable changes to this project will be documented in this file.

This project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html)

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