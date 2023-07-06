# 修改游戏代码 {#tutorial_patching}

[TOC]

下面，我们把目光聚焦于 DLL 项目的 `main.cpp`。

```cpp
#include <PVZMod.h>

using namespace PVZMod;

void PVZMod::Main(InitPatch& patch)
{

}
```

`PVZMod::Main` 函数是入口函数，此函数会在游戏开始运行前被调用。一切对游戏代码的修改操作，都应在此函数中完成。当此函数执行完毕后，游戏将开始运行，游戏开始运行后，不可再对代码进行任何修改。

本框架中，提供的许多对游戏进行修改的接口，请留意第一个参数为 `InitPatch& patch` 的函数，这些函数被称为“补丁函数”，通常在含有“Patch”的命名空间中（魔法成员相关函数除外），这些函数需要在 `PVZMod::Main` 中调用，将 `PVZMod::Main` 的 `patch` 参数传递给补丁函数，以对游戏进行相应的修改。

补丁函数通常有以下几种形式：

## 一般形式的补丁函数

即一个普通的函数，分为无参补丁函数和有参补丁函数：

### 无参补丁函数

指只有一个 `InitPatch& patch` 参数的补丁函数，通常是对某些代码的固定修改，使用方法是直接调用，通常可以调用多次，但只有第一次生效，如 `PVZMod::GameObjectPatch::FixBoardToolTipPos`：

```cpp
#include <PVZMod.h>
#include <GameObjectPatch.h>

using namespace PVZMod;

void PVZMod::Main(InitPatch& patch)
{
	GameObjectPatch::FixBoardToolTipPos(patch);		// 直接调用即可修改相应代码。
	GameObjectPatch::FixBoardToolTipPos(patch);		// 第二次调用不会抛出异常，但是不会有任何效果。
}
```

### 有参补丁函数

指除了 `InitPatch& patch`，还有其它参数的补丁函数，由于需要根据传入的参数进行不同的补丁，通常只能调用一次，调用第二次则会抛出异常，如 `PVZMod::EffectPatch::SetReanimationParamArray`：

```cpp
#include <PVZMod.h>
#include <EffectPatch.h>

using namespace PVZMod;

ReanimationParams gReanimParams[] = 
{
	// ...
};

void PVZMod::Main(InitPatch& patch)
{
	EffectPatch::SetReanimationParamArray(patch, gReanimParams, sizeof(gReanimParams) / sizeof(ReanimationParams));		// 有参补丁函数需要传入对应的参数调用。
    // EffectPatch::SetReanimationParamArray(patch, gReanimParams, sizeof(gReanimParams) / sizeof(ReanimationParams));	// 第二次调用会抛出异常。
}
```

还有一种情况，是可以多次调用，并且根据多次调用传入的参数产生叠加的效果，例如 `PVZMod::ResourcePatch::AddResFile`。

## 用于继承原版类的补丁函数

这类补丁函数，实现对原版游戏中某个类进行继承，重写部分代码，实现扩展功能。这类函数也分为两种：

### 继承支持多态的类

对于原版中支持多态的类，如基于 `Widget` 的类，可以直接继承，添加成员，重写虚函数，如 `PVZMod::GameUIPatch::ReplaceGameSelector`：

```cpp
#include <PVZMod.h>
#include <GameSelector.h>
#include <GameUIPatch.h>

using namespace PVZMod;

class MyGameSelector: public GameSelector
{
public:
	// ...
}

void PVZMod::Main(InitPatch& patch)
{
	GameUIPatch::ReplaceGameSelector<MyGameSelector>(patch);
}
```

### 继承不支持多态的类 —— 魔法成员机制

原版游戏中，还有大部分类是不支持多态的，例如 `PVZMod::Plant`、`PVZMod::Zombie` 等基于 `PVZMod::GameObject` 的类，还有如 `PVZMod::LawnApp` 和 `PVZMod::Board` 这类实现多态继承比较复杂的类，继承这些类，需要用到“魔法成员机制”，具体使用方法会在后面的章节详细解释，简单来说，就是在继承的类中，定义指定名称的成员函数或成员变量，就会自动进行对应的补丁，以调用对应函数或操作对应的变量。

另外，两种形式的继承还可能同时存在于一个类，例如通过 `PVZMod::ResourcePatch::ReplacePakInterface` 函数替换 `PakInterface`，既支持重写虚函数，也有魔法成员。
