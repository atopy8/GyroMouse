#pragma once

#include <stdexcept>
#include <string>


class CallbackError : public std::runtime_error {
    public:
        explicit CallbackError(const std::string& message) : std::runtime_error(message) {}
};