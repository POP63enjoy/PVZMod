#pragma once
#ifndef _PVZMOD_LAWN_DIALOG_H_
#define _PVZMOD_LAWN_DIALOG_H_

#include "Dialog.h"

namespace PVZMod
{
	class LawnApp;
	class ReanimationWidget;
	class LawnStoneButton;

	constexpr int DIALOG_HEADER_OFFSET = 45;

	/// 【游戏类】石头对话框。（原 ::LawnDialog）
	class LawnDialog :public Dialog
	{
	public:
		LawnApp*				mApp;
		int						mButtonDelay;
		ReanimationWidget*		mReanimation;
		bool					mDrawStandardBack;
		LawnStoneButton*		mLawnYesButton;
		LawnStoneButton*		mLawnNoButton;
		bool					mTallBottom;
		bool					mVerticalCenterText;

	public:
		int GetLeft()
		{
			return mContentInsets.mLeft + mBackgroundInsets.mLeft;
		}

		int GetWidth()
		{
			return mWidth - mContentInsets.mLeft - mContentInsets.mRight - mBackgroundInsets.mLeft - mBackgroundInsets.mRight;
		}

		int GetTop()
		{
			return mContentInsets.mTop + mBackgroundInsets.mTop + 99;
		}

		void CalcSize(int theExtraX, int theExtraY);
		void CalcSize(int theExtraX, int theExtraY, int theMinWidth);

		LawnDialog(LawnApp* theApp,
			int theId,
			int isModal,
			const SexyString& theDialogHeader,
			const SexyString& theDialogLines,
			const SexyString& theDialogFooter,
			int theButtonMode);
		virtual ~LawnDialog();

		virtual void			AddedToManager(WidgetManager* theWidgetManager);
		virtual void			RemovedFromManager(WidgetManager* theWidgetManager);
		virtual void			Resize(int theX, int theY, int theWidth, int theHeight);
		virtual void			Draw(Graphics* g);
		virtual void			Update();
		virtual int				WriteWordWrapped(Graphics* g, const Rect& theRect, const SexyString& theLine, int theLineSpacing, int theJustification);
		virtual int				GetWordWrappedHeight(Graphics* g, int theWidth, const SexyString& theLine, int aLineSpacing);
		virtual void			SetButtonDelay(int theDelay);
		virtual void			CheckboxChecked(int theId, bool cheked);
		virtual void			ButtonPress(int theId);
		virtual void			ButtonDepress(int theId);
	};

	class Reanimation;
	enum ReanimationType;

	class ReanimationWidget :public Widget
	{
	public:
		LawnApp*		mApp;
		Reanimation*	mReanim;
		LawnDialog*		mLawnDialog;
		float			mPosX;
		float			mPosY;

	public:
		ReanimationWidget();
		virtual ~ReanimationWidget();

		virtual void	Draw(Graphics* g);
		virtual void	Update();
		void			AddReanimation(float x, float y, ReanimationType theReanimationType);
	};
}

#endif // !_PVZMOD_LAWN_DIALOG_H_
