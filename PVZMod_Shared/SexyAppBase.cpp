#define PVZMOD_SEXYAPP_ALL_PUBLIC

#include "SexyAppBase.h"
#include "DDInterface.h"
#include "WidgetManager.h"
#include "DDImage.h"
#include <cassert>

using namespace PVZMod;

SexyAppBase*& PVZMod::gSexyAppBase = *(SexyAppBase**)0x6BA058;

void SexyAppBase::SetCursor(int theCursorNum)
{
	int function = 0x55ad30;
	__asm
	{
		mov ecx,this
		mov eax,theCursorNum
		call function
	}
}

void SexyAppBase::SetBoolean(const String& theId, bool theValue)
{
	mBoolProperties[theId] = theValue;
}

void SexyAppBase::SetString(const String& theId, const WString& theValue)
{
	mStringProperties[theId] = theValue;
}

bool SexyAppBase::ProcessDeferredMessages(bool singleMessage)
{
	if (singleMessage == false)
	{
		while (ProcessDeferredMessages(true));
		return false;
	}

	int func = 0x555EB0;
	bool result;
	__asm
	{
		push this
		call func
		mov result, al
	}

	return result;
}

int SexyAppBase::InitDDInterface()
{
	int func = 0x5583a0;
	int result;
	__asm
	{
		mov esi, this
		call func
		mov result, eax
	}
	return result;
}

bool SexyAppBase::GetBoolean(const String& theId)
{
	auto anItr = mBoolProperties.find(theId);
	assert(anItr != mBoolProperties.end());

	if (anItr != mBoolProperties.end())
		return anItr->second;
	else
		return false;
}

bool SexyAppBase::RegistryReadString(const String& theKey, String* theString)
{
	char aStr[1024];

	uint32_t aType;
	uint32_t aLen = sizeof(aStr) - 1;

	if (!RegistryRead(theKey, &aType, (uint8_t*)aStr, &aLen))
		return false;

	if (aType != REG_SZ)
		return false;

	aStr[aLen] = 0;

	*theString = aStr;
	return true;
}

bool SexyAppBase::RegistryRead(const String& theValueName, uint32_t* theType, uint8_t* theValue, uint32_t* theLength)
{
	return RegistryReadKey(theValueName, theType, theValue, theLength, HKEY_CURRENT_USER);
}

bool SexyAppBase::RegistryReadKey(const String& theValueName, uint32_t* theType, uint8_t* theValue, uint32_t* theLength, HKEY theMainKey)
{
	bool result;
	int func = 0x550070;
	__asm
	{
		push theMainKey
		mov edx, theLength
		mov ecx, theValue
		push theType
		push theValueName
		push this
		call func
		mov result, al
	}
	return result;
}

bool SexyAppBase::RegistryWrite(const String& theValueName, uint32_t theType, const uint8_t* theValue, uint32_t theLength)
{
	bool result;
	int func = 0x54f610;
	__asm
	{
		push theLength
		push theValue
		push theType
		mov ebx, theValueName
		push this
		call func
		mov result, al
	}
	return result;
}

bool SexyAppBase::RegistryWriteString(const String& theValueName, const String& theString)
{
	return RegistryWrite(theValueName, REG_SZ, (uint8_t*)theString.c_str(), theString.length());
}

bool SexyAppBase::Is3DAccelerated()
{
	return mDDInterface->mIs3D;
}

void SexyAppBase::ReinitDDInterface()
{
	InitDDInterface();
	ReInitImages();
	mWidgetManager->mImage = mDDInterface->GetScreenImage();
	mWidgetManager->MarkAllDirty();
}

void SexyAppBase::KeepAspectRatioFullClient(int theClientWidth, int theClientHeight)
{
	Rect rect;
	if ((double)mWidth / mHeight < (double)theClientWidth / theClientHeight)	// ×óÓÒºÚ±ß
	{
		rect.mHeight = theClientHeight;
		rect.mWidth = (int)ceil((double)theClientHeight * mWidth / mHeight);
		rect.mY = 0;
		rect.mX = (theClientWidth - rect.mWidth) / 2;
	}
	else																		// ÉÏÏÂºÚ±ß
	{
		rect.mWidth = theClientWidth;
		rect.mHeight = (int)ceil((double)theClientWidth * mHeight / mWidth);
		rect.mX = 0;
		rect.mY = (theClientHeight - rect.mHeight) / 2;
	}
	if (mDDInterface)
	{
		mDDInterface->mPresentationRect = rect;
		mDDInterface->mDisplayWidth = theClientWidth;
		mDDInterface->mDisplayHeight = theClientHeight;
	}

	if (mWidgetManager)
		mWidgetManager->Resize({ 0,0,mWidth,mHeight }, rect);
}

LRESULT SexyAppBase::WindowSizingKeepAspectRatio(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	RECT& rc = *(RECT*)lParam;

	RECT windowRect;
	GetWindowRect(hwnd, &windowRect);

	RECT clientRect;
	GetClientRect(hwnd, &clientRect);

	int borderWidth = windowRect.right - windowRect.left - (clientRect.right - clientRect.left);
	int borderHeight = windowRect.bottom - windowRect.top - (clientRect.bottom - clientRect.top);

	rc.right -= borderWidth;
	rc.bottom -= borderHeight;

	double aspect = (double)mWidth / mHeight;

	int newWidth = rc.right - rc.left;
	int newHeight = rc.bottom - rc.top;

	switch (wParam)
	{
	case WMSZ_LEFT:
		rc.left = rc.right - newWidth;
		rc.bottom = (LONG)(rc.top + newWidth / aspect + 0.5);
		break;
	case WMSZ_RIGHT:
		rc.right = rc.left + newWidth;
		rc.bottom = (LONG)(rc.top + newWidth / aspect + 0.5);
		break;
	case WMSZ_TOP:
		rc.top = rc.bottom - newHeight;
		rc.right = (LONG)(rc.left + newHeight * aspect + 0.5);
		break;
	case WMSZ_BOTTOM:
		rc.bottom = rc.top + newHeight;
		rc.right = (LONG)(rc.left + newHeight * aspect + 0.5);
		break;
	case WMSZ_BOTTOMRIGHT:
		rc.right = rc.left + newWidth;
		rc.bottom = (LONG)(rc.top + newWidth / aspect + 0.5);
		break;
	case WMSZ_TOPRIGHT:
		rc.right = rc.left + newWidth;
		rc.top = (LONG)(rc.bottom - newWidth / aspect + 0.5);
		break;
	case WMSZ_BOTTOMLEFT:
		rc.left = rc.right - newWidth;
		rc.bottom = (LONG)(rc.top + newWidth / aspect + 0.5);
		break;
	case WMSZ_TOPLEFT:
		rc.left = rc.right - newWidth;
		rc.top = (LONG)(rc.bottom - newWidth / aspect + 0.5);
		break;
	}

	rc.right += borderWidth;
	rc.bottom += borderHeight;

	return TRUE;
}
