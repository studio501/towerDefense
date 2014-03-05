	#include "ChoseTower.h"
#include "GameLayer.h"
#include "MyTower.h"
ChoseTower::ChoseTower(void)
{
}


ChoseTower::~ChoseTower(void)
{
}

bool ChoseTower::init(GameLayer *gamelayer,CCPoint position)
{
	if(this){
		this->autorelease();
	}
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCNode::create());
		_gamelayer=gamelayer;

		_clickPosition=position;
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Items05-hd.plist");
		_towerInLuobo=CCSpriteBatchNode::create("Items05-hd.pvr.ccz");

		_choseTowerOne=CCMenuItemImage::create("tower.png","tower.png",this,menu_selector(ChoseTower::chosetower1));
		_choseTowerOne->setPosition(ccpAdd(ccp(-50,30),position));

		_choseTowerTwo=CCMenuItemImage::create("tower.png","tower.png",this,menu_selector(ChoseTower::chosetower2));
		_choseTowerTwo->setPosition(ccpAdd(ccp(0,30),position));

		_choseTowerThree=CCMenuItemImage::create("tower.png","tower.png",this,menu_selector(ChoseTower::chosetower3));
		_choseTowerThree->setPosition(ccpAdd(ccp(50,30),position));

		_chostower=CCMenu::create(_choseTowerOne,_choseTowerTwo,_choseTowerThree,NULL);
		_chostower->setPosition(CCPointZero);
		
		this->addChild(_chostower);
		_gamelayer->addChild(this,10,5);
		
		bRet=true;

	} while (0);

	return bRet;
}
void ChoseTower::chosetower1(CCObject *pSender){
	
	
	MyTower *tower=new MyTower;
	tower->initWithLayer(_gamelayer,_clickPosition);
	_gamelayer->_towers->addObject(tower);
	this->getParent()->removeChildByTag(5,true);

	
}

void ChoseTower::chosetower2(CCObject *pSender){

}

void ChoseTower::chosetower3(CCObject *pSender){

}
