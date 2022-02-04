#pragma once

int CalcFuelCost(int * hor_Pos, int hor_Pos_Length, int curr, int * step_Cost, int min)
{
    int total = 0;

    int new_Pos = 0;
    for(int i = 0; i < hor_Pos_Length; ++i)
    {
        new_Pos = hor_Pos[i];
        if(new_Pos > curr)
        {
            total += step_Cost[new_Pos - curr];
        }
        else
        {
            total += step_Cost[curr - new_Pos];
        }

        if(total >= min)
            return min;
    }

    return total;
}

void Advent_Of_Code_2021_07()
{
    int result1 = 0;
    int result2 = 0;

    FILE *day7_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day7_input.txt", "r");
    if(day7_File)
    {
        int hor_Pos_Length = 0;
        int temp_Hor_Pos = 0;
        while(fscanf(day7_File, "%d,", &temp_Hor_Pos) != EOF)
        {
            ++hor_Pos_Length;
        }

        fseek(day7_File, 0, SEEK_SET);
        
        int *hor_Pos = 0;
        STORE_PERM_DATA(hor_Pos, hor_Pos_Length);
        int max_Pos = 0;
        for(int i = 0; i < hor_Pos_Length; ++i)
        {
            fscanf(day7_File, "%d,", &temp_Hor_Pos);
            hor_Pos[i] = temp_Hor_Pos;
            if(temp_Hor_Pos > max_Pos)
                max_Pos = temp_Hor_Pos;
        }
        ++max_Pos;

        fclose(day7_File);
        
        int *tested_Distance = 0;
        STORE_PERM_DATA(tested_Distance, max_Pos);
        for(int i = 0; i < max_Pos; ++i)
        {
            tested_Distance[i] = -1;
        }

        
        int *step_Cost = 0;
        STORE_PERM_DATA(step_Cost, max_Pos);
        int previous = 0;
        for(int i = 0; i < max_Pos; ++i)
        {
            step_Cost[i] = i + previous;
            previous = step_Cost[i];
        }
        
        //for(int i = 0; i < max_Pos; ++i)
        //{
        //    printf("%d, ", step_Cost[i]);
        //}
        //printf("\n");

        // Result 1
        //result1 = 99999999;
        //int fuel_Used = 0;
        //for(int i = 0; i < hor_Pos_Length; ++i)
        //{
        //    fuel_Used = tested_Distance[hor_Pos[i]];

        //    if(fuel_Used < 0)
        //    {
        //        tested_Distance[hor_Pos[i]] = CalcFuelCost(hor_Pos, hor_Pos_Length, hor_Pos[i], step_Cost, result1);
        //        printf("hor_Pos[i] - %d, ", tested_Distance[hor_Pos[i]]);
        //    }

        //    fuel_Used = tested_Distance[hor_Pos[i]];
        //    if(fuel_Used < result1)
        //    {
        //        result1 = fuel_Used;
        //    }
        //}

        result1 = 99999999;
        int fuel_Used = 0;
        for(int i = 0; i < max_Pos; ++i)
        {
            tested_Distance[i] = CalcFuelCost(hor_Pos, hor_Pos_Length, i, step_Cost, result1);
            fuel_Used = tested_Distance[i];

            printf("hor_Pos[i] - %d, ", fuel_Used);

            if(fuel_Used < result1)
            {
                result1 = fuel_Used;
            }
        }

        //for(int i = 0; i < max_Pos; ++i)
        //{
        //    printf("hor_Pos[i] - %d, ", tested_Distance[i]);
        //    printf("\n");
        //}
    }

    //ASSERT(result1 == 352331);
    printf("The thirtenth star answer is - %d\n", result1);
    //ASSERT(result2 == 99266250);
    printf("The fourtenth star answer is - %d\n", result2);
}
