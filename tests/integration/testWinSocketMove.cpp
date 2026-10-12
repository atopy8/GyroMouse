#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>
#include <utility>

#include "windows/WinNetworkContext.hpp"
#include "windows/WinSocket.hpp"

namespace {
constexpr std::uint16_t PORT_A = 54321;
constexpr std::uint16_t PORT_B = 54322;
}

// Move constructor: the destination takes over a working socket,
// the source is left invalid.
TEST(WinSocketMove, MoveConstructorTransfersOwnership) {
    auto context = std::make_shared<WinNetworkContext>();
    WinSocket source(context);

    WinSocket destination(std::move(source));

    EXPECT_NO_THROW(destination.bindPort(PORT_A));          // destination works
    EXPECT_THROW(source.bindPort(PORT_B), std::runtime_error); // source is INVALID_SOCKET
}

// Move assignment: the destination's OLD socket must be closed,
// and the source's socket must take its place.
TEST(WinSocketMove, MoveAssignmentClosesPreviousSocket) {
    auto context = std::make_shared<WinNetworkContext>();

    WinSocket destination(context);
    destination.bindPort(PORT_A);   // destination currently holds PORT_A

    WinSocket source(context);
    source.bindPort(PORT_B);

    destination = std::move(source); // PORT_A's socket must be closed here

    // If the old socket had leaked, PORT_A would still be taken and this would throw.
    WinSocket probe(context);
    EXPECT_NO_THROW(probe.bindPort(PORT_A));
}

// The shared context must stay alive as long as a socket uses it,
// even if every other owner is gone.
TEST(WinSocketMove, SocketOutlivesOtherContextOwners) {
    auto context = std::make_shared<WinNetworkContext>();
    WinSocket socket(context);
    context.reset(); // the socket is now the last owner of the context

    EXPECT_NO_THROW(socket.bindPort(PORT_A));
}