#include "WelcomeScene.h"
#include"cocos2d.h"
#include"MyXiaoXiaoLe.h"
USING_NS_CC;

Scene* WelcomeScene::createScene() {
	auto scene = Scene::create();
	auto layer = WelcomeScene::create();
	scene->addChild(layer);
	return scene;
}

// 欢迎界面 初始化函数
bool WelcomeScene::init() {
	// 先初始化父类，不成功返回false
	if (!Layer::init()) {
		return false;
	}


	// 添加背景图片
	auto sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(Point(800 / 2, 1200 / 2));
	sprite->setScale(3.0f);
	this->addChild(sprite);

	// 添加开始按钮
	auto startItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(WelcomeScene::menuStartCallback, this));

	startItem->setPosition(Vec2(800 / 2, 1200 / 8));



	auto menu = Menu::create(startItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

void WelcomeScene::menuStartCallback(Ref* pSender)
{
	// 跳转到游戏界面
	auto scene = StarSprite::createScene();
	Director::getInstance()->replaceScene(scene);
}