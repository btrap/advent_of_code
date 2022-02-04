#define _AMD64_

// Solution for problem 1
#pragma warning(push)

#pragma warning(disable : 4201) // we want anonymous unions and structs 
#pragma warning(disable : 4514) // we can't control that the compiler doesnt inline printf
#pragma warning(disable : 4710) // we can't control that the compiler doesnt inline printf
#pragma warning(disable : 4820) // we can't control byte padding
#pragma warning(disable : 4996) // freopen is plenty safe for us
#pragma warning(disable : 5039) // we dont care if callbacks throw exceptions

#include <cstdio>

#include "aoc_helpers.h"

#include "day202101.h"
#include "day202102.h"
#include "day202103.h"
#include "day202104.h"
#include "day202105.h"
#include "day202106.h"
#include "day202107.h"
#include "day202108.h"
#include "day202109.h"
#include "day202110.h"
#include "day202111.h"
#include "day202112.h"
#include "day202113.h"
#include "day202114.h"
#include "day202115.h"
#include "day202116.h"
#include "day202117.h"
#include "day202118.h"
#include "day202119.h"
#include "day202120.h"
#include "day202121.h"
#include "day202122.h"
#include "day202123.h"
#include "day202124.h"
#include "day202125.h"

//// Question:
//void problem()
//{
//    int result1 = 0;
//    int result2 = 0;
//    FILE *temp = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day1_input.txt", "r");
//    // run tests
//    fclose(temp);
//    ASSERT(result1 == 0);
//    printf("The first star answer is - %d\n", result1);
//    ASSERT(result2 == 0);
//    printf("The second star answer is - %d\n", result2);
//}
//// Answer1:
//// Answer2:

int main(int argc, char **argv)
{
    // Init memory
    SetupMemoryPools();

    Advent_Of_Code_2021_01();
    //Advent_Of_Code_2021_02();
    //Advent_Of_Code_2021_03();
    //Advent_Of_Code_2021_04();
    //Advent_Of_Code_2021_05();
    //Advent_Of_Code_2021_06();
    //Advent_Of_Code_2021_07(); // (n^2 + 2) / 2
    //Advent_Of_Code_2021_08();
    //Advent_Of_Code_2021_09();
    //Advent_Of_Code_2021_10();
    //Advent_Of_Code_2021_11();
    //Advent_Of_Code_2021_12();
    //Advent_Of_Code_2021_13();
    //Advent_Of_Code_2021_14();
    //Advent_Of_Code_2021_15(); // PATH FINDING
    //Advent_Of_Code_2021_16();
    //Advent_Of_Code_2021_17(); // TRAGECTORY <-- WORKING ON THIS
    //Advent_Of_Code_2021_18(); // BROKEN
    //Advent_Of_Code_2021_19();
    //Advent_Of_Code_2021_20();
    //Advent_Of_Code_2021_21();
    //Advent_Of_Code_2021_22();
    //Advent_Of_Code_2021_23();
    //Advent_Of_Code_2021_24();
    //Advent_Of_Code_2021_25();

    return 0;
}

#pragma warning(pop)
