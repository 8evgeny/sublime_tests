#ifndef ASYNC_TCP_CLIENT_SIMPLEX_CMD_FACTORY_HPP
#define ASYNC_TCP_CLIENT_SIMPLEX_CMD_FACTORY_HPP

#include "async_tcp_client_simplex_cmd.hpp"
#include "tools/ExtendINIReader.hpp"

namespace eth_controller::cmd::async::client_simplex
{

std::shared_ptr<AsyncTcpClientSimplexCmd> create(
        const std::string &path2ini,
        const std::string &section);

//bool readIniSettings(const std::string &path2ini, const std::string section, Settings &settings_dst);

}; // END namespace eth_controller::cmd::async::client_simplex
#endif // END ASYNC_TCP_CLIENT_SIMPLEX_CMD_FACTORY_HPP
