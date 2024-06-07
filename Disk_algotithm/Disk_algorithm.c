#include<stdio.h>
#include "Disk_algorithm.h"

void cscan(int *array, int size) {
    printf("执行C-SCAN算法...\n");
    int totalHeadMovement = 0;
    int currentPosition = 50; // 假设起始位置为50
    int maxRange = 199; // 假设磁盘最大范围为199
    int tempArray[size + 2]; // 包含起始位置和终点位置的临时数组

    for (int i = 0; i < size; i++) {
        tempArray[i] = array[i];
    }
    tempArray[size] = currentPosition;
    tempArray[size + 1] = maxRange;

    // 对请求队列进行排序
    for (int i = 0; i < size + 2 - 1; i++) {
        for (int j = 0; j < size + 2 - i - 1; j++) {
            if (tempArray[j] > tempArray[j + 1]) {
                int temp = tempArray[j];
                tempArray[j] = tempArray[j + 1];
                tempArray[j + 1] = temp;
            }
        }
    }

    int currentIndex;
    for (int i = 0; i < size + 2; i++) {
        if (tempArray[i] == currentPosition) {
            currentIndex = i;
            break;
        }
    }

    for (int i = currentIndex; i < size + 2; i++) {
        totalHeadMovement += abs(tempArray[i] - currentPosition);
        currentPosition = tempArray[i];
    }

    totalHeadMovement += maxRange; // 跳到另一端
    currentPosition = 0;

    for (int i = 0; i < currentIndex; i++) {
        totalHeadMovement += abs(tempArray[i] - currentPosition);
        currentPosition = tempArray[i];
    }

    printf("C-SCAN算法执行完成，总磁头移动距离: %d\n", totalHeadMovement);
}
