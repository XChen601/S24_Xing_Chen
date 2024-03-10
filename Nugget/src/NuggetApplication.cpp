#include "pch.h"

#include"NuggetApplication.h"
#include"NuggetWindow.h"

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
		Initialize();

		while (true) 
		{
			OnUpdate();

			NuggetWindow::GetWindow()->SwapBuffers();
			NuggetWindow::GetWindow()->PollEvents();

		}

		Shutdown();

		NuggetWindow::Shutdown();

	}
}
