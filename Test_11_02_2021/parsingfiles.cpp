#include "parsingfiles.h"

struct ParsingFiles::Impl {
    Impl();

    void ReadDir();
    void ReadFile();

//    camera::CameraPtr camera;

//    optics::OpticsMoverPtr optics_mover;
//    bool flip_frame_sw = false;
//    bool use_optics_mover = true;

//    unsigned long long feedbacks_counter = 0;  // How many feedbacks was received

//    std::shared_ptr<const domain::Settings> _settings = nullptr;
//    static const std::string NAME;
};

ParsingFiles::Impl::Impl(){}



ParsingFiles::ParsingFiles() : _d(std::make_unique<Impl>()) {}




