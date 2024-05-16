#include"pch.h"
#include"NuggetWindow.h"
#include"codeGLFW/WindowGLFW.h"

namespace Nugget
{
	NuggetWindow::NuggetWindow()
	{
#ifdef NUGGET_GLFW_WINDOW
		mWindow = std::unique_ptr<WindowImpl>{ new WindowGLFW };
#else
	#definition_NUGGET_GLFW_is_missing
#endif

	}

	void NuggetWindow::Init()
	{
		if (!mInstance)
			mInstance = new NuggetWindow;
	}

	NuggetWindow* NuggetWindow::GetWindow()
	{
		return mInstance;
	}

	void NuggetWindow::Shutdown()
	{
		if (mInstance)
			delete mInstance;

	}

	void NuggetWindow::SwapBuffers()
	{
		mWindow->SwapBuffers();
	}

	void NuggetWindow::PollEvents()
	{
		mWindow->PollEvents();
	}

	void NuggetWindow::Create(int width, int height)
	{
		mWindow->Create(width, height);
	}
	int NuggetWindow::GetWidth() const
	{
		return mWindow->GetWidth();
	}

	int NuggetWindow::GetHeight() const
	{
		return mWindow->GetHeight();
	}

	void NuggetWindow::SetKeyPressedCallback(std::function<void(const KeyPressed&)>& callbackFunc)
	{
		mWindow->SetKeyPressedCallback(callbackFunc);
	}

	void NuggetWindow::SetKeyReleasedCallback(std::function<void(const KeyReleased&)>& callbackFunc)
	{
		mWindow->SetKeyReleasedCallback(callbackFunc);
	}

	void NuggetWindow::SetWindowCloseCallback(std::function<void()> callbackFunc)
	{
		mWindow->SetWindowCloseCallback(callbackFunc);
	}

}