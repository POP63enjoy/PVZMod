#include "Buffer.h"

using namespace PVZMod;

void Buffer::WriteByte(uint8_t theByte)
{
	if (mWriteBitPos % 8 == 0)
		mData.push_back((char)theByte);
	else
	{
		int anOfs = mWriteBitPos % 8;
		mData[mWriteBitPos / 8] |= theByte << anOfs;
		mData.push_back((char)(theByte >> (8 - anOfs)));
	}

	mWriteBitPos += 8;
	if (mWriteBitPos > mDataBitSize)
		mDataBitSize = mWriteBitPos;
}

void Buffer::WriteLong(long theLong)
{
	WriteByte((uint8_t)theLong);
	WriteByte((uint8_t)(theLong >> 8));
	WriteByte((uint8_t)(theLong >> 16));
	WriteByte((uint8_t)(theLong >> 24));
}

long Buffer::ReadLong() const
{
	long aLong = ReadByte();
	aLong |= ((long)ReadByte()) << 8;
	aLong |= ((long)ReadByte()) << 16;
	aLong |= ((long)ReadByte()) << 24;

	return aLong;
}

uint8_t Buffer::ReadByte() const
{
	if ((mReadBitPos + 7) / 8 >= (int)mData.size())
	{
		return 0; // Underflow
	}

	if (mReadBitPos % 8 == 0)
	{
		uint8_t b = mData[mReadBitPos / 8];
		mReadBitPos += 8;
		return b;
	}
	else
	{
		int anOfs = mReadBitPos % 8;

		uint8_t b = 0;

		b = mData[mReadBitPos / 8] >> anOfs;
		b |= mData[(mReadBitPos / 8) + 1] << (8 - anOfs);

		mReadBitPos += 8;

		return b;
	}
}
