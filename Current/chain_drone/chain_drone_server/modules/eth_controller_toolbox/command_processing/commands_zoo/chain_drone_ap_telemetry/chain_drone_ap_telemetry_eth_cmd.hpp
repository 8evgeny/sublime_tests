#ifndef CHAIN_DRONE_AP_TELEMETRY_ETH_CMD_HPP
#define CHAIN_DRONE_AP_TELEMETRY_ETH_CMD_HPP

#include "../eth_cmd_base.hpp"
#include AP_TEMETRY_INTERFACE_PATH

namespace eth_cmd_processing
{

class EthCmdAPChainDroneTelemetry : public EthCmdBase
{

public:
    EthCmdAPChainDroneTelemetry();
    virtual int get_serialize_size() const override;
    virtual bool serialize_noalloc(uint8_t* cmd_buffer, int &buffer_size_bytes) const override;
    virtual bool deserialize(uint8_t const * cmd_buffer) override;
    void set(const ChainDroneTelemetryAP &_tele);
    void get(ChainDroneTelemetryAP &_tele);
private:
    int serialize_size_bytes = -1;
    ChainDroneTelemetryAP tele_data;
}; // -- class EthCmdAPChainDroneTelemetry

} // -- namespace eth_cmd_processing

#endif // AP_TELEMETRY_ETH_CMD_HPP
