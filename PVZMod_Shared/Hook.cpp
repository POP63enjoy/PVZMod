#include "Hook.h"
#include <detours.h>
#include <new>

using namespace PVZMod;

Hook::Hook()
{
	mHeap = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE, 0, 0);
}

Hook::~Hook()
{
	HeapDestroy(mHeap);
}

void* Hook::HookFunction(void* pFunction, void* pDetour)
{
	void* pPointer = pFunction;
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&pPointer, pDetour);
	DetourTransactionCommit();
	return pPointer;
}

#pragma pack(push, 1)
struct InsertCodeAsm
{
	char pushad =	'\x60';						// pushad
	char pushfd =	'\x9c';						// pushfd
	char push_esp =	'\x54';						// push esp
	char call =		'\xe8';		int calladdr;	// call addr
	char popfd =	'\x9d';						// popfd
	char popad =	'\x61';						// popad
	char jmp =		'\xe9';		int jmpaddr;	// jmp addr
	char end =		'\xcc';						// int3
};
#pragma pack(pop)

void Hook::InsertCode(void* address, InsertCodeFunc code, int trampolineOffset)
{
	InsertCodeAsm* ica = new (HeapAlloc(mHeap, 0, sizeof(InsertCodeAsm))) InsertCodeAsm;
	ica->calladdr = (int)code - (int)&ica->popfd;
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	void* trampoline = address;
	DetourAttach(&trampoline, ica);
	DetourTransactionCommit();
	ica->jmpaddr = (int)trampoline - (int)&ica->end + trampolineOffset;
}

void Hook::InsertCodeAndJump(void* address, void* jmpAddress, InsertCodeFunc code)
{
	InsertCodeAsm* ica = new (HeapAlloc(mHeap, 0, sizeof(InsertCodeAsm))) InsertCodeAsm;
	ica->calladdr = (int)code - (int)&ica->popfd;
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	void* trampoline = address;
	DetourAttach(&trampoline, ica);
	DetourTransactionCommit();
	ica->jmpaddr = (int)jmpAddress - (int)&ica->end;
}


DWORD Hook::cmp(DWORD num1, DWORD num2)
{
	DWORD result;
	__asm
	{
		mov eax, num2
		cmp num1, eax
		pushfd
		pop result
	}
	return result;
}


DWORD Hook::test(DWORD num1, DWORD num2)
{
	DWORD result;
	__asm
	{
		mov eax, num2
		test num1, eax
		pushfd
		pop result
	}
	return result;
}