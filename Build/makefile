CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=../EasyGAL.cpp ../Compiler/Lexer.cpp ../Compiler/Parser.cpp ../Compiler/Error.cpp ../Compiler/FunctionParser.cpp ../Compiler/TableParser.cpp ../Shared/Error.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=../EasyGAL

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)