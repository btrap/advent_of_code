#pragma once

struct Pair_Insert
{
    char testL;
    char testR;

    char value;

    umax count;

    int nextL;
    int nextR;
};

void PrintInsertNodes(Pair_Insert *pair_Insert, int pair_Insert_Count)
{
    for(int i = 0;i < pair_Insert_Count; ++i)
    {
        printf("value left = %c ", pair_Insert[i].testL);
        printf("value right = %c ", pair_Insert[i].testR);
        printf("value = %c ", pair_Insert[i].value);
        printf("count = %d ", pair_Insert[i].count);
        printf("left = %d ", pair_Insert[i].nextL);
        printf("right = %d \n", pair_Insert[i].nextR);
    }
    printf("\n");
}

void SetupGraph(Pair_Insert *pair_Insert, int pair_Insert_Count)
{
    for(int i = 0; i < pair_Insert_Count; ++i)
    {
        for(int j = 0; j < pair_Insert_Count; ++j)
        {
            if(pair_Insert[i].testL == pair_Insert[j].testL && pair_Insert[i].value == pair_Insert[j].testR)
            {
                pair_Insert[i].nextL = j;
            }

            if(pair_Insert[i].value == pair_Insert[j].testL && pair_Insert[i].testR == pair_Insert[j].testR)
            {
                pair_Insert[i].nextR = j;
            }
        }
    }
}

void InsertPairInsertNode(Pair_Insert *pair_Insert, int pos, umax *char_Counts, int step)
{
    if(step < 1)
        return;

    ++char_Counts[pair_Insert[pos].value - 'A'];

    InsertPairInsertNode(pair_Insert, pair_Insert[pos].nextL, char_Counts, step - 1);
    InsertPairInsertNode(pair_Insert, pair_Insert[pos].nextR, char_Counts, step - 1);
}

//void InsertPairInsertNode(Pair_Insert *pair_Insert, int pos, umax *char_Counts, int step)
//{
//    if(step < 0)
//        return;
// 
//    if(pair_Insert[pos].triggered > 0)
//    {
//        int diff = 0;
//        for(int i = 0; i < pair_Insert[pos].char_Counts_Count; ++i)
//        {
//            diff = pair_Insert[pos].triggered - step;
//            while(diff > step)
//            {
//                pair_Insert[pos].char_Counts[i] *= 2;
//                step - 
//            }
//
//            if(diff > 0)
//        }
//
//        return;
//    }
//
//    pair_Insert[pos].triggered = step;
//    ++pair_Insert[pos].char_Counts[pair_Insert[pos].value - 'A'];
//
//    InsertPairInsertNode(pair_Insert, pair_Insert[pos].nextL, char_Counts, step - 1);
//    InsertPairInsertNode(pair_Insert, pair_Insert[pos].nextR, char_Counts, step - 1);
//}

