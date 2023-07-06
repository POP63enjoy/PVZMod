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

## 关卡存读档 - MF_Sync、MF_FixAfterLoad

注意：默认情况下，框架会以复制字节的形式自动存读主魔法类中新增的成员变量，而如果定义了 `MF_Sync` 开头的任意魔法函数，框架将关闭自动存读机制，开发者应手动存读新增的成员变量。

* ✅ 可以用于主魔法类。
* ✅ 可以用于子魔法类。

```cpp
// 存读类成员数据。
void MF_Sync_SyncData(SaveGameContext& theContext, MagicBoard::Sync_SyncData_t& base);

// 存读对象池数据。
void MF_Sync_SyncDataArray(SaveGameContext& theContext, MagicBoard::Sync_SyncDataArray_t& base);

// 存读对象池内的对象。
void MF_Sync_SyncDataArrayObject(SaveGameContext& theContext, MagicBoard::Sync_SyncDataArrayObject_t& base);

// 存读其它对象。
void MF_Sync_SyncOtherObject(SaveGameContext& theContext, MagicBoard::Sync_SyncOtherObject_t& base);

// 存读其它内容。
void MF_Sync_SyncOther(SaveGameContext& theContext, MagicBoard::Sync_SyncOther_t& base);

// 读档后修复。
void MF_FixAfterLoad(MagicBoard::FixAfterLoad_t& base);
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

## 静态关卡名称 - MC_LEVEL_NAME

指定当前关卡名称。优先级小于动态关卡名称 `mvDynLevelName`，大于 @ref magic_ref_lawn_app 的 `MF_GetLevelName`。

* ❌ 不可用于主魔法类。
* ✅ 可以用于子魔法类。

```cpp
static constexpr const SexyChar* MC_LEVEL_NAME = _S("Level Name");
```

## 动态关卡名称 - mvUseDynLevelName、mvDynLevelName

动态指定关卡内当前右下角的关卡名。优先级最高，对于过场中和菜单中的关卡名没有影响。

* ✅ 可以用于主魔法类。
* ❌ 不可用于子魔法类。

```cpp
// 为 true 则 mvDynLevelName 生效。当 Board 重新创建后，此值会重置为 false，请注意需手动存储状态。
static inline bool mvUseDynLevelName = false;
static inline SexyString mvDynLevelName = _S("Dynamic Name");
```

## 绘制关卡名称 - MF_DrawLevel

* ✅ 可以用于主魔法类。
* ✅ 可以用于子魔法类。

```cpp
void MF_DrawLevel(Graphics* g, const SexyString& theLevelName, int thePosX, int thePosY, DrawStringJustification theJustification, Font* theFont, const Color& theColor, MagicBoard::DrawLevel_t& base);
```

* @param g 绘图对象。

  @param theLevelName 关卡名称。

  @param thePosX X 坐标。

  @param thePosY Y 坐标。

  @param theFont 字体。
  
  @param theColor 颜色。
  
  @param theJustification 对齐方式。

## 画面偏移 - mvOffsetX、mvOffsetY

对关卡画面进行偏移，同时修改鼠标判定。

* ✅ 可以用于主魔法类。
* ❌ 不可用于子魔法类。

```cpp
static inline int mvOffsetX = 0;
static inline int mvOffsetY = 0;
```
