cmake_minimum_required(VERSION 4.0)
project(JumpDodge)

# 设置 raylib 路径
set(RAYLIB_PATH "C:/raylib/w64devkit")

# 包含头文件
include_directories(
    "${CMAKE_SOURCE_DIR}/include"                          # 项目头文件
    "${RAYLIB_PATH}/x86_64-w64-mingw32/include"
)

# 添加可执行文件
file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(JumpDodge ${SOURCES})

# 直接链接 MinGW 的静态库（libraylib.a）
target_link_libraries(JumpDodge "${RAYLIB_PATH}/x86_64-w64-mingw32/lib/libraylib.a")

# Windows 额外依赖项
if(WIN32)
    target_link_libraries(JumpDodge
        opengl32
        gdi32
        winmm
    )
endif()