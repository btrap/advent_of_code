#pragma once

void Advent_Of_Code_2021_20()
{
    int result1 = 0;
    int result2 = 0;

    FILE *day20_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day20_test_input.txt", "r");
    //FILE *day20_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day20_input.txt", "r");
    if(day20_File)
    {
        fseek(day20_File, 0, SEEK_SET);
        fclose(day20_File);
    }

    //ASSERT(result1 == 000);
    printf("The twenty first star answer is - %d\n", result1);
    //ASSERT(result2 == 000);
    printf("The twenty second star answer is - %d\n", result2);
}

