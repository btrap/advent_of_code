#pragma once

int ConvertFromBinaryToInt(int *binary, int binary_Length)
{
    int return_Value = 0;
    int pos = 0;

    for(int i = 0; i < binary_Length; ++i)
    {
        pos = (binary_Length - 1 - i);
        return_Value += binary[i] << pos;
    }

    return return_Value;
}

void Advent_Of_Code_2021_03()
{
    int result1 = 0;
    int result2 = 0;
    FILE *temp = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day3_input.txt", "r");

    int binary_Sums[12] = {0};
    if(temp)
    {
        FILE *walker = temp;

        int line_Count = 0;
        int word_Length = 12;
        char command[13];
        while(fscanf(walker, "%s", command) != EOF)
        {
            ++line_Count;
            for(int i = 0; command[i] != 0; ++i)
            {
                binary_Sums[i] += command[i] - '0';
            }
        }

        int half_Line_Count = (line_Count / 2);
        int gamma_Rate = 0;
        int epsilon_Rate = 0;
        int pos = 0;
        int bit = 0;
        for(int i = 0; i < word_Length; ++i)
        {
            bit = (binary_Sums[i] <= half_Line_Count);
            pos = (11 - i);
            gamma_Rate += bit << pos;
            epsilon_Rate += (1 - bit) << pos;
        }
        result1 = gamma_Rate * epsilon_Rate;
        ASSERT(result1 == 4001724);

        fseek(temp, 0, SEEK_SET);

        int *bin_Value = 0;
        int bin_Value_Size = line_Count * word_Length;
        int bin_Value_Count = line_Count;
        int currentBin = 0;
        STORE_PERM_DATA(bin_Value, bin_Value_Size);
        while(fscanf(walker, "%s", command) != EOF)
        {
            for(int i = 0; command[i] != 0; ++i)
            {
                bin_Value[currentBin * word_Length + i] = command[i] - '0';
            }
            ++currentBin;
        }
 
        int test_Pos = 0;
        int one_Count = 0;
        int zero_Count = 0;
        int keep_Bit = 0;
        
        int *temp_Bin = 0;
        int temp_Bin_Count = 0;

        int oxygen_Generator_Rate = 0;
        int co2_Scrubber_rate = 0;
        
        while(test_Pos < word_Length)
        {
            one_Count = 0;
            zero_Count = 0;

            // test for 1 or 0
            for(int i = 0; i < bin_Value_Count; ++i)
            {
                if(bin_Value[i * word_Length + test_Pos])
                {
                    ++one_Count;
                }
                else
                {
                    ++zero_Count;
                }
            }

            if(one_Count >= zero_Count)
            {
                keep_Bit = 1;
                temp_Bin_Count = one_Count;
            }
            else
            {
                keep_Bit = 0;
                temp_Bin_Count = zero_Count;
            }
            
            // Move keepers up
            int final_Pos = 0;
            int temp_Bin_Pos = 0;
            for(int i = 0; i < bin_Value_Count; ++i)
            {
                if(bin_Value[i * word_Length + test_Pos] == keep_Bit)
                {
                    for(int j = 0; j < word_Length; ++j)
                    {
                        final_Pos = i * word_Length + j;
                        bin_Value[temp_Bin_Pos * word_Length + j] = bin_Value[final_Pos];
                    }
                    ++temp_Bin_Pos;
                }
            }
            bin_Value_Count = temp_Bin_Count;

            ++test_Pos;
        }
        oxygen_Generator_Rate = ConvertFromBinaryToInt(bin_Value, word_Length);
        ASSERT(oxygen_Generator_Rate == 2545);
        
        fseek(temp, 0, SEEK_SET);
        bin_Value_Size = line_Count * word_Length;
        bin_Value_Count = line_Count;
        currentBin = 0;
        while(fscanf(walker, "%s", command) != EOF)
        {
            for(int i = 0; command[i] != 0; ++i)
            {
                bin_Value[currentBin * word_Length + i] = command[i] - '0';
            }
            ++currentBin;
        }

        test_Pos = 0;
        while(test_Pos < word_Length)
        {
            one_Count = 0;
            zero_Count = 0;

            // test for 1 or 0
            for(int i = 0; i < bin_Value_Count; ++i)
            {
                if(bin_Value[i * word_Length + test_Pos])
                {
                    ++one_Count;
                }
                else
                {
                    ++zero_Count;
                }
            }

            if(one_Count < zero_Count)
            {
                keep_Bit = 1;
                temp_Bin_Count = one_Count;
            }
            else
            {
                keep_Bit = 0;
                temp_Bin_Count = zero_Count;
            }

            // Move keepers up
            int final_Pos = 0;
            int temp_Bin_Pos = 0;
            int other_Pos = 0;
            for(int i = 0; i < bin_Value_Count; ++i)
            {
                if(bin_Value[i * word_Length + test_Pos] == keep_Bit)
                {
                    for(int j = 0; j < word_Length; ++j)
                    {
                        final_Pos = i * word_Length + j;
                        other_Pos = temp_Bin_Pos * word_Length + j;
                        bin_Value[other_Pos] = bin_Value[final_Pos];
                    }
                    ++temp_Bin_Pos;
                }
            }
            bin_Value_Count = temp_Bin_Count;

            ++test_Pos;
        }
        co2_Scrubber_rate = ConvertFromBinaryToInt(bin_Value, word_Length);
        ASSERT(co2_Scrubber_rate == 231);

        result2 = oxygen_Generator_Rate * co2_Scrubber_rate;

        fclose(temp);
    }

    ASSERT(result1 == 4001724);
    printf("The fifth star answer is - %d\n", result1);
    ASSERT(result2 == 587895);
    printf("The sixth star answer is - %d\n", result2);
}
