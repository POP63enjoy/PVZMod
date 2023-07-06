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
		float                       mTime;                          ///< �׶ε���ʼʱ��
		float                       mLowValue;                      ///< �׶��������������Сֵ
		float                       mHighValue;                     ///< �׶���������������ֵ
		TodCurves                   mCurveType;                     ///< �ӵ�ǰ�׶ι�������һ�׶εĻ���Ч������
		TodCurves                   mDistribution;                  ///< �׶�����������Сֵ�����ֵ֮��ĸ��ʷֲ�����
	};

	class FloatParameterTrack
	{
	public:
		FloatParameterTrackNode*	mNodes;
		int                         mCountNodes;
	};
}

#endif // !_PVZMOD_DEFINITION_H_
