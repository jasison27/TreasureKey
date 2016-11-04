#ifndef __EXAMPLE_LAYER_H__
#define __EXAMPLE_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class Example : public cocos2d::Layer
{
public:
	CREATE_FUNC(Example);
	static Example* createWithShape(int shape);
	virtual bool initWithShape(int shape);
	void removeFigure();
	void menuGoBackCallback(Ref* sender);
	std::vector <Vec2> getPoints();
	void update(float) override;
private:
	Label *tme;
	float tmeremain;
	DrawNode *drawNode;
	std::vector<Vec2> points;
	Menu *menu;
};

#endif
