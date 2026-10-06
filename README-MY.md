# Rx编译器

## 本项目环境为windows wsl

## 如何使用

### lexer&parser

使用的antlr版本antlr-4.13.2-complete，将其jar文件放置于tools目录中

运行run_antlr.sh生成C++的词法分析器和语法分析器于gencpp目录中

编译语法分析器需要对应版本的runtime
下载[antlr4-cpp-runtime-4.13.2-source.zip](https://www.antlr.org/download/antlr4-cpp-runtime-4.13.2-source.zip)
解包后运行

```sh
cmake -S . -B build-wsl -DCMAKE_BUILD_TYPE=Release \
  -DANTLR_BUILD_CPP_TESTS=OFF \
  -DANTLR_BUILD_SHARED=OFF -DANTLR_BUILD_STATIC=ON \
  -DANTLR4_INSTALL=ON -DDISABLE_WARNINGS=ON \
  -DCMAKE_INSTALL_PREFIX=$PWD/install-wsl
cmake --build build-wsl -j
cmake --install build-wsl
```

将install-wsl中的include和lib文件夹拷到项目根目录中

在根目录下执行build.sh即可在build目录中构建lexer库“librx_lexer.a”
