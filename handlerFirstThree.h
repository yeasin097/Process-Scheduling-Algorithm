//
// Created by yeasi on 20-Jun-23.
//

#ifndef CLION_HANDLERFIRSTTHREE_H
#define CLION_HANDLERFIRSTTHREE_H

#endif //CLION_HANDLERFIRSTTHREE_H


#include "utility"
#include "vector"
#include "iostream"
#include "firstComeFirstServe.h"
#include "shortestJobFirst.h"

void handlerMain(int choice, std::vector<int>& arrival, std::vector<int>& burst) {
    if(choice==2) {
        shortestJobFirst sjf_object(arrival,burst);
        std::cout << "Data sent" << std::endl;
        sjf_object.printSJFtimes();
        sjf_object.gantChartSJF();
    }
    else if(choice==3) {
        fcfsAlgorithm_class fcfs_object(arrival,burst);
        fcfs_object.printFCFStimes();
        fcfs_object.gantChartFCFS();
    }
}
