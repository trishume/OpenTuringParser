#include "TuringParser/ParseError.h"

#include <cctype>
#include <sstream>

using namespace OTParser;

//! Function that converts almost any type to a string
template<class T>
static std::string MyToString(T i)
{
    std::ostringstream ss;
    std::string s;
    ss << i;
    s = ss.str();
    
    return s;
}


std::string ParseError::getFormatForType(ParseError::ErrType type) {
	switch(type) {
		case ParseError::UNKNOWN: return "An unknown error occured";
#define PARSE_ERROR(id,err) case ParseError::id: return err;
#include "TuringParser/ParseErrors.h"
#undef PARSE_ERROR
	}
    return ""; // never reaches here, switch handles all cases
}

ParseError& ParseError::operator<<(std::string arg) {
    Args.push_back(arg);
    return *this;
}
ParseError& ParseError::operator<<(int arg) {
    Args.push_back(MyToString(arg));
    return *this;
}
ParseError& ParseError::operator<<(char arg) {
    Args.push_back(MyToString(arg));
    return *this;
}

std::string ParseError::getMessage() {
	std::string format = getFormatForType(Type);
    
    // replace all the format specifiers
    size_t found=format.find_first_of("%");
    while (found!=std::string::npos)
    {
        // the number that comes after the format specifier
        char num = format[found+1];
        // the position to continue finding more formats after
        size_t continuePos = found+1;
        if (isdigit(num)) {
            // this gets the value of the digit because ascii numbers are in order
            int digit = num - '0';
            std::string arg = Args[digit];
            // replace 2 charecters (%n) with the arg
            format.replace(found, 2, arg);
            // start finding after the arg we have just swapped in
            continuePos = found + arg.size();
        }
        found=format.find_first_of("%",continuePos);
    }
    return format;
}