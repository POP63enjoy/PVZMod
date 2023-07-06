#pragma once
#ifndef _PVZMOD_RESOURCE_MANAGER_H_
#define _PVZMOD_RESOURCE_MANAGER_H_

#include "SexyCommon.h"
#include "SharedImage.h"
#include "Image.h"
#include <Windows.h>

namespace PVZMod
{
	namespace ImageLib
	{
		class Image;
	};

	class XMLParser;
	class XMLElement;
	class Image;
	class SoundInstance;
	class SexyAppBase;
	class Font;

	typedef Map<String, String>	StringToStringMap;
	typedef Map<SexyString, SexyString>	XMLParamMap;

	/// 【游戏类】资源管理器。（原 `Sexy::ResourceManager`）
	class ResourceManager
	{
	protected:
		enum ResType
		{
			ResType_Image,
			ResType_Sound,
			ResType_Font
		};

		struct BaseRes
		{
			ResType			mType;
			String			mId;
			String			mResGroup;
			String			mPath;
			XMLParamMap		mXMLAttributes;
			bool			mFromProgram;

			virtual ~BaseRes() {}
			virtual void DeleteResource() { }
		};

		struct ImageRes : public BaseRes
		{
			SharedImageRef	mImage;
			String			mAlphaImage;
			String			mAlphaGridImage;
			String			mVariant;
			bool			mAutoFindAlpha;
			bool			mPalletize;
			bool			mA4R4G4B4;
			bool			mA8R8G8B8;
			bool			mDDSurface;
			bool			mPurgeBits;
			bool			mMinimizeSubdivisions;
			int				mRows;
			int				mCols;
			DWORD			mAlphaColor;
			AnimInfo		mAnimInfo;

			ImageRes() { mType = ResType_Image; }
			virtual void DeleteResource();
		};

		struct SoundRes : public BaseRes
		{
			int				mSoundId;
			double			mVolume;
			int				mPanning;

			SoundRes() { mType = ResType_Sound; }
			virtual void DeleteResource();
		};

		struct FontRes : public BaseRes
		{
			Font*			mFont;
			Image*			mImage;
			String			mImagePath;
			String			mTags;

			// For SysFonts
			bool			mSysFont;
			bool			mBold;
			bool			mItalic;
			bool			mUnderline;
			bool			mShadow;
			int				mSize;


			FontRes() { mType = ResType_Font; }
			virtual void DeleteResource();
		};

		typedef Map<String, BaseRes*> ResMap;
		typedef List<BaseRes*> ResList;
		typedef Map<String, ResList, StringLessNoCase> ResGroupMap;

		Set<String, StringLessNoCase> mLoadedGroups;

		ResMap					mImageMap;
		ResMap					mSoundMap;
		ResMap					mFontMap;

		XMLParser*				mXMLParser;
		String					mError;
		bool					mHasFailed;
		SexyAppBase*			mApp;
		String					mCurResGroup;
		String					mDefaultPath;
		String					mDefaultIdPrefix;
		bool					mAllowMissingProgramResources;
		bool					mAllowAlreadyDefinedResources; // for reparsing file while running
		bool					mHadAlreadyDefinedError;

		ResGroupMap				mResGroupMap;
		ResList*				mCurResGroupList;
		Iterator<ResList>		mCurResGroupListItr;


		bool					Fail(const String& theErrorText);

		virtual bool			ParseCommonResource(XMLElement& theElement, BaseRes* theRes, ResMap& theMap);
		virtual bool			ParseSoundResource(XMLElement& theElement);
		virtual bool			ParseImageResource(XMLElement& theElement);
		virtual bool			ParseFontResource(XMLElement& theElement);
		virtual bool			ParseSetDefaults(XMLElement& theElement);
		virtual bool			ParseResources();

		bool					DoParseResources();
		void					DeleteMap(ResMap& theMap);
		virtual void			DeleteResources(ResMap& theMap, const String& theGroup);

		bool					LoadAlphaGridImage(ImageRes* theRes, DDImage* theImage);
		bool					LoadAlphaImage(ImageRes* theRes, DDImage* theImage);
		virtual bool			DoLoadImage(ImageRes* theRes);
		virtual bool			DoLoadFont(FontRes* theRes);
		virtual bool			DoLoadSound(SoundRes* theRes);

		int						GetNumResources(const String& theGroup, ResMap& theMap);

	public:
		ResourceManager(SexyAppBase* theApp);
		virtual ~ResourceManager();

		bool					ParseResourcesFile(const String& theFilename);
		bool					ReparseResourcesFile(const String& theFilename);

		String					GetErrorText();
		bool					HadError();
		bool					IsGroupLoaded(const String& theGroup);

		int						GetNumImages(const String& theGroup);
		int						GetNumSounds(const String& theGroup);
		int						GetNumFonts(const String& theGroup);
		int						GetNumResources(const String& theGroup);

		virtual bool			LoadNextResource();
		virtual void			ResourceLoadedHook(BaseRes* theRes);

		virtual void			StartLoadResources(const String& theGroup);
		virtual bool			LoadResources(const String& theGroup);

		bool					ReplaceImage(const String& theId, Image* theImage);
		bool					ReplaceSound(const String& theId, int theSound);
		bool					ReplaceFont(const String& theId, Font* theFont);

		void					DeleteImage(const String& theName);
		SharedImageRef			LoadImage(const String& theName);

		void					DeleteFont(const String& theName);
		Font*					LoadFont(const String& theName);

		SharedImageRef			GetImage(const String& theId);
		int						GetSound(const String& theId);
		Font*					GetFont(const String& theId);

		// Returns all the XML attributes associated with the image
		const XMLParamMap&		GetImageAttributes(const String& theId);

		// These throw a ResourceManagerException if the resource is not found
		virtual SharedImageRef	GetImageThrow(const String& theId);
		virtual int				GetSoundThrow(const String& theId);
		virtual Font*			GetFontThrow(const String& theId);

		void					SetAllowMissingProgramImages(bool allow);

		virtual void			DeleteResources(const String& theGroup);
		void					DeleteExtraImageBuffers(const String& theGroup);

		const ResList*			GetCurResGroupList() { return mCurResGroupList; }
		String					GetCurResGroup() { return mCurResGroup; }
		void					DumpCurResGroup(String& theDestStr);
	};

	static_assert(sizeof(ResourceManager) == 0xcc);

	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	struct ResourceManagerException : public std::exception
	{
		String what;
		ResourceManagerException(const String& theWhat) : what(theWhat) { }
	};
}

#endif // !_PVZMOD_RESOURCE_MANAGER_H_
