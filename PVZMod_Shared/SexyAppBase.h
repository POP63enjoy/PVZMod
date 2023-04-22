#pragma once
#ifndef _PVZMOD_SEXY_APP_BASE_H_
#define _PVZMOD_SEXY_APP_BASE_H_

#include "SexyCommon.h"
#include "ButtonListener.h"
#include "DialogListener.h"
#include <Windows.h>
#include "Rect.h"
#include "Color.h"
#include "SharedImage.h"
#include "CritSect.h"
#include "Buffer.h"
#include "Ratio.h"

namespace PVZMod
{
	class DDImage;
	class MusicInterface;
	class Dialog;
	class Widget;
	class WidgetManager;
	class MemoryImage;
	class Image;
	class Buffer;
	class DDInterface;
	class ResourceManager;
	class SoundManager;
	class InitPatch;

	class WidgetSafeDeleteInfo
	{
	public:
		int						mUpdateAppDepth;
		Widget* mWidget;
	};

	typedef List<WidgetSafeDeleteInfo> WidgetSafeDeleteList;
	typedef Set<MemoryImage*> MemoryImageSet;
	typedef Map<int, Dialog*> DialogMap;
	typedef List<Dialog*> DialogList;
	typedef List<MSG> WindowsMessageList;
	typedef Vector<String> StringVector;
	//typedef std::basic_string<TCHAR> tstring; // string of TCHARs

	typedef Map<String, SexyString> StringSexyStringMap;
	typedef Map<String, String> StringStringMap;
	typedef Map<String, WString> StringWStringMap;
	typedef Map<String, bool> StringBoolMap;
	typedef Map<String, int> StringIntMap;
	typedef Map<String, double> StringDoubleMap;
	typedef Map<String, StringVector> StringStringVectorMap;

	typedef Map<HANDLE, int> HandleToIntMap;

	enum
	{
		CURSOR_POINTER,
		CURSOR_HAND,
		CURSOR_DRAGGING,
		CURSOR_TEXT,
		CURSOR_CIRCLE_SLASH,
		CURSOR_SIZEALL,
		CURSOR_SIZENESW,
		CURSOR_SIZENS,
		CURSOR_SIZENWSE,
		CURSOR_SIZEWE,
		CURSOR_WAIT,
		CURSOR_NONE,
		CURSOR_CUSTOM,
		NUM_CURSORS
	};

	/// 【游戏类】宝开框架主类。（原 `Sexy::SexyAppBase`）
	class SexyAppBase :public ButtonListener, public DialogListener
	{
	public:
		uint32_t					mRandSeed;

		String				mCompanyName;
		String				mFullCompanyName;
		String				mProdName;
		SexyString				mTitle;
		String				mRegKey;
		String				mChangeDirTo;

		int						mRelaxUpdateBacklogCount; // app doesn't try to catch up for this many frames
		int						mPreferredX;
		int						mPreferredY;
		int						mWidth;
		int						mHeight;
		int						mFullscreenBits;
		double					mMusicVolume;
		double					mSfxVolume;
		double					mDemoMusicVolume;
		double					mDemoSfxVolume;
		bool					mNoSoundNeeded;
		bool					mWantFMod;
		bool					mCmdLineParsed;
		bool					mSkipSignatureChecks;
		bool					mStandardWordWrap;
		bool					mbAllowExtendedChars;

		HANDLE					mMutex;
		bool					mOnlyAllowOneCopyToRun;
		UINT					mNotifyGameMessage;
		CritSect				mCritSect;
		bool					mBetaValidate;
		uint8_t					mAdd8BitMaxTable[512];
		WidgetManager* mWidgetManager;
		DialogMap				mDialogMap;
		DialogList				mDialogList;
		DWORD					mPrimaryThreadId;
		bool					mSEHOccured;
		bool					mShutdown;
		bool					mExitToTop;
		bool					mIsWindowed;
		bool					mIsPhysWindowed;
		bool					mFullScreenWindow; // uses ChangeDisplaySettings to run fullscreen with mIsWindowed true
		bool					mForceFullscreen;
		bool					mForceWindowed;
		bool					mInitialized;
		bool					mProcessInTimer;
		DWORD					mTimeLoaded;
		HWND					mHWnd;
		HWND					mInvisHWnd;
		bool					mIsScreenSaver;
		bool					mAllowMonitorPowersave;
		WindowsMessageList		mDeferredMessages;
		bool					mNoDefer;
		bool					mFullScreenPageFlip;
		bool					mTabletPC;
		DDInterface* mDDInterface;
		bool					mAlphaDisabled;
		MusicInterface* mMusicInterface;
		bool					mReadFromRegistry;
		String				mRegisterLink;
		String				mProductVersion;
		Image* mCursorImages[NUM_CURSORS];
		HCURSOR					mOverrideCursor;
		bool					mIsOpeningURL;
		bool					mShutdownOnURLOpen;
		String				mOpeningURL;
		DWORD					mOpeningURLTime;
		DWORD					mLastTimerTime;
		DWORD					mLastBigDelayTime;
		double					mUnmutedMusicVolume;
		double					mUnmutedSfxVolume;
		int						mMuteCount;
		int						mAutoMuteCount;
		bool					mDemoMute;
		bool					mMuteOnLostFocus;
		MemoryImageSet			mMemoryImageSet;
		SharedImageMap			mSharedImageMap;
		bool					mCleanupSharedImages;

