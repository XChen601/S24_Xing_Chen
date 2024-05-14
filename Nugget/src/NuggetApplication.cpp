#include "pch.h"

#include"NuggetApplication.h"
#include"NuggetWindow.h"
#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include"stb_image.h"

#include"Renderer.h"
#include"Image.h"
#include"Shader.h"


namespace Nugget {
	void NuggetApplication::Initialize()
	{

	}
	void NuggetApplication::OnUpdate()
	{
	}

	void NuggetApplication::Shutdown()
	{
	}
	void NuggetApplication::Run()
	{
		Renderer::Init();

		NuggetWindow::Init();
		NuggetWindow::GetWindow()->Create(1000, 800);
		
		

		// Shaders //
		
		Shader sProg{ "C:\\Users\\xchen\\source\\repos\\S24_Xing_Chen\\Nugget\\Assets\\Shaders\\DefaultVertexShader.glsl",
		"C:\\Users\\xchen\\source\\repos\\S24_Xing_Chen\\Nugget\\Assets\\Shaders\\DefaultFragmentShader.glsl" };


		// Texture //

		Nugget::Image pic{ "C:\\Users\\xchen\\source\\repos\\S24_Xing_Chen\\Nugget\\Assets\\Textures\\Test.png" };

		Initialize();

		while (true) 
		{
			OnUpdate();

			Renderer::ClearScreen();

			Renderer::Draw(pic, 200, 100);

			NuggetWindow::GetWindow()->SwapBuffers();
			NuggetWindow::GetWindow()->PollEvents();

		}

		Shutdown();

		NuggetWindow::Shutdown();

	}
}
