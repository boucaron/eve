//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/scalar/logical_xor.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE("Check logical_xor return type")
{
  TTS_EXPR_IS(eve::logical_xor(0.f, 0.f), eve::logical<float>);
  TTS_EXPR_IS(eve::logical_xor(0., 0.), eve::logical<double>);

  TTS_EXPR_IS(eve::logical_xor(std::int8_t(), std::int8_t()), eve::logical<std::int8_t>);
  TTS_EXPR_IS(eve::logical_xor(std::int16_t(), std::int16_t()), eve::logical<std::int16_t>);
  TTS_EXPR_IS(eve::logical_xor(std::int32_t(), std::int32_t()), eve::logical<std::int32_t>);
  TTS_EXPR_IS(eve::logical_xor(std::int64_t(), std::int64_t()), eve::logical<std::int64_t>);

  TTS_EXPR_IS(eve::logical_xor(std::uint8_t(), std::uint8_t()), eve::logical<std::uint8_t>);
  TTS_EXPR_IS(eve::logical_xor(std::uint16_t(), std::uint16_t()), eve::logical<std::uint16_t>);
  TTS_EXPR_IS(eve::logical_xor(std::uint32_t(), std::uint32_t()), eve::logical<std::uint32_t>);
  TTS_EXPR_IS(eve::logical_xor(std::uint64_t(), std::uint64_t()), eve::logical<std::uint64_t>);
}

TTS_CASE("Check logical_xor behavixor")
{
  TTS_EQUAL(eve::logical_xor(std::uint8_t(0), std::uint8_t(0)), false);
  TTS_EQUAL(eve::logical_xor(std::uint16_t(0), std::uint16_t(0)), false);
  TTS_EQUAL(eve::logical_xor(std::uint32_t(0), std::uint32_t(0)), false);
  TTS_EQUAL(eve::logical_xor(std::uint64_t(0), std::uint64_t(0)), false);
  TTS_EQUAL(eve::logical_xor(std::int8_t(0), std::int8_t(0)), false);
  TTS_EQUAL(eve::logical_xor(std::int16_t(0), std::int16_t(0)), false);
  TTS_EQUAL(eve::logical_xor(std::int32_t(0), std::int32_t(0)), false);
  TTS_EQUAL(eve::logical_xor(std::int64_t(0), std::int64_t(0)), false);
  TTS_EQUAL(eve::logical_xor(0.0f, 0.0f), false);
  TTS_EQUAL(eve::logical_xor(-0.0, 0.0), false);

  TTS_EQUAL(eve::logical_xor(std::uint8_t(0), std::uint8_t(1)), true);
  TTS_EQUAL(eve::logical_xor(std::uint16_t(0), std::uint16_t(1)), true);
  TTS_EQUAL(eve::logical_xor(std::uint32_t(0), std::uint32_t(1)), true);
  TTS_EQUAL(eve::logical_xor(std::uint64_t(0), std::uint64_t(1)), true);
  TTS_EQUAL(eve::logical_xor(std::int8_t(0), std::int8_t(1)), true);
  TTS_EQUAL(eve::logical_xor(std::int16_t(0), std::int16_t(1)), true);
  TTS_EQUAL(eve::logical_xor(std::int32_t(0), std::int32_t(1)), true);
  TTS_EQUAL(eve::logical_xor(std::int64_t(0), std::int64_t(1)), true);
  TTS_EQUAL(eve::logical_xor(-1.5f, 0.0f), true);
  TTS_EQUAL(eve::logical_xor(-4.753, 0.0), true);
}
