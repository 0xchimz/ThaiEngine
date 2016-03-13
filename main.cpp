//
// Created by Chin on 2/18/2016.
//

#include "lib/Reader.h"
#include "lib/Counter.h"
#include "lib/Search.h"

using namespace std;
using namespace ThaiEngine;
using namespace Counter;
using namespace SearchEngine;

int main(int argc, char* argv[]){
//    char *file = "D:\\Office\\Software Pattern\\ThaiEngine\\SyllableDB-V1.dat";
    char *file;
    char *keyword;
    char *output;
    if (argc > 2) {
        file = argv[1];
        keyword = argv[2];
        output = argv[3];
    } else {
        cout << "Please enter full path of .dat file and keyword file" << endl;
        exit(0);
    }

    LOADER *loader = new LOADER(file);

    vector<RECORD> v;
    v = loader->read_file();

    SEARCH *search = new SEARCH(v, keyword, output);
    search->get_keyword();

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