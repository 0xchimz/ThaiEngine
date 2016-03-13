//
// Created by Chinnaporn Soonue on 3/13/2016 AD.
//

#ifndef THAIENGINE_SEARCH_H
#define THAIENGINE_SEARCH_H

#include <vector>
#include "Reader.h"
#include <fstream>
#include <cstring>
#include <map>
#include <chrono>

typedef std::chrono::time_point<std::chrono::high_resolution_clock> hires_clock;

#define NOW() std::chrono::high_resolution_clock::now()
#define DIFF(start) std::chrono::duration_cast<std::chrono::microseconds>(NOW() - start).count()

struct CompareCStrings
{
    bool operator()(const char* lhs, const char* rhs) const {
        return std::strcmp(lhs, rhs) < 0;
    }
};

namespace SearchEngine{
    class SEARCH{
    private:
        std::vector<ThaiEngine::RECORD> data;
        std::ifstream file_keyword;
        std::ofstream file_output;
        int num_found = 0;
        int num_not_found = 0;
        int num_total = 0;
        std::map<char*, int, CompareCStrings> cache;
    public:
        SEARCH(std::vector<ThaiEngine::RECORD> link, char* keyword, char* output);
        int search(char* keyword);
        void get_keyword();
    };
}

#endif //THAIENGINE_SEARCH_H
