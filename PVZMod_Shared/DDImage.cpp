#include "DDImage.h"

using namespace PVZMod;

bool DDImage::Check3D(Image* theImage)
{
	int func = 0x5719f0;
	bool result;
	__asm
	{
		mov eax, theImage
		call func
		mov result, al
	}
	return result;
}

bool DDImage::Check3D(DDImage* theImage)
{
	int func = 0x571af0;
	bool result;
	__asm
	{
		mov ecx, theImage
		call func
		mov result, al
	}
	return result;
}

DDImage* DDImage::GetNew()
{
	DDImage* ddimage = (DDImage*)operator new(sizeof(DDImage));
	int func = 0x5718e0;
	__asm
	{
		push ddimage
		call func
	}
	return ddimage;
}

void DDImage::DeleteDDSurface()
{
	if (mSurface != NULL)
	{
		if ((mColorTable == NULL) && (mBits == NULL) && (mD3DData == NULL))
			GetBits();

		mSurface->Release();
		mSurface = NULL;
	}
}

LPDIRECTDRAWSURFACE DDImage::GetSurface()
{
	int func = 0x5726f0;
	LPDIRECTDRAWSURFACE result;
	__asm
	{
		mov eax, this
		call func
		mov result, eax
	}
	return result;
}

void DDImage::DeleteAllNonSurfaceData()
{
	delete[] mBits;
	mBits = NULL;

	delete[] mNativeAlphaData;
	mNativeAlphaData = NULL;

	delete[] mRLAdditiveData;
	mRLAdditiveData = NULL;

	delete[] mRLAlphaData;
	mRLAlphaData = NULL;

	delete[] mColorTable;
	mColorTable = NULL;

	delete[] mColorIndices;
	mColorIndices = NULL;
}
