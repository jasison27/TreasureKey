#ifndef __TOUCH_DRAW_LAYER_H__
#define __TOUCH_DRAW_LAYER_H__

#include "cocos2d.h"
#include "BasicScene.h"
#include <vector>
USING_NS_CC;

class TouchDrawLayer : public Layer
{
public:
	CREATE_FUNC(TouchDrawLayer);
	static TouchDrawLayer* createWithNothing(BasicScene* fa, std::vector<Vec2> &pts);
	bool initWithNothing(BasicScene* fa, std::vector<Vec2> &pts);
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
	void onCloseCallBack(Ref* pSender);
	void onDoneCallback(Ref *sender);
	void onSettingCallBack(Ref *sender);
	float calcSimilarity();
	void getRetry();
private:
	void calcPoints();
	BasicScene* container;
	Sprite* cursor;
	MenuItemImage *doneItem;
	MenuItemImage *closeItem;
	MenuItemImage *settingItem;
	Sprite *box;
	bool hint;
	float l, r, d, u;
	std::vector <Vec2> expoints;
	std::vector <Vec2> points;
	std::vector <Vec2> pointsTmp;
	std::vector <std::vector<Vec2> > pointsVec;
	DrawNode *drawNode;
	DrawNode *tmpDrawNode;
	DrawNode *exDrawNode;
};

#endif
