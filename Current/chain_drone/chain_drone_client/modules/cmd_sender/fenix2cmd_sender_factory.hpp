#ifndef FENIX2CMD_SENDER_FACTORY_HPP
#define FENIX2CMD_SENDER_FACTORY_HPP

#include "fenix2cmd_sender.hpp"
#include <memory>

namespace fenix2cmd_sender
{
    std::shared_ptr<Fenix2CmdSender> create(const std::string &path2ini, const std::string &section);
} // -- namespace fenix2cmd_sender

#endif //FENIX2CMD_SENDER_FACTORY_HPP
