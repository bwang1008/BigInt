# BigInt

[![Master build](https://github.com/bwang1008/BigInt/actions/workflows/cmake-single-platform.yml/badge.svg)](https://github.com/bwang1008/BigInt/actions/workflows/cmake-single-platform.yml)

Big-integer library for C++, with a focus on integer multiplication. This is a personal project for practicing C++.

## Features

### Constructor


Constructors can take in an integer, a string of numeric digits, or a literal of numeric digits suffixed by `_b`:

```cpp
#include "BigInt/BigInt/include/big_int.hpp"

using BigInt::operator""_b;

BigInt::BigInt x{123};
BigInt::BigInt y{"123456789123456789"};
BigInt::BigInt z = -99999999999999999999_b;
```

A copy of an existing `BigInt::BigInt` can be made:
```
BigInt::BigInt x2 = x;
```

### Output

The base-10 string representation of a `BigInt::BigInt` can be obtained with `.str()` method:

```cpp
#include <string>
#include "BigInt/BigInt/include/big_int.hpp"

BigInt::BigInt x{123};
const std::string x_representation = x.str();
```

The string representation is used when put in an output stream:

```cpp
#include <iostream>
#include "BigInt/BigInt/include/big_int.hpp"

BigInt::BigInt x{123};
std::cout << "Value of x = " << x << std::endl;
```

Output:

```sh
Value of x = 123
```

### Arithmetic Operations

- Negation (unary `-`)
- Addition (`+`, `+=`)
- Subtraction (`-`, `-=`)
- Multiplication (`*`, `*=`)
- Division (`/`, `/=`)
- Modulo (`%`, `%=`)

```cpp
#include <iostream>
#include "BigInt/BigInt/include/big_int.hpp"

BigInt::BigInt x{123};
BigInt::BigInt y{11};

std::cout << "1) Value of -x   : " << -x << std::endl;
std::cout << "2) Value of x + y: " << x + y << std::endl;
std::cout << "3) Value of x - y: " << x - y << std::endl;
std::cout << "4) Value of x * y: " << x * y << std::endl;
std::cout << "5) Value of x / y: " << x / y << std::endl;
std::cout << "6) Value of x % y: " << x % y << std::endl;
```

Output:

```txt
1) Value of -x   : -123
2) Value of x + y: 134
3) Value of x - y: 112
4) Value of x * y: 1353
5) Value of x / y: 11
6) Value of x % y: 2
```

### Relational Operations

Operators `==`, `!=`, `<`, `<=`, `>`, `>=` that compare the values of two `BigInt::BigInt`:

```cpp
#include <iostream>
#include "BigInt/BigInt/include/big_int.hpp"

BigInt::BigInt x{123};
BigInt::BigInt y{11};

std::cout << "1) Value of (x == y): " << x == y << std::endl;
std::cout << "2) Value of (x != y): " << x != y << std::endl;
std::cout << "3) Value of (x > y) : " << x > y << std::endl;
std::cout << "4) Value of (x >= y): " << x >= y << std::endl;
std::cout << "5) Value of (x < y) : " << x < y << std::endl;
std::cout << "6) Value of (x <= y): " << x <= y << std::endl;
```

Output:

```
1) Value of (x == y): 0
2) Value of (x != y): 1
3) Value of (x > y) : 1
4) Value of (x >= y): 1
5) Value of (x < y) : 0
6) Value of (x <= y): 0
```

### Helper Methods

#### abs

Get the absolute value of a `BigInt::BigInt`:

```cpp
#include <iostream>
#include "BigInt/BigInt/include/big_int.hpp"

BigInt::BigInt x{123};
BigInt::BigInt y{-456};

BigInt::BigInt x_abs = x.abs();
BigInt::BigInt y_abs = y.abs();
std::cout << "1) x.abs() = " << x_abs << std::endl;
std::cout << "2) y.abs() = " << y_abs << std::endl;
```

Output:

```cpp
1) x.abs() = 123
2) y.abs() = 456
```

### Helper Functions

#### compare

Returns -1 if `x < y`, 0 if `x == y`, or 1 if `x > y`:

```cpp
#include <iostream>
#include "BigInt/BigInt/include/big_int.hpp"

BigInt::BigInt x{123};
BigInt::BigInt y{456};

int comparison_result = BigInt::BigInt::compare(x, y);
std::cout << "1) Comparison of x and y: " << comparison_result << std::endl;
```

Output:

```txt
1) Comparison of x and y: -1
```

#### quotient_and_remainder_grade_school

Returns the division and remainder of x divided by y as a pair.

```cpp
#include <iostream>
#include <utility>
#include "BigInt/BigInt/include/big_int.hpp"

BigInt::BigInt x{123};
BigInt::BigInt y{11};

std::pair<BigInt::BigInt, BigInt::BigInt> division_and_remainder = BigInt::BigInt::quotient_and_remainder_grade_school(x, y);

std::cout << "1) Result of division: " << division_and_remainder.first << std::endl;
std::cout << "2) Result of remainder: " << division_and_remainder.second << std::endl;
```

Output:

```txt
1) Result of divison: 11
2) Result of remainder: 2
```

#### gcd

Return the greatest common divisor of two `BigInt::BigInt`:

```cpp
#include <iostream>
#include <utility>
#include "BigInt/BigInt/include/big_int.hpp"

BigInt::BigInt x{21};
BigInt::BigInt y{56};

BigInt::BigInt g = BigInt::BigInt::gcd(x, y);
std::cout << "1) Greatest common divisor of x and y: " << g << std::endl;
```

Output:

```txt
1) Greatest common divisor of x and y: 7
```
