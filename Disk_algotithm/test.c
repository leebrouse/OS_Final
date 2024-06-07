#include <stdio.h>
#include <stdlib.h>

#define SIZE 8 // 请求队列的大小

// 函数声明
void fcfs(int *array, int size);
void sstf(int *array, int size);
void cscan(int *array, int size);

void printMenu() {
    printf("磁盘调度算法菜单:\n");
    printf("1. FCFS (先来先服务)\n");
    printf("2. SSTF (最短寻道时间优先)\n");
    printf("3. C-SCAN (循环扫描)\n");
    printf("选择一个选项 (1-3): ");
}

int main() {
    int choice;
    int requests[SIZE] = {98, 183, 37, 122, 14, 124, 65, 67}; // 示例请求队列

    while (1) {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fcfs(requests, SIZE);
                break;
            case 2:
                sstf(requests, SIZE);
                break;
            case 3:
                cscan(requests, SIZE);
                break;
            default:
                printf("无效选择，请选择1到3之间的一个选项。\n");
                continue;
        }
        break;
    }

    return 0;
}

void fcfs(int *array, int size) {
    printf("执行FCFS算法...\n");
    int totalHeadMovement = 0;
    int currentPosition = 50; // 假设起始位置为50

    for (int i = 0; i < size; i++) {
        totalHeadMovement += abs(array[i] - currentPosition);
        currentPosition = array[i];
        printf("当前磁道为：%d. %d\n",i+1,currentPosition);
    }

    printf("FCFS算法执行完成，总磁头移动距离: %d\n", totalHeadMovement);
}

void sstf(int *array, int size) {
    printf("执行SSTF算法...\n");
    int totalHeadMovement = 0;
    int currentPosition = 50; // 假设起始位置为50
    int completed[size];
    for (int i = 0; i < size; i++) completed[i] = 0;

    for (int i = 0; i < size; i++) {
        int shortestSeekTime = 10000;
        int shortestSeekIndex = -1;

        for (int j = 0; j < size; j++) {
            if (!completed[j]) {
                int seekTime = abs(array[j] - currentPosition);
                if (seekTime < shortestSeekTime) {
                    shortestSeekTime = seekTime;
                    shortestSeekIndex = j;
                }
            }
        }

        totalHeadMovement += shortestSeekTime;
        currentPosition = array[shortestSeekIndex];
        completed[shortestSeekIndex] = 1;
    }

    printf("SSTF算法执行完成，总磁头移动距离: %d\n", totalHeadMovement);
}

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
