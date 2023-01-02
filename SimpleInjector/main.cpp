#include "injector.h"

int main() 
{
	inject(L"TestAppToHook.exe", L"HookTest01.dll");
	return getchar();
}
