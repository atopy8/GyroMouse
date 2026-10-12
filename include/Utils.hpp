#pragma once

#include <cstdint>

/**
 * @brief utils function to parse the argurments given by the user at the start of the code.
 * @param argc the argc passed to main (should be 1 or 2)
 * @param argv the argv passed to main 
 * @return 0 if error (not in 1:65535 range, not a number, wrong number of args, ...), else the port number (5000 by default (if argc == 1))
 */
std::uint16_t parsePort(const int argc, const char *argv[]);