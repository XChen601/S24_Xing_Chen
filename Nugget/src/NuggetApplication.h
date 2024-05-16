#pragma once

#include"pch.h"
#include "Utility.h"
#include"NuggetEvents.h"


constexpr int NUGGET_FRAME_RATE{ 60 };

namespace Nugget 
{
	class NUGGET_API NuggetApplication {
	public:
		NuggetApplication();

		virtual void Initialize();
		virtual void OnUpdate();
		virtual void Shutdown();
		
		void Run();

		void SetKeyPressedCallback(std::function<void(const KeyPressed&)> callbackFunc);
		void SetKeyReleasedCallback(std::function<void(const KeyReleased&)> callbackFunc);
		void SetWindowCloseCallback(std::function<void()> callbackFunc);

		void DefaultWindowCloseHandler();

	private:
		std::chrono::steady_clock::time_point mNextFrameTime;
		std::chrono::milliseconds mFrameDuration{ std::chrono::milliseconds{1000} / NUGGET_FRAME_RATE };

		bool mShouldContinue{ true };
	};
}
