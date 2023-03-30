#pragma once
#ifndef _PVZMOD_DATA_ARRAY_H_
#define _PVZMOD_DATA_ARRAY_H_

#include "PVZSTL.h"
#include <cassert>

namespace PVZMod
{
	enum
	{
		DATA_ARRAY_INDEX_MASK	= 0xFFFF,
		DATA_ARRAY_KEY_MASK		= 0xFFFF0000,
		DATA_ARRAY_KEY_SHIFT	= 0x10,
		DATA_ARRAY_MAX_SIZE		= 0x10000,
		DATA_ARRAY_KEY_FIRST	= 0x1,
	};

	namespace __PRIVATE__
	{
		inline size_t defaultExtraSize = 0;
	}

	/// 【游戏类】对象池。（原 ::DataArray）
	///
	/// @tparam T				对象类型。
	/// @tparam mExtraTypeSize	动态扩充大小。
	template <typename T, size_t* mExtraTypeSize = &__PRIVATE__::defaultExtraSize>
	class DataArray
	{
	public:
		/// 对象结构。
		class DataArrayItem
		{
		public:
			/// @cond
			size_t&		__getID() { return *(size_t*)((size_t)this + sizeof(T) + *mExtraTypeSize); }
			void		__setID(size_t theID) { __getID() = theID; }
			/// @endcond

			/// 对象。
			T															mItem;

			/// 对象 ID。
			/// 
			/// 低十六位为对象内存索引，高十六位为对象识别码。
			/// 
			/// 若对象正在使用，则为当前对象 ID，若对象空闲，则为下一个空闲对象的 ID。
			__declspec(property(get = __getID, put = __setID)) size_t	mID;
		private:
			size_t _;
		};

		/// 对象数组扩展封装。
		class Block
		{
		public:
			DataArrayItem* mBlock;	///< 对象数组真实指针。

			/// 根据 mExtraTypeSize 取得对象引用。
			DataArrayItem& operator[](size_t index) { return *(DataArrayItem*)((size_t)mBlock + (sizeof(DataArrayItem) + *mExtraTypeSize) * index); }
		};

		Block			mBlock;			///< 对象数组。
		size_t			mMaxUsedCount;	///< 最大对象使用量。
		size_t			mMaxSize;		///< 最大对象容量。
		size_t			mFreeListHead;	///< 空闲对象 ID 链表头。
		size_t			mSize;			///< 当前正在使用的对象数量。
		size_t			mNextKey;		///< 下一个对象识别码。
		const char*		mName;			///< 名称。

	public:
		DataArray()
		{
			mBlock.mBlock = nullptr;
			mMaxUsedCount = 0;
			mMaxSize = 0;
			mFreeListHead = 0;
			mSize = 0;
			mNextKey = DATA_ARRAY_KEY_FIRST;
			mName = nullptr;
		}

		~DataArray()
		{
			if (mBlock.mBlock)
			{
				DataArrayFreeAll();
				operator delete(mBlock.mBlock);
				mBlock.mBlock = nullptr;
				mMaxUsedCount = 0;
				mMaxSize = 0;
				mFreeListHead = 0;
				mSize = 0;
				mName = nullptr;
			}
		}

		/// 初始化
		///
		/// @param theMaxSize	容量。
		/// @param theName		名称。
		void DataArrayInitialize(size_t theMaxSize, const char* theName)
		{
			assert(mBlock.mBlock == nullptr);
			mBlock.mBlock = (DataArrayItem*)operator new(theMaxSize * (sizeof(DataArrayItem) + *mExtraTypeSize));
			mMaxSize = theMaxSize;
			mNextKey = ((((short)theName[1] & 0xF) << 8) | theName[2]) + 0xD000;
			mName = theName;
		}

		/// 分配一个对象。
		///
		/// @return	分配的对象指针。
		T* DataArrayAlloc()
		{
			assert(mSize < mMaxSize);
			assert(mFreeListHead <= mMaxUsedCount);
			size_t index;
			if (mFreeListHead == mMaxUsedCount)
			{
				index = mMaxUsedCount;
				mMaxUsedCount++;
				mFreeListHead = mMaxUsedCount;
			}
			else
			{
				index = mFreeListHead;
				mFreeListHead = mBlock[mFreeListHead].mID;
			}
			memset(&mBlock[index], 0, (sizeof(DataArrayItem) + *mExtraTypeSize));
			mBlock[index].mID = index | (mNextKey++ << DATA_ARRAY_KEY_SHIFT);
			if (mNextKey == DATA_ARRAY_MAX_SIZE)
				mNextKey = DATA_ARRAY_KEY_FIRST;
			mSize++;
			return new(&mBlock[index].mItem)T();
		}

		/// 释放对象。
		///
		/// @param theItem	对象指针。
		void DataArrayFree(T* theItem)
		{
			DataArrayItem* aItem = (DataArrayItem*)theItem;
			assert(DataArrayGet(aItem->mID) == theItem);
			theItem->~T();
			size_t temp = mFreeListHead;
			mFreeListHead = aItem->mID & DATA_ARRAY_INDEX_MASK;
			aItem->mID = temp;
			mSize--;
		}

		/// 根据 ID 获取对象，如果对象不存在则报错。
		///
		/// @param theId	对象 ID。
		/// @return			对象指针。
		T* DataArrayGet(size_t theId)
		{
			assert(DataArrayTryToGet(theId) != nullptr);
			return &mBlock[theId & DATA_ARRAY_INDEX_MASK].mItem;
		}

		/// 根据 ID 尝试获取对象。
		///
		/// @param theId	对象 ID。
		/// @return			对象指针，如果对象不存在则返回 nullptr。
		T* DataArrayTryToGet(size_t theId)
		{
			if (theId != 0 && (theId & DATA_ARRAY_INDEX_MASK) < mMaxSize && mBlock[theId & DATA_ARRAY_INDEX_MASK].mID == theId)
				return &mBlock[theId & DATA_ARRAY_INDEX_MASK].mItem;
			return nullptr;
		}

		/// 获取对象的 ID。
		///
		/// @param theItem	对象指针。
		/// @return			对象 ID。
		size_t DataArrayGetId(T* theItem)
		{
			return ((DataArrayItem*)theItem)->mID;
		}

		/// 遍历对象。
		///
		/// @param theItem	返回遍历的对象。
		/// @return			遍历完成则返回 false。
		bool IterateNext(T*& theItem)
		{
			DataArrayItem* aItem = (DataArrayItem*)theItem;
			if (aItem)
				aItem++;
			else
				aItem = &mBlock[0];

			while (aItem < &mBlock[mMaxUsedCount])
			{
				if (aItem->mID & DATA_ARRAY_KEY_MASK)
				{
					theItem = (T*)aItem;
					return true;
				}
				aItem++;
			}

			theItem = (T*)-1;
			return false;
		}

		/// 释放所有对象。
		void DataArrayFreeAll()
		{
			T* aItem = nullptr;
			while (IterateNext(aItem))
				DataArrayFree(aItem);
		}
	};
}

#endif // !_PVZMOD_DATA_ARRAY_H_
