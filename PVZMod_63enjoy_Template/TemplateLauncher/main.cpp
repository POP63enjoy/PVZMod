#include <Windows.h>
#include <detours.h>
#include <tchar.h>

#define EXENAME TEXT("PlantsVsZombies.exe")
#define DLLPATH "../"
#define EXEPATH TEXT("./game/")

#ifdef _DEBUG
#	ifdef _WIN64	// 仅保留 64 位启动器配置，实际并不支持 64 位，Windows 平台上并没有 64 位版本的 PVZ。
#		define DLLNAME "$ext_projectname$64_d.dll"
#	else
#		define DLLNAME "$ext_projectname$_d.dll"
#	endif
#else
#	ifdef _WIN64
#		define DLLNAME "$ext_projectname$64.dll"
#	else
#		define DLLNAME "$ext_projectname$.dll"
#	endif
#endif

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PTSTR pCmdLine, int nCmdShow)
{
	const char* dllName = DLLPATH DLLNAME;

	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi = { 0 };

	if (!DetourCreateProcessWithDlls(EXEPATH EXENAME, pCmdLine, nullptr, nullptr, FALSE, 0, nullptr, EXEPATH, &si, &pi, 1, &dllName, nullptr))
	{
		MessageBox(nullptr, TEXT("DetourCreateProcessWithDlls failed"), TEXT("Error"), MB_ICONERROR);
		return 1;
	}

	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return 0;
}
