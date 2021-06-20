#include<string>
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include"cocos2d.h"
#include"MyXiaoXiaoLe.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define schedule_selector(_SELECTOR) static_cast<cocos2d::SEL_SCHEDULE>(&_SELECTOR)
#include "ui/CocosGUI.h"//ʹ��UI�ؼ����������ͷ�ļ�
using namespace cocos2d::ui;
#include "AudioEngine.h"//�������ſ�
USING_NS_CC;
using namespace std;

bool StarSprite::isright()//�ж����ɵ��ǲ��ǲ���������
{
	for (int x = 2; x < 11; x++)
	{
		for (int y = 2; y < 14; y++)
		{
			if (types[x - 2][y] == types[x - 1][y] && types[x - 2][y] == types[x][y])
				return false;
			if (types[x - 1][y] == types[x][y] && types[x - 1][y] == types[x + 1][y])
				return false;
			if (types[x][y] == types[x + 1][y] && types[x][y] == types[x + 2][y])
				return false;
			if (types[x][y - 2] == types[x][y - 1] && types[x][y - 2] == types[x][y])
				return false;
			if (types[x][y - 1] == types[x][y] && types[x][y - 1] == types[x][y + 1])
				return false;
			if (types[x][y] == types[x][y + 1] && types[x][y] == types[x][y + 2])
				return false;
		}
	}
	return true;
}

Scene* StarSprite::createScene()
{
	auto scene = Scene::create();
	auto layer = StarSprite::create();
	scene->addChild(layer);
	return scene;
}


StarSprite* StarSprite::createStar(int type, float x, float y)
{
	StarSprite* star = new StarSprite();
	if (star && star->init())
	{
		star->autorelease();
		star->StarInit(type, x, y);
		return star;
	}
	CC_SAFE_DELETE(star);//ʹ��delete������ɾ��һ���������ΪNULL���򲻽��в���
	return 0;
}

bool StarSprite::init()
{
	if (!Layer::init())
	{
		return false;
	}
	steps = 10;
	scores = 0;
	Size size = Director::getInstance()->getVisibleSize();
	auto* background = Sprite::create("background.png");
	background->setPosition(size.width / 2, size.height / 2);
	background->setScale(1.7f);
	addChild(background, 0);
	srand((unsigned)time(NULL));
	bool isok = false;
	while (!isok)
	{
		for (int x = COLSMIN; x < COLSMAX; x++)
		{
			for (int y = ROWSMIN; y < ROWSMAX; y++)
			{
				type = 1 + rand() % 5;
				types[x][y] = type;
			}
			
		}
		isok = isright();
	}

	for (int x = COLSMIN; x < COLSMAX; x++)
	{
		for (int y = ROWSMIN; y < ROWSMAX; y++)
		{
			StarInit(types[x][y], x, y);
		}

	}
	auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��Ļ�ߴ�
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ȡ����ԭ��
	//����Ļ����ʾָ��
	Sprite* mouse = Sprite::create("mouse.jpg");
	mouse->setScale(0.3f);
	this->addChild(mouse);
	auto myMouseListener = EventListenerMouse::create();//����ʱ���������������¼�
	
	myMouseListener->onMouseMove = [=](Event* event)//������ƶ�ʱ
	{
		EventMouse* e = (EventMouse*)event;
		mouse->setPosition(e->getCursorX(), e->getCursorY());
		isTouchEnable = true;
		checkAndRemoveSprite();
		FillSprite();
		isTouchEnable = true;
	};
	myMouseListener->onMouseDown = [=](Event* event)//�������ʱ
	{
		if (isTouchEnable)
		{
			static int t = 0;
			EventMouse* e = (EventMouse*)event;
			log("%f %f %d", e->getCursorX(), e->getCursorY(),types[int((e->getCursorX() + 111) / 80)][int((e->getCursorY() + 20) / 80)]);
			end.x = 0;
			end.y = 0;
			if (int((e->getCursorX() + 111) / 80) >= COLSMIN && int((e->getCursorX() + 111) / 80) < COLSMAX
				&& int((e->getCursorY() + 20) / 80) >= ROWSMIN && int((e->getCursorY() + 20) / 80) < ROWSMAX)
			{
				if (t == 0)
				{
					start.x = int((e->getCursorX() + 111) / 80);
					start.y = int((e->getCursorY() + 20) / 80);
				}
				else
				{
					end.x = int((e->getCursorX() + 111) / 80);
					end.y = int((e->getCursorY() + 20) / 80);

					if (start.x == end.x && start.y == end.y)//���ε����һ���ط�
					{
						if (types[start.x][start.y] > 5)
						{
							if (types[start.x][start.y] == 6)//����˱�ը���
								xingxing6(start.x, start.y);
							if (types[start.x][start.y] == 7)//������һ����
								xingxing7(start.x, start.y);
							if (types[start.x][start.y] == 8)//������һ����
								xingxing8(start.x, start.y);
							start.x = 0; start.y = 0;//���˫�����������ǣ���������Ч����������洢��λ��
							end.x = 0; end.y = 0;
						}
					}
					if (start.x + start.y - end.x - end.y == 1 || end.x + end.y - start.x - start.y == 1)//��������ڵ�λ��
					{
						bool isswap=swapstar();//������ڣ����Խ���,��������������洢��λ�ò�Ȼ���±��start
						if (isswap)
						{
							start.x = 0;
							start.y = 0;
							end.x = 0;
							end.y = 0;
							steps--;
						}
					}
					start = end;
					end.x = 0;
					end.y = 0;
					
				}				
				t++;
			}
			isTouchEnable = true;
			checkAndRemoveSprite();
			FillSprite();
			isTouchEnable = true;
			mouse->setScale(0.2f);
		}
	};
	myMouseListener->onMouseUp = [=](Event* event)//������ɿ�ʱ
	{
		mouse->setScale(0.3f);
		isTouchEnable = true;
		checkAndRemoveSprite();
		FillSprite();
		isTouchEnable = true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, this);
	isAction = false;
	isTouchEnable = true;
	return true;
}

void StarSprite::xingxing6(int inx, int iny)//��ը
{
	int x, y;
	int xm, ym;
	types[inx][iny] = 0;
	if (inx >= 4 && iny < 9)
	{
		x = inx - 2;
		xm = inx + 2;
	}
	if (inx < 4)
	{
		x = 2;
		xm = inx + 2;
	}
	if (inx >= 9)
	{
		x = inx - 2;
		xm = 10;
	}
	if (iny >= 4 && iny < 12)
	{
		y = iny - 2;
		ym = iny + 2;
	}
	if (iny < 4)
	{
		y = 2;
		ym = iny + 2;
	}
	if (iny >= 12)
	{
		y = iny - 2;
		ym = 13;
	}
	for (int xx = x; xx <= xm; xx++)
	{
		for (int yy = y; yy <= ym; yy++)
		{
			if(types[xx][yy] <=5)
				types[xx][yy] = 0;
			else 
			{
				if (types[xx][yy] == 6)
					xingxing6(xx, yy);
				if (types[xx][yy] == 7)
					xingxing7(xx, yy);
				if (types[xx][yy] == 8)
					xingxing8(xx, yy);
			}
		}
	}

}

void StarSprite::xingxing7(int inx, int iny)//����һ��
{
	types[inx][iny] = 0;
	for (int x = COLSMIN; x <= COLSMAX; x++)
	{
		if (types[x][iny] <= 5 || types[x][iny] == 7)
			types[x][iny] = 0;
		else
		{
			if (types[x][iny] == 6)
				xingxing6(x, iny);
			if (types[x][iny] == 8)
				xingxing8(x, iny);
		}
	}
}

void StarSprite::xingxing8(int inx, int iny)//����һ��
{
	types[inx][iny] = 0;
	for (int y = ROWSMIN; y <= ROWSMAX; y++)
	{
		if(types[inx][y]<=5|| types[inx][y]==8)
			types[inx][y] = 0;
		else
		{
			if (types[inx][y] == 6)
				xingxing6(inx, y);
			if (types[inx][y] == 7)
				xingxing7(inx, y);
		}
	}
}

