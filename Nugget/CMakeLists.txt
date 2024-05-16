set(HEADER_FILES
	include/Nugget.h
	src/NuggetApplication.h
	src/Utility.h
	src/NuggetWindow.h
	src/WindowImpl.h
	src/codeGLFW/WindowGLFW.h
	src/Renderer.h
	src/RendererImplement.h
	src/codeOpenGL/RendererOpenGL.h
	src/Shader.h
	src/ShaderImplement.h
	src/codeOpenGL/ShaderOpenGL.h
	src/Image.h
	src/ImageImplement.h
	src/codeOpenGL/ImageOpenGL.h
	src/NuggetEvents.h
	src/NuggetKeys.h
	src/Unit.h
)

set(SOURCE_FILES
	src/NuggetApplication.cpp
	src/NuggetWindow.cpp
	src/codeGLFW/WindowGLFW.cpp
	src/Renderer.cpp
	src/codeOpenGL/RendererOpenGL.cpp
	src/Shader.cpp
	src/codeOpenGL/ImageOpenGL.cpp
	src/NuggetEvents.cpp
	src/Unit.cpp
)


add_library(Nugget SHARED ${HEADER_FILES} ${SOURCE_FILES})

target_compile_definitions(Nugget 
	PUBLIC
		$<$<CONFIG:Debug>:NUGGET_DEBUG=2>
		$<$<CONFIG:RelWithDebInfo>:NUGGET_DEBUG=1>
	PRIVATE 
		NUGGET_LIB
		NUGGET_GLFW_WINDOW
		NUGGET_OPENGL
	
)

if(MSVC)
	target_compile_definitions(Nugget PUBLIC NUGGET_MS_COMPILER)
endif()

target_include_directories(Nugget PRIVATE ../glfw/include)
target_include_directories(Nugget PRIVATE ../Nugget)
target_include_directories(Nugget PRIVATE ../glad/include)
target_include_directories(Nugget PRIVATE ../stbi)

target_precompile_headers(Nugget PRIVATE src/pch.h)

target_link_libraries(Nugget glfw)
target_link_libraries(Nugget glad)
target_link_libraries(Nugget stbi)


file(COPY Assets DESTINATION ${PROJECT_BINARY_DIR}/Nugget)
file(COPY Assets DESTINATION ${PROJECT_BINARY_DIR}/Debug/Nugget)
file(COPY Assets DESTINATION ${PROJECT_BINARY_DIR}/Release/Nugget)