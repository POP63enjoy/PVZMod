#pragma once
#include <cassert>
#include "Definition.h"

namespace PVZMod
{
	template <typename T> 
	class TodListNode
	{
	public:
		T					mValue;
		TodListNode<T>*		mNext;
		TodListNode<T>*		mPrev;
	};

	template <typename T> 
	class TodList
	{
	public:
		TodListNode<T>*		mHead;
		TodListNode<T>*		mTail;
		int					mSize;
		TodAllocator*		mpAllocator;

	public:
		TodList()
		{
			mHead = nullptr;
			mTail = nullptr;
			mSize = 0;
			mpAllocator = nullptr;
		}

		~TodList()
		{
			RemoveAll();
		}

		TodListNode<T>* GetHead()
		{
			assert(mHead != nullptr);
			return mHead;
		}

		TodListNode<T>* GetTail()
		{
			assert(mTail != nullptr);
			return mTail;
		}

		void AddHead(const T& theHead)
		{
			if (mpAllocator == nullptr)
				mpAllocator = FindGlobalAllocator(sizeof(TodListNode<T>));

			TodListNode<T>* aNode = (TodListNode<T>*)mpAllocator->Calloc(sizeof(TodListNode<T>));

			if (aNode)
				aNode->mValue = theHead;

			aNode->mNext = mHead;
			aNode->mPrev = nullptr;

			if (mHead)
				mHead->mPrev = aNode;
			else
				mTail = aNode;

			mSize++;
			mHead = aNode;
		}

		void AddTail(const T& theTail)
		{
			if (mpAllocator == nullptr)
				mpAllocator = FindGlobalAllocator(sizeof(TodListNode<T>));

			TodListNode<T>* aNode = (TodListNode<T>*)mpAllocator->Calloc(sizeof(TodListNode<T>));

			if (aNode)
				aNode->mValue = theTail;

			aNode->mNext = nullptr;
			aNode->mPrev = mTail;

			if (mTail)
				mTail->mNext = aNode;
			else
				mHead = aNode;

			mSize++;
			mTail = aNode;
		}

		T RemoveHead()
		{
			TodListNode<T>* aHead = mHead;
			TodListNode<T>* aSecNode = aHead->mNext;

			mHead = aSecNode;

			if (aSecNode)
				aSecNode->mPrev = nullptr;
			else
				mTail = nullptr;
		
			T aVal = aHead->mValue;

			mSize--;
			mpAllocator->Free(aHead, sizeof(TodListNode<T>));

			return aVal;
		}

		TodListNode<T>* RemoveAt(TodListNode<T>* theNode)
		{
			if (theNode->mPrev != nullptr)
				theNode->mPrev->mNext = theNode->mNext;
			else
				mHead = theNode->mNext;

			if (theNode->mNext != nullptr)
				theNode->mNext->mPrev = theNode->mPrev;
			else
				mTail = theNode->mPrev;

			mSize--;
			mpAllocator->Free(theNode, sizeof(TodListNode<T>));

			return theNode->mNext;
		}

		TodListNode<T>* Find(const T& theItem) const
		{
			for (TodListNode<T>* aNode = mHead; aNode != nullptr; aNode = aNode->mNext)
				if (aNode->mValue == theItem)
					return aNode;

			return nullptr;
		}

		void RemoveAll()
		{
			TodListNode<T>* aNode = mHead;

			while (aNode)
			{
				TodListNode<T>* temp = aNode;
				aNode = aNode->mNext;
				mpAllocator->Free(temp, sizeof(TodListNode<T>));
			}

			mSize = 0;
			mHead = nullptr;
			mTail = nullptr;
		}

		void SetAllocator(TodAllocator* theAllocator) 
		{ 
			assert(mSize == 0);
			mpAllocator = theAllocator;
		}
	};
}