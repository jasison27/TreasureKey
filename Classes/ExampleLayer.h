#ifndef EXAMPLE_LAYER_H__
#define EXAMPLE_LAYER_H__

#include "cocos2d.h"
#include "BasicScene.h"
USING_NS_CC;

class ExampleLayer : public Layer
{
public:
	CREATE_FUNC(ExampleLayer);
	static ExampleLayer* createWithThemeLevel(BasicScene* fa, int themen, int lev);
	virtual bool initWithThemeLevel(BasicScene* fa, int themen, int lev);
	void onSkipCallback(Ref* sender);
	void onSettingCallBack(Ref* sender);
	std::vector <Vec2> getPoints();
	void update(float) override;
	void resumeFromHelpLayer();
	bool onTouchBegan(Touch *touch, Event *event);
private:
	int theme, level;
	BasicScene * container;
	Label *tme;
	Sprite *timer;
	int countEffect;
	float remainingT;
	float totalT;
	int drawedpoint;
	int npoints;
	DrawNode *drawNode;
	std::vector<Vec2> points;
};

#endif
