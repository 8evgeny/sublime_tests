#include "eth_cmd_factory.hpp"

#ifdef USE_ETH_CMD_UNCOMPRESS_FRAME_DEFAULT
#include "uncompress_frame/uncomp_frame_eth_cmd.hpp"
#endif /* USE_ETH_CMD_UNCOMPRESS_FRAME_DEFAULT */

#ifdef USE_ETH_CMD_COPTER_ALARM
#include "copter_alarm/copter_alarm_eth_cmd.hpp"
#endif /* USE_ETH_CMD_COPTER_ALARM*/

#ifdef USE_ETH_CMD_TELEMETRY_ATAS
#include "telemetry_atas/telemetry_atas_eth_cmd.hpp"
#endif /* USE_ETH_CMD_TELEMETRY_ATAS */

#ifdef USE_ETH_CMD_POWEROFF_REQUEST
#include "poweroff_request/poweroff_request_eth_cmd.hpp"
#endif /* USE_ETH_CMD_POWEROFF_REQUEST */

#ifdef USE_ETH_CMD_CONFIRM_CMD_RECEIVE
#include "confirmation_cmd_receive/confirmation_cmd_receive.hpp"
#endif /* USE_ETH_CMD_CONFIRM_CMD_RECEIVE */

#ifdef USE_ETH_CMD_AP_TELEMETRY
#include "ap_telemetry/ap_telemetry_eth_cmd.hpp"
#endif /* USE_ETH_CMD_AP_TELEMETRY */

#ifdef USE_ETH_CMD_AP_CHAIN_DRONE_TELEMETRY
#include "chain_drone_ap_telemetry/chain_drone_ap_telemetry_eth_cmd.hpp"
#endif /* USE_ETH_CMD_AP_CHAIN_DRONE_TELEMETRY */


#ifdef USE_ETH_CMD_TRACKER_METADATA
#include "track_meta/track_meta_eth_cmd.hpp"
#endif /* USE_ETH_CMD_TRACKER_METADATA */

#ifdef USE_ETH_CMD_TRACKER_METADATA_POS
#include "track_meta_pos/track_meta_pos_eth_cmd.hpp"
#endif

#ifdef USE_ETH_CMD_TELEMETRY_ORIENTATION
#include "telemetry_orientation/telemetry_orientation_eth_cmd.hpp"
#endif /* USE_ETH_CMD_TELEMETRY_ORIENTATION */

#ifdef USE_ETH_CMD_AP_POS_CNT
#include "ap_pos_cnt/ap_pos_cnt_eth_cmd.hpp"
#endif /* USE_ETH_CMD_AP_POS_CNT */

#ifdef USE_ETH_CMD_FENIX2META
#include "fenix2meta/fenix2meta_eth_cmd.hpp"
#endif /*USE_ETH_CMD_FENIX2META*/

#ifdef USE_ETH_CMD_FENIX2CMD
#include "fenix2cmd/fenix2cmd_eth_cmd.hpp"
#endif /*USE_ETH_CMD_FENIX2CMD*/

#include <cassert>
#include <iostream>

