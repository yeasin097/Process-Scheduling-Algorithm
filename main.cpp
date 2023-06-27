#include "iostream"
#include "vector"
#include "handlerFirstThree.h"
#include "handlerPriority.h"
#include "choiceList.h"
#include "roundRobin.h"

int main() {
    choiceList();

    std::vector<int> burstTime={6, 5, 9, 3, 10};
    std::vector<int> arrivalTime={1, 3, 5, 4, 2};
    std::vector<int> priority={2, 3, 1, 5, 4};

    std::cout<< "Your Choice: ";
    int choice; std::cin>>choice;



//    int process; std::cin>>process;
//    for(int i=1; i<=process; i++) {
//        int brust,arrival, pri;
//        std::cin>> brust>> arrival>>pri;
//        burstTime.push_back(brust);
//        arrivalTime.push_back(arrival);
//        priority.push_back(pri);
//
//    }
    if(choice<=3){
        handlerMain(choice, arrivalTime, burstTime);
    }
    else if(choice==4 || choice==5) {
        handlerPriority(choice, arrivalTime, burstTime, priority);
    }
    else if(choice==6) { // round robin
        roundRobin roundRobinObject(arrivalTime, burstTime, 4);
        //roundRobinObject.printStartFinish();
        roundRobinObject.printRobinTimes();
    }

}
