#pragma once

#error 本文件仅用于参考，不要包含

#include "MagicZombie.h"
#include "Zombie.h"

namespace PVZMod
{
	/// MagicZombie 魔法成员参考。
	class MagicZombie_Reference :public Zombie
	{
	public:
		/// 僵尸 DataArray 大小。
		static const size_t MC_DATA_ARRAY_SIZE;
	};
}