#pragma once
#include "pch.h"



//extern CatAttack catattack[AnimCnt];
//extern DogAttack dogattack[AnimCnt];
//extern BearAttack bearattack;

class Hero
{
	int HP;
	bool firstmap;
	/// <summary>
	/// ī�޶� �����մϴ�.
	/// </summary>
	float VAngleX = 0;
	float VAngleY = 0;



public:
	float PosX;
	float PosY;
	float PosZ;
	float lightColorR = 1.0f;
	float lightColorG = 1.0f;
	float lightColorB = 1.0f;
	Hero();
	~Hero();
	void ISW();
	void ISA();
	void ISS();
	void ISD();
	void damage();
	void Update();
	int InfoHP();
	void location();
	float getLeft();
	float getRight();
	float getBehind();
	float getFront();
	void VAngleMotion(int x, int y);
	void initHero();

	/*friend void HeroVSDog();
	friend void HeroVSBear();
	friend void HeroVSCat();*/
	///////////////ī�޶� �����մϴ�.///////////////

};