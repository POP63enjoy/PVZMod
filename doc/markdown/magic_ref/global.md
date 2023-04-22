# 全局魔法成员 {#magic_ref_global}

[TOC]

这些魔法成员可以用于所有类型的魔法类。

## 允许重复注册 - MC_MULTI_REG

用于标记一个子魔法类是否允许重复注册。

* ❌ 不可用于主魔法类。
* ✅ 可以用于子魔法类。

```cpp
static constexpr bool MC_MULTI_REG = true;	// 允许重复注册。
```

## 引用 - MT_Ref

定义一个子魔法类所引用的其它子魔法类，这些类将在本类注册前自动注册。

* ❌ 不可用于主魔法类。
* ✅ 可以用于子魔法类。

```cpp
using MT_Ref = Magic::TypeList<Class1, Class2, Class3>;		// 在注册此类之前，依次注册 Class1、Class2、Class3 类。
```

