#pragma once

#include "Trex.h"

using namespace TrexEngine;

class ExampleLayer : public TrexEngine::Layer
{
public:

	ExampleLayer();

	void OnAttach(TrexEngine::Window* p_Window) override;


	void OnEvent() override;

	void OnRender() override;

	void OnUpdate(TrexEngine::Shader* p_Shader) override;

	void OnDettach() override;

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