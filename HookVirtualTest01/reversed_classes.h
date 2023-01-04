/* ReClass.Net was used to reverse the structure after looking at the captured instance pointer! */
#include <iostream>
#include <psapi.h>
#include <Windows.h>

#pragma pack(1)

class std_string_rev
{
public:
	char* dataPtr; //0x0000
	char dataArray[16]; //0x0008
	int64_t dataLength; //0x0018
	int64_t dataMaxLength; //0x0020
}; //Size: 0x0028
static_assert(sizeof(std_string_rev) == 0x28);

class Actor
{
public:
	int32_t SpecialID; //0x0008
	char Pad01[4]; //0x000C
	class std_string_rev Name; //0x0010
	float Health; //0x0038

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
}; //Size: 0x003C
static_assert(sizeof(Actor) == 0x3C);

class Player : public Actor
{
public:
	char Pad01[4]; //0x003C
	int32_t PlayerID; //0x0040
}; //Size: 0x0044
static_assert(sizeof(Player) == 0x44);

class Enemy : public Actor
{
public:
	char Pad01[4]; //0x003C
	int32_t EnemyID; //0x0040
}; //Size: 0x0044
static_assert(sizeof(Enemy) == 0x44);