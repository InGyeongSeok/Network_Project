#version 330 core

layout (location = 0) in vec3 vPos;		//--- ���� ���α׷����� �޾ƿ� ���� ��ǥ��
layout (location = 1) in vec3 vNormal;	//--- ��������
layout (location = 2) in vec2 vTexCoord; //--- �ؽ�ó ��ǥ

layout (location = 5) in vec3 vColor;
out vec3 yanggang;

out vec3 FragPos;						//--- ��ü�� ��ġ���� �����׸�Ʈ ���̴��� ������.
out vec3 Normal;						//--- ��ְ��� �����׸�Ʈ ���̴��� ������.
out vec2 TexCoord;

uniform mat4 modelTransform;			//--- �𵨸� ��ȯ
uniform mat4 viewTransform;				//--- ���� ��ȯ(ī�޶�)
uniform mat4 projectionTransform;		//--- ���� ��ȯ(����, ����)

void main()
{
	gl_Position =  projectionTransform * viewTransform * modelTransform * vec4(vPos, 1.0);	//--- ��ǥ���� ���� * ī�޶� * �� ��ȯ�� �����Ѵ�.

	TexCoord = vTexCoord; //--- �ؽ�ó ��ǥ ����

	FragPos = vec3(modelTransform * vec4(vPos, 1.0));	//--- ��ü�� ���� ���� ����� �����׸�Ʈ ���̴����� �Ѵ�. 
														//--- ���� ��������� �ִ� ���ؽ� ���� �����׸�Ʈ ���̴��� ������.
	Normal = mat3(transpose(inverse(modelTransform))) * vNormal;			//--- ��ְ��� �����׸�Ʈ ���̴��� ������.

	yanggang = vColor;
}