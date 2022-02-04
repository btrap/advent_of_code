#pragma once

struct SnailFish_Pair;
struct SnailFish_Pair
{
    int x;
    int y;

    SnailFish_Pair *x_Child;
    SnailFish_Pair *y_Child;
};

struct SnailFish_Tree
{
    SnailFish_Pair *snailFish_Pairs;
};

void PrintSnailFishNumber(SnailFish_Pair * snailFish_Pair_Tree)
{
    printf("[");
    if(snailFish_Pair_Tree->x == -1)
    {
        PrintSnailFishNumber(snailFish_Pair_Tree->x_Child);
    }
    else
    {
        printf("%d", snailFish_Pair_Tree->x);
    }
    printf(",");
    if(snailFish_Pair_Tree->y == -1)
    {
        PrintSnailFishNumber(snailFish_Pair_Tree->y_Child);
    }
    else
    {
        printf("%d", snailFish_Pair_Tree->y);
    }
    printf("]");
}

int SetupTree(SnailFish_Pair *snailFish_Pairs, char *buff, int pos)
{
    if(buff[pos] == '[')
    {
        snailFish_Pairs->x = -1;
        STORE_PERM_DATA(snailFish_Pairs->x_Child, 1);
        pos = SetupTree(snailFish_Pairs->x_Child, buff, pos + 1);
    }
    else
    {
        snailFish_Pairs->x = buff[pos] - '0';
        ++pos;
    }

    ASSERT(buff[pos] == ',');
    ++pos;

    if(buff[pos] == '[')
    {
        snailFish_Pairs->y = -1;
        STORE_PERM_DATA(snailFish_Pairs->y_Child, 1);
        pos = SetupTree(snailFish_Pairs->y_Child, buff, pos + 1);
    }
    else
    {
        snailFish_Pairs->y = buff[pos] - '0';
        ++pos;
    }

    ASSERT(buff[pos] == ']');
    ++pos;

    return pos;
}

void NextLeft(SnailFish_Pair *snailFish_Pairs, SnailFish_Pair *test, SnailFish_Pair** next_Left, bool* next, bool* found)
{
    if(*found)
    {
        return;
    }

    if(snailFish_Pairs == test)
    {
        *next = true;
        //if(snailFish_Pairs->x == -1)
        //{
        //    *next_Left = snailFish_Pairs;
        //    *found = true;
        //}
        return;
    }
    
    if(snailFish_Pairs->y == -1)
    {
        //printf("y child, ");
        NextLeft(snailFish_Pairs->y_Child, test, next_Left, next, found);
    }
    else
    {
        //printf(" (%d) ", snailFish_Pairs->y);
        if(*next)
        {
            //printf("Next LEFT  (%d) ", snailFish_Pairs->y);
            *next_Left = snailFish_Pairs;
            *found = true;
            return;
        }
    }

    if(snailFish_Pairs->x == -1)
    {
        //printf("x child, ");
        NextLeft(snailFish_Pairs->x_Child, test, next_Left, next, found);
    }
    else
    {
        //printf(" (%d) ", snailFish_Pairs->x);
        if(*next)
        {
            //printf("Next LEFT (%d) ", snailFish_Pairs->x);
            *next_Left = snailFish_Pairs;
            *found = true;
            return;
        }
    }
}

void NextRight(SnailFish_Pair *snailFish_Pairs, SnailFish_Pair *test, SnailFish_Pair** next_Right, bool* next, bool* found)
{
    if(*found)
    {
        return;
    }

    if(snailFish_Pairs == test)
    {
        *next = true;
        //if(snailFish_Pairs->y == -1)
        //{
        //    *next_Right = snailFish_Pairs;
        //    *found = true;
        //}
        return;
    }

    if(snailFish_Pairs->x == -1)
    {
        //printf("x child, ");
        NextRight(snailFish_Pairs->x_Child, test, next_Right, next, found);
    }
    else
    {
        //printf(" (%d) ", snailFish_Pairs->x);
        if(*next)
        {
            //printf("Next Right (%d) ", snailFish_Pairs->x);
            *next_Right = snailFish_Pairs;
            *found = true;
        }
    }

    if(snailFish_Pairs->y == -1)
    {
        //printf("y child, ");
        NextRight(snailFish_Pairs->y_Child, test, next_Right, next, found);
    }
    else
    {
        //printf(" (%d) ", snailFish_Pairs->y);
        if(*next)
        {
            //printf("Next Right (%d) ", snailFish_Pairs->y);
            *next_Right = snailFish_Pairs;
            *found = true;
        }
    }
}


