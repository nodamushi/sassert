# sassert

C++のstatic\_assert失敗時に値を確認できるマクロを提供します。


# 使い方

sassert.hをインクルードパスに入れてください。

```cpp
#include "sassert.h"

// @return x * x
constexpr int pow(int x){return x  +  x;}

SASSERT_EQ(pow(10),100); // 10*10 == 100
SASSERT_NE(pow(10),20);  // 10*10 != 20
SASSERT_LT(pow(1),2);    // 1*1 < 2
SASSERT_GT(pow(10),50);  // 10*10 > 50
SASSERT_LTE(pow(10),100);// 10*10 <= 100
SASSERT_GTE(pow(10),100);// 10*10 >= 100

```


# エラーの例

nds::assert\_○<型, 値, 期待値, ファイル行 >という形でエラーに値が記述されます。

コンパイラによって出現位置は異なりますので、それっぽいところを探してください。

IAR Embedded Workbench等で使う場合は、エラーログを右クリックし、ログのフィルタリングを無し（全て）にして表示してください。


G++

```
include/sassert.h: In instantiation of 'struct nds::assert_eq<int, 20, 100, nds::line<6> >':
foo.cpp:6:1:   required from here
include/sassert.h:54:17: error: static assertion failed: Value == Expected
   54 |   static_assert(value,"Value == Expected");
      |                 ^~~~~
include/sassert.h:31:45: error: static assertion failed: pow(10) == 100
   30 |   static_assert(::nds::assert_##op <::nds::assert_type_t<decltype(x)>,\
      |                 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   31 |                 x,y,::nds::line<__LINE__>>::value,#x message #y)
      |                 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~
include/sassert.h:22:27: note: in expansion of macro '__NDS__ASSERT_BASE'
   22 | #  define SASSERT_EQ(x,y) __NDS__ASSERT_BASE(eq," == ",x,y)
      |                           ^~~~~~~~~~~~~~~~~~
foo.cpp:6:1: note: in expansion of macro 'SASSERT_EQ'
    6 | SASSERT_EQ(pow(10),100); // 10*10 == 100
      | ^~~~~~~~~~
```


Clang++

```
include/sassert.h:75:3: error: static_assert failed due to requirement 'value' "Value > Expected"
  static_assert(value,"Value > Expected");
  ^             ~~~~~
foo.cpp:9:1: note: in instantiation of template class 'nds::assert_gt<int, 20, 50, nds::line<9> >' requested here
SASSERT_GT(pow(10),50);  // 10*10 > 50
^
include/sassert.h:25:27: note: expanded from macro 'SASSERT_GT'
#  define SASSERT_GT(x,y) __NDS__ASSERT_BASE(gt," > ",x,y)
                          ^
include/sassert.h:30:24: note: expanded from macro '__NDS__ASSERT_BASE'
  static_assert(::nds::assert_##op <::nds::assert_type_t<decltype(x)>,\
```
