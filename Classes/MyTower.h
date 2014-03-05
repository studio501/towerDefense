#pragma once

#include "cocos2d.h"

USING_NS_CC;
extern class GameLayer;
extern class Enemy;
#define TOWER_COST 100
class MyTower :
	public CCNode
{
public:
	MyTower(void);
	~MyTower(void);
	//用gamelayer对象实例和位置创建一个炮塔
	bool initWithLayer(GameLayer *gamelayer,CCPoint location);
	void update(float dt);
	void draw();
	
	void attackEnemy();

	void shootWeapon(float dt);
	void chosenEnemyForAttack(Enemy *enemy);
	void removeBullet(CCObject *pSender);
	void damageEnemy();
	void targetKilled();
	void lostSightOfEnemy();

public:
	GameLayer *_gameLayer;
	int _attackRange;
	int _damage;
	float _fireRate;
	CCSprite *_towerSprite;
	bool _attacking;
	Enemy *_chosenEnemy;


};

