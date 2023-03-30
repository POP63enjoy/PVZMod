#include "PVZMod.h"
#include "MagicZombie.h"
#include "Board.h"

using namespace PVZMod;

void MagicZombie::Binding_ExtendBase(InitPatch& patch, size_t theZombieSize, size_t theDataArraySize)
{
	patch.PatchTask("MagicZombie::Binding_ExtendBase", [&]
		{
			*(size_t*)0x40928a = theZombieSize * theDataArraySize;
			if (theDataArraySize != 1024)
			{
				static size_t _theDataArraySize = theDataArraySize;
				patch.mHook.InsertCode((void*)0x4092b2, [](Hook::Regs* regs)
					{
						*(size_t*)(regs->ebp + 0x98) = _theDataArraySize;
					});
			}
			Board::gExtraZombieSize = theZombieSize - sizeof(Zombie);
			if (theZombieSize != sizeof(Zombie))
			{
				static const DWORD addresslist[] = {
					//Í¼¼ø
					0x00402A79,
					0x00403039,
					//Board::ProcessDeleteQueue
					0x0041D4F6,
					0x0041D508,
					0x0041D514,
					0x0041D51C,
					0x0041D592,
					0x0041D5A4,
					//DataArray<Zombie>::DataArrayTryToGet
					0x0041E194,
					0x0041E1A2,
					//Board::IterateZombies,
					0x0041E295,
					0x0041E2A1,
					0x0041E2B2,
					0x0041E2B9,
					//DataArray<Zombie>::DataArrayAlloc
					0x0041F72D,
					0x0041F734,
					0x0041F73F,
					0x0041F746,
					0x0041F75C,
					//DataArray<Zombie>::DataArrayTryToGet
					0x0041F7A1,
					0x0041F7AB,
					//DataArray<Zombie>::DataArrayFreeAll
					0x00420130,
					0x00420139,
					0x00420145,
					0x00420154,
					0x0042015C,
					0x004201BE,
					0x004201CA,
					//Plant::UpdateTanglekelp
					0x004639D4,
					0x00463A0A,
					0x00463A14,
					0x00463B48,
					0x00463B52,
					//Plant::FindSquashTarget
					0x004641C2,
					//Plant::UpdateSquash
					0x0046424A,
					//Plant::Fire
					0x0046ABEC,
					//Plant::Die
					0x0046B237,
					0x0046B23F,
					//Projectile::UpdateNormalMotion
					0x004713E6,
					0x004713F0,
					//FixBoardAfterLoad
					0x00485A84,
					0x00485A90,
					0x00485AA2,
					0x00485AAA,
					//SyncDataArray<Zombie>
					0x0048603E,
					//Zombie::ZombieInitialize
					0x00527509,
					0x00527516,
					//Zombie::BungeeDropZombie
					0x00528E7D,
					//Zombie::IsTanglekelpTarget
					0x0052A632,
					//Zombie::BobsledCrash
					0x0052C428,
					//Zombie::UpdateZombieBobsled
					0x0052C50C,
					//Zombie::SummonBackupDancer
					0x0052CCFB,
					0x0052CDCF,
					//Zombie::SummonBackupDancers
					0x0052CE21,
					0x0052CE29,
					//Zombie::NeedsMoreBackupDancers
					0x0052CEE8,
					0x0052CEF4,
					//Zombie::DrawBobsledReanim
					0x00530B8D,
					//Zombie::DrawBungeeReanim
					0x00530F99,
					0x00530FA7,
					//Zombie::IsMovingAtChilledSpeed
					0x005333D0,
					0x005333DA,
					0x00533414,
					0x0053341C,
					//Zombie::StartMindControlled
					0x00533F3B,
					0x00533F43,
					0x00533F4C,
					0x00533F8E,
					0x00533F96,
					//Zombie::BobsledDie
					0x005347B7,
					0x005347ED,
					//Zombie::BobsledBurn
					0x00534836,
					0x00534861,
					//Zombie::BungeeDie
					0x00534950,
					0x00534958,
					//Zombie::IsTanglekelpTarge
					0x00536956,
					//Zombie::GetBobsledPosition
					0x00538B33,
					0x00538B41,
					//Zombie::BossBungeeSpawn
					0x005396F0,
					//Zombie::BossBungeeLeave
					0x0053975A,
					0x00539764,
					//Zombie::BossAreBungeesDone
					0x005397D6,
					0x005397DE
				};
				for (DWORD addr : addresslist)
				{
					DWORD* addrwrite = (DWORD*)addr;
					*addrwrite += theZombieSize - sizeof(Zombie);
				}
			}
		}, true, true);
}
