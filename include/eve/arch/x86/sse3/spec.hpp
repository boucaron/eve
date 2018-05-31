//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SSE3_SPEC_HPP_INCLUDED
#define EVE_ARCH_X86_SSE3_SPEC_HPP_INCLUDED

#include <eve/arch/x86/sse3/tags.hpp>

#if !defined(EVE_CURRENT_ABI)
  #if EVE_SIMD_X86 == EVE_SSE3_VERSION
    #define EVE_CURRENT_ABI ::eve::sse_
    #define EVE_CURRENT_API ::eve::sse3_
  #endif
#endif

#if EVE_SIMD_X86 >= EVE_SSE3_VERSION
  #include <pmmintrin.h>
#endif

#endif
