#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // minimal integer = INT_MIN
#define TAILS_LENGTH 4

int findElement(int element, int *arr, int size);
void removeElement(int idx, int *arr, int size);

int main(int argc, char *argv[])
{
    int height, width;
    scanf("%d %d", &height, &width);
    int *matrix = (int *)malloc(sizeof(int) * width * height);

    // test print of the size of the matrix
    // printf("\nm -- %d\nn -- %d\n", m, n);

    for (int i = 0; i < (width * height); i++)
    {
        scanf("%d", &matrix[i]);
    }

    // test print of the matrix
    // for (int i = 0; i < (width * height); i++)
    // {
    //     printf("%d  ", matrix[i]);
    //     if((i + 1) % width == 0) {
    //         printf("\n");
    //     }
    // }

    // allocate an array for all the tails and initialize it with minimal int
    int *matrixTail = (int *)malloc(sizeof(int) * width * height * 4);
    for (int i = 0; i < width * height * 4; i++)
    {
        matrixTail[i] = INT_MIN;
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if (w < (width - 1))
            {
                // create an array for maximums of tails and initialize it with minimal int
                int *maximums = (int *)malloc(sizeof(int) * (width - w - 1));
                // for (int i = 0; i < (width - w - 1); i++)
                // {
                //     maximums[i] = INT_MIN;
                // }
                int maxCurr = matrix[h * width + w + 1];
                maximums[0] = maxCurr;
                int idx = 1;
                for (int i = (w + 2); i < width; i++)
                {
                    maxCurr += matrix[h * width + i];
                    maximums[idx] = maxCurr;
                    idx++;
                }
                for (int i = 0; i < (width - w - 1); i++)
                {
                    if (maximums[i] > matrixTail[h * width * 4 + w * 4 + 0])
                    {
                        matrixTail[h * width * 4 + w * 4 + 0] = maximums[i];
                    }
                }
                free(maximums);
            }

            if (h > 0)
            {
                // create an array for maximums of tails and initialize it with minimal int
                int *maximums = (int *)malloc(sizeof(int) * h);
                // for (int i = 0; i < h; i++)
                // {
                //     maximums[i] = INT_MIN;
                // }
                int maxCurr = matrix[(h - 1) * width + w];
                maximums[0] = maxCurr;
                int idx = 1;
                for (int i = (h - 2); i > -1; i--)
                {
                    maxCurr += matrix[i * width + w];
                    maximums[idx] = maxCurr;
                    idx++;
                }
                for (int i = 0; i < h; i++)
                {
                    if (maximums[i] > matrixTail[h * width * 4 + w * 4 + 1])
                    {
                        matrixTail[h * width * 4 + w * 4 + 1] = maximums[i];
                    }
                }
                free(maximums);
            }

            if (w > 0)
            {
                // create an array for maximums of tails and initialize it with minimal int
                int *maximums = (int *)malloc(sizeof(int) * w);
                // for (int i = 0; i < w; i++)
                // {
                //     maximums[i] = INT_MIN;
                // }
                int maxCurr = matrix[h * width + w - 1];
                maximums[0] = maxCurr;
                int idx = 1;
                for (int i = (w - 2); i > -1; i--)
                {
                    maxCurr += matrix[h * width + i];
                    maximums[idx] = maxCurr;
                    idx++;
                }
                for (int i = 0; i < w; i++)
                {
                    if (maximums[i] > matrixTail[h * width * 4 + w * 4 + 2])
                    {
                        matrixTail[h * width * 4 + w * 4 + 2] = maximums[i];
                    }
                }
                free(maximums);
            }

            if (h < (height - 1))
            {
                // create an array for maximums of tails and initialize it with minimal int
                int *maximums = (int *)malloc(sizeof(int) * height - h - 1);
                // for (int i = 0; i < (height - h - 1); i++)
                // {
                //     maximums[i] = INT_MIN;
                // }
                int maxCurr = matrix[(h + 1) * width + w];
                maximums[0] = maxCurr;
                int idx = 1;
                for (int i = (h + 2); i < height; i++)
                {
                    maxCurr += matrix[i * width + w];
                    maximums[idx] = maxCurr;
                    idx++;
                }
                for (int i = 0; i < (height - h - 1); i++)
                {
                    if (maximums[i] > matrixTail[h * width * 4 + w * 4 + 3])
                    {
                        matrixTail[h * width * 4 + w * 4 + 3] = maximums[i];
                    }
                }
                free(maximums);
            }
        }
    }

    // test print of all the tails
    // for (int i = 0; i < width * height * 4; i++)
    // {
    //     printf("%d ", matrixTail[i]);
    //     if ((i + 1) % 4 == 0)
    //     {
    //         printf("    ");
    //     }
    //     if ((i + 1) % (width * 4) == 0)
    //     {
    //         printf("\n");
    //     }
    // }

    int sumMax = INT_MIN;
    for (int w = 0; w < width; w++)
    {
        for (int i = 0; i < (height - 3); i++)
        {
            int sums[2] = {0, 0};
            int sumCurr = INT_MIN;
            int fieldHeight = 0;
            int numOfRightTails = 0;
            int numOfLeftTails = 0;
            int rightTails[4];
            int leftTails[4];

            for (int h = i; h < height; h++)
            {
                int rightTailIdx = (h * width * 4 + w * 4 + 0);
                int leftTailIdx = (h * width * 4 + w * 4 + 2);
                int matrixItemIdx = (h * width + w);

                if (matrixTail[rightTailIdx] != INT_MIN)
                {
                    sums[0] += matrix[matrixItemIdx] + matrixTail[rightTailIdx];
                    rightTails[numOfRightTails] = matrixTail[rightTailIdx];
                    numOfRightTails += 1;
                }

                if (matrixTail[leftTailIdx] != INT_MIN)
                {
                    sums[1] += matrix[matrixItemIdx] + matrixTail[leftTailIdx];
                    leftTails[numOfLeftTails] = matrixTail[leftTailIdx];
                    numOfLeftTails += 1;
                }

                fieldHeight += 1;

                if (numOfRightTails > 3)
                {
                    int tmp = rightTails[0];
                    for (int i = 1; i < TAILS_LENGTH; i++)
                    {
                        // printf("rightTails[%d] -- %d\n", i, rightTails[i]);
                        tmp = (tmp > rightTails[i]) ? rightTails[i] : tmp;
                    }
                    sums[0] -= tmp;
                    removeElement(findElement(tmp, rightTails, TAILS_LENGTH), rightTails, TAILS_LENGTH);
                    numOfRightTails -= 1;
                }

                if (numOfLeftTails > 3)
                {
                    int tmp = leftTails[0];
                    for (int i = 1; i < TAILS_LENGTH; i++)
                    {
                        tmp = (tmp > leftTails[i]) ? leftTails[i] : tmp;
                    }
                    sums[1] -= tmp;
                    removeElement(findElement(tmp, leftTails, TAILS_LENGTH), leftTails, TAILS_LENGTH);
                    numOfLeftTails -= 1;
                }

                if (fieldHeight >= 3)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        sumCurr = (sumCurr < sums[i]) ? sums[i] : sumCurr;
                    }
                    sumMax = (sumCurr > sumMax) ? sumCurr : sumMax;
                }
            }
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int i = 0; i < (width - 3); i++)
        {
            int sums[2] = {0, 0};
            int sumCurr = INT_MIN;
            int fieldWidth = 0;
            int numOfUpperTails = 0;
            int numOfBottomTails = 0;
            int upperTails[4];
            int bottomTails[4];

            for (int w = i; w < width; w++)
            {
                int upperTailIdx = (h * width * 4 + w * 4 + 1);
                int bottomTailIdx = (h * width * 4 + w * 4 + 3);
                int matrixItemIdx = (h * width + w);

                if (matrixTail[upperTailIdx] != INT_MIN)
                {
                    sums[0] += matrix[matrixItemIdx] + matrixTail[upperTailIdx];
                    upperTails[numOfUpperTails] = matrixTail[upperTailIdx];
                    numOfUpperTails += 1;
                }

                if (matrixTail[bottomTailIdx] != INT_MIN)
                {
                    sums[1] += matrix[matrixItemIdx] + matrixTail[bottomTailIdx];
                    bottomTails[numOfBottomTails] = matrixTail[bottomTailIdx];
                    numOfBottomTails += 1;
                }

                fieldWidth += 1;

                if (numOfUpperTails > 3)
                {
                    int tmp = upperTails[0];
                    for (int i = 1; i < TAILS_LENGTH; i++)
                    {
                        tmp = (tmp > upperTails[i]) ? upperTails[i] : tmp;
                    }
                    sums[0] -= tmp;
                    removeElement(findElement(tmp, upperTails, TAILS_LENGTH), upperTails, TAILS_LENGTH);
                    numOfUpperTails -= 1;
                }

                if (numOfBottomTails > 3)
                {
                    int tmp = bottomTails[0];
                    for (int i = 1; i < TAILS_LENGTH; i++)
                    {
                        tmp = (tmp > bottomTails[i]) ? bottomTails[i] : tmp;
                    }
                    sums[1] -= tmp;
                    removeElement(findElement(tmp, bottomTails, TAILS_LENGTH), bottomTails, TAILS_LENGTH);
                    numOfBottomTails -= 1;
                }

                if (fieldWidth >= 3)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        sumCurr = (sumCurr < sums[i]) ? sums[i] : sumCurr;
                    }
                    sumMax = (sumCurr > sumMax) ? sumCurr : sumMax;
                }
            }
        }
    }

    printf("%d\n", sumMax);

    free(matrix);
    return 0;
}

int findElement(int element, int *arr, int size)
{
    int ret = -1;

    for (int i = 0; i < size; i++)
    {
        if (arr[i] == element)
        {
            ret = i;
        }
    }

    return ret;
}

void removeElement(int idx, int *arr, int size)
{
    for (int i = idx; i < (size - 1); i++)
    {
        arr[i] = arr[i + 1];
    }
}
