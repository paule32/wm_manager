#include "win0001.h"

int main(int argc, char **argv)
{
    kallup::TWindowTUI::root_app = new
    kallup::TWindowTUI::TWindowApplication(argc,argv);
               
    auto tu  = kallup::Create_TWindowManager(kallup::Implementations::Text,
               kallup::TWindowTUI::root_app);
    tu->exec();

//    auto sf = kallup::Create_TWindowManager(kallup::Implementations::Simple);
//    sf->exec();

//    auto ff = kallup::Create_TWindowManager(kallup::Implementations::Windows95);
//    ff->exec();
    
    return 0;
}

