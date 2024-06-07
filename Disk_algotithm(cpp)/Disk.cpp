//Author: Leebrouse
//Date:2024/6/7
#include "Disk.h"
#include <iostream>
#include <algorithm>
#include <cmath> // for abs function

// 构造函数，初始化磁盘请求向量
Disk::Disk(std::vector<int> disk)
    : disk{disk} {}

// 先来先服务 (FCFS) 算法
void Disk::FCFS(Disk& requests, int head)
{    
    // 在向量开头插入初始磁头位置
    requests.disk.insert(requests.disk.begin(), head);
    std::cout << "FCFS排序: ";
    requests.printInfo(requests); // 打印排序后的磁盘请求向量
}

// 比较函数，用于比较左右请求的距离
int compare(int left, int current, int right) {
    int leftDistance = abs(current - left);
    int rightDistance = abs(current - right);

    // 返回更近的那个请求方向
    if (leftDistance < rightDistance) {
        return -1; // 选左值
    } else {
        return 1; // 选右值
    }
}

// 最短寻道时间优先 (SSTF) 算法
void Disk::SSTF(Disk& requests, int head)
{
    // 将初始磁头位置加入请求向量，并排序
    requests.disk.push_back(head);
    std::sort(requests.disk.begin(), requests.disk.end());

    int headIndex = requests.indexElement(requests, head);
    std::vector<bool> visited(requests.disk.size(), false); // 记录哪些请求已处理
    visited[headIndex] = true;

    std::cout << "SSTF排序: ";
    std::cout << requests.disk[headIndex] << ' ';

    // 处理所有请求
    for (int i = 1; i < requests.disk.size(); ++i)
    {
        int leftIndex = headIndex - 1;
        int rightIndex = headIndex + 1;

        // 跳过已访问的请求
        while (leftIndex >= 0 && visited[leftIndex]) --leftIndex;
        while (rightIndex < requests.disk.size() && visited[rightIndex]) ++rightIndex;

        int choice;
        if (leftIndex >= 0 && rightIndex < requests.disk.size()) {
            choice = compare(requests.disk[leftIndex], requests.disk[headIndex], requests.disk[rightIndex]);
        } else if (leftIndex >= 0) {
            choice = -1; // 只能选左值
        } else if (rightIndex < requests.disk.size()) {
            choice = 1; // 只能选右值
        } else {
            break; // 没有更多的请求了
        }

        if (choice == -1) {
            headIndex = leftIndex;
        } else {
            headIndex = rightIndex;
        }

        visited[headIndex] = true;
        std::cout << requests.disk[headIndex] << ' ';
    }

    std::cout << std::endl;
}

// 扫描 (SCAN) 算法
void Disk::SCAN(Disk& requests, int head)
{   
    // 将初始磁头位置、0和199加入请求向量，并排序
    requests.disk.push_back(head);
    requests.disk.push_back(0);
    requests.disk.push_back(199);
    std::sort(requests.disk.begin(), requests.disk.end());

    int headIndex = requests.indexElement(requests, head);

    std::cout << "SCAN排序: ";

    // 从 headIndex 开始向右处理请求
    for (auto iter = requests.disk.begin() + headIndex; iter != requests.disk.end(); iter++)
    {
        std::cout << *iter << " ";
    }

    // 从 headIndex + 1 开始向左处理请求
    for (auto iter = requests.disk.rbegin() + (requests.disk.size() - headIndex - 1); iter != requests.disk.rend(); iter++)
    {
        std::cout << *iter << " ";
    }

    std::cout << std::endl;
}

// 循环扫描 (C-SCAN) 算法
void Disk::CSCAN(Disk& requests, int head)
{   
    // 将初始磁头位置、0和199加入请求向量，并排序
    requests.disk.push_back(head);
    requests.disk.push_back(0);
    requests.disk.push_back(199);
    std::sort(requests.disk.begin(), requests.disk.end());

    int headIndex = requests.indexElement(requests, head);

    std::cout << "C-SCAN排序: "<<'\n';

    // 从 headIndex 开始向右处理请求，直到向量末尾
    for (auto iter = requests.disk.begin() + headIndex; iter != requests.disk.end(); iter++)
    {
        int currentDisk = *iter;
        std::cout << currentDisk << ' ';
    }

    // 从向量头部处理请求，直到 headIndex 处
    for (auto iter = requests.disk.begin(); iter != requests.disk.begin() + headIndex; iter++)
    {   
        int currentDisk = *iter;
        std::cout << currentDisk << ' ';
    }
    std::cout <<'\n';
}

// 打印磁盘请求向量
void Disk::printInfo(Disk& requests)
{
    for (int request : requests.disk) {
        std::cout << request << " ";
    }
    std::cout << std::endl;
}

// 查找元素在向量中的索引
int Disk::indexElement(Disk& requests, int index)
{
    auto it = std::find(requests.disk.begin(), requests.disk.end(), index);

    if (it != requests.disk.end()) {
        // 计算下标
        int idx = std::distance(requests.disk.begin(), it);
        return idx;
    } else {
        std::cout << "未找到值为 " << index << " 的元素" << std::endl;
        return -1; // 返回一个无效的索引
    }
}
