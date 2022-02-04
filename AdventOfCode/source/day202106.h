#pragma once

void Advent_Of_Code_2021_06()
{
    umax result1 = 0;
    umax result2 = 0;

    FILE *day6_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day6_input.txt", "r");
    if(day6_File)
    {
        int life_Cycle_r1 = 80;
        int life_Cycle_r2 = 256;
        int repro_Rate = 6;
        int birth_Cycle = 8 + 1;
        
        umax *children_Max = 0;
        STORE_PERM_DATA(children_Max, birth_Cycle);
        for(int i = 0; i < birth_Cycle; ++i)
        {
            children_Max[i] = 0;
        }

        int fish = 0;
        while(fscanf(day6_File, "%d,", &fish) != EOF)
        {
            ++children_Max[fish];
        }

        fclose(day6_File);

        umax new_Cycle = 0;
        for(int i = 0; i < life_Cycle_r1; ++i)
        {
            new_Cycle = children_Max[0];

            for(int i = 1; i < birth_Cycle; ++i)
            {
                children_Max[i - 1] = children_Max[i];
            }

            children_Max[repro_Rate] += new_Cycle;
            children_Max[birth_Cycle - 1] = new_Cycle;
        }
        
        umax max_Fish = 0;
        for(int i = 0; i < birth_Cycle; ++i)
        {
            max_Fish += children_Max[i];
            //printf("MaxFish - %llu\n", max_Fish);
        }

        result1 = max_Fish;

        for(int i = life_Cycle_r1; i < life_Cycle_r2; ++i)
        {
            new_Cycle = children_Max[0];

            for(int i = 1; i < birth_Cycle; ++i)
            {
                children_Max[i - 1] = children_Max[i];
            }

            children_Max[repro_Rate] += new_Cycle;
            children_Max[birth_Cycle - 1] = new_Cycle;
        }
        
        max_Fish = 0;
        for(int i = 0; i < birth_Cycle; ++i)
        {
            max_Fish += children_Max[i];
            //printf("MaxFish - %llu\n", max_Fish);
        }

        result2 = max_Fish;
    }
    
    ASSERT(result1 == 343441);
    printf("The eleventh star answer is - %llu\n", result1);
    ASSERT(result2 == 1569108373832);
    printf("The twelfth star answer is - %llu\n", result2);
}
