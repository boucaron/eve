//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/derivative/sqrt.hpp>
#include <type_traits>

TTS_CASE_TPL("Check derivative(sqrt) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::derivative(eve::sqrt)(T()), T);
    TTS_EXPR_IS(eve::derivative(eve::sqrt)(T()), T);
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::sqrt) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_ULP_EQUAL(eve::derivative(eve::sqrt)(T{9}), T(1/6.0), 0.5);
  }
}