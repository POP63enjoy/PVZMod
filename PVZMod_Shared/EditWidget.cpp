#include "EditWidget.h"
#include "SysFont.h"
#include "WidgetManager.h"
#include "SexyAppBase.h"
#include "EditListener.h"
#include "Graphics.h"

using namespace PVZMod;

static int gEditWidgetColors[][3] =
{ {255, 255, 255},
{0, 0, 0},
{0, 0, 0},
{0, 0, 0},
{255, 255, 255} };

EditWidget::EditWidget(int theId, EditListener* theEditListener)
{
	mId = theId;
	mEditListener = theEditListener;
	mFont = NULL;

	mHadDoubleClick = false;
	mHilitePos = -1;
	mLastModifyIdx = -1;
	mLeftPos = 0;
	mUndoCursor = 0;
	mUndoHilitePos = 0;
	mLastModifyIdx = 0;
	mBlinkAcc = 0;
	mCursorPos = 0;
	mShowingCursor = false;
	mDrawSelOverride = false;
	mMaxChars = -1;
	mMaxPixels = -1;
	mPasswordChar = 0;
	mBlinkDelay = 40;

	SetColors(gEditWidgetColors, NUM_COLORS);
}

EditWidget::~EditWidget()
{
	delete mFont;
	ClearWidthCheckFonts();

}

void EditWidget::ClearWidthCheckFonts()
{
	for (WidthCheckList::iterator anItr = mWidthCheckList.begin(); anItr != mWidthCheckList.end(); ++anItr)
		delete anItr->mFont;

	mWidthCheckList.clear();
}

void EditWidget::AddWidthCheckFont(Font* theFont, int theMaxPixels)
{
	mWidthCheckList.push_back(WidthCheck());
	WidthCheck& aCheck = mWidthCheckList.back();
	aCheck.mWidth = theMaxPixels;
	aCheck.mFont = theFont->Duplicate();
}

void EditWidget::SetText(const SexyString& theText, bool leftPosToZero)
{
	mString = theText;
	mCursorPos = mString.length();
	mHilitePos = 0;
	if (leftPosToZero)
		mLeftPos = 0;
	else
		FocusCursor(true);

	MarkDirty();
}

SexyString& EditWidget::GetDisplayString()
{
	if (mPasswordChar == 0)
		return mString;

	if (mPasswordDisplayString.size() != mString.size())
	{
		mPasswordDisplayString = SexyString(mString.size(), mPasswordChar);
		//mPasswordDisplayString.resize(mString.size());
		//for (int i=0; i<(int)mPasswordDisplayString.length(); i++)
		//	mPasswordDisplayString[i] = mPasswordChar; 
	}

	return mPasswordDisplayString;
}

bool EditWidget::WantsFocus()
{
	return true;
}

void EditWidget::Resize(int theX, int theY, int theWidth, int theHeight)
{
	Widget::Resize(theX, theY, theWidth, theHeight);

	FocusCursor(false);
}

void EditWidget::SetFont(Font* theFont, Font* theWidthCheckFont)
{
	delete mFont;
	mFont = theFont->Duplicate();

	ClearWidthCheckFonts();
	if (theWidthCheckFont != NULL)
		AddWidthCheckFont(theWidthCheckFont);
}

