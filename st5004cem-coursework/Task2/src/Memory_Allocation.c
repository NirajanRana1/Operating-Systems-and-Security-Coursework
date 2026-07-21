#include <stdio.h>

int main() {
    int req[] = {1, 2, 3, 4, 1, 5, 2, 3, 1, 2};
    int ram[3] = {-1, -1, -1}; // -1 means empty slot
    int faults = 0;

    for (int i = 0; i < 10; i++) {
        int found = 0;
        for (int j = 0; j < 3; j++) if (ram[j] == req[i]) found = 1; // check if in RAM

        if (!found) { // not in RAM = miss
            faults++;
            for (int j = 0; j < 2; j++) ram[j] = ram[j+1]; // kick out oldest
            ram[2] = req[i]; // add new at end
            printf("Page %d: MISS  -> RAM: [%d, %d, %d]\n", req[i], ram[0], ram[1], ram[2]);
        } else { // already in RAM = hit
            printf("Page %d: HIT   -> RAM: [%d, %d, %d]\n", req[i], ram[0], ram[1], ram[2]);
        }
    }
    printf("Total faults: %d\n", faults);
    return 0;
}