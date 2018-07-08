//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_EXT_AGGREGATE_HPP_INCLUDED
#define EVE_EXT_AGGREGATE_HPP_INCLUDED

#include <eve/arch/spec.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/detail/function/make.hpp>
#include <eve/detail/function/load.hpp>
#include <eve/detail/is_iterator.hpp>
#include <eve/detail/is_range.hpp>
#include <eve/detail/compiler.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/plus.hpp>
#include <eve/ext/is_pack.hpp>
#include <type_traits>
#include <iterator>
#include <array>

namespace eve
{
  // Wrapper for SIMD registers holding multiple native SIMD registers
  template<typename Type, typename Size>
  struct pack<Type,Size,eve::aggregated_>
  {
    using substorage_type         = pack<Type,typename Size::split_type>;
    using storage_type            = std::array<substorage_type,2>;
    using abi_type                = eve::aggregated_;
    using value_type              = typename substorage_type::value_type;
    using size_type               = std::size_t;
    using reference               = typename substorage_type::reference;
    using const_reference         = typename substorage_type::const_reference;
    using iterator                = typename substorage_type::iterator;
    using const_iterator          = typename substorage_type::const_iterator;
    using reverse_iterator        = typename substorage_type::reverse_iterator;
    using const_reverse_iterator  = typename substorage_type::const_reverse_iterator;

    static constexpr std::size_t static_size  = Size::value;
    static constexpr std::size_t alignment    = substorage_type::alignment;

    // ---------------------------------------------------------------------------------------------
    // Ctor
    EVE_FORCEINLINE pack()            noexcept {}

    EVE_FORCEINLINE pack(storage_type const& r) noexcept : data_(r) {}

    // ---------------------------------------------------------------------------------------------
    // Constructs a pack from a Range
    template< typename Iterator
            , typename = std::enable_if_t< detail::is_iterator_v<Iterator>>
            >
    EVE_FORCEINLINE explicit pack(Iterator b, Iterator e) noexcept
                  : data_(detail::load(as_<pack>{},abi_type{},b,e))
    {}

    template<typename Range>
    EVE_FORCEINLINE explicit pack (Range&& r
                                  , std::enable_if_t<   detail::is_range_v<Range>
                                                    && !ext::is_pack_v<Range>
                                                    && !std::is_same_v<storage_type,Range>
                                                    >* = 0
                                  ) noexcept
                  : pack( std::begin(std::forward<Range>(r)), std::end(std::forward<Range>(r)))
    {}

    // ---------------------------------------------------------------------------------------------
    // Constructs a pack from a pointer
    EVE_FORCEINLINE explicit pack(Type* ptr) noexcept
                  : data_(detail::load(as_<pack>{},abi_type{},ptr))
    {}

    template< std::size_t Alignment
            , typename = std::enable_if_t<(Alignment>=alignment)>
            >
    EVE_FORCEINLINE explicit pack(aligned_ptr<Type,Alignment> ptr) noexcept
                  : data_(detail::load(as_<pack>{},abi_type{},ptr))
    {}

    // ---------------------------------------------------------------------------------------------
    // Constructs a pack from a single value
    EVE_FORCEINLINE explicit pack(Type v) noexcept
                  : data_( detail::make(as_<pack>{},::eve::aggregated_{},v) )
    {}

    // ---------------------------------------------------------------------------------------------
    // Constructs a pack from a sequence of values
    template<typename T0, typename... Ts
            , typename = std::enable_if_t <   std::is_convertible_v<T0,Type>
                                          && (... &&  std::is_convertible_v<Ts,Type>)
                                          && !Size::is_default
                                          >
            >
    EVE_FORCEINLINE pack(T0 const& v0, Ts const&... vs) noexcept
                  : pack(detail::make(as_<pack>{},::eve::aggregated_{},v0,vs...))
    {
      static_assert ( 1+sizeof...(vs) == static_size
                    , "[eve] Size mismatch in initializer list for pack"
                    );
    }

