#include <string>
#include <future>
#include "FileExtractor.h"
#include "KeyListener.h"
#include "PixelSearchProject.h"
#include <iostream>

/*
* The key '*' will cycle through these data tables
* 
* Data Table 
* Title, Company, Description
*	T  C  D |
*	1, 2, 3 | 1st position data entry
*	4, 5, 6 | 2nd position data entry
*	7, 8, 9 | 3rd position data entry
* 
*/
int main(int argc, char* argv[]) {
    std::string fName{ "resources.txt" };

    FileExtractor fe{ fName };
    fe.init();

    std::vector<Data::Table> output = fe.getOutput();
    
    std::thread listenerThread([output = std::move(output)]() mutable {
        KeyListener kl{ output };
        kl.run();
    });
    listenerThread.detach();

    QApplication app(argc, argv);
    PixelSearchProject window;
    window.show();

    return app.exec();
}
