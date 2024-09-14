#pragma once

#include "Source/Trex.h"

class ExampleLayer : public TrexEngine::Layer
{
public:

	ExampleLayer();

	void OnAttach() override;

	void OnEvent() override;

	void OnUpdate(const TrexEngine::Shader&  shader) override;

	void OnRender(const TrexEngine::Renderer& Render) override;

	void OnDettach() override;

	~ExampleLayer();

private:

	TrexEngine::VertexArray        VAO;
	TrexEngine::VertexBufferLayout VBL;
	TrexEngine::VertexBuffer       VBO;
	TrexEngine::IndexBuffer        EBO;

	float Vertices[20] =
	{
		-0.5f, -0.5f,		1.0f, 0.5f, 0.5f,
		 0.5f, -0.5f,		0.5f, 1.0f, 0.0f,
		-0.5f,  0.5f,		0.2f, 0.5f, 1.0f,
		 0.5f,  0.5f,		1.0f, 0.5f, 0.2f
	};

	float i = 0.0f;
	bool Increace = true;

	unsigned int Indicies[6] =
	{
		0, 1, 2,
		1, 2, 3
	};


};