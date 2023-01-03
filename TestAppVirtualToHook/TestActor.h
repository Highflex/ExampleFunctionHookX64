/* practical example of class based structures */

#include <iostream>

class Actor
{
public:
    int SpecialID;

    Actor(int inSpecialID, std::string inActorName, float inHealth) 
    {
        SpecialID = inSpecialID;
        Name = inActorName;
        Health = inHealth;
    }

    virtual void PrintInformation() 
    {
        std::cout << "Debug Info about Actor:\n";
        std::cout << "\n";
        std::cout << "SpecialID: " << SpecialID << "\n";
        std::cout << "Name: " << Name << "\n";
        std::cout << "Health: " << Health << "\n";
        std::cout << "\n";
    }

    virtual void Tick()
    {
        std::cout << Name << " Tick" << "\n";
    }

    virtual void SetName(std::string NewName)
    {
        Name = NewName;
    }

    virtual std::string GetName()
    {
        return Name;
    }

    void TestFunction()
    {
        std::cout << "Called the Test function!!!!!\n";
        std::cout << "Name is: " << GetName() << "\n";
        std::cout << "Health is: " << Health << "\n";
    }

    std::string Name;
    float Health;
};

class Player : public Actor
{
public:
    Player(int inPlayerID) : Actor(99, "Player", 100.0f) {
        PlayerID = inPlayerID;
    }

    virtual void Tick() override
    {
        Actor::Tick();
        std::cout << "Tick Player Additions!" << "\n";
    }

    virtual void PrintInformation() override
    {
        // call super then the custom logic!!!!
        Actor::PrintInformation();

        std::cout << "Debug Info about Player now!!!\n";
        std::cout << "PlayerID: " << PlayerID << "\n";
    }

    void SetPlayerID(int NewPlayerID)
    {
        PlayerID = NewPlayerID;
    }

    int PlayerID;
};

class Enemy : public Actor
{
public:
    Enemy(int inEnemyID) : Actor(98, "Enemy", 100.0f) {
        EnemyID = inEnemyID;
    }

    int EnemyID;

    virtual void PrintInformation() override
    {
        // call super then the custom logic!!!!
        Actor::PrintInformation();

        std::cout << "Debug Info about Enemy now!!!\n";
        std::cout << "EnemyID: " << EnemyID << "\n";
    }

    virtual void Tick() override
    {
        Actor::Tick();
        std::cout << "Tick Enemy Additions!" << "\n";
    }

    void SetEnemyID(int NewEnemyID)
    {
        EnemyID = NewEnemyID;
    }
};


