cd ./grammar
java -jar ../tools/antlr-4.13.2-complete.jar -Dlanguage=Cpp -visitor -o ../gencpp RxLexer.g4 RxParser.g4
cd ..