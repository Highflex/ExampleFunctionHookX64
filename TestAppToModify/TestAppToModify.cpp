// TestAppToModify.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>

/* the status to use when compiled */
int status = 1;

int main()
{
    // run loop
    for (;;)
    {
        Sleep(500);

        if (status == 1)
        {
            std::cout << "Not modified yet!\n";
        }
        else
        {
            std::cout << "Modified the App!\n";
        }
    }
}