//
// Created by yeasi on 25-Jun-23.
//

#ifndef OSPROJECT_CHOICELIST_H
#define OSPROJECT_CHOICELIST_H

#endif //OSPROJECT_CHOICELIST_H
#include "iostream"

void choiceList() {
   std::string str="1.\tFirst Come First Serve (FCFS) Scheduling Algorithm\n"
                   "2.\tNon-Preemptive Shortest Job First (SJF) Scheduling Algorithm\n"
                   "3.\tPreemptive Shortest Job First (SJF) Scheduling Algorithm\n"
                   "4.\tNon-Preemptive Priority Scheduling Algorithm\n"
                   "5.\tPreemptive Priority Scheduling Algorithm\n"
                   "6.\tRound Robin Scheduling Algorithm\n"
                   "7.\tYour Own Scheduling Algorithm\n";

    std::cout<<str;
}
