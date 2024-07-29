#include "UDPClient.hpp"
#include "eth/EthGlobal.hpp"

#include "UDPSocket.hpp"
#include "eth/base/SocketAddress.hpp"

UDPClient::UDPClient(const uint32_t& sndBufSize)
    : _srcAddress{new SocketAddress}
    , _dstAddress{new SocketAddress}
    , _socket{new UDPSocket}
    , _sndBufSize{sndBufSize}
    , _sndBuf{new uint8_t[_sndBufSize]}
{
#ifdef DEBUG
    if(!_srcAddress) {
        ERROR_MSG("UDPClient: error _srcAddress not created!");
    }
    if(!_dstAddress) {
        ERROR_MSG("UDPClient: error _dstAddress not created!");
    }
    if(!_socket) {
        ERROR_MSG("UDPClient: error _socket not created!");
    }

    if(_sndBufSize <= 4) {
        ERROR_MSG("UDPClient: error (_sndBufSize < 4)");
    }
    if(!_sndBuf) {
        ERROR_MSG("UDPClient: error _sndBuf not created!");
    }
#endif
}

UDPClient::~UDPClient()
{
    _socket->close_();
    delete _srcAddress;
    delete _dstAddress;
    delete _socket;
    delete [] _sndBuf;
}

bool UDPClient::open(const SocketAddress& srcAddress, const SocketAddress& dstAddress)
{
    bool result = false;
    *_srcAddress = srcAddress;
    *_dstAddress = dstAddress;

    _socket->close_();
    _socket->setAddress(*_srcAddress);
    _socket->createSocket();
    if(_socket->isOpen()) {
        result = true;
    }
    return result;
}

void UDPClient::close()
{
    _socket->close_();
}

bool UDPClient::isSocketOpen()
{
    return _socket->isOpen();
}

bool UDPClient::send(const uint8_t* data, const int32_t& dataLength)
{
    return _socket->sndto(*_dstAddress, data, dataLength);
}
