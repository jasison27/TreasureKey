#ifndef START_LAYER_H__
#define START_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class StartLayer : public Layer
{
public:
	CREATE_FUNC(StartLayer);
	StartLayer* createWithTime(float dt);
	bool initWithTime(float dt);
	void update(float dt) override;
private:
	float remainingT;
};

#endif
