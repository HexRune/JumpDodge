cmake_minimum_required(VERSION 3.30)

# 项目信息
project(JumpDodge
    VERSION 1.0.0
    LANGUAGES CXX C
    DESCRIPTION "JumpDodge - 2D 跳跃躲避"
)

set(EXECUTABLE_NAME "JumpDodge")  # 输出文件名

# 设置C/C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 设置构建类型
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# 检测编译器
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(COMPILER_IS_MSVC TRUE)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(COMPILER_IS_CLANG TRUE)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILER_IS_GCC TRUE)
endif()

# 编译器设置
if(COMPILER_IS_MSVC)
    # 基本编译选项
    add_compile_options(/W3 /utf-8)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    
    # 根据构建类型设置不同的编译选项
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        # Debug 模式：禁用优化，启用调试信息，但不添加全局编译选项
        set(CMAKE_CXX_FLAGS_DEBUG "/Od /Zi /RTC1")
        set(CMAKE_C_FLAGS_DEBUG "/Od /Zi /RTC1")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
    else()
        # Release 模式：启用优化
        set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
        set(CMAKE_C_FLAGS_RELEASE "/O2 /DNDEBUG")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    endif()
elseif(COMPILER_IS_CLANG OR COMPILER_IS_GCC)
    add_compile_options(-Wall -Wextra)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -O0)
    else()
        add_compile_options(-O3)
    endif()
endif()

# 第三方库警告抑制
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_WARN_DEPRECATED OFF)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS ON)

# raylib 配置
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# MSVC 特定的 raylib 配置
if(COMPILER_IS_MSVC)
    # 强制 raylib 使用与主项目相同的运行时库
    set(USE_MSVC_RUNTIME_LIBRARY_DLL ON CACHE BOOL "" FORCE)
    
    # 禁用一些可能导致问题的 GLFW 功能
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
    
    # 确保 GLFW 使用正确的运行时库和编译选项
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(GLFW_USE_MSVC_RUNTIME_LIBRARY_DLL ON CACHE BOOL "" FORCE)
        # 强制设置 GLFW 的 Debug 编译标志，避免优化选项冲突
        set(CMAKE_CXX_FLAGS_DEBUG_INIT "/Od /Zi /RTC1")
        set(CMAKE_C_FLAGS_DEBUG_INIT "/Od /Zi /RTC1")
    endif()
    
    # 设置全局策略以避免编译选项冲突
    cmake_policy(SET CMP0092 NEW)  # 不自动添加 /W3
endif()

add_subdirectory(library/raylib)

# 修复 GLFW 在 MSVC Debug 模式下的编译选项冲突
if(COMPILER_IS_MSVC AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    # 获取 GLFW 目标并修复其编译选项
    if(TARGET glfw)
        # 移除可能冲突的优化选项
        get_target_property(GLFW_COMPILE_OPTIONS glfw COMPILE_OPTIONS)
        if(GLFW_COMPILE_OPTIONS)
            list(REMOVE_ITEM GLFW_COMPILE_OPTIONS "/O2")
            set_target_properties(glfw PROPERTIES COMPILE_OPTIONS "${GLFW_COMPILE_OPTIONS}")
        endif()
        
        # 设置正确的 Debug 编译选项
        target_compile_options(glfw PRIVATE /Od /Zi /RTC1)
        target_compile_definitions(glfw PRIVATE _DEBUG)
    endif()
endif()

# 恢复警告
set(CMAKE_WARN_DEPRECATED ON)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS OFF)

# 源文件
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS 
    "src/*.cpp" "src/*.c" "src/*.h" "src/*.hpp"
)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS 
    "include/*.h" "include/*.hpp"
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# 基本属性
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "${EXECUTABLE_NAME}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# MSVC 特定设置
if(COMPILER_IS_MSVC)
    # 确保主项目使用正确的运行时库
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MSVC_RUNTIME_LIBRARY "${CMAKE_MSVC_RUNTIME_LIBRARY}"
    )
    
    # Debug 模式下的额外设置
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_definitions(${PROJECT_NAME} PRIVATE _ITERATOR_DEBUG_LEVEL=2)
    endif()
endif()

# 链接 raylib
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# 包含目录
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 平台特定链接
if(WIN32)
    # Windows 系统库（所有编译器通用）
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        winmm gdi32 user32 shell32)

    # Release 模式下隐藏控制台窗口
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        if(COMPILER_IS_MSVC)
            # MSVC 方式
            set_target_properties(${PROJECT_NAME} PROPERTIES
                WIN32_EXECUTABLE TRUE
                LINK_FLAGS "/ENTRY:mainCRTStartup"
            )
        elseif(COMPILER_IS_GCC)
            # MinGW/GCC 方式
            set_target_properties(${PROJECT_NAME} PROPERTIES
                WIN32_EXECUTABLE TRUE
            )
        # elseif(COMPILER_IS_CLANG)
        # 对于 Clang，暂时保持控制台应用以避免链接问题
        endif()
    endif()
    
elseif(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        m pthread dl rt)
elseif(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    find_library(OPENGL_LIBRARY OpenGL)
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        ${COCOA_LIBRARY} ${IOKIT_LIBRARY} 
        ${COREVIDEO_LIBRARY} ${OPENGL_LIBRARY}
    )
endif()

# 复制资源文件
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/resources")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
        COMMENT "Copying resources"
    )
endif()

# 调试设置
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# 构建信息
message(STATUS "=== Build Configuration ===")
message(STATUS "Project: ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: C++${CMAKE_CXX_STANDARD}")
if(COMPILER_IS_MSVC)
    message(STATUS "MSVC Runtime: ${CMAKE_MSVC_RUNTIME_LIBRARY}")
endif()
message(STATUS "Output: ${CMAKE_BINARY_DIR}/bin")
message(STATUS "==============================")

# 清理目标
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning build directory"
)