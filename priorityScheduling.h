//
// Created by yeasi on 6/25/2023.
//

#ifndef OSPROJECT_PRIORITYSCHEDULING_H
#define OSPROJECT_PRIORITYSCHEDULING_H

#endif //OSPROJECT_PRIORITYSCHEDULING_H

#include "vector"
#include "utility"
#include "algorithm"
#include "iostream"

class priorityScheduling {
    std::vector< std::pair<int,int> > priority_arrival;
    std::vector< std::pair<int,int> > priority_burst;
    std::vector< std::pair<int,int> > priority_process;

    std::vector< std::pair<int,int> > processStartTime;
    std::vector< std::pair<int,int> > processFinishTime;

    int waiting_time=0;
    int turn_around_time=0;
    int response_time=0;

public:
    priorityScheduling(std::vector<int>& arrival, std::vector<int>& burst, std::vector<int>& priority) {
        for (int i = 1; i <= priority.size(); ++i) {
           priority_arrival.push_back(std::make_pair(priority[i-1], arrival[i-1]));
           priority_burst.push_back(std::make_pair(priority[i-1], burst[i-1]));
           priority_process.push_back(std::make_pair(priority[i-1], i));
        }

        std::sort(priority_process.begin(), priority_process.end());
        std::sort(priority_burst.begin(), priority_burst.end());
        std::sort(priority_arrival.begin(), priority_arrival.end());

        int running_time=0;
        bool done[100]={false};
        int jobs=arrival.size();

        while(jobs) {
            for(int i=0; i<priority_arrival.size(); i++) {
                if(running_time>=priority_arrival[i].second && !done[i]) {
                    processStartTime.push_back(std::make_pair(priority_process[i].second, running_time));
                    processFinishTime.push_back(std::make_pair(priority_process[i].second, running_time+priority_burst[i].second));
                    running_time+=priority_burst[i].second;
                    waiting_time+=(processStartTime[i].second-priority_arrival[i].second);
                    turn_around_time+=(processFinishTime[i].second-priority_arrival[i].second);
                    response_time=waiting_time; // non-preemptive algorithm
                    done[i]= true;
                    jobs--;
                    break;
                }
                else {
                    running_time++;
                }
            }
        }
    }


    void printPrioritytimes() {
        std::cout<< "Average Waiting Time: " <<  (double) waiting_time/priority_arrival.size() << std::endl;
        std::cout<< "Average Turn Around Time: " <<  (double) turn_around_time/priority_arrival.size() << std::endl;
        std::cout<< "Average Response Time: " <<  (double) response_time/priority_arrival.size() << std::endl;
    }

    void gantChartFCFS() {
        for(int i=0; i<processStartTime.size(); i++) {
            std::cout << processStartTime[i].second << "---P" << processStartTime[i].first << "---" << processFinishTime[i].second << "   ";
        }
        std::cout << std::endl;
    }
};