		int						mNonDrawCount;
		int						mFrameTime;

		bool					mIsDrawing;
		bool					mLastDrawWasEmpty;
		bool					mHasPendingDraw;
		double					mPendingUpdatesAcc;
		double					mUpdateFTimeAcc;
		DWORD					mLastTimeCheck;
		DWORD					mLastTime;
		DWORD					mLastUserInputTick;

		int						mSleepCount;
		int						mDrawCount;
		int						mUpdateCount;
		int						mUpdateAppState;
		int						mUpdateAppDepth;
		double					mUpdateMultiplier;
		bool					mPaused;
		int						mFastForwardToUpdateNum;
		bool					mFastForwardToMarker;
		bool					mFastForwardStep;
		DWORD					mLastDrawTick;
		DWORD					mNextDrawTick;
		int						mStepMode;  // 0 = off, 1 = step, 2 = waiting for step

		int						mCursorNum;
		SoundManager* mSoundManager;
		HCURSOR					mHandCursor;
		HCURSOR					mDraggingCursor;
		WidgetSafeDeleteList	mSafeDeleteList;
		bool					mMouseIn;
		bool					mRunning;
		bool					mActive;
		bool					mMinimized;
		bool					mPhysMinimized;
		bool					mIsDisabled;
		bool					mHasFocus;
		int						mDrawTime;
		uint32_t					mFPSStartTick;
		int						mFPSFlipCount;
		int						mFPSDirtyCount;
		int						mFPSTime;
		int						mFPSCount;
		bool					mShowFPS;
		int						mShowFPSMode;
		int						mScreenBltTime;
		bool					mAutoStartLoadingThread;
		bool					mLoadingThreadStarted;
		bool					mLoadingThreadCompleted;
		bool					mLoaded;
		bool					mYieldMainThread;
		bool					mLoadingFailed;
		bool					mCursorThreadRunning;
		bool					mSysCursor;
		bool					mCustomCursorsEnabled;
		bool					mCustomCursorDirty;
		bool					mLastShutdownWasGraceful;
		bool					mIsWideWindow;
		bool mWriteToSexyCache;
		bool mSexyCacheBuffers;

		int						mNumLoadingThreadTasks;
		int						mCompletedLoadingThreadTasks;

		// For recording/playback of program control
		bool					mRecordingDemoBuffer;
		bool					mPlayingDemoBuffer;
		bool					mManualShutdown;
		String			mDemoPrefix;
		String			mDemoFileName;
		Buffer					mDemoBuffer;
		int						mDemoLength;
		int						mLastDemoMouseX;
		int						mLastDemoMouseY;
		int						mLastDemoUpdateCnt;
		bool					mDemoNeedsCommand;
		bool					mDemoIsShortCmd;
		int						mDemoCmdNum;
		int						mDemoCmdOrder;
		int						mDemoCmdBitPos;
		bool					mDemoLoadingComplete;
		HandleToIntMap			mHandleToIntMap; // For waiting on handles
		int						mCurHandleNum;

		typedef std::pair<String, int> DemoMarker;
		typedef List<DemoMarker> DemoMarkerList;
		DemoMarkerList			mDemoMarkerList;

		bool					mDebugKeysEnabled;
		bool					mEnableMaximizeButton;
		bool					mCtrlDown;
		bool					mAltDown;
		bool mAllowAltEnter;

