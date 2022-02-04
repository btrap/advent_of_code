#pragma once

struct Lava_Tubes
{
    int *tubes;
    bool *tube_Tested;
    int length;
    int height;
    int step;
    
    int *basins;
    int basin_Count;
};

void SetupLavaTubes(Lava_Tubes *lava_Tubes)
{
    int pos = 0;
    for(int j = 0; j < lava_Tubes->height + 2; ++j)
    {
        for(int i = 0; i < lava_Tubes->length + 2; ++i)
        {
            pos = i + j * lava_Tubes->step;
            lava_Tubes->tubes[pos] = 10;
            lava_Tubes->tube_Tested[pos] = true;
        }
    }
}

void PrintLavaTubes(Lava_Tubes *lava_Tubes)
{
    int pos = 0;
    for(int j = 0; j < lava_Tubes->height + 2; ++j)
    {
        for(int i = 0; i < lava_Tubes->length + 2; ++i)
        {
            pos = i + j * lava_Tubes->step;
            printf("%d", lava_Tubes->tubes[pos]);
        }
        printf("\n");
    }

    for(int j = 0; j < lava_Tubes->height + 2; ++j)
    {
        for(int i = 0; i < lava_Tubes->length + 2; ++i)
        {
            pos = i + j * lava_Tubes->step;
            if(lava_Tubes->tube_Tested[pos])
                printf("1");
            else
                printf("0");
        }
        printf("\n");
    }
}

bool TestLowPoint(Lava_Tubes *lava_Tubes, int pos)
{
    bool result = true;

    int test = lava_Tubes->tubes[pos];
    result &= (test < lava_Tubes->tubes[pos + 1]);
    result &= (test < lava_Tubes->tubes[pos - 1]);
    result &= (test < lava_Tubes->tubes[pos + lava_Tubes->step]);
    result &= (test < lava_Tubes->tubes[pos - lava_Tubes->step]);

    return result;
}

int FindRiskLevel(Lava_Tubes *lava_Tubes)
{
    int low_Points = 0;
    int risk_Level = 0;
    int pos = 0;
    int test = 0;
    for(int j = 1; j < lava_Tubes->height+1; ++j)
    {
        for(int i = 1; i < lava_Tubes->length+1; ++i)
        {
            pos = i + j * lava_Tubes->step;
            test = lava_Tubes->tubes[pos];
            if(TestLowPoint(lava_Tubes, pos))
            {
                printf("%d\n", test);
                risk_Level += test + 1;
                ++low_Points;
            }
        }
    }
    STORE_PERM_DATA(lava_Tubes->basins, low_Points);

    return risk_Level;
}

int GetBasinValue(Lava_Tubes *lava_Tubes, int pos)
{
    if(lava_Tubes->tube_Tested[pos] == true)
        return 0;

    lava_Tubes->tube_Tested[pos] = true;
    int result = 1;

    if(lava_Tubes->tubes[pos + 1] < 9)
    {
        result += GetBasinValue(lava_Tubes, pos + 1);
    }
    if(lava_Tubes->tubes[pos - 1] < 9)
    {
        result += GetBasinValue(lava_Tubes, pos - 1);
    }
    if(lava_Tubes->tubes[pos + lava_Tubes->step] < 9)
    {
        result += GetBasinValue(lava_Tubes, pos + lava_Tubes->step);
    }
    if(lava_Tubes->tubes[pos - lava_Tubes->step] < 9)
    {
        result += GetBasinValue(lava_Tubes, pos - lava_Tubes->step);
    }

    return result;
}

int FindBasins(Lava_Tubes *lava_Tubes)
{
    int pos = 0;
    int test = 0;
    int new_Basin = 0;
    for(int j = 1; j < lava_Tubes->height+1; ++j)
    {
        for(int i = 1; i < lava_Tubes->length+1; ++i)
        {
            pos = i + j * lava_Tubes->step;
            test = lava_Tubes->tubes[pos];
            if(TestLowPoint(lava_Tubes, pos))
            {
                new_Basin = GetBasinValue(lava_Tubes, pos);
                printf("%d\n", new_Basin);
                lava_Tubes->basins[lava_Tubes->basin_Count] = new_Basin;
                ++lava_Tubes->basin_Count;
            }
        }
    }

    int result = 1;
    int largest = 0;
    int largest_Index = 0;
    for(int j = 0; j < 3; ++j)
    {
        largest = lava_Tubes->basins[0];
        for(int i = 1; i < lava_Tubes->basin_Count; ++i)
        {
            if(lava_Tubes->basins[i] > largest)
            {
                largest_Index = i;
                largest = lava_Tubes->basins[i];
            }
        }
        lava_Tubes->basins[largest_Index] = 0;
        result *= largest;
    }

    return result;
}

void Advent_Of_Code_2021_09()
{
    int result1 = 0;
    int result2 = 0;

    FILE *day9_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day9_input.txt", "r");
    if(day9_File)
    {
        int length = 0;
        int height = 0;
        char value = 0;
        // Get length
        while(fscanf(day9_File, "%c", &value) != EOF)
        {
            if(value == '\n')
            {
                ++height;
                break;
            }
            ++length;
        }
        // Get height
        while(fscanf(day9_File, "%c", &value) != EOF)
        {
            if(value == '\n')
            {
                ++height;
            }
        }

        fseek(day9_File, 0, SEEK_SET);

        Lava_Tubes lava_Tubes = {};
        lava_Tubes.length = length;
        lava_Tubes.height = height;
        length += 2;
        height += 2;
        lava_Tubes.step = length;
        STORE_PERM_DATA(lava_Tubes.tubes, length * height);
        STORE_PERM_DATA(lava_Tubes.tube_Tested, length * height);
        SetupLavaTubes(&lava_Tubes);
        
        int pos = 0;
        for(int j = 1; j < lava_Tubes.height+1; ++j)
        {
            for(int i = 1; i < lava_Tubes.length+1; ++i)
            {
                fscanf(day9_File, "%c", &value);
                pos = i + j * lava_Tubes.step;
                lava_Tubes.tubes[pos] = value - '0';
                lava_Tubes.tube_Tested[pos] = false;
                //printf("%d", lava_Tubes.tubes[pos]);
            }
            fscanf(day9_File, "%c", &value);
            //printf("\n");
        }
        fclose(day9_File);

        PrintLavaTubes(&lava_Tubes);
        result1 = FindRiskLevel(&lava_Tubes);
        result2 = FindBasins(&lava_Tubes);
    }

    ASSERT(result1 == 532);
    printf("The seventheth star answer is - %d\n", result1);
    ASSERT(result2 == 1110780);
    printf("The eightenth star answer is - %d\n", result2);
}
