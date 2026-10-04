cd ./grammar
java -jar ../tools/antlr-4.13.2-complete.jar -Dlanguage=Cpp -visitor -o ../gencpp Lexer.g4 Parser.g4
cd ..