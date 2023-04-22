#pragma once
#ifndef _PVZMOD_SEXY_APP_H_
#define _PVZMOD_SEXY_APP_H_

#include "SexyAppBase.h"

namespace PVZMod
{
	class InternetManager;
	class BetaSupport;

	/// 【游戏类】宝开私有程序主类。（原 `Sexy::SexyApp`）
	class SexyApp : public SexyAppBase
	{
	public:
		InternetManager*		mInternetManager;
		BetaSupport*			mBetaSupport;

		String					mBetaSupportSiteOverride;
		String					mBetaSupportProdNameOverride;
		String					mReferId;
		String					mVariation;
		uint32_t				mDownloadId;
		String					mRegSource;
		uint32_t				mLastVerCheckQueryTime;
		bool					mSkipAd;
		bool					mDontUpdate;

		int						mBuildNum;
		String					mBuildDate;

		String					mUserName;
		String					mRegUserName;
		String					mRegCode;
		bool					mIsRegistered;
		bool					mBuildUnlocked;

		int						mTimesPlayed;
		int						mTimesExecuted;
		bool					mTimedOut;

	public:
		virtual void			UpdateFrames();

		virtual void			WriteToRegistry();
		virtual void			ReadFromRegistry();

		virtual bool			CheckSignature(const Buffer& theBuffer, const String& theFileName);

		virtual bool			ShouldCheckForUpdate();
		virtual void			UpdateCheckQueried();

		virtual void			URLOpenSucceeded(const String& theURL);

	public:
		SexyApp();
		virtual ~SexyApp();

		bool					Validate(const String& theUserName, const String& theRegCode);

		virtual bool			OpenRegisterPage(DefinesMap theDefinesMap);
		virtual bool			OpenRegisterPage();

		virtual void			PreDisplayHook();
		virtual void			InitPropertiesHook();
		virtual void			Init();
		virtual void			PreTerminate();

		virtual bool			OpenHTMLTemplate(const String& theTemplateFile, const DefinesMap& theDefinesMap);
		virtual void			OpenUpdateURL();

		virtual void			HandleCmdLineParam(const String& theParamName, const String& theParamValue);
		virtual String			GetGameSEHInfo();
		virtual void			GetSEHWebParams(DefinesMap* theDefinesMap);

		virtual void			HandleNotifyGameMessageCommandLine(const WString&);
	};

	static_assert(sizeof(SexyApp) == 0x768);
}

#endif // !_PVZMOD_SEXY_APP_H_
