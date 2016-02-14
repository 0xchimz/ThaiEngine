#include <iostream>
#include <fstream>
#include <string.h>

#define TEXT_SIZE 1023

using namespace std;

class RECORD {
public:
    struct header {
        uint32_t id;
        uint16_t lang :2;
        uint16_t length :10;
        bool tail_space :1;
        bool is_unused :1;
        bool numeric :1;
        bool filter:1;
        uint32_t map_file_pos;
    } header;
    int64_t timestamp;
    std::string text;
};

bool time_type(ifstream &is){
    is.seekg(8, is.cur);

    int *zero = new int;
    is.read((char*) &zero, sizeof(int));

    is.seekg(-12, is.cur);

    return (int)zero == 0;
}

int main(int argc, char* argv[]) {

    RECORD *record = new RECORD;
    char NUM1[] = "1";
    char NUM2[] = "2";
    char NUM3[] = "3";

    ifstream is;

    if (argc > 1) {
        if(strcmp(argv[1], NUM1)){
            is.open("D:\\Office\\Software Pattern\\ThaiEngine\\SyllableDB-V1.dat", ios::binary );
        } else if(strcmp(argv[1], NUM2)){
            is.open("D:\\Office\\Software Pattern\\ThaiEngine\\SyllableDB-V2.dat", ios::binary );
        } else if(strcmp(argv[1], NUM3)){
            is.open("D:\\Office\\Software Pattern\\ThaiEngine\\SyllableDB-V3.dat", ios::binary );
        } else {
            is.open(argv[1], ios::binary );
        }
    } else {
        is.open("D:\\Office\\Software Pattern\\ThaiEngine\\SyllableDB-V3.dat", ios::binary );
    }

    if (is.fail())
    {
        cout << "Input file opening failed";
        return 0;
    }

    is.seekg(256, is.beg);

    while(!is.eof()){
        is.read((char*) &record->header, sizeof(record->header));

        if(time_type(is)){
            is.read((char*) &record->timestamp, sizeof(int64_t));
            is.seekg(4, is.cur);
        } else {
            int32_t timestamp;
            is.read((char*) &timestamp, sizeof(timestamp));
            record->timestamp = (int64_t) timestamp;
        }

        char buffer[TEXT_SIZE];
        is.getline(&buffer[0], TEXT_SIZE, 0);

        record->text = std::string(buffer);
        cout << record->header.id << ". "  << record->text << endl;
    }

    is.close();

    return 0;
}
