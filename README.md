## About

This repository contains a header only template library that requires at least C++11 to compile. The headers are in /src folder, see [the doc](#documentation-of-src) for examples of usage. Note that only things that matter for users are listed.

Compiler extensions are employed, but compatibility is ensured (for GCC, Clang, and MSVC). It is basically safe to consider that the code conforms to the C++ standard.

Most undefined behaviors will be caught (by C-style `assert`) if macro `NDEBUG` is not defined ([reference](https://en.cppreference.com/w/cpp/error/assert.html)), see the code for concrete conditions.

When using the library, never do `using namespace std;` and `using namespace aal;` simultaneously in any scope, otherwise the code probably won't compile due to too many name collisions. By the way, it is always recommended to do neither of them.

## Documentation of /src

### src/aliases/integral.hpp, src/aliases/floating_point.hpp

Provide aliases for integer types and floating-point number types, see the code for details.

