#include "StartLayer.h"
#include "Util.h"

StartLayer * StartLayer::createWithTime(BasicScene* fa, float dt) {
	auto ret = StartLayer::create();
	ret->initWithTime(fa, dt);
	return ret;
}

bool StartLayer::initWithTime(BasicScene* fa, float dt) {
	container = fa;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	remainingT = dt;
	remainingT2 = dt * 2;

	auto cg = Sprite::create("Backgroundforscene0.png");
	cg->setScaleX(visibleSize.width / cg->getContentSize().width);
	cg->setScaleY(visibleSize.height / cg->getContentSize().height);
	cg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(cg);

	mandy = Sprite::create("mapstart1.png");
	mandy->setScale(981.0f / 2017.0f * visibleSize.width / mandy->getContentSize().width);
	mandy->setAnchorPoint(Vec2(0, 0));
	mandy->setPosition(71.0f / 2017.0f * visibleSize.width, 8.0f / 1135.0f  * visibleSize.height);
	this->addChild(mandy);

	this->scheduleUpdate();

	Util::getInstance()->startBackgroundMusic(START_SCREEN_MUSIC);

	return true;
}

void StartLayer::update(float dt) {
	remainingT -= dt;
	remainingT2 -= 2 * dt;
	if (remainingT < 0) {
		remainingT = 0;
		Util::getInstance()->stopBackgroudMusic();
		container->onRemoveStartLayerCallBack();
		this->removeFromParentAndCleanup(true);
	}
	int rT = ceil(remainingT2);
	if (ceil(remainingT2) != ceil(remainingT2 + dt) && rT >= 1 && rT <= 4) {
		char textureFile[] = "mapstart1.png";
		textureFile[8] = '1' + 4 - rT;
		CCLOG("%s", textureFile);
		mandy->setTexture(textureFile);
	}
}
