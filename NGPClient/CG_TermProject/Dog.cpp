#include "Dog.h"

extern int DogCnt;

Dog::Dog() : 
head(Head(glm::vec3(156. / 255, 91. / 255, 54. / 255),2)),
body(Body(glm::vec3(156. / 255, 91. / 255, 54. / 255),2)),
armL(Arm (glm::vec3(156. / 255, 91. / 255, 54. / 255), -1,2)),
armR(Arm (glm::vec3(156. / 255, 91. / 255, 54. / 255), 1,2)),
legL(Leg (glm::vec3(156. / 255, 91. / 255, 54. / 255), -1,2)),
legR(Leg (glm::vec3(156. / 255, 91. / 255, 54. / 255), 1,2)),

earL(Ear (glm::vec3(138. / 255, 73. / 255, 36. / 255), -1,2)),
earR(Ear (glm::vec3(138. / 255, 73. / 255, 36. / 255), 1,2)),


beardvertical(Beard(glm::vec3(36. / 255, 36. / 255, 36. / 255), 1, 1,2)),
beardhorizon(Beard(glm::vec3(36. / 255, 36. / 255, 36. / 255), 1, 2,2)),


nose(Nose(glm::vec3(36. / 255, 36. / 255, 36. / 255),2)),
eyesL(Eyes(glm::vec3(255. / 255, 54. / 255, 54. / 255), -1,2)),
eyesR(Eyes(glm::vec3(255. / 255, 54. / 255, 54. / 255), 1,2)),
Position(glm::vec3(1.f, -1.f, 1.f)), Direction(0.f),
swordL(Sword(glm::vec3(72. / 255, 255. / 255, 255. / 255), -1,2)),
swordR(Sword(glm::vec3(72. / 255, 255. / 255, 255. / 255), 1,2))
{
	random_device rd;
	default_random_engine dre(rd());
	uniform_real_distribution<float> urdX{ 97, 103 };
	uniform_real_distribution<float> urdZ{ -3, 3 };
	Position.x = urdX(dre);
	Position.y = -1.0f;
	Position.z = urdZ(dre);
	HP = 40;
	Attack = 20;
	Index = DogCnt;
	++DogCnt;
}


void Dog::draw()
{
	nose.draw();
	head.draw();
	armL.draw();
	armR.draw();
	body.draw();
	legL.draw();
	legR.draw();
	eyesL.draw();
	eyesR.draw();
	earL.draw();
	earR.draw();
	beardvertical.draw();
	beardhorizon.draw();
	
	swordL.draw();
	swordR.draw();
}

void Dog::update()
{

	nose.keyIn(Position, Direction);
	head.keyIn(Position, Direction);
	armL.keyIn(Position, Direction);
	armR.keyIn(Position, Direction);
	body.keyIn(Position, Direction);
	legL.keyIn(Position, Direction);
	legR.keyIn(Position, Direction);
	eyesL.keyIn(Position, Direction);
	eyesR.keyIn(Position, Direction);
	earL.keyIn(Position, Direction);
	earR.keyIn(Position, Direction);
	beardvertical.keyIn(Position, Direction);
	beardhorizon.keyIn(Position, Direction);
	swordL.keyIn(Position, Direction);
	swordR.keyIn(Position, Direction);


}

void Dog::doginfo(SC_MONSTER_PACKET* p)
{
	Direction = p->direction;
	Position.x = p->x;
	Position.y = p->y;
	Position.z = p->z;
	HP = p->hp;
}

Dog::~Dog()
{
}

float Dog::getLeft()
{
	return Position.x - 0.12f;
}

float Dog::getRight()
{
	return Position.x + 0.12f;
}

float Dog::getBehind()
{
	return Position.z - 0.12f;
}

float Dog::getFront()
{
	return Position.z + 0.12f;
}

float Dog::getBottom()
{
	return Position.y;
}

float Dog::getTop()
{
	return 0.0f;				//계산하기 귀찮으니 대충 0으로 잡겠음(의미없는값)
}

void Dog::initDog()
{
	Direction=0.f;
	HP = 40;
}


