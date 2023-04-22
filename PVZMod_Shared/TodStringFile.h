#pragma once
#ifndef _PVZMOD_TOD_STRING_FILE_H_
#define _PVZMOD_TOD_STRING_FILE_H_

#include "SexyCommon.h"

namespace PVZMod
{
	/// ����Ϸ��������ȡ TodString �ı�����ԭ `::%TodStringListReadItems`��
	///
	/// @param theFileText	TodString �ı���
	/// @result				Ϊ false ���ȡʧ�ܡ�
	bool				TodStringListReadItems(const SexyChar* theFileText);

	/// ����Ϸ��������ȡ TodString �ļ�����ԭ `::%TodStringListReadFile`��
	///
	/// @param theFileName	�ļ�����
	/// @result				Ϊ false ���ȡʧ�ܡ�
	bool				TodStringListReadFile(const char* theFileName);

	/// ����Ϸ���������� TodString �ļ�������ʧ���򵯳���Ϣ�򡣣�ԭ `::%TodStringListLoad`��
	///
	/// @param theFileName	�ļ�����
	void                TodStringListLoad(const char* theFileName);

	/// ����Ϸ��������ѯ TodString ���Ӧ�ַ�������ԭ `::%TodStringListFind`��
	///
	/// @param theName	TodString �����ƣ������������š�
	/// @return			��Ӧ���ַ�������������ڣ��򷵻� "<Missing %s>" ��
	SexyString          TodStringListFind(const SexyString& theName);

	/// ����Ϸ���������� TodString����ԭ `::%TodStringTranslate`��
	///
	/// @param theName	�������ŵ� TodString �����ƻ���ͨ�ַ�����
	/// @return			��� theName �Ǵ��������ŵ� TodString ��򷵻� TodStringListFind ��ѯ�Ľ�����������ͨ�ַ������򷵻��ַ�������
	SexyString			TodStringTranslate(const SexyString& theString);

	/// ����Ϸ���������� TodString����ԭ `::%TodStringTranslate`��
	///
	/// @param theName	�������ŵ� TodString �����ƻ���ͨ�ַ�����
	/// @return			��� theName �Ǵ��������ŵ� TodString ��򷵻� TodStringListFind ��ѯ�Ľ�����������ͨ�ַ������򷵻��ַ�������
	SexyString			TodStringTranslate(const SexyChar* theString);

	/// ����Ϸ��������ѯ TodString ���Ƿ���ڡ���ԭ `::%TodStringListExists`��
	///
	/// @param theName	TodString �����ƣ����������š�
	/// @return			��� TodString ����ڻ� theName �����������ţ����� false�����򷵻� true��
	bool                TodStringListExists(const SexyString& theString);
}

#endif // !_PVZMOD_TOD_STRING_FILE_H_
