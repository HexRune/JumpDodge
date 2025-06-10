cmake_minimum_required(VERSION 4.0)
project(JumpDodge
    VERSION 1.0.0
    LANGUAGES CXX
    DESCRIPTION "JumpDodge - raylib简易跳跃游戏"
)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置 raylib 路径
set(RAYLIB_PATH "C:/raylib" CACHE PATH "Raylib安装路径")

# 包含头文件目录
include_directories(
    "${CMAKE_SOURCE_DIR}/include"                           # 项目头文件
    "${RAYLIB_PATH}/raylib/src"                            
    "${RAYLIB_PATH}/w64devkit/x86_64-w64-mingw32/include"
)

# 库文件路径
set(RAYLIB_LIB "${RAYLIB_PATH}/w64devkit/x86_64-w64-mingw32/lib/libraylib.a")

# 添加可执行文件
file(GLOB SOURCES CONFIGURE_DEPENDS 
    "src/*.cpp"
    "src/*.c"
)
# 创建可执行目标
add_executable(${PROJECT_NAME} ${SOURCES})

# 直接链接 MinGW 的静态库（libraylib.a）
target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIB})

# Windows 额外依赖项
if(WIN32)
    target_link_libraries(${PROJECT_NAME} 
        opengl32
        gdi32
        winmm
    )
endif()