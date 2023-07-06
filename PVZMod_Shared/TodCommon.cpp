#include "TodCommon.h"
#include <cassert>
#include "TodStringFile.h"
#include "SexyCommon.h"
#include "Font.h"
#include "Graphics.h"
#include <numbers>

using namespace PVZMod;

void PVZMod::TodScaleRotateTransformMatrix(SexyMatrix3* m, float x, float y, float rad, float theScaleX, float theScaleY)
{
	int func = 0x516820;
	__asm
	{
		mov esi, m
		push theScaleY
		push theScaleX
		push rad
		push y
		push x
		call func
		add esp, 0x14
	}
}

int PVZMod::RandRangeInt(int theMin, int theMax)
{
	assert(theMin <= theMax);
	return Rand(theMax - theMin + 1) + theMin;
}

float PVZMod::RandRangeFloat(float theMin, float theMax)
{
	assert(theMin <= theMax);
	return Rand(theMax - theMin) + theMin;
}

bool PVZMod::TodLoadResources(const String& theGroup)
{
	int func = 0x517370;
	bool result;
	__asm
	{
		push theGroup
		call func
		add esp, 0x4
		mov result, al
	}
	return result;
}

SexyString PVZMod::TodReplaceNumberString(const SexyString& theText, const SexyChar* theStringToFind, int theNumber)
{
	SexyString aFinalString = TodStringTranslate(theText);
	
	if (size_t aPos = aFinalString.find(theStringToFind); aPos != SexyString::npos)
	{
		SexyString aNumberString = StrFormat(_S("%d"), theNumber);
		aFinalString.replace(aPos, sexystrlen(theStringToFind), aNumberString);
	}

	return aFinalString;
}

SexyString PVZMod::TodReplaceString(const SexyString& theText, const SexyChar* theStringToFind, const SexyString& theStringToSubstitute)
{
	SexyString aFinalString = TodStringTranslate(theText);
	
	if (size_t aPos = aFinalString.find(theStringToFind); aPos != SexyString::npos)
	{
		SexyString aFinalStringToSubstitute = TodStringTranslate(theStringToSubstitute);
		aFinalString.replace(aPos, sexystrlen(theStringToFind), aFinalStringToSubstitute);
	}

	return aFinalString;
}

void PVZMod::TodDrawString(Graphics* g, const SexyString& theText, int thePosX, int thePosY, Font* theFont, const Color& theColor, DrawStringJustification theJustification)
{
	SexyString aFinalString = TodStringTranslate(theText);

	int aPosX = thePosX;
	if (theJustification == DS_ALIGN_RIGHT || theJustification == DS_ALIGN_RIGHT_VERTICAL_MIDDLE)
	{
		aPosX -= theFont->StringWidth(aFinalString);
	}
	else if (theJustification == DS_ALIGN_CENTER || theJustification == DS_ALIGN_CENTER_VERTICAL_MIDDLE)
	{
		aPosX -= theFont->StringWidth(aFinalString) / 2;
	}

	theFont->DrawString(g, aPosX, thePosY, aFinalString, theColor, g->mClipRect);
}

TodAllocator* PVZMod::FindGlobalAllocator(int theSize)
{
	int func = 0x5177c0;
	TodAllocator* result;
	__asm
	{
		mov esi, theSize
		call func
		mov result, eax
	}
	return result;
}


float PVZMod::TodCurveQuad(float theTime)
{
	return theTime * theTime;
}

float PVZMod::TodCurveInvQuad(float theTime)
{
	return 2 * theTime - theTime * theTime;
}

float PVZMod::TodCurveS(float theTime)
{
	return 3 * theTime * theTime - 2 * theTime * theTime * theTime;
}

float PVZMod::TodCurveInvQuadS(float theTime)
{
	if (theTime <= 0.5f)
	{
		return TodCurveInvQuad(theTime * 2.0f) * 0.5f;
	}
	return TodCurveQuad((theTime - 0.5f) * 2.0f) * 0.5f + 0.5f;
}

float PVZMod::TodCurveBounce(float theTime)
{
	return 1 - fabs(2 * theTime - 1);
}

float PVZMod::TodCurveQuadS(float theTime)
{
	if (theTime <= 0.5f)
	{
		return TodCurveQuad(theTime * 2.0f) * 0.5f;
	}
	return TodCurveInvQuad((theTime - 0.5f) * 2.0f) * 0.5f + 0.5f;
}

float PVZMod::TodCurveCubic(float theTime)
{
	return theTime * theTime * theTime;
}

float PVZMod::TodCurveInvCubic(float theTime)
{
	return (theTime - 1.0f) * (theTime - 1.0f) * (theTime - 1.0f) + 1.0f;
}

float PVZMod::TodCurveCubicS(float theTime)
{
	if (theTime <= 0.5f)
	{
		return TodCurveCubic(theTime * 2.0f) * 0.5f;
	}
	return TodCurveInvCubic((theTime - 0.5f) * 2.0f) * 0.5f + 0.5f;
}

