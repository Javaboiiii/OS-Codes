//Worst Fit:
#include <iostream>
#include <vector>

using namespace std;

// Structure to represent a memory block
struct MemoryBlock {
    int id;
    int size;
    bool allocated;
};

// Function to allocate memory using Worst Fit strategy
void worstFit(vector<MemoryBlock>& memory, int processId, int processSize) {
    int worstFitIndex = -1;
    int maxFragmentation = INT_MIN;

    for (int i = 0; i < memory.size(); ++i) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            int fragmentation = memory[i].size - processSize;
            if (fragmentation > maxFragmentation) {
                maxFragmentation = fragmentation;
                worstFitIndex = i;
            }
        }
    }

    if (worstFitIndex != -1) {
        memory[worstFitIndex].id = processId;
        memory[worstFitIndex].allocated = true;
        cout << "Process " << processId << " allocated to Memory Block " << worstFitIndex << endl;
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
        worstFit(memory, processId++, processSize);
    }

    return 0;
}

