#include "pch.h"

#include"NuggetApplication.h"
#include"NuggetWindow.h"
#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include"stb_image.h"

#include"Renderer.h"
#include"Image.h"
#include"Shader.h"
#include"NuggetKeys.h"


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
		NuggetWindow::Init();
		NuggetWindow::GetWindow()->Create(1000, 800);
		
		Renderer::Init();

		// Shaders //
		
		Shader sProg{ "C:\\Users\\xchen\\source\\repos\\S24_Xing_Chen\\Nugget\\Assets\\Shaders\\DefaultVertexShader.glsl",
		"C:\\Users\\xchen\\source\\repos\\S24_Xing_Chen\\Nugget\\Assets\\Shaders\\DefaultFragmentShader.glsl" };


		// Texture //

		Nugget::Image pic{ "C:\\Users\\xchen\\source\\repos\\S24_Xing_Chen\\Nugget\\Assets\\Textures\\Test.png" };

		Initialize();

		mNextFrameTime = std::chrono::steady_clock::now() + mFrameDuration;

		int x{ 50 };

		SetKeyPressedCallback([&x](const KeyPressed& event) {
			if (event.GetKeyCode() == NUGGET_KEY_RIGHT)
				x += 50;
		});

		while (true) 
		{
			Renderer::ClearScreen();
			OnUpdate();

			Renderer::Draw(pic, x, 100);


			std::this_thread::sleep_until(mNextFrameTime);
			mNextFrameTime = std::chrono::steady_clock::now() + mFrameDuration;

			NuggetWindow::GetWindow()->SwapBuffers();
			NuggetWindow::GetWindow()->PollEvents();

		}

		Shutdown();

		NuggetWindow::Shutdown();

	}
	
	void NuggetApplication::SetKeyPressedCallback(std::function<void(const KeyPressed&)> callbackFunc)
	{
		NuggetWindow::GetWindow()->SetKeyPressedCallback(callbackFunc);
	}

	void NuggetApplication::SetKeyReleasedCallback(std::function<void(const KeyReleased&)> callbackFunc)
	{
		NuggetWindow::GetWindow()->SetKeyReleasedCallback(callbackFunc);
	}

	void NuggetApplication::SetWindowCloseCallback(std::function<void()> callbackFunc)
	{
		NuggetWindow::GetWindow()->SetWindowCloseCallback(callbackFunc);
	}

}
