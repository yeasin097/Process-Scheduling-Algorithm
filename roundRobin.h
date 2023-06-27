//
// Created by yeasi on 26-Jun-23.
//

#ifndef OSPROJECT_ROUNDROBIN_H
#define OSPROJECT_ROUNDROBIN_H

#endif //OSPROJECT_ROUNDROBIN_H
#include "iostream"
#include "vector"
#include "queue"
#include "algorithm"

using namespace std;



class roundRobin {
    vector< pair<int,int> > processStartTime;
    vector< pair<int,int> > processFinishTime;
    vector< pair<int,int> > arrivalBurst;
    vector< pair<int,int> > arrivalProcess;

    int waiting_time=0;
    int turn_around_time=0;
    int response_time=0;

public:
    roundRobin(vector<int>& arrival, vector<int>& burst, int quantum=2){
        for(int i=0; i<arrival.size(); i++) {
            arrivalBurst.push_back(make_pair(arrival[i],burst[i]));
            arrivalProcess.push_back(make_pair(arrival[i], i+1));
        }

        sort(arrivalBurst.begin(), arrivalBurst.end());
        sort(arrivalProcess.begin(), arrivalProcess.end());

        queue<int>queueProcess;
        int running_time=0;

        int jobs=arrival.size();
        bool done[100]={false};
        bool isWaited[100]={false};

        int not_initiated = burst.size();

        // first job pushed to queue
        queueProcess.push(arrivalProcess[0].second);
        not_initiated--;
        running_time=arrivalProcess[0].first;
        int indexofRunningProcess;

        while(jobs) {

            int runningProcess=queueProcess.front();
            int timeLeftofRunningProcess;

//            cout << "Queue at time = " << running_time << "   ";
//            int tempQ=queueProcess.size();
//            while (tempQ--) {
//                int temp=queueProcess.front();
//                cout <<  temp << " ";
//                queueProcess.pop();
//                queueProcess.push(temp);
//            }
//            cout<< "running process " << runningProcess <<endl;

            for(int i=0; i<arrival.size(); i++) {
                if(arrivalProcess[i].second==runningProcess) {
                    timeLeftofRunningProcess=arrivalBurst[i].second;
                    indexofRunningProcess=i;
                }
            }

            if(not_initiated>0) {
                for(int time=running_time; time<=running_time+min(timeLeftofRunningProcess, quantum); time++) {
                    for(int i=0; i<jobs; i++) {
                        if(time==arrivalProcess[i].first && runningProcess!=arrivalProcess[i].second) { // a process is created then it pushed to queue.
                            queueProcess.push(arrivalProcess[i].second);
                            not_initiated--;
                            //cout<< "NotInitiated Loop" << endl;
                        }
                    }
                }
            }

            queueProcess.pop();

            if(timeLeftofRunningProcess>quantum) { // the process won't be finished in this quantum time
                if(!isWaited[indexofRunningProcess]) { // if first time running then update start time
                    processStartTime.push_back(make_pair(arrivalProcess[indexofRunningProcess].second, running_time));
                    isWaited[indexofRunningProcess]= true;
                }
                queueProcess.push(runningProcess);
                arrivalBurst[indexofRunningProcess].second=timeLeftofRunningProcess-quantum;
                running_time+=quantum;
            }
            else {

                if(!isWaited[indexofRunningProcess]) { // if a process total burst time less than quantum
                    processStartTime.push_back(make_pair(arrivalProcess[indexofRunningProcess].second, running_time));
                    isWaited[indexofRunningProcess]= true;
                }
                //cout<< "Process finised P" << arrivalProcess[indexofRunningProcess].second << endl;
                arrivalBurst[indexofRunningProcess].second=0;
                processFinishTime.push_back(make_pair(arrivalProcess[indexofRunningProcess].second, running_time+timeLeftofRunningProcess));
                running_time+=timeLeftofRunningProcess;
                jobs--; // a job is finished


            }
        }

        sort(processStartTime.begin(), processStartTime.end());
        sort(processFinishTime.begin(), processFinishTime.end());

        for(int i=0; i<processStartTime.size(); i++) {
            waiting_time+=processFinishTime[i].second-arrival[i]-burst[i];
            turn_around_time+=processFinishTime[i].second-arrival[i];
            response_time+=processStartTime[i].second-arrival[i];
        }
    }

    void printStartFinish() {
        cout<< "Start Times" << endl;
        for(int i=0; i<processStartTime.size(); i++) {
            cout << processStartTime[i].first << "P  " << processStartTime[i].second << endl;
        }
        cout<< "Finish Times" << endl;
        for(int i=0; i<processFinishTime.size(); i++) {
            cout << processFinishTime[i].first << "P  " << processFinishTime[i].second << endl;
        }
    }

    void printRobinTimes() {
        cout<< "Average Waiting Time: " <<  (double) waiting_time/arrivalBurst.size() << std::endl;
        cout<< "Average Turn Around Time: " <<  (double) turn_around_time/arrivalBurst.size() << std::endl;
        cout<< "Average Response Time: " <<  (double) response_time/arrivalBurst.size() << std::endl;
    }
};
