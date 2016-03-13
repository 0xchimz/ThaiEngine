//
// Created by Chinnaporn Soonue on 3/13/2016 AD.
//

#include "Search.h"

using namespace std;
using namespace ThaiEngine;

namespace SearchEngine {

    SEARCH::SEARCH(vector<RECORD> link, char *keyword, char *output) {
        data = link;
        try {
            file_keyword.open(keyword, ios::in);
            cout << "Reading keyword file..." << endl;
            file_output.open(output, ios::out);
            cout << "Prepare file to write resutl..." << endl;
        }catch (std::exception e){
            throw std::invalid_argument("Input file opening failed");
        }
    }

    void SEARCH::get_keyword() {

        char tmp1[3], tmp2[25], tmp3[5], keyword[MAX_SYLLABLE_TEXTSIZE];
        file_output << "Search Result...\n";
        file_output << "===============================\n";
        cout << "Start searching..." << endl;
        start = clock();
        while(file_keyword >> tmp1 >> tmp2 >> tmp3 >> keyword){
            int res = search(keyword);

            if(res != -1){
                file_output << keyword << " | Found at ID: " << res << "\n";
                num_found = num_found + 1;
            } else {
                file_output << keyword << " | Not found in database...\n";
                num_not_found = num_not_found + 1;
            }
            num_total = num_total + 1;
        }
        stop = clock();
        file_output << "===============================\n";
        file_output << "Result: \n";
        file_output << "Found: " << num_found << " keyword(s)\n";
        file_output << "Not Found: " << num_not_found << " keyword(s)\n";
        time_duration = (stop-start)/(double)CLOCKS_PER_SEC;
        file_output << "Total Time: " << time_duration << " sec\n";
        file_output.close();
    }

    int SEARCH::search(char *keyword) {
        map<char*, int, CompareCStrings>::iterator pos = cache.find(keyword);
        if (pos != cache.end()) {
            return pos->second;
        }
        for(int i=0; i<data.size(); i++){
            ThaiEngine::RECORD tmp = data.at(i);

            string tmp_str(tmp.text);
            string key(keyword);
            size_t found = tmp_str.find(key);

            if(found != string::npos){
                cache[tmp.text] = tmp.HEADER.id;
                return tmp.HEADER.id;
            }
        }
        return -1;
    }
}