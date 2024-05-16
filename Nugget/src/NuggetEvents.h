#pragma once

#include "Utility.h"
#

namespace Nugget
{
	class NUGGET_API KeyPressed
	{
	public:
		KeyPressed(int kCode);

		int GetKeyCode() const;

	private:
		int mKeyCode;
	};

	class NUGGET_API KeyReleased
	{
	public:
		KeyReleased(int kCode);

		int GetKeyCode() const;

	private:
		int mKeyCode;
	};
}