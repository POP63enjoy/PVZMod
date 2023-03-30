#pragma once
#ifndef _PVZMOD_SHARED_IMAGE_H_
#define _PVZMOD_SHARED_IMAGE_H_

#include "PVZSTL.h"

namespace PVZMod
{
	class Image;
	class DDImage;
	class MemoryImage;

	class SharedImage
	{
	public:
		DDImage*				mImage;
		int						mRefCount;		

		SharedImage();
	};

	typedef Map<std::pair<String, String>, SharedImage> SharedImageMap;

	class SharedImageRef
	{
	public:
		SharedImage*			mSharedImage;
		MemoryImage*			mUnsharedImage;
		bool					mOwnsUnshared;

	public:
		SharedImageRef();
		SharedImageRef(const SharedImageRef& theSharedImageRef);
		SharedImageRef(SharedImage* theSharedImage);
		~SharedImageRef();

		void					Release();

		SharedImageRef&			operator=(const SharedImageRef& theSharedImageRef);
		SharedImageRef&			operator=(SharedImage* theSharedImage);
		SharedImageRef&			operator=(MemoryImage* theUnsharedImage);
		MemoryImage*			operator->();
		operator Image*();
		operator MemoryImage*();
		operator DDImage*();
	};
}

#endif // !_PVZMOD_SHARED_IMAGE_H_
