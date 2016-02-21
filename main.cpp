//
// Created by Chin on 2/18/2016.
//
#include "lib/Reader.h";

using namespace std;
using namespace thaiengine;

int main(int argc, char* argv[]){
    char *file = "D:\\Office\\Software Pattern\\ThaiEngine\\SyllableDB-V1.dat";
    LOADER *loader = new LOADER(file);
    loader->read_file();

    cout << "Number of all element: " << loader->recordCounting() << endl;

    cout << "Print result" << endl;
    cout << "==================" << endl;
//    loader->printAllRecord();

    return 0;
}
