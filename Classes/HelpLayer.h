#ifndef HELP_LAYER_H__
#define HELP_LAYER_H__

#include "cocos2d.h"
#include "BasicScene.h"
USING_NS_CC;

class HelpLayer : public Layer
{
public:
	CREATE_FUNC(HelpLayer);
	static HelpLayer* createWithOption(BasicScene* fa, LayerEnum lenum);
	bool initWithOption(BasicScene* fa, LayerEnum lenum);
	void menuThemeCallBack(Ref *pSender);
	void menuLevelCallBack(Ref *pSender);
	void menuIntroCallBack(Ref *pSender);
	void menuCloseCallBack(Ref *pSender);
	bool onTouchBegan(Touch *touch, Event *event);
private:
	MenuItemImage* itemMusic;
	void onMusicCallBack(Ref* ref);
	BasicScene* container;
	LayerEnum mylenum;
};

#endif
