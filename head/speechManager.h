#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>

#include "speaker.h"


class SpeechManager {
public:
    SpeechManager();
    ~SpeechManager();

    void showMenu(); // 显示菜单
    void exitSystem(); // 退出系统
    void initSpeech(); // 初始化比赛
    void createSpeaker(); // 创建选手
    void startSpeech(); // 开始比赛
    void speechDraw(); //抽签
    void speechContest(); // 比赛

    std::vector<int> v1;
    std::vector<int> v2;
    std::vector<int> vVictor;
    std::map<int, Speaker> m_Speaker;
    int m_Index; // 记录当前轮数
};