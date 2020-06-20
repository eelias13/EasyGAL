CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=../Main.cpp ../Compiler/Lexer.cpp ../Compiler/Parser.cpp ../Compiler/Error.cpp ../Compiler/FunctionParser.cpp ../Compiler/TableParser.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=EasyGal

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)