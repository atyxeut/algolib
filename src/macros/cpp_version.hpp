#ifndef AAL_SRC_MACROS_CPP_VERSION_HPP
#define AAL_SRC_MACROS_CPP_VERSION_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/macros/cpp_version.hpp */

// see https://en.cppreference.com/w/cpp/preprocessor/replace#Predefined_macros for details

#if __cplusplus >= 201402L
#define AAL_CPP14 1
#else
#define AAL_CPP14 0
#endif

#if __cplusplus >= 201703L
#define AAL_CPP17 1
#else
#define AAL_CPP17 0
#endif

#endif // AAL_SRC_MACROS_CPP_VERSION_HPP
