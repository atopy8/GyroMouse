#include <span>
#include <vector>
#include <string>
#include <charconv>
#include <format>


#include "parsing/GyroParser.hpp"
#include "CallbackError.hpp"

GyroPosition parseGyroFromResult(std::span<std::uint8_t> buffer){
    std::string s(reinterpret_cast<char *>(buffer.data()), buffer.size());

    double values[3];
    for (int i = 0; i < 3; i++){
        const std::size_t sepIdx = s.find(",");
        if (i<2 && sepIdx == std::string::npos){
            throw CallbackError(std::format("No comma found when parsing line {}", buffer));
        }

        const std::string field = s.substr(0, sepIdx);
        std::from_chars_result result = std::from_chars(field.data(), field.data() + field.size(), values[i]);
        if (result.ec != std::errc{} || result.ptr != field.data() + field.size()){
            throw CallbackError(std::format("Invalid format for double in line {}", buffer));
        }

        if (i == 2)
            s = "";
        else
            s = s.substr(sepIdx + 1);
    }

    GyroPosition result = {values[0], values[1], values[2]};
    return result;
}