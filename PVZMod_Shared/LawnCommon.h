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

	/// ����Ϸ������������ѡ�򡣣�ԭ `::%MakeNewCheckBox`��
	///
	/// @param theId		��ѡ�� ID��
	/// @param theListener	�¼���������
	/// @param theDefault	�Ƿ�Ĭ�Ͽ�ѡ��
	/// 
	/// @return				��ѡ��ָ�롣
	extern Checkbox* (*MakeNewCheckBox)(int theId, CheckboxListener* theListener, bool theDefault);

	/// ����Ϸ�ࡿPVZ ר�ñ༭�򡣣�ԭ `::%LawnEditWidget`��
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

	/// ����Ϸ�����������༭�򡣣�ԭ `::%CreateEditWidget`��
	///
	/// @param theId		�༭�� ID��
	/// @param theListener	�¼���������
	/// @param theDialog	�����Ի���
	/// 
	/// @return				�༭��ָ�롣
	LawnEditWidget*				CreateEditWidget(int theId, EditListener* theListener, Dialog* theDialog);

	/// ����Ϸ���������Ʊ༭�򡣣�ԭ `::%DrawEditBox`��
	/// 
	///	@param g			��ͼ����
	/// @param theWidget	�༭��ָ�롣
	void						DrawEditBox(Graphics* g, EditWidget* theWidget);
}

#endif // !_PVZMOD_LAWN_COMMON_H_
