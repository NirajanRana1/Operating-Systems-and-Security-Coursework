#include <stdio.h>

int main() 
{
    int page_size = 4;                          // Each page holds 4 units
    int pages_in_ram = 3;                       // RAM can hold 3 pages
    int ram[3];                                 // RAM slots
    int ram_count = 0;                          // How many pages loaded
    
    // Process needs these addresses (like pages in a book you want to read)
    int requests[] = {1, 2, 3, 4, 1, 5, 2, 3, 1, 2};
    int n = 10;                                 // Total requests
    
    int page_faults = 0;                        // Times page not in RAM
    
    printf("Paging System (page_size=%d, ram_slots=%d)\n\n", page_size, pages_in_ram);
    
    for (int i = 0; i < n; i++) 
    {
        int page = requests[i];
        int found = 0;
        
        // Check if page already in RAM
        for (int j = 0; j < ram_count; j++) 
        {
            if (ram[j] == page) 
            {
                found = 1;
                printf("Page %d: HIT (already in RAM)\n", page);
                break;
            }
        }
        
        // Page not in RAM = page fault (need to load from disk)
        if (!found) 
        {
            page_faults++;
            if (ram_count < pages_in_ram)       // RAM has empty slot
            {
                ram[ram_count] = page;
                ram_count++;
                printf("Page %d: MISS -> loaded to RAM slot %d\n", page, ram_count-1);
            }
            else                                // RAM full, replace oldest (FIFO)
            {
                // Shift everything left, add new at end (FIFO replacement)
                for (int j = 0; j < pages_in_ram - 1; j++)
                    ram[j] = ram[j + 1];
                ram[pages_in_ram - 1] = page;
                printf("Page %d: MISS -> replaced oldest, RAM: [%d,%d,%d]\n", 
                       page, ram[0], ram[1], ram[2]);
            }
        }
    }
    
    // Calculate stats
    float miss_rate = (float)page_faults / n * 100;
    float hit_rate = 100 - miss_rate;
    
    printf("\n--- Results ---\n");
    printf("Page faults: %d\n", page_faults);
    printf("Hit rate: %.1f%%\n", hit_rate);
    printf("Miss rate: %.1f%%\n", miss_rate);
    
    return 0;
}