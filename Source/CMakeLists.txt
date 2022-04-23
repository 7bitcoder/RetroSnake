
add_subdirectory(Library)

add_executable(RetroSnake
  main.cpp
)

target_link_libraries(RetroSnake 
  RetroSnakeLib
)