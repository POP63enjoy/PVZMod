#pragma once
#ifndef _PVZMOD_SCROLL_LISTENER_H_
#define _PVZMOD_SCROLL_LISTENER_H_

namespace PVZMod
{
	/// ����Ϸ�ࡿ�������¼��ӿڡ���ԭ `Sexy::ScrollListener`��
	class ScrollListener
	{
	public:
		virtual void ScrollPosition(int theId, double thePosition) {};
	};
}

#endif // !_PVZMOD_SCROLL_LISTENER_H_
