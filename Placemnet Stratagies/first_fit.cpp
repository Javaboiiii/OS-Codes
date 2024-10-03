//First Fit:
#include <iostream>
#include <vector> // Include the vector header

using namespace std;

// Structure to represent a memory block
struct MemoryBlock {
    int id;
    int size;
    bool allocated;
};

// Function to allocate memory using First Fit strategy
void firstFit(vector<MemoryBlock>& memory, int processId, int processSize) {
    for (int i = 0; i < memory.size(); ++i) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            memory[i].id = processId;
            memory[i].allocated = true;
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

    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    for (int i = 0; i < numProcesses; ++i) {
        int processSize;
        cout << "Enter size of process " << processId << ": ";
        cin >> processSize;
        firstFit(memory, processId++, processSize);
    }

    return 0;
}
