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

// ��ӭ���� ��ʼ������
bool gameover::init() {
	// �ȳ�ʼ�����࣬���ɹ�����false
	if (!Layer::init()) {
		return false;
	}


	// ��ӱ���ͼƬ
	auto sprite = Sprite::create("gameover.jpeg");
	sprite->setPosition(Point(800 / 2, 1200 / 2));
	sprite->setScale(3.0f);
	this->addChild(sprite);
	return true;
}