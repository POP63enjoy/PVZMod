# MagicBoard {#magic_ref_board}

[TOC]

* 命名空间：`PVZMod::MagicBoard`。
* 目标类型：`PVZMod::Board`。

```cpp
#include <Board.h>
#include <MagicBoard.h>
```

## 构造函数和析构函数 - MF_Constructor、MF_Destructor

* ✅ 可以用于主魔法类。
* ✅ 可以用于子魔法类。

```cpp
void MF_Constructor(LawnApp* theApp, MagicBoard::Constructor_t& base);	// 构造函数。
void MF_Destructor(MagicBoard::Destructor_t& base);						// 析构函数。
```

## 关卡信息初始化 - MF_InitLevel

* ✅ 可以用于主魔法类。
* ✅ 可以用于子魔法类。

```cpp
void MF_InitLevel(MagicBoard::InitLevel_t& base);
```

## 释放资源 - MF_DisposeBoard

* ✅ 可以用于主魔法类。
* ✅ 可以用于子魔法类。

```cpp
void MF_DisposeBoard(MagicBoard::DisposeBoard_t& base);
```

## 出怪计算 - MF_ZombiePicker

* ✅ 可以用于主魔法类。
* ✅ 可以用于子魔法类。

```cpp
// 计算波数，计算结果存放在 mNumWaves 中。
void MF_ZombiePicker_CalculateNumWaves(MagicBoard::ZombiePicker_CalculateNumWaves_t& base);

// 针对特殊关卡进行特殊的僵尸放置操作。如果返回 true，则不执行普通关卡的常规出怪计算操作。
bool MF_ZombiePicker_SpecialLevelPut(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_SpecialLevelPut_t& base);

// 计算本波基础出怪点数，计算结果存放在 theZombiePicker.mZombiePoints 中。
void MF_ZombiePicker_CalculateBasicPoints(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_CalculateBasicPoints_t& base);

// 在出怪点数加倍之前进行僵尸放置操作。（在原版中，这里用于放置旗帜波的特殊僵尸）
void MF_ZombiePicker_PutBeforeMultiple(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_PutBeforeMultiple_t& base);

// 计算出怪点数倍数，将基础出怪点数乘倍数的结果存放在 theZombiePicker.mZombiePoints 中。
void MF_ZombiePicker_CalculateMultiplePoints(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_CalculateMultiplePoints_t& base);

// 放置关卡预设僵尸。
void MF_ZombiePicker_PutPreset(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_PutPreset_t& base);

// 放置随机僵尸。
void MF_ZombiePicker_PutRandom(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_PutRandom_t& base);
```

* @param theZombiePicker 出怪计算信息。

  @param theWave 当前波数。

## 画面偏移 - mvOffsetX、mvOffsetY

对关卡画面进行偏移，同时修改鼠标判定。

* ✅ 可以用于主魔法类。
* ❌ 不可用于子魔法类。

```cpp
static inline int mvOffsetX = 0;
static inline int mvOffsetY = 0;
```

## 自动存储新增成员变量 - MC_AUTO_SAVE_EXTENDED_DATA

如果为 true 或未定义，则在游戏存档时通过拷贝字节的方式存储所有新增成员变量。

* ✅ 可以用于主魔法类。
* ❌ 不可用于子魔法类。

```cpp
static constexpr bool MC_AUTO_SAVE_EXTENDED_DATA = false;	// 禁止自动存储新增成员。
```
