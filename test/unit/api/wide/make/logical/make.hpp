//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <tts/tests/relation.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

TTS_CASE_TPL("Check enumerating constructor for wide of logical", EVE_TYPE)
{
  auto filler = [](auto i, auto) { return i % 3 ? true : false; };

  eve::logical<T> simd(filler);
  eve::logical<T> ref;

  for(std::ptrdiff_t i = 0; i < simd.size(); ++i)
    ref.set(i, filler(i, simd.size()));

  TTS_EQUAL(simd, ref);
}
