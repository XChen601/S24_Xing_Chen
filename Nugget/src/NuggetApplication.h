#pragma once

#include "Utility.h"

namespace Nugget {
	class NUGGET_API NuggetApplication {
	public:
		virtual void Initialize();
		virtual void OnUpdate();
		virtual void Shutdown();
		
		void Run();

	private:
	
	};
	

}
