#pragma once

/**
 * @struct GyroPosition
 * @brief RAII for the gyro position resource. after parsing a movement, a line will be parsed into this object
 */
typedef struct GyroPosition_t {
    const double x;
    const double y;
    const double z;
} GyroPosition;