int ExplodeNumber(SnailFish_Pair *snailFish_Pairs, int depth, SnailFish_Pair *root)
{
    int result = 0;

    if(depth < 3)
    {
        if(snailFish_Pairs->x == -1)
        {
            result += ExplodeNumber(snailFish_Pairs->x_Child, depth + 1, root);
        }
        if(snailFish_Pairs->y == -1)
        {
            result += ExplodeNumber(snailFish_Pairs->y_Child, depth + 1, root);
        }
    }

    if(depth == 3)
    {
        if(snailFish_Pairs->x == -1)
        {
            ++result;

            SnailFish_Pair *next_Left = 0;
            bool next = false;
            bool found = false;
            NextLeft(root, snailFish_Pairs->x_Child, &next_Left, &next, &found);
            if(found)
            {
                if(next_Left->y != -1)
                {
                    next_Left->y += snailFish_Pairs->x_Child->x;
                }
                else
                {
                    next_Left->x += snailFish_Pairs->x_Child->x;
                }
            }

            next_Left = 0;
            next = false;
            found = false;
            NextRight(root, snailFish_Pairs->x_Child, &next_Left, &next, &found);
            if(found)
            {
                if(next_Left->x != -1)
                {
                    next_Left->x += snailFish_Pairs->x_Child->y;
                }
                else
                {
                    next_Left->y += snailFish_Pairs->x_Child->y;
                }
            }

            snailFish_Pairs->x = 0;
        }
        else if(snailFish_Pairs->y_Child)
        {
            snailFish_Pairs->x += snailFish_Pairs->y_Child->x;
        }

        if(snailFish_Pairs->y == -1)
        {
            ++result;
            SnailFish_Pair *next_Right = 0;
            bool next = false;
            bool found = false;
            NextRight(root, snailFish_Pairs->y_Child, &next_Right, &next, &found);
            if(found)
            {
                if(next_Right->x != -1)
                {
                    next_Right->x += snailFish_Pairs->y_Child->y;
                }
                else
                {
                    next_Right->y += snailFish_Pairs->y_Child->y;
                }
            }

            next_Right = 0;
            next = false;
            found = false;
            NextLeft(root, snailFish_Pairs->y_Child, &next_Right, &next, &found);
            if(found)
            {
                if(next_Right->y != -1)
                {
                    next_Right->y += snailFish_Pairs->y_Child->x;
                }
                else
                {
                    next_Right->x += snailFish_Pairs->y_Child->x;
                }
            }

            snailFish_Pairs->y = 0;
        }
        else if(snailFish_Pairs->x_Child)
        {
            snailFish_Pairs->y += snailFish_Pairs->x_Child->y;
        }

        snailFish_Pairs->x_Child = 0;
        snailFish_Pairs->y_Child = 0;
        PrintSnailFishNumber(root);
        printf("\n");
    }

    return result;
}

int SplitNumbers(SnailFish_Pair *snailFish_Pairs)
{
    bool split = false;
    if(snailFish_Pairs->x == -1)
    {
        split += SplitNumbers(snailFish_Pairs->x_Child);
    }
    else
    {
        if(snailFish_Pairs->x > 10)
        {
            ++split;
            STORE_PERM_DATA(snailFish_Pairs->x_Child, 1);
            snailFish_Pairs->x_Child->x = snailFish_Pairs->x / 2;
            snailFish_Pairs->x_Child->x_Child = 0;
            snailFish_Pairs->x_Child->y = snailFish_Pairs->x - snailFish_Pairs->x_Child->x;
            snailFish_Pairs->x_Child->y_Child = 0;
            snailFish_Pairs->x = -1;
        }
    }
    if(snailFish_Pairs->y == -1)
    {
        split += SplitNumbers(snailFish_Pairs->y_Child);
    }
    else
    {
        if(snailFish_Pairs->y > 10)
        {
            ++split;
            STORE_PERM_DATA(snailFish_Pairs->y_Child, 1);
            snailFish_Pairs->y_Child->x = snailFish_Pairs->y / 2;
            snailFish_Pairs->y_Child->x_Child = 0;
            snailFish_Pairs->y_Child->y = snailFish_Pairs->y - snailFish_Pairs->y_Child->x;
            snailFish_Pairs->y_Child->y_Child = 0;
            snailFish_Pairs->y = -1;
        }
    }

    return split;
}

