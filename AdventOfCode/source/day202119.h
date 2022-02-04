#pragma once

void Advent_Of_Code_2021_19()
{
    int result1 = 0;
    int result2 = 0;

    FILE *day19_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day19_test_input.txt", "r");
    //FILE *day19_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day19_input.txt", "r");
    if(day19_File)
    {
        fseek(day19_File, 0, SEEK_SET);
        fclose(day19_File);
    }

    //ASSERT(result1 == 000);
    printf("The twenty first star answer is - %d\n", result1);
    //ASSERT(result2 == 000);
    printf("The twenty second star answer is - %d\n", result2);
}

