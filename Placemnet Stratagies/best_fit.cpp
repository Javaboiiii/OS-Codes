//Best Fit
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct MemoryBlock {
    int id;
    int size;
    bool allocated;
};

void bestFit(vector<MemoryBlock>& memory, int processId, int processSize) {
    int bestFitIndex = -1;
    int minFragmentation = INT_MAX;

    for (int i = 0; i < memory.size(); ++i) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            int fragmentation = memory[i].size - processSize;
            if (fragmentation < minFragmentation) {
                minFragmentation = fragmentation;
                bestFitIndex = i;
            }
        }
    }

    if (bestFitIndex != -1) {
        memory[bestFitIndex].id = processId;
        memory[bestFitIndex].allocated = true;
        cout << "Process " << processId << " allocated to Memory Block " << bestFitIndex << endl;
    } else {
        cout << "Not enough memory available for Process " << processId << endl;
    }
}

int main() {
    int blockSize;
    cout << "Enter the number of memory blocks: ";
    cin >> blockSize;

    vector<MemoryBlock> memory(blockSize);

    for (int i = 0; i < blockSize; ++i) {
        cout << "Enter size of memory block " << i << ": ";
        cin >> memory[i].size;
        memory[i].id = -1;
        memory[i].allocated = false;
    }

    int processId = 1;

    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    for (int i = 0; i < numProcesses; ++i) {
        int processSize;
        cout << "Enter size of process " << processId << ": ";
        cin >> processSize;
        bestFit(memory, processId++, processSize);
    }

    return 0;
}
