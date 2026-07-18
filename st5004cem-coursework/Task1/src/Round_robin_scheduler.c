#include <stdio.h>

// Process info
struct Process {
    int id;             // Process name/number
    int burst;          // Total work time needed
    int remaining;      // Work left to do
};

int main() 
{
    struct Process p[3] = {
        {1, 10, 10},    // Process 1: needs 10 units of time
        {2, 5, 5},      // Process 2: needs 5 units
        {3, 8, 8}       // Process 3: needs 8 units
    };
    
    int quantum = 3;    // Time slice - like giving each person 3 minutes to talk
    int done = 0;       // How many processes finished
    int time = 0;       // Total time passed
    
    printf("Round-Robin Scheduling (quantum = %d)\n\n", quantum);
    
    // Keep going until all processes finish
    while (done < 3) 
    {
        for (int i = 0; i < 3; i++) 
        {
            if (p[i].remaining > 0)              // If process has work left
            {
                if (p[i].remaining <= quantum)    // Can finish in this turn
                {
                    time += p[i].remaining;
                    printf("P%d: runs %d units, finishes at time %d\n", 
                           p[i].id, p[i].remaining, time);
                    p[i].remaining = 0;
                    done++;
                }
                else                               // Needs more turns
                {
                    time += quantum;
                    p[i].remaining -= quantum;
                    printf("P%d: runs %d units, %d left at time %d\n", 
                           p[i].id, quantum, p[i].remaining, time);
                }
            }
        }
    }
    
    printf("\nAll processes completed at time %d\n", time);
    return 0;
}