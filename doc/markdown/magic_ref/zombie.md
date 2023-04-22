# MagicZombie {#magic_ref_zombie}

[TOC]

* 命名空间：`PVZMod::MagicZombie`
* 目标类型：`PVZMod::Zombie`

```cpp
#include <Zombie.h>
#include <MagicZombie.h>
```

## 初始化 - MF_ZombieInitialize

* ✅ 可以用于主魔法类。
* ✅ 可以用于子魔法类。

```cpp
// 初始化成员变量，返回僵尸定义信息。（一般直接原封不动返回 base 的返回值）
ZombieDefinition& MF_ZombieInitialize_InitMemberVariable(int theRow, ZombieType theType, bool theVariant, Zombie* theParentZombie, int theFromWave, MagicZombie::ZombieInitialize_InitMemberVariable_t& base);

// 初始化动画。
void MF_ZombieInitialize_InitReanimation(ZombieDefinition& theZombieDef, MagicZombie::ZombieInitialize_InitReanimation_t& base);

// 针对不同僵尸类型初始化，可传出渲染图层和渲染图层偏移。
void MF_ZombieInitialize_InitType(ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer& theRenderLayer, int& theRenderOffset, MagicZombie::ZombieInitialize_InitType_t& base);

// 针对不同僵尸类型初始化之后。
void MF_ZombieInitialize_AfterInitType(ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer theRenderLayer, int theRenderOffset, MagicZombie::ZombieInitialize_AfterInitType_t& base);
```

* @param theRow 僵尸所在行。

  @param theType 僵尸类型。

  @param theVariant 是否为变体。

  @param theParentZombie 父僵尸对象。

  @param theFromWave 僵尸所在波数。

  @param theZombieDef 僵尸定义信息。

  @param theRenderLayer 僵尸渲染图层。

  @param theRenderOffset 僵尸渲染图层偏移。

## 对象上限 - MC_DATA_ARRAY_SIZE

默认值 1024。

* ✅ 可以用于主魔法类。
* ❌ 不可用于子魔法类。

```cpp
static constexpr size_t MC_DATA_ARRAY_SIZE = 2048;	// 将对象上限设置为 2048
```
