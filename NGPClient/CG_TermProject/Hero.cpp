#include "Hero.h"
#include "Sound.h"


extern Sound playSound;


extern bool catlive;
extern bool doglive;
extern bool bearlive;
extern bool herodead;

extern float HeroLocationX;
extern float HeroLocationZ;


Hero::Hero(int colorID) : Unit(1.f)
{
	random_device rd;
	default_random_engine dre(rd());
	uniform_real_distribution<float> urd{ 0, 255 };
	if (colorID == 0)
		color = glm::vec3(1.0f, 1.0f, 1.0f);
	else if (colorID == 1)
		color = glm::vec3(1.0f, 0.0f, 0.0f);
	else if (colorID == 2)
		color = glm::vec3(0.0f, 1.0f, 0.0f);
	scaleX = 0.3;
	scaleY = 0.3;
	scaleZ = 0.3;
	HP = 100;
	firstmap = true;
	status = true;
	
}
Hero::~Hero()
{

}

void Hero::damage()
{

}



int Hero::InfoHP() {
	return HP / 10;
}

void Hero::Update()
{

	//damage();
	glm::mat4 Scale = glm::scale(Unit, glm::vec3(scaleX, scaleY, scaleZ));
	glm::mat4 Trans;
	
	Trans = glm::translate(Unit, glm::vec3(PosX, PosY, PosZ ));


	

	glm::mat4 AddTrans = glm::translate(Unit, glm::vec3(0., 1., 0.));
	Change = Trans * Scale * AddTrans;
}



void Hero::Draw()
{

	glBindVertexArray(VAO);
	GLuint SelectColor = glGetUniformLocation(shaderID, "SelectColor");
	glUniform1i(SelectColor, 1);

	GLuint aColor = glGetUniformLocation(shaderID, "objectColor");
	glUniform4f(aColor, color.r, color.g, color.b, 1.0);
	GLuint modelLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Change));
	glDrawArrays(GL_TRIANGLES, 0, vertex1.size() * 3);


}

void Hero::location()
{
	HeroLocationX = PosX;
	HeroLocationZ = PosZ;
}


float Hero::getLeft()
{
	return PosX - 0.12f;
}

float Hero::getRight()
{
	return PosX + 0.12f;
}

float Hero::getBehind()
{
	return PosZ - 0.12f;
}

float Hero::getFront()
{
	return PosZ + 0.12f;
}

void Hero::get_Info(float* x, float* y, bool* status, float* dirx, float *diry, float *dirz)
{
	*x = VAngleX;
	*y = VAngleY;
	if (HP <= 0)
		*status = false;
	else
		*status = true;
	*dirx = TermGunDir.x;
	*diry = TermGunDir.y;
	*dirz = TermGunDir.z;

}

std::string Hero::getNickname()
{
	return nickname;
}

///////////////////camera part///////////////////


