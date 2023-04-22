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

	/// ����Ϸ�ࡿ����ء���ԭ `::%DataArray`��
	///
	/// @tparam T				�������͡�
	/// @tparam mExtraTypeSize	��̬�����С��
	template <typename T, size_t* mExtraTypeSize = &__PRIVATE__::defaultExtraSize>
	class DataArray
	{
	public:
		/// ����ṹ��
		class DataArrayItem
		{
		public:
			/// @cond
			size_t&		__getID() { return *(size_t*)((size_t)this + sizeof(T) + *mExtraTypeSize); }
			void		__setID(size_t theID) { __getID() = theID; }
			/// @endcond

			/// ����
			T															mItem;

			/// ���� ID��
			/// 
			/// ��ʮ��λΪ�����ڴ���������ʮ��λΪ����ʶ���롣
			/// 
			/// ����������ʹ�ã���Ϊ��ǰ���� ID����������У���Ϊ��һ�����ж���� ID��
			__declspec(property(get = __getID, put = __setID)) size_t	mID;
		private:
			size_t _;
		};

		/// ����������չ��װ��
		class Block
		{
		public:
			DataArrayItem* mBlock;	///< ����������ʵָ�롣

			/// ���� mExtraTypeSize ȡ�ö������á�
			DataArrayItem& operator[](size_t index) { return *(DataArrayItem*)((size_t)mBlock + (sizeof(DataArrayItem) + *mExtraTypeSize) * index); }
		};

		Block			mBlock;			///< �������顣
		size_t			mMaxUsedCount;	///< ������ʹ������
		size_t			mMaxSize;		///< ������������
		size_t			mFreeListHead;	///< ���ж��� ID ����ͷ��
		size_t			mSize;			///< ��ǰ����ʹ�õĶ���������
		size_t			mNextKey;		///< ��һ������ʶ���롣
		const char*		mName;			///< ���ơ�

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

		/// ��ʼ��
		///
		/// @param theMaxSize	������
		/// @param theName		���ơ�
		void DataArrayInitialize(size_t theMaxSize, const char* theName)
		{
			assert(mBlock.mBlock == nullptr);
			mBlock.mBlock = (DataArrayItem*)operator new(theMaxSize * (sizeof(DataArrayItem) + *mExtraTypeSize));
			mMaxSize = theMaxSize;
			mNextKey = ((((short)theName[1] & 0xF) << 8) | theName[2]) + 0xD000;
			mName = theName;
		}

		/// ����һ������
		///
		/// @return	����Ķ���ָ�롣
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

		/// �ͷŶ���
		///
		/// @param theItem	����ָ�롣
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

		/// ���� ID ��ȡ����������󲻴����򱨴�
		///
		/// @param theId	���� ID��
		/// @return			����ָ�롣
		T* DataArrayGet(size_t theId)
		{
			assert(DataArrayTryToGet(theId) != nullptr);
			return &mBlock[theId & DATA_ARRAY_INDEX_MASK].mItem;
		}

		/// ���� ID ���Ի�ȡ����
		///
		/// @param theId	���� ID��
		/// @return			����ָ�룬������󲻴����򷵻� nullptr��
		T* DataArrayTryToGet(size_t theId)
		{
			if (theId != 0 && (theId & DATA_ARRAY_INDEX_MASK) < mMaxSize && mBlock[theId & DATA_ARRAY_INDEX_MASK].mID == theId)
				return &mBlock[theId & DATA_ARRAY_INDEX_MASK].mItem;
			return nullptr;
		}

		/// ��ȡ����� ID��
		///
		/// @param theItem	����ָ�롣
		/// @return			���� ID��
		size_t DataArrayGetId(T* theItem)
		{
			return ((DataArrayItem*)theItem)->mID;
		}

		/// ��������
		///
		/// @param theItem	���ر����Ķ���
		/// @return			��������򷵻� false��
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

		/// �ͷ����ж���
		void DataArrayFreeAll()
		{
			T* aItem = nullptr;
			while (IterateNext(aItem))
				DataArrayFree(aItem);
		}
	};
}

#endif // !_PVZMOD_DATA_ARRAY_H_
