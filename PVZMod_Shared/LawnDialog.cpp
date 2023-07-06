#include "LawnDialog.h"
#include "Image.h"
#include "GameButton.h"
#include "LawnApp.h"
#include "Res.h"
#include "TodStringFile.h"
#include "Font.h"
#include "Graphics.h"
#include "EffectSystem.h"
#include "Reanimator.h"

using namespace PVZMod;

void LawnDialog::CalcSize(int theExtraX, int theExtraY)
{
	// 根据边距计算一个最小宽度
	int aWidth = mBackgroundInsets.mLeft + mBackgroundInsets.mRight + mContentInsets.mLeft + mContentInsets.mRight + theExtraX;
	// 最小宽度需要额外考虑到标题字符串的宽度
	if (mDialogHeader.size() > 0) aWidth += mHeaderFont->StringWidth(mDialogHeader);
	// 对话框贴图的最小宽度
	int aTopMidWidth = IMAGE_DIALOG_TOPMIDDLE->mWidth;
	int aImageWidth = IMAGE_DIALOG_TOPLEFT->mWidth + IMAGE_DIALOG_TOPRIGHT->mWidth + aTopMidWidth;
	// 计算最终的宽度
	if (aWidth <= aImageWidth)
	{
		aWidth = aImageWidth;
	}
	else if (aTopMidWidth > 0)
	{
		int anExtraWidth = (aWidth - aImageWidth) % aTopMidWidth;
		if (anExtraWidth)
		{
			aWidth += aTopMidWidth - anExtraWidth;
		}
	}

	// 根据边距计算一个最小高度
	int aHeight = mBackgroundInsets.mTop + mBackgroundInsets.mBottom + mContentInsets.mTop + mContentInsets.mBottom + theExtraY + DIALOG_HEADER_OFFSET;
	// 额外考虑到标题字符串的高度
	if (mDialogHeader.size() > 0)
	{
		aHeight += -mHeaderFont->GetAscentPadding() + mHeaderFont->GetHeight() + mSpaceAfterHeader;
	}
	// 对话框宽度和高度额外考虑正文文本
	if (mDialogLines.size() > 0)
	{
		aWidth += aTopMidWidth;
		Graphics g;
		g.SetFont(mLinesFont);
		int aBasicWidth = aWidth - mBackgroundInsets.mLeft - mBackgroundInsets.mRight - mContentInsets.mLeft - mContentInsets.mRight - 4;
		aHeight += GetWordWrappedHeight(&g, aBasicWidth, mDialogLines, mLinesFont->GetLineSpacing() + mLineSpacingOffset) + 30;
	}
	aHeight += mButtonHeight;
	// 对话框贴图的最小高度
	int aBottomHeight = (mTallBottom ? IMAGE_DIALOG_BIGBOTTOMLEFT : IMAGE_DIALOG_BOTTOMLEFT)->mHeight;
	int aImageHeight = IMAGE_DIALOG_TOPLEFT->mHeight + aBottomHeight + DIALOG_HEADER_OFFSET;
	// 计算最终的高度
	if (aHeight < aImageHeight)
	{
		aHeight = aImageHeight;
	}
	else
	{
		int aCenterHeight = IMAGE_DIALOG_CENTERLEFT->mHeight;
		int anExtraHeight = (aHeight - aImageHeight) % aCenterHeight;
		if (anExtraHeight) aHeight += aCenterHeight - anExtraHeight;
	}

	Resize(mX, mY, aWidth, aHeight);
}

LawnDialog::LawnDialog(LawnApp* theApp,
	int theId,
	int isModal,
	const SexyString& theDialogHeader,
	const SexyString& theDialogLines,
	const SexyString& theDialogFooter,
	int theButtonMode)
	:Dialog(nullptr, nullptr, theId, isModal, theDialogHeader, theDialogLines, _S(""), BUTTONS_NONE)
{
	mApp = theApp;
	mButtonDelay = -1;
	mReanimation = new ReanimationWidget();
	mReanimation->mLawnDialog = this;
	mDrawStandardBack = true;
	mTallBottom = false;
	mVerticalCenterText = true;
	mDialogHeader = TodStringTranslate(theDialogHeader);
	mDialogLines = TodStringTranslate(theDialogLines);
	SetColor(0, { 0xE0,0xBB,0x62 });
	SetColor(1, { 0xE0,0xBB,0x62 });
	SetHeaderFont(FONT_DWARVENTODCRAFT24);
	SetLinesFont(FONT_DWARVENTODCRAFT15);
	mContentInsets = Insets(36, 35, 46, 36);

	if (theButtonMode == 1)
	{
		mLawnYesButton = MakeButton(1000, this, _S("[BUTTON_YES]"));
		mLawnNoButton = MakeButton(1001, this, _S("[BUTTON_NO]"));
	}
	else if (theButtonMode == 2)
	{
		mLawnYesButton = MakeButton(1000, this, _S("[BUTTON_OK]"));
		mLawnNoButton = MakeButton(1001, this, _S("[BUTTON_CANCEL]"));
	}
	else if (theButtonMode == 3)
	{
		mLawnYesButton = MakeButton(1000, this, theDialogFooter);
		mLawnNoButton = nullptr;
	}
	else
	{
		mLawnYesButton = nullptr;
		mLawnNoButton = nullptr;
	}

	mApp->SetCursor(CURSOR_POINTER);
	CalcSize(0, 0);
}

