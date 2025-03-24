#!/usr/bin/bash

set -euo pipefail

# usage:
# $ ./lint.sh <file_name>
# Example:
# $ ./lint.sh main.hpp

clang-tidy -p build-debug "$1" -config='' --quiet