		int						mSyncRefreshRate;
		bool					mVSyncUpdates;
		bool					mVSyncBroken;
		int						mVSyncBrokenCount;
		DWORD					mVSyncBrokenTestStartTick;
		DWORD					mVSyncBrokenTestUpdates;
		bool					mWaitForVSync;
		bool					mSoftVSyncWait;
		bool					mUserChanged3DSetting;
		bool					mAutoEnable3D;
		bool					mTest3D;
		DWORD					mMinVidMemory3D;
		DWORD					mRecommendedVidMemory3D;

		bool					mWidescreenAware;
		bool mWidescreenTranslate;
		Rect					mScreenBounds;
		bool					mEnableWindowAspect;
		Ratio					mWindowAspect;

		StringWStringMap		mStringProperties;
		StringBoolMap			mBoolProperties;
		StringIntMap			mIntProperties;
		StringDoubleMap			mDoubleProperties;
		StringStringVectorMap	mStringVectorProperties;
		ResourceManager* mResourceManager;
		LONG					mOldWndProc;
#ifdef PVZMOD_SEXYAPP_ALL_PUBLIC
	public:
#else
	protected:	
#endif
		void					RehupFocus();
		void					ClearKeysDown();
		bool					ProcessDeferredMessages(bool singleMessage);
		void					UpdateFTimeAcc();
		virtual bool			Process(bool allowSleep = true);		
		virtual void			UpdateFrames();
		virtual bool			DoUpdateFrames();
		virtual void			DoUpdateFramesF(float theFrac);
		virtual void			MakeWindow();
		virtual void			EnforceCursor();
		virtual void			ReInitImages();
		virtual void			DeleteNativeImageData();	
		virtual void			DeleteExtraImageData();
	
		// Loading thread methods	
		virtual void			LoadingThreadCompleted();
		static void				LoadingThreadProcStub(void *theArg);	

		// Cursor thread methods
		void					CursorThreadProc();
		static void				CursorThreadProcStub(void *theArg);
		void					StartCursorThread();
	
		void					WaitForLoadingThread();				
		void					ProcessSafeDeleteList();	
		void					RestoreScreenResolution();
		void					DoExit(int theCode);

		void					TakeScreenshot();
		void					DumpProgramInfo();	
		void					ShowMemoryUsage();			

		// Registry helpers
		bool					RegistryRead(const String& theValueName, uint32_t* theType, uint8_t* theValue, uint32_t* theLength);
		bool					RegistryReadKey(const String& theValueName, uint32_t* theType, uint8_t* theValue, uint32_t* theLength, HKEY theMainKey = HKEY_CURRENT_USER);
		bool					RegistryWrite(const String& theValueName, uint32_t theType, const uint8_t* theValue, uint32_t theLength);

		// Demo recording helpers	
		void					ProcessDemo();
	public:
		SexyAppBase();
		virtual ~SexyAppBase();

		// Common overrides:
		virtual MusicInterface*	CreateMusicInterface(HWND theHWnd);
		virtual void			InitHook();
		virtual void			ShutdownHook();	
		virtual void			PreTerminate();
		virtual void			LoadingThreadProc();
		virtual void			WriteToRegistry();
		virtual void			ReadFromRegistry();
		virtual Dialog*			NewDialog(int theDialogId, bool isModal, const SexyString& theDialogHeader, const SexyString& theDialogLines, const SexyString& theDialogFooter, int theButtonMode);		
		virtual void			PreDisplayHook();

		// Public methods
		virtual void			BeginPopup();
		virtual void			EndPopup();
		virtual int				MsgBox(const String &theText, const String &theTitle = "Message", int theFlags = MB_OK);
		virtual int				MsgBox(const WString &theText, const WString &theTitle = L"Message", int theFlags = MB_OK);
		virtual void			Popup(const String& theString);
		virtual void			Popup(const WString& theString);
		virtual void			LogScreenSaverError(const String &theError);
		virtual void			SafeDeleteWidget(Widget* theWidget);	

		virtual void			URLOpenFailed(const String& theURL);
		virtual void			URLOpenSucceeded(const String& theURL);
		virtual bool			OpenURL(const String& theURL, bool shutdownOnOpen = false);	
		virtual String			GetProductVersion(const String& thePath);	

		virtual void			SEHOccured();
		virtual String			GetGameSEHInfo();
		virtual void			GetSEHWebParams(DefinesMap* theDefinesMap);
		virtual void			Shutdown();	

		virtual void			DoParseCmdLine();
		virtual void			ParseCmdLine(const String& theCmdLine);
		virtual void			HandleCmdLineParam(const String& theParamName, const String& theParamValue);
		virtual void			HandleNotifyGameMessage(int theType, int theParam); // for HWND_BROADCAST of mNotifyGameMessage (0-1000 are reserved for SexyAppBase for theType)
		virtual void			HandleGameAlreadyRunning(); 

