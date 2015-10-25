//
//  Side.h
//  Project 3
//
//  Created by Ruby on 5/10/14.
//  Copyright (c) 2014 Ruby. All rights reserved.
//

#ifndef __Project_3__Side__
#define __Project_3__Side__

#include <iostream>
class Player;
class Board;
enum Side { NORTH, SOUTH };

inline
Side opponent(Side s)
{
    return Side(1 - s);
}

//void evalMove(Side playerSide, const Board& b, int& bestHole, long& value, int& depth);
bool MovePossible (const Board& b, Side s);

#endif /* defined(__Project_3__Side__) */
