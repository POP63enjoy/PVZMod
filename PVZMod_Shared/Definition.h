#pragma once
#ifndef _PVZMOD_DEFINITION_H_
#define _PVZMOD_DEFINITION_H_

namespace PVZMod
{
	struct TodAllocator
	{
		void*				mFreeList;
		void*				mBlockList;
		int					mGrowCount;
		int					mTotalItems;
		int					mItemSize;

		void				Initialize(int theGrowCount, int theItemSize);
		void				Dispose();
		void				FreeAll();
		void*				Alloc(int theItemSize);
		void*				Calloc(int theItemSize);
		void				Free(void* theItem, int theItemSize);
		void				Grow();
		bool				IsPointerFromAllocator(void* theItem);
		bool				IsPointerOnFreeList(void* theItem);
	};

	enum TodCurves;

	class FloatParameterTrackNode
	{
	public:
		float                       mTime;                          ///< 阶段的起始时间
		float                       mLowValue;                      ///< 阶段内数据允许的最小值
		float                       mHighValue;                     ///< 阶段内数据允许的最大值
		TodCurves                   mCurveType;                     ///< 从当前阶段过渡至下一阶段的缓动效果曲线
		TodCurves                   mDistribution;                  ///< 阶段内数据在最小值和最大值之间的概率分布曲线
	};

	class FloatParameterTrack
	{
	public:
		FloatParameterTrackNode*	mNodes;
		int                         mCountNodes;
	};
}

#endif // !_PVZMOD_DEFINITION_H_
