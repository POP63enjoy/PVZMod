#pragma once
#ifndef _PVZMOD_BUTTON_LISTENER_H_
#define _PVZMOD_BUTTON_LISTENER_H_

namespace PVZMod
{
	/// 【游戏类】按钮事件接口。（原 Sexy::ButtonListener）
	class ButtonListener
	{
	public:
		virtual void			ButtonPress(int theId) {}
		virtual void			ButtonPress(int theId, int theClickCount) { ButtonPress(theId); }
		virtual void			ButtonDepress(int theId) {}
		virtual void			ButtonDownTick(int theId) {}
		virtual void			ButtonMouseEnter(int theId) {}
		virtual void			ButtonMouseLeave(int theId) {}
		virtual void			ButtonMouseMove(int theId, int theX, int theY) {}
	};
}

#endif // !_PVZMOD_BUTTON_LISTENER_H_
