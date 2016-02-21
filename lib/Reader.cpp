#include <stdexcept>
#include "Reader.h"

using namespace std;

namespace thaiengine {

    LOADER::LOADER(char *file) {
        link = file;
    }

    bool LOADER::time_type() {
        if(isType32 == -1) {
            is.seekg(8, is.cur);

            int *zero = new int;
            is.read((char *) &zero, sizeof(int));

            is.seekg(-12, is.cur);

            isType32 = (int) zero == 0;

            return (int) zero == 0;
        }
        return isType32;
    }

    char* LOADER::find_text() {
        char buffer[MAX_SYLLABLE_TEXTSIZE];
        is.getline(&buffer[0], MAX_SYLLABLE_TEXTSIZE, 0);
        return buffer;
    }

    vector<RECORD*> LOADER::read_file() {
        isType32 = -1;
        record = new vector<RECORD*>;
        try {
            is.open(link, ios::binary);
            cout << "Reading file..." << endl;
        }catch (std::exception e){
            throw std::invalid_argument("Input file opening failed");
        }

        is.seekg(0, is.end);
        int length = is.tellg();

        is.seekg(256, is.beg);

        while(is.tellg() <= length){
            cout << is.tellg() << " // " << length << " " << (is.tellg() <= length) << " ";
            RECORD* tmp = new RECORD;
            is.read((char*) &tmp->HEADER, sizeof(tmp->HEADER));

            if(time_type()){
                cout << "Type 1 ";
                is.read((char*) &tmp->timestamp, sizeof(int64_t));
                is.seekg(4, is.cur);
            } else {
                cout << "Type 2 ";
                int32_t timestamp;
                is.read((char*) &timestamp, sizeof(timestamp));
                tmp->timestamp = (int64_t) timestamp;
            }
            strcpy(tmp->text, LOADER::find_text());

            try {
                cout << tmp->HEADER.id << ". " << tmp->text << endl;
                record->push_back(tmp);
                numOfRecord++;
            }catch (const std::exception e){
                throw std::invalid_argument("Error while push Element!");
            }
        }

        is.close();

        return *record;
    }

    int LOADER::recordCounting() {
        return numOfRecord;
    }

    void LOADER::printAllRecord() {
        for (RECORD *item: *record) {
            cout << item->HEADER.id << ". " << item->text << endl;
        }
    }
}