#pragma once

#include "Trex.h"

using namespace TrexEngine;

class ExampleLayer : public TrexEngine::Layer
{
public:

	ExampleLayer();

	void OnAttach() override;

	void OnEvent() override;

	void OnUpdate() override;

	void OnRender() override;

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
		-0.5f, -0.5f,		1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,		0.9f, 0.8f, 0.7f,
		-0.5f,  0.5f,		0.8f, 0.6f, 0.4f,
		 0.5f,  0.5f,		0.7f, 0.4f, 0.1f
	};

	float i = 0.0f;
	bool Increace = true;

	unsigned int Indicies[6] =
	{
		0, 1, 2,
		1, 2, 3
	};


};