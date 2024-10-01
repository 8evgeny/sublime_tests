#ifndef FENIX2META_KEEPER_FACTORY_HPP
#define FENIX2META_KEEPER_FACTORY_HPP

#include <memory>
#include <string>

#include "fenix2meta_keeper.hpp"

namespace fenix2meta_keeper
{
std::shared_ptr<Fenix2MetaKeeper> create(
        const std::string &path2ini,
        const std::string &section);
} // -- namespace ap_tele_keeper

#endif //FENIX2META_KEEPER_FACTORY_HPP
