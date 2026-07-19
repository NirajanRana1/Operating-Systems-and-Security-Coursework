#include <stdio.h>

// FIFO: replace oldest page (first one that came in)
int fifo(int req[], int n) 
{
    int ram[3], count = 0, faults = 0;       // RAM slots, pages loaded, error count
    
    for (int i = 0; i < n; i++) 
    {
        int found = 0;
        // Search if page already in RAM
        for (int j = 0; j < count; j++) 
            if (ram[j] == req[i]) { found = 1; break; }
        
        if (!found)                          // Page not in RAM = fault
        {
            faults++;
            if (count < 3)                   // Space available? Just add
                ram[count++] = req[i];
            else                             // Full? Remove oldest, add new
            { 
                for (int j = 0; j < 2; j++) ram[j] = ram[j+1]; 
                ram[2] = req[i]; 
            }
        }
    }
    return faults;
}

// LRU: replace page not used for longest time
int lru(int req[], int n) 
{
    int ram[3], last[3], count = 0, time = 0, faults = 0;
    
    for (int i = 0; i < n; i++) 
    {
        int found = 0;
        // Search if page in RAM
        for (int j = 0; j < count; j++) 
            if (ram[j] == req[i]) { found = 1; last[j] = time; break; }  // Update when used
        
        if (!found)                          // Page not in RAM = fault
        {
            faults++;
            if (count < 3)                   // Space available? Just add
            { ram[count] = req[i]; last[count++] = time; }
            else                             // Full? Find oldest used, replace it
            { 
                int l = 0; 
                for (int j = 1; j < 3; j++) if (last[j] < last[l]) l = j; // Find LRU
                ram[l] = req[i]; last[l] = time; 
            }
        }
        time++;                              // Clock ticks
    }
    return faults;
}

int main() 
{
    int req[] = {1, 2, 3, 4, 1, 5, 2, 3, 1, 2}, n = 10;
    int f = fifo(req, n), l = lru(req, n);
    
    // Show results
    printf("FIFO - Faults: %d, Hit: %.1f%%\n", f, (n-f)*10.0);
    printf("LRU  - Faults: %d, Hit: %.1f%%\n", l, (n-l)*10.0);
    printf("\nLRU is %s (fewer faults)\n", l < f ? "better" : (l > f ? "worse" : "same"));
    return 0;
