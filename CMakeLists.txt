cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME go_channels_in_c)
set(CMAKE_C_STANDARD 11)
set(SOURCES main.c src/buffer/ring_buffer.c src/channel/channel.c)
set(HEADERS include/buffer/ring_buffer.h include/channel/channel.h)

project(${PROJECT_NAME} C)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})


