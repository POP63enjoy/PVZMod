#pragma once
#ifndef _PVZMOD_TOD_COMMON_H_
#define _PVZMOD_TOD_COMMON_H_

#include "SexyMatrix.h"
#include "ResourceManager.h"

namespace PVZMod
{
	struct TodWeightedGridArray
	{
		int mX;
		int mY;
		int mWeight;
	};

	void					TodScaleRotateTransformMatrix(SexyMatrix3* m, float x, float y, float rad, float theScaleX, float theScaleY);

	int						RandRangeInt(int theMin, int theMax);
	float					RandRangeFloat(float theMin, float theMax);
	inline char				ClampByte(char theNum, char theMin, char theMax) { return theNum <= theMin ? theMin : theNum >= theMax ? theMax : theNum; }
	inline int				ClampInt(int theNum, int theMin, int theMax) { return theNum <= theMin ? theMin : theNum >= theMax ? theMax : theNum; }
	inline float			ClampFloat(float theNum, float theMin, float theMax) { return theNum <= theMin ? theMin : theNum >= theMax ? theMax : theNum; }
	inline float			Distance2D(float x1, float y1, float x2, float y2) { return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)); }
	inline float			FloatLerp(float theStart, float theEnd, float theFactor) { return theStart + theFactor * (theEnd - theStart); }
	inline int				FloatRoundToInt(float theFloatValue) { return (int)(theFloatValue > 0 ? theFloatValue + 0.5f : theFloatValue - 0.5f); }
	inline bool				FloatApproxEqual(float theFloatVal1, float theFloatVal2) { return fabs(theFloatVal1 - theFloatVal2) < FLT_EPSILON; }

	bool					TodLoadResources(const String& theGroup);

	SexyString				TodReplaceNumberString(const SexyString& theText, const SexyChar* theStringToFind, int theNumber);
	SexyString				TodReplaceString(const SexyString& theText, const SexyChar* theStringToFind, const SexyString& theStringToSubstitute);

	enum DrawStringJustification
	{
		DS_ALIGN_LEFT,
		DS_ALIGN_RIGHT,
		DS_ALIGN_CENTER,
		DS_ALIGN_LEFT_VERTICAL_MIDDLE,
		DS_ALIGN_RIGHT_VERTICAL_MIDDLE,
		DS_ALIGN_CENTER_VERTICAL_MIDDLE,
	};

	void					TodDrawString(Graphics* g, const SexyString& theText, int thePosX, int thePosY, Font* theFont, const Color& theColor, DrawStringJustification theJustification);


	struct TodAllocator;

	TodAllocator*			FindGlobalAllocator(int theSize);

	/// ��������
	enum TodCurves
	{
		CURVE_CONSTANT,             ///< ���������ߡ�
		CURVE_LINEAR,               ///< �������ߡ�
		CURVE_EASE_IN,              ///< �������� - ���롣
		CURVE_EASE_OUT,             ///< �������� - ������
		CURVE_EASE_IN_OUT,          ///< ���뻺�����ߡ�
		CURVE_EASE_IN_OUT_WEAK,     ///< ���뻺������ - Ч��������
		CURVE_FAST_IN_OUT,          ///< ���������ߡ�
		CURVE_FAST_IN_OUT_WEAK,     ///< ���������� - Ч��������
		CURVE_WEAK_FAST_IN_OUT,     ///< �����������ߡ�
		CURVE_BOUNCE,               ///< ����Ч�����ߡ�
		CURVE_BOUNCE_FAST_MIDDLE,   ///< ����Ч������ - ���Ρ�
		CURVE_BOUNCE_SLOW_MIDDLE,   ///< ����Ч������ - ���Ρ�
		CURVE_SIN_WAVE,             ///< �������ߡ�
		CURVE_EASE_SIN_WAVE         ///< ���뻺�����������ߡ�
	};

	float					TodCurveQuad(float theTime);
	float					TodCurveInvQuad(float theTime);
	float					TodCurveS(float theTime);
	float					TodCurveInvQuadS(float theTime);
	float					TodCurveBounce(float theTime);
	float					TodCurveQuadS(float theTime);
	float					TodCurveCubic(float theTime);
	float					TodCurveInvCubic(float theTime);
	float					TodCurveCubicS(float theTime);
	float					TodCurvePoly(float theTime, float thePoly);
	float					TodCurveInvPoly(float theTime, float thePoly);
	float					TodCurvePolyS(float theTime, float thePoly);
	float					TodCurveCircle(float theTime);
	float					TodCurveInvCircle(float theTime);
	float					TodCurveEvaluate(float theTime, float thePositionStart, float thePositionEnd, TodCurves theCurve);
	float					TodCurveEvaluateClamped(float theTime, float thePositionStart, float thePositionEnd, TodCurves theCurve);
	float					TodAnimateCurveFloatTime(float theTimeStart, float theTimeEnd, float theTimeAge, float thePositionStart, float thePositionEnd, TodCurves theCurve);
	float					TodAnimateCurveFloat(int theTimeStart, int theTimeEnd, int theTimeAge, float thePositionStart, float thePositionEnd, TodCurves theCurve);
	int						TodAnimateCurve(int theTimeStart, int theTimeEnd, int theTimeAge, int thePositionStart, int thePositionEnd, TodCurves theCurve);
}

#endif // !_PVZMOD_TOD_COMMON_H_
