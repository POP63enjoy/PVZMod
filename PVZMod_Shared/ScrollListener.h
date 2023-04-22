#pragma once
#ifndef _PVZMOD_SCROLL_LISTENER_H_
#define _PVZMOD_SCROLL_LISTENER_H_

namespace PVZMod
{
	/// 【游戏类】滚动条事件接口。（原 `Sexy::ScrollListener`）
	class ScrollListener
	{
	public:
		virtual void ScrollPosition(int theId, double thePosition) {};
	};
}

#endif // !_PVZMOD_SCROLL_LISTENER_H_
