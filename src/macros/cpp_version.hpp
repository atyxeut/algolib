#ifndef AAL_SRC_MACROS_CPP_VERSION_HPP
#define AAL_SRC_MACROS_CPP_VERSION_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/macros/cpp_version.hpp */

// see https://en.cppreference.com/w/cpp/preprocessor/replace#Predefined_macros for details

#if __cplusplus >= 201402L
#define AAL_CPP14 1
#else
#define AAL_CPP14 0
#endif // test if the current C++ version is C++14 or above

#if __cplusplus >= 201703L
#define AAL_CPP17 1
#else
#define AAL_CPP17 0
#endif // test if the current C++ version is C++17 or above

#if __cplusplus >= 202002L
#define AAL_CPP20 1
#else
#define AAL_CPP20 0
#endif // test if the current C++ version is C++20 or above

#if __cplusplus >= 202302L
#define AAL_CPP23 1
#else
#define AAL_CPP23 0
#endif // test if the current C++ version is C++23 or above

#endif // AAL_SRC_MACROS_CPP_VERSION_HPP
