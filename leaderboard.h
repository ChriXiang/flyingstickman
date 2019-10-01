#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QWidget>
#include <QDesktopWidget>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QList>
#include <QDir>

#include <iostream>
#include <string>
#include <vector>


class LeaderBoard{
public:
    LeaderBoard();

    void parser();
    std::vector<std::pair<std::string, int>> getLeaders();
    void addLeader(std::string name, int score);
    bool sortScore(const std::pair<std::string,int> &a,const std::pair<std::string,int> &b);

private:
    std::vector<std::pair<std::string, int>> leaders;
    QFile file;
};

#endif // LEADERBOARD_H