		virtual void			Start();	
		virtual void			Init();	
		virtual void			PreDDInterfaceInitHook();
		virtual void			PostDDInterfaceInitHook();
		virtual bool			ChangeDirHook(const char *theIntendedPath);
		virtual void			PlaySample(int theSoundNum);
		virtual void			PlaySample(int theSoundNum, int thePan);

		virtual double			GetMasterVolume();
		virtual double			GetMusicVolume();
		virtual double			GetSfxVolume();
		virtual bool			IsMuted();

		virtual void			SetMasterVolume(double theVolume);
		virtual void			SetMusicVolume(double theVolume);
		virtual void			SetSfxVolume(double theVolume);	
		virtual void			Mute(bool autoMute = false);
		virtual void			Unmute(bool autoMute = false);

		void					StartLoadingThread();
		virtual double			GetLoadingThreadProgress();	

		void					CopyToClipboard(const String& theString);
		String					GetClipboard();

		void					SetCursor(int theCursorNum);
		int						GetCursor();
		void					EnableCustomCursors(bool enabled);	
		virtual DDImage*		GetImage(const String& theFileName, bool commitBits = true);	
		virtual SharedImageRef	SetSharedImage(const String&, const String&, DDImage*, bool*);
		virtual SharedImageRef	GetSharedImage(const String& theFileName, const String& theVariant = "", bool* isNew = nullptr);

		void					CleanSharedImages();
		void					PrecacheAdditive(MemoryImage* theImage);
		void					PrecacheAlpha(MemoryImage* theImage);
		void					PrecacheNative(MemoryImage* theImage);
		void					SetCursorImage(int theCursorNum, Image* theImage);

		DDImage*				CreateCrossfadeImage(Image* theImage1, const Rect& theRect1, Image* theImage2, const Rect& theRect2, double theFadeFactor);
		void					ColorizeImage(Image* theImage, const Color& theColor);
		DDImage*				CreateColorizedImage(Image* theImage, const Color& theColor);
		DDImage*				CopyImage(Image* theImage, const Rect& theRect);
		DDImage*				CopyImage(Image* theImage);
		void					MirrorImage(Image* theImage);
		void					FlipImage(Image* theImage);
		void					RotateImageHue(MemoryImage *theImage, int theDelta);
		uint32_t				HSLToRGB(int h, int s, int l);
		uint32_t				RGBToHSL(int r, int g, int b);
		void					HSLToRGB(const uint32_t* theSource, uint32_t* theDest, int theSize);
		void					RGBToHSL(const uint32_t* theSource, uint32_t* theDest, int theSize);

		void					AddMemoryImage(MemoryImage* theMemoryImage);
		void					RemoveMemoryImage(MemoryImage* theMemoryImage);
		void					Remove3DData(MemoryImage* theMemoryImage);
		virtual void			SwitchScreenMode();
		virtual void			SwitchScreenMode(bool wantWindowed);
		virtual void			SwitchScreenMode(bool wantWindowed, bool is3d, bool force = false);
		virtual void			SetAlphaDisabled(bool isDisabled);
	
		virtual Dialog*			DoDialog(int theDialogId, bool isModal, const SexyString& theDialogHeader, const SexyString& theDialogLines, const SexyString& theDialogFooter, int theButtonMode);
		virtual Dialog*			GetDialog(int theDialogId);
		virtual void			AddDialog(int theDialogId, Dialog* theDialog);
		virtual void			AddDialog(Dialog* theDialog);
		virtual bool			KillDialog(int theDialogId, bool removeWidget, bool deleteWidget);
		virtual bool			KillDialog(int theDialogId);
		virtual bool			KillDialog(Dialog* theDialog);
		virtual int				GetDialogCount();
		virtual void			ModalOpen();
		virtual void			ModalClose();	
		virtual void			DialogButtonPress(int theDialogId, int theButtonId);
		virtual void			DialogButtonDepress(int theDialogId, int theButtonId);

		virtual void			GotFocus();
		virtual void			LostFocus();	
		virtual bool			IsAltKeyUsed(WPARAM wParam);
		virtual bool			DebugKeyDown(int theKey);	
		virtual bool			DebugKeyDownAsync(int theKey, bool ctrlDown, bool altDown);
		virtual void			CloseRequestAsync();
		bool					Is3DAccelerated();
		bool					Is3DAccelerationSupported();
		bool					Is3DAccelerationRecommended();
		void					DemoSyncRefreshRate();
		void					Set3DAcclerated(bool is3D, bool reinit = true);
		virtual void			Done3dTesting();
		virtual String			NotifyCrashHook(); // return file name that you want to upload
	
