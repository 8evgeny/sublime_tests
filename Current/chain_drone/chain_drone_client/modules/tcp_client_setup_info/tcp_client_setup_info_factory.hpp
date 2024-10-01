#ifndef TCP_CLIENT_SETUP_INFO_FACTORY_FACTORY_HPP
#define TCP_CLIENT_SETUP_INFO_FACTORY_FACTORY_HPP

#include "tcp_client_setup_info.hpp"
#include "tools/ExtendINIReader.hpp"

namespace eth_controller::cmd::async::client_simplex
{

std::shared_ptr<TcpClientSetupInfo> create(
        const std::string &path2ini,
        const std::string &section);

//bool readIniSettings(const std::string &path2ini, const std::string section, Settings &settings_dst);

}; // END namespace eth_controller::cmd::async::client_simplex
#endif // END TCP_CLIENT_SETUP_INFO_FACTORY_FACTORY_HPP
