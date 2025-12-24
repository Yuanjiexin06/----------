#include <iostream>
#include <ctime>

#include "speechManager.h"
#include "speaker.h"
using namespace std;

int main() {

    //添加随机数种子
    srand((unsigned int)time(NULL));
    SpeechManager sm; // 创建演讲比赛管理对象
    //测试
    // for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); ++it) {
    //     std::cout << "选手编号: " << it->first << " 姓名: " << it->second.m_Name << " 分数: " << it->second.m_Score[0] << std::endl;
    // }
    while (true) {
        sm.showMenu(); // 显示菜单
        int choice;
        std::cout << "请输入您的选择:>";
        std::cin >> choice; // 用户输入选择
        switch (choice) {
            case 1:
                // 开始演讲比赛的逻辑
                sm.startSpeech();
                break;
            case 2:
                // 查看往届记录的逻辑
                sm.showRecord();
                break;
            case 3:
                // 清除往届记录的逻辑
                sm.clearRecord();
                break;
            case 0:
                sm.exitSystem(); // 退出系统
                break;
            default:
                system("clear");
                std::cout << "无效的选择，请重新输入！" << std::endl; // 清屏
                break;
        }
    }
    return 0;
}