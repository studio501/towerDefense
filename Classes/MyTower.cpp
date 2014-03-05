#include "MyTower.h"

#include "GameLayer.h"
#include "Enemy.h"
MyTower::MyTower(void)
{
}


MyTower::~MyTower(void)
{
}

bool MyTower::initWithLayer(GameLayer *gamelayerFormLayer,CCPoint location)
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCNode::create());
		_gameLayer=gamelayerFormLayer;
		_attackRange = 70;
		_damage = 8;
		_fireRate = 0.5;

		//CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("NT3_CN.png")->getCString());
		//_towerSprite=CCSprite::createWithSpriteFrame(frame);
		_towerSprite=CCSprite::create("tower.png");
		_towerSprite->setPosition(location);
		this->addChild(_towerSprite);
		_gameLayer->addChild(this);
		this->scheduleUpdate();

		_attacking=false;
		_chosenEnemy=NULL;



		bRet=true;


	} while (0);
	return bRet;
}

void MyTower::draw()
{
	//ccDrawColor4F(255, 255, 255, 255);
	//ccDrawCircle(_towerSprite->getPosition(), _attackRange, 360, 30, false);
}


void MyTower::update(float dt)
{
	if(_chosenEnemy){
		CCPoint normalized = ccpNormalize(ccp(_chosenEnemy->_mySprite->getPositionX()-_towerSprite->getPositionX(),_chosenEnemy->_mySprite->getPositionY()-_towerSprite->getPositionY()));
		_towerSprite->setRotation (CC_RADIANS_TO_DEGREES(atan2(normalized.y,-normalized.x))+90);
		if(!_gameLayer->isCircleCollision(_towerSprite->getPosition(),_attackRange,_chosenEnemy->_mySprite->getPosition(),1)){
			this->lostSightOfEnemy();
		}
	
		
	}else{
		CCObject *pObject=NULL;
		CCARRAY_FOREACH(_gameLayer->_enemies,pObject){
			Enemy *enemy=(Enemy *)pObject;
			if(_gameLayer->isCircleCollision(_towerSprite->getPosition(),_attackRange,enemy->_mySprite->getPosition(),1)){
				this->chosenEnemyForAttack(enemy);
				break;
			}
		}
	}
}




void MyTower::targetKilled()
{
	if(_chosenEnemy){
		_chosenEnemy=NULL;
	}
	this->unschedule(schedule_selector(MyTower::shootWeapon));
		
}

void MyTower::attackEnemy()
{
	this->schedule(schedule_selector(MyTower::shootWeapon),_fireRate);
}

void MyTower::shootWeapon(float dt)
{
	//


	CCSprite *bullet=CCSprite::create("bullet.png");
	bullet->setPosition(this->_towerSprite->getPosition());
	_gameLayer->addChild(bullet);
	CCMoveTo *moveto=CCMoveTo::create(0.1,_chosenEnemy->_mySprite->getPosition());
	CCCallFunc *effect=CCCallFunc::create(this,callfunc_selector(MyTower::damageEnemy));
	CCCallFuncO *shootBullet=CCCallFuncO::create(this,callfuncO_selector(MyTower::removeBullet),bullet);
	
	bullet->runAction(CCSequence::create(moveto,effect,shootBullet,NULL));
	
	

}

void MyTower::chosenEnemyForAttack(Enemy *enemy)
{

	_chosenEnemy = NULL;
	_chosenEnemy = enemy;
	this->attackEnemy();
	enemy->getAttacked(this);

}

void MyTower::removeBullet(CCObject *pSender)
{
	CCSprite *bullet=(CCSprite *)pSender;
	bullet->getParent()->removeChild(bullet,true);


}

void MyTower::damageEnemy()
{
	//this->unschedule(schedule_selector(MyTower::damageEnemy));
	//this->unschedule(schedule_selector(MyTower::shootWeapon));
	if(_chosenEnemy)
		_chosenEnemy->getDamaged(_damage);
	
}


void MyTower::lostSightOfEnemy()
{
	_chosenEnemy->gotLostSight(this);
	if(_chosenEnemy)
		_chosenEnemy =NULL; 

	this->unschedule(schedule_selector(MyTower::shootWeapon));

}