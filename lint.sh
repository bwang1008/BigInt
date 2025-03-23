#!/usr/bin/bash

set -euo pipefail

# usage:
# $ ./lint.sh <file_name>
# Example:
# $ ./lint.sh main.hpp

clang-tidy -p debug "$1" -config='' --quiet
