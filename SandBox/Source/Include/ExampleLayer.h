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
	TrexEngine::Texture            texture;
	
	float Vertex[28] =
	{
		 0.25f,  0.5f,  1.0f, 0.0f, 0.0f,	 1.0f, 0.0f,
		 0.25f, -0.5f,  0.0f, 1.0f, 0.0f,	 1.0f, 1.0f,
		-0.25f,  0.5f,  0.0f, 0.0f, 1.0f,	 0.0f, 0.0f,
		-0.25f, -0.5f,  1.0f, 1.0f, 1.0f,	 0.0f, 1.0f
	};

	unsigned int Indicies[6] =
	{
		0, 1, 2,
		1, 2, 3
	};

};