SnailFish_Pair * AddSnailNumbers(SnailFish_Pair *snailFish_PairsA, SnailFish_Pair *snailFish_PairsB)
{
    SnailFish_Pair *snailFish_PairsSum;
    STORE_PERM_DATA(snailFish_PairsSum, 1);

    snailFish_PairsSum->x = -1;
    snailFish_PairsSum->x_Child = snailFish_PairsA;
    snailFish_PairsSum->y = -1;
    snailFish_PairsSum->y_Child = snailFish_PairsB;
    
    SnailFish_Pair *depth_Nodes[3];
    
    PrintSnailFishNumber(snailFish_PairsSum);
    printf("\n");

    int reduce = 0;
    do
    {
        reduce = 0;
        reduce += ExplodeNumber(snailFish_PairsSum, 0, snailFish_PairsSum);
        PrintSnailFishNumber(snailFish_PairsSum);
        printf("\n");

        reduce += SplitNumbers(snailFish_PairsSum);
        PrintSnailFishNumber(snailFish_PairsSum);
        printf("\n");
    } while(reduce);

    return snailFish_PairsSum; 
}

umax GetMagnitude(SnailFish_Pair *snailFish_Pairs)
{
    umax result = 0;

    if(snailFish_Pairs->x == -1)
    {
        result += 3 * GetMagnitude(snailFish_Pairs->x_Child);
    }
    else
    {
        result += 3 * snailFish_Pairs->x;
    }

    if(snailFish_Pairs->y == -1)
    {
        result += 2 * GetMagnitude(snailFish_Pairs->y_Child);
    }
    else
    {
        result += 2 * snailFish_Pairs->y;
    }

    return result;
}

void Advent_Of_Code_2021_18()
{
    int result1 = 0;
    int result2 = 0;

    FILE *day18_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day18_test_input.txt", "r");
    //FILE *day18_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day18_input.txt", "r");
    if(day18_File)
    {
        int rows_To_Add = 0;
        char *buff;
        STORE_TEMP_DATA(buff, 128);
        while(fscanf(day18_File, "%s", buff) != EOF)
        {
            ++rows_To_Add;
        }
        fseek(day18_File, 0, SEEK_SET);
        
        SnailFish_Tree *snailFish_Trees;
        STORE_PERM_DATA(snailFish_Trees, rows_To_Add);
        int max_Pairs = 28;
        for(int i = 0; i < rows_To_Add; ++i)
        {
            STORE_PERM_DATA(snailFish_Trees[i].snailFish_Pairs, 1);

            fscanf(day18_File, "%s", buff);
            //printf("%s\n", buff);

            for(int j = 0; j < max_Pairs; ++j)
            {
                snailFish_Trees[i].snailFish_Pairs[j].x = -1;
                snailFish_Trees[i].snailFish_Pairs[j].y = -1;
                snailFish_Trees[i].snailFish_Pairs[j].x_Child = 0;
                snailFish_Trees[i].snailFish_Pairs[j].y_Child = 0;
            }

            SetupTree(snailFish_Trees[i].snailFish_Pairs, buff, 1);
            //PrintSnailFishNumber(snailFish_Trees[i].snailFish_Pairs);
            //printf("\n");
        }

        fclose(day18_File);
            
        SnailFish_Pair *result = snailFish_Trees[0].snailFish_Pairs;
        for(int i = 1; i < rows_To_Add; ++i)
        {
            result = AddSnailNumbers(result, snailFish_Trees[i].snailFish_Pairs);
        }
        result1 = GetMagnitude(result);
    }

    //ASSERT(result1 == 000);
    printf("The twenty first star answer is - %d\n", result1);
    //ASSERT(result2 == 000);
    printf("The twenty second star answer is - %d\n", result2);
}

