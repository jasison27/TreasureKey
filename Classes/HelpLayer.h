#ifndef HELP_LAYER_H__
#define HELP_LAYER_H__

#include "cocos2d.h"
#include "BasicScene.h"
USING_NS_CC;

class HelpLayer : public Layer
{
public:
	CREATE_FUNC(HelpLayer);
	static HelpLayer* createWithOption(BasicScene* fa, bool hintf);
	bool initWithOption(BasicScene* fa, bool hintf);
	void menuThemeCallBack(Ref *pSender);
	void menuLevelCallBack(Ref *pSender);
	void menuIntroCallBack(Ref *pSender);
	void menuHintCallBack(Ref *pSender);
private:
	BasicScene* container;
};

#endif
