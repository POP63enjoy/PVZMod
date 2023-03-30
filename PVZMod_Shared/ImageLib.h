#pragma once
#ifndef _PVZMOD_IMAGE_LIB_H_
#define _PVZMOD_IMAGE_LIB_H_

#include "SexyCommon.h"

namespace PVZMod
{
	namespace ImageLib
	{
		class Image
		{
		public:
			int						mWidth;
			int						mHeight;
			unsigned long*			mBits;

		public:
			Image();
			virtual ~Image();

			int						GetWidth();
			int						GetHeight();
			unsigned long*			GetBits();
		};
	}
}

#endif // !_PVZMOD_IMAGE_LIB_H_
