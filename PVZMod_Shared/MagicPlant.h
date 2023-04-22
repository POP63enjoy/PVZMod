#pragma once
#ifndef _PVZMOD_MAGIC_PLANT_H_
#define _PVZMOD_MAGIC_PLANT_H_

#ifndef _PVZMOD_PLANT_H_
#error 必须在 #include <MagicPlant.h> 之前 #include <Plant.h> 。
#endif // !_PVZMOD_BOARD_H_

#include "Magic.h"

namespace PVZMod
{
	class InitPatch;
	class Plant;
	class PlantDefinition;
	class Reanimation;
	enum SeedType;

	/// `Plant` 魔法成员扩展。
	namespace MagicPlant
	{
		/// 子魔法类注册管理器。
		template <typename BaseClass>
		class RegisterManager
		{
		public:
			/// 【补丁函数】注册以植物类型为判断条件的子魔法类。
			///
			/// @tparam PlantClass				子魔法类，继承于 BaseClass，不允许定义构造函数、析构函数、虚函数、非静态成员变量。
			/// @param patch					补丁对象。
			/// @param thePlantId				植物编号。
			/// @param enableMultipleRegister	为 true 则允许重复注册相同的类。（不包括通过 MT_Ref 引用的类）
			template <typename PlantClass>
			RegisterManager RegisterPlant(InitPatch& patch, SeedType thePlantId, bool enableMultipleRegister = false);
		};

		/// 【补丁函数】为 Plant 注册主魔法类。
		///
		/// @tparam T		主魔法类，继承于 Plant，不允许定义构造函数、析构函数、虚函数。
		/// @param patch	补丁对象。
		/// @return			用于注册子魔法类。
		template <typename T>
		RegisterManager<T> RegisterMain(InitPatch& patch);

		void Binding_ExtendBase(InitPatch& patch, size_t thePlantSize, size_t theDataArraySize);

		using PlantInitialize_InitMemberVariable_t = Magic::BaseFunction<PlantDefinition& (Plant* _this, int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType)>;
		void Binding_MF_PlantInitialize_InitMemberVariable(InitPatch& patch, const std::function<PlantDefinition& (Plant* _this, int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType, PlantInitialize_InitMemberVariable_t& base)>& func);

		using PlantInitialize_InitReanimation = Magic::BaseFunction<Reanimation* (Plant* _this, PlantDefinition& thePlantDef)>;
		void Binding_MF_PlantInitialize_InitReanimation(InitPatch& patch, const std::function<Reanimation* (Plant* _this, PlantDefinition& thePlantDef, PlantInitialize_InitReanimation& base)>& func);

		using PlantInitialize_BeforeInitType = Magic::BaseFunction<void(Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim)>;
		void Binding_MF_PlantInitialize_BeforeInitType(InitPatch& patch, const std::function<void(Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_BeforeInitType& base)>& func);

		using PlantInitialize_InitType = Magic::BaseFunction<void(Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim)>;
		void Binding_MF_PlantInitialize_InitType(InitPatch& patch, const std::function<void(Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_InitType& base)>& func);

		using PlantInitialize_AfterInitType = Magic::BaseFunction<void(Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim)>;
		void Binding_MF_PlantInitialize_AfterInitType(InitPatch& patch, const std::function<void(Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_AfterInitType& base)>& func);
	}
}

#include "MagicPlant.inl"

#endif // !_PVZMOD_MAGIC_PLANT_H_
