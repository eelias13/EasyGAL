# manual build: 
# g++ *.cpp Compiler/*.cpp Compiler/FunctionParser/*cpp Compiler/Lexer/*.cpp Compiler/Linker/*.cpp Compiler/PreCompiler/*cpp Compiler/StackHelper/*.cpp

EasyGal: Main.o FunctionParser.o LookUpTable.o Node.o ShuntingYard.o Lexer.o Token.o Linker.o PreCompiler.o StackHelper.o Compiler.o Helper.o Table.o
	g++ Main.o FunctionParser.o LookUpTable.o Node.o ShuntingYard.o Lexer.o Token.o Linker.o PreCompiler.o StackHelper.o Compiler.o Helper.o Table.o -o EasyGal

# in Main
Main.o: Main.cpp Main.hpp
	g++ -c Main.cpp

# in Compiler
FunctionParser.o: Compiler/FunctionParser/FunctionParser.cpp Compiler/FunctionParser/FunctionParser.hpp
	g++ -c Compiler/FunctionParser/FunctionParser.cpp

LookUpTable.o: Compiler/FunctionParser/LookUpTable.cpp Compiler/FunctionParser/LookUpTable.hpp
	g++ -c Compiler/FunctionParser/LookUpTable.cpp 

Node.o: Compiler/FunctionParser/Node.cpp Compiler/FunctionParser/Node.hpp 
	g++ -c Compiler/FunctionParser/Node.cpp

ShuntingYard.o: Compiler/FunctionParser/ShuntingYard.cpp Compiler/FunctionParser/ShuntingYard.hpp
	g++ -c Compiler/FunctionParser/ShuntingYard.cpp

Lexer.o: Compiler/Lexer/Lexer.cpp Compiler/Lexer/Lexer.hpp
	g++ -c Compiler/Lexer/Lexer.cpp

Token.o: Compiler/Lexer/Token.cpp Compiler/Lexer/Token.hpp
	g++ -c Compiler/Lexer/Token.cpp

Linker.o: Compiler/Linker/Linker.cpp Compiler/Linker/Linker.hpp
	g++ -c Compiler/Linker/Linker.cpp

PreCompiler.o: Compiler/PreCompiler/PreCompiler.cpp Compiler/PreCompiler/PreCompiler.hpp
	g++ -c Compiler/PreCompiler/PreCompiler.cpp

StackHelper.o: Compiler/StackHelper/StackHelper.cpp Compiler/StackHelper/StackHelper.hpp
	g++ -c Compiler/StackHelper/StackHelper.cpp

Compiler.o: Compiler/Compiler.cpp Compiler/Compiler.hpp
	g++ -c Compiler/Compiler.cpp

Helper.o: Helper.cpp Helper.hpp
	g++ -c Helper.cpp

Table.o: Compiler/Table.cpp Compiler/Table.hpp
	g++ -c Compiler/Table.cpp


# Translator


clean:
	rm Main.o 
	rm FunctionParser.o 
	rm LookUpTable.o
	rm Node.o 
	rm ShuntingYard.o
	rm Lexer.o 
	rm Token.o 
	rm Linker.o 
	rm PreCompiler.o 
	rm StackHelper.o 
	rm Compiler.o 
	rm Helper.o 
	rm Table.o
