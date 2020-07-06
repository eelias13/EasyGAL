# g++ settings
CC=g++
CFLAGS=-c -Wall
LDFLAGS=


# files for compiler
COMPILER_MAIN=Compiler.cpp Shared/Validate.cpp
PARSER=Parser/Lexer.cpp Parser/Parser.cpp Parser/Error.cpp Parser/FunctionParser.cpp Parser/TableParser.cpp
TRANSLATOR=Translator/DNF.cpp Translator/Fuses.cpp Translator/Helper.cpp Translator/Serialization.cpp Translator/Translator.cpp
# name of compiler executable
COMPILER_EXECUTABLE=EasyGAL 


# files for simulator
SIMULATOR_MAIN=Sim/Simulator.cpp Sim/Gal.cpp Sim/CLI.cpp Shared/Validate.cpp
# name of simulator executable
SIMULATOR_EXECUTABLE=EasySim


# general build instruction 
COMPILER_OBJECTS=$(PARSER:.cpp=.o) $(COMPILER_MAIN:.cpp=.o) $(TRANSLATOR:.cpp=.o) 
SIMULATOR_OBJECTS=$(SIMULATOR_MAIN:.cpp=.o) 

$(COMPILER_EXECUTABLE): $(COMPILER_OBJECTS)
	$(CC) $(LDFLAGS) $(COMPILER_OBJECTS) -o $@

$(SIMULATOR_EXECUTABLE): $(SIMULATOR_OBJECTS)
	$(CC) $(LDFLAGS) $(SIMULATOR_OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(COMPILER_OBJECTS)
	rm $(SIMULATOR_OBJECTS)
	


# build instruction for simulator
simulator: simulator_main

simulator_main: $(SIMULATOR_MAIN) $(SIMULATOR_EXECUTABLE)


# build instruction for compiler
compiler: parser translator compiler_main

compiler_main: $(COMPILER_MAIN) $(COMPILER_EXECUTABLE)

parser: $(PARSER) $(COMPILER_EXECUTABLE)

translator: $(TRANSLATOR) $(COMPILER_EXECUTABLE)
