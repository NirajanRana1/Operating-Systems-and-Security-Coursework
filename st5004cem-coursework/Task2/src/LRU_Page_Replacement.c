#include <stdio.h>

int main() 
{
    int ram[3], last_used[3], count = 0, time = 0, faults = 0;
    int req[] = {1, 2, 3, 4, 1, 5, 2, 3, 1, 2};
    
    printf("LRU Page Replacement\n\n");
    
    for (int i = 0; i < 10; i++) 
    {
        int page = req[i], found = 0;
        
        // Check if in RAM
        for (int j = 0; j < count; j++) 
        {
            if (ram[j] == page) { found = 1; last_used[j] = time; printf("Page %d: HIT\n", page); break; }
        }
        
        if (!found) 
        {
            faults++;
            if (count < 3) { ram[count] = page; last_used[count++] = time; printf("Page %d: MISS -> slot %d\n", page, count-1); }
            else 
            {
                int lru = 0;
                for (int j = 1; j < 3; j++) if (last_used[j] < last_used[lru]) lru = j;
                ram[lru] = page; last_used[lru] = time;
                printf("Page %d: MISS -> replaced slot %d\n", page, lru);
            }
        }
        time++;
    }
    
    printf("\nFaults: %d, Hit rate: %.1f%%\n", faults, (10-faults)*10.0);
    return 0;
}