#pragma once

#define START_GAME(className)\
int main()\
{\
	className _game;\
	_game.Run();\
	return 0;\
}
#ifdef NUGGET_MS_COMPILER
	#ifdef NUGGET_LIB
		#define NUGGET_API __declspec(dllexport)
	#else 
		#define NUGGET_API __declspec(dllimport)
	#endif
#else
	#define NUGGET_API
#endif


#if NUGGET_DEBUG==2
	#define NUGGET_ERROR(x) std::cout<<x<<std::endl;
	#define NUGGET_LOG(x) std::cout<<x<<std::endl;
#elif NUGGET_DEBUG==1
	#define NUGGET_ERROR(x) std::cout<<x<<std::endl;
	#define NUGGET_LOG(x)
#else
	#define NUGGET_ERROR(x) 
	#define NUGGET_LOG(x)
#endif