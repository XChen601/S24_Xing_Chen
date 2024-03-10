add_executable(Game Source.cpp)


include_directories("../Nugget/include")

target_link_libraries(Game Nugget)