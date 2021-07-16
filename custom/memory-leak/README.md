# memory-leak

Program which gradually allocates target memory in the desired time duration. It takes in both target memory and duration as parameters and occupies memory every second. The objective is to replicate the behaviour of a misbehaving application resulting in memory leak.   

## Usage
```
./memory-leak <target bytes (MB)> <target duration (s)>
```

Sample Usage:
```
./memory-leak 1000 100
```
This will occupy 1000MB over 100 seconds and exit.

## Compiling
```
g++ main.cpp -lpthread -o memory-leak-amd64 -static
aarch64-linux-gnu-g++-8 main.cpp -lpthread -o memory-leak-arm64 -static
```