void EditWidget::Draw(Graphics* g) // Already translated
{
	if (mFont == NULL)
		mFont = new SysFont(mWidgetManager->mApp, "Arial Unicode MS", 10, false);

	SexyString& aString = GetDisplayString();

	g->SetColor(mColors[COLOR_BKG]);
	g->FillRect(0, 0, mWidth, mHeight);

	for (int i = 0; i < 2; i++)
	{
		Graphics* aClipG = g->Create();
		aClipG->SetFont(mFont);

		if (i == 1)
		{
			int aCursorX = mFont->StringWidth(aString.substr(0, mCursorPos)) - mFont->StringWidth(aString.substr(0, mLeftPos));
			int aHiliteX = aCursorX + 2;
			if ((mHilitePos != -1) && (mCursorPos != mHilitePos))
				aHiliteX = mFont->StringWidth(aString.substr(0, mHilitePos)) - mFont->StringWidth(aString.substr(0, mLeftPos));

			if (!mShowingCursor)
				aCursorX += 2;

			aCursorX = min(max(0, aCursorX), mWidth - 8);
			aHiliteX = min(max(0, aHiliteX), mWidth - 8);

			aClipG->ClipRect(4 + min(aCursorX, aHiliteX), (mHeight - mFont->GetHeight()) / 2, abs(aHiliteX - aCursorX), mFont->GetHeight());
		}
		else
			aClipG->ClipRect(4, 0, mWidth - 8, mHeight);

		bool hasfocus = mHasFocus || mDrawSelOverride;
		if (i == 1 && hasfocus)
		{
			aClipG->SetColor(mColors[COLOR_HILITE]);
			aClipG->FillRect(0, 0, mWidth, mHeight);
		}

		if (i == 0 || !hasfocus)
			aClipG->SetColor(mColors[COLOR_TEXT]);
		else
			aClipG->SetColor(mColors[COLOR_HILITE_TEXT]);
		aClipG->DrawString(aString.substr(mLeftPos), 4, (mHeight - mFont->GetHeight()) / 2 + mFont->GetAscent());

		delete aClipG;
	}

	g->SetColor(mColors[COLOR_OUTLINE]);
	g->DrawRect(0, 0, mWidth - 1, mHeight - 1);
}

void EditWidget::UpdateCaretPos()
{
	SexyAppBase* anApp = mWidgetManager->mApp;

	Point aPoint = GetAbsPos();

	if (aPoint.mX < 10) aPoint.mX = 10;
	else if (aPoint.mX > anApp->mWidth - 10) aPoint.mX = anApp->mWidth - 10;
	if (aPoint.mY < 10) aPoint.mY = 10;
	else if (aPoint.mY > anApp->mHeight - 10) aPoint.mY = anApp->mHeight - 10;

	SetCaretPos(aPoint.mX, aPoint.mY);
}

void EditWidget::GotFocus()
{
	Widget::GotFocus();
	if (mWidgetManager && mWidgetManager->mApp->mTabletPC)
	{
		SexyAppBase* anApp = mWidgetManager->mApp;

		CreateCaret(anApp->mHWnd, NULL, 0, 0);
		UpdateCaretPos();
		ShowCaret(anApp->mHWnd);
	}

	mShowingCursor = true;
	mBlinkAcc = 0;
	MarkDirty();
}

void EditWidget::LostFocus()
{
	Widget::LostFocus();

	if (mWidgetManager && mWidgetManager->mApp->mTabletPC)
	{
		HideCaret(mWidgetManager->mApp->mHWnd);
		DestroyCaret();
	}

	mShowingCursor = false;
	MarkDirty();
}

void EditWidget::Update()
{
	Widget::Update();

	if (mHasFocus)
	{
		if (mWidgetManager->mApp->mTabletPC)
		{
			UpdateCaretPos();
		}

		if (++mBlinkAcc > mBlinkDelay)
		{
			MarkDirty();
			mBlinkAcc = 0;
			mShowingCursor = !mShowingCursor;
		}
	}
}

void EditWidget::EnforceMaxPixels()
{
	if (mMaxPixels <= 0 && mWidthCheckList.empty()) // no width checking in effect
		return;

	if (mWidthCheckList.empty())
	{
		while (mFont->StringWidth(mString) > mMaxPixels)
			mString = mString.substr(0, mString.length() - 1);

		return;
	}

	for (WidthCheckList::iterator anItr = mWidthCheckList.begin(); anItr != mWidthCheckList.end(); ++anItr)
	{
		int aWidth = anItr->mWidth;
		if (aWidth <= 0)
		{
			aWidth = mMaxPixels;
			if (aWidth <= 0)
				continue;
		}

		while (anItr->mFont->StringWidth(mString) > aWidth)
			mString = mString.substr(0, mString.length() - 1);
	}
}

bool EditWidget::IsPartOfWord(SexyChar theChar)
{
	return (((theChar >= _S('A')) && (theChar <= _S('Z'))) ||
		((theChar >= _S('a')) && (theChar <= _S('z'))) ||
		((theChar >= _S('0')) && (theChar <= _S('9'))) ||
			(theChar == _S('_')));
}

void EditWidget::ProcessKey(KeyCode theKey, SexyChar theChar)
{
	int func = 0x543250;
	int _theChar = theChar;
	__asm
	{
		push _theChar
		push theKey
		mov ecx, this
		call func
	}
}

