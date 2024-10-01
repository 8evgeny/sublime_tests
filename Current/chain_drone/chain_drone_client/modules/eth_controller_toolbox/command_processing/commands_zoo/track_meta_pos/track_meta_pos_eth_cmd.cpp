#include "track_meta_pos_eth_cmd.hpp"

#include "../../eth_cmd_common_types.hpp"

#include <cstring>
#include <cstdint>
#include <cassert>

namespace eth_cmd_processing
{

EthCmdTrackerMetaDataPos::EthCmdTrackerMetaDataPos()
{
    serialize_size_bytes = sizeof(TrackMeta2AP_pos);
    cmd_id = ETH_CMD_TRACKER_METADATA_POS;
}

int EthCmdTrackerMetaDataPos::get_serialize_size() const
{
    return serialize_size_bytes;
}

bool EthCmdTrackerMetaDataPos::serialize_noalloc(uint8_t *cmd_buffer, int &buffer_size_bytes) const
{
    memcpy(cmd_buffer, reinterpret_cast<uint8_t const *>(&trackmeta_pos), serialize_size_bytes);

    #ifdef SYSTEM_BIG_ENDIAN
    ReverseBytes(byte_arr_ptr, serialize_size_bytes);
    #endif //SYSTEM_BIG_ENDIAN

    cmd_buffer += serialize_size_bytes;
    buffer_size_bytes = serialize_size_bytes;
    return true;
}

bool EthCmdTrackerMetaDataPos::deserialize(uint8_t const *cmd_buffer)
{
    trackmeta_pos = *(reinterpret_cast<TrackMeta2AP_pos const *>(cmd_buffer));
    cmd_buffer += serialize_size_bytes;
    return true;
}

void EthCmdTrackerMetaDataPos::set(const TrackMeta2AP_pos &_trackmeta_pos)
{
    trackmeta_pos = _trackmeta_pos;
}

void EthCmdTrackerMetaDataPos::get(TrackMeta2AP_pos &_trackmeta_pos)
{
    _trackmeta_pos = trackmeta_pos;
}

} // -- namespace eth_cmd_processing
