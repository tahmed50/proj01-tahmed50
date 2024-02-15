#include "warehouse.h"
#include "packer.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int binNumber;
    int lastUsed;
} BinUsage;

BinUsage binUsage[NUMSLOTS];


void initBinUsage() {
    for (int i = 0; i < NUMSLOTS; i++) {
        binUsage[i].binNumber = EMPTYBIN; 
        binUsage[i].lastUsed = -1; 
    }
}


int findLRUBinSlot() {
    int lruSlot = 0;
    for (int i = 1; i < NUMSLOTS; i++) {
        if (binUsage[i].lastUsed < binUsage[lruSlot].lastUsed) {
            lruSlot = i;
        }
    }
    return lruSlot;
}


void updateBinUsage(int slot, int binNumber) {
    binUsage[slot].binNumber = binNumber;
    binUsage[slot].lastUsed = partIndex(); 
}
void processPart(int partNumber) {
    int binNumber = binFromPart(partNumber);
    int partIdx = partIndex();

    for (int i = 0; i < NUMSLOTS; i++) {
        if (binUsage[i].binNumber == binNumber) {
            binUsage[i].lastUsed = partIdx; 
            return; 
        }
    }

    int targetSlot = -1;
    for (int i = 0; i < NUMSLOTS; i++) {
        if (binUsage[i].binNumber == EMPTYBIN) {
            targetSlot = i;
            break;
        }
    }

    if (targetSlot == -1) {
        targetSlot = findLRUBinSlot();
    }

    getBin(binNumber, targetSlot);
    updateBinUsage(targetSlot, binNumber);
}

int main() {
    initBinUsage();
}