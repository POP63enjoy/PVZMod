#pragma once
#ifndef _PVZMOD_CHECKBOX_LISTENER_H_
#define _PVZMOD_CHECKBOX_LISTENER_H_

namespace PVZMod
{
	/// ����Ϸ�ࡿ��ѡ���¼��ӿڡ���ԭ `Sexy::CheckboxListener`��
	class CheckboxListener
	{
	public:
		virtual void			CheckboxChecked(int theId, bool checked) {}
	};
}

#endif // !_PVZMOD_CHECKBOX_LISTENER_H_
