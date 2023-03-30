#include "WidgetManager.h"
#include "Graphics.h"
#include "Widget.h"

using namespace PVZMod;

void WidgetManager::DeferOverlay(Widget* theWidget, int thePriority)
{
	mDeferredOverlayWidgets.push_back(std::pair<Widget*, int>(theWidget, thePriority));
	if (thePriority < mMinDeferredOverlayPriority)
		mMinDeferredOverlayPriority = thePriority;
}

void WidgetManager::FlushDeferredOverlayWidgets(int theMaxPriority)
{
	for (;;)
	{
		int aNextMinPriority = 0x7FFFFFFF;

		for (int i = 0; i < (int)mDeferredOverlayWidgets.size(); i++)
		{
			Widget* aWidget = mDeferredOverlayWidgets[i].first;
			if (aWidget != NULL)
			{
				int aPriority = mDeferredOverlayWidgets[i].second;

				if (aPriority == mMinDeferredOverlayPriority)
				{
					// Overlays don't get clipped
					Graphics g(*mCurG);
					g.Translate(-mMouseDestRect.mX, -mMouseDestRect.mY);
					g.Translate(aWidget->mX, aWidget->mY);
					g.SetFastStretch(!g.Is3D());
					g.SetLinearBlend(g.Is3D());

					aWidget->DrawOverlay(&g, aPriority);
					mDeferredOverlayWidgets[i].first = NULL;
				}
				else
				{
					if (aPriority < aNextMinPriority)
						aNextMinPriority = aPriority;
				}
			}
		}

		mMinDeferredOverlayPriority = aNextMinPriority;
		if (aNextMinPriority == 0x7FFFFFFF)
		{
			// No more widgets lined up for overlays, clear our vector
			mDeferredOverlayWidgets.resize(0);
			break;
		}

		// Lowest overlay priority is higher or equal to our current widget, 
		//  so continue deferring
		if (aNextMinPriority >= theMaxPriority)
			break;
	}
}

void WidgetManager::MousePosition(int x, int y)
{
	int aLastMouseX = mLastMouseX;
	int aLastMouseY = mLastMouseY;

	mLastMouseX = x;
	mLastMouseY = y;

	int aWidgetX;
	int aWidgetY;
	Widget* aWidget = GetWidgetAt(x, y, &aWidgetX, &aWidgetY);

	if (aWidget != mOverWidget)
	{
		Widget* aLastOverWidget = mOverWidget;
		mOverWidget = NULL;

		if (aLastOverWidget != NULL)
			MouseLeave(aLastOverWidget);

		mOverWidget = aWidget;
		if (aWidget != NULL)
		{
			MouseEnter(aWidget);
			aWidget->MouseMove(aWidgetX, aWidgetY);
		}
	}
	else if ((aLastMouseX != x) || (aLastMouseY != y))
	{
		if (aWidget != NULL)
			aWidget->MouseMove(aWidgetX, aWidgetY);
	}
}

void WidgetManager::RehupMouse()
{
	if (mLastDownWidget != NULL)
	{
		if (mOverWidget != NULL)
		{
			Widget* aWidgetOver = GetWidgetAt(mLastMouseX, mLastMouseY, NULL, NULL);

			if (aWidgetOver != mLastDownWidget)
			{
				Widget* anOverWidget = mOverWidget;
				mOverWidget = NULL;
				MouseLeave(anOverWidget);
			}
		}
	}
}

int WidgetManager::GetWidgetFlags()
{
	return mHasFocus ? mWidgetFlags : GetModFlags(mWidgetFlags, mLostFocusFlagsMod);
}

void WidgetManager::MouseEnter(Widget* theWidget)
{
	theWidget->mIsOver = true;

	theWidget->MouseEnter();
	if (theWidget->mDoFinger)
		theWidget->ShowFinger(true);
}

void WidgetManager::MouseLeave(Widget* theWidget)
{
	theWidget->mIsOver = false;

	theWidget->MouseLeave();
	if (theWidget->mDoFinger)
		theWidget->ShowFinger(false);
}

void WidgetManager::Resize(const Rect& theMouseDestRect, const Rect& theMouseSourceRect)
{
	mWidth = theMouseDestRect.mWidth + 2 * theMouseDestRect.mX;
	mHeight = theMouseDestRect.mHeight + 2 * theMouseDestRect.mY;
	mMouseDestRect = theMouseDestRect;
	mMouseSourceRect = theMouseSourceRect;
}

Widget* WidgetManager::GetAnyWidgetAt(int x, int y, int* theWidgetX, int* theWidgetY)
{
	bool found;
	return GetWidgetAtHelper(x, y, GetWidgetFlags(), &found, theWidgetX, theWidgetY);
}

Widget* WidgetManager::GetWidgetAt(int x, int y, int* theWidgetX, int* theWidgetY)
{
	Widget* aWidget = GetAnyWidgetAt(x, y, theWidgetX, theWidgetY);
	if ((aWidget != NULL) && (aWidget->mDisabled))
		aWidget = NULL;
	return aWidget;
}

bool WidgetManager::IsLeftButtonDown()
{
	return (mActualDownButtons & 1) ? true : false;
}
