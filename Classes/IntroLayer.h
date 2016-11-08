#ifndef INTRO_LAYER_H__
#define INTRO_LAYER_H__

#include "cocos2d.h"
#include "BasicScene.h"
USING_NS_CC;

class IntroLayer : public Layer
{
public:
	CREATE_FUNC(IntroLayer);
	static IntroLayer* createWithTime(BasicScene* fa, float dt);
	void onSettingCallBack(Ref* ref);
	bool initWithTime(BasicScene* fa, float dt);
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
	void update(float dt) override;
	void finish();
private:
	BasicScene* container;
	Label* text;
	int textn;
	int totaln;
	float duration;
	float remainingT;
};

#endif