LawnDialog::~LawnDialog()
{
	delete mReanimation;
	delete mLawnYesButton;
	delete mLawnNoButton;
}

void LawnDialog::AddedToManager(WidgetManager* theWidgetManager)
{
	Dialog::AddedToManager(theWidgetManager);
	AddWidget(mReanimation);
	if (mLawnYesButton)
		AddWidget(mLawnYesButton);
	if (mLawnNoButton)
		AddWidget(mLawnNoButton);
}

void LawnDialog::RemovedFromManager(WidgetManager* theWidgetManager)
{
	Dialog::RemovedFromManager(theWidgetManager);
	if (mLawnYesButton)
		RemoveWidget(mLawnYesButton);
	if (mLawnNoButton)
		RemoveWidget(mLawnNoButton);
	RemoveWidget(mReanimation);

	if (mReanimation->mReanim)
	{
		mApp->mEffectSystem->mReanimationHolder->mReanimations.DataArrayFree(mReanimation->mReanim);
		mReanimation->mReanim = nullptr;
	}
}

void LawnDialog::Resize(int theX, int theY, int theWidth, int theHeight)
{
	int func = 0x45a760;
	__asm
	{
		push theHeight
		push theWidth
		push theY
		push theX
		mov ecx, this
		call func
	}
}

void LawnDialog::Draw(Graphics* g)
{
	int func = 0x45a940;
	__asm
	{
		push g
		mov ecx, this
		call func
	}
}

void LawnDialog::Update()
{
	Dialog::Update();
	if (mUpdateCnt == mButtonDelay)
	{
		if (mLawnYesButton)
		{
			mLawnYesButton->SetDisabled(false);
		}
		if (mLawnNoButton)
		{
			mLawnNoButton->SetDisabled(false);
		}
	}
	MarkDirty();
}

int LawnDialog::WriteWordWrapped(Graphics* g, const Rect& theRect, const SexyString& theLine, int theLineSpacing, int theJustification)
{
	int func = 0x53e4d0;
	int result;
	__asm
	{
		push theJustification
		push theLineSpacing
		push theLine
		push theRect
		push g
		mov ecx, this
		call func
		mov result, eax
	}
	return result;
}

int LawnDialog::GetWordWrappedHeight(Graphics* g, int theWidth, const SexyString& theLine, int aLineSpacing)
{
	int func = 0x53e510;
	int result;
	__asm
	{
		push aLineSpacing
		push theLine
		push theWidth
		push g
		mov ecx, this
		call func
		mov result, eax
	}
	return result;
}

void LawnDialog::SetButtonDelay(int theDelay)
{
	mButtonDelay = theDelay;
	if (mLawnYesButton)
		mLawnYesButton->SetDisabled(true);
	if (mLawnNoButton)
		mLawnNoButton->SetDisabled(true);
}

void LawnDialog::CheckboxChecked(int theId, bool cheked)
{
	int func = 0x45a6b0;
	int _cheked;
	__asm
	{
		push _cheked
		push theId
		mov ecx, this
		call func
	}
}

void LawnDialog::ButtonPress(int theId)
{
	int func = 0x45a670;
	__asm
	{
		push theId
		mov ecx, this
		call func
	}
}

void LawnDialog::ButtonDepress(int theId)
{
	int func = 0x45a690;
	__asm
	{
		push theId
		mov ecx, this
		call func
	}
}

ReanimationWidget::ReanimationWidget()
	:mPosX(0), mPosY(0), mApp(gLawnApp), mReanim(nullptr), mLawnDialog(nullptr)
{
	mMouseVisible = false;
	mClip = false;
	mHasAlpha = true;
}

ReanimationWidget::~ReanimationWidget()
{
	if (mReanim)
	{
		mApp->mEffectSystem->mReanimationHolder->mReanimations.DataArrayFree(mReanim);
		mReanim = nullptr;
	}
}

void ReanimationWidget::Draw(Graphics* g)
{
	int func = 0x45af20;
	__asm
	{
		push g
		mov ecx, this
		call func
	}
}

void ReanimationWidget::Update()
{
	int func = 0x45af40;
	__asm
	{
		mov ecx, this
		call func
	}
}
