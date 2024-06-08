// Author: Leebrouse
// Date: 2024/6/7

#include <iostream>
#include <vector>
#include "Disk.h"

using namespace std;
// 菜单函数声明
void meun();

int main(int argc, char const *argv[]) {
    // 磁盘请求向量
    vector<int> disk = {98, 183, 37, 122, 20, 124, 40,51};

    // 创建 Disk 对象
    Disk requests(disk);

    // 初始磁头位置
    int head = 50;

    // 用户选择的选项
    int choice;

    // 直到用户选择退出
       
    while (choice!=5)
    {
         // 显示菜单
        meun();
        
        // 获取用户输入
        std::cin >> choice;

        // 根据用户选择执行相应的调度算法
        switch (choice) {
            case 1:
                // 先来先服务 (FCFS) 算法
                requests.FCFS(requests, head);
                cout<<'\n';
                break;
            case 2:
                // 最短寻道时间优先 (SSTF) 算法
                requests.SSTF(requests, head);
                cout<<'\n';
                break;
            case 3:
                // 扫描 (SCAN) 算法
                requests.SCAN(requests, head);
                cout<<'\n';
                break;
            case 4:
                // 循环扫描 (C-SCAN) 算法
                requests.CSCAN(requests, head);
                cout<<'\n';
                break;
            case 5:
                cout<<"成功退出！!\n";
                cout<<'\n';
                break;
            default:
                // 无效的选项
                cout << "无效的选项, Again!!!\n" << '\n';
                break;
        }
    }
    return 0;
}

// 显示磁盘调度算法菜单
void meun() {
    cout << "磁盘调度算法菜单:\n";
    cout << "1. FCFS (先来先服务)\n";
    cout << "2. SSTF (最短寻道时间优先)\n";
    cout << "3. SCAN (扫描)\n";
    cout << "4. C-SCAN (循环扫描)\n";
    cout << "5. 退出\n";
    cout << "选择一个选项: ";
}
