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
#include <eve/constant/zero.hpp>
#include <eve/constant/half.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/logical_andnot.hpp>
#include <eve/function/nbtrue.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sign.hpp>
#include <eve/function/signnz.hpp>
#include <eve/function/sqr.hpp>
#include <eve/module/math/detail/generic/erf_kernel.hpp>
#include <eve/platform.hpp>
#include <type_traits>

namespace eve::detail
{
  template<floating_real_scalar_value T>
  EVE_FORCEINLINE T erfc_(EVE_SUPPORTS(cpu_), T x) noexcept
  {
    if constexpr(eve::platform::supports_invalids)
      if(is_nan(x)) return x;
    if constexpr(eve::platform::supports_infinites)
      if (eve::is_infinite(x)) return oneminus(signnz(x));
    if (is_eqz(x)) return T(1);
    if constexpr(std::is_same_v<T, double>)
    {
      T y =  eve::abs(x);
      if (y <= 0.46875) //15/32
      {
        T ysq = if_else(y > halfeps(as<T>()), sqr(y), eve::zero);
        T res = kernel1_erf1(x, ysq);
        res =  oneminus(res);
        return res;
      }
      else if (y <= 4.0)
      {
        T res = kernel1_erf2(x, y);
        res   = kernel1_finalize2(res, y);
        if (is_ltz(x)) res = 2.0-res;
        return res;
      }
      else if  (y <= 26.543)
      {
        T res = kernel1_erf3(x, y);
        res =   kernel1_finalize2(res, y);
        if (is_ltz(x)) res = T(2)-res;
        return res;
      }
      else return (is_ltz(x)) ? T(2) : zero(as<T>());
    }
    else  if constexpr(std::is_same_v<T, float>)
    {
      T xx =  eve::abs(x);
      T r1 = zero(as<T>());
      T z =  xx/inc(xx);
      if (3.0f*xx < 2.0f)
      {
        r1 = kernel_erfc3(z);
      }
      else
      {
       z-= 0.4f;
       r1 = exp(-sqr(xx))*kernel_erfc2(z);
      }
      return (x < 0.0f) ? 2.0f-r1 : r1;
    }
  }

  template<floating_real_simd_value T>
  EVE_FORCEINLINE T erfc_(EVE_SUPPORTS(cpu_), T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using elt_t = element_type_t<T>;
      if constexpr(std::is_same_v<elt_t, double>)
      {
        T y =  eve::abs(a0);
        y =  if_else(y > T(26.543), T(27), y);
        T sqry =  sqr(y);
        auto test1 =  eve::is_less(y, T( 0.46875)); // 15/32;
        T r1 = eve::zero(as<T>());
        std::size_t nb = eve::nbtrue(test1);
        if (nb > 0)  //here y < 0.46875
        {
          T ysq = if_else(y > halfeps(as<T>()), sqry, eve::zero);
          r1 = kernel1_erf1(a0, ysq);
          r1 =  oneminus(r1);
          if (nb == T::static_size) return r1;
        }
        auto test2 = (y <= T(4));
        auto test3 = logical_andnot(test2, test1);

        auto nb1 =  eve::nbtrue(test3);
        if(nb1 > 0) //here we treat 0.46875 <= y and y <= 4
        {
          T res = kernel1_erf2(a0, y);
          res   = kernel1_finalize2(res, y);
          res = if_else(is_ltz(a0), 2.0-res, res);
          r1 = if_else(test3, res, r1);
          if (nb+nb1 == T::static_size) return r1;
        }
        //here we treat y > 4
        T res = kernel1_erf3(a0, y);
        res =   kernel1_finalize2(res, y);
        res = if_else(is_ltz(a0), 2.0-res, res);
        r1 = if_else(test2, r1, res);
        return r1;
      }
      else  if constexpr(std::is_same_v<elt_t, float>)
      {
        T x =  eve::abs(a0);
        auto test0 = eve::is_ltz(a0);
        T r1 = zero(as<T>());
        auto test1 = eve::is_less(x, 6.6666667e-01f);
        T z = x/inc(x);

        std::size_t nb = nbtrue(test1);
        if(nb > 0)
        {
          r1 = kernel_erfc3(z);
          if (nb >= T::static_size)
            return eve::if_else(test0, T(2)-r1, r1);
        }
        z -= T(0.4);
        T r2 = exp(-sqr(x))*kernel_erfc2(z);
        r1 = if_else(test1, r1, r2);
        if constexpr(eve::platform::supports_infinites)
          r1 = if_else (is_equal(x, inf(as<T>())), zero, r1);

        return eve::if_else(test0, T(2)-r1, r1);
      }
    }
    else
      return apply_over(erfc, a0);
  }
}