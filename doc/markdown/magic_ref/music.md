# MagicMusic {#magic_ref_music}

[TOC]

* 命名空间：`PVZMod::MagicMusic`。
* 目标类型：`PVZMod::Music`。

```cpp
#include <Music.h>
#include <MagicMusic.h>
```

## 构造函数和析构函数 

直接使用 C++ 构造函数和析构函数。

* ✅ 可以用于主魔法类。
* ❌ 不可用于子魔法类。

```cpp
class MyMusic :public Music
{
public:
	MyMusic();		// 构造函数
	~MyMusic();		// 析构函数
};
```

## 播放音乐 - MF_PlayMusic

* ✅ 可以用于主魔法类。
* ❌ 不可用于子魔法类。

```cpp
void MF_PlayMusic(MusicTune theMusicTune, int theOffset, int theDrumsOffset, MagicMusic::PlayMusic_t& base);
```

* @param theMusicTune 音乐编号。

  @param theOffset 音乐进度，为 -1 则从头播放。

  @param theDrumsOffset 鼓音轨进度。

