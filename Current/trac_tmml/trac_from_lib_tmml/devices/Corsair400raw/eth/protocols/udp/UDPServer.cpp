#include "UDPServer.hpp"
#include "eth/EthGlobal.hpp"
#include "eth/protocols/udp/UDPSocket.hpp"
#include <cassert>
#include <chrono>

UDPServer::UDPServer(const uint32_t& rcvBufSize, const uint32_t& sndBufSize)
    : BaseThread(10)
    , _rcvBufSize{rcvBufSize}
    , _rcvBuf{new uint8_t[_rcvBufSize]}
    , _sndBufSize{sndBufSize}
    , _sndBuf{new uint8_t[_sndBufSize]}
    , _rcvLength{0}
    , _cntFrame{0}
    , _cntFrameLast{0}
    , _fps{0}
    , _timePoint{std::chrono::steady_clock::now()}
{
#ifdef DEBUG
    if(_rcvBufSize <= 4) {
        ERROR_MSG("UDPServer: _rcvBufSize < 4!");
    }
    if(_sndBufSize <= 4) {
        ERROR_MSG("UDPServer: _sndBufSize < 4!");
    }
    if(!_rcvBuf) {
        ERROR_MSG("UDPServer: _rcvBuf not created!");
    }
    if(!_sndBuf) {
        ERROR_MSG("UDPServer: _sndBuf not created!");
    }
#endif
}

UDPServer::~UDPServer()
{
    delete [] _rcvBuf;
    delete [] _sndBuf;
}

void UDPServer::open(const SocketAddress &srcAddress, const SocketAddress &dstAddress)
{
    _socket.close_();
    _srcAddress = srcAddress;
    _dstAddress = dstAddress;
    startThd();
}
void UDPServer::close()
{
    if(BaseThread::isRunningThd()) {
        BaseThread::stopThd();
    }
    _socket.close_();
    _fps = 0;
    _cntFrame = 0;
}

bool UDPServer::isConnected()
{
   return _socket.isOpen() && isRunningThd();
}

bool UDPServer::send(const uint8_t* data, const int32_t& length)
{
    return _socket.sndto(_dstAddress, data, length);
}

bool UDPServer::initThd()
{
    bool result = true;
    if(_socket.open_(_srcAddress)) {
        if(!_socket.setNonBlocking(true)) {
            ERROR_MSG("UDPServer: failed to set UDP socket non blocking");
        }
        if(!_socket.setBroadcast(true)) {
            ERROR_MSG("UDPServer: failed to set UDP socket broadcast");
        }
        if(!_socket.setRcvTimeout(1, 0)) { // only bloking mode
            ERROR_MSG("UDPServer: failed to set UDP socket rcv timeout");
        }
        if(!_socket.setSndTimeout(1, 0)) { // only bloking mode
            ERROR_MSG("UDPServer: failed to set UDP socket snd timeout");
        }
        if(!_socket.setRcvBufferSize(1920 * 1080 * 2)) {
            ERROR_MSG("UDPServer: failed to set UDP socket rcv buffer size");
        }
        if(!_socket.setReusable(true)) {
            ERROR_MSG("UDPServer: failed to set UDP socket port reusable");
        }
//        ERROR_MSG("UDPServer: UDP socket buffer: ");
//        bool res = false;/
//        ERROR_MSG(_socket.getRcvBufferSize(res));

    } else {
        result = false;
        ERROR_MSG("UDPServer: failed open UDP socket");
    }
    return result;
}

void UDPServer::runThd()
{
    _rcvLength = 0;
    SocketAddress packetSrcAddress;
    do {
        _rcvLength = _socket.rcvfrom(packetSrcAddress, _rcvBuf, _rcvBufSize);
        if(_rcvLength > 0) {
            handle(packetSrcAddress, _rcvBuf, _rcvLength);
        }
        std::chrono::steady_clock::time_point currentPoint = std::chrono::steady_clock::now();
        if(std::chrono::duration_cast<std::chrono::milliseconds>(currentPoint - _timePoint).count() >= 1000) {
            _fps = _cntFrame - _cntFrameLast;
            _cntFrameLast = _cntFrame;
            _timePoint = currentPoint;
        }
    } while (_rcvLength > 0);
}

void UDPServer::closeThd()
{
    _socket.close_();
}


