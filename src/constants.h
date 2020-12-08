#ifndef CONSTANTS_H
#define CONSTANTS_H

//
// Timing constraints
//

// Constraints in DRAM clocks
#define     tRC     76
#define     tRAS    52
#define     tRRD_L  6
#define     tRRD_S  4
#define     tRP     24
#define     tCWD    20
#define     tCAS    24
#define     tRCD    24
#define     tWR     20
#define     tRTP    12
#define     tCCD_L  8
#define     tCCD_S  4
#define     tBURST  4
#define     tWTR_L  12
#define     tWTR_S  4

// Constraints in nanoseconds
#define     tRFC    350
#define     REFI    7800

// Other constants
#define     CONTROLLER_CAPACITY 16

#endif
