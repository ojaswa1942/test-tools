// g++ main.cpp -lpthread && ./a.out 

#include<iostream>
#include<chrono>
#include<thread>
#define llint long long int

using namespace std;

void sleep(int t) {
    this_thread::sleep_for(chrono::seconds(t));
}

llint* allocateMemoryToIntegers(llint n) {
    llint *ptr = (llint*) malloc(n * sizeof(llint));
    if(!ptr) {
        cout<<"Error: unable to allocate memory"<<endl;
        exit(1);
    }
    return ptr;
}

void fillAllocatedMemory(llint *ptr, llint n) {
    for (llint i = 0; i < n; i++){
        ptr[i] = 1ll;
    }
}

void allocateAndFillMemory(llint n) {
    llint *ptr = allocateMemoryToIntegers(n);
    fillAllocatedMemory(ptr, n);
}

int main(int argc, char *argv[]){
    llint targetBytes = 1ll * 1024 * 1024 * 500;     // 500Mb
    int targetTime = 120;   // seconds

    if(argc >= 2) {
        targetBytes = stoll(argv[1]) * 1024 * 1024;
    }
    if(argc >= 3) {
        targetTime = stoi(argv[2]);
    }
    
    llint llintegersTotal = targetBytes / sizeof(llint);
    llint llintegersPerSecond = llintegersTotal / targetTime;

    cout<<"Target Time: "<<targetTime<<endl;
    cout<<"Target Bytes: "<<targetBytes<<endl;
    cout<<"Allocation per second: "<<float(llintegersPerSecond * sizeof(llint))/(1024*1024)<<" MB"<<endl;

    cout<<"> init;"<<endl<<endl;

    llint currentAllocatedIntegers = 0;
    llint currentAllocatedSize = 0;

    while(currentAllocatedIntegers <= (llintegersTotal - llintegersPerSecond)) {    // do not exceed specified
        allocateAndFillMemory(llintegersPerSecond);
        currentAllocatedIntegers += llintegersPerSecond;
        currentAllocatedSize += (llintegersPerSecond * sizeof(llint));
        cout<<"Total size allocated: "<<(currentAllocatedSize)/(1024 * 1024)<<" megabytes"<<endl;
        sleep(1);
    }

    if(targetBytes - currentAllocatedSize > 0) {
        allocateAndFillMemory((targetBytes - currentAllocatedSize)/sizeof(llint));  // ignore error of 8bytes
        currentAllocatedSize += (targetBytes - currentAllocatedSize);
    }

    cout<<"Completed total memory allocation"<<endl;
    return 1;
}
