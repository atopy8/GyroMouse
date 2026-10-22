#include <span>
#include <vector>
#include <string>
#include <string_view>
#include <charconv>
#include <format>


#include "parsing/GyroParser.hpp"
#include "CallbackError.hpp"

double parseField(std::string_view field, std::size_t packetSize) {
    double value = 0.0;
    const char *begin = field.data();
    const char *end = begin + field.size();

    std::from_chars_result result = std::from_chars(field.data(), field.data() + field.size(), value);
    if (result.ec != std::errc{} || result.ptr != end || !std::isfinite(value)) {
        throw CallbackError(std::format("Invalid number in packet of size {}", packetSize));
    }
    return value;
}

GyroPosition parseGyroFromResult(std::span<std::uint8_t> buffer){
    if (buffer.size()==0){
        throw CallbackError(std::format("Empty Packets"));
    }  

    std::string_view line(reinterpret_cast<const char *>(buffer.data()), buffer.size());
    
    //we strip \r\n
    if (line.ends_with('\n')) {
        line.remove_suffix(1);
        if (line.ends_with('\r')) {
            line.remove_suffix(1);
        }
    }

    const std::size_t firstComma = line.find(',');
    const std::size_t secondComma =
        (firstComma == std::string_view::npos) ? std::string_view::npos
                                               : line.find(',', firstComma + 1);
    if (secondComma == std::string_view::npos) {
        throw CallbackError(std::format("Expected 3 fields in packet of size {}", buffer.size()));
    }

    const std::string_view xField = line.substr(0, firstComma);
    const std::string_view yField = line.substr(firstComma + 1, secondComma - firstComma - 1);
    const std::string_view zField = line.substr(secondComma + 1);

    // Each field must be fully consumed and finite.
    return GyroPosition{
        parseField(xField, buffer.size()),
        parseField(yField, buffer.size()),
        parseField(zField, buffer.size()),
    };
}