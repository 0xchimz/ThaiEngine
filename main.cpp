//
// Created by Chin on 2/18/2016.
//

#include "lib/Reader.h";
#include "lib/Counter.h";

using namespace std;
using namespace ThaiEngine;
using namespace Counter;

int main(int argc, char* argv[]){
//    char *file = "D:\\Office\\Software Pattern\\ThaiEngine\\SyllableDB-V1.dat";
    char *file = new char;
    if (argc > 1) {
        strcpy(file, argv[1]);
    } else {
        cout << "Please enter full path of .dat file" << endl;
        exit(0);
    }
    LOADER *loader = new LOADER(file);

    vector<RECORD> v;
    v = loader->read_file();

    Counter::SIZE count;
    long size = count.getSize(v);
    cout << "Number of all element: " << size << endl;

    cout << "Print result" << endl;
    cout << "==================" << endl;
    for (int i = 0 ; i < size ; i++) {
        ThaiEngine::RECORD e = v.at(i);
        cout << e.HEADER.id << ". " << e.text << endl;
    }

    return 0;
}