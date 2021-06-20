#pragma once
#include"cocos2d.h"
USING_NS_CC;

#define COLSMIN 2
#define COLSMAX 11
#define ROWSMIN 2
#define ROWSMAX 14
#define SPRITE_WIDTH 105

class point
{
public:
	int x;
	int y;
};

class StarSprite : public cocos2d::Layer
{
public:
	int type;//��������
	Sprite* star;
	Sprite* map[13][16];
	int types[13][16] = { 0 };
	static cocos2d::Scene* createScene();
	point start;
	point end;
	bool isright();
	static StarSprite* createStar(int type,float x,float y);
	void StarInit(int type, int x, int y);
	bool swapstar();
	void checkAndRemoveSprite();
	void removeSprite();
	void StarSprite::SpriteRemoveAction(int x, int y);
	virtual bool init();
	void getRowChain(point p, std::list<point>& chainList);
	void getColChain(point p, std::list<point>& chainList);
	bool isAction;//��ʾ�Ƿ�����ִ�ж���
	bool isTouchEnable;//�Ƿ��ܹ����
	void xingxing6(int x, int y);
	void xingxing7(int x, int y);
	void xingxing8(int x, int y);
	int steps = 10;
	int scores = 0;
	CREATE_FUNC(StarSprite);
	void FillSprite();
};


