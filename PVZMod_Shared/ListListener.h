#pragma once
#ifndef _PVZMOD_LIST_LISTENER_H_
#define _PVZMOD_LIST_LISTENER_H_

namespace PVZMod
{
	/// ����Ϸ�ࡿ�б��¼��ӿڡ���ԭ `Sexy::ListListener`��
	class ListListener
	{
	public:
		virtual void ListClicked(int theId, int theIdx, int theClickCount) {}
		virtual void ListClosed(int theId) {}
		virtual void ListHiliteChanged(int theId, int theOldIdx, int theNewIdx) {}
	};
}

#endif // !_PVZMOD_LIST_LISTENER_H_
