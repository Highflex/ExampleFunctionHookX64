#include "injector.h"

int main() 
{
	int selection = 1;
	std::cout << "Enter '1' to Inject into TestAppToHook.exe\n";
	std::cout << "Enter '2' to Inject into TestAppToModify.exe\n";
	std::cout << "Enter '3' to Inject into TestAppVirtualToHook.exe\n";
	std::cin >> selection;

	switch (selection)
	{
		case 1:
			inject(L"TestAppToHook.exe", L"HookTest01.dll");
			break;
		case 2:
			inject(L"TestAppToModify.exe", L"ModifyTest01.dll");
			break;
		case 3:
			inject(L"TestAppVirtualToHook.exe", L"HookVirtualTest01.dll");
		default:
			break;
	}

	std::cout << "DLL Injected!\n";
	return getchar();
}
