#include "FinishLayer.h"

FinishLayer * FinishLayer::createWithScore(BasicScene * fa, float sc) {
	FinishLayer* layer = FinishLayer::create();
	if (layer->initWithScore(fa, sc)) return layer;
	return nullptr;
}

bool FinishLayer::initWithScore(BasicScene * fa, float sc) {
	container = fa;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto bg = Sprite::create("blackscreen.png");
	bg->setScale(visibleSize.width / bg->getContentSize().width);
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(0, 0);
	this->addChild(bg);

	auto oneTouch = EventListenerTouchOneByOne::create();
	oneTouch->onTouchBegan = CC_CALLBACK_2(FinishLayer::onTouchBegan, this);
	oneTouch->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(oneTouch, this);

	if (sc > 0.7) {
		auto mandy = Sprite::create("MandyWin.png");
		mandy->setAnchorPoint(Vec2(0, 0));
		mandy->setPosition(0, 0);
		mandy->setScale(931.0f / 2.0f / 949.0f * visibleSize.width / mandy->getContentSize().width);
		this->addChild(mandy);

		auto nextItem = MenuItemImage::create("NextLevel.png", "NextLevelHover.png", CC_CALLBACK_1(FinishLayer::onNextCallBack, this));
		nextItem->setScale(144.0f / 949.0f * visibleSize.width / nextItem->getContentSize().width);
		nextItem->setAnchorPoint(Vec2(0, 0));
		nextItem->setPosition(812.0f / 949.0f * visibleSize.width, 430.0f / 554.0f  * visibleSize.height);

		auto menu = Menu::create(nextItem, NULL);
		menu->setPosition(0, 0);
		this->addChild(menu);

		char text[90];
		sprintf(text, "CONGRATULATIONS\nYOUR SCORE %.1lf\nTHANK YOU!\nYOU JUST UNLOCK\nONE MORE SHAPE", sc * 100);
		auto label = Label::createWithTTF(text, "Cartoonist.ttf", 24);
		label->setPosition(visibleSize/2);//!!!!to be modified
		label->setColor(Color3B(0x4c, 0x42, 0x34));
		label->setAlignment(TextHAlignment::CENTER);
		this->addChild(label);
	}
	else {
		auto robert = Sprite::create("LooseRoberto.png");
		robert->setAnchorPoint(Vec2(1, 0));
		robert->setPosition(visibleSize.width, 0);
		robert->setScale(954.0f / 2.0f / 949.0f * visibleSize.width / robert->getContentSize().width);
		this->addChild(robert);

		auto retryItem = MenuItemImage::create("Exit.png", "ExitHover.png", CC_CALLBACK_1(FinishLayer::onRetryCallBack, this));
		retryItem->setScale(122.0f / 2017.0f * visibleSize.width / retryItem->getContentSize().width);
		retryItem->setAnchorPoint(Vec2(0, 0));
		retryItem->setPosition(1878.0f / 2017.0f * visibleSize.width, 1001.0f / 1135.0f  * visibleSize.height);

		auto menu = Menu::create(retryItem, NULL);
		menu->setPosition(0, 0);
		this->addChild(menu);

		char text[90];
		sprintf(text, "HAHAHA\nYOUR SCORE %.1lf\nYOU MUST TRY\nAGAIN!", sc * 100);
		auto label = Label::createWithTTF(text, "Cartoonist.ttf", 24);
		label->setPosition(visibleSize / 2);//!!!!to be modified
		label->setColor(Color3B(0x4c, 0x42, 0x34));
		label->setAlignment(TextHAlignment::CENTER);
		this->addChild(label);
	}

	return true;
}

bool FinishLayer::onTouchBegan(Touch * touch, Event * event) {
	return true;
}

void FinishLayer::onNextCallBack(Ref * ref) {
	container->onNextLevelCallBack();
	this->removeFromParentAndCleanup(true);
}

void FinishLayer::onRetryCallBack(Ref * ref) {
	container->onRetryLevelCallBack();
	this->removeFromParentAndCleanup(true);
}