void Hero::camera()
{

	cameraPos = glm::vec3(PosX, PosY +0.5, PosZ);


	glm::mat4 VAngleY_Rot = glm::rotate(glm::mat4(1.0f), glm::radians(-VAngleY), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 VAngleX_Rot = glm::rotate(glm::mat4(1.0f), glm::radians(-VAngleX), glm::vec3(1.0, 0.0, 0.0));

	glm::vec3 CDir(0.f, 0.f, -10.f);
	CDir = VAngleY_Rot * VAngleX_Rot * glm::vec4(CDir, 1.f);
	CDir.x += 1.f;

	glm::vec3 cameraDirection(cameraPos + CDir);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraDirection.y -= 0.5f;
	glm::mat4 view = glm::lookAt(cameraPos, cameraDirection, cameraUp);


	TermGunDir = normalize(cameraDirection - cameraPos);

	/////////////////////////////////////////////////////////////////////

	unsigned int viewLocation = glGetUniformLocation(shaderID, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	unsigned int viewPosLocation = glGetUniformLocation(shaderID, "viewPos");
	glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);

}

void Hero::TopView()
{
	glm::vec3 cameraPos = glm::vec3(PosX, PosY + 0.5, PosZ);
	glm::vec3 cameraDirection = glm::vec3(PosX, 0.0, PosZ);
	glm::vec3 cameraUp = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::mat4 view = glm::mat4(1.0f);


	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	unsigned int viewLocation = glGetUniformLocation(shaderID, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
}

void Hero::camera3D()
{
	glm::vec3 cameraPos = glm::vec3(0.f, 5.f, 5.f);
	glm::vec3 cameraDirection = glm::vec3(0.f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::mat4(1.0f);


	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	unsigned int viewLocation = glGetUniformLocation(shaderID, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

}

void Hero::cameraProjection()
{
	projection = glm::perspective(glm::radians(90.0f), (float)width / height, 0.1f, 200.0f);
	projectionLocation = glGetUniformLocation(shaderID, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
	glViewport(0, 0, width, height);
}

void Hero::DrawHP()
{
	for (int i = 0; i < HP / 10; ++i) {
		glm::mat4 Change;
		Change = Unit;
		GLuint projectionTransform = glGetUniformLocation(shaderID, "projectionTransform");
		glUniformMatrix4fv(projectionTransform, 1, GL_FALSE, glm::value_ptr(Change));
		Change = Unit;
		GLuint viewTransform = glGetUniformLocation(shaderID, "viewTransform");
		glUniformMatrix4fv(viewTransform, 1, GL_FALSE, glm::value_ptr(Change));

		glm::mat4 Scale = glm::scale(Unit, glm::vec3(0.3));
		glm::mat4 Trans = glm::translate(Unit, glm::vec3(-0.95, 0.95, 0));
		Change = Trans * Scale;
		Change = glm::translate(Unit, glm::vec3(i * 0.08f, 0, 0)) * Change;
		GLuint modelTransform = glGetUniformLocation(shaderID, "modelTransform");
		glUniformMatrix4fv(modelTransform, 1, GL_FALSE, glm::value_ptr(Change));

		glDrawArrays(GL_POLYGON, 0, 4);
	}
}

void Hero::cameraProjection2()
{
	glViewport(width / 1.26, height / 1.35, 200, 200);
	projection = glm::mat4(1.0f);
	projection = glm::ortho(-ortho, ortho, -ortho, ortho, -ortho, ortho);
	projectionLocation = glGetUniformLocation(shaderID, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
}

void Hero::VAngleMotion(int x, int y)
{
	VAngleY += (x - width / 2) / 12.5;


	VAngleX += (y - height / 2) / 12.5;
	if (VAngleX >= 15.f) {
		VAngleX = 15.f;
	}
	else if (VAngleX <= -15.f) {
		VAngleX = -15.f;
	}
	glutWarpPointer(width / 2, height / 2);
}


void Hero::setInfo(SC_PLAYER_PACKET* p)
{
	status = p->status;
	Hero_ID = p->player_id;
	HP = p->player_hp;
	PosX = p->Player_pos.x;
	PosY = p->Player_pos.y;
	PosZ = p->Player_pos.z;
	lightColorR = p->Player_light.R;
	lightColorG = p->Player_light.G;
	lightColorB = p->Player_light.B;
	ready = p->ready;
	
	nickname = p->nickname;



}
void Hero::initHero()
{
	PosX = 0;
	PosY = 0.5;
	PosZ = 10.0;
	ready = false;
	HP = 100;
	lightColorR = 1.0f;
	lightColorG = 1.0f;
	lightColorB = 1.0f;

	lightColorR = 1.0f;
	lightColorG = 1.0f;
	lightColorB = 1.0f;
	carAddX = 0;
	carAddY = 0;
	carAddZ= 10;
	TermGunDir.x = 0;
	TermGunDir.y = 0;
	TermGunDir.z = 0;
	cameraPos.x = 0;
	cameraPos.y = 0;
	cameraPos.z = 0;

	CarX = 0.0;
	CarY = 1.0;
	CarZ = 0.0;

	CarDX = 0.0;
	CarDY = 0.0;
	CarDZ = 0.0;
	ortho = 12.0;
	status = true;


	VAngleX = 0;
	VAngleY = 0;
	firstmap = true;

	ortho = 12.0;


}
