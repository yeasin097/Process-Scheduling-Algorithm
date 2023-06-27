//
// Created by yeasi on 24-Jun-23.
//

#ifndef CLION_SHORTESTJOBFIRST_H
#define CLION_SHORTESTJOBFIRST_H

#endif //CLION_SHORTESTJOBFIRST_H

#include "iostream"
#include "vector"
#include "utility"
#include "algorithm"


class shortestJobFirst {
    std::vector< std::pair<int,int> > burstArrival;
    std::vector< std::pair<int,int> > burstProcess;
    std::vector< std::pair<int,int> > processStartTime;
    std::vector< std::pair<int,int> > processFinishTime;

    int waiting_time=0;
    int turn_around_time=0;
    int response_time=0;

public:
    shortestJobFirst(std::vector<int>& arrival, std::vector<int>& burst) {

        for(int i=1; i<=arrival.size(); i++) {
            burstArrival.push_back(std::make_pair(burst[i-1], arrival[i-1]));
            burstProcess.push_back(std::make_pair(burst[i-1],i));
        }

        std::sort(burstArrival.begin(), burstArrival.end());
        std::sort(burstProcess.begin(), burstProcess.end());

        int running_time=0;
        bool done[100]={false};
        int jobs=arrival.size();

        while(jobs) {
            for(int i=0; i<burstArrival.size(); i++) {
                if(running_time>=burstArrival[i].second && !done[i]) {
                    done[i]= true;
                    processStartTime.push_back(std::make_pair(burstProcess[i].second, running_time));
                    processFinishTime.push_back(std::make_pair(burstProcess[i].second, running_time+burstProcess[i].first));
                    waiting_time+=processStartTime[i].second-burstArrival[i].second;
                    turn_around_time+=processFinishTime[i].second-burstArrival[i].second;
                    response_time=waiting_time; // non-preemptive algorithm
                    jobs--;
                    running_time+=burstProcess[i].first;
                    break;
                }
                else {
                    running_time++;
                }
            }
        }
    }

    void printSJFtimes() {
        std::cout<< "Average Waiting Time: " <<  (double) waiting_time/burstArrival.size() << std::endl;
        std::cout<< "Average Turn Around Time: " <<  (double) turn_around_time/burstArrival.size() << std::endl;
        std::cout<< "Average Response Time: " <<  (double) response_time/burstArrival.size() << std::endl;
    }

    void gantChartSJF() {
        for(int i=0; i<processStartTime.size(); i++) {
            std::cout << processStartTime[i].second << "---P" << processStartTime[i].first << "---" << processFinishTime[i].second << "   ";
        }
        std::cout << std::endl;
    }
};
