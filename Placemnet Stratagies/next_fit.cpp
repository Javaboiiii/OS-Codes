//Next Fit
#include <iostream>
#include <vector>

using namespace std;

// Structure to represent a memory block
struct MemoryBlock {
    int id;
    int size;
    bool allocated;
};

// Function to allocate memory using Next Fit strategy
void nextFit(vector<MemoryBlock>& memory, int processId, int processSize, int& lastAllocatedIndex) {
    for (int i = lastAllocatedIndex; i < memory.size(); ++i) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            memory[i].id = processId;
            memory[i].allocated = true;
            lastAllocatedIndex = i;
            cout << "Process " << processId << " allocated to Memory Block " << i << endl;
            return;
        }
    }
    for (int i = 0; i < lastAllocatedIndex; ++i) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            memory[i].id = processId;
            memory[i].allocated = true;
            lastAllocatedIndex = i;
            cout << "Process " << processId << " allocated to Memory Block " << i << endl;
            return;
        }
    }
    cout << "Not enough memory available for Process " << processId << endl;
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
    int lastAllocatedIndex = 0; // Used for Next Fit

    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    for (int i = 0; i < numProcesses; ++i) {
        int processSize;
        cout << "Enter size of process " << processId << ": ";
        cin >> processSize;
        nextFit(memory, processId++, processSize, lastAllocatedIndex);
    }

    return 0;
}
