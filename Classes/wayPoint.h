#pragma once

#include "cocos2d.h"

USING_NS_CC;
extern class GameLayer;


class wayPoint :
	public CCNode
{
public:
	wayPoint(void);
	~wayPoint(void);
	bool initWithLayer(GameLayer *gameLayer,CCPoint tempLocation);
	void draw();

public:
	GameLayer *_gameLayer;
	CCPoint _myPosition;
	wayPoint *nextWayPoint;


};

