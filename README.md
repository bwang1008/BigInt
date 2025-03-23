# BigInt

Big-integer library for C++. This is a personal project for practicing C++.

## Compilation

Starting from the root of the repository,

```sh
mkdir debug
cd debug
cmake -S .. -B . -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug
make
```

Change `debug` to `release` and `-DCMAKE_BUILD_TYPE=Debug` to `-DCMAKE_BUILD_TYPE=Release` for release version.


## Running tests with coverage:

```sh
ctest -T test -T coverage
```
using `ctest` version `3.16.3`.

View coverage results with

```sh
gcov --display-progress --function-summaries --human-readable --use-colors CMakeFiles/tests.dir/BigInt/tests/test_big_int.cpp.o --stdout
```

View coverage results with `gcovr` library:

First install it:

```sh
python3 -m venv .venv
source .venv/bin/activate
pip3 install gcovr==8.2  # Last version that supports Python 3.8
```

```sh
cd debug
gcovr -r .. --object-directory . --exclude _deps/catch2-src --html-theme github.dark-blue --html-details --output example_html.details.html
```
then open file `example_html.details.html` in a browser.

Branch coverage doesn't really mean anything: https://stackoverflow.com/questions/42003783/lcov-gcov-branch-coverage-with-c-producing-branches-all-over-the-place


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
