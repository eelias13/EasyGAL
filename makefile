CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=Main.cpp Lexer.cpp Parser.cpp Error.cpp FunctionParser.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=EasyGal

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)