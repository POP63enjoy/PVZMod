#include "ResourcePatch.h"
#include "ImageLib.h"
#include <algorithm>
#include "PVZMod.h"
#include "LawnApp.h"
#include "ResourceManager.h"
#include "Res.h"

using namespace PVZMod;
using namespace ResourcePatch;
using namespace ImageLib;

/*ImageLoader* ImageLoader::gImageLoader = nullptr;
ImageLoader::GetImage_t ImageLoader::gRawGetImage = nullptr;

void ImageLoader::PatchImageLoader(InitPatch& patch)
{
	patch.PatchTask("ResourcePatch::ImageLoader::PatchImageLoader", [&]
		{
			gImageLoader = this;
			GetImage_t getImage = [](const String& theName, bool lookForAlphaImage)
			{
				int aLastDotPos = theName.rfind('.');
				int aLastSlashPos = max((int)theName.rfind('\\'), (int)theName.rfind('/'));

				std::string anExt;
				std::string aFilename;
				std::string aPath;

				aPath = theName.substr(0, aLastSlashPos + 1);
				if (aLastDotPos > aLastSlashPos)
				{
					anExt = theName.substr(aLastDotPos, theName.length() - aLastDotPos);
					aFilename = theName.substr(aLastSlashPos + 1, aLastDotPos - aLastSlashPos - 1);
				}
				else
				{
					aFilename = theName.substr(aLastSlashPos + 1, theName.length() - aLastSlashPos - 1);
				}
				return gImageLoader->GetImage(aPath, aFilename, anExt, lookForAlphaImage);
			};
			gRawGetImage = (GetImage_t)patch.mHook.HookFunction((void*)0x5d7960, getImage);
		}, true, true);
}

ImageLib::Image* ImageLoader::GetImage(const std::string& thePath, const std::string& theName, const std::string& theExt, bool lookForAlphaImage)
{
	return gRawGetImage((thePath + theName + theExt).c_str(), lookForAlphaImage);
}

ImageLib::Image* ImageLoader::LoadAlphaImage(const std::string& thePath, const std::string& theName, ImageLib::Image* theImage)
{
	ImageLib::Image* anAlphaImage = nullptr;
	// Check _ImageName
	anAlphaImage = GetImage(thePath, "_" + theName, "", false);

	// Check ImageName_
	if (anAlphaImage == nullptr)
		anAlphaImage = GetImage(thePath, theName + "_", "", false);

	ImageLib::Image* anImage = theImage;

	if (anAlphaImage != nullptr)
	{
		if (anImage != nullptr)
		{
			if ((anImage->mWidth == anAlphaImage->mWidth) &&
				(anImage->mHeight == anAlphaImage->mHeight))
			{
				unsigned long* aBits1 = anImage->mBits;
				unsigned long* aBits2 = anAlphaImage->mBits;
				int aSize = anImage->mWidth * anImage->mHeight;

				for (int i = 0; i < aSize; i++)
				{
					*aBits1 = (*aBits1 & 0x00FFFFFF) | ((*aBits2 & 0xFF) << 24);
					++aBits1;
					++aBits2;
				}
			}

			delete anAlphaImage;
		}
		else if (gAlphaComposeColor == 0xFFFFFF)
		{
			anImage = anAlphaImage;

			unsigned long* aBits1 = anImage->mBits;

			int aSize = anImage->mWidth * anImage->mHeight;
			for (int i = 0; i < aSize; i++)
			{
				*aBits1 = (0x00FFFFFF) | ((*aBits1 & 0xFF) << 24);
				++aBits1;
			}
		}
		else
		{
			const int aColor = gAlphaComposeColor;
			anImage = anAlphaImage;

			unsigned long* aBits1 = anImage->mBits;

			int aSize = anImage->mWidth * anImage->mHeight;
			for (int i = 0; i < aSize; i++)
			{
				*aBits1 = aColor | ((*aBits1 & 0xFF) << 24);
				++aBits1;
			}
		}
	}
	return anImage;
}*/

void ResourcePatch::AddResFile(InitPatch& patch, const String& theFileName, bool(*theExtractFunction)(ResourceManager*, const char*))
{
	patch.PatchTask("ResourcePatch::AddResFile", [&]
		{
			patch.PatchTask("ResourcePatch::AddResFile Patch", [&]
				{
					patch.mHook.InsertCode((void*)0x45493e, [](Hook::Regs* regs)
						{
							LawnApp* app = (LawnApp*)regs->ebp;
							for (auto& file : gResFileList)
							{
								if (!app->mResourceManager->ParseResourcesFile(file.first))
								{
									app->ShowResourceError(true);
								}
							}
						});
				});
			gResFileList.push_back({ theFileName,theExtractFunction });
		}, false);
}

/*void ResourcePatch::DisableMainPakLoad(InitPatch& patch)
{
	patch.PatchTask("ResourcePatch::DisableMainPakLoad", [&]
		{
			*(DWORD*)0x55a17a = 0x909026EB;
		});
}*/
