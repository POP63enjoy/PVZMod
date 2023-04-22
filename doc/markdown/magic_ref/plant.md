# MagicPlant {#magic_ref_plant}

[TOC]

* 命名空间：`PVZMod::MagicPlant`
* 目标类型：`PVZMod::Plant`

```cpp
#include <Plant.h>
#include <MagicPlant.h>
```

## 初始化 - MF_PlantInitialize

* ✅ 可以用于主魔法类。
* ✅ 可以用于子魔法类。

```cpp
// 初始化成员变量，返回植物定义信息。（一般直接原封不动返回 base 的返回值）
PlantDefinition& MF_PlantInitialize_InitMemberVariable(int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType, MagicPlant::PlantInitialize_InitMemberVariable_t& base);

// 初始化动画，返回主体动画指针。
Reanimation* MF_PlantInitialize_InitReanimation(PlantDefinition& thePlantDef, MagicPlant::PlantInitialize_InitReanimation& base);

// 针对不同植物类型初始化之前。
void MF_PlantInitialize_BeforeInitType(PlantDefinition& thePlantDef, Reanimation* theBodyReanim, MagicPlant::PlantInitialize_BeforeInitType& base);

// 针对不同植物类型初始化。
void MF_PlantInitialize_InitType(PlantDefinition& thePlantDef, Reanimation* theBodyReanim, MagicPlant::PlantInitialize_InitType& base);

// 针对不同植物类型初始化之后。
void MF_PlantInitialize_AfterInitType(PlantDefinition& thePlantDef, Reanimation* theBodyReanim, MagicPlant::PlantInitialize_AfterInitType& base);
```

* @param theGridX 列数。

  @param theGridY 行数。

  @param theSeedType 植物类型。

  @param theImitaterType 模仿者类型。

  @param thePlantDef 植物定义信息。

  @param theBodyReanim 植物主体动画。

## 对象上限 - MC_DATA_ARRAY_SIZE

默认值 1024。

* ✅ 可以用于主魔法类。
* ❌ 不可用于子魔法类。

```cpp
static constexpr size_t MC_DATA_ARRAY_SIZE = 2048;	// 将对象上限设置为 2048
```

