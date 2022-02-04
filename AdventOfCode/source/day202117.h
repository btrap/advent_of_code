#pragma once

int SumTorial(int value)
{
    int result = value;
    for(int i = 1; i < value; ++i)
    {
        result += i;
    }
    return result;
}

int GetXVelocity(int value)
{
    int result = 0;
    for(result = 1; value > 1; ++result)
    {
        value -= result;
    }
    --result;

    if(!value)
        return result;

    return -1;
}

int GetYVelocity(int value)
{
    int result = 0;
    for(result = 1; value > 1; ++result)
    {
        value -= result;
    }
    --result;

    if(!value)
        return result;

    return -1;
}

struct Trench_Point
{
    int x;
    int y;
};

void PrintTrenchPoints(Trench_Point *trench_Point)
{
    printf("Point(%d, %d)\n", trench_Point->x, trench_Point->y);
}

void PrintTrenchPoints(int x, int y)
{
    printf("Point(%d, %d)\n", x, y);
}

void Advent_Of_Code_2021_17()
{
    int result1 = 0;
    int result2 = 0;

    FILE *day17_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day17_input.txt", "r");
    if(day17_File)
    {
        //Trench_Point target_Area_Start = {195, -67};
        //Trench_Point target_Area_End = {238, -93};

        //while(fscanf(day17_File, "target area: x=%d..%d, y=%d..%d", &target_Area_Start.x, &target_Area_Start.y, &target_Area_End.x, &target_Area_End.y) != EOF)
        //{
        //}
        fclose(day17_File);
        
        Trench_Point target_Area_Start = {20, -5};
        Trench_Point target_Area_End = {30, -10};

        Trench_Point probe = {0, 0};

        Trench_Point init_Velocity = {6, 9};
        Trench_Point velocity = {0, 0};
        velocity.x = init_Velocity.x;
        velocity.y = init_Velocity.y;

        Trench_Point hit_Point = { 0,0 };

        int valid_Velocity = 0;
        int height = 0;

        int x_Velocity = 0;
        int neg_Velocity = 0;
        int y_Test = 0;
        for(int x = target_Area_Start.x; x <= target_Area_End.x; ++x)
        {
            x_Velocity = GetXVelocity(x);
            if(x_Velocity == -1)
                continue;

            y_Test = -11;
            for(int y_Velocity = -target_Area_End.y; y_Velocity > 0; --y_Velocity)
            {
                if(y_Velocity > 0)
                {
                    neg_Velocity = -y_Velocity;
                }

                for(int y = 0; y >= target_Area_End.y; y += neg_Velocity)
                {
                    if(y <= target_Area_Start.y && y_Test < y)
                    {
                        y_Test = y;
                        PrintTrenchPoints(x, y);
                    }
                }
            }

            //for(int y_Velocity = 1; y_Velocity <= (-target_Area_End.y); ++y_Velocity)
            //{
            //    for(int y = target_Area_Start.y; y >= target_Area_End.y; y -= y_Velocity)
            //    {
            //        ++valid_Velocity;
            //        height = SumTorial(y_Velocity);
            //        if(result1 < height)
            //            result1 = height;
            //    }
            //}
        }
        printf("Max Height %d\n", result1);
    }

    //ASSERT(result1 == 000);
    printf("The twenty first star answer is - %d\n", result1);
    //ASSERT(result2 == 000);
    printf("The twenty second star answer is - %d\n", result2);
}
