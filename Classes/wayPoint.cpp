#include "wayPoint.h"

#include "GameLayer.h"
wayPoint::wayPoint(void)
{
}


wayPoint::~wayPoint(void)
{

}

bool wayPoint::initWithLayer(GameLayer *gameLayer,CCPoint tempLocation)
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCNode::create());

		_gameLayer=gameLayer;
		this->setPosition(CCPointZero);
		
		_myPosition=tempLocation;
		_gameLayer->addChild(this);

		
	} while (0);


	return bRet;
}

void wayPoint::draw()
{
	//glLineWidth(2);
	//ccDrawColor4F(0,255,0,255);
	//ccDrawCircle(_myPosition,6,360,30,false);
	//ccDrawCircle(_myPosition,3,360,30,false);
	//if(nextWayPoint){
	//	ccDrawLine(_myPosition,nextWayPoint->_myPosition);
	//}

}