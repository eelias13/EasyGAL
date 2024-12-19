# Emscripten compiler
CC = g++

# Flags for compilation
CFLAGS = -O3 -Wall -Wno-unused-label -std=c++17 -I./Shared -I./Parser -I./Translator

# Exported functions for Emscripten
EXTRA_FLAGS = -s EXPORTED_FUNCTIONS='["_tableData2jedec", "_code2TableData", "_compile"]'

# Source files
SOURCES = Shared/Utility.cpp \
          Shared/API.cpp \
          Shared/Validate.cpp \
          Parser/Lexer.cpp \
          Parser/Parser.cpp \
          Parser/Error.cpp \
          Parser/FunctionParser.cpp \
          Parser/TableParser.cpp \
          Translator/DNF.cpp \
          Translator/Fuses.cpp \
          Translator/Helper.cpp \
          Translator/Serialization.cpp \
          Translator/Translator.cpp \
          Translator/Configs.cpp 

# Target WebAssembly module
WASM_MODULE = easy_gal.js
EXECUTABLE = EasyGAL 


wasm: $(WASM_MODULE)
bin: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES) Compiler.cpp 
	$(CC) $(CFLAGS) -o $@ $^

$(WASM_MODULE): $(SOURCES) WasmMain.cpp 
	em++ $(CFLAGS) $(EXTRA_FLAGS) -o $@ $^

clean:
	rm -f $(WASM_MODULE) $(EXECUTABLE) easy_gal.wasm *.o ./Shared/*.o ./Parser/*.o ./Translator/*.o

