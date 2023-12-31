#include "pch.h"
#include <numeric>
#include <limits>
#include <random>
extern vector<Hero> heroes; 


extern bool g_catlive;
extern bool g_doglive;
extern bool g_bearlive;
extern bool g_herodead;

extern int AnimalCnt;


Animal::Animal(int type, int id) : AnimalType(type),Index(id)
{

	random_device rd;
	default_random_engine dre(rd());
	if (type == Cat) {
		uniform_real_distribution<float> urdX{ -104,-97 };
		uniform_real_distribution<float> urdZ{ -3, 3 };
		PosX = urdX(dre);
		PosY = -1.0f;
		PosZ = urdZ(dre);
		HP = 20;
		Attack = 10;	
		if (AnimalCnt == AnimalMax) { 
			AnimalCnt = 0;
		}

	}
	else if (type == Dog) {
		uniform_real_distribution<float> urdX{ 97, 103 };
		uniform_real_distribution<float> urdZ{ -3, 3 };
		PosX = urdX(dre);
		PosY = -1.0f;
		PosZ = urdZ(dre);
		HP = 40;
		Attack = 20;
		if (AnimalCnt == AnimalMax) { 
			AnimalCnt = 0;
		}
	}
	else if (type == Bear) {
		PosX = 0;
		PosY = -1.0f;
		PosZ = -100.f;
		HP = 100;
		Attack = 30;
	}
	Direction = 0.f;
	AnimalCrushHero = false;


}
float Animal::calculateDistance(float targetX, float targetZ)
{
    float dz = targetZ - PosZ;
    float dx = targetX - PosX;
    return sqrt(dz * dz + dx * dx);
}

void Animal::update()
{
    float closestDistance = 3.40282e+38;
    int closestHeroIndex = -1;

    for (int i = 0; i < heroes.size(); ++i) {
        if (heroes[i]._flag) {
            float distance = calculateDistance(heroes[i].getPosX(), heroes[i].getPosZ());
            if (distance < closestDistance) {
                closestDistance = distance;
                closestHeroIndex = i;
            }
        }

    }

    heroes[closestHeroIndex].location();
    float dz = HeroLocationZ - PosZ;
    float dx = HeroLocationX - PosX;

    Direction = atan2(dx, dz);

    closelineX = HeroLocationX - PosX;
    closelineZ = HeroLocationZ - PosZ;

    if ((g_catlive && heroes[closestHeroIndex]._flag && AnimalType == Cat && closestHeroIndex != -1) || (g_doglive && heroes[closestHeroIndex]._flag && AnimalType == Dog &&closestHeroIndex != -1) ||
        (g_bearlive && heroes[closestHeroIndex]._flag && AnimalType == Bear&& closestHeroIndex != -1)) {

        if (!(closelineX <= 0.5 && closelineX >= -0.5)) {

            if (closelineX >= 0.5) {
                closelineX -= 0.01;
                PosX += 0.01;
            }
            if (closelineX < -0.5) {
                closelineX += 0.01;
                PosX -= 0.01;
            }
        }

        if (!(closelineZ <= 0.5 && closelineZ >= -0.5)) {
            if (closelineZ > 0.5) {
                closelineZ -= 0.01;
                PosZ += 0.01;
            }
            if (closelineZ < -0.5) {
                closelineZ += 0.01;
                PosZ -= 0.01;
            }

        }

    }

    if ((closelineX <= 0.5 && closelineX >= -0.5) && (closelineZ <= 0.5 && closelineZ >= -0.5)) {
        if (AnimalType == Cat) {
            if (this->HP > 0) {
                AnimalCrushHero = true;
                heroes[closestHeroIndex].catattack[Index].Activate = true;
                ++heroes[closestHeroIndex].catattack[Index].AttackCount;
            }
       
        }
        if (AnimalType == Dog) {
            if (this->HP > 0) {
                AnimalCrushHero = true;
                heroes[closestHeroIndex].dogattack[Index].Activate = true;
                ++heroes[closestHeroIndex].dogattack[Index].AttackCount;
            }
           
        }
        if (AnimalType == Bear) {
            if (this->HP > 0) {
                AnimalCrushHero = true;
                heroes[closestHeroIndex].bearattack.Activate = true;
                ++(heroes[closestHeroIndex].bearattack.AttackCount);
            }
           
        }
    }
    else {
        if (AnimalType == Cat) {
            AnimalCrushHero = false;
            heroes[closestHeroIndex].catattack[Index].Activate = false;
        }
        if (AnimalType == Dog) {
            AnimalCrushHero = false;
            heroes[closestHeroIndex].dogattack[Index].Activate = false;
        }
        if (AnimalType == Bear) {
            AnimalCrushHero = false;
            heroes[closestHeroIndex].bearattack.Activate = false;
        }
    }

}


Animal::~Animal()
{

}


void Animal::damage()
{
	HP -= 10;

}

float Animal::getLeft()
{
	return PosX - 0.12f;
}

float Animal::getRight()
{
	return PosX + 0.12f;
}

float Animal::getBehind()
{
	return PosZ - 0.12f;
}

float Animal::getFront()
{
	return PosZ + 0.12f;
}

float Animal::getBottom()
{
	return PosY;
}

float Animal::getTop()
{
	return 0.0f;
}

void Animal::initAnimals()
{
    random_device rd;
    default_random_engine dre(rd());
    AnimalCnt = 0;
	if (AnimalType == Cat) {
        uniform_real_distribution<float> urdX{ -104,-97 };
        uniform_real_distribution<float> urdZ{ -3, 3 };
        PosX = urdX(dre);
        PosY = -1.0f;
        PosZ = urdZ(dre);

		HP = 20;
		Attack = 10;
	}
	if (AnimalType == Dog) {
        uniform_real_distribution<float> urdX{ 97, 103 };
        uniform_real_distribution<float> urdZ{ -3, 3 };
        PosX = urdX(dre);
        PosY = -1.0f;
        PosZ = urdZ(dre);

		HP = 40;
		Attack = 20;
	}

    if (AnimalType == Bear) {
        PosX = 0;
        PosY = -1.0f;
        PosZ = -100.f;
        HP = 100;
        Attack = 30;
    }
    Direction = 0.f;
	AnimalCrushHero = false;
}


