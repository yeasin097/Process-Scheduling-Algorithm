//
// Created by yeasi on 6/25/2023.
//

#ifndef OSPROJECT_FIRSTCOMEFIRSTSERVE_H
#define OSPROJECT_FIRSTCOMEFIRSTSERVE_H

#endif //OSPROJECT_FIRSTCOMEFIRSTSERVE_H
//
// Created by yeasi on 22-Jun-23.
//

#ifndef CLION_FISTCOMEFIRSTSERVE_H
#define CLION_FISTCOMEFIRSTSERVE_H

#endif //CLION_FISTCOMEFIRSTSERVE_H

#include "vector"
#include "utility"
#include "algorithm"
#include "iostream"


class fcfsAlgorithm_class {
    std::vector< std::pair<int,int> > processStartTime;
    std::vector< std::pair<int,int> > processFinishTime;
    std::vector< std::pair<int,int> > arrivalBurst;
    std::vector< std::pair<int,int> > arrivalProcess;

    int waiting_time=0;
    int turn_around_time=0;
    int response_time=0;
public:
    fcfsAlgorithm_class(std::vector<int>& arrival, std::vector<int>& burst) {

        for(int i=1; i<=arrival.size(); i++) {
            arrivalBurst.push_back(std::make_pair(arrival[i-1],burst[i-1]));
            arrivalProcess.push_back( std::make_pair(arrival[i-1], i));
        }

        std::sort(arrivalBurst.begin(), arrivalBurst.end());
        std::sort(arrivalProcess.begin(), arrivalProcess.end());


        // because the vectors are sorted based on their arrival time
        // and it is not a preemptive algorithm then I can just iterate the
        // vectors from beginning to end.

        int running_time = 0;

        for(int i=1; i<=arrivalProcess.size(); i++) {
            running_time = std::max(running_time, arrivalProcess[i-1].first);
            // if first process did not arrive at 0th time or if there is any vacancy between processes.
            processStartTime.push_back(std::make_pair(arrivalProcess[i-1].second, running_time));
            processFinishTime.push_back(std::make_pair(arrivalProcess[i-1].second, running_time+arrivalBurst[i-1].second));
            running_time+=arrivalBurst[i-1].second;

            waiting_time+=processStartTime[i-1].second-arrivalProcess[i-1].first;
            turn_around_time+= processFinishTime[i-1].second-arrivalProcess[i-1].first;
            // As this is a non-preemptive algorithm, waiting time and response time are same
            response_time=waiting_time;
        }
    }


    void printFCFStimes() {
        std::cout<< "Average Waiting Time: " <<  (double) waiting_time/arrivalBurst.size() << std::endl;
        std::cout<< "Average Turn Around Time: " <<  (double) turn_around_time/arrivalBurst.size() << std::endl;
        std::cout<< "Average Response Time: " <<  (double) response_time/arrivalBurst.size() << std::endl;
    }

    void gantChartFCFS() {
        for(int i=0; i<processStartTime.size(); i++) {
            std::cout << processStartTime[i].second << "---P" << processStartTime[i].first << "---" << processFinishTime[i].second << "   ";
        }
        std::cout << std::endl;
    }


};
