#include "StartLayer.h"

StartLayer * StartLayer::createWithTime(BasicScene* fa, float dt) {
	auto ret = StartLayer::create();
	ret->initWithTime(fa, dt);
	return ret;
}

bool StartLayer::initWithTime(BasicScene* fa, float dt) {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	remainingT = dt;

	auto cg = Sprite::create("StartingScreenLandscape.png");
	auto sc = std::max(visibleSize.width / cg->getContentSize().width, visibleSize.height / cg->getContentSize().height);
	cg->setScale(sc);
	cg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(cg);
	this->scheduleUpdate();

	container = fa;
	return true;
}

void StartLayer::update(float dt) {
	remainingT -= dt;
	if (remainingT < 0) {
		remainingT = 0;
		container->onRemoveStartLayerCallBack();
		this->removeFromParentAndCleanup(true);
	}
}
