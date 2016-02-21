//
// Created by Chin on 2/18/2016.
//

#ifndef THAIENGINE_MAIN_H
#define THAIENGINE_MAIN_H

#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>

#define MAX_SYLLABLE_TEXTSIZE 1024

namespace thaiengine{
    class RECORD {
    public:
        struct HEADER {
            uint32_t id;
            uint16_t lang :2;
            uint16_t length :10;
            uint16_t tail_space :1;
            uint16_t is_unused :1;
            uint16_t numeric :1;
            uint16_t filter:1;
            uint32_t map_file_pos;
        }HEADER;
        int64_t timestamp;
        char text[MAX_SYLLABLE_TEXTSIZE];
    };
    class LOADER {
    public:
        LOADER(char* link);
        std::vector<RECORD*> read_file();
        int recordCounting();
        void printAllRecord();
    private:
        char* link;
        int isType32;
        std::vector<RECORD*> *record;
        std::ifstream is;
        int numOfRecord;
        bool time_type();
        char* find_text();
    };
}

#endif //THAIENGINE_MAIN_H
