#include <iostream>
#include "controller/CovidDataController.hpp"

/** 
* Main
* 
* This function runs the CovidDataController on the provided filename file.
*
* @author Dan LeBlanc
* @studentno 040749264
*/
int main() {
    std::string filename = "covid19-download.csv";
    CovidDataController cdc;
    int status;
    try {
        cdc.load_csv(filename);
        status = cdc.run();
    } catch (const std::runtime_error e) {
        std::cout << e.what();
        status = 1;
    }

    return status;
}


