set(HEADER_FILES
	include/Nugget.h
	src/NuggetApplication.h
	src/Utility.h
	src/NuggetWindow.h
	src/WindowImpl.h
	src/codeGLFW/WindowGLFW.h

)

set(SOURCE_FILES
	src/NuggetApplication.cpp
	src/NuggetWindow.cpp
	src/codeGLFW/WindowGLFW.cpp
)


add_library(Nugget SHARED ${HEADER_FILES} ${SOURCE_FILES})

target_compile_definitions(Nugget 
	PUBLIC
		$<$<CONFIG:Debug>:NUGGET_DEBUG=2>
		$<$<CONFIG:RelWithDebInfo>:NUGGET_DEBUG=1>
	PRIVATE 
		NUGGET_LIB
		NUGGET_GLFW_WINDOW
	
)

if(MSVC)
	target_compile_definitions(Nugget PUBLIC NUGGET_MS_COMPILER)
endif()

target_include_directories(Nugget PRIVATE ../glfw/include)
target_include_directories(Nugget PRIVATE ../Nugget)

target_precompile_headers(Nugget PRIVATE src/pch.h)

target_link_libraries(Nugget glfw)