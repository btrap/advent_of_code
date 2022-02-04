#pragma once

// Question:
void Advent_Of_Code_2021_01()
{
    int increased = 0;
    FILE *temp = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day1_input.txt", "r");
    if(temp)
    {
        int ch = 0;
        int lines = 0;
        FILE *walker = temp;
        while((ch = fgetc(walker)) != EOF)
        {
            if(ch == '\n')
                ++lines;
        }
        
        //fclose(temp);
        //temp = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day1_input.txt", "r");

        fseek(temp, 0, SEEK_SET);

        //walker = temp;

        int *depths = 0;
        int testDepth;
        STORE_PERM_DATA(depths, lines);
        for(int i = 0; i < lines; ++i)
        {
            //testDepth = getw(walker);
            //fread(&testDepth, sizeof(testDepth), 1, temp);
            fscanf(walker, "%d", &testDepth);
            depths[i] = testDepth;
        }

        fclose(temp);

        int next = 0;
        int current = depths[0];
        int diff = 0;
        for(int i = 1; i < lines; ++i)
        {
            diff = depths[i] - current;
            if(diff > 0)
            {
                ++increased;
            }
            current = depths[i];
        }
        ASSERT(increased == 1624);
        printf("The first star answer is - %d\n", increased);

        increased = 0;
        for(int i = 0; i < lines - 3; ++i)
        {
            current = depths[i] + depths[i+1] + depths[i+2];
            next = depths[i+1] + depths[i+2] + depths[i+3];
            diff = next - current;
            if(diff > 0)
            {
                ++increased;
            }
            current = depths[i];
        }
        ASSERT(increased == 1653);
        printf("The second star answer is - %d\n", increased);
    }
}
// Answer1: 1624
// Answer2: 1653

