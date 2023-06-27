//
// Created by yeasi on 6/25/2023.
//

#ifndef OSPROJECT_HANDLERPRIORITY_H
#define OSPROJECT_HANDLERPRIORITY_H

#endif //OSPROJECT_HANDLERPRIORITY_H
#include "vector"
#include "priorityScheduling.h"

void handlerPriority(int choice, std::vector<int>& arrival, std::vector<int>& burst, std::vector<int>& priority) {
    if(choice==4) {
        priorityScheduling priority_object(arrival, burst, priority);

    }
}
