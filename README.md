# XYZParser

Very simple XYZ molecule file parser written roughly according to [this](https://openbabel.org/wiki/XYZ_(format)) definition.

The parser and the tests are completely header only. Boost is the only dependency. It has been tested with boost 1.75. Compile with clang using the following command:
```
clang++ TestRunner.cpp -std=c++20 -o test
```
