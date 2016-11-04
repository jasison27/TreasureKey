#ifndef __TOUCH_DRAW_LAYER_H__
#define __TOUCH_DRAW_LAYER_H__

#include "cocos2d.h"
#include "GameScene.h"
USING_NS_CC;
class Game;

class TouchDraw : public cocos2d::Layer
{
public:
	CREATE_FUNC(TouchDraw);
	static TouchDraw* createWithScene(Game *gS);
	bool initWithScene(Game *gS);
	std::vector <Vec2> getPoints();
	void menuExitCallback(cocos2d::Ref* pSender);
private:
	Sprite* cursor;
	MenuItemImage *finishItem;
	MenuItemImage *closeItem;
	Sprite *box;
	float l, r, d, u;
	std::vector<Vec2> points;
	void menuFinishCallback(Ref *sender);
	Game *gameScene;
	std::vector <Vec2> pointsTmp;
	std::vector <std::vector<Vec2> > pointsVec;
	DrawNode *drawNode;
	DrawNode *tmpDrawNode;
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
};

#endif
