# Projet Gyro Mouse

This project is for using the gyroscope of your phone as a mouse on your PC.

## Current architecture

For now, the project is in the first step : its receiving packets, having an implementation taking into account the next evolutions, being able to compile it wether its on windows or posix and having a test infrastructure put in place.

### Interfaces:

#### ISocket: 
*Interfacing the Socket object. The socket object can bind to a port and receive packets from the latter.*

#### ISocketFactory: 

*Using the Factory pattern, we can create sockets without having to worry about the platform using it (windows or posix) and having it returns abstract ISocket objects. The ISocketFactory object must be created by the SocketFactoryProvider, again to abstract the ISocketFactory for the end user.*

#### INetworkContext: 
*Interface of the network context object. Needed for windows (WSAStartup, WSACleanup, ...) we interface it to have a abstraction and having the same treatment not depending on a implementation for each platform.*

The implementation of these interfaces are made in the windows or posix directories.
One of these directories will be compiled, and the choice is being made with cmake, depending on the platform detected.

### Windows

#### WinNetworkContext:
*The ownership of the consext is shared between the factory and the sockets, so we are sure the context isn't closed before any of the sockets*

### ReceiveSocket:
*Function used to handle the receptions of a socket. Can handle a maximum of consecutive network errors (std::runtime_error) before returning 1(network error), or if the error comes from parsing and treatment, we catch CallbackError and return 2*


### Tests

A testing infrastructure has been put in place so the project is industry ready. It utilize google test/ mock.

## Futures evolutions

- step 2 : parsing the data

- multi phone supports : one socket per phone, each one in his reception loop -> having a productor/consumer logic. thread safe


