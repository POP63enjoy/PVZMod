# MagicLawnApp {#magic_ref_lawn_app}

[TOC]

* 命名空间：`PVZMod::MagicLawnApp`。
* 目标类型：`PVZMod::LawnApp`。

```cpp
#include <LawnApp.h>
#include <MagicLawnApp.h>
```

## 构造函数和析构函数 - MF_Constructor、MF_Destructor

* ✅ 可以用于主魔法类。
* ❌ 不可用于子魔法类。

```cpp
void MF_Constructor(MagicLawnApp::Constructor_t& base);	 	// 构造函数。
void MF_Destructor(MagicLawnApp::Destructor_t& base);		// 析构函数。
```

## 初始化与释放 - MF_Init、MF_LoadingThreadProc、MF_LoadingCompleted、MF_Shutdown

* ✅ 可以用于主魔法类。
* ❌ 不可用于子魔法类。

```cpp
// 基本初始化。
void MF_Init(MagicLawnApp::Init_t& base);

// 在另一个线程进行耗时资源加载操作，会在标题界面显示进度条。
void MF_LoadingThreadProc(MagicLawnApp::LoadingThreadProc_t& base);

// 加载完成，点击标题界面中的开始游戏按钮后执行。
void MF_LoadingCompleted(MagicLawnApp::LoadingCompleted_t& base);

// 关闭游戏时释放资源。
void MF_Shutdown(MagicLawnApp::Shutdown_t& base);
```

## 游戏窗口消息处理 - MF_WindowProc

* ✅ 可以用于主魔法类。
* ❌ 不可用于子魔法类。

```cpp
static LRESULT MF_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, MagicLawnApp::WindowProc_t& base);
// 或
LRESULT MF_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, MagicLawnApp::WindowProc_t& base);
// 注意 this 指针可能为 nullptr。
```

* @param hwnd 窗口句柄。

  @param uMsg 消息类型。

  @param wParam 消息的第一个参数。

  @param lParam 消息的第二个参数。

* @return 消息处理结果。

## 全局对话框 - MC_NUM_DIALOGS、MF_DialogButtonDepress

* ✅ 可以用于主魔法类。
* ❌ 不可用于子魔法类。

```cpp
// 全局对话框数量，限制范围为 [MC_NUM_DIALOGS, 1000) 。
static constexpr int MC_NUM_DIALOGS = NUM_DIALOGS + 10;

// 处理全局对话框的按钮点击。
void MF_DialogButtonDepress(int theId, bool isYes, MagicLawnApp::DialogButtonDepress_t& base);
```

* @param theId 对话框 id。

  @param isYes 为 true 则点击“确定”或“是”按钮，为 false 则点击“取消”或“否”按钮。

## 各种补丁

* ✅ 可以用于主魔法类。
* ❌ 不可用于子魔法类。

```cpp
// 是否使用独占全屏。
// 为 true 时使用独占全屏，为 false 时使用无边框窗口全屏，重建窗口后生效。（默认为 true）
static inline bool mvExclusiveFullscreen = false;	

// 自动修复画面比例。
// 为 true 时，重建窗口将自动修复画面比例。（默认为 false）
static inline bool mvAutoFixAspectRatio = true;

// 窗口是否可以缩放。
// 为 true 时窗口可以缩放，重建窗口后生效。（默认为 false）
static inline bool mvWindowCanResize = true;
```