void StarSprite::checkAndRemoveSprite()//�ж��Ƿ��п����Ƴ����ǹ�
{
	for (int r = ROWSMIN; r < ROWSMAX; r++)
		for (int c = COLSMIN; c < COLSMAX; c++)
		{
			if (types[c][r]==0)
				continue;
			//�ȱ����������ڵ��ǹ�������ͬ���ǹ��ŵ�һ��list��
			point p = { c,r };
			std::list<point>colChainList;
			getColChain(p, colChainList);
			std::list<point>RowChainList;
			getRowChain(p, RowChainList);

			std::list<point>::iterator it;
			std::list<point>::iterator rowit;

			if ((colChainList.size()==3&& RowChainList.size()==3
				&&colChainList.size() + RowChainList.size() == 6)
				|| (colChainList.size()==5&& RowChainList.size()==1)
				|| (RowChainList.size()==5 && colChainList.size()==1)
				|| colChainList.size() + RowChainList.size()==8)//�����һ�����ɱ�ը��
			{
				for (it = colChainList.begin(); it != colChainList.end(); it++)
				{
					p = (point)*it;
					if (it == colChainList.begin()) 
						types[c][r] = 6;
					else {
						if (types[p.x][p.y] <= 5)
							types[p.x][p.y] = 0;
					}
				}
				for (rowit = RowChainList.begin(); rowit != RowChainList.end(); rowit++)
				{
					p = (point)*rowit;
					
					if (types[p.x][p.y] <= 5)
						types[p.x][p.y] = 0;
				}
			}
			if (colChainList.size() == 4 || RowChainList.size() == 4)
			{
				if (colChainList.size() == 4)//һ���ĸ�����������һ��
				{
					for (it = colChainList.begin(); it != colChainList.end(); it++)
					{
						p = (point)*it;
						if (it == colChainList.begin())
							types[c][r] = 7;
						else if (types[p.x][p.y] <= 5)
							types[p.x][p.y] = 0;
					}
				}
				if (RowChainList.size() == 4)//һ���ĸ�����������һ��
				{
					for (rowit = RowChainList.begin(); rowit != RowChainList.end(); rowit++)
					{
						p = (point)*rowit;
						if (rowit == RowChainList.begin())
							types[p.x][p.y] = 8;
						else if (types[p.x][p.y] <= 5)
							types[p.x][p.y] = 0;
					}
				}
			}
			if (colChainList.size() == 3 || RowChainList.size() == 3)
			{
				if (colChainList.size() == 3)//���һ������
				{

					for (it = colChainList.begin(); it != colChainList.end(); it++)
					{
						p = (point) *it;
						if (types[p.x][p.y] <= 5)
							types[p.x][p.y] = 0;
					}
				}
				if (RowChainList.size() == 3)//���һ������
				{
					for (rowit = RowChainList.begin(); rowit != RowChainList.end(); rowit++)
					{
						p = (point)*rowit;
						if (types[p.x][p.y] <= 5)
							types[p.x][p.y] = 0;
					}
				}
			}

		}
	removeSprite();
}

void StarSprite::removeSprite()//�Ƴ��յ����Ǻ�������������
{
	int t = 0;
	for (int c = COLSMIN; c < COLSMAX; c++)
	{
		for (int r = ROWSMIN; r < ROWSMAX; r++)
		{
			if (types[c][r] < 1 || types[c][r]>5)//�����յĺ�������������
			{
				scores++;
				SpriteRemoveAction(c, r);
			}
		}
	}
}

void StarSprite::SpriteRemoveAction(int x,int y)//������ʧ�Ķ���
{
	isAction = true;
	isTouchEnable = false;
	auto pFadeIn = FadeOut::create(1);
	auto pRotateBy = RotateBy::create(0.6f, 180);//˳ʱ����ת30��
	auto pScaleBy = ScaleBy::create(0.6f, 0.5f);
	map[x][y]->runAction(Spawn::create(pFadeIn, pRotateBy, pScaleBy, nullptr));
	if (types[x][y] >= 6)
	{
		char s[20];
		sprintf(s, "xingxing%d.png", types[x][y]);
		map[x][y] = Sprite::create(s);
		map[x][y]->setScale(1.5f);
		map[x][y]->setPosition(80 * x - 80, 20 + 80 * y);
		addChild(map[x][y]);
	}
}

void StarSprite::FillSprite()//���������ȱ��λ����ȥ���¼���
{
	int colRemoveNumber[9] = { 0 };
	for (int c = COLSMIN; c < COLSMAX; c++)
	{
		int removeSpriteOfCol = 0;
		for (int r = ROWSMIN; r < ROWSMAX; r++)//�������ϱ���
		{
			if (types[c][r] == 0)
			{
				removeSpriteOfCol++;
				log("%d %d",c, r);
			}

			else if (removeSpriteOfCol > 0)
			{
				//����������
				
				int newRow = r - removeSpriteOfCol;//�����������յģ�ԭ����5�еľ�Ҫ��3��ȥ
				log("%d %d %d %d", c, r, removeSpriteOfCol, newRow);
				auto move = MoveTo::create(0.2f, Vec2(float(80 * int(c) - 80), float(20 + 80 * int(newRow))));
				map[c][r]->runAction(move);
				types[c][newRow] = types[c][r];
				types[c][r] = 0;
				log("%d %d", 80 * int(c) - 80, 20 + 80 * int(newRow));
				
			//	map[c][r]->runAction(MoveTo::create(0.2f, Vec2(80 * int(c) - 80, 20 + 80 * r)));
			//	map[c][r]->runAction(MoveTo::create(0.2f, Vec2(80 * int(c) - 80, 20 + 80 * int(newRow))));
				Sprite* pi = map[c][r];
				map[c][r] = map[c][newRow];
				map[c][newRow] = pi;
			}
				
		}
		colRemoveNumber[c-COLSMIN] = removeSpriteOfCol;//��¼��ÿһ�еĿ�����
	}
	for (int c = COLSMIN; c < COLSMAX; c++)	//��䶥���ĿյĲ���
	{
		for (int r = ROWSMAX - colRemoveNumber[c-COLSMIN]; r < ROWSMAX; r++)
		{
			types[c][r]= 1 + rand() % 5;
			StarInit(types[c][r], c, r);
		}
	}
}

