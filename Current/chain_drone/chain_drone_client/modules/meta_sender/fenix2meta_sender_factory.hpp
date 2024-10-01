#ifndef FENIX2META_SENDER_FACTORY_HPP
#define FENIX2META_SENDER_FACTORY_HPP

#include "fenix2meta_sender.hpp"
#include <memory>

namespace fenix2meta_sender
{
    std::shared_ptr<Fenix2MetaSender> create(const std::string &path2ini, const std::string &section);
} // -- namespace fenix2meta_sender

#endif //FENIX2META_SENDER_FACTORY_HPP
