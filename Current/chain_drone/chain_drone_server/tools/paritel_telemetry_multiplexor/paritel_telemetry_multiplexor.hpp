#ifndef PARITEL_TELEMETRY_MULTIPLEXOR
#define PARITEL_TELEMETRY_MULTIPLEXOR

#include "tools/esrt_toolbox/esrt_api.hpp"
#include "tools/teletxt_toolbox/teletxt_api.hpp"

#include "paritel_telemetry_ap.hpp"
#include "paritel_telemetry_general.hpp"

namespace telemetry_mux
{   
    /*
    Преобразование телеметрии из файлов ESRT в универсальный формат
    */
    // ESRTdata --> ParitelTelemetryGen
    void conv_ESRT_to_TeleGen(
        const ESRTdata &esrt_src,
        ParitelTelemetryGen &teleGen_dst);


    void conv_Teletxt_to_TeleGen(
        const Teletxt &teleTxt_src,
        int _frameNumber,
        ParitelTelemetryGen &teleGen_dst);
    /*
    Преобразование телеметрии из формата от автопилота (АП) парителя в универсальный формат 
    */
    // ParitelTelemetryAP --> ParitelTelemetryGen
    void conv_TeleAP_to_TeleGen(
        const ParitelTelemetryAP &teleAP_src,
        int _frameNumber,
        ulong frame_time,
        ParitelTelemetryGen &teleGen_dst);
    
    void conv_Teletxt_to_TeleGen(
            const Teletxt &teleTxt_src,
            int _frameNumber,
            ParitelTelemetryGen &teleGen_dst);

    void conv_TeleGen_to_Teletxt(
            const ParitelTelemetryGen &teleGen_src,
            Teletxt &teleTxt_dst);


} // -- telemetry_mux

#endif //PARITEL_TELEMETRY_MULTIPLEXOR
