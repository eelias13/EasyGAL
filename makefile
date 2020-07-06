# g++ settings
CC=g++
CFLAGS=-c -Wall
LDFLAGS=


# files for compiler
COMPILER_MAIN=Compiler.cpp
PARSER=Parser/Lexer.cpp Parser/Parser.cpp Parser/Error.cpp Parser/FunctionParser.cpp Parser/TableParser.cpp
TRANSLATOR=Translator/DNF.cpp Translator/Fuses.cpp Translator/Helper.cpp Translator/Serialization.cpp Translator/Translator.cpp
# all object for compiler
COMPILER_OBJECTS=$(PARSER:.cpp=.o) $(COMPILER_MAIN:.cpp=.o) $(TRANSLATOR:.cpp=.o)
# name of compiler executable
COMPILER_EXECUTABLE=EasyGAL 


# files for simulator
SIMULATOR_MAIN=Sim/Simulator.cpp Sim/Gal.cpp 
INTERFACE=Sim/CLI.cpp
# all object for simulator
SIMULATOR_OBJECTS=$(SIMULATOR_MAIN:.cpp=.o) $(INTERFACE:.cpp=.o) 
# name of simulator executable
SIMULATOR_EXECUTABLE=EasySim

# general build logic
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
simulator: simulator_shared interface simulator_main
simulator_main: $(SIMULATOR_MAIN) $(SIMULATOR_EXECUTABLE)
interface: $(INTERFACE) $(SIMULATOR_EXECUTABLE)


# build instruction for compiler
compiler: parser translator compiler_shared compiler_main
compiler_main: $(COMPILER_MAIN) $(COMPILER_EXECUTABLE)
parser: $(PARSER) $(COMPILER_EXECUTABLE)
translator: $(TRANSLATOR) $(COMPILER_EXECUTABLE)
