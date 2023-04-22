#pragma once
#ifndef _PVZMOD_BUFFER_H_
#define _PVZMOD_BUFFER_H_

#include "PVZSTL.h"

namespace PVZMod
{
	typedef Vector<uint8_t> ByteVector;

	/// 【游戏类】缓冲区。（原 `Sexy::Buffer`）
	class Buffer
	{
	public:
		ByteVector				mData;
		int						mDataBitSize;
		mutable int				mReadBitPos;
		mutable int				mWriteBitPos;

	public:
		Buffer();
		virtual ~Buffer();

		void					SeekFront() const;
		void					Clear();

		void					FromWebString(const String& theString);
		void					WriteByte(uint8_t theByte);
		void					WriteNumBits(int theNum, int theBits);
		static int				GetBitsRequired(int theNum, bool isSigned);
		void					WriteBoolean(bool theBool);
		void					WriteShort(short theShort);
		void					WriteLong(long theLong);
		void					WriteString(const String& theString);
		void					WriteUTF8String(const WString& theString);
		void					WriteLine(const String& theString);
		void					WriteBuffer(const ByteVector& theBuffer);
		void					WriteBytes(const uint8_t* theByte, int theCount);
		void					SetData(const ByteVector& theBuffer);
		void					SetData(uint8_t* thePtr, int theCount);

		String					ToWebString() const;
		WString					UTF8ToWideString() const;
		uint8_t					ReadByte() const;
		int						ReadNumBits(int theBits, bool isSigned) const;
		bool					ReadBoolean() const;
		short					ReadShort() const;
		long					ReadLong() const;
		String					ReadString() const;
		WString					ReadUTF8String() const;
		String					ReadLine() const;
		void					ReadBytes(uint8_t* theData, int theLen) const;
		void					ReadBuffer(ByteVector* theByteVector) const;

		const uint8_t*			GetDataPtr() const;
		int						GetDataLen() const;
		int						GetDataLenBits() const;
		uint32_t				GetCRC32(uint32_t theSeed = 0) const;

		bool					AtEnd() const;
		bool					PastEnd() const;
	};
}

#endif // !_PVZMOD_BUFFER_H_
