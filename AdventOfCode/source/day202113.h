#pragma once

struct Transparent_Paper
{
    char *grid;
    int length;
    int height;

    int *x_Folds;
    int x_Folds_Count;
    int *y_Folds;
    int y_Folds_Count;
};

void PrintTransparentPaper(Transparent_Paper * trans_Paper)
{
    for(int j = 0; j < trans_Paper->height; ++j)
    {
        for(int i = 0; i < trans_Paper->length; ++i)
        {
            printf("%c", trans_Paper->grid[j * trans_Paper->length + i]);
        }
        printf("\n");
    }
    printf("\n");
}

int CountTransparentPaperDots(Transparent_Paper * trans_Paper)
{
    int result = 0;
    for(int j = 0; j < trans_Paper->height; ++j)
    {
        for(int i = 0; i < trans_Paper->length; ++i)
        {
            if(trans_Paper->grid[j * trans_Paper->length + i] == '#')
            {
                ++result;
            }
        }
    }
    return result;
}

void FoldTransparentPaper(Transparent_Paper * trans_Paper, int x, int y)
{
    if(x > 0)
    {
        int right_Pos = 0;
        int new_Length = x * 2 + 1;
        for(int j = 0; j < trans_Paper->height; ++j)
        {
            for(int i = 0; i < new_Length / 2; ++i)
            {
                right_Pos = new_Length - 1 - i;
                if(trans_Paper->grid[j * trans_Paper->length + i] == '.')
                    trans_Paper->grid[j * trans_Paper->length + i] = trans_Paper->grid[j * trans_Paper->length + right_Pos];
            }
            //PrintTransparentPaper(trans_Paper);
        }
        //PrintTransparentPaper(trans_Paper);

        int next_Pos = 0;
        for(int j = 0; j < trans_Paper->height; ++j)
        {
            for(int i = 0; i < trans_Paper->length / 2; ++i)
            {
                trans_Paper->grid[next_Pos] = trans_Paper->grid[j * trans_Paper->length + i];
                ++next_Pos;
            }
            //PrintTransparentPaper(trans_Paper);
        }
        //PrintTransparentPaper(trans_Paper);

        trans_Paper->length -= x + 1;
        //PrintTransparentPaper(trans_Paper);
    }

    if(y > 0)
    {
        int top_Pos = 0;
        int new_Height = y * 2 + 1;
        for(int j = 0; j < new_Height / 2; ++j)
        {
            top_Pos = new_Height - 1 - j;
            for(int i = 0; i < trans_Paper->length; ++i)
            {
                if(trans_Paper->grid[j * trans_Paper->length + i] == '.')
                    trans_Paper->grid[j * trans_Paper->length + i] = trans_Paper->grid[top_Pos * trans_Paper->length + i];
            }
        }

        trans_Paper->height -= y;
    }
}

void Advent_Of_Code_2021_13()
{
    int result1 = 0;
    int result2 = 0;
    
    //FILE *day13_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day13_test_input.txt", "r");
    FILE *day13_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day13_input.txt", "r");
    int read_X = 0;
    int read_Y = 0;
    int point_Count = 0;
    int max_X = 0;
    int max_Y = 0;
    char xy_Char = 0;
    int xy_Value = 0;
    int x_Fold_Count = 0;
    int y_Fold_Count = 0;
    if(day13_File)
    {
        char file_Line[32];
        while(fscanf(day13_File, "%s", file_Line) != EOF)
        {
            if(file_Line[0] == 'f')
            {
                fscanf(day13_File, "%s", file_Line);
                fscanf(day13_File, "%s", file_Line);
                sscanf(file_Line, " %c=%d\n", &xy_Char, &xy_Value);
                if(xy_Char == 'x')
                {
                    ++x_Fold_Count;
                }

                if(xy_Char == 'y')
                {
                    ++y_Fold_Count;
                }
            }
            else if(file_Line[0] != '\n')
            {
                sscanf(file_Line, "%d,%d\n", &read_X, &read_Y);
                ++point_Count;
                if(read_X > max_X)
                    max_X = read_X;
                if(read_Y > max_Y)
                    max_Y = read_Y;
            }
        }
        ++max_X;
        ++max_Y;

        fseek(day13_File, 0, SEEK_SET);
        Transparent_Paper trans_Paper = {};
        STORE_PERM_DATA(trans_Paper.grid, max_X * max_Y);
        STORE_PERM_DATA(trans_Paper.x_Folds, x_Fold_Count);
        STORE_PERM_DATA(trans_Paper.y_Folds, y_Fold_Count);
        trans_Paper.length = max_X;
        trans_Paper.height = max_Y;
        
        for(int j = 0; j < trans_Paper.height; ++j)
        {
            for(int i = 0; i < trans_Paper.length; ++i)
            {
                trans_Paper.grid[j * trans_Paper.length + i] = '.';
            }
        }
        //PrintTransparentPaper(&trans_Paper);

        int folds = 0;
        while(fscanf(day13_File, "%s", file_Line) != EOF)
        {
            if(file_Line[0] == 'f')
            {
                fscanf(day13_File, "%s", file_Line);
                fscanf(day13_File, "%s", file_Line);
                sscanf(file_Line, " %c=%d\n", &xy_Char, &xy_Value);

                if(xy_Char == 'x')
                {
                    //for(int i = 0; i < trans_Paper.height; ++i)
                    //{
                    //    trans_Paper.grid[i * trans_Paper.length + xy_Value] = '-';
                    //}
                    FoldTransparentPaper(&trans_Paper, xy_Value, 0);
                    //PrintTransparentPaper(&trans_Paper);

                    trans_Paper.x_Folds[trans_Paper.x_Folds_Count] = xy_Value;
                    ++trans_Paper.x_Folds_Count;
                }

                if(xy_Char == 'y')
                {
                    //for(int i = 0; i < trans_Paper.length; ++i)
                    //{
                    //    trans_Paper.grid[xy_Value * trans_Paper.length + i] = '-';
                    //}
                    FoldTransparentPaper(&trans_Paper, 0, xy_Value);
                    //PrintTransparentPaper(&trans_Paper);

                    trans_Paper.y_Folds[trans_Paper.y_Folds_Count] = xy_Value;
                    ++trans_Paper.y_Folds_Count;
                }

                ++folds;

                if(folds == 1)
                {
                    result1 = CountTransparentPaperDots(&trans_Paper);
                }

                if(folds > 4)
                {
                    PrintTransparentPaper(&trans_Paper);
                }
            }
            else if(file_Line[0] != '\n')
            {
                sscanf(file_Line, "%d,%d\n", &read_X, &read_Y);
                trans_Paper.grid[read_Y * trans_Paper.length + read_X] = '#';
            }
        }
        PrintTransparentPaper(&trans_Paper);

        fclose(day13_File);
    }

    ASSERT(result1 == 837);
    printf("The twenty first star answer is - %d\n", result1);
    //ASSERT(result2 == 247); // EPZGKCHU
    printf("The twenty second star answer is - %d\n", result2);
}

