add_executable(Game Source.cpp MyGame.h MyGame.cpp Score.h Score.cpp Fireball.h Fireball.cpp Enemy.h Enemy.cpp)


include_directories("../Nugget/include")

target_link_libraries(Game Nugget)