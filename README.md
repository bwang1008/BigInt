# BigInt

Big-integer library for C++. This is a personal project for practicing C++.

## Compilation

Starting from the root of the repository,

```sh
mkdir build
cd build
cmake -S .. -B .
make
```

## Running tests

```sh
./tests
```

.clang-tidy generated via

```sh
clang-tidy --dump-config --checks=*,-fuchsia-default-arguments-calls,-fuchsia-trailing-return,-llvm-header-guard,-google-runtime-references -- --std=c++20 > .clang-tidy
```

Ignored checks:

- `fuchsia-default-arguments-calls`: extraneous warnings on standard-library function calls
- `fuchsia-trailing-return`: conflicts with modernize-use-trailing-return-type
- `llvm-header-guard`: do not want to expose full path of file
- `google-runtime-references`: want to pass in a non-const object by reference

.clang-format generated via

```sh
clang-format --style=llvm -dump-config > .clang-format
```
