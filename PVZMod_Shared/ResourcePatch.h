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

	/// ��Դ��ز�����
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


		/// ���������������µ� XML ��Դ�ļ���������б�
		///
		/// @param patch				��������
		/// @param theFileName			��Դ XML �ļ�����
		/// @param theExtractFunction	��Դ���غ�����ʹ�� PVZMod_Tools �е� ResourceGen ���ɡ�
		void AddResFile(InitPatch& patch, const String& theFileName, bool(*theExtractFunction)(ResourceManager*, const char*));

		/// �������������滻 PakInterface �ࡣ
		///
		/// @tparam T		һ��������PakInterface ���࣬���Զ��幹�캯��������������������д�麯����<br/>
		///					���Զ���һ��ħ������ `void MF_LoadPak();`������������� PAK �ļ���
		/// 
		/// @param patch	��������
		template <typename T>
		void ReplacePakInterface(InitPatch& patch);
	}
}

#include "ResourcePatch.inl"

#endif // !_PVZMOD_RESOURCE_PATCH_H_
