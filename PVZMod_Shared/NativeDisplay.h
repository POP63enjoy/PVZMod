#pragma once
#ifndef _PVZMOD_NATIVE_DISPLAY_H_
#define _PVZMOD_NATIVE_DISPLAY_H_

#include <cstdint>

namespace PVZMod
{
	/// ����Ϸ�ࡿ������ʾ�ӿڡ���ԭ `Sexy::NativeDisplay`��
	class NativeDisplay
	{
	public:
		int						mRGBBits;
		uint32_t				mRedMask;
		uint32_t				mGreenMask;
		uint32_t				mBlueMask;
		int						mRedBits;
		int						mGreenBits;
		int						mBlueBits;
		int						mRedShift;
		int						mGreenShift;
		int						mBlueShift;

	public:
		NativeDisplay();
		virtual ~NativeDisplay();
	};
}

#endif // !_PVZMOD_NATIVE_DISPLAY_H_
