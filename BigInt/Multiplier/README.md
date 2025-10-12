# Multiplier Class

The Multiplier class contains the main logic for different multiplication algorithms. The base Multiplier class contains an abstract method to multiply two positive BigInts.


## Adding a new Multiplier subclass

The below contains an outline on adding a new Multiplier subclass that implements a multiplication algorithm:

* Add a new class in `BigInt/Multiplier/multiplier.hpp` that inherits from Multiplier
* Update `BigInt/BigInt/include/big_int.hpp` that declares the new class and makes it a friend of BigInt
* Implement the new class's overridden `multiply_positive()` function in a new file under `BigInt/Multiplier/src/`
* Copy the existing tests in `BigInt/Multiplier/tests/test_multiplication_methods.cpp` and apply to new Multiplier subclass
* Update `BigInt/Multiplier/CMakeLists.txt` to add the new source file to `MultiplierLib`
* Run the tests to make sure nothing is clearly wrong
