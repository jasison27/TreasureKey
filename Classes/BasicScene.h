#ifndef BASIC_SCENE_H__
#define BASIC_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class BasicScene : public Scene
{
public:
	virtual void onHelpCloseCallBack() = 0;
};

#endif