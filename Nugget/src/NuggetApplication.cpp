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
	NuggetApplication::NuggetApplication()
	{
		NuggetWindow::Init();
		NuggetWindow::GetWindow()->Create(1000, 800);

		Renderer::Init();

		SetWindowCloseCallback([this]() {DefaultWindowCloseHandler(); });
	}

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
		Initialize();

		mNextFrameTime = std::chrono::steady_clock::now() + mFrameDuration;


		while (mShouldContinue)
		{
			Renderer::ClearScreen();

			OnUpdate();

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

	void NuggetApplication::DefaultWindowCloseHandler()
	{
		mShouldContinue = false;
	}

}
