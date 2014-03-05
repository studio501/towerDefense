#pragma once

#include "cocos2d.h"


USING_NS_CC;


class GameLayer :
	public CCLayer
{
public:

	GameLayer(void);
	~GameLayer(void);
	static CCScene *GameScene();
	virtual bool init();
	CREATE_FUNC(GameLayer);

public:
	virtual void registerWithTouchDispatcher(void);
	//virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	//virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	//virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

	//�������
	void loadTowerBase();
	bool canBuyTower();

	//���·��
	void addWayPoints();
	//�����ײ
	bool isCircleCollision(CCPoint firstPosition,int firstRadius,CCPoint secondPosition,int secondRadius);
	//����һ������
	bool loadWave();
	//�������
	void enemyGotKilled();
	void playerGetDamagedByEnemy();
	void doGameOver();
	void choseTowerMenu(CCObject *pSender);


public:
	int _wave;
	int _playerHp;
	int _gold;
	CCLabelBMFont *ui_hp_lbl;
	bool _gameEnded;
	CCLabelBMFont *ui_wave_lbl;
	CCLabelBMFont *ui_gameover_lbl;
	CCLabelBMFont *ui_wingame_lbl;
	CCLabelBMFont *ui_gold_lbl;
	bool _isTouchBase;

	CCArray *_towerBase;
	CCArray *_towers;
	CCArray *_wayPoints;
	CCArray *_enemies;
	
};

