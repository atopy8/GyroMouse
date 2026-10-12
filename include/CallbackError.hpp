#pragma once

#include <stdexcept>
#include <string>

/**
 * @class CallbackError
 * @brief Used to distinguish runtime error from error happening during the callback function of the receive function of the socket.
 * @details For example if during the receive function of the socket, we call a callback function "parse" and this function throws an error, it should be a callbackerror instead of a 
 * std::runtime_error so it doesn't count as a network error.
 */
class CallbackError : public std::runtime_error {
    public:
        explicit CallbackError(const std::string& message) : std::runtime_error(message) {}
};