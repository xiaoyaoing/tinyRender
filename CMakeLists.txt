cmake_minimum_required(VERSION 3.17)
project(tinyRender)
#
#cmake_minimum_required(VERSION 3.17)
#project(untitled)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

##add_executable(${PROJECT_NAME} main.cpp)
set(SDL_DIR /usr/local/Cellar/sdl2/2.0.14_1/) # 这个SDL开发包的路径，可以通过brew info sdl2查出来
include_directories(${SDL_DIR}/include/) # 添加SDL头文件搜索路径
link_directories(${SDL_DIR}/lib/)
link_libraries(SDL2)


set(HEADERS
        geometry.h
        global.h
        tgaimage.h
        shader/shader.h
        headers/frameBuffer.h
        model.h
        texture.h
        window.h
        camera.h
        renderThread.h
        )
set(RESOURCES
        tgaimage.cpp
        main.cpp
        shader/shader.cpp
        geometry.cpp
        pipeline.cpp
        resources/frameBuffer.cpp
        vertex.cpp
        model.cpp
        window.cpp
        camera.cpp
        )

add_executable(tinyRender ${HEADERS} ${RESOURCES})

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED} SDL2 SDL2_test SDL2main)
