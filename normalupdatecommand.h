#ifndef NORMALUPDATECOMMAND_H
#define NORMALUPDATECOMMAND_H

#include "command.h"

class NormalUpdateCommand : public Command{
public:
    NormalUpdateCommand();
    virtual ~NormalUpdateCommand() = default;
    virtual int update(bool paused, int direction, int player_colliding, int level);

//    void resetEntity(int level);
//    void createFinishline(EmptyEntity *root, double start_x, unsigned int world_height, unsigned int world_width);
//    void createObstacles(EmptyEntity *root, std::vector<ObstacleConfig *> obstacle_data, unsigned int world_height, unsigned int world_width);

private:
};

#endif // NORMALUPDATECOMMAND_H
