#pragma once
#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class WelcomeScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuStartCallback(Ref* pSender);
	CREATE_FUNC(WelcomeScene);
};

#endif // __WELCOME_SCENE_H__