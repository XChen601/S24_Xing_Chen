#pragma once

#include"RendererImplement.h"
#include"Shader.h"

namespace Nugget
{
	class RendererOpenGL : public RendererImplement
	{
	public:
		RendererOpenGL();
		~RendererOpenGL();

		virtual void Draw(Image& pic, int x, int y) override;
		virtual void Draw(Image& pic, Shader& shader, int x, int y) override;
		virtual void ClearScreen() override;

	private:
		Shader mDefaultShader{ "../Assets/Shaders/defaultVertexShader.glsl", 
			"../Assets/Shaders/defaultFragmentShader.glsl" };
	};
}