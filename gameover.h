#pragma once


#include "cocos2d.h"
USING_NS_CC;

class gameover : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(gameover);
};

