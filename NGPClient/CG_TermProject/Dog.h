#pragma once

#include "Head.h"
#include "Nose.h"
#include "Body.h"
#include "Arm.h"
#include "Leg.h"
#include "Eyes.h"
#include "Ear.h"
#include "Beard.h"
#include "sword.h"
#include "Hero.h"

#include "Gun.h"
#include "particle.h"

extern Hero hero[3];


class Dog
{
	Head head;
	Nose nose;
	Body body;
	Arm armL;
	Arm armR;
	Leg legL;
	Leg legR;
	Eyes eyesL;
	Eyes eyesR;
	Ear earL;
	Ear earR;
	Beard beardvertical;
	Beard beardhorizon;
	Sword swordR;
	Sword swordL;

	int Attack;
	glm::vec3 Position;
	float Direction;

	float closelineX;
	float closelineZ;


public:
	Dog();
	~Dog();
	int HP;

	int Index = 0;
	void draw();
	void update();
	void doginfo(SC_MONSTER_PACKET* p);
	float getLeft();
	float getRight();
	float getBehind();
	float getFront();
	float getBottom();
	float getTop();
	void initDog();
};

