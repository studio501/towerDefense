#include "Enemy.h"
#include "GameLayer.h"

#include "wayPoint.h"
#include "MyTower.h"
Enemy::Enemy(void)
{
	_attackBy=CCArray::create();
	_attackBy->retain();
}


Enemy::~Enemy(void)
{
	CC_SAFE_RELEASE_NULL(_attackBy);
}

bool Enemy::initWithLayer(GameLayer *gameLayer)
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCNode::create());
		_gameLayer=gameLayer;
		_maxHp = 40;
		_currentHp = _maxHp;

		_active = false;

		_walkingSpeed = 1;

		_mySprite = CCSprite::create("enemy.png");
		this->addChild(_mySprite);

		wayPoint * waypoint = (wayPoint *)(_gameLayer->_wayPoints->objectAtIndex(_gameLayer->_wayPoints->count()-1));

		_destinationWaypoint = waypoint->nextWayPoint;

		CCPoint pos = waypoint->_myPosition;
		_myPosition = pos;

		_mySprite->setPosition(pos);

		_gameLayer->addChild(this);

		this->scheduleUpdate();
		bRet=true;

	} while (0);
	return bRet;

}

void Enemy::doActive(float dt)
{
	this->unschedule(schedule_selector(Enemy::doActive));
	_active=true;
}

void Enemy::update(float delta)
{
	
	if(!_active) return;

	//if([theGame circle:myPosition withRadius:1 collisionWithCircle:destinationWaypoint.myPosition collisionCircleRadius:1])
	if(_gameLayer->isCircleCollision(_myPosition,1,_destinationWaypoint->_myPosition,1))
	{
		if(_destinationWaypoint->nextWayPoint)
		{
			_destinationWaypoint = _destinationWaypoint->nextWayPoint;
		}else
		{
			//Reached the end of the road. Damage the player
			_gameLayer->playerGetDamagedByEnemy();
			this->getRemove();
		}
	}

	CCPoint targetPoint = _destinationWaypoint->_myPosition;
	float movementSpeed = _walkingSpeed;

	CCPoint normalized = ccpNormalize(ccp(targetPoint.x-_myPosition.x,targetPoint.y-_myPosition.y));
	_mySprite->setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y,-normalized.x)));

	_myPosition = ccp(_myPosition.x+normalized.x * movementSpeed,_myPosition.y+normalized.y * movementSpeed);

	_mySprite->setPosition(_myPosition);
	if(_currentHp<=0){
		this->getRemove();
	}
}

void Enemy::getRemove()
{
	_gameLayer->_gold+=AWARD_GOLD;
	_gameLayer->ui_gold_lbl->setCString(CCString::createWithFormat("GOLD :%d",_gameLayer->_gold)->getCString());

	CCObject *pObject=NULL;
	CCARRAY_FOREACH(_attackBy,pObject){
		MyTower *attacker=(MyTower *)pObject;
		attacker->targetKilled();
	}
	this->getParent()->removeChild(this,true);
	_gameLayer->_enemies->removeObject(this);

	//Notify the game that we killed an enemy so we can check if we can send another wave
	_gameLayer->enemyGotKilled();
}

void Enemy::draw()
{
	float spWidth = 20;
	ccDrawSolidRect(ccp(_mySprite->getPositionX()-spWidth,_mySprite->getPositionY()+20),ccp(_mySprite->getPositionX()-spWidth+_currentHp,_mySprite->getPositionY()+20+5),ccc4f(255,0,0,0.5));
	ccDrawColor4F(0,255,0,0);
	ccDrawRect(ccp(_mySprite->getPositionX()-spWidth,_mySprite->getPositionY()+20),ccp(_mySprite->getPositionX()+spWidth,_mySprite->getPositionY()+20+5));

}

void Enemy::getAttacked(MyTower *attacker)
{
	_attackBy->addObject(attacker);


}
void Enemy::gotLostSight(MyTower *attacker)
{
	_attackBy->removeObject(attacker);
}
void Enemy::getDamaged(int damage)
{
	_currentHp-=damage;

}