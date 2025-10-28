#ifndef AAL_SRC_MACROS_TARGET_HPP
#define AAL_SRC_MACROS_TARGET_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/macros/target.hpp */

#if defined(__i386__) || defined(_M_IX86)
#define AAL_ARCH_X86 1
#endif // test if the target architecture is x86

#if defined(__x86_64__) || defined(_M_X64)
#define AAL_ARCH_X86_64 1
#endif // test if the target architecture is x86_64

#ifdef _MSC_VER
#define AAL_COMPILER_MSVC 1
#endif // test if the target compiler is MSVC

#endif // AAL_SRC_MACROS_TARGET_HPP
