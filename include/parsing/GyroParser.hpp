#pragma once

#include "parsing/GyroPosition.hpp"

GyroPosition parseGyroFromResult(std::span<std::uint8_t> result) throw(CallbackError);