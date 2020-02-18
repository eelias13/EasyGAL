#include "Main.hpp"

using namespace std;

int main()
{
    vector<string> code;
    code.push_back("pin 22 =iPin;");
    code.push_back("pin 3=oPin1;");
    code.push_back("pin 4 = oPin2;");
    code.push_back("iPin = oPin1 & oPin2;");

    vector<Pair> tokenPairs = Lexer::tokenize(Lexer::spit(code));
    Helper::printPare(tokenPairs);
}