// TestAppVirtualToHook.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>
#include <vector>

// include custom test class
#include "TestActor.h"

void ConstructAndFillDefaultData(std::vector<Actor*>& OutData)
{
    Actor* TestActor01 = new Actor(1, "TestActor01", 100.0f);
    TestActor01->TestFunction();
    Actor* TestActor02 = new Actor(2, "TestActor02", 100.0f);
    Actor* TestActor03 = new Actor(3, "TestActor03", 100.0f);
    Player* TestPlayer01 = new Player(34);
    Enemy* TestEnemy01 = new Enemy(22);
    OutData.push_back(TestActor01);
    OutData.push_back(TestActor02);
    OutData.push_back(TestActor03);
    OutData.push_back(TestPlayer01);
    OutData.push_back(TestEnemy01);
}

int main()
{
    // build default test data
    std::vector<Actor*> ActorContainer;
    ConstructAndFillDefaultData(ActorContainer);

    // main loop
    for (;;)
    {
        // iterate actor container and call tick for each object
        for (auto& element : ActorContainer) {
            element->Tick();
        }

        std::cout << "\n";
        Sleep(1000);
    }

    return 0;
}

