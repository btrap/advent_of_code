#pragma once

struct SevenSegmentDisplay
{
    char display_Set[7];
    char display[7];
    int length = 7;
};

void InitSSD(SevenSegmentDisplay * ssd)
{
    for(int i = 0; i < ssd->length; ++i)
    {
        ssd->display[i] = 'a' + i;
        ssd->display_Set[i] = '.';
    }
}

void SetSSD(SevenSegmentDisplay * ssd, char * ticks)
{
    while(*ticks != 0)
    {
        switch(*ticks)
        {
            case 'a':
            {
                ssd->display_Set[0] = ssd->display[0];
            }break;
            case 'b':
            {
                ssd->display_Set[1] = ssd->display[1];
            }break;
            case 'c':
            {
                ssd->display_Set[2] = ssd->display[2];
            }break;
            case 'd':
            {
                ssd->display_Set[3] = ssd->display[3];
            }break;
            case 'e':
            {
                ssd->display_Set[4] = ssd->display[4];
            }break;
            case 'f':
            {
                ssd->display_Set[5] = ssd->display[5];
            }break;
            case 'g':
            {
                ssd->display_Set[6] = ssd->display[6];
            }break;
        }
        ++ticks;
    }
}

void PrintSSD(SevenSegmentDisplay * ssd)
{
    char value = 0;
    char value_Next = 0;
    for(int i = 0; i < ssd->length; ++i)
    {
        value = ssd->display_Set[i];
        value_Next = ssd->display_Set[(i + 1) % ssd->length];
        switch(i)
        {
            case 0:
            case 3:
            case 6:
            {
                printf(" %c%c%c%c \n", value, value, value, value);
            }break;
            case 1:
            case 4:
            {
                printf("%c    %c\n", value, value_Next);
                printf("%c    %c\n", value, value_Next);
            }break;
        }
    }
}

void PrintSSDPanel(SevenSegmentDisplay * ssd, int digit_Count)
{
    char value = 0;
    char value_Helper = 0;
    for(int i = 0; i < ssd[0].length; ++i)
    {
        for(int j = 0; j < digit_Count; ++j)
        {
            value = ssd[j].display_Set[i];
            switch(i)
            {
                case 0:
                case 3:
                case 6:
                {
                    printf(" %c%c%c%c", value, value, value, value);
                    printf("   ");
                }break;
                case 1:
                case 4:
                {
                    value_Helper = ssd[j].display_Set[i + 1];
                    printf("%c    %c", value, value_Helper);
                    printf("  ");
                }break;
                case 2:
                case 5:
                {
                    value_Helper = ssd[j].display_Set[i - 1];
                    printf("%c    %c", value_Helper, value);
                    printf("  ");
                }break;
            }
        }
        printf("\n");
    }
}

struct TestSDD
{
    char digits[8];
    int set_Digits;
    int digit_Count;
    int final_Value;
};

void PrintTests(TestSDD *tests, int test_Digit_Count)
{
    for(int i = 0; i < test_Digit_Count; ++i)
    {
        printf("%s ", &tests[i].digits);
    }
    printf("\n");
}

void TranslateTest(TestSDD *test, char *translate)
{
    for(int i = 0; i < test->digit_Count; ++i)
    {
        for(int j = 0; j < 7; ++j)
        {
            if(translate[j] == test->digits[i])
            {
                test->digits[i] = 'a' + j;
                printf("%c -> %c\n", translate[j], test->digits[i]);
                break;
            }
        }
    }
}

int TickCount(char *ticks)
{
    int result = 0;
    while(*ticks != 0)
    {
        ++result;
        ++ticks;
    }
    return result;
}

