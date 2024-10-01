#include "chain_drone_ap_telemetry_eth_cmd.hpp"

#include "../../eth_cmd_common_types.hpp"
#include <cstring>
#include <cstdint>
#include <cassert>
#include "../../eth_serialization_tools.hpp"


namespace eth_cmd_processing
{

EthCmdAPChainDroneTelemetry::EthCmdAPChainDroneTelemetry()
{
    serialize_size_bytes = sizeof(ChainDroneTelemetryAP);
    cmd_id = ETH_CMD_CHAIN_DRONE_AP_TELEMETRY;
} // -- constructor EthCmdAPChainDroneTelemetry

int EthCmdAPChainDroneTelemetry::get_serialize_size() const
{
    return serialize_size_bytes;
}

bool EthCmdAPChainDroneTelemetry::serialize_noalloc(uint8_t *cmd_buffer, int &buffer_size_bytes) const
{
    memcpy(cmd_buffer, reinterpret_cast<uint8_t const *>(&tele_data), serialize_size_bytes);

    #ifdef SYSTEM_BIG_ENDIAN
    ReverseBytes(byte_arr_ptr, serialize_size_bytes);
    #endif //SYSTEM_BIG_ENDIAN


    cmd_buffer += serialize_size_bytes;
    buffer_size_bytes = serialize_size_bytes;
    return true;
}

bool EthCmdAPChainDroneTelemetry::deserialize(uint8_t const *cmd_buffer)
{
    tele_data = *(reinterpret_cast<ChainDroneTelemetryAP const *>(cmd_buffer));
    cmd_buffer += serialize_size_bytes;
    return true;
}

void EthCmdAPChainDroneTelemetry::set(const ChainDroneTelemetryAP &_tele_src)
{
    tele_data = _tele_src;
}

void EthCmdAPChainDroneTelemetry::get(ChainDroneTelemetryAP &_tele_dst)
{
    _tele_dst = tele_data;
}

} // -- namespace eth_cmd_processing
