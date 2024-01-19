cmake_minimum_required(VERSION 3.20.0)

# default board and board's path
set(BOARD_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(BOARD nucleo_l476rg)

# find and include zephyr dependencies
find_package(Zephyr REQUIRED
  HINTS $ENV{ZEPHYR_BASE}
        ${CMAKE_CURRENT_LIST_DIR}/../zephyr
)

# set project name
project(zephyr_template)

# application source files
FILE(GLOB app_sources
  src/main.c
)

target_sources(app PRIVATE ${app_sources})
