#include "GameLayer.h"
#include "MyTower.h"
#include "wayPoint.h"
#include "Enemy.h"
#include "ChoseTower.h"


CCScene *GameLayer::GameScene()
{
	CCScene *pScene=NULL;
	do{

		pScene=CCScene::create();
		CC_BREAK_IF(!pScene);


		GameLayer *gameLayer=GameLayer::create();
		CC_BREAK_IF(!gameLayer);


		pScene->addChild(gameLayer);



	}while (0);


	return pScene;
}
GameLayer::GameLayer(void)
{
	_towerBase=CCArray::create();
	_towerBase->retain();

	_towers=CCArray::create();
	_towers->retain();
	_wayPoints=CCArray::create();
	_wayPoints->retain();

	_enemies=CCArray::create();
	_enemies->retain();
}


GameLayer::~GameLayer(void)
{
	CC_SAFE_RELEASE_NULL(_towerBase);
	CC_SAFE_RELEASE_NULL(_towers);
	CC_SAFE_RELEASE_NULL(_wayPoints);
	CC_SAFE_RELEASE_NULL(_enemies);
}


bool GameLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		setTouchEnabled(true);

		//设置背景
		CCSize winSize=CCDirector::sharedDirector()->getWinSize();

		CCSprite *background=CCSprite::create("Bg.png");
		background->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(background,0);
		//增加炮塔基底
		loadTowerBase();
		//画路径结点
		addWayPoints();

		ui_wave_lbl = CCLabelBMFont::create(CCString::createWithFormat("WAVE: %d",_wave)->getCString(),"font_red_14.fnt");
		
		ui_wave_lbl->setPosition(ccp(400,winSize.height-12));
		ui_wave_lbl->setAnchorPoint(ccp(0,0.5));
		this->addChild(ui_wave_lbl,10);
		_wave=0;
		loadWave();
		_playerHp=5;
		_gold=500;
		ui_hp_lbl = CCLabelBMFont::create(CCString::createWithFormat("HP: %d",_playerHp)->getCString(),"font_red_14.fnt");
		this->addChild(ui_hp_lbl,10);
		ui_hp_lbl->setPosition(ccp(35,winSize.height-12));
		ui_gold_lbl=CCLabelBMFont::create(CCString::createWithFormat("GOLD: %d",_gold)->getCString(),"font_red_14.fnt");
		ui_gold_lbl->setPosition(ccp(120,winSize.height-12));
		this->addChild(ui_gold_lbl);


		_isTouchBase=false;
		
		_gameEnded=false;

		bRet = true;


	} while (0);

	return bRet;
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{

	




}
void GameLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{

}
void GameLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it=pTouches->begin();
	CCTouch *touch=(CCTouch *) (*it);
	
	CCPoint location=touch->getLocation();

	CCObject *pObject=NULL;
	CCARRAY_FOREACH(_towerBase,pObject){
		CCSprite *tPos=(CCSprite *)pObject;
		CCSize size=tPos->getContentSize();
		CCRect rect=CCRectMake(tPos->getPositionX()-size.width/2,tPos->getPositionY()-size.height/2,size.width,size.height);
		CCRect rectTower1=CCRectMake(tPos->getPositionX()-size.width/2-50,tPos->getPositionY()-size.height/2-30,size.width,size.height);
		CCRect rectTower2=CCRectMake(tPos->getPositionX(),tPos->getPositionY()-size.height/2-30,size.width,size.height);
		CCRect rectTower3=CCRectMake(tPos->getPositionX()-size.width/2+50,tPos->getPositionY()-size.height/2-30,size.width,size.height);
		
		if(rect.containsPoint(location)&&!tPos->getUserData()){

			ChoseTower *chosTower=new ChoseTower;
			chosTower->init(this,tPos->getPosition());
			_isTouchBase=true;


			
			break;

		}else{

			_isTouchBase=false;
			this->removeChildByTag(5,true);
		}

	}


}
 void GameLayer::registerWithTouchDispatcher(void)
 {
	 CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
 }

 void GameLayer::loadTowerBase()
 {
	 CCString *plistPath=CCString::createWithFormat("TowersPosition.plist");
	 CCArray *towerPositions=CCArray::createWithContentsOfFile(plistPath->getCString());
	 CCObject *pObject=NULL;
	 CCARRAY_FOREACH(towerPositions,pObject){

		 CCDictionary *towerBasePos=(CCDictionary *)pObject;
		 CCSprite *towerBaseSprite=CCSprite::create("open_spot1.png");
		// float x=towerBasePos->objectForKey("x");
		 float x=((CCString *)towerBasePos->objectForKey("x"))->floatValue();
		 float y=((CCString *)towerBasePos->objectForKey("y"))->floatValue();
		 towerBaseSprite->setPosition(ccp(x,y));
		 _towerBase->addObject(towerBaseSprite);
		 this->addChild(towerBaseSprite);




	 }
 }
 void GameLayer::choseTowerMenu(CCObject *pSender)
 {
	 
	 //CCPoint *tempPoint=(CCPoint *)pSender;
	 //CCLOG("%f,%f",tempPoint->x,tempPoint->y);

	 



 }
 bool GameLayer::canBuyTower()
 {
	 if(_gold-TOWER_COST>=0)
		 return true;
	 return false;
 }

 void GameLayer::addWayPoints()
 {
	 
	 wayPoint * waypoint1=new wayPoint;
	 waypoint1->initWithLayer(this,ccp(420,35));
	 _wayPoints->addObject(waypoint1);
	 waypoint1->nextWayPoint=NULL;

	 wayPoint * waypoint2=new wayPoint;
	 waypoint2->initWithLayer(this,ccp(35,35));
	 _wayPoints->addObject(waypoint2);
	 waypoint2->nextWayPoint =waypoint1;
	 
	 wayPoint * waypoint3=new wayPoint;
	 waypoint3->initWithLayer(this,ccp(35,130));
	 _wayPoints->addObject(waypoint3);
	 waypoint3->nextWayPoint =waypoint2;

	 wayPoint * waypoint4=new wayPoint;
	 waypoint4->initWithLayer(this,ccp(445,130));
	 _wayPoints->addObject(waypoint4);
	 waypoint4->nextWayPoint =waypoint3;

	 wayPoint * waypoint5=new wayPoint;
	 waypoint5->initWithLayer(this,ccp(445,220));
	 _wayPoints->addObject(waypoint5);
	 waypoint5->nextWayPoint =waypoint4;

	 wayPoint * waypoint6=new wayPoint;
	 waypoint6->initWithLayer(this,ccp(-40,220));
	 _wayPoints->addObject(waypoint6);
	 waypoint6->nextWayPoint =waypoint5;
 }

 bool GameLayer::isCircleCollision(CCPoint firstPosition,int firstRadius,CCPoint secondPosition,int secondRadius)
 {
	 float xdif = firstPosition.x - secondPosition.x;
	 float ydif = firstPosition.y - secondPosition.y;

	 float distance = sqrt(xdif*xdif+ydif*ydif);

	 if(distance <= firstRadius+secondRadius) 
		 return true;

	 return false;
	 
 }

 bool GameLayer::loadWave()
 {
	 CCString *pListPath=CCString::createWithFormat("Waves.plist");
	 CCArray *waveData=CCArray::createWithContentsOfFile(pListPath->getCString());

	 if(_wave>=waveData->count()){
		 return false;
	 }
	 CCArray *currenData=CCArray::createWithArray((CCArray *)waveData->objectAtIndex(_wave));
	 CCObject *pObject=NULL;
	 CCARRAY_FOREACH(currenData,pObject){

		 CCDictionary *enemyData=(CCDictionary *)pObject;
		 Enemy *enemy=new Enemy;
		 enemy->initWithLayer(this);

		 _enemies->addObject(enemy);
		 enemy->schedule(schedule_selector(Enemy::doActive),((CCString *)enemyData->objectForKey("spawnTime"))->floatValue());


	 }
	 _wave++;
	 ui_wave_lbl->setCString(CCString::createWithFormat("WAVE: %d",_wave)->getCString());
	 return true;

 }
 void GameLayer::enemyGotKilled()
 {
	 if(_enemies->count()<=0){
		 if(!this->loadWave()){

			 CCDirector::sharedDirector()->replaceScene(CCTransitionSplitCols::create(1,GameLayer::GameScene()));
	 }

 }
 }

 void GameLayer::playerGetDamagedByEnemy()
 {
	 _playerHp--;
	 ui_hp_lbl->setString(CCString::createWithFormat("HP: %d",_playerHp)->getCString());
	 if (_playerHp <=0) {
		 this->doGameOver();
	 }
 }

 void GameLayer::doGameOver()
 {
	 if(!_gameEnded){
		 _gameEnded=true;

		 //this->pauseSchedulerAndActions();		 
		 

		 

		 CCDirector::sharedDirector()->replaceScene(CCTransitionRotoZoom::create(1,GameLayer::GameScene()));

	 }

 }