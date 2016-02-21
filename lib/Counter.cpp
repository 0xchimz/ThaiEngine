//
// Created by Chin on 2/18/2016.
//

#include "Counter.h"

using namespace Counter;

namespace Counter {
    long SIZE::getSize(std::vector<ThaiEngine::RECORD> link) {
        return link.size();
    }
}