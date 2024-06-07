// Author: Leebrouse
// Date: 2024/6/7
#ifndef DISK_H
#define DISK_H

#include <vector>

class Disk
{  
private:
    std::vector<int> disk; // 存储磁盘请求的向量
    
public:
    // 默认构造函数
    Disk();

    // 带参数的构造函数，用于初始化磁盘请求向量
    Disk(std::vector<int> disk);

    // 先来先服务 (FCFS) 算法
    void FCFS(Disk requests, int head);

    // 最短寻道时间优先 (SSTF) 算法
    void SSTF(Disk requests, int head);

    // 扫描 (SCAN) 算法
    void SCAN(Disk requests, int head);

    // 循环扫描 (C-SCAN) 算法
    void CSCAN(Disk requests, int head);

    // 打印磁盘请求向量
    void printInfo(Disk requests);

    // 查找元素在向量中的索引
    int indexElement(Disk requests, int index);
};

#endif // DISK_H
