#pragma once
#ifndef _PVZMOD_HOOK_H_
#define _PVZMOD_HOOK_H_

#include <Windows.h>

namespace PVZMod
{
	/// 提供基本的函数替换和插入代码操作。
	class Hook
	{
	private:
		HANDLE mHeap;
	public:
		Hook();
		~Hook();
		
		/// 替换函数。
		///
		/// @param pFunction	要替换的函数的指针。
		/// @param pDetour		替换成此指针指向的函数。
		/// @return				用于调用原始函数的指针。
		void* HookFunction(void* pFunction, void* pDetour);

		/// 寄存器结构。
		struct Regs
		{
			DWORD efl;
			DWORD edi;
			DWORD esi;
			DWORD ebp;
			DWORD esp;
			DWORD ebx;
			DWORD edx;
			DWORD ecx;
			DWORD eax;
		};

		/// 插入代码的函数类型。
		using InsertCodeFunc = void(__stdcall*)(Regs*);

		/// 插入代码。
		///
		/// 将在指定位置插入 jmp 指令跳转到被插入的代码，并备份 jmp 覆盖掉的指令到另一区域，执行完插入的代码后返回到备份的指令处，再跳回原来的地址。
		/// 
		/// @param address				插入的地址。
		/// @param code					插入的代码。
		/// @param trampolineOffset		返回到备份的指令处时偏移的字节。
		void InsertCode(void* address, InsertCodeFunc code, int trampolineOffset = 0);

		/// 插入代码，执行后跳转到指定地址。
		/// 
		/// 将在指定位置插入 jmp 指令跳转到被插入的代码，执行完插入的代码后跳转到指定位置。
		/// 
		/// @param address				插入的地址。
		/// @param jmpAddress			跳回的地址。
		/// @param code					插入的代码。
		void InsertCodeAndJump(void* address, void* jmpAddress, InsertCodeFunc code);

		/// 执行汇编 cmp 指令的操作。
		/// 
		/// @param num1	第一操作数。
		/// @param num2	第二操作数。
		/// @return		执行后 efl 寄存器的值。
		static DWORD cmp(DWORD num1, DWORD num2);

		/// 执行汇编 test 指令的操作。
		/// 
		/// @param num1	第一操作数。
		/// @param num2	第二操作数。
		/// @return		执行后 efl 寄存器的值。
		static DWORD test(DWORD num1, DWORD num2);
	};
}

#endif // !_PVZMOD_HOOK_H_
