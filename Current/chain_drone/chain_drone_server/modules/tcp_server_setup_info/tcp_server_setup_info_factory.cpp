#include "tcp_server_setup_info_factory.hpp"

namespace eth_controller::cmd::async::server_simplex
{

bool readIniSettings(const std::string &path2ini,
                     const std::string section,
                     Settings &settings_dst)
{
    std::cout << "BEGIN " << section << "::readIniSettings\n";
    INIReader reader(path2ini);
    if(reader.ParseError() < 0)
    {
        std::cout << "ini reader parse error!\n";
        return false;
    } // END     if(reader.ParseError() < 0)

    bool ini_report = true;
    ini_report &= ext_ini::Get(path2ini, section, "node_alias", settings_dst.node_alias);
    ini_report &= ext_ini::Get(path2ini, section, "dst_ip_v4", settings_dst.dst_ip_v4);
    ini_report &= ext_ini::GetInteger(path2ini, section, "dst_port", settings_dst.dst_port);
    int single_command_buf_size_byte_buf;
    ini_report &= ext_ini::GetInteger(path2ini, section, "single_command_buf_size_byte", single_command_buf_size_byte_buf);
    settings_dst.single_command_buf_size_byte = single_command_buf_size_byte_buf;

    std::cout << "END " << section << "::readIniSettings" << std::endl;
    return ini_report;
} // END readIniSettings


std::shared_ptr<TcpServerSetupInfo> create(const std::string &path2ini, const std::string &section)
{
    std::cout << "START create eth_controller::cmd::async::server_simplex::TcpServerSetupInfo" << std::endl;
    Settings settings;
    if (!readIniSettings(path2ini, section, settings))
    {
        std::cout << "TcpServerSetupInfo factory:: Not ok readIniSettings(" << path2ini << ", " << section << ", settings)!" << std::endl;
    } // END if (!readIniSettings(path2ini, section, settings))
    std::cout << "END create eth_controller::cmd::async::server_simplex::TcpServerSetupInfo" << std::endl;
    return std::make_shared<TcpServerSetupInfo>(settings);
} // END create

}; // END eth_controller::cmd::async::server_simplex
