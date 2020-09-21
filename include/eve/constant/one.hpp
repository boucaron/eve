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

#include <eve/detail/implementation.hpp>
#include <eve/as.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(one_, one);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto one_(EVE_SUPPORTS(cpu_), as_<T> const &) noexcept
    {
      return T(1);
    }
  }
}