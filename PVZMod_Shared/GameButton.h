#pragma once
#ifndef _PVZMOD_GAME_BUTTON_H_
#define _PVZMOD_GAME_BUTTON_H_

#include "DialogButton.h"
#include "SexyVector.h"

namespace PVZMod
{
	class LawnApp;

	/// 【游戏类】游戏按钮。（原 `::%GameButton`）
	class GameButton
	{
	public:
		LawnApp*			mApp;
		Widget*				mParentWidget;
		int					mX;
		int					mY;
		int					mWidth;
		int					mHeight;
		bool				mIsOver;
		bool				mIsDown;
		bool				mDisabled;
		Color				mColors[6];
		int					mId;
		SexyString			mLabel;
		int					mLabelJustify;
		Font*				mFont;
		Image*				mButtonImage;
		Image*				mOverImage;
		Image*				mDownImage;
		Image*				mDisabledImage;
		Image*				mOverOverlayImage;
		Rect				mNormalRect;
		Rect				mOverRect;
		Rect				mDownRect;
		Rect				mDisabledRect;
		bool				mInverted;
		bool				mBtnNoDraw;
		bool				mFrameNoDraw;
		double				mOverAlpha;
		double				mOverAlphaSpeed;
		double				mOverAlphaFadeInSpeed;
		bool				mDrawStoneButton;
		int					mTextOffsetX;
		int					mTextOffsetY;
		int					mButtonOffsetX;
		int					mButtonOffsetY;

	public:
		GameButton();
		virtual ~GameButton();

		virtual void	DrawButtonImage(Graphics* g, Image* theImage, const Rect& theRect, int x, int y);
		virtual void	SetFont(Font* theFont);
		virtual void	Resize(int theX, int theY, int theWidth, int theHeight);
		virtual void	SetLabel(const SexyString& theLabel);
	};
	
	static_assert(sizeof(GameButton) == 0x138);

	class LawnStoneButton :public DialogButton
	{
	public:
		LawnStoneButton(Image* theComponentImage, int theId, ButtonListener* theListener);

		virtual void	Draw(Graphics* g);
		void			SetLabel(const SexyString& theLabel);
	};

	extern LawnStoneButton* (*MakeButton)(int theId, ButtonListener* theListener, const SexyString& theText);
	void DrawStoneButton(Graphics* g, int x, int y, int theWidth, int theHeight, bool isDown, bool isHighLighted, const SexyString& theLabel);

	class NewLawnButton :public DialogButton
	{
	public:
		Font*			mHiliteFont;
		int				mTextDownOffsetX;
		int				mTextDownOffsetY;
		int				mButtonOffsetX;
		int				mButtonOffsetY;
		bool			mUsePolygonShape;
		SexyVector2		mPolygonShape[4];

		int unknown1, unknown2;

	public:
		NewLawnButton(Image* theComponentImage, int theId, ButtonListener* theListener);

		virtual void	Draw(Graphics* g);
		virtual bool	IsPointVisible(int x, int y);
		void			SetLabel(const SexyString& theLabel);
	};

	NewLawnButton* MakeNewButton(int theId, ButtonListener* theListener, const SexyString& theText, Font* theFont, Image* theImageNormal, Image* theImageOver, Image* theImageDown);
}

#endif // !_PVZMOD_GAME_BUTTON_H_
