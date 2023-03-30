#include "HyperlinkWidget.h"
#include "SysFont.h"
#include "WidgetManager.h"
#include "Graphics.h"

using namespace PVZMod;

HyperlinkWidget::HyperlinkWidget(int theId, ButtonListener* theButtonListener) :
	ButtonWidget(theId, theButtonListener),
	mColor(255, 255, 255),
	mOverColor(255, 255, 255)
{
	mDoFinger = true;
	mUnderlineOffset = 3;
	mUnderlineSize = 1;
}

void HyperlinkWidget::Draw(Graphics* g)
{
	/*if (mFont == NULL)
		mFont = new SysFont(mWidgetManager->mApp, "Arial Unicode MS", 10); //baz changed

	int aFontX = (mWidth - mFont->StringWidth(mLabel)) / 2;
	int aFontY = (mHeight + mFont->GetAscent()) / 2 - 1;

	if (mIsOver)
		g->SetColor(mOverColor);
	else
		g->SetColor(mColor);

	g->SetFont(mFont);
	g->DrawString(mLabel, aFontX, aFontY);

	for (int i = 0; i < mUnderlineSize; i++)
		g->FillRect(aFontX, aFontY + mUnderlineOffset + i, mFont->StringWidth(mLabel), 1);*/
	int func = 0x542260;
	__asm
	{
		push g
		mov ecx, this
		call func
	}
}

void HyperlinkWidget::MouseEnter()
{
	ButtonWidget::MouseEnter();

	MarkDirtyFull();
}

void HyperlinkWidget::MouseLeave()
{
	ButtonWidget::MouseLeave();

	MarkDirtyFull();
}