#pragma once

#include "cocos2d.h"

USING_NS_CC;


extern class GameLayer;
extern class wayPoint;
extern class MyTower;

#define AWARD_GOLD 50
class Enemy :
	public CCNode
{
public:
	Enemy(void);
	~Enemy(void);
	bool initWithLayer(GameLayer *gameLayer);
	void doActive(float dt);
	void getRemove();
	void update(float delta);
	void draw();
	void getAttacked(MyTower *attacker);
	void gotLostSight(MyTower *attacker);
	void getDamaged(int damage);



public:
	GameLayer *_gameLayer;
	CCSprite *_mySprite;
	CCPoint _myPosition;
	int _maxHp;
	int _currentHp;
	float _walkingSpeed;
	wayPoint *_destinationWaypoint;
	bool _active;
	CCArray *_attackBy;

};

