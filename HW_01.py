import sys

matrix = []
matrixSize = []
MIN_INT = (-sys.maxsize - 1)

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

# find max tail for each item in whole matrix and save it to the list matrixTail
# matrixTail['line * width * 4 + pos * 4 + 0' - right tail
#           'line * width * 4 + pos * 4 + 1' - upper tail
#           'line * width * 4 + pos * 4 + 2' - left tail
#           'line * width * 4 + pos * 4 + 3' - bottom tail]
for h in range(height):
    for w in range(width):

        if w < width - 1:
            maximums = []
            maxCurr = matrix[h * width + w + 1]
            maximums.append(maxCurr)
            for i in range(w + 2, width):
                maxCurr += matrix[h * width + i]
                maximums.append(maxCurr)
            matrixTail[h * width * 4 + w * 4 +
                       0] = max(maximums)  # right max tail
        else:
            matrixTail[h * width * 4 + w * 4 + 0] = MIN_INT

        if h > 0:
            maximums = []
            maxCurr = matrix[(h - 1) * width + w]
            maximums.append(maxCurr)
            for i in range(h - 2, -1, -1):
                maxCurr += matrix[i * width + w]
                maximums.append(maxCurr)
            matrixTail[h * width * 4 + w * 4 +
                       1] = max(maximums)  # upper max tail
        else:
            matrixTail[h * width * 4 + w * 4 + 1] = MIN_INT

        if w > 0:
            maximums = []
            maxCurr = matrix[h * width + w - 1]
            maximums.append(maxCurr)
            for i in range(w - 2, -1, -1):
                maxCurr += matrix[h * width + i]
                maximums.append(maxCurr)
            matrixTail[h * width * 4 + w * 4 +
                       2] = max(maximums)  # left max tail
        else:
            matrixTail[h * width * 4 + w * 4 + 2] = MIN_INT

        if h < height - 1:
            maximums = []
            maxCurr = matrix[(h + 1) * width + w]
            maximums.append(maxCurr)
            for i in range(h + 2, height):
                maxCurr += matrix[i * width + w]
                maximums.append(maxCurr)
            matrixTail[h * width * 4 + w * 4 +
                       3] = max(maximums)  # bottom max tail
        else:
            matrixTail[h * width * 4 + w * 4 + 3] = MIN_INT

        del(maxCurr)
        del(maximums)

# for i in range(len(matrixTail)):
#     print(matrixTail[i], end=' ')
#     if (i + 1) % 4 == 0:
#         print(' ', end=' ')
#     if (i + 1) % (width * 4) == 0:
#         print()

sumMax = MIN_INT
# find max sum for all fields that have the stem field in the vertical direction
for w in range(width):
    for i in range(height - 3):
        sums = [0] * 2
        sumCurr = MIN_INT
        fieldHeight = 0
        numOfRightTails = 0
        numOfLeftTails = 0
        rightTails = []
        leftTails = []
        for h in range(i, height):
            rightTailIdx = (h * width * 4 + w * 4 + 0)
            leftTailIdx = (h * width * 4 + w * 4 + 2)
            matrixItemIdx = (h * width + w)

            if matrixTail[rightTailIdx] != MIN_INT:
                sums[0] += matrix[matrixItemIdx] + matrixTail[rightTailIdx]
                numOfRightTails += 1
                rightTails.append(matrixTail[rightTailIdx])

            if matrixTail[leftTailIdx] != MIN_INT:
                sums[1] += matrix[matrixItemIdx] + matrixTail[leftTailIdx]
                numOfLeftTails += 1
                leftTails.append(matrixTail[leftTailIdx])

            fieldHeight += 1

            if numOfRightTails > 3:
                tmp = min(rightTails)
                sums[0] -= tmp
                rightTails.remove(tmp)

            if numOfLeftTails > 3:
                tmp = min(leftTails)
                sums[1] -= tmp
                leftTails.remove(tmp)

            if fieldHeight >= 3:
                sumCurr = max(sums)
                sumMax = max(sumMax, sumCurr)
                # print("column = ", w, "\nrow = ", h, "\nfieldHeight = ",
                #       fieldHeight, "\nsumCurr = ", sumCurr, "\nSumMax = ", sumMax, "\nleftTails = ", leftTails, "\n")

# find max sum for all fields that have the stem field in the horizontal direction
for h in range(height):
    for i in range(width - 3):
        sums = [0] * 2
        sumCurr = MIN_INT
        fieldWidth = 0
        numOfUpperTails = 0
        numOfBottomTails = 0
        upperTails = []
        bottomTails = []
        for w in range(i, width):
            upperTailIdx = (h * width * 4 + w * 4 + 1)
            bottomTailIdx = (h * width * 4 + w * 4 + 3)
            matrixItemIdx = (h * width + w)

            if matrixTail[upperTailIdx] != MIN_INT:
                sums[0] += matrix[matrixItemIdx] + matrixTail[upperTailIdx]
                numOfUpperTails += 1
                upperTails.append(matrixTail[upperTailIdx])

            if matrixTail[bottomTailIdx] != MIN_INT:
                sums[1] += matrix[matrixItemIdx] + \
                    matrixTail[bottomTailIdx]
                numOfBottomTails += 1
                bottomTails.append(matrixTail[bottomTailIdx])

            fieldWidth += 1

            if numOfUpperTails > 3:
                tmp = min(upperTails)
                sums[0] -= tmp
                upperTails.remove(tmp)

            if numOfBottomTails > 3:
                tmp = min(bottomTails)
                sums[1] -= tmp
                bottomTails.remove(tmp)

            if fieldWidth >= 3:
                sumCurr = max(sums)
                sumMax = max(sumMax, sumCurr)
                # print("column = ", w, "\nrow = ", h, "\nfieldHeight = ",
                #       fieldHeight, "\nsumCurr = ", sumCurr, "\nSumMax = ", sumMax, "\nleftTails = ", leftTails, "\n")

print(sumMax)