void Advent_Of_Code_2021_14()
{
    umax result1 = 0;
    umax result2 = 0;

    //FILE *day14_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day14_test_input.txt", "r");
    FILE *day14_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day14_input.txt", "r");
    if(day14_File)
    {
        Pair_Insert temp_Insert = {};
        int pair_Insert_Count = 0;

        int polymer_Template_Length = 0;
        char polymer_Template[32];
        fscanf(day14_File, "%s\n", polymer_Template);
        while(fscanf(day14_File, "%c%c -> %c\n", &temp_Insert.testL, &temp_Insert.testR, &temp_Insert.value) != EOF)
        {
            ++pair_Insert_Count;
        }
        fseek(day14_File, 0, SEEK_SET);

        int char_Counts_Count = 'Z' - 'A';
        umax char_Counts['Z'-'A'];
        for(int i = 0; i < char_Counts_Count; ++i)
        {
            char_Counts[i] = 0;
        }

        Pair_Insert *pair_Inserts;
        STORE_TEMP_DATA(pair_Inserts, pair_Insert_Count);
        fscanf(day14_File, "%s\n", polymer_Template);
        polymer_Template_Length = StringLength(polymer_Template);
        for(int i = 0; i < pair_Insert_Count; ++i)
        {
            fscanf(day14_File, "%c%c -> %c\n", &pair_Inserts[i].testL, &pair_Inserts[i].testR, &pair_Inserts[i].value);
            pair_Inserts[i].count = 0;
        }
        PrintInsertNodes(pair_Inserts, pair_Insert_Count);

        fclose(day14_File);

        SetupGraph(pair_Inserts, pair_Insert_Count);
        PrintInsertNodes(pair_Inserts, pair_Insert_Count);
        
        for(int i = 0; i < polymer_Template_Length; ++i)
        {
            ++char_Counts[polymer_Template[i] - 'A'];
        }

        for(int i = 0; i < char_Counts_Count; ++i)
        {
            if(char_Counts[i] > 0)
                printf("%c = %d ", 'A' + i, char_Counts[i]);
        }
        printf("\n");
        
        int step_Count = 40; // 9 // 39 // 4
        //for(int i = 0; i < polymer_Template_Length-1; ++i)
        //{
        //    for(int j = 0; j < pair_Insert_Count; ++j)
        //    {
        //        if(pair_Inserts[j].testL == polymer_Template[i] && pair_Inserts[j].testR == polymer_Template[i+1])
        //        {
        //            InsertPairInsertNode(pair_Inserts, j, char_Counts, step_Count);
        //        }
        //    }
        //}

        for(int i = 0; i < char_Counts_Count; ++i)
        {
            if(char_Counts[i] > 0)
                printf("%c = %d ", 'A' + i, char_Counts[i]);
        }
        printf("\n");

        umax storage[128] = {};
        for(int i = 0; i < polymer_Template_Length; ++i)
        {
            for(int j = 0; j < pair_Insert_Count; ++j)
            {
                if(pair_Inserts[j].testL == polymer_Template[i] && pair_Inserts[j].testR == polymer_Template[i+1])
                {
                    ++pair_Inserts[j].count;
                }
            }
        }

        for(int i = 0; i < step_Count; ++i)
        {
            for(int j = 0; j < pair_Insert_Count; ++j)
            {
                storage[pair_Inserts[j].nextL] += pair_Inserts[j].count;
                storage[pair_Inserts[j].nextR] += pair_Inserts[j].count;
                char_Counts[pair_Inserts[j].value - 'A'] += pair_Inserts[j].count;
            }
            for(int j = 0; j < pair_Insert_Count; ++j)
            {
                pair_Inserts[j].count = storage[j];
                storage[j] = 0;
            }
        }
        PrintInsertNodes(pair_Inserts, pair_Insert_Count);

        //for(int i = 0; i < pair_Insert_Count; ++i)
        //{
        //    char_Counts[pair_Inserts[i].value - 'A'] += pair_Inserts[i].count;
        //}


        for(int i = 0; i < char_Counts_Count; ++i)
        {
            if(char_Counts[i] > 0)
                printf("%c = %d ", 'A' + i, char_Counts[i]);
        }
        printf("\n");

        umax max_Char = 0;
        umax min_Char = -1;
        for(int i = 0; i < char_Counts_Count; ++i)
        {
            if(char_Counts[i] == 0)
                continue;

            if(char_Counts[i] > max_Char)
            {
                max_Char = char_Counts[i];
            }

            if(char_Counts[i] < min_Char)
            {
                min_Char = char_Counts[i];
            }
        }
        result1 = max_Char - min_Char;
        printf("%llu - %llu = %llu", max_Char, min_Char, result1);
        printf("%llu", result1);
    }

    //ASSERT(result1 == 3906);
    printf("The twenty first star answer is - %d\n", result1);
    //ASSERT(result2 == 4441317262452);
    printf("The twenty second star answer is - %d\n", result2);
}
