/**
 * @file sassert.h
 * @brief provide assert macros.SASSERT_EQ/NE/LT/GT/LTE/GTE
 */
/*
 * These codes are licensed under CC0.
 * http://creativecommons.org/publicdomain/zero/1.0/
 */
#ifndef __NDS_SASSERT_H__
#define __NDS_SASSERT_H__

# ifdef NO_SASSERT

#  define SASSERT_EQ(x,y)
#  define SASSERT_NE(x,y)
#  define SASSERT_LT(x,y)
#  define SASSERT_GT(x,y)
#  define SASSERT_LTE(x,y)
#  define SASSERT_GTE(x,y)

# else
# include <cassert>
# include <type_traits>

#  define SASSERT_EQ(x,y) __NDS__ASSERT_BASE(eq," == ",x,y)
#  define SASSERT_NE(x,y) __NDS__ASSERT_BASE(ne," != ",x,y)
#  define SASSERT_LT(x,y) __NDS__ASSERT_BASE(lt," < ",x,y)
#  define SASSERT_GT(x,y) __NDS__ASSERT_BASE(gt," > ",x,y)
#  define SASSERT_LTE(x,y) __NDS__ASSERT_BASE(lte," <= ",x,y)
#  define SASSERT_GTE(x,y) __NDS__ASSERT_BASE(gte," >= ",x,y)

#  define __NDS__ASSERT_BASE(op,message,x,y)\
  static_assert(::nds::assert_##op <::nds::assert_type_t<decltype(x)>,\
                x,y,::nds::line<__LINE__>>::value,#x message #y)


namespace nds{


template<unsigned int l>struct line;

template<typename I>
struct assert_type
{
  using t1 = typename std::remove_reference<I>::type;
  using type = typename std::remove_cv<t1>::type;
};

template<typename I>
using assert_type_t = typename assert_type<I>::type;


template<typename I, I Value,I Expected,typename _file_line_>
struct assert_eq
{
  static constexpr bool value = Value == Expected;
  static_assert(value,"Value == Expected");
};

template<typename I, I Value,I Expected,typename _file_line_>
struct assert_ne
{
  static constexpr bool value = Value != Expected;
  static_assert(value,"Value != Expected");
};

template<typename I, I Value,I Expected,typename _file_line_>
struct assert_lt
{
  static constexpr bool value = Value < Expected;
  static_assert(value,"Value < Expected");
};

template<typename I, I Value,I Expected,typename _file_line_>
struct assert_gt
{
  static constexpr bool value = Value > Expected;
  static_assert(value,"Value > Expected");
};

template<typename I, I Value,I Expected,typename _file_line_>
struct assert_lte
{
  static constexpr bool value = Value <= Expected;
  static_assert(value,"Value <= Expected");
};

template<typename I, I Value,I Expected,typename _file_line_>
struct assert_gte
{
  static constexpr bool value = Value >= Expected;
  static_assert(value,"Value >= Expected");
};

}

# endif
#endif //-- __NDS_SASSERT_H__ --
