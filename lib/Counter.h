//
// Created by PUNPIKORN RATTANAWIROJKUL on 2/21/2016 AD.
//

#ifndef THAIENGINE_COUNTER_H
#define THAIENGINE_COUNTER_H

#include "Reader.h"
#include <vector>

namespace Counter {
    class SIZE {
    public:
        long getSize(std::vector<ThaiEngine::RECORD> link);
    };
}


#endif //THAIENGINE_COUNTER_H
