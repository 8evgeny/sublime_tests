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



ParsingFiles::ParsingFiles(std::string i) : pImpl{new Impl{i}} {}

ParsingFiles::ReadDir(){
    boost::filesystem::directory_iterator  p("/home/jhon");
    for (boost::filesystem::directory_entry& x : boost::filesystem::directory_iterator(p)){
        boost::filesystem::file_status fs = x.status();
        if(fs.type()==boost::filesystem::regular_file)
            std::cout << x.path() << '\n';
    }

}


