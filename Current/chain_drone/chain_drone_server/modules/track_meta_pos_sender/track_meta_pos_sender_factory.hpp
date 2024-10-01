#ifndef TRACK_META_POS_SENDER_FACTORY_HPP
#define TRACK_META_POS_SENDER_FACTORY_HPP

#include "track_meta_pos_sender.hpp"
#include <memory>

namespace track_meta_sender
{
    std::shared_ptr<TrackMetaPosSender> create(const std::string &path2ini, const std::string &section);
} // -- namespace track_meta_sender

#endif //TRACK_META_Pos SENDER_FACTORY_HPP
