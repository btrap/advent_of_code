#pragma once

struct Hydrothermal_Line
{
    int sx;
    int sy;
    int ex;
    int ey;
};

struct Hydrothermal_Vent
{
    int *vent_Grid;
    int max_Size;
};

void PrintGrid(Hydrothermal_Vent *hydro_Vent)
{
    for(int i = 0; i < hydro_Vent->max_Size; ++i)
    {
        for(int j = 0; j < hydro_Vent->max_Size; ++j)
        {
            int value = hydro_Vent->vent_Grid[i * hydro_Vent->max_Size + j];
            if(value)
            {
                printf("%d ", value);
            }
            else
            {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int OverlapPoints(Hydrothermal_Vent *hydro_Vent)
{
    int result = 0;

    for(int i = 0; i < hydro_Vent->max_Size; ++i)
    {
        for(int j = 0; j < hydro_Vent->max_Size; ++j)
        {
            int value = hydro_Vent->vent_Grid[i * hydro_Vent->max_Size + j];
            if(value > 1)
            {
                ++result;
            }
        }
    }

    return result;
}

void ResetVents(Hydrothermal_Vent *hydro_Vent)
{
    for(int i = 0; i < hydro_Vent->max_Size; ++i)
    {
        for(int j = 0; j < hydro_Vent->max_Size; ++j)
        {
            hydro_Vent->vent_Grid[i * hydro_Vent->max_Size + j] = 0;
        }
    }
}

bool IsDiagonal(Hydrothermal_Line *hydro_Line)
{
    int x_Diff = hydro_Line->sx - hydro_Line->ex;
    int y_Diff = hydro_Line->sy - hydro_Line->ey;

    return (x_Diff == y_Diff) || (x_Diff == -y_Diff);
}

void Advent_Of_Code_2021_05()
{
    int result1 = 0;
    int result2 = 0;

    FILE *day5_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day5_input.txt", "r");
    if(day5_File)
    {
        int vent_Count = 0;
        Hydrothermal_Line temp_Line = {0};
        int max_Size = 0;

        while(fscanf(day5_File, "%d,%d -> %d,%d\n", &temp_Line.sx, &temp_Line.sy, &temp_Line.ex, &temp_Line.ey) != EOF)
        {
            ++vent_Count;
            if(max_Size < temp_Line.sx)
            {
                max_Size = temp_Line.sx;
            }
            if(max_Size < temp_Line.sy)
            {
                max_Size = temp_Line.sy;
            }
            if(max_Size < temp_Line.ex)
            {
                max_Size = temp_Line.ex;
            }
            if(max_Size < temp_Line.ey)
            {
                max_Size = temp_Line.ey;
            }
        }
        fseek(day5_File, 0, SEEK_SET);
        
        Hydrothermal_Vent hydro_Vent = {0};
        hydro_Vent.max_Size = max_Size + 1;
        STORE_PERM_DATA(hydro_Vent.vent_Grid, max_Size * max_Size);
        //PrintGrid(&hydro_Vent);

        while(fscanf(day5_File, "%d,%d -> %d,%d\n", &temp_Line.sx, &temp_Line.sy, &temp_Line.ex, &temp_Line.ey) != EOF)
        {
            if(temp_Line.sx == temp_Line.ex)
            {
                int start = temp_Line.sy;
                int end = temp_Line.ey;

                if(temp_Line.sy > temp_Line.ey)
                {
                    end = temp_Line.sy;
                    start = temp_Line.ey;
                }

                for(int j = start; j < end + 1; ++j)
                {
                    ++hydro_Vent.vent_Grid[temp_Line.sx + hydro_Vent.max_Size * j];
                }
            }
            else if(temp_Line.sy == temp_Line.ey)
            {
                int start = temp_Line.sx;
                int end = temp_Line.ex;

                if(temp_Line.sx > temp_Line.ex)
                {
                    end = temp_Line.sx;
                    start = temp_Line.ex;
                }

                for(int i = start; i < end + 1; ++i)
                {
                    ++hydro_Vent.vent_Grid[temp_Line.sy * hydro_Vent.max_Size + i];
                }
            }
            //PrintGrid(&hydro_Vent);
        }

        //PrintGrid(&hydro_Vent);
        result1 = OverlapPoints(&hydro_Vent);

        fseek(day5_File, 0, SEEK_SET);

        while(fscanf(day5_File, "%d,%d -> %d,%d\n", &temp_Line.sx, &temp_Line.sy, &temp_Line.ex, &temp_Line.ey) != EOF)
        {
            if(IsDiagonal(&temp_Line))
            {
                int start_X = temp_Line.sx;
                int end_X = temp_Line.ex;
                
                int start_Y = temp_Line.sy;
                int end_Y = temp_Line.ey;

                if(temp_Line.sx > temp_Line.ex)
                {
                    start_X = temp_Line.ex;
                    end_X = temp_Line.sx;
                    
                    start_Y = temp_Line.ey;
                    end_Y = temp_Line.sy;
                }

                if(start_Y > end_Y)
                {
                    int j = start_Y;
                    for(int i = start_X; i < end_X + 1; ++i)
                    {
                        ++hydro_Vent.vent_Grid[j * hydro_Vent.max_Size + i];
                        --j;
                    }
                }
                else
                {
                    int j = start_Y;
                    for(int i = start_X; i < end_X + 1; ++i)
                    {
                        ++hydro_Vent.vent_Grid[j * hydro_Vent.max_Size + i];
                        ++j;
                    }
                }
            }

            //PrintGrid(&hydro_Vent);
        }

        fclose(day5_File);

        //PrintGrid(&hydro_Vent);
        result2 = OverlapPoints(&hydro_Vent);
    }

    ASSERT(result1 == 5147);
    printf("The ninth star answer is - %d\n", result1);
    ASSERT(result2 == 16925);
    printf("The tenth star answer is - %d\n", result2);
}
