CC=g++
CFLAGS=-c -Wall
LDFLAGS=
OTHER=../EasyGAL.cpp  ../Shared/Error.cpp 
COMPILER=../Compiler/Lexer.cpp ../Compiler/Parser.cpp ../Compiler/Error.cpp ../Compiler/FunctionParser.cpp ../Compiler/TableParser.cpp
TRANSLATOR=../Translator/DNF.o ../Translator/Fuses.cpp ../Translator/Helper.cpp ../Translator/Serialization.cpp ../Translator/Translator.cpp
OBJECTS=$(COMPILER:.cpp=.o) $(OTHER:.cpp=.o) $(TRANSLATOR:.cpp=.o)
EXECUTABLE=../EasyGAL

all: other compiler translator

other: $(OTHER) $(EXECUTABLE)

compiler: $(COMPILER) $(EXECUTABLE)

translator: $(TRANSLATOR) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)