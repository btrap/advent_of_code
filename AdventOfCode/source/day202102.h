#pragma once

void Advent_Of_Code_2021_02()
{
    int result1 = 0;
    int result2 = 0;
    FILE *temp = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day2_input.txt", "r");
    
    int depth = 0;
    int horizontal = 0;
    int aim = 0;
    if(temp)
    {
        FILE *walker = temp;

        char command[8];
        int value = 0;
        while(fscanf(walker, "%s %d", command, &value) != EOF)
        {
            if(command[0] == 'f')
            {
                horizontal += value;
            }
            if(command[0] == 'd')
            {
                depth += value;
            }
            if(command[0] == 'u')
            {
                depth -= value;
            }
        }
        result1 = depth * horizontal;

        fseek(temp, 0, SEEK_SET);

        depth = 0;
        horizontal = 0;
        aim = 0;
        while(fscanf(walker, "%s %d", command, &value) != EOF)
        {
            if(command[0] == 'f')
            {
                horizontal += value;
                depth += aim * value;
            }
            if(command[0] == 'd')
            {
                aim += value;
            }
            if(command[0] == 'u')
            {
                aim -= value;
            }
        }
        result2 = depth * horizontal;

        fclose(temp);
    }

    ASSERT(result1 == 1813801);
    printf("The third star answer is - %d\n", result1);
    ASSERT(result2 == 1960569556);
    printf("The forth star answer is - %d\n", result2);
}

