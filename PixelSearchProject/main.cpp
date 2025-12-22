#include <string>
#include <future>
#include "FileExtractor.h"
#include "PixelSearchProject.h"
#include <QtWidgets/QApplication>


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

int main(int argc, char *argv[]) {
    std::future<void> future = std::async(std::launch::async,
        []() {
            // init vars
            std::string fName{ "resources.txt" };
            FileExtractor fe{ fName };
            fe.init();

            // start keylistener
        }
    );


    QApplication app(argc, argv);
    PixelSearchProject window;
    window.show();
    return app.exec();
}
