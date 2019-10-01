#ifndef CONFIGSTAGE3_H
#define CONFIGSTAGE3_H

#include <vector>

#include "config.h"
#include "configuration.h"

class ConfigStage3 : public Configuration {
public:
    ConfigStage3(Config& config);
    ~ConfigStage3() override;

    virtual unsigned int getWorldWidth() override;
    virtual unsigned int getWorldHeight() override;
    virtual std::vector<ObstacleConfig*> getObstacleData() override;
    virtual std::vector<ObstacleConfig*> getLevelObstacleData(int level);

    int getLive();

protected:
    virtual void setupConfig() override;
    virtual void setupObstacle(QString element, std::vector<ObstacleConfig*>* obstacle_data);

private:
    Config& config;
    std::vector<ObstacleConfig*> level1obstacle_data;
    std::vector<ObstacleConfig*> level2obstacle_data;
    std::vector<ObstacleConfig*> level3obstacle_data;
    int life;
};

#endif // CONFIGSTAGE3_H