namespace eth_cmd_processing
{
EthCmdFactory::EthCmdFactory()
{
#ifdef USE_ETH_CMD_UNCOMPRESS_FRAME_DEFAULT
    std::function< std::shared_ptr<EthCmdBase> () > uncompress_frame_callback = []()
    {
        return std::make_shared<EthCmdUncompFrame>();
    }; // uncompress_frame_callback
    factory_callbacks_map[ETH_CMD_UNCOMPRESS_FRAME_DEFAULT] = uncompress_frame_callback;
#endif /* USE_ETH_CMD_UNCOMPRESS_FRAME_DEFAULT */

#ifdef USE_ETH_CMD_COPTER_ALARM
    std::function< std::shared_ptr<EthCmdBase> () > copter_alarm_callback = []()
    {
        return std::make_shared<EthCmdCopterAlarm>();
    }; // copter_alarm_callback
    factory_callbacks_map[ETH_CMD_COPTER_ALARM] = copter_alarm_callback;
#endif /* USE_ETH_CMD_COPTER_ALARM*/

#ifdef USE_ETH_CMD_TELEMETRY_ATAS
    std::function< std::shared_ptr<EthCmdBase> () > telemetry_atas_callback = []()
    {
        return std::make_shared<EthCmdTelemetryAtas>();
    }; // poweroff request callback
    factory_callbacks_map[ETH_CMD_TELEMETRY_ATAS] = telemetry_atas_callback;
#endif /* USE_ETH_CMD_TELEMETRY_ATAS */

#ifdef USE_ETH_CMD_POWEROFF_REQUEST
    std::function< std::shared_ptr<EthCmdBase> () > poweroff_request_callback = []()
    {
        return std::make_shared<EthCmdRequestPoweroff>();
    }; // poweroff request callback
    factory_callbacks_map[ETH_CMD_POWEROFF_REQUEST] = poweroff_request_callback;
#endif /* USE_ETH_CMD_POWEROFF_REQUEST */

#ifdef USE_ETH_CMD_CONFIRM_CMD_RECEIVE
    std::function< std::shared_ptr<EthCmdConfirmCmdReceive> () > confirm_cmd_receive_callback = []()
    {
        return std::make_shared<EthCmdConfirmCmdReceive>();
    }; // confirm cmd receive callback
    factory_callbacks_map[ETH_CMD_CONFIRM_CMD_RECEIVE] = confirm_cmd_receive_callback;
#endif /* USE_ETH_CMD_CONFIRM_CMD_RECEIVE */

#ifdef USE_ETH_CMD_AP_TELEMETRY
    std::function< std::shared_ptr<EthCmdAPTelemetry> () > ap_telemetry_callback = []()
    {
        return std::make_shared<EthCmdAPTelemetry>();
    }; // ap telemetry callback
    factory_callbacks_map[ETH_CMD_AP_TELEMETRY] = ap_telemetry_callback;
#endif /* USE_ETH_CMD_AP_TELEMETRY */

#ifdef USE_ETH_CMD_AP_CHAIN_DRONE_TELEMETRY
    std::function< std::shared_ptr<EthCmdChainDroneAPTelemetry> () > chain_done_ap_telemetry_callback = []()
    {
        return std::make_shared<EthCmdChainDroneAPTelemetry>();
    }; // ap telemetry callback
    factory_callbacks_map[ETH_CMD_CHAIN_DRONE_AP_TELEMETRY] = ap_telemetry_callback;
#endif // USE_ETH_CMD_AP_CHAIN_DRONE_TELEMETRY

#ifdef USE_ETH_CMD_TRACKER_METADATA
    std::function< std::shared_ptr<EthCmdTrackerMetaData> () > tracker_metadata_callback = []()
    {
        return std::make_shared<EthCmdTrackerMetaData>();
    }; // tracker metadata callback
    factory_callbacks_map[ETH_CMD_TRACKER_METADATA] = tracker_metadata_callback;
#endif /* USE_ETH_CMD_TRACKER_METADATA */

#ifdef USE_ETH_CMD_TRACKER_METADATA_POS
    std::function< std::shared_ptr<EthCmdTrackerMetaDataPos> () > tracker_metadata_pos_callback = []()
    {
        return std::make_shared<EthCmdTrackerMetaDataPos>();
    }; // tracker metadata callback
    factory_callbacks_map[ETH_CMD_TRACKER_METADATA_POS] = tracker_metadata_pos_callback;
#endif /* USE_ETH_CMD_TRACKER_METADATA_POS */


#ifdef USE_ETH_CMD_TELEMETRY_ORIENTATION
    std::function< std::shared_ptr<EthCmdOrientTelemetry> () > orient_telemetry_callback = []()
    {
        return std::make_shared<EthCmdOrientTelemetry>();
    };
    factory_callbacks_map[ETH_CMD_ORIENTATION_TELEMETRY] = orient_telemetry_callback;
#endif /* USE_ETH_CMD_TELEMETRY_ORIENTATION */

#ifdef USE_ETH_CMD_AP_POS_CNT
    std::function< std::shared_ptr<EthCmdApPosCnt> () > ap_pos_cnt_callback = []()
    {
        return std::make_shared<EthCmdApPosCnt>();
    };
    factory_callbacks_map[ETH_CMD_AP_POS_CNT] = ap_pos_cnt_callback;
#endif /* USE_ETH_CMD_AP_POS_CNT */

#ifdef USE_ETH_CMD_FENIX2META
    std::function< std::shared_ptr<EthCmdFenix2MetaData>() > fenix2_metadata_callback = []()
    {
        return std::make_shared<EthCmdFenix2MetaData>();
    }; // fenix2 metadata callback
    factory_callbacks_map[ETH_CMD_FENIX2_METADATA] = fenix2_metadata_callback;
#endif /*USE_ETH_CMD_FENIX2META*/

#ifdef USE_ETH_CMD_FENIX2CMD
    std::function< std::shared_ptr<EthCmdFenix2CmdData>() > fenix2_cmd_data_callback = []()
    {
        return std::make_shared<EthCmdFenix2CmdData>();
    }; // fenix2 cmddata callback
    factory_callbacks_map[ETH_CMD_FENIX2_CMD_DATA] = fenix2_cmd_data_callback;
#endif /*USE_ETH_CMD_FENIX2CMD*/

} // -- END EthCmdFactory

std::shared_ptr<EthCmdBase> EthCmdFactory::create(EthCommands cmd_type) const
{
    assert(cmd_type != ETH_CMD_NO_COMMAND);
    // assert(factory_callbacks_map.find(cmd_type) != factory_callbacks_map.end());
    if(factory_callbacks_map.find(cmd_type) == factory_callbacks_map.end())
    {
        std::cout << "Error factory_callbacks_map.find(cmd_type) != factory_callbacks_map.end(); cmd_type=" + std::to_string(cmd_type);
        return nullptr;
    }

    return factory_callbacks_map.at(cmd_type)(); // can be throw except std::out_of_range if cmd_type not in keys factory_callbacks_map
} // -- END create
} // eth_cmd_processing
