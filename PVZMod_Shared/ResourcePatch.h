#pragma once
#ifndef _PVZMOD_RESOURCE_PATCH_H_
#define _PVZMOD_RESOURCE_PATCH_H_

#include "PVZSTL.h"
#include <Windows.h>

namespace PVZMod
{
	class InitPatch;
	class ResourceManager;

	namespace ImageLib
	{
		class Image;
	}

	/// 资源相关补丁。
	namespace ResourcePatch
	{
		/*class ImageLoader
		{
		public:
			void PatchImageLoader(InitPatch& patch);

			virtual ImageLib::Image* GetImage(const std::string& thePath, const std::string& theName, const std::string& theExt, bool lookForAlphaImage);

			ImageLib::Image* LoadAlphaImage(const std::string& thePath, const std::string& theName, ImageLib::Image* theImage);

			template<typename T>
			bool TryImageExt(const std::string& thePath, const std::string& theName, const std::string& theExt, const std::string& theTargetExt, T func);
		private:
			static ImageLoader* gImageLoader;
			using GetImage_t = ImageLib::Image* (*)(const String& theFileName, bool lookForAlphaImage);
			static GetImage_t gRawGetImage;
		};*/


		/// 【补丁函数】将新的 XML 资源文件加入加载列表。
		///
		/// @param patch				补丁对象。
		/// @param theFileName			资源 XML 文件名。
		/// @param theExtractFunction	资源加载函数，使用 PVZMod_Tools 中的 ResourceGen 生成。
		void AddResFile(InitPatch& patch, const String& theFileName, bool(*theExtractFunction)(ResourceManager*, const char*));

		/// 【补丁函数】替换 PakInterface 类。
		///
		/// @tparam T		一个集成于PakInterface 的类，可以定义构造函数和析构函数，可以重写虚函数。<br/>
		///					可以定义一个魔法函数 `void MF_LoadPak();`，在这里面加载 PAK 文件。
		/// 
		/// @param patch	补丁对象。
		template <typename T>
		void ReplacePakInterface(InitPatch& patch);
	}
}

#include "ResourcePatch.inl"

#endif // !_PVZMOD_RESOURCE_PATCH_H_
