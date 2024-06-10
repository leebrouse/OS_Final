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
void Disk::FCFS(Disk requests, int head)
{    
    // 在向量开头插入初始磁头位置
    requests.disk.insert(requests.disk.begin(), head);
    std::cout << "FCFS排序: ";
    requests.printInfo(requests); // 打印排序后的磁盘请求向量
    std::cout<<'\n';
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

void Disk::SSTF(Disk requests, int head)
{
    // 将初始磁头位置加入请求向量，并排序
    requests.disk.push_back(head);
    std::sort(requests.disk.begin(), requests.disk.end());

    int headIndex = requests.indexElement(requests, head);

    std::cout << "SSTF排序: ";
    std::cout << requests.disk[headIndex] << ' ';

    // 处理所有请求
    for (int i = 0; i < requests.disk.size(); i++)
    {
        if (headIndex == 0) {
            // 边界情况：磁头在最左边，由于在处理之前已经被sort排序则只需循环输出就可，最后return退出；
            for (auto iter = requests.disk.begin()+1; iter != requests.disk.end(); iter++) {
                std::cout << *iter << " ";
            }
            std::cout<<'\n';
            return;
        }
        else if (headIndex == requests.disk.size() - 1) {
            // 边界情况：磁头在最右边，由于在处理之前已经被sort排序则只需循环输出就可，最后return退出；
            for (auto iter = requests.disk.begin()+1; iter != requests.disk.end(); iter++) {
                std::cout << *iter << " ";
            }
            std::cout<<'\n';
            return;
        }
        else {
            // 在两个请求之间，继续处理
            if (compare(requests.disk[headIndex-1],requests.disk[headIndex],requests.disk[headIndex+1])==-1) {
                // 左侧请求更近，向左移动磁头，删除已经过的序号
                std::cout << requests.disk[headIndex - 1] << " ";
                requests.disk.erase(requests.disk.begin()+headIndex);
                headIndex--;
            }
            else {
                // 右侧请求更近，向右移动磁头，删除已经过的序号
                std::cout << requests.disk[headIndex + 1] << " ";
                requests.disk.erase(requests.disk.begin()+headIndex);
                
                //vector中erase的特点，erase()可以删除vector中的元素，后续的元素会前移，则无需进行headIndex++;
                // headIndex++;
            }
        }
    }
    std::cout<<'\n';
}


// 扫描 (SCAN) 算法
void Disk::SCAN(Disk requests, int head)
{   
    // 将初始磁头位置,并排序
    requests.disk.push_back(head);
    std::sort(requests.disk.begin(), requests.disk.end());

    int headIndex = requests.indexElement(requests, head);

    std::cout << "SCAN排序: ";

    // 从 headIndex 开始向右处理请求
    for (auto iter = requests.disk.begin() + headIndex; iter != requests.disk.end(); iter++)
    {
        std::cout << *iter << " ";
    }

    // 从 headIndex - 1 开始向左处理请求
    for (auto iter = requests.disk.begin()+headIndex-1; iter !=requests.disk.begin(); iter--)
    {
        std::cout << *iter << " ";
    }

    std::cout<<'\n';
}

// 循环扫描 (C-SCAN) 算法
void Disk::CSCAN(Disk requests, int head)
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
void Disk::printInfo(Disk requests)
{
    for (int request : requests.disk) {
        std::cout << request << " ";
    }
    std::cout << std::endl;
}

// 查找元素在向量中的索引
int Disk::indexElement(Disk requests, int index)
{
    auto it = std::find(requests.disk.begin(), requests.disk.end(), index);

    if (it != requests.disk.end()) {
        // 计算下标
        int idx = std::distance(requests.disk.begin(), it);
        return idx;
    } else {
        std::cout << "未找到值为%d " << index << " 的元素" << std::endl;
        return -1; // 返回一个无效的索引
    }
}
