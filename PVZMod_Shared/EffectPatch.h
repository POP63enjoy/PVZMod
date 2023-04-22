#pragma once
#ifndef _PVZMOD_EFFECT_PATCH_H_
#define _PVZMOD_EFFECT_PATCH_H_

namespace PVZMod
{
	class InitPatch;
	class ReanimationParams;

	/// ��Ч��ز�����
	namespace EffectPatch
	{
		/// �������������滻�����������顣
		/// 
		/// �˺������滻���ж���������׷�ӡ�
		/// 
		/// ����ʹ�� PVZMod_Tools �е� ReanimManager ���ߣ��˹��߻����ɵ�����������Ĵ���ʵ������������
		/// 
		/// @param patch		��������
		/// @param theArray		�����������顣
		/// @param theSize		�����С��
		void SetReanimationParamArray(InitPatch& patch, ReanimationParams* theArray, size_t theSize);
	}
}

#endif // !_PVZMOD_EFFECT_PATCH_H_
