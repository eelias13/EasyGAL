# -------------------------------------------------------- genreal --------------------------------------------------------

# g++ settings
CC = g++
CFLAGS = -c -Werror
LDFLAGS =

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

# -------------------------------------------------------- compiler --------------------------------------------------------

# files for compiler
COMPILER_MAIN = Compiler.cpp
PARSER = Parser/Lexer.cpp Parser/Parser.cpp Parser/Error.cpp Parser/FunctionParser.cpp Parser/TableParser.cpp
TRANSLATOR = Translator/DNF.cpp Translator/Fuses.cpp Translator/Helper.cpp Translator/Serialization.cpp  Translator/Translator.cpp  Translator/Configs.cpp

# all object for compiler
COMPILER_OBJECTS= $(COMPILER_MAIN:.cpp=.o) $(PARSER:.cpp=.o)  $(TRANSLATOR:.cpp=.o)

# name of compiler executable
COMPILER_EXECUTABLE = EasyGAL 

# g++ compiler instruction 
$(COMPILER_EXECUTABLE): $(COMPILER_OBJECTS)
	$(CC) $(LDFLAGS) $(COMPILER_OBJECTS) -o $@

# build instruction for compiler
compiler: parser translator compiler_main
compiler_main: $(COMPILER_MAIN) $(COMPILER_EXECUTABLE)
parser: $(PARSER) $(COMPILER_EXECUTABLE)
translator: $(TRANSLATOR) $(COMPILER_EXECUTABLE)

# -------------------------------------------------------- simulator --------------------------------------------------------

# files for simulator
SIMULATOR_MAIN = Sim/Simulator.cpp Sim/Gal.cpp 
INTERFACE = Sim/CLI.cpp

# all object for simulator
SIMULATOR_OBJECTS = $(SIMULATOR_MAIN:.cpp=.o) $(INTERFACE:.cpp=.o) 

# name of simulator executable
SIMULATOR_EXECUTABLE = EasySim

# g++ compiler instruction 
$(SIMULATOR_EXECUTABLE): $(SIMULATOR_OBJECTS)
	$(CC) $(LDFLAGS) $(SIMULATOR_OBJECTS) -o $@


# build instruction for simulator
simulator: interface simulator_main
simulator_main: $(SIMULATOR_MAIN) $(SIMULATOR_EXECUTABLE)
interface: $(INTERFACE) $(SIMULATOR_EXECUTABLE)

# -------------------------------------------------------- clean --------------------------------------------------------

clean:
	rm $(COMPILER_OBJECTS)
	rm $(SIMULATOR_OBJECTS)