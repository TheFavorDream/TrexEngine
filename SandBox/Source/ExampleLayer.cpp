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
	Shader::GetInstance()->SetUniformF("u_Color", i);
	Shader::GetInstance()->SetUniformF("Scale", i);

	switch (Increace)
	{
	case true:
		i += 0.0001f;

		if (i >= 1.5f)
		{
			Increace = false;
		}


		break;

	case false:
		i -= 0.0001f;

		if (i <= 0.0f)
		{
			Increace = true;
		}
		break;
	}

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