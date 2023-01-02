#include "injector.h"

int main() 
{
	int selection = 1;
	std::cout << "Enter '1' to Inject into TestAppToHook.exe\n";
	std::cout << "Enter '2' to Inject into TestAppToModify.exe\n";
	std::cin >> selection;

	if(selection == 1)
		inject(L"TestAppToHook.exe", L"HookTest01.dll");
	else
		inject(L"TestAppToModify.exe", L"ModifyTest01.dll");

	std::cout << "DLL Injected!\n";
	return getchar();
}
