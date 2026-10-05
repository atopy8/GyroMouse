#pragma once

#include "interface/ISocket.hpp"
#include <functional>

int receiveSocket(ISocket &socket, int maxConsecutiveErrors, std::function<void(std::span<const std::uint8_t>)> callbackFunction);