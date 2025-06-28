cmake_minimum_required(VERSION 3.14)
project(TCPUDPClient C)

set(CMAKE_C_STANDARD 11)

# Optional: Use Ninja if available
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set include path
include_directories(include)

# Add sources
file(GLOB SOURCES "src/*.c")

# Add executable
add_executable(ssh_client ${SOURCES})


