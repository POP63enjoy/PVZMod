#pragma once
#ifndef _PVZMOD_EDIT_LISTENER_H_
#define _PVZMOD_EDIT_LISTENER_H_

#include "PVZSTL.h"
#include "KeyCodes.h"
namespace PVZMod
{
	/// ����Ϸ�ࡿ������¼��ӿڡ���ԭ `Sexy::EditListener`��
	class EditListener
	{
	public:
		virtual void			EditWidgetText(int theId, const SexyString& theString) {};

		virtual bool			AllowKey(int theId, KeyCode theKey) { return true; }
		virtual bool			AllowChar(int theId, SexyChar theChar) { return true; }
		virtual bool			AllowText(int theId, const SexyString& theText) { return true; }
	};
}

#endif // !_PVZMOD_EDIT_LISTENER_H_