		virtual bool			CheckSignature(const Buffer& theBuffer, const String& theFileName);
		virtual bool			DrawDirtyStuff();
		virtual void			Redraw(Rect* theClipRect);

		// Properties access methods
		bool					LoadProperties(const String& theFileName, bool required, bool checkSig);
		bool					LoadProperties();
		virtual void			InitPropertiesHook();

		// Resource access methods
		void					LoadResourceManifest();
		void					ShowResourceError(bool doExit = false);
	
		bool					GetBoolean(const String& theId);
		bool					GetBoolean(const String& theId, bool theDefault);	
		int						GetInteger(const String& theId);
		int						GetInteger(const String& theId, int theDefault);
		double					GetDouble(const String& theId);
		double					GetDouble(const String& theId, double theDefault);
		SexyString				GetString(const String& theId);
		SexyString				GetString(const String& theId, const SexyString& theDefault);

		StringVector			GetStringVector(const String& theId);

		void					SetBoolean(const String& theId, bool theValue);
		void					SetInteger(const String& theId, int theValue);
		void					SetDouble(const String& theId, double theValue);
		void					SetString(const String& theId, const WString& theValue);
	
		// Demo access methods
		bool					PrepareDemoCommand(bool required);
		void					WriteDemoTimingBlock();
		void					WriteDemoBuffer();
		bool					ReadDemoBuffer(String &theError);//UNICODE
		void					DemoSyncBuffer(Buffer* theBuffer);
		void					DemoSyncString(String* theString);
		void					DemoSyncInt(int* theInt);
		void					DemoSyncBool(bool* theBool);
		void					DemoAssertStringEqual(const String& theString);
		void					DemoAssertIntEqual(int theInt);
		void					DemoAddMarker(const String& theString);
		void					DemoRegisterHandle(HANDLE theHandle);
		void					DemoWaitForHandle(HANDLE theHandle);
		bool					DemoCheckHandle(HANDLE theHandle);
	

		// Registry access methods
		bool					RegistryGetSubKeys(const String& theKeyName, StringVector* theSubKeys);
		bool					RegistryReadString(const String& theValueName, String* theString);
		bool					RegistryReadInteger(const String& theValueName, int* theValue);
		bool					RegistryReadBoolean(const String& theValueName, bool* theValue);
		bool					RegistryReadData(const String& theValueName, uint8_t* theValue, uint32_t* theLength);
		bool					RegistryWriteString(const String& theValueName, const String& theString);
		bool					RegistryWriteInteger(const String& theValueName, int theValue);
		bool					RegistryWriteBoolean(const String& theValueName, bool theValue);
		bool					RegistryWriteData(const String& theValueName, const uint8_t* theValue, uint32_t theLength);
		bool					RegistryEraseKey(const SexyString& theKeyName);
		void					RegistryEraseValue(const SexyString& theValueName);

		// File access methods
		bool					WriteBufferToFile(const String& theFileName, const Buffer* theBuffer);
		bool					ReadBufferFromFile(const String& theFileName, Buffer* theBuffer, bool dontWriteToDemo = false);//UNICODE
		bool					WriteBytesToFile(const String& theFileName, const void *theData, unsigned long theDataLen);
		bool					FileExists(const String& theFileName);
		bool					EraseFile(const String& theFileName);

		// Misc methods
		virtual void			DoMainLoop();
		virtual bool			UpdateAppStep(bool* updated);
		virtual bool			UpdateApp();
		int						InitDDInterface();
		void					ClearUpdateBacklog(bool relaxForASecond = false);
		bool					IsScreenSaver();
		virtual bool			AppCanRestore();
		virtual bool			OverrideWindowProc(HWND, unsigned int, unsigned int, int, int*);
		static LRESULT CALLBACK	WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	public:	// 新增函数
		void ReinitDDInterface();
		void KeepAspectRatioFullClient(int theClientWidth, int theClientHeight);
		LRESULT WindowSizingKeepAspectRatio(HWND hwnd, WPARAM wParam, LPARAM lParam);
	};

	static_assert(sizeof(SexyAppBase) == 0x640);

	/// 【游戏变量】全局 SexyAppBase 指针。
	extern SexyAppBase*& gSexyAppBase;
}

#endif // !_PVZMOD_SEXY_APP_BASE_H_