float PVZMod::TodCurvePoly(float theTime, float thePoly)
{
	return (float)pow(theTime, thePoly);
}

float PVZMod::TodCurveInvPoly(float theTime, float thePoly)
{
	return (float)pow(theTime - 1.0f, thePoly) + 1.0f;
}

float PVZMod::TodCurvePolyS(float theTime, float thePoly)
{
	if (theTime <= 0.5f)
	{
		return TodCurvePoly(theTime * 2.0f, thePoly) * 0.5f;
	}
	return TodCurveInvPoly((theTime - 0.5f) * 2.0f, thePoly) * 0.5f + 0.5f;
}

float PVZMod::TodCurveCircle(float theTime)
{
	if (theTime > 1 - 1E-6f)
	{
		return 1.0f;
	}
	return 1.0f - (float)sqrt(1.0f - theTime * theTime);
}

float PVZMod::TodCurveInvCircle(float theTime)
{
	if (theTime < 1E-06f)
	{
		return 0.0f;
	}
	return (float)sqrt(1.0f - (theTime - 1.0f) * (theTime - 1.0f));
}

float PVZMod::TodCurveEvaluate(float theTime, float thePositionStart, float thePositionEnd, TodCurves theCurve)
{
	float aWarpedTime;
	switch (theCurve)
	{
	case CURVE_CONSTANT:
		aWarpedTime = 0;
		break;
	case CURVE_LINEAR:
		aWarpedTime = theTime;
		break;
	case CURVE_EASE_IN:
		aWarpedTime = TodCurveQuad(theTime);
		break;
	case CURVE_EASE_OUT:
		aWarpedTime = TodCurveInvQuad(theTime);
		break;
	case CURVE_EASE_IN_OUT:
		aWarpedTime = TodCurveS(TodCurveS(theTime));
		break;
	case CURVE_EASE_IN_OUT_WEAK:
		aWarpedTime = TodCurveS(theTime);
		break;
	case CURVE_FAST_IN_OUT:
		aWarpedTime = TodCurveInvQuadS(TodCurveInvQuadS(theTime));
		break;
	case CURVE_FAST_IN_OUT_WEAK:
		aWarpedTime = TodCurveInvQuadS(theTime);
		break;
	case CURVE_BOUNCE:
		aWarpedTime = TodCurveBounce(theTime);
		break;
	case CURVE_BOUNCE_FAST_MIDDLE:
		aWarpedTime = TodCurveQuad(TodCurveBounce(theTime));
		break;
	case CURVE_BOUNCE_SLOW_MIDDLE:
		aWarpedTime = TodCurveInvQuad(TodCurveBounce(theTime));
		break;
	case CURVE_SIN_WAVE:
		aWarpedTime = sinf(2 * std::numbers::pi_v<float> * theTime);
		break;
	case CURVE_EASE_SIN_WAVE:
		aWarpedTime = sinf(2 * std::numbers::pi_v<float> * TodCurveS(theTime));
		break;
	default:
		assert(false);
		return -1;
	}
	return (thePositionEnd - thePositionStart) * aWarpedTime + thePositionStart;
}

float PVZMod::TodCurveEvaluateClamped(float theTime, float thePositionStart, float thePositionEnd, TodCurves theCurve)
{
	if (theTime <= 0.0f)
	{
		return thePositionStart;
	}

	if (theTime >= 1.0f)
	{
		if (theCurve == CURVE_BOUNCE ||
			theCurve == CURVE_BOUNCE_FAST_MIDDLE ||
			theCurve == CURVE_BOUNCE_SLOW_MIDDLE ||
			theCurve == CURVE_SIN_WAVE ||
			theCurve == CURVE_EASE_SIN_WAVE)
		{
			return thePositionStart;
		}
		else
		{
			return thePositionEnd;
		}
	}

	return TodCurveEvaluate(theTime, thePositionStart, thePositionEnd, theCurve);
}

float PVZMod::TodAnimateCurveFloatTime(float theTimeStart, float theTimeEnd, float theTimeAge, float thePositionStart, float thePositionEnd, TodCurves theCurve)
{
	float aWarpedAge = (theTimeAge - theTimeStart) / (theTimeEnd - theTimeStart);
	return TodCurveEvaluateClamped(aWarpedAge, thePositionStart, thePositionEnd, theCurve);
}

float PVZMod::TodAnimateCurveFloat(int theTimeStart, int theTimeEnd, int theTimeAge, float thePositionStart, float thePositionEnd, TodCurves theCurve)
{
	float aWarpedAge = (theTimeAge - theTimeStart) / (float)(theTimeEnd - theTimeStart);
	return TodCurveEvaluateClamped(aWarpedAge, thePositionStart, thePositionEnd, theCurve);
}

int PVZMod::TodAnimateCurve(int theTimeStart, int theTimeEnd, int theTimeAge, int thePositionStart, int thePositionEnd, TodCurves theCurve)
{
	return FloatRoundToInt(TodAnimateCurveFloat(theTimeStart, theTimeEnd, theTimeAge, (float)thePositionStart, (float)thePositionEnd, theCurve));
}