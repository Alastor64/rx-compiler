# =============================================================================
# Rx 编译器前端构建脚本（当前只到词法阶段：先把 ANTLR 生成的词法分析器
# 编成一个静态库 rx_lexer）。
#
# 用法：在仓库根目录执行下面两条命令
#   cmake -S . -B build      第 1 步：读本文件，在 build/ 里生成构建系统
#   cmake --build build -j   第 2 步：真正编译，产物是 build/librx_lexer.a
#
# 三条前提约定：
#   1. 本文件不往仓库里写任何东西；所有生成物都在 build/ 里（build/ 已被
#      .gitignore 忽略，不影响 git 状态）。
#   2. gencpp/、lib/、include/antlr4-runtime/ 是你本机准备好的文件，本文件
#      只读它们，不生成也不修改。
#   3. 不要把本文件复制进 gencpp/，也不要在这几个目录里再建别的 CMake 工程。
# =============================================================================


# -----------------------------------------------------------------------------
# 本工程要求的 CMake 最低版本。
# 3.16 是 Ubuntu 22.04 自带 cmake(3.22) 以下的安全值，且足够支持本文件所有写法。
# 不要往下调：新版 CMake(4.x) 已不再兼容低于 3.5 的写法，会直接报错。
# -----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.16)


# -----------------------------------------------------------------------------
# 声明工程名和用到的语言。
#   rx-compiler ：工程名。它只影响 CMake 自动生成的变量名（例如
#                 rx-compiler_SOURCE_DIR）和 IDE 里显示的工程名，
#                 和最终可执行文件叫什么名字无关。
#   LANGUAGES CXX：只需要 C++ 编译器；不写 C，CMake 就不会去找 C 编译器。
# -----------------------------------------------------------------------------
project(rx-compiler LANGUAGES CXX)


# -----------------------------------------------------------------------------
# 全局编译设置：对本文件后面定义的所有 target 都生效。
# -----------------------------------------------------------------------------

# ANTLR 4.13.2 的 C++ 运行时头文件用到了 C++17 特性，所以标准至少要是 17。
set(CMAKE_CXX_STANDARD 17)

# 如果当前编译器不支持 C++17，就让 CMake 直接报错。
# 不写这句的话，CMake 可能悄悄降级到旧标准，然后在编译时爆出一堆莫名其妙的错误。
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 关掉编译器扩展：传 -std=c++17 而不是 -std=gnu++17。
# 生成代码和 runtime 都按标准 C++17 写，关掉扩展可以避免方言差异带来的怪问题。
set(CMAKE_CXX_EXTENSIONS OFF)

# 让 CMake 在 build/ 下额外生成 compile_commands.json。
# clangd / IntelliSense 靠它知道“每个文件是用什么参数编译的”（头文件路径、宏、
# C++ 标准等）。这个文件也在 build/ 里，不会进仓库。
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 只有“单配置生成器”（Unix Makefiles、Ninja）才需要手动指定构建类型；
# 多配置生成器（Visual Studio 那类）由 IDE 自己选，不能在这里强设，
# 所以要判断 CMAKE_CONFIGURATION_TYPES 是否为空。
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)

    # 默认用 Release（即 -O3 -DNDEBUG）。生成代码很大，Debug 会明显更慢。
    #   CACHE STRING：把它做成可缓存变量，命令行仍可用
    #                 -DCMAKE_BUILD_TYPE=Debug 覆盖。
    #   FORCE       ：在“用户没指定”的情况下，把默认值写进缓存。
    # （只有上面的 if 成立才会走到这里，所以命令行传进来的值不会被覆盖。）
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)

# 结束 if
endif()


# -----------------------------------------------------------------------------
# 找到 ANTLR4 的 C++ 运行时。
#
# 你准备好的运行时自带一份 CMake“包描述文件”：
#     lib/cmake/antlr4-runtime/antlr4-runtime-config.cmake
# find_package 读到它以后，会自动创建一个叫 antlr4_static 的“导入目标”，
# 那个目标里已经写好了头文件目录、静态库路径和 Threads 依赖。
# 所以：不要自己写 include_directories / link_directories / 手动指定 .a 路径。
# -----------------------------------------------------------------------------

# 先确认包描述文件真的存在，不存在就给一句人话提示，
# 而不是让后面冒出一堆 “antlr4-runtime not found” 之类的晦涩报错。
# CMAKE_CURRENT_SOURCE_DIR 就是本文件所在目录（即仓库根目录），
# 用它的好处是：无论你在哪个目录调用 cmake，路径都不会错。
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/cmake/antlr4-runtime/antlr4-runtime-config.cmake")

    # 立刻停止配置并打印这句话，退出码非 0。
    message(FATAL_ERROR "找不到 ANTLR4 C++ runtime：请把 include/antlr4-runtime/ 与 lib/ 放到仓库根目录。")

# 结束 if
endif()

# 查找这个包：
#   antlr4-runtime ：包名。带连字符是官方规定的名字，对应上面那个 -config.cmake 文件。
#   CONFIG         ：只认包自带的 xxx-config.cmake，不用 FindXXX.cmake 去猜。
#   REQUIRED       ：找不到就直接报错停止，而不是静默跳过。
#   PATHS ...      ：去哪里找包，也就是上面检查过的那个目录。
#   NO_DEFAULT_PATH：禁止再去系统目录（如 /usr/lib/cmake）里找别的版本，
#                    防止和你这份 runtime 混用，造成符号不匹配。
find_package(antlr4-runtime CONFIG REQUIRED
    PATHS "${CMAKE_CURRENT_SOURCE_DIR}/lib/cmake/antlr4-runtime"
    NO_DEFAULT_PATH)


# -----------------------------------------------------------------------------
# 变量：ANTLR 生成的代码放在哪。
# 仓库根下的 gencpp/ 里是 run_antlr.sh 生成的 RxLexer.cpp / RxLexer.h。
# 定义成变量是为了下面多处引用同一个路径，将来换目录只改这一行。
# -----------------------------------------------------------------------------
set(RX_GEN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/gencpp")

# 生成代码不存在时给出人话提示（要先去跑生成脚本），
# 避免编译器抛 “RxLexer.h: No such file or directory”这种看不出原因的错。
if(NOT EXISTS "${RX_GEN_DIR}/RxLexer.cpp")

    # 提示里直接写清楚该做什么。
    # 注意：run_antlr.sh 内部是 cd ./grammar 之后再引用 ../tools 和 ../gencpp，
    # 那些相对路径只有在仓库根目录执行时才成立，所以必须在根目录跑它。
    message(FATAL_ERROR "找不到 ${RX_GEN_DIR}/RxLexer.cpp：请在仓库根目录执行 ./run_antlr.sh 生成。")

# 结束 if
endif()


# -----------------------------------------------------------------------------
# 词法分析库：把 ANTLR 生成的 RxLexer.cpp 编成一个静态库。
#   rx_lexer      ：target 的名字；构建产物是 build/librx_lexer.a。
#   STATIC        ：静态库。它会被链接进最终的可执行文件，运行时不需要额外带库文件。
#   最后一个参数  ：要编译的源文件。.h 由 #include 自动带进来，不需要在这里列。
# -----------------------------------------------------------------------------
add_library(rx_lexer STATIC "${RX_GEN_DIR}/RxLexer.cpp")

# 把“生成代码目录”暴露给所有链接了 rx_lexer 的目标。
#   PUBLIC 的含义：我自己编译需要这个路径，链接我的人（比如以后的可执行文件）
#   也自动需要。所以以后 add_executable(rxc ...) 只要链接 rx_lexer，
#   就能直接 #include "RxLexer.h"，不必再写一遍 include 路径。
target_include_directories(rx_lexer PUBLIC "${RX_GEN_DIR}")

# 链接 ANTLR 运行时（上面 find_package 造出来的导入目标）。
# 同样用 PUBLIC，因为 RxLexer.h 里 #include 了 antlr4-runtime.h，
# 任何使用 rx_lexer 的目标都必须能看到那些头文件、也必须链接上这个静态库。
# 这一行同时会把 antlr4_static 自带的 Threads 依赖一起带上。
target_link_libraries(rx_lexer PUBLIC antlr4_static)

# Windows 专用：antlr4_static 是静态库，而运行时头文件默认会把符号标成
# “从 DLL 导入”。不定义 ANTLR4CPP_STATIC，Windows 下链接会报找不到符号。
# 你这份 runtime 是 Linux 版，在 WSL 里编译时这段不会生效；
# 留着是为了将来万一换成 Windows 版 runtime 时不用改文件。
if(WIN32)

    # PUBLIC：使用 rx_lexer 的人也一并带上这个宏。
    target_compile_definitions(rx_lexer PUBLIC ANTLR4CPP_STATIC)

# 结束 if
endif()

# 关掉 ANTLR 生成代码自身产生的告警（继承相关、未使用参数等，数量很多），
# 否则你自己代码里真正的告警会被淹没。
#   PRIVATE：只作用于编译 RxLexer.cpp 这件事，不污染你自己的源码。
#   $<...>  ：生成器表达式，按编译器类型二选一：
#             非 MSVC 的 GCC/Clang/AppleClang 用 -w，MSVC 用 /w。
target_compile_options(rx_lexer PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-w>
    $<$<CXX_COMPILER_ID:MSVC>:/w>)


# -----------------------------------------------------------------------------
# 以后做语法分析阶段时，把下面几行的注释去掉即可（现在留作参考）。
#   add_library(rx_parser STATIC ...)
#       把 ANTLR 生成的 RxParser.cpp 等文件再编成一个静态库。
#       RxParserBaseListener.cpp / RxParserBaseVisitor.cpp 是 listener / visitor
#       基类的实现文件（基本是空壳），跟着一起编。
#   target_include_directories(rx_parser PUBLIC "${RX_GEN_DIR}")
#       和 rx_lexer 一样，暴露生成代码目录。
#   target_link_libraries(rx_parser PUBLIC rx_lexer)
#       parser 内部要用到 RxLexer 的类型（token 常量、CommonTokenStream 等），
#       所以链接 rx_lexer。用 PUBLIC 是为了让“链接 rx_parser 的人”也自动
#       获得 lexer 的头文件和库。
# -----------------------------------------------------------------------------
add_library(rx_parser STATIC
    "${RX_GEN_DIR}/RxParser.cpp"
    "${RX_GEN_DIR}/RxParserBaseListener.cpp"
    "${RX_GEN_DIR}/RxParserBaseVisitor.cpp")
target_include_directories(rx_parser PUBLIC "${RX_GEN_DIR}")
target_link_libraries(rx_parser PUBLIC rx_lexer)



# =============================================================================
# 你自己的代码：src/ 根目录放实现和头文件，src/main/ 放带 main() 的入口
#
# 目录约定：
#   src/*.hpp  src/*.cpp     你的头文件和实现 → 编成静态库 rx_my
#   src/main/*.cpp           每个文件 → 一个可执行文件（文件名即可执行文件名）
#
# 三层结构：rx_lexer（ANTLR 生成代码）← rx_my（你的实现）← 各个入口
# =============================================================================

# 你的源码根目录（仓库根下的 src/）。
set(RX_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

# 收集 src/ 根目录下的 .cpp 和 .hpp。
#   GLOB 不递归进子目录，所以 src/main/*.cpp 不会被收进库里 —— 这正是我们要的：
#   带 main() 的文件如果进了库，链接可执行文件时可能撞车（重复的 main）。
#   CONFIGURE_DEPENDS：以后新增/删除文件，下次 build 会自动重新扫描，不用手动重跑 cmake。
file(GLOB RX_MY_SOURCES CONFIGURE_DEPENDS "${RX_SRC_DIR}/*.cpp")
file(GLOB RX_MY_HEADERS CONFIGURE_DEPENDS "${RX_SRC_DIR}/*.hpp")

# 一个 .cpp 都没有时报错（例如目录被改名），而不是静默编出一个空库。
if(NOT RX_MY_SOURCES)
    message(FATAL_ERROR "${RX_SRC_DIR} 下没有找到任何 .cpp 文件。")
endif()

# 你的实现编成静态库，产物 build/librx_my.a。
# （头文件列进来只是为了让 IDE 能看到它们，不参与编译。）
add_library(rx_my STATIC ${RX_MY_SOURCES} ${RX_MY_HEADERS})

# PUBLIC：链接 rx_my 的目标自动获得 src/ 头文件路径，
# 于是 src/main/*.cpp 里可以直接 #include "tokenizer.hpp"。
target_include_directories(rx_my PUBLIC "${RX_SRC_DIR}")

# 你的代码要用 ANTLR 的类（RxLexer 等），所以链接 rx_lexer。
# PUBLIC：你的头文件里暴露了 ANTLR 类型（tokenizer.hpp 里 #include 了 RxLexer.h），
# 链接你的可执行文件同样需要这些头文件和运行时。
target_link_libraries(rx_my PUBLIC rx_parser)

# 可选：给你自己的代码打开常用告警（生成代码那边已用 -w 关掉，互不影响）。
# target_compile_options(rx_my PRIVATE
#     $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall;-Wextra>)


# -----------------------------------------------------------------------------
# src/main/ 下每个 .cpp 生成一个可执行文件：
#   src/main/dump.cpp  -> build/dump
#   src/main/count.cpp -> build/count
# 可执行文件名 = 去掉 .cpp 的文件名，所以别用中文或空格命名。
# -----------------------------------------------------------------------------
file(GLOB RX_MAIN_SOURCES CONFIGURE_DEPENDS "${RX_SRC_DIR}/main/*.cpp")

foreach(main_source IN LISTS RX_MAIN_SOURCES)
    # NAME_WE：去掉目录和扩展名的文件名，例如 ".../src/main/dump.cpp" → "dump"
    get_filename_component(main_name "${main_source}" NAME_WE)

    # 只包含这一个 main 文件的可执行文件
    add_executable("${main_name}" "${main_source}")

    # PRIVATE：这个可执行文件自己需要 rx_my，不传染给别人
    target_link_libraries("${main_name}" PRIVATE rx_my)
endforeach()

# 一个入口都没有时提示一下（不是错误，可能你正在重构）
if(NOT RX_MAIN_SOURCES)
    message(STATUS "src/main/ 下没有 .cpp，本次不生成任何可执行文件。")
endif()