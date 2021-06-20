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

// ��ӭ���� ��ʼ������
bool WelcomeScene::init() {
	// �ȳ�ʼ�����࣬���ɹ�����false
	if (!Layer::init()) {
		return false;
	}


	// ��ӱ���ͼƬ
	auto sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(Point(800 / 2, 1200 / 2));
	sprite->setScale(3.0f);
	this->addChild(sprite);

	// ��ӿ�ʼ��ť
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
	// ��ת����Ϸ����
	auto scene = StarSprite::createScene();
	Director::getInstance()->replaceScene(scene);
}