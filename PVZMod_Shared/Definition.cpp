#include "Definition.h"
#include <cassert>
#include <cstdint>
#include <cstring>
#include <cstdlib>

using namespace PVZMod;

void TodAllocator::Initialize(int theGrowCount, int theItemSize)
{
	assert(theItemSize >= sizeof(void*));

	mFreeList = nullptr;
	mBlockList = nullptr;
	mGrowCount = theGrowCount;
	mTotalItems = 0;
	mItemSize = theItemSize;
}

void TodAllocator::Dispose()
{
	FreeAll();
}

void TodAllocator::Grow()
{
	assert(mGrowCount > 0);
	assert(mItemSize >= sizeof(void*));

	void* aBlock = malloc(mGrowCount * mItemSize + 4);
	*(void**)aBlock = mBlockList;
	mBlockList = aBlock;

	void* aFreeList = mFreeList;
	void* aItem = (void*)((uint32_t)aBlock + 4);
	for (int i = 0; i < mGrowCount; i++)
	{
		*(void**)aItem = aFreeList;
		aFreeList = aItem;
		aItem = (void*)((uint32_t)aItem + mItemSize);
	}
	mFreeList = aFreeList;
}

bool TodAllocator::IsPointerFromAllocator(void* theItem)
{
	size_t aBlockSize = mGrowCount * mItemSize;  // 每次“Grow”的内存大小，即每个区块的内存大小
	for (void* aPtr = mBlockList; aPtr != nullptr; aPtr = *(void**)aPtr)
	{
		uint32_t aItemPtr = (uint32_t)theItem;
		// 区块的首个四字节为额外申请的、用于存储指向下一区块的指针的区域
		uint32_t aBlockPtr = (uint32_t)aPtr + sizeof(void*);
		// 判断 theItem 是否位于当前区块内且指向某一项的区域的起始地址
		if (aItemPtr >= aBlockPtr && aItemPtr < aBlockPtr + aBlockSize && (aItemPtr - aBlockPtr) % mItemSize == 0)
			return true;
	}
	return false;
}

bool TodAllocator::IsPointerOnFreeList(void* theItem)
{
	for (void* aPtr = mFreeList; aPtr != nullptr; aPtr = *(void**)aPtr)
		if (theItem == aPtr)
			return true;
	return false;
}

void* TodAllocator::Alloc(int theItemSize)
{
	mTotalItems++;
	if (mFreeList == nullptr)
		Grow();

	void* anItem = (void*)mFreeList;
	mFreeList = *(void**)anItem;
	return anItem;
}

void* TodAllocator::Calloc(int theItemSize)
{
	void* anItem = Alloc(theItemSize);
	memset(anItem, 0, theItemSize);
	return anItem;
}

void TodAllocator::Free(void* theItem, int theItemSize)
{
	mTotalItems--;
	assert(IsPointerFromAllocator(theItem));
	assert(!IsPointerOnFreeList(theItem));
	*(void**)theItem = mFreeList;  // 将原可用区域头存入 [*theItem] 中
	mFreeList = theItem;  // 将 theItem 设为新的可用区域头
}

void TodAllocator::FreeAll()
{
	for (void* aBlock = mBlockList; aBlock != nullptr; )
	{
		void* aNext = *(void**)aBlock;
		free(aBlock);
		aBlock = aNext;
	}

	mBlockList = nullptr;
	mFreeList = nullptr;
	mTotalItems = 0;
}
