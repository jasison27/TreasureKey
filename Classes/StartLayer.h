#ifndef START_LAYER_H__
#define START_LAYER_H__

#include "cocos2d.h"
#include "BasicScene.h"
USING_NS_CC;

class StartLayer : public Layer
{
public:
	CREATE_FUNC(StartLayer);
	static StartLayer* createWithTime(BasicScene* fa, float dt);
	bool initWithTime(BasicScene* fa, float dt);
	void update(float dt) override;
private:
	BasicScene* container;
	float remainingT;
};

#endif
