#include "leaderboard.h"

LeaderBoard::LeaderBoard() :
    leaders(std::vector<std::pair<std::string, int>>())
{
    // leader board is saved at current directory.
    QDir dir(".");
    file.setFileName(dir.absolutePath() + QString("/leader.txt"));
    parser();
}

void LeaderBoard::parser(){

    //Open the config file
    if (file.open(QIODevice::ReadOnly)) {

        QTextStream buffer(&file);

        while (!buffer.atEnd()) {
            QString line = buffer.readLine();

            QStringList split_line = line.split(":", QString::SkipEmptyParts);

            QString element = split_line.at(1);

            leaders.push_back(std::make_pair(split_line.first().toStdString() , element.toInt()));
        }

        file.close();
    } else {
        std::cerr << "ll Leader board file not found" << std::endl;
    }
    //Create the stickman, given the parameters from the config file
}

bool LeaderBoard::sortScore(const std::pair<std::string,int> &a,const std::pair<std::string,int> &b) {
       return (a.second > b.second);
}

void LeaderBoard::addLeader(std::string name, int score){

    for (unsigned int i = 0;i < leaders.size(); i ++){
        if (score >= leaders[i].second){
            leaders.insert(leaders.begin() + i,std::make_pair(name , score));
            //puts("cat");
            break;
        }
        else if (i == leaders.size() - 1){
            leaders.push_back(std::make_pair(name , score));
            break;
        }
    }

    if (file.open(QIODevice::WriteOnly)) {

        QTextStream in(&file);

        for (unsigned int i = 0; i < leaders.size(); i++)
        {
            in<<leaders[i].first.c_str()<<':'<<leaders[i].second<<endl;
        }
        file.close();
    }
    else{
        std::cerr << "hh Leader board file not found" << std::endl;
    }
}

std::vector<std::pair<std::string, int>> LeaderBoard::getLeaders(){
    return leaders;
}
