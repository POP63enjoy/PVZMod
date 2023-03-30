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

	/// Plant 魔法成员扩展。
	///
	/// @see MagicPlant_Reference
	namespace MagicPlant
	{
		template <typename BaseClass>
		class RegisterManager
		{
		public:
			template <SeedType thePlantId,typename PlantClass>
			RegisterManager RegisterPlant(InitPatch& patch);
		};

		/// 【补丁函数】为 Plant 扩展魔法成员。
		///
		/// @tparam T		一个继承于 Plant 的类，不允许定义构造函数、析构函数、虚函数。
		/// @param patch	补丁对象。
		template <typename T>
		RegisterManager<T> Extend(InitPatch& patch);

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
