#include "ResourceManager.h"

using namespace PVZMod;

bool ResourceManager::ParseResourcesFile(const String& theFilename)
{
	bool result;
	int func = 0x5BD530;
	__asm
	{
		push this
		mov ecx, theFilename
		call func
		mov result, al
	}
	return result;
}

bool ResourceManager::ReparseResourcesFile(const String& theFilename)
{
	bool oldDefined = mAllowAlreadyDefinedResources;
	mAllowAlreadyDefinedResources = true;

	bool aResult = ParseResourcesFile(theFilename);

	mAllowAlreadyDefinedResources = oldDefined;

	return aResult;
}

bool ResourceManager::ReplaceImage(const String& theId, Image* theImage)
{
	ResMap::iterator anItr = mImageMap.find(theId);
	if (anItr != mImageMap.end())
	{
		anItr->second->DeleteResource();
		((ImageRes*)anItr->second)->mImage = (MemoryImage*)theImage;
		((ImageRes*)anItr->second)->mImage.mOwnsUnshared = true;
		return true;
	}
	else
		return false;
}

void ResourceManager::DeleteImage(const String& theName)
{
	ReplaceImage(theName, NULL);
}

SharedImageRef ResourceManager::LoadImage(const String& theName)
{
	ResMap::iterator anItr = mImageMap.find(theName);
	if (anItr == mImageMap.end())
		return NULL;

	ImageRes* aRes = (ImageRes*)anItr->second;
	if ((DDImage*)aRes->mImage != NULL)
		return aRes->mImage;

	if (aRes->mFromProgram)
		return NULL;

	if (!DoLoadImage(aRes))
		return NULL;

	return aRes->mImage;
}