int TicksToValue(char *ticks)
{
    int result = 0;

    int tick_Count = TickCount(ticks);
    if(tick_Count == 7)
        return 8;
    if(tick_Count == 3)
        return 7;
    if(tick_Count == 4)
        return 4;
    if(tick_Count == 2)
        return 1;
    
    if(tick_Count == 6)
    {
        bool is0 = true;
        bool is6 = true;
        bool is9 = true;
        for(int i = 0; i < tick_Count; ++i)
        {
            if(ticks[i] == 'c') // c
            {
                is6 = false;
            }
            if(ticks[i] == 'd') // d
            {
                is0 = false;
            }
            if(ticks[i] == 'e') // e
            {
                is9 = false;
            }
        }

        if(is9)
            return 9;
        if(is6)
            return 6;
        if(is0)
            return 0;
    }

    if(tick_Count == 5)
    {
        bool is2 = true;
        bool is3 = true;
        bool is5 = true;
        for(int i = 0; i < tick_Count; ++i)
        {
            if(ticks[i] == 'b') // b
            {
                    is2 = false;
                    is3 = false;
            }
            if(ticks[i] == 'c') // c
            {
                    is5 = false;
            }
            if(ticks[i] == 'e') // e
            {
                    is3 = false;
                    is5 = false;
            }
            if(ticks[i] == 'f') // f
            {
                    is2 = false;
            }
        }

        if(is2)
            return 2;
        if(is3)
            return 3;
        if(is5)
            return 5;
    }

    return result;
}

void PrintDigits(int set_Digits)
{
    for(int i = 0; i < 7; ++i)
    {
        printf("%d ", (set_Digits >> i) & 1U);
    }
    printf("\n");
}

void SetDigits(TestSDD *final_Output)
{
    final_Output->set_Digits = 0;
    for(int i = 0; i < final_Output->digit_Count; ++i)
    {
        final_Output->set_Digits |= 1UL << (final_Output->digits[i] - 'a');
    }

    printf("%s\n", final_Output->digits);
    PrintDigits(final_Output->set_Digits);
}

int BitsSet(int bit)
{
    int result = 0;

    while(bit)
    {
        if(bit & 1)
            ++result;
        bit >>= 1;
    }
    return result;
}

char GetSetChar(int bitA, int bitB)
{
    int diff = bitA ^ bitB;
    PrintDigits(diff);
    for(int i = 0; i < 7; ++i)
    {
        if((diff >> i) & 1U)
            return 'a' + i;
    }
    return 0;
}

char GetSetChar(int bit)
{
    for(int i = 0; i < 7; ++i)
    {
        if((bit >> i) & 1U)
            return 'a' + i;
    }
    return 0;
}

