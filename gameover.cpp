#include "WelcomeScene.h"
#include"cocos2d.h"
#include"MyXiaoXiaoLe.h"
#include"gameover.h"
USING_NS_CC;

Scene* gameover::createScene() {
	auto scene = Scene::create();
	auto layer = gameover::create();
	scene->addChild(layer);
	return scene;
}

// 欢迎界面 初始化函数
bool gameover::init() {
	// 先初始化父类，不成功返回false
	if (!Layer::init()) {
		return false;
	}


	// 添加背景图片
	auto sprite = Sprite::create("gameover.jpeg");
	sprite->setPosition(Point(800 / 2, 1200 / 2));
	sprite->setScale(3.0f);
	this->addChild(sprite);
	return true;
}