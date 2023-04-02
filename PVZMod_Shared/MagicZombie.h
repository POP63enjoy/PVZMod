#pragma once
#ifndef _PVZMOD_MAGIC_ZOMBIE_H_
#define _PVZMOD_MAGIC_ZOMBIE_H_

#include "Magic.h"

namespace PVZMod
{
	class InitPatch;
	class Zombie;
	class ZombieDefinition;
	enum ZombieType;

	/// Zombie 魔法成员扩展。
	///
	/// @see MagicZombie_Reference
	namespace MagicZombie
	{
		template <typename BaseClass>
		class RegisterManager
		{
		public:
			template <ZombieType theZombieId, typename ZombieClass>
			RegisterManager RegisterZombie(InitPatch& patch);
		};

		/// 【补丁函数】为 Zombie 扩展魔法成员。
		///
		/// @tparam T		一个继承于 Zombie 的类，不允许定义构造函数、析构函数、虚函数。
		/// @param patch	补丁对象。
		template <typename T>
		RegisterManager<T> Extend(InitPatch& patch);

		void Binding_ExtendBase(InitPatch& patch, size_t theZombieSize, size_t theDataArraySize);

		using ZombieInitialize_InitMemberVariable_t = Magic::BaseFunction<ZombieDefinition& (Zombie* _this, int theRow, ZombieType theType, bool theVariant, Zombie* theParentZombie, int theFromWave)>;
		void Binding_MF_ZombieInitialize_InitMemberVariable(InitPatch& patch, const std::function<ZombieDefinition& (Zombie* _this, int theRow, ZombieType theType, bool theVariant, Zombie* theParentZombie, int theFromWave, ZombieInitialize_InitMemberVariable_t& base)>& func);
	}
}

#include "MagicZombie.inl"

#endif // !_PVZMOD_MAGIC_ZOMBIE_H_