//acedgfb cdfbe gcdfa fbcad dab cefabd cdfgeb eafb cagedb ab | cdfeb fcadb cdfeb cdbaf
void Advent_Of_Code_2021_08()
{
    int result1 = 0;
    int result2 = 0;

    //FILE *day8_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day8_test_input.txt", "r");
    FILE *day8_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day8_input.txt", "r");
    if(day8_File)
    {
        int test_Count = 0;
        int tick_Count = 0;

        int digit_Count = 8;
        int test_Digit_Count = 10;
        char test_Digit[8];
        while(fscanf(day8_File, "%s,", test_Digit) != EOF)
        {
            while(test_Digit[0] != '|')
            {
                fscanf(day8_File, "%s,", test_Digit);
            }

            for(int i = 0; i < 4; ++i)
            {
                fscanf(day8_File, "%s,", test_Digit);
                tick_Count = TickCount(test_Digit);
                if(tick_Count == 7)
                    ++result1;
                if(tick_Count == 4)
                    ++result1;
                if(tick_Count == 3)
                    ++result1;
                if(tick_Count == 2)
                    ++result1;
            }

            ++test_Count;
        }

        fseek(day8_File, 0, SEEK_SET);
        
        char temp_Digits[8] = {};
        int temp_Count = 0;
        int pos = 0;
        int other = 0;
        for(int test_Index = 0; test_Index < test_Count; ++test_Index)
        {
            other = 0;
            TestSDD *tests = 0;
            STORE_TEMP_DATA(tests, test_Digit_Count);
            
            for(int i = 0; i < test_Digit_Count; ++i)
            {
                fscanf(day8_File, "%s,", &temp_Digits);
                temp_Count = TickCount(temp_Digits);

                if(temp_Count == 2)
                {
                    pos = 0;
                }
                else if(temp_Count == 3)
                {
                    pos = 1;
                }
                else if(temp_Count == 4)
                {
                    pos = 2;
                }
                else if(temp_Count == 7)
                {
                    pos = 3;
                }
                else
                {
                    pos = 4 + other;
                    ++other;
                }

                for(int d = 0; d < temp_Count; ++d)
                {
                    tests[pos].digits[d] = temp_Digits[d];
                }

                tests[pos].digit_Count = temp_Count;
                tests[pos].set_Digits = 0;
                SetDigits(&tests[pos]);
            }
            fscanf(day8_File, "%s,", test_Digit);
            //PrintTests(tests, test_Digit_Count);

            // Make translation table
            char translate[8] = {0};
            char testResult = GetSetChar(tests[0].set_Digits, tests[1].set_Digits);
            translate[0] = testResult; // a
            int mod4 = tests[2].set_Digits ^ tests[0].set_Digits; // bd
            // 7 acf
            
            int e = 0;
            for(int i = 0; i < test_Digit_Count; ++i)
            {
                if(tests[i].digit_Count == 6)
                {
                    int find9 = tests[i].set_Digits ^ tests[1].set_Digits; // acf
                    find9 = find9 ^ mod4; // bd
                    if(BitsSet(find9) == 1)
                    {
                        testResult = GetSetChar(find9);
                        translate[6] = testResult; // g
                        e = tests[3].set_Digits ^ tests[i].set_Digits;
                        testResult = GetSetChar(e);
                        translate[4] = testResult; // e
                        break;
                    }
                }
            }

            for(int i = 0; i < test_Digit_Count; ++i)
            {
                if(tests[i].digit_Count == 5)
                {
                    int findNext = tests[i].set_Digits ^ tests[3].set_Digits; // (bf be) ce
                    if(findNext & mod4) // bd
                    {
                        int b = (findNext & mod4);
                        testResult = GetSetChar(b);
                        translate[1] = testResult; // b
                        testResult = GetSetChar(mod4 ^ b);
                        translate[3] = testResult; // d
                        
                        findNext = findNext ^ b;
                        if(findNext != e)
                        {
                            translate[5] =  GetSetChar(findNext); // f
                        }
                    }
                    else
                    {
                        testResult = GetSetChar(findNext ^ e);
                        translate[2] = testResult; // c
                    }
                }
            }

            TestSDD final_Output[4];
            //SevenSegmentDisplay ssd_Display[4] = {};
            int ssd_Count = 4;
            int screen_Output = 0;
            for(int i = 0; i < ssd_Count; ++i)
            {
                screen_Output *= 10;
                //InitSSD(&ssd_Display[i]);
                fscanf(day8_File, "%s,", final_Output[i].digits);
                final_Output[i].digit_Count = digit_Count;
                
                //printf("%s \n", final_Output[i].digits);
                TranslateTest(&final_Output[i], translate);
                //printf("%s \n", final_Output[i].digits);



                final_Output[i].final_Value = TicksToValue(final_Output[i].digits);
                screen_Output += final_Output[i].final_Value;
                //printf("%d \n", final_Output[i].final_Value);
                //printf("%d \n", screen_Output);
                //SetSSD(&ssd_Display[i], final_Output[i].digits);
            }
            result2 += screen_Output;

            //PrintSSDPanel(ssd_Display, ssd_Count);
        }

        fclose(day8_File);
    }

    ASSERT(result1 == 390);
    printf("The fifthtenth star answer is - %d\n", result1);
    //ASSERT(result2 == 99266250);
    printf("The sixtenth star answer is - %d\n", result2);
}

