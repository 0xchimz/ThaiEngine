#include <stdexcept>
#include "Reader.h"
#include <iconv.h>

using namespace std;

namespace ThaiEngine {

    LOADER::LOADER(char *file) {
        link = file;
    }

    bool LOADER::time_type() {
        if(isType32 == -1) {
            is.seekg(8, is.cur);
            isType32 = (is.get() == '\0' && is.get() == '\0' && is.get() == '\0' && is.get() == '\0');
            is.seekg(-12, is.cur);
        }
        return isType32;
    }

    vector<RECORD> LOADER::read_file() {
        iconv_t charset = iconv_open("UTF8", "CP874");
        int curId = 0;
        isType32 = -1;
        try {
            is.open(link, ios::binary);
            cout << "Reading file..." << endl;
        }catch (std::exception e){
            throw std::invalid_argument("Input file opening failed");
        }

        is.seekg(256, is.beg);

        while(!is.eof()){
            RECORD tmp;
            is.read((char*) &tmp.HEADER, sizeof(tmp.HEADER));

            if(curId + 1 != tmp.HEADER.id)  break;

            curId = tmp.HEADER.id;

            if(time_type()){
                is.read((char*) &tmp.timestamp, sizeof(time_t));
                is.seekg(4, is.cur);
            } else {
                time_t timestamp;
                is.read((char*) &timestamp, sizeof(time_t));
                tmp.timestamp = (int64_t) timestamp;
            }
            char tmp_text[MAX_SYLLABLE_TEXTSIZE];
            is.getline(&tmp_text[0], MAX_SYLLABLE_TEXTSIZE, '\0');

            size_t inSize = MAX_SYLLABLE_TEXTSIZE;
            size_t outSize = MAX_SYLLABLE_TEXTSIZE;
            char *input = &tmp_text[0];
            char *output = &tmp.text[0];
            iconv(charset, &input, &inSize, &output, &outSize);

            try {
                record.push_back(tmp);
            }catch (const std::exception e){
                throw std::invalid_argument("Error while push Element!");
            }
        }

        is.close();

        return record;
    }
}