# EVM C++ Utils

[![readme style standard](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

EVM utility functions, types, and interfaces library

Header-only C++20 library providing virtual classes for EVM state & accounts.
Other types : Bytes ( bytecode ), Address ( 20-byte array ), Block and TX Contexts.
Includes utils for parsing bytecode, addresses, and contracts.

## Table of Contents

- [Usage](#usage)
- [Dependencies](#dependencies)
- [Media](#media)
- [Maintainer](#maintainer)
- [License](#license)

## Usage

Add include path to compilation `-I./path/to/evm-cpp-utils/include`.

Import types and/or utils into your code.
```
#include <evm-cpp-utils/types.h>
#include <evm-cpp-utils/utils.h>
```

Use functionality as defined in header files under `src/types/` & `src/utils/`, respectively.

Inherit from virtual classes to modify and/or wrap EVM base implementation.

**NOTE:** [Dependencies](#dependencies) must be linked into compilation aswell.

## Dependencies

- [intx][intx] : 256-bit (32-byte) unsigned integers
- [ethash][ethash] : Ethereum hash functions

## Media

![EVM State Chart]([images]/evm-cpp-utils/evm-state-chart.jng)

## Maintainer

Brandon Roberts [@b-j-roberts]

## License

[MIT][MIT]

[intx]: https://github.com/chfast/intx
[ethash]: http://github.com/chfast/ethash
[MIT]: LICENSE
[@b-j-roberts]: https://github.com/b-j-roberts
[images]: https://github.com/FraktalLabs/docs/blob/master/images
