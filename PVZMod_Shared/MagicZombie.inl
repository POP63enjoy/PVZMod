#pragma once
#ifndef _PVZMOD_MAGIC_ZOMBIE_INL_
#define _PVZMOD_MAGIC_ZOMBIE_INL_

namespace PVZMod
{
	namespace MagicZombie
	{
		namespace __PRIVATE__
		{
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombieInitialize_InitMemberVariable);
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombieInitialize_InitReanimation);
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombieInitialize_InitType);
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombieInitialize_AfterInitType);

			PVZMOD_CHECK_MAGIC_VAR(MC_DATA_ARRAY_SIZE);
		}

		template <typename T>
		RegisterManager<T> Extend(InitPatch& patch)
		{
			static_assert(std::is_base_of<Zombie, T>::value);
			patch.PatchTask("MagicZombie::ExtendZombie", [&]
				{
					using namespace __PRIVATE__;

					{
						size_t dataArraySize = 1024;
						PVZMOD_MAGIC_SVAR(MC_DATA_ARRAY_SIZE, const size_t, T,
							{
								dataArraySize = T::MC_DATA_ARRAY_SIZE;
							});
						Binding_ExtendBase(patch, sizeof(T), dataArraySize);
					}

					PVZMOD_MAGIC_FUNC(MF_ZombieInitialize_InitMemberVariable, ZombieDefinition & (int theRow, ZombieType theType, bool theVariant, Zombie * theParentZombie, int theFromWave, ZombieInitialize_InitMemberVariable_t & base), T,
						{
							Binding_MF_ZombieInitialize_InitMemberVariable(patch, [](Zombie* _this, int theRow, ZombieType theType, bool theVariant, Zombie* theParentZombie, int theFromWave, ZombieInitialize_InitMemberVariable_t& base) -> ZombieDefinition&
								{
									return ((T*)_this)->MF_ZombieInitialize_InitMemberVariable(theRow, theType, theVariant, theParentZombie, theFromWave, base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_ZombieInitialize_InitReanimation, void(ZombieDefinition & theZombieDef, ZombieInitialize_InitReanimation_t & base), T,
						{
							Binding_MF_ZombieInitialize_InitReanimation(patch, [](Zombie* _this, ZombieDefinition& theZombieDef, ZombieInitialize_InitReanimation_t& base)
								{
									((T*)_this)->MF_ZombieInitialize_InitReanimation(theZombieDef, base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_ZombieInitialize_InitType, void(ZombieDefinition & theZombieDef, Zombie * theParentZombie, RenderLayer & theRenderLayer, int& theRenderOffset, ZombieInitialize_InitType_t & base), T,
						{
							Binding_MF_ZombieInitialize_InitType(patch, [](Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer& theRenderLayer, int& theRenderOffset, ZombieInitialize_InitType_t& base)
								{
									((T*)_this)->MF_ZombieInitialize_InitType(theZombieDef, theParentZombie, theRenderLayer, theRenderOffset, base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_ZombieInitialize_AfterInitType, void(ZombieDefinition & theZombieDef, Zombie * theParentZombie, RenderLayer theRenderLayer, int theRenderOffset, ZombieInitialize_AfterInitType_t & base), T,
						{
							Binding_MF_ZombieInitialize_AfterInitType(patch, [](Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer theRenderLayer, int theRenderOffset, ZombieInitialize_AfterInitType_t& base)
								{
									((T*)_this)->MF_ZombieInitialize_AfterInitType(theZombieDef, theParentZombie, theRenderLayer, theRenderOffset, base);
								});
						});
				}, true, true);

			return {};
		}

		template<typename BaseClass>
		template<ZombieType theZombieId, typename ZombieClass>
		RegisterManager<BaseClass> RegisterManager<BaseClass>::RegisterZombie(InitPatch& patch)
		{
			static_assert(std::is_base_of<BaseClass, ZombieClass>::value);
			static_assert(sizeof(BaseClass) == sizeof(ZombieClass));
			patch.PatchTask("MagicZombie::RegisterManager::RegisterZombie", [&]
				{
					using namespace __PRIVATE__;

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_ZombieInitialize_InitMemberVariable, ZombieDefinition & (int theRow, ZombieType theType, bool theVariant, Zombie * theParentZombie, int theFromWave, ZombieInitialize_InitMemberVariable_t & base), ZombieClass, BaseClass,
						{
							Binding_MF_ZombieInitialize_InitMemberVariable(patch, [](Zombie* _this, int theRow, ZombieType theType, bool theVariant, Zombie* theParentZombie, int theFromWave, ZombieInitialize_InitMemberVariable_t& base)->ZombieDefinition&
								{
									if (theType == theZombieId)
										return ((ZombieClass*)_this)->MF_ZombieInitialize_InitMemberVariable(theRow, theType, theVariant, theParentZombie, theFromWave, base);
									else
										return base();
								});
						});

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_ZombieInitialize_InitReanimation, void(ZombieDefinition & theZombieDef, ZombieInitialize_InitReanimation_t & base), ZombieClass, BaseClass,
						{
							Binding_MF_ZombieInitialize_InitReanimation(patch, [](Zombie* _this, ZombieDefinition& theZombieDef, ZombieInitialize_InitReanimation_t& base)
								{
									if (_this->mZombieType == theZombieId)
										((ZombieClass*)_this)->MF_ZombieInitialize_InitReanimation(theZombieDef, base);
									else
										base();
								});
						});

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_ZombieInitialize_InitType, void(ZombieDefinition & theZombieDef, Zombie * theParentZombie, RenderLayer & theRenderLayer, int& theRenderOffset, ZombieInitialize_InitType_t & base), ZombieClass, BaseClass,
						{
							Binding_MF_ZombieInitialize_InitType(patch, [](Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer& theRenderLayer, int& theRenderOffset, ZombieInitialize_InitType_t& base)
								{
									if (_this->mZombieType == theZombieId)
										((ZombieClass*)_this)->MF_ZombieInitialize_InitType(theZombieDef, theParentZombie, theRenderLayer, theRenderOffset, base);
									else
										base();
								});
						});

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_ZombieInitialize_AfterInitType, void(ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer theRenderLayer, int theRenderOffset, ZombieInitialize_AfterInitType_t& base), ZombieClass, BaseClass,
						{
							Binding_MF_ZombieInitialize_AfterInitType(patch, [](Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer theRenderLayer, int theRenderOffset, ZombieInitialize_AfterInitType_t& base)
								{
									if (_this->mZombieType == theZombieId)
										((ZombieClass*)_this)->MF_ZombieInitialize_AfterInitType(theZombieDef, theParentZombie, theRenderLayer, theRenderOffset, base);
									else
										base();
								});
						});
				}, false);
			return {};
		}
	}
}

#endif // !_PVZMOD_MAGIC_ZOMBIE_INL_
