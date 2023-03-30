#pragma once
#ifndef _PVZMOD_CHECKBOX_LISTENER_H_
#define _PVZMOD_CHECKBOX_LISTENER_H_

namespace PVZMod
{
	/// 【游戏类】复选框事件接口。（原 Sexy::CheckboxListener）
	class CheckboxListener
	{
	public:
		virtual void			CheckboxChecked(int theId, bool checked) {}
	};
}

#endif // !_PVZMOD_CHECKBOX_LISTENER_H_
