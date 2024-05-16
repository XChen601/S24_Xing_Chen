#pragma once

#include"pch.h"
#include"WindowImpl.h"
#include"Utility.h"
//#include"NuggetEvents.h"

namespace Nugget
{
	class NUGGET_API NuggetWindow
	{
	public:
		static void Init();
		static NuggetWindow* GetWindow();
		static void Shutdown();


		void SwapBuffers();
		void PollEvents();
		void Create(int width, int height);
		int GetWidth() const;
		int GetHeight() const;

		void SetKeyPressedCallback(std::function<void(const KeyPressed&)>& callbackFunc);
		void SetKeyReleasedCallback(std::function<void(const KeyReleased&)>& callbackFunc);
		void SetWindowCloseCallback(std::function<void()> callbackFunc);

	private:
		inline static NuggetWindow* mInstance{ nullptr };
		
		std::unique_ptr<WindowImpl> mWindow{nullptr};


		NuggetWindow();
	};


}