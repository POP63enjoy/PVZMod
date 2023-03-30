#include "LawnCommon.h"
#include "Res.h"
#include "Dialog.h"
#include "Graphics.h"

using namespace PVZMod;

Checkbox* (*PVZMod::MakeNewCheckBox)(int theId, CheckboxListener* theListener, bool theDefault) = (decltype(MakeNewCheckBox))0x459c00;

int gLawnEditWidgetColors[][4] = {
	{ 0,   0,   0,   0 },
	{ 0,   0,   0,   0 },
	{ 240, 240, 255, 255 },
	{ 255, 255, 255, 255 },
	{ 0,   0,   0,   255 },
};

LawnEditWidget::LawnEditWidget(int theId, EditListener* theListener, Dialog* theDialog) : EditWidget(theId, theListener)
{
	mDialog = theDialog;
	mAutoCapFirstLetter = true;
}

LawnEditWidget::~LawnEditWidget()
{
}

void LawnEditWidget::KeyDown(KeyCode theKey)
{
	EditWidget::KeyDown(theKey);
	if (theKey == KeyCode::KEYCODE_ESCAPE)
		mDialog->KeyDown(KeyCode::KEYCODE_ESCAPE);
}

void LawnEditWidget::KeyChar(char theChar)
{
	if (mAutoCapFirstLetter && isalpha(theChar))
	{
		theChar = toupper(theChar);
		mAutoCapFirstLetter = false;
	}

	EditWidget::KeyChar(theChar);
}

LawnEditWidget* PVZMod::CreateEditWidget(int theId, EditListener* theListener, Dialog* theDialog)
{
	LawnEditWidget* aEditWidget = new LawnEditWidget(theId, theListener, theDialog);
	aEditWidget->SetFont(FONT_BRIANNETOD16);
	aEditWidget->SetColors(gLawnEditWidgetColors, EditWidget::NUM_COLORS);
	aEditWidget->mBlinkDelay = 14;

	return aEditWidget;
}

void PVZMod::DrawEditBox(Graphics* g, EditWidget* theWidget)
{
	Rect aDest(theWidget->mX - 8, theWidget->mY - 4, theWidget->mWidth + 16, theWidget->mHeight + 8);
	g->DrawImageBox(aDest, IMAGE_EDITBOX);
}
