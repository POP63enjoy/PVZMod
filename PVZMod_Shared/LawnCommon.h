#pragma once
#ifndef _PVZMOD_LAWN_COMMON_H_
#define _PVZMOD_LAWN_COMMON_H_

#include "EditWidget.h"

namespace PVZMod
{
	constexpr int BOARD_WIDTH = 800, BOARD_HEIGHT = 600;

	class Checkbox;
	class CheckboxListener;
	class LawnEditWidget;
	class EditListener;
	class Dialog;

	/// 【游戏函数】创建复选框（原 ::MakeNewCheckBox）。
	///
	/// @param theId		复选框 ID。
	/// @param theListener	事件侦听器。
	/// @param theDefault	是否默认框选。
	/// 
	/// @return				复选框指针。
	extern Checkbox* (*MakeNewCheckBox)(int theId, CheckboxListener* theListener, bool theDefault);

	/// 【游戏类】PVZ 专用编辑框（原 ::LawnEditWidget）
	class LawnEditWidget : public EditWidget
	{
	public:
		Dialog*					mDialog;
		bool					mAutoCapFirstLetter;

	public:
		LawnEditWidget(int theId, EditListener* theListener, Dialog* theDialog);
		~LawnEditWidget();

		virtual void			KeyDown(KeyCode theKey);
		virtual void			KeyChar(char theChar);
	};

	/// 【游戏函数】创建编辑框。
	///
	/// @param theId		编辑框 ID。
	/// @param theListener	事件侦听器。
	/// @param theDialog	所属对话框。
	/// 
	/// @return				编辑框指针。
	LawnEditWidget*				CreateEditWidget(int theId, EditListener* theListener, Dialog* theDialog);

	/// 【游戏函数】绘制编辑框。
	/// 
	///	@param g			绘图对象。
	/// @param theWidget	编辑框指针。
	void						DrawEditBox(Graphics* g, EditWidget* theWidget);
}

#endif // !_PVZMOD_LAWN_COMMON_H_
