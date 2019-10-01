#ifndef HUGEUPDATECOMMAND_H
#define HUGEUPDATECOMMAND_H

#include "command.h"

class HugeUpdateCommand : public Command{
public:
    HugeUpdateCommand();
    virtual ~HugeUpdateCommand() = default;
    virtual int update(bool paused, int direction, int player_colliding, int level);

private:
};

#endif // HUGEUPDATECOMMAND_H
