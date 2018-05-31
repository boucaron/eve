//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_AVX_SPEC_HPP_INCLUDED
#define EVE_ARCH_X86_AVX_SPEC_HPP_INCLUDED

#include <eve/arch/x86/avx/tags.hpp>

#if !defined(EVE_CURRENT_ABI)
  #if EVE_SIMD_X86 == EVE_AVX_VERSION
    #define EVE_CURRENT_ABI ::eve::avx_
    #define EVE_CURRENT_API ::eve::avx_
  #endif
#endif

#if EVE_SIMD_X86 >= EVE_AVX_VERSION
  #include <immintrin.h>
#endif

#endif
