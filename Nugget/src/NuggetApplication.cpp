#include "pch.h"

#include"NuggetApplication.h"

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

		Initialize();

		while (true) {

			OnUpdate();

		}

		Shutdown();

	}
}