bool StarSprite::swapstar()//���Խ�������ѡ�е����ڵ�����
{
	isTouchEnable = false;
	float time = 0.2;

	int typess = types[start.x][start.y];//��������
	types[start.x][start.y] = types[end.x][end.y];
	types[end.x][end.y]= typess;

	std::list<point>colChainListOfFirst;
	getColChain(start, colChainListOfFirst);
	std::list<point>rowChainListOfFirst;
	getRowChain(start, rowChainListOfFirst);
	std::list<point>colChainListOfSecond;
	getColChain(end, colChainListOfSecond);
	std::list<point>rowChainListOfSecond;
	getRowChain(end, rowChainListOfSecond);
	log("%d %d %d %d", colChainListOfFirst.size(), rowChainListOfFirst.size(),
		colChainListOfSecond.size(), rowChainListOfSecond.size());
	 if (colChainListOfFirst.size() >= 3
		|| rowChainListOfFirst.size() >= 3
		|| colChainListOfSecond.size() >= 3
		|| rowChainListOfSecond.size() >= 3)//��ͨ����
		{
			//�ƶ�
		 auto move1 = MoveTo::create(time, Vec2(float(80 * int(start.x)) - 80, float(20 + 80 * int(start.y))));
		map[end.x][end.y]->runAction(move1);
		auto move2 = MoveTo::create(time, Vec2(float(80 * int(end.x) - 80), float(20 + 80 * int(end.y))));
		map[start.x][start.y]->runAction(move2);
		Sprite* pi = map[end.x][end.y];
		map[end.x][end.y] = map[start.x][start.y];
		map[start.x][start.y] = pi;
		return true;

		}
	else {
		int typess = types[start.x][start.y];
		types[start.x][start.y] = types[end.x][end.y];
		types[end.x][end.y] = typess;
		types[end.x][end.y] = typess;
		return false;
	}
	
}

void StarSprite::getRowChain(point p, std::list<point>& chainList)//�жϸ��еĸ�������ͬ������
{
	chainList.push_back(p);
	//����
	int neiborRow = p.y - 1;
	while (neiborRow >= ROWSMIN)
	{
		point neibor{ p.x,neiborRow };
		if (types[p.x][neiborRow]==types[p.x][p.y])
		{
			chainList.push_back(neibor);
			neiborRow--;
		}
		else
			break;
	}

	//����
	neiborRow = p.y + 1;
	while (neiborRow < ROWSMAX)
	{
		point neibor{ p.x,neiborRow };
		if (types[p.x][neiborRow] == types[p.x][p.y])
		{
			chainList.push_back(neibor);
			neiborRow++;
		}
		else
			break;
	}
}

void StarSprite::getColChain(point p, std::list<point>& chainList)//�жϸ��еĸ�������ͬ������
{
	chainList.push_back(p);
	//����
	int neiborCol = p.x - 1;
	while (neiborCol >= COLSMIN)
	{
		point neibor{ neiborCol ,p.y };
		if (types[neiborCol][p.y] == types[p.x][p.y])
		{
			chainList.push_back(neibor);
			neiborCol--;
		}
		else
			break;
	}

	//����
	neiborCol = p.x + 1;
	while (neiborCol < COLSMAX)
	{
		point neibor{ neiborCol,p.y };
		if (types[neiborCol][p.y] == types[p.x][p.y])
		{
			chainList.push_back(neibor);
			neiborCol++;
		}
		else
			break;
	}
}

void StarSprite::StarInit(int type, int x, int y)//��ʼ���ʼ������
{
	char s[20];
	sprintf(s, "xingxing%d.png", type);
	auto star = Sprite::create(s);
	map[x][y] = star;
	if (type != 0)
	star->setScale(1.5f);
	star->setPosition(80 * x - 80, 20 + 80 * y);
	addChild(star);
}
