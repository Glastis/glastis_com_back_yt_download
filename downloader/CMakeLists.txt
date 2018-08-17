cmake_minimum_required(VERSION 3.9)
project(downloader)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME}
        main.c              header/main.h
        get_list_info.c     header/get_list_info.h
        process.c           header/process.h
        utilities.c         header/utilities.h
        download.c          header/download.h

        )

target_link_libraries(${PROJECT_NAME} curl)
