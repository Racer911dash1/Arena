# Changelog

All notable changes to this project will be documented in this file.

This project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html)

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