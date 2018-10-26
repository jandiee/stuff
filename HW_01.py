import sys

matrix = []
matrixSize = []

i = 0
for line in sys.stdin:
    for val in line.split():
        if i < 2:
            matrixSize.append(val)
        else:
            matrix.append(val)
        i += 1
del(i)

for i in range(len(matrixSize)):
    matrixSize[i] = int(matrixSize[i])

for i in range(len(matrix)):
    matrix[i] = int(matrix[i])

height = matrixSize[0]
width = matrixSize[1]
# print("Rows - ", height, "\nColumns - ", width)

matrixTail = [0] * width * height * 4

for h in range(height):
    for w in range(width):

        maxCurr = 0
        maximums = []
        if w != width - 1:
            for i in range(w + 1, width):
                maxCurr += matrix[h * width + i]
                maximums.append(maxCurr)
            matrixTail[h * width * 4 + w * 4 +
                       0] = max(maximums)  # right max tail
        # else:
        #     matrixTail[h * width * 4 + w * 4 + 0] = -sys.maxsize - 1

        maxCurr = 0
        maximums = []
        if h != 0:
            for i in range(h - 1, -1, -1):
                maxCurr += matrix[i * width + w]
                maximums.append(maxCurr)
            matrixTail[h * width * 4 + w * 4 +
                       1] = max(maximums)  # upper max tail
        # else:
        #     matrixTail[h * width * 4 + w * 4 + 1] = -sys.maxsize - 1

        maxCurr = 0
        maximums = []
        if w != 0:
            for i in range(w - 1, -1, -1):
                maxCurr += matrix[h * width + i]
                maximums.append(maxCurr)
            matrixTail[h * width * 4 + w * 4 +
                       2] = max(maximums)  # left max tail
        # else:
        #     matrixTail[h * width * 4 + w * 4 + 2] = -sys.maxsize - 1

        maxCurr = 0
        maximums = []
        if h != height - 1:
            for i in range(h + 1, height):
                maxCurr += matrix[i * width + w]
                maximums.append(maxCurr)
            matrixTail[h * width * 4 + w * 4 +
                       3] = max(maximums)  # bottom max tail
        # else:
        #     matrixTail[h * width * 4 + w * 4 + 3] = -sys.maxsize - 1

        del(maxCurr)
        del(maximums)

# for i in range(len(matrixTail)):
#     print(matrixTail[i], end=' ')
#     if (i + 1) % 4 == 0:
#         print(' ', end=' ')
#     if (i + 1) % (width * 4) == 0:
#         print()
