cmake_minimum_required(VERSION 3.10)
project(chess)

# Set the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Find the SDL2 package
# find_package()

# Include the SDL2 header files
# include_directories(${SDL2_INCLUDE_DIRS})

# Define your executable
add_executable(chess main.c board.c)

# Link the SDL2 library and the math library with your executable
target_link_libraries(chess m)  # Added 'm' for the math library

