cmake_minimum_required(VERSION 3.10)

project(Labirynth)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "C:\\libraries\\SFML-2.6.0-VC")

find_package(SFML 2.6 COMPONENTS system graphics window REQUIRED)

add_executable(Labirynth main.cpp Util.cpp Textbox.cpp Button.cpp Labirynth.cpp )

target_include_directories(Labirynth PRIVATE "C:\\libraries\\SFML-2.6.0-VC\\include")

target_link_libraries(Labirynth PRIVATE
                    sfml-graphics
                    sfml-system
                    sfml-window)
