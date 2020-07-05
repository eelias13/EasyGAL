CC=g++
CFLAGS=-c -Wall
LDFLAGS=
OTHER=EasyGAL.cpp 
PARSER=Parser/Lexer.cpp Parser/Parser.cpp Parser/Error.cpp Parser/FunctionParser.cpp Parser/TableParser.cpp
TRANSLATOR=Translator/DNF.o Translator/Fuses.cpp Translator/Helper.cpp Translator/Serialization.cpp Translator/Translator.cpp
OBJECTS=$(PARSER:.cpp=.o) $(OTHER:.cpp=.o) $(TRANSLATOR:.cpp=.o)
EXECUTABLE=EasyGAL

all: parser translator other

other: $(OTHER) $(EXECUTABLE)

parser: $(PARSER) $(EXECUTABLE)

translator: $(TRANSLATOR) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)