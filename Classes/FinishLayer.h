#ifndef FINISH_LAYER_H__
#define FINISH_LAYER_H__

#include "cocos2d.h"
#include "BasicScene.h"
USING_NS_CC;

class FinishLayer : public Layer
{
public:
	CREATE_FUNC(FinishLayer);
	static FinishLayer* createWithScore(BasicScene* fa, float sc);
	bool initWithScore(BasicScene* fa, float sc);
	bool onTouchBegan(Touch *touch, Event *event);
	void onNextCallBack(Ref *ref);
	void onRetryCallBack(Ref *ref);
private:
	BasicScene* container;
};

#endif