    // ---------------------------------------------------------------------------------------------
    // Constructs a pack with a generator function
    template<typename Generator>
    EVE_FORCEINLINE pack( Generator&& g
                        , std::enable_if_t<std::is_invocable_v< Generator
                                                              , std::size_t,std::size_t
                                                              >
                                          >* = 0
                        ) noexcept
    {
      for(std::size_t i=0;i<size();++i)
        this->operator[](i) = std::forward<Generator>(g)(i,static_size);
    }

    // ---------------------------------------------------------------------------------------------
    // Raw storage access
    EVE_FORCEINLINE storage_type   storage() const  noexcept { return data_; }
    EVE_FORCEINLINE storage_type&  storage()        noexcept { return data_; }

    EVE_FORCEINLINE operator storage_type()  const noexcept { return data_; }

    // ---------------------------------------------------------------------------------------------
    // array-like interface
    static EVE_FORCEINLINE constexpr std::size_t  size()     noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr size_type    max_size() noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr bool         empty()    noexcept { return false;       }

    EVE_FORCEINLINE void swap(pack& rhs) noexcept
    {
      using std::swap;
      swap(data_, rhs.data_);
    }

    // ---------------------------------------------------------------------------------------------
    // begin() variants
    EVE_FORCEINLINE iterator        begin()       noexcept  { return data_[0].begin(); }
    EVE_FORCEINLINE const_iterator  begin() const noexcept  { return data_[0].begin(); }
    EVE_FORCEINLINE const_iterator cbegin()       noexcept  { return data_[0].begin(); }

    EVE_FORCEINLINE reverse_iterator        rbegin()        noexcept { return data_[1].rbegin();  }
    EVE_FORCEINLINE const_reverse_iterator  rbegin() const  noexcept { return data_[1].rbegin();  }
    EVE_FORCEINLINE const_reverse_iterator crbegin() const  noexcept { return data_[1].crbegin(); }

    // ---------------------------------------------------------------------------------------------
    // end() variants
    EVE_FORCEINLINE iterator          end()         noexcept  { return data_[1].end();  }
    EVE_FORCEINLINE const_iterator    end()   const noexcept  { return data_[1].end();  }
    EVE_FORCEINLINE const_iterator    cend()        noexcept  { return data_[1].cend(); }
    EVE_FORCEINLINE reverse_iterator  rend()        noexcept  { return data_[0].rend(); }

    EVE_FORCEINLINE const_reverse_iterator  rend() const noexcept { return data_[0].rend();   }
    EVE_FORCEINLINE const_reverse_iterator crend() const noexcept { return data_[0].crend();  }

    // ---------------------------------------------------------------------------------------------
    // elementwise access
    EVE_FORCEINLINE reference       operator[](std::size_t i)       noexcept { return begin()[i]; }
    EVE_FORCEINLINE const_reference operator[](std::size_t i) const noexcept { return begin()[i]; }

    EVE_FORCEINLINE reference       back()        noexcept  { return data_[1].back(); }
    EVE_FORCEINLINE const_reference back() const  noexcept  { return data_[1].back(); }

    EVE_FORCEINLINE reference       front()       noexcept  { return data_[0].front(); }
    EVE_FORCEINLINE const_reference front() const noexcept  { return data_[0].front(); }

    // ---------------------------------------------------------------------------------------------
    // Self-increment/decrement operators
    EVE_FORCEINLINE pack& operator++() noexcept
    {
      *this += Type{1};
      return *this;
    }

    EVE_FORCEINLINE pack operator++(int) noexcept
    {
      auto that(*this);
      operator++();
      return that;
    }

    // ---------------------------------------------------------------------------------------------
    // Self-assignment operators
    template<typename Other>
    EVE_FORCEINLINE pack& operator+=(Other const& other) noexcept
    {
      *this = eve::plus(*this, other);
      return *this;
    }

    private:
    storage_type data_;
  };
}

#endif