#pragma once

#include "Trex.h"

#include <vector>

using namespace TrexEngine;


class Wednesdex : public TrexEngine::Layer
{
public:

	Wednesdex();

	void OnAttach() override;
	void OnEvent() override;
	void OnRender() override;
	void OnUpdate() override;
	void OnDettach() override;
	void EnableLayer() override;
	void DisableLayer() override;

	void CameraKeyControll();
	void CameraMouseControll();

	void CreateSphere(float radius, VertexBuffer& VBO, VertexArray& VAO, IndexBuffer& EBO);

	~Wednesdex();

private:
	TrexEngine::Engine* m_Engine = NULL;

	TrexEngine::Logger Log;
	TrexEngine::VertexArray        VAO;
	TrexEngine::VertexBufferLayout VBL;
	TrexEngine::VertexBuffer       VBO;
	TrexEngine::IndexBuffer        EBO;

	TrexEngine::VertexBufferLayout  SkyVBL;
	TrexEngine::VertexBuffer		SkyVBO;
	TrexEngine::VertexArray			SkyVAO;

	TrexEngine::Camera             TrexCamera;

	glm::vec3 LightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 LightPosition = glm::vec3(17.0f, 3.0f, 10.0f);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 SphereModel = glm::mat4(1.0f);

	


	float SkyBoxVertex[108] =
	{
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
	};

	glm::vec3 Coords[3] = 
	{
		glm::vec3(0.0f, 3.0f, -10.0f),
		glm::vec3(12.0f, 3.0f, -10.0f),
		glm::vec3(24.0f, 3.0f, -10.0f)
	};

	unsigned int Indicies[36] =
	{
		0, 1, 2,
		1, 2, 3,

		4, 5, 6,
		5, 6, 7,

	    8, 9, 10,
		9, 10,11,

		12, 13, 14,
		13, 14, 15,

		16, 17, 18,
		17, 18, 19,

		20, 21, 22,
		21, 22, 23
	};

};
