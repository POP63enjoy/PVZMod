#pragma once
#include "SexyVector.h"
#include "Color.h"
#include "DataArray.h"
#include "Definition.h"

namespace PVZMod
{
	class Image;

	class TrailDefinition
	{
	public:
		Image* mImage;
		int						mMaxPoints;
		float					mMinPointDistance;
		int						mTrailFlags;
		FloatParameterTrack		mTrailDuration;
		FloatParameterTrack		mWidthOverLength;
		FloatParameterTrack		mWidthOverTime;
		FloatParameterTrack		mAlphaOverLength;
		FloatParameterTrack		mAlphaOverTime;
	};

	class TrailPoint
	{
	public:
		SexyVector2				aPos;
	};

	class TrailHolder;

	class Trail
	{
	public:
		TrailPoint				mTrailPoints[20];
		int						mNumTrailPoints;
		bool					mDead;
		int						mRenderOrder;
		int						mTrailAge;
		int						mTrailDuration;
		TrailDefinition*		mDefinition;
		TrailHolder*			mTrailHolder;
		float					mTrailInterp[4];
		SexyVector2				mTrailCenter;
		bool					mIsAttachment;
		Color					mColorOverride;
	};

	class TrailHolder
	{
	public:
		DataArray<Trail>		mTrails;
	};
}