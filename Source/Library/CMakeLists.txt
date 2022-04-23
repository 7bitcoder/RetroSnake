file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp)

add_library(RetroSnakeLib ${SOURCES})

target_include_directories(RetroSnakeLib PUBLIC
  h
)

