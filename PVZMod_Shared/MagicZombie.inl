#pragma once
#ifndef _PVZMOD_MAGIC_ZOMBIE_INL_
#define _PVZMOD_MAGIC_ZOMBIE_INL_

namespace PVZMod
{
	namespace MagicZombie
	{
		namespace __PRIVATE__
		{
			PVZMOD_CHECK_MAGIC_VAR(MC_DATA_ARRAY_SIZE);
		}

		template <typename T>
		void Extend(InitPatch& patch)
		{
			static_assert(std::is_base_of<Zombie, T>::value);
			patch.PatchTask("MagicZombie::Extend", [&]
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
				}, true, true);
		}
	}
}

#endif // !_PVZMOD_MAGIC_ZOMBIE_INL_
