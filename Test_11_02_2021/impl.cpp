//#include "parsingfiles.h"
//struct ParsingFiles::Impl {
//    Impl();

//    void ReadDirImpl() ;
//    void ReadFileImpl();

//};
//ParsingFiles::Impl::Impl(){}
//void ParsingFiles::Impl::ReadDirImpl(){
//    boost::filesystem::directory_iterator  p("/home/jhon");
//    for (boost::filesystem::directory_entry& x : boost::filesystem::directory_iterator(p)){
//        boost::filesystem::file_status fs = x.status();
//        if(fs.type()==boost::filesystem::regular_file)
//            std::cout << x.path() << '\n';
//    }

//}
