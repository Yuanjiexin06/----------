#include <iostream>
using namespace std;
#include "speechManager.h"

SpeechManager::SpeechManager()
{
    // 初始化比赛
    this->initSpeech();
    this->createSpeaker();
}
SpeechManager::~SpeechManager()
{
}
void SpeechManager::showMenu()
{
    std::cout << "欢迎使用演讲比赛流程管理系统" << std::endl;
    std::cout << "1. 开始演讲比赛" << std::endl;
    std::cout << "2. 查看往届记录" << std::endl;
    std::cout << "3. 清除往届记录" << std::endl;
    std::cout << "0. 退出比赛程序" << std::endl;
}
void SpeechManager::exitSystem()
{
    std::cout << "感谢使用演讲比赛流程管理系统，期待下次再见！" << std::endl;
    exit(0);
}
void SpeechManager::initSpeech()
{
    this->v1.clear();
    this->v2.clear();
    this->vVictor.clear();
    this->m_Speaker.clear();
    this->m_Index = 1;
}
void SpeechManager::createSpeaker()
{
    std::string nameSeed = "ABCDEFGHIJKL";
    for (int i = 0; i < nameSeed.size(); ++i)
    {
        std::string name = "选手";
        name += nameSeed[i];
        Speaker sp;
        sp.m_Name = name;
        for (int i = 0; i < 2; ++i)
        {
            sp.m_Score[i] = 0;
        }
        this->v1.push_back(i + 10001);
        this->m_Speaker.insert(std::make_pair(i + 10001, sp));
    }
}
void SpeechManager::startSpeech()
{

    // 抽签
    this->speechDraw();
    // 开始第一轮比赛
    this->speechContest();
    // 显示晋级结果

    // 抽签

    // 开始第二轮比赛

    // 显示最终结果

    // 保存分数到文件中
}
void SpeechManager::speechDraw()
{
    std::cout << "第<< " << this->m_Index << " >>轮比赛选手正在抽签" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    if (this->m_Index == 1)
    {
        // 第一轮比赛
        random_shuffle(v1.begin(), v1.end());
        std::cout << "抽签顺序如下" << std::endl;
        for (std::vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
        {
            std::cout << (*it) << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        // 第二轮比赛
        random_shuffle(v2.begin(), v2.end());
        for (std::vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
        {
            std::cout << (*it) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------------------" << std::endl;
    cout << "请按任意键继续..." << endl;
    cin.ignore(); // 清除残留的回车
    cin.get();    // 等待用户按键
}
void SpeechManager::speechContest()
{
    //准备临时容器 存放小组成绩
    multimap<double, int , greater<double>> groupScore; // 分数-选手编号

    //记录人员个数 6人一组
    int num = 0;
    std::cout << "第<< " << this->m_Index << " >>轮比赛正式开始" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    vector<int> v_Src; // 比赛选手容器
    if (this->m_Index == 1)
    {
        v_Src = this->v1;
    }
    else
    {
        v_Src = this->v2;
    }
    // 遍历所以比赛选手
    for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
    {
        num++;
        // 评委打分
        deque<double> d;
        for (int i = 0; i < 10; i++)
        {
            double score = (rand() % 401 + 600) / 10.f;
            //cout << score << " ";
            d.push_back(score);
        }
        //cout << endl;
        sort(d.begin(), d.end(), greater<double>()); // 排序
        d.pop_front();                               // 去掉最高分
        d.pop_back();                                // 去掉最低分
        double sum = accumulate(d.begin(), d.end(), 0.0f); // 求和
        double avg = sum / (double)d.size();               // 求平均分
        //打印平均分
        //cout << "选手编号: " << *it << " 姓名: " << this->m_Speaker[*it].m_Name << " 得分: " << avg << endl;
        //将平均分放到map容器中
        this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
        
        //将打分的的数据放到临时的小组容器中
        groupScore.insert(make_pair(avg, *it));
        //每6个人取前三晋级
        if (num % 6 == 0){
            cout << "第" << num / 6 << "小组比赛名次：" << endl;
            for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
            {
                cout << "选手编号: " << it->second << " 姓名: " << this->m_Speaker[it->second].m_Name << " 得分: " << it->first << endl;
            }
            //获取前三名
            int count = 0;
            for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++ , count++)
            {
                if (this->m_Index == 1)
                {
                    this->v2.push_back(it->second);
                }
                else
                {
                    this->vVictor.push_back(it->second);
                }
            }
            groupScore.clear(); // 清空容器 为下组比赛做准备
            cout << "---------------------------------------------" << endl;
        }
    }
    cout << "第" << this->m_Index << "轮比赛结束" << endl;
    cout << "请按任意键继续..." << endl;
    cin.ignore(); // 清除残留的回车
    cin.get();    // 等待用户按键
}