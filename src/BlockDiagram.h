#ifndef BLOCKDIAGRAM_H
#define BLOCKDIAGRAM_H

#include "Block.h"

class BlockDiagram
{
public:
    BlockDiagram();
    BlockDiagram(std::vector<Block*> &new_chain);

private:
    std::vector<Block *> chain;
};

#endif // BLOCKDIAGRAM_H
