
#pragma once
#include "Header.h"

//좌표 XYZ / 스케일 / 색상 

class Grass
{
	glm::mat4 Change;
	float Xpos;
	float Ypos;
	float Zpos;
	int Grassnum;
	float Direction;
	int randN;
public:

	Grass();

	~Grass();
	void Update();
	void Draw();

};

