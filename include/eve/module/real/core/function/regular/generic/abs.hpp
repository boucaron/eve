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

#include <eve/concept/value.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_andnot.hpp>
#include <eve/function/max.hpp>

namespace eve::detail
{
  template<real_value T> EVE_FORCEINLINE constexpr T abs_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
            if constexpr( floating_value<T> )               return bit_andnot(a, mzero(eve::as(a)));
      else  if constexpr( unsigned_value<T> )               return a;
      else  if constexpr( signed_integral_scalar_value<T> ) return a < T(0) ? -a : a;
      else                                                  return eve::max(a, -a);
    }
    else
    {
      return apply_over(eve::abs, a);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto abs_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op( EVE_CURRENT_API{}, cond, eve::abs, t);
  }
}