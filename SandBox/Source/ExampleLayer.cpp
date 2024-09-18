#include "ExampleLayer.h"
ExampleLayer::ExampleLayer()
	:	Layer("ExampleLayer")
{

}

void ExampleLayer::OnAttach()
{

	VBL.push<float>(2);
	VBL.push<float>(3);

	VBO.BufferData(Vertices, sizeof(Vertices));

	VAO.AddLayouts(VBO, VBL);

	EBO.BufferData(Indicies, 6);
}

void ExampleLayer::OnEvent()
{
}

void ExampleLayer::OnUpdate()
{

}

void ExampleLayer::OnRender()
{
	Renderer::GetInstance()->DrawElements(VBO, EBO, VAO);
}


void ExampleLayer::OnDettach()
{
}




ExampleLayer::~ExampleLayer()
{

}