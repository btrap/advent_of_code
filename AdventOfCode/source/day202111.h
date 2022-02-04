#pragma once

struct Dumbo_Octopi
{
    int *octopi;

    int siblings[100][8];
    int sibling_Count[100];

    int flashes;

    int length;
    int height;
};

void SetupOctopi(Dumbo_Octopi * octos)
{
    int pos = 0;
    int new_Pos = 0;
    int step = 0;
    int max = 0;
    for(int j = 0; j < octos->height; ++j)
    {
        for(int i = 0; i < octos->length; ++i)
        {
            max = octos->height * octos->length;
            step = j * octos->length;
            pos = i + step;
            octos->octopi[pos] = 10;
            octos->sibling_Count[pos] = 0;
            octos->flashes = 0;

            new_Pos = pos + 1;
            if((new_Pos < max) && (i + 1 < octos->length))
            {
                octos->siblings[pos][octos->sibling_Count[pos]] = new_Pos;
                ++octos->sibling_Count[pos];
                printf("%d, ", new_Pos);
            }
        
            new_Pos = pos - 1;
            if(new_Pos >= 0 && (i - 1 >= 0))
            {
                octos->siblings[pos][octos->sibling_Count[pos]] = new_Pos;
                ++octos->sibling_Count[pos];
                printf("%d, ", new_Pos);
            }

            int upperRow = pos + octos->length;
            new_Pos = upperRow;
            if(new_Pos < max)
            {
                octos->siblings[pos][octos->sibling_Count[pos]] = new_Pos;
                ++octos->sibling_Count[pos];
                printf("%d, ", new_Pos);
            }

            new_Pos = upperRow + 1;
            if(new_Pos < max && (i + 1 < octos->length))
            {
                octos->siblings[pos][octos->sibling_Count[pos]] = new_Pos;
                ++octos->sibling_Count[pos];
                printf("%d, ", new_Pos);
            }
            new_Pos = upperRow - 1;
            if(new_Pos < max && (i - 1 >= 0))
            {
                octos->siblings[pos][octos->sibling_Count[pos]] = new_Pos;
                ++octos->sibling_Count[pos];
                printf("%d, ", new_Pos);
            }

            int lowerRow = pos - octos->length;
            new_Pos = lowerRow;
            if(new_Pos >= 0)
            {
                octos->siblings[pos][octos->sibling_Count[pos]] = new_Pos;
                ++octos->sibling_Count[pos];
                printf("%d, ", new_Pos);
            }

            new_Pos = lowerRow + 1;
            if(new_Pos >= 0 && (i + 1 < octos->length))
            {
                octos->siblings[pos][octos->sibling_Count[pos]] = new_Pos;
                ++octos->sibling_Count[pos];
                printf("%d, ", new_Pos);
            }
            new_Pos = lowerRow - 1;
            if(new_Pos >= 0 && (i - 1 >= 0))
            {
                octos->siblings[pos][octos->sibling_Count[pos]] = new_Pos;
                ++octos->sibling_Count[pos];
                printf("%d, ", new_Pos);
            }
                printf("\n");
        }
    }
}

void PrintOctopi(Dumbo_Octopi *octos)
{
    int pos = 0;
    for(int j = 0; j < octos->height; ++j)
    {
        for(int i = 0; i < octos->length; ++i)
        {
            pos = i + j * octos->length;
            printf("%d", octos->octopi[pos]);
        }
        printf("\n");
    }
        printf("\n");
}

void LightUpOctopiSiblings(Dumbo_Octopi *octos, int pos)
{
    if(octos->octopi[pos] > 9)
    {
        ++octos->flashes;
        octos->octopi[pos] = 0;
                //printf("pos - %d, \n", pos);
        for(int i = 0; i < octos->sibling_Count[pos]; ++i)
        {
            if(octos->octopi[octos->siblings[pos][i]] > 0)
            {
                ++octos->octopi[octos->siblings[pos][i]];
                LightUpOctopiSiblings(octos, octos->siblings[pos][i]);
;                //printf("child - %d, ", octos->siblings[pos][i]);
            }
                //printf("\n");
        }
        //PrintOctopi(octos);
    }
}

int StepOctopi(Dumbo_Octopi *octos)
{
    int pos = 0;
    for(int j = 0; j < octos->height; ++j)
    {
        for(int i = 0; i < octos->length; ++i)
        {
            pos = i + j * octos->length;
            ++octos->octopi[pos];
        }
    }
    //PrintOctopi(octos);

    int old_Flash = octos->flashes;
    for(int j = 0; j < octos->height; ++j)
    {
        for(int i = 0; i < octos->length; ++i)
        {
            pos = i + j * octos->length;
            LightUpOctopiSiblings(octos, pos);
        }
    }

    return octos->flashes - old_Flash;
}

void Advent_Of_Code_2021_11()
{
    int result1 = 0;
    int result2 = 0;

    FILE *day11_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day11_input.txt", "r");
    if(day11_File)
    {
        int length = 0;
        int height = 0;
        char value = 0;
        // Get length
        while(fscanf(day11_File, "%c", &value) != EOF)
        {
            if(value == '\n')
            {
                ++height;
                break;
            }
            ++length;
        }
        // Get height
        while(fscanf(day11_File, "%c", &value) != EOF)
        {
            if(value == '\n')
            {
                ++height;
            }
        }

        fseek(day11_File, 0, SEEK_SET);

        Dumbo_Octopi octopi_Grid = {};
        octopi_Grid.length = length;
        octopi_Grid.height = height;
        STORE_PERM_DATA(octopi_Grid.octopi, length * height);
        //STORE_PERM_DATA(octopi_Grid.light_Up, length * height);
        SetupOctopi(&octopi_Grid);
        
        int pos = 0;
        for(int j = 0; j < octopi_Grid.height; ++j)
        {
            for(int i = 0; i < octopi_Grid.length; ++i)
            {
                fscanf(day11_File, "%c", &value);
                pos = i + j * octopi_Grid.length;
                octopi_Grid.octopi[pos] = value - '0';
                //octopi_Grid.light_Up[pos] = false;
            }
            fscanf(day11_File, "%c", &value);
        }
        fclose(day11_File);

        //PrintOctopi(&octopi_Grid);

        for(int i = 0; i < 100; ++i)
        {
            StepOctopi(&octopi_Grid);
            //PrintOctopi(&octopi_Grid);
        }
        result1 = octopi_Grid.flashes;
 
        int new_Flashes = 0;
        int step_Count = 100;
        while(new_Flashes < 100)
        {
            new_Flashes = StepOctopi(&octopi_Grid);
            ++step_Count;
        }
        PrintOctopi(&octopi_Grid);
    }

    ASSERT(result1 == 1793);
    printf("The twenty first star answer is - %d\n", result1);
    ASSERT(result2 == 247);
    printf("The twenty second star answer is - %d\n", result2);
}
