#include <span>
#include <vector>
#include <string>
#include <charconv>


#include "parsing/GyroParser.hpp"
#include "CallbackError.hpp"

GyroPosition parseGyroFromResult(std::span<std::uint8_t> buffer){
    std::string s; // = reinterpret_cast<std::string>(result);
    std::from_chars_result res = std::from_chars(buffer.first(), buffer.first() + buffer.size(), s);
    std::string xString = s.substr(0, s.find(","));
    s.erase(0, s.find(","));
    std::string yString = s.substr(0, s.find(","));
    s.erase(0, s.find(","));
    std::string zString = s.substr(0, s.length());

    const int x = std::stod(xString);
    const int y = std::stod(yString);
    const int z = std::stod(zString);

    GyroPosition result = {x, y, z};
    return result;
}