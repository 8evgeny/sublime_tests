#ifndef GSTC_RTSP_SERVER_FACTORY_HPP
#define GSTC_RTSP_SERVER_FACTORY_HPP

#include <memory>
#include "gstc_rtsp_server.hpp"


using namespace std;

std::shared_ptr<rtsp::server::RTSPServer> create(rtsp::server::SettingsRtspSrv settings_)
{
    std::shared_ptr<rtsp::server::RTSPServer> srv = std::make_shared<rtsp::server::RTSPServer>(settings_);
    return srv;
} // -- END create

bool readSettingsRtspSrv(const std::string & pathToSettings,
                  const std::string & ini_section_name,
                  bool &success)
{
    cout << "ReadSettings" << endl;
    return success;
} // -- END readSettings



#endif //!GSTC_RTSP_SERVER_FACTORY_HPP
