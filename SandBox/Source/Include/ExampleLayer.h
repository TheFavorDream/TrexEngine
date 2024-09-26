#pragma once

#include "Trex.h"

using namespace TrexEngine;

class ExampleLayer : public TrexEngine::Layer
{
public:

	ExampleLayer();

	void OnAttach(TrexEngine::Window* p_Window, TrexEngine::Shader* p_Shader) override;


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

	float Vertices[20] =
	{
		-0.5f, -0.5f,		
		 0.5f, -0.5f,		
		-0.5f,  0.5f,		
		 0.5f,  0.5f
	};

	float i = 0.0f;
	bool Increace = true;

	unsigned int Indicies[6] =
	{
		0, 1, 2,
		1, 2, 3
	};


};