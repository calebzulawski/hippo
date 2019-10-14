# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.2.3] - 2019-10-14
### Fixed
- Fixed broken implementation of `bool` (again)

## [0.2.2] - 2019-10-14
### Fixed
- Fixed broken implementations of `bool` and native arrays
- Fixed `char *` not printing as a string if `string.h` isn't included

## [0.2.1] - 2019-10-14
### Fixed
- Add workaround for [an old GCC bug](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=47226) in `std::variant` and `std::tuple` printers

## [0.2.0] - 2019-10-13
### Added
- This change log
- Documentation!
- Support for the following types:
  - `enum` via reflection macros
  - pointers
  - `std::pair`, `std::tuple`
  - `std::variant`
  - `std::bitset`
  - `std::chrono::duration`
  - `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`
  - `std::complex`
  - `std::atomic`
- Formatting via `hippo::formatter`
### Fixed
- `HIPPO_MEMBER_EXPR` can now be used with lambdas
- A variety of bugs caught by unit tests
- Warnings presented by `-Wall -Wextra -Wpedantic` in GCC and Clang
### Changed
- Standard library printers are now available in `hippo/std/*.h`

## [0.1.1] - 2019-04-03
### Fixed
- Mark `hippo::condense` inline

## [0.1.0] - 2019-04-03
### Added
- Initial implementation of pretty printers

[unreleased]: https://github.com/calebzulawski/hippo/compare/0.2.3...master
[0.2.3]: https://github.com/calebzulawski/hippo/compare/0.2.2...0.2.3
[0.2.2]: https://github.com/calebzulawski/hippo/compare/0.2.1...0.2.2
[0.2.1]: https://github.com/calebzulawski/hippo/compare/0.2.0...0.2.1
[0.2.0]: https://github.com/calebzulawski/hippo/compare/0.1.1...0.2.0
[0.1.1]: https://github.com/calebzulawski/hippo/compare/0.1.0...0.1.1
[0.1.0]: https://github.com/calebzulawski/hippo/releases/tag/0.1.0
