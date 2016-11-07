#ifndef __TOUCH_DRAW_LAYER_H__
#define __TOUCH_DRAW_LAYER_H__

#include "cocos2d.h"
#include "BasicScene.h"
USING_NS_CC;

class TouchDrawLayer : public Layer
{
public:
	CREATE_FUNC(TouchDrawLayer);
	static TouchDrawLayer* createWithNothing(BasicScene* fa);
	bool initWithNothing(BasicScene* fa);
	std::vector <Vec2> getPoints();
	void menuExitCallback(Ref* pSender);
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
	void menuFinishCallback(Ref *sender);
private:
	BasicScene* container;
	Sprite* cursor;
	MenuItemImage *finishItem;
	MenuItemImage *closeItem;
	Sprite *box;
	float l, r, d, u;
	std::vector<Vec2> points;
	std::vector <Vec2> pointsTmp;
	std::vector <std::vector<Vec2> > pointsVec;
	DrawNode *drawNode;
	DrawNode *tmpDrawNode;
};

#endif
