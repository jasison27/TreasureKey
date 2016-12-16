#ifndef FINISH_LAYER_H__
#define FINISH_LAYER_H__

#include "cocos2d.h"
#include "BasicScene.h"
USING_NS_CC;

class FinishLayer : public Layer
{
public:
	CREATE_FUNC(FinishLayer);
	static FinishLayer* createWithScoreThemeLevel(BasicScene* fa, float sc, int the, int lev);
	bool initWithScoreThemeLevel(BasicScene* fa, float sc, int the, int lev);
	bool onTouchBegan(Touch *touch, Event *event);
	void onNextCallBack(Ref *ref);
	void onRetryCallBack(Ref *ref);
	void onBackToLevelCallBack(Ref *ref);
	void removeBubbleThings();
private:
	float remainingT;
	BasicScene* container;
	int themen, leveln;
	int effectn;
	Layer* firstLayer;
};

#endif
