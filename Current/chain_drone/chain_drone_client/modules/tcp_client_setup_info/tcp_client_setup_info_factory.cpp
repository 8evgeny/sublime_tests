#include "tcp_client_setup_info_factory.hpp"


namespace eth_controller::cmd::async::client_simplex
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
    ini_report &= ext_ini::Get(path2ini, section, "src_ip_v4", settings_dst.src_ip_v4);
    ini_report &= ext_ini::GetInteger(path2ini, section, "src_port", settings_dst.src_port);
    ini_report &= ext_ini::GetInteger(path2ini, section, "single_command_buf_size_byte", settings_dst.single_command_buf_size_byte);
    ini_report &= ext_ini::GetInteger(path2ini, section, "cmd_tx_loop_delay_ms", settings_dst.cmd_tx_loop_delay_ms);

    std::cout << "END " << section << "::readIniSettings" << std::endl;
    return ini_report;
} // END readIniSettings


std::shared_ptr<TcpClientSetupInfo> create(const std::string &path2ini, const std::string &section)
{
    std::cout << "START create eth_controller::cmd::async::client_simplex::TcpClientSetupInfo" << std::endl;
    Settings settings;
    if (!readIniSettings(path2ini, section, settings))
    {
        std::cout << "TcpClientSetupInfo factory:: Not ok readIniSettings(" << path2ini << ", " << section << ", settings)!" << std::endl;
    } // END if (!readIniSettings(path2ini, section, settings))
    std::cout << "END create eth_controller::cmd::async::client_simplex::TcpClientSetupInfo" << std::endl;
    return std::make_shared<TcpClientSetupInfo>(settings);
} // END create

}; // END eth_controller::cmd::async::client_simplex
