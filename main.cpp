/* 
 * File:   main.cpp
 * Author: williampoynter
 *
 * Created on September 20, 2013, 10:46 PM
 */

#include <cstdlib>
#include "Application.h"

using namespace std;

int main(int argc, char** argv) {
        
        Application app(argc, argv);
        
        app.run();
        
        return 0;
}

