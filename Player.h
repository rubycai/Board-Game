//
//  Player.h
//  Project 3
//
//  Created by Ruby on 5/10/14.
//  Copyright (c) 2014 Ruby. All rights reserved.
//

#ifndef __Project_3__Player__
#define __Project_3__Player__

#include <iostream>
#include "Side.h"
#include <string>

class Timer;
class Board;

class Player
{
public:
    Player(std::string name);
    std::string name() const;
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const = 0;
    virtual ~Player();
private:
    std::string m_name;
};

class HumanPlayer:public Player
{
public:
    HumanPlayer(std::string name);
    //virtual ~HumanPlayer();
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const;
};

class BadPlayer:public Player
{
public:
    BadPlayer(std::string name);
    //virtual ~BadPlayer();
    //virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const;
};

class SmartPlayer:public Player
{
public:
    SmartPlayer(std::string name);
    //virtual ~SmartPlayer();
    //virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const;
private:
    void evalMove(Side playerSide, const Board& b, int& bestHole, long& value, Timer timer) const;
};

#endif /* defined(__Project_3__Player__) */
