#pragma once

#include "interface/ISocket.hpp"
#include <functional>

/**
 * @brief receive logic. We pass it a socket and loop on the receive function of it. In the loop, after every socket.receive(), we call the callbackFunction on the packets received.
 * @param socket is the socket on which we will receive the packets
 * @param maxConsecutiveErrors is the threshold for consecutive network errors we allow
 * @param callbackFunction is the callback function that will be called after each receive. It must only be able to throw CallbackError
 * @return 1 if too many network errors, 2 if callback error. Shouldn't terminate so no success return.
 */
int receiveSocket(ISocket &socket, int maxConsecutiveErrors, std::function<void(std::span<const std::uint8_t>)> callbackFunction);