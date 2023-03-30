#include "ImageLib.h"
#include "PakInterface.h"

using namespace PVZMod;

ImageLib::Image::Image()
{
	mWidth = 0;
	mHeight = 0;
	mBits = NULL;
}

ImageLib::Image::~Image()
{
	delete[] mBits;
}

int	ImageLib::Image::GetWidth()
{
	return mWidth;
}

int	ImageLib::Image::GetHeight()
{
	return mHeight;
}

unsigned long* ImageLib::Image::GetBits()
{
	return mBits;
}
