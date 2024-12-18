#include <emscripten/emscripten.h>
#include <vector>
#include <string>

#include "Shared/Validate.h"
#include "Shared/TableData.h"
#include "Shared/Dependencies/json.hpp"
#include "Shared/Utility.h"
#include "Shared/API.h"
#include "Parser/Parser.h"
#include "Parser/Error.h"
#include "Translator/Translator.hpp"
#include "Translator/Configs.h"

using namespace std;

extern "C"
{
	EMSCRIPTEN_KEEPALIVE
	const char *tableData2jedec(const char *tableDataJson, const char *deviceName)
	{
		// Use different variable names to avoid shadowing
		string tdJson = std::string(tableDataJson);
		string devName = std::string(deviceName);

		// Use a static string to avoid returning a pointer to a local variable
		static string output;
		output = api::tableData2jedec(tdJson, devName);
		return output.c_str();
	}

	EMSCRIPTEN_KEEPALIVE
	const char *code2TableData(const char *easyGALCode, const char *deviceName)
	{
		string egCode = std::string(easyGALCode);
		string devName = std::string(deviceName);

		static string output;
		output = api::code2TableData(egCode, devName);
		return output.c_str();
	}

	EMSCRIPTEN_KEEPALIVE
	const char *compile(const char *easyGALCode, const char *deviceName)
	{
		string egCode = std::string(easyGALCode);
		string devName = std::string(deviceName);

		Parser parser = Parser(egCode);
		vector<TableData> tableData = parser.parse();

		Configs::CircuitConfig DeviceType;
		vector<uint32_t> inputPins;
		vector<uint32_t> outputPins;
		initDeviceType(DeviceType, devName, inputPins, outputPins);
		validate(tableData, inputPins, outputPins);

		static string output;
		output = Translator::Process(tableData, DeviceType);
		return output.c_str();
	}
}
