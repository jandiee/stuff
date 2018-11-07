#include <stdio.h>
#include <stdlib.h>

#define BOTS_COORDS 4

int bot_run(int *matrix, int width, int **bots, int bot_idx);
void permute(int *array, int i, int length);
void swap(int *array, int i, int j);
int factorial(int x);
void putToArray(int *array, int length, int **permutations_arr, int index);

int idx = 0;
int **bots_permutations;

int main(int argc, char const **argv)
{
    // scan size of the matrix, allocate it and scan numbers into it
    int height, width;
    scanf("%d %d", &height, &width);
    int *matrix = (int *)malloc(sizeof(int) * width * height);
    for (int i = 0; i < (height * width); i++)
    {
        scanf("%d", &matrix[i]);
    }

    // scan number of bots, allocate it and scan coordinates of starting and ending field
    int num_of_bots;
    scanf("%d", &num_of_bots);
    int **bots;
    bots = (int **)malloc(sizeof(int *) * num_of_bots);
    for (int i = 0; i < num_of_bots; i++)
    {
        bots[i] = (int *)malloc(sizeof(int) * BOTS_COORDS);
        for (int j = 0; j < BOTS_COORDS; j++)
        {
            scanf("%d", &bots[i][j]);
        }
    }

    int *bots_to_permute = (int *)malloc(sizeof(int) * num_of_bots);
    for (int i = 0; i < num_of_bots; i++)
    {
        bots_to_permute[i] = i;
    }

    // copy the matrix with the original values
    int *original_matrix = (int *)malloc(sizeof(int) * width * height);
    for (int i = 0; i < (height * width); i++)
    {
        original_matrix[i] = matrix[i];
    }

    int fact_num_of_bots = factorial(num_of_bots);
    bots_permutations = (int **)malloc(sizeof(int *) * fact_num_of_bots);
    for (int i = 0; i < fact_num_of_bots; i++)
    {
        bots_permutations[i] = (int *)malloc(sizeof(int) * num_of_bots);
    }

    permute(bots_to_permute, 0, num_of_bots);

    int sumMax = 0;
    int sumCurr = 0;
    for (int i = 0; i < fact_num_of_bots; i++)
    {
        sumCurr = 0;
        for (int j = 0; j < num_of_bots; j++)
        {
            sumCurr += bot_run(matrix, width, bots, bots_permutations[i][j]);
        }
        for (int j = 0; j < (width * height); j++)
        {
            matrix[j] = original_matrix[j];
        }
        sumMax = sumCurr > sumMax ? sumCurr : sumMax;
    }

    printf("%d\n", sumMax);

    return 0;
}

// returns a sum of the values in the path of one bot
// also stop adding if the bot goes onto a field that has already been harvested
int bot_run(int *matrix, int width, int **bots, int bot_idx)
{
    int ret = 0;

    if (bots[bot_idx][0] == bots[bot_idx][2] && bots[bot_idx][1] == bots[bot_idx][3])
    {
        return 0;
    }

    if (bots[bot_idx][0] == bots[bot_idx][2])
    {
        if (bots[bot_idx][1] < bots[bot_idx][3])
        {
            for (int i = bots[bot_idx][1]; i <= bots[bot_idx][3]; i++)
            {
                // stop adding if the bot goes onto a field that has been harvested
                if (matrix[bots[bot_idx][0] * width + i] == 0)
                {
                    break;
                }
                // harvest the field
                ret += matrix[bots[bot_idx][0] * width + i];
                matrix[bots[bot_idx][0] * width + i] = 0;
            }
        }
        else
        {
            for (int i = bots[bot_idx][1]; i >= bots[bot_idx][3]; i--)
            {
                // stop adding if the bot goes onto a field that has been harvested
                if (matrix[bots[bot_idx][0] * width + i] == 0)
                {
                    break;
                }
                // harvest the field
                ret += matrix[bots[bot_idx][0] * width + i];
                matrix[bots[bot_idx][0] * width + i] = 0;
            }
        }
    }
    else
    {
        if (bots[bot_idx][0] < bots[bot_idx][2])
        {
            for (int i = bots[bot_idx][0]; i <= bots[bot_idx][2]; i++)
            {
                // printf("matrix[i * width + bots[bot_idx][1] -- %d\n", matrix[i * width + bots[bot_idx][1]]);
                // stop adding if the bot goes onto a field that has been harvested
                if (matrix[i * width + bots[bot_idx][1]] == 0)
                {
                    break;
                }
                // harvest the field
                ret += matrix[i * width + bots[bot_idx][1]];
                // printf("ret -- %d\n", ret);
                matrix[i * width + bots[bot_idx][1]] = 0;
            }
        }
        else
        {
            for (int i = bots[bot_idx][0]; i >= bots[bot_idx][2]; i--)
            {
                // printf("matrix[i * width + bots[bot_idx][1] -- %d\n", matrix[i * width + bots[bot_idx][1]]);
                // stop adding if the bot goes onto a field that has been harvested
                if (matrix[i * width + bots[bot_idx][1]] == 0)
                {
                    break;
                }
                // harvest the field
                ret += matrix[i * width + bots[bot_idx][1]];
                // printf("ret -- %d\n", ret);
                matrix[i * width + bots[bot_idx][1]] = 0;
            }
        }
    }

    return ret;
}

void permute(int *array, int i, int length)
{
    if (length == i)
    {
        putToArray(array, length, bots_permutations, idx++);
        return;
    }

    int j = i;

    for (j = i; j < length; j++)
    {
        swap(array, i, j);
        permute(array, i + 1, length);
        swap(array, i, j);
    }
}

void swap(int *array, int i, int j)
{
    int tmp = array[j];
    array[j] = array[i];
    array[i] = tmp;
}

int factorial(int x)
{
    if (x == 0 || x == 1)
    {
        return 1;
    }
    else
    {
        return (x * factorial(x - 1));
    }
}

void putToArray(int *array, int length, int **permutations_arr, int index)
{
    for (int i = 0; i < length; i++)
    {
        bots_permutations[index][i] = array[i];
    }
}
