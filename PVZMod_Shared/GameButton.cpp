#include "GameButton.h"
#include "TodStringFile.h"
#include "Image.h"
#include "Res.h"
#include "LawnApp.h"
#include "Board.h"

using namespace PVZMod;

LawnStoneButton::LawnStoneButton(Image* theComponentImage, int theId, ButtonListener* theListener)
	:DialogButton(nullptr, theId, theListener)
{
}

void LawnStoneButton::Draw(Graphics* g)
{
	bool v2; // al

	if (!this->mBtnNoDraw)
	{
		v2 = this->mIsDown && this->mIsOver && !this->mDisabled;
		DrawStoneButton(g, 0, 0, this->mWidth, this->mHeight, v2 != this->mInverted, this->mIsOver, this->mLabel);
	}
}

void LawnStoneButton::SetLabel(const SexyString& theLabel)
{
	mLabel = TodStringTranslate(theLabel);
}

LawnStoneButton* (*PVZMod::MakeButton)(int theId, ButtonListener* theListener, const SexyString& theText) = (decltype(MakeButton))0x44A9B0;

void PVZMod::DrawStoneButton(Graphics* g, int x, int y, int theWidth, int theHeight, bool isDown, bool isHighLighted, const SexyString& theLabel)
{
	int func = 0x449DD0;
	int _isHighLighted = isHighLighted, _isDown = isDown;
	__asm
	{
		push theLabel
		push _isHighLighted
		push _isDown
		push theHeight
		push theWidth
		push y
		mov eax, x
		push g
		call func
		add esp, 0x1c
	}
}

NewLawnButton::NewLawnButton(Image* theComponentImage, int theId, ButtonListener* theListener)
	:DialogButton(theComponentImage,theId,theListener)
{
	mHiliteFont = nullptr;
	mTextDownOffsetX = 0;
	mTextDownOffsetY = 0;
	mButtonOffsetX = 0;
	mButtonOffsetY = 0;
	mUsePolygonShape = false;
	SetColor(5, Color::White);
}

void NewLawnButton::Draw(Graphics* g)
{
	int func = 0x44ab00;
	__asm
	{
		push g
		mov ecx, this
		call func
	}
}

bool NewLawnButton::IsPointVisible(int x, int y)
{
	int func = 0x44aee0;
	bool result;
	__asm
	{
		push y
		push x
		mov ecx, this
		call func
		mov result, al
	}
	return result;
}

void NewLawnButton::SetLabel(const SexyString& theLabel)
{
	mLabel = TodStringTranslate(theLabel);
}

NewLawnButton* PVZMod::MakeNewButton(int theId, ButtonListener* theListener, const SexyString& theText, Font* theFont, Image* theImageNormal, Image* theImageOver, Image* theImageDown)
{
	NewLawnButton* button = new NewLawnButton(nullptr, theId, theListener);
	button->SetFont(theFont ? theFont : FONT_BRIANNETOD12);
	button->SetLabel(theText);
	button->mWidth = theImageNormal->mWidth;
	button->mHeight = theImageNormal->mHeight;
	button->mButtonImage = theImageNormal;
	button->mDownImage = theImageDown;
	button->mOverImage = theImageOver;
	button->mHasAlpha = 1;
	button->mHasTransparencies = 1;
	button->mTranslateX = 1;
	button->mTranslateY = 1;
	return button;
}