void EditWidget::KeyDown(KeyCode theKey)
{
	if (((theKey < 'A') || (theKey >= 'Z')) && mEditListener->AllowKey(mId, theKey))
		ProcessKey(theKey, 0);

	Widget::KeyDown(theKey);
}

void EditWidget::KeyChar(SexyChar theChar)
{
	//	if (mEditListener->AllowChar(mId, theChar))
	ProcessKey(KEYCODE_UNKNOWN, theChar);

	Widget::KeyChar(theChar);
}

int EditWidget::GetCharAt(int x, int y)
{
	int aPos = 0;

	SexyString& aString = GetDisplayString();

	for (int i = mLeftPos; i < (int)aString.length(); i++)
	{
		SexyString aLoSubStr = aString.substr(mLeftPos, i - mLeftPos);
		SexyString aHiSubStr = aString.substr(mLeftPos, i - mLeftPos + 1);

		int aLoLen = mFont->StringWidth(aLoSubStr);
		int aHiLen = mFont->StringWidth(aHiSubStr);
		if (x >= (aLoLen + aHiLen) / 2 + 5)
			aPos = i + 1;
	}

	return aPos;
}

void EditWidget::FocusCursor(bool bigJump)
{
	while (mCursorPos < mLeftPos)
	{
		if (bigJump)
			mLeftPos = max(0, mLeftPos - 10);
		else
			mLeftPos = max(0, mLeftPos - 1);
		MarkDirty();
	}

	if (mFont != NULL)
	{
		SexyString& aString = GetDisplayString();
		while ((mWidth - 8 > 0) && (mFont->StringWidth(aString.substr(0, mCursorPos)) - mFont->StringWidth(aString.substr(0, mLeftPos)) >= mWidth - 8))
		{
			if (bigJump)
				mLeftPos = min(mLeftPos + 10, (int)mString.length() - 1);
			else
				mLeftPos = min(mLeftPos + 1, (int)mString.length() - 1);

			MarkDirty();
		}
	}
}

void EditWidget::MouseDown(int x, int y, int theBtnNum, int theClickCount)
{
	Widget::MouseDown(x, y, theBtnNum, theClickCount);

	mHilitePos = -1;
	mCursorPos = GetCharAt(x, y);

	if (theClickCount > 1)
	{
		mHadDoubleClick = true;
		HiliteWord();
	}

	MarkDirty();

	FocusCursor(false);
}

void EditWidget::MouseUp(int x, int y, int theBtnNum, int theClickCount)
{
	Widget::MouseUp(x, y, theBtnNum, theClickCount);
	if (mHilitePos == mCursorPos)
		mHilitePos = -1;

	if (mHadDoubleClick)
	{
		mHilitePos = -1;
		mCursorPos = GetCharAt(x, y);

		mHadDoubleClick = false;
		HiliteWord();
	}

	MarkDirty();
}

void EditWidget::HiliteWord()
{
	SexyString& aString = GetDisplayString();

	if (mCursorPos < (int)aString.length())
	{
		// Find first space before word
		mHilitePos = mCursorPos;
		while ((mHilitePos > 0) && (IsPartOfWord(aString[mHilitePos - 1])))
			mHilitePos--;

		// Find first space after word
		while ((mCursorPos < (int)aString.length() - 1) && (IsPartOfWord(aString[mCursorPos + 1])))
			mCursorPos++;
		if (mCursorPos < (int)aString.length())
			mCursorPos++;
	}
}

void EditWidget::MouseDrag(int x, int y)
{
	Widget::MouseDrag(x, y);

	if (mHilitePos == -1)
		mHilitePos = mCursorPos;

	mCursorPos = GetCharAt(x, y);
	MarkDirty();

	FocusCursor(false);
}

void EditWidget::MouseEnter()
{
	Widget::MouseEnter();

	mWidgetManager->mApp->SetCursor(CURSOR_TEXT);
}

void EditWidget::MouseLeave()
{
	Widget::MouseLeave();

	mWidgetManager->mApp->SetCursor(CURSOR_POINTER);
}

void EditWidget::MarkDirty()
{
	if (mColors[COLOR_BKG].mAlpha != 255)
		Widget::MarkDirtyFull();
	else
		Widget::MarkDirty();
}
