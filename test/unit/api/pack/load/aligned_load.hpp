//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ALIGNED_LOAD_HPP
#define ALIGNED_LOAD_HPP

#include <eve/pack.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <tts/tts.hpp>
#include <tts/tests/basic.hpp>
#include <algorithm>

using eve::fixed;
using eve::as_aligned;

TTS_CASE( "Check ctor from aligned pointer for pack of 1 element" )
{
  using eve::pack;
  constexpr auto algt = pack<Type,fixed<1>>::alignment;

  alignas(algt) std::array<Type,1> ref{ 42 };
  pack<Type,fixed<1>> simd( as_aligned<algt>(&ref[0]) );

  TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
}

TTS_CASE( "Check ctor from aligned pointer for pack of 2 elements" )
{
  using eve::pack;
  constexpr auto algt = pack<Type,fixed<2>>::alignment;

  alignas(algt) std::array<Type,2> ref{ 42, 69 };
  pack<Type,eve::fixed<2>> simd( as_aligned<algt>( &ref[0]) );

  TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
}

TTS_CASE( "Check ctor from aligned pointer for pack of 4 elements" )
{
  using eve::pack;
  constexpr auto algt = pack<Type,fixed<4>>::alignment;

  alignas(algt) std::array<Type,4> ref{ 42, 69, 13, 37 };
  pack<Type,eve::fixed<4>> simd( as_aligned<algt>( &ref[0]) );

  TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
}

TTS_CASE( "Check ctor from aligned pointer for pack of 8 elements" )
{
  using eve::pack;
  constexpr auto algt = pack<Type,fixed<8>>::alignment;

  alignas(algt) std::array<Type,8> ref{ 4, 2, 6, 9, 1, 3, 3, 7 };
  pack<Type,eve::fixed<8>> simd( as_aligned<algt>( &ref[0]) );

  TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
}

TTS_CASE( "Check ctor from aligned pointer for pack of 16 elements" )
{
  using eve::pack;
  constexpr auto algt = pack<Type,fixed<16>>::alignment;

  alignas(algt) std::array<Type,16> ref { 4, 2, 6, 9, 1, 3, 3, 7
                                        , 4, 2, 6, 9, 1, 3, 3, 7
                                        };
  pack<Type,eve::fixed<16>> simd( as_aligned<algt>( &ref[0]) );

  TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
}

TTS_CASE( "Check ctor from aligned pointer for pack of 32 elements" )
{
  using eve::pack;
  constexpr auto algt = pack<Type,fixed<32>>::alignment;

  alignas(algt)
  std::array<Type,32> ref { 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                          , 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                          };
  pack<Type,eve::fixed<32>> simd( as_aligned<algt>( &ref[0]) );

  TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
}

TTS_CASE( "Check ctor from aligned pointer for pack of 64 elements" )
{
  using eve::pack;
  constexpr auto algt = pack<Type,fixed<64>>::alignment;

  alignas(algt)
  std::array<Type,64> ref { 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                          , 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                          , 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                          , 4, 2, 6, 9, 1, 3, 3, 7, 4, 2, 6, 9, 1, 3, 3, 7
                          };
  pack<Type,eve::fixed<64>> simd( as_aligned<algt>( &ref[0]) );

  TTS_EXPECT( std::equal(simd.begin(),simd.end(),ref.begin()));
}

#endif
