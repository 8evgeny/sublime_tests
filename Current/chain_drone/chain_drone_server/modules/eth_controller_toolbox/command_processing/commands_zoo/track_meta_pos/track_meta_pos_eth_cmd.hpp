#ifndef TRACK_META_POS_ETH_CMD_HPP
#define TRACK_META_POS_ETH_CMD_HPP

#include "../eth_cmd_base.hpp"
#include TRACKER_METADATA_POS_INTERFACE_PATH

namespace eth_cmd_processing
{

class EthCmdTrackerMetaDataPos : public EthCmdBase
{
public:
    EthCmdTrackerMetaDataPos();
    virtual int get_serialize_size() const override;
    virtual bool serialize_noalloc(uint8_t* cmd_buffer, int &buffer_size_bytes) const override;
    virtual bool deserialize(uint8_t const * cmd_buffer) override;
    void set(const TrackMeta2AP_pos &_trackmeta_pos);
    void get(TrackMeta2AP_pos &_trackmeta_pos);
private:
    int serialize_size_bytes = -1;
    TrackMeta2AP_pos trackmeta_pos;
}; // -- class EthCmdTrackerMetaData

} // -- namespace eth_cmd_processing

#endif //TRACK_META_POS_ETH_CMD_HPP
