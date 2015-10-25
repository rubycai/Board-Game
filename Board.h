//
//  Board.h
//  Project 3
//
//  Created by Ruby on 5/10/14.
//  Copyright (c) 2014 Ruby. All rights reserved.
//

#ifndef __Project_3__Board__
#define __Project_3__Board__

#include <iostream>
#include "Side.h"

class Board
{
public:
    Board(int nHoles, int nInitialBeansPerHole);
    Board(const Board& other);
    ~Board();
    int holes() const;
    int beans(Side s, int hole) const;
    int beansInPlay(Side s) const;
    int totalBeans() const;
    bool sow(Side s, int hole, Side& endSide, int& endHole);
    bool moveToPot(Side s, int hole, Side potOwner);
    bool setBeans(Side s, int hole, int beans);
private:
    int* m_Hole[2];
    int m_nHolesPerSide;
};

#endif /* defined(__Project_3__Board__) */
