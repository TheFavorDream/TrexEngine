#pragma once

#include "Trex.h"

using namespace TrexEngine;


class ExampleLayer : public TrexEngine::Layer
{
public:

	ExampleLayer();

	void OnAttach(TrexEngine::Window* p_Window, TrexEngine::ShaderManager* p_ShadersMG, TrexEngine::Input* p_Events, ResourceManager* p_Resources) override;

	void OnEvent() override;

	void OnRender() override;

	void OnUpdate() override;

	void OnDettach() override;

	void EnableLayer() override;
	void DisableLayer() override;


	~ExampleLayer();

private:

	TrexEngine::Logger Log;

	TrexEngine::VertexArray        VAO;
	TrexEngine::VertexBufferLayout VBL;
	TrexEngine::VertexBuffer       VBO;
	TrexEngine::IndexBuffer        EBO;

	float Vertices[120] =
	{
		0.9f,  0.2f,		1.0f, 0.0f, 0.0f, 		//UP Right
		0.9f, -0.2f,		1.0f, 0.0f, 0.0f,		//Down Right
	    0.6f,  0.2f,		1.0f, 0.0f, 0.0f,		// Up Left
	    0.6f, -0.2f,		1.0f, 0.0f, 0.0f,		//Down Left

	   -0.6f,   0.2f,		0.0f, 1.0f, 0.0f, 		//UP Right
	   -0.6f,  -0.2f,		0.0f, 1.0f, 0.0f,		//Down Right
	   -0.9f,   0.2f,		0.0f, 1.0f, 0.0f,		// Up Left
	   -0.9f,  -0.2f,		0.0f ,1.0f, 0.0f,		//Down Left

	   -0.2f,   0.2f,		0.0f, 0.0f, 1.0f, 		//UP Right
	   -0.2f,  -0.2f,		0.0f, 0.0f, 1.0f,		//Down Right
	    0.2f,   0.2f,		0.0f, 0.0f, 1.0f,		// Up Left
	    0.2f,  -0.2f,		0.0f ,0.0f, 1.0f,		//Down Left

		0.9f,  -0.3f,		1.0f, 1.0f, 0.0f, 		//UP Right
		0.9f,  -0.7f,		1.0f, 1.0f, 0.0f,		//Down Right
		0.6f,  -0.3f,		1.0f, 1.0f, 0.0f,		// Up Left
		0.6f,  -0.7f,		1.0f, 1.0f, 0.0f,		//Down Left

	   -0.6f,  -0.3f,		0.0f, 1.0f, 1.0f, 		//UP Right
	   -0.6f,  -0.7f,		0.0f, 1.0f, 1.0f,		//Down Right
	   -0.9f,  -0.3f,		0.0f, 1.0f, 1.0f,		// Up Left
	   -0.9f,  -0.7f,		0.0f ,1.0f, 1.0f,		//Down Left

	   -0.2f,  -0.3f,		1.0f, 0.0f, 1.0f, 		//UP Right
	   -0.2f,  -0.7f,		1.0f, 0.0f, 1.0f,		//Down Right
		0.2f,  -0.3f,		1.0f, 0.0f, 1.0f,		// Up Left
		0.2f,  -0.7f,		1.0f ,0.0f, 1.0f		//Down Left
	    
	};

	unsigned int Indicies[36] =
	{
		0, 1, 2,
		1, 2, 3,

		4, 5, 6, 
		5, 6, 7,

		8, 9, 10, 
		9, 10, 11,

		12, 13, 14,
		13, 14, 15,

		16, 17, 18,
		17, 18, 19,

		20, 21, 22,
		21, 22, 23
	};


};
