#pragma once
#ifndef _PVZMOD_MAGIC_ZOMBIE_H_
#define _PVZMOD_MAGIC_ZOMBIE_H_

#ifndef _PVZMOD_ZOMBIE_H_
#error 必须在 #include <MagicZombie.h> 之前 #include <Zombie.h> 。
#endif // !_PVZMOD_BOARD_H_

#include "Magic.h"

namespace PVZMod
{
	class InitPatch;
	class Zombie;
	class ZombieDefinition;
	enum RenderLayer;
	enum ZombieType;

	/// `Zombie` 魔法成员扩展。
	namespace MagicZombie
	{
		/// 子魔法类注册管理器。
		template <typename BaseClass>
		class RegisterManager
		{
		public:
			/// 【补丁函数】注册以僵尸类型为判断条件的子魔法类。
			///
			/// @tparam ZombieClass				子魔法类，继承于 BaseClass，不允许定义构造函数、析构函数、虚函数、非静态成员变量。
			/// @param patch					补丁对象。
			/// @param theZombieId				僵尸编号。
			/// @param enableMultipleRegister	为 true 则允许重复注册相同的类。（不包括通过 MT_Ref 引用的类）
			template <typename ZombieClass>
			RegisterManager RegisterZombie(InitPatch& patch, ZombieType theZombieId, bool enableMultipleRegister = false);
		};

		/// 【补丁函数】为 Zombie 注册主魔法类。
		///
		/// @tparam T		主魔法类，继承于 Zombie，不允许定义构造函数、析构函数、虚函数。
		/// @param patch	补丁对象。
		/// @return			用于注册子魔法类。
		template <typename T>
		RegisterManager<T> RegisterMain(InitPatch& patch);

		////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////

		// 基本信息绑定 & 对象上限 - MC_DATA_ARRAY_SIZE

		void Binding_ExtendBase(InitPatch& patch, size_t theZombieSize, size_t theDataArraySize);

		// 初始化 - MF_ZombieInitialize

		using ZombieInitialize_InitMemberVariable_t = Magic::BaseFunction<ZombieDefinition& (Zombie* _this, int theRow, ZombieType theType, bool theVariant, Zombie* theParentZombie, int theFromWave)>;
		void Binding_MF_ZombieInitialize_InitMemberVariable(InitPatch& patch, const std::function<ZombieDefinition& (Zombie* _this, int theRow, ZombieType theType, bool theVariant, Zombie* theParentZombie, int theFromWave, ZombieInitialize_InitMemberVariable_t& base)>& func);

		using ZombieInitialize_InitReanimation_t = Magic::BaseFunction<void(Zombie* _this, ZombieDefinition& theZombieDef)>;
		void Binding_MF_ZombieInitialize_InitReanimation(InitPatch& patch, const std::function<void(Zombie* _this, ZombieDefinition& theZombieDef, ZombieInitialize_InitReanimation_t& base)>& func);
		
		using ZombieInitialize_InitType_t = Magic::BaseFunction<void(Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer& theRenderLayer, int& theRenderOffset)>;
		void Binding_MF_ZombieInitialize_InitType(InitPatch& patch, const std::function<void(Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer& theRenderLayer, int& theRenderOffset, ZombieInitialize_InitType_t& base)>& func);

		using ZombieInitialize_AfterInitType_t = Magic::BaseFunction<void(Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer theRenderLayer, int theRenderOffset)>;
		void Binding_MF_ZombieInitialize_AfterInitType(InitPatch& patch, const std::function<void(Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer theRenderLayer, int theRenderOffset, ZombieInitialize_AfterInitType_t& base)>& func);
	}
}

#include "MagicZombie.inl"

#endif // !_PVZMOD_MAGIC_ZOMBIE_H_
