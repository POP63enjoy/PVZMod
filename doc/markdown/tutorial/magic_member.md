# 魔法成员机制 {#tutorial_magic_member}

[TOC]

魔法成员是本框架的一个重要的机制，基于 C++ 的 SFINAE 特性，判断指定名称和类型的类成员是否存在，继而进行相应的补丁操作。

## 基本使用方法

### 主魔法类

在 @ref magic_ref 中查看支持魔法成员的类型，调用对应命名空间的 `RegisterMain` 函数，模板参数传入一个类型，类型的限定条件见对应的函数的文档，如：

```cpp
#include <PVZMod.h>

#include <LawnApp.h>
#include <MagicLawnApp.h>

using namespace PVZMod;

class MyApp :public LawnApp
{
public:
	
};

void PVZMod::Main(InitPatch& patch)
{
	MagicLawnApp::RegisterMain<MyApp>(patch);
}
```

这个例子中，`PVZMod::LawnApp` 类通过 @ref magic_ref_lawn_app 替换成了 `MyApp` 类，这个类被称为“主魔法类”，此时，可以参考文档中的说明，在 `MyApp` 中添加对应的成员，实现对应的补丁，如以下例子，实现了窗口等比缩放和无边框窗口全屏：

```cpp
class MyApp :public LawnApp
{
public:
	LRESULT MF_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, MagicLawnApp::WindowProc_t& base)
	{
		switch (uMsg)
		{
		case WM_SETCURSOR:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		case WM_SIZING:
			if (this)
				return WindowSizingKeepAspectRatio(hwnd, wParam, lParam);
			break;
		case WM_SIZE:
			if (this)
				KeepAspectRatioFullClient(LOWORD(lParam), HIWORD(lParam));
			InvalidateRect(hwnd, nullptr, FALSE);
			return 0;
		case WM_PAINT:
			if (this && mInitialized && !mSEHOccured)
			{
				RECT aClientRect;
				GetClientRect(hwnd, &aClientRect);

				PAINTSTRUCT ps;
				HDC dc = BeginPaint(hwnd, &ps);

				FillRect(dc, &aClientRect, (HBRUSH)GetStockObject(BLACK_BRUSH));

				if (mRunning)
					Redraw(nullptr);

				EndPaint(hwnd, &ps);

				return 0;
			}
		}
		return base();
	}

	inline static bool mvExclusiveFullscreen = false;
	inline static bool mvAutoFixAspectRatio = true;
	inline static bool mvWindowCanResize = true;
};
```

### 子魔法类

部分类型还支持将特定条件的对象替换成单独的类型，这个类型被称为“子魔法类”，例如以下代码，`MyPlant` 为主魔法类，而 `MyPeaShooter` 为子魔法类，仅对豌豆射手生效：

```cpp
#include <PVZMod.h>

#include <Plant.h>
#include <MagicPlant.h>

using namespace PVZMod;

class MyPlant :public Plant
{
public:

};

class MyPeaShooter :public MyPlant
{
public:

};

void PVZMod::Main(InitPatch& patch)
{
	MagicPlant::RegisterMain<MyPlant>(patch)
		.RegisterPlant<MyPeaShooter>(patch, SEED_PEASHOOTER);
}
```

部分魔法成员仅可用于子魔法类，或仅可用于主魔法类，请注意文档中的标注。

## 各种魔法成员的使用

魔法成员的使用应参考 @ref magic_ref 中的说明，保证类型正确，否则将报错。

### 魔法函数

魔法函数以 `MF_` 开头，定义后，会自动进行相应补丁，通常会替换某个原版函数，通常有一个名为 `base` 的参数，这个参数用于调用被替换的函数，可以使用 `base();` 直接以原始参数调用被替换的函数，也可以手动传入不同的参数，以不同的参数调用被替换的函数。

原版有些较长的函数，被拆成了多个魔法函数，以实现仅对函数的一部分进行替换，例如 @ref magic_ref_board 中的 `MF_ZombiePicker`，将原版的 `Board::ZombiePicker` 分成了 `MF_ZombiePicker_CalculateNumWaves`、`MF_ZombiePicker_SpecialLevelPut`、`MF_ZombiePicker_CalculateBasicPoints`、`MF_ZombiePicker_PutBeforeMultiple`、`MF_ZombiePicker_CalculateMultiplePoints`、`MF_ZombiePicker_PutPreset` 和 `MF_ZombiePicker_PutRandom` 七部分，每部分可以单独替换。

### 魔法变量和魔法常量

魔法变量以 `mv` 开头，魔法常量以 `MC_` 开头。文档所中描述的所有有关魔法变量和魔法常量的“默认值”均为未定义情况下默认的值，而非定义后未初始化的默认值，一旦定义，必须初始化。

## 新增成员变量

通常情况下，仅可在主魔法类中新增成员变量，框架将自动为新增的成员变量分配多余的空间。对于新增成员变量的初始化，要注意，分几种情况，像是 @ref magic_ref_music 直接使用 C++ 原本的构造函数和析构函数，则按照正常方式初始化；而像是 @ref magic_ref_lawn_app 这种，使用 `MF_Constructor` 和 `MF_Destructor`，则要手动初始化，尤其是对于非基本类型的成员，则需要手动调用其构造函数和析构函数，可以使用框架提供的 `PVZMOD_INIT_GROUP` 进行批量初始化，例如：

```cpp
class MyApp :public LawnApp
{
public:
	PVZMOD_INIT_GROUP(MyApp, InitGroup, (
		std::vector<int> a;
		std::string b;
		std::map<int, int> c;
	), InitGroup_t() :b("hello world") {});

	void MF_Constructor(MagicLawnApp::Constructor_t& base)
	{
		base();
		mInitGroup.ctor();
	}
	void MF_Destructor(MagicLawnApp::Destructor_t& base)
	{
		mInitGroup.dtor();
		base();
	}
};
```

另外，对于如 `PVZMod::Board` 这种需要存档的类型，如果新增非基本类型的成员，则需要使用 `MF_Sync` 进行存档。
