#include <gtest/gtest.h>
#include "MockSocket.hpp"
#include "ReceiveSocket.hpp"
#include "CallbackError.hpp"

ACTION(MyThrowException){
    throw std::runtime_error("simulated");
}


TEST(SocketTestBase, One) {
    EXPECT_EQ(1, 1);
}

TEST(SocketTest, TooMuchErrors){
    MockSocket mock;
    EXPECT_CALL(mock, receive(testing::_))
        .Times(4)
        .WillRepeatedly(MyThrowException());

    std::function<void(std::span<const uint8_t>)> emptyCallback = [](std::span<const uint8_t> buffer) {};

    EXPECT_EQ(1, receiveSocket(mock, 3, emptyCallback));
}

TEST(SocketTest, RecoversAfterError){
    MockSocket mock;

    EXPECT_CALL(mock, receive(testing::_))
        .Times(5)
        .WillOnce(MyThrowException())
        .WillOnce(testing::Return(0))
        .WillOnce(MyThrowException())
        .WillOnce(MyThrowException())
        .WillOnce(MyThrowException());

    std::function<void(std::span<const uint8_t>)> emptyCallback = [](std::span<const uint8_t> buffer) {};

    EXPECT_EQ(1, receiveSocket(mock, 2, emptyCallback));
}

TEST(SocketTest, DataCallback){
    MockSocket mock;

    const std::vector<std::uint8_t> fakeData = {0x01, 0x02, 0x03};

    EXPECT_CALL(mock, receive(testing::_))
        .WillOnce([fakeData](std::span<std::uint8_t> buffer) -> std::size_t {
                std::size_t size = fakeData.size();
                for (std::size_t i = 0; i < size; i++){
                    buffer[i] = fakeData[i];
                }
                return fakeData.size();
            })
        .WillOnce(MyThrowException())
        .WillOnce(MyThrowException())
        .WillOnce(MyThrowException());

    std::vector<std::uint8_t> received;
    std::function<void(std::span<const std::uint8_t>)> captureCallback = [&received](std::span<const std::uint8_t> data){
            received.assign(data.begin(), data.end());
        };

    receiveSocket(mock, 2, captureCallback);

    EXPECT_EQ(fakeData, received);
}

TEST(SocketTest, CallbackError){
    MockSocket mock;

    const std::vector<std::uint8_t> fakeData = {0x01, 0x02, 0x03};

    EXPECT_CALL(mock, receive(testing::_))
        .Times(1)
        .WillOnce([fakeData](std::span<std::uint8_t> buffer) -> std::size_t
                  {
                std::size_t size = fakeData.size();
                for (std::size_t i = 0; i < size; i++){
                    buffer[i] = fakeData[i];
                }
                return fakeData.size(); });

    std::vector<std::uint8_t> received;
    std::function<void(std::span<const std::uint8_t>)> errCallback = [&received](std::span<const std::uint8_t> data)
    {
        throw CallbackError("Simulating callback error");
    };

    

    EXPECT_EQ(2, receiveSocket(mock, 3, errCallback));
}