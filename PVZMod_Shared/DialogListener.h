#pragma once
#ifndef _PVZMOD_DIALOG_LISTENER_H_
#define _PVZMOD_DIALOG_LISTENER_H_

namespace PVZMod
{
	/// 【游戏类】对话框事件接口。（原 `Sexy::DialogListener`）
	class DialogListener
	{
	public:
		virtual void			DialogButtonPress(int theDialogId, int theButtonId) {}
		virtual void			DialogButtonDepress(int theDialogId, int theButtonId) {}
	};
}

#endif // !_PVZMOD_DIALOG_LISTENER_H_
