#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <cstdint>

#include "parsing/GyroParser.hpp"
#include "CallbackError.hpp"


TEST(ParserTest, FunctionProperly){
    const std::string buffer_str = {"-5.5E-4,-2.75E-4,0.0\r\n"};
    const std::uint8_t *begin = reinterpret_cast<const std::uint8_t *>(buffer_str.data());

    std::vector<std::uint8_t> buffer = {begin, begin + buffer_str.size()};
    GyroPosition pos = parseGyroFromResult(buffer);

    EXPECT_DOUBLE_EQ(pos.x, -5.5E-4);
    EXPECT_DOUBLE_EQ(pos.y, -2.75E-4);
    EXPECT_DOUBLE_EQ(pos.z, 0.0);
}

TEST(ParserTest, ErrorProperly){
    const std::string buffer_str = {"-5.5E-4abc,-2.75E-4,0.0\r\n"};
    const std::uint8_t *begin = reinterpret_cast<const std::uint8_t *>(buffer_str.data());

    std::vector<std::uint8_t> buffer = {begin, begin + buffer_str.size()};
    EXPECT_THROW(parseGyroFromResult(buffer), CallbackError);
}

TEST(GyroParserTest, RejectEmptyPacket) {
    std::vector<std::uint8_t> buffer = {};
    EXPECT_THROW(parseGyroFromResult(buffer), CallbackError);
}