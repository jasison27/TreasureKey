#include "FinishLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

FinishLayer * FinishLayer::createWithScore(BasicScene * fa, float sc) {
	FinishLayer* layer = FinishLayer::create();
	if (layer->initWithScore(fa, sc)) return layer;
	return nullptr;
}

bool FinishLayer::initWithScore(BasicScene * fa, float sc) {
	container = fa;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto bg = Sprite::create("blackscreen.png");
	bg->setScaleX(visibleSize.width / bg->getContentSize().width);
	bg->setScaleY(visibleSize.height / bg->getContentSize().height);
	bg->setPosition(visibleSize / 2);
	this->addChild(bg);

	auto oneTouch = EventListenerTouchOneByOne::create();
	oneTouch->onTouchBegan = CC_CALLBACK_2(FinishLayer::onTouchBegan, this);
	oneTouch->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(oneTouch, this);

	auto backToLevelItem = MenuItemImage::create("levels.png", "levelsHover.png", CC_CALLBACK_1(FinishLayer::onBackToLevelCallBack, this));
	backToLevelItem->setScale(687.0f / 2017.0f * visibleSize.width / backToLevelItem->getContentSize().width);
	backToLevelItem->setAnchorPoint(Vec2(0, 0));
	backToLevelItem->setPosition(1320.0f / 2017.0f * visibleSize.width, 735.0f / 1135.0f  * visibleSize.height);

	if (sc > 0.7) {
		if (Util::getInstance()->getMusic()) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			SimpleAudioEngine::getInstance()->playEffect("pass.wav");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			SimpleAudioEngine::getInstance()->playEffect("pass.ogg");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			SimpleAudioEngine::getInstance()->playEffect("pass.caf");
#endif
		}
		auto mandy = Sprite::create("MandyWin.png");
		mandy->setAnchorPoint(Vec2(0, 0));
		mandy->setPosition(0, 0);
		mandy->setScale(931.0f / 2.0f / 949.0f * visibleSize.width / mandy->getContentSize().width);
		this->addChild(mandy);

		auto nextItem = MenuItemImage::create("NextLevel.png", "NextLevelHover.png", CC_CALLBACK_1(FinishLayer::onNextCallBack, this));
		nextItem->setScale(144.0f / 949.0f * visibleSize.width / nextItem->getContentSize().width);
		nextItem->setAnchorPoint(Vec2(0, 0));
		nextItem->setPosition(802.0f / 949.0f * visibleSize.width, 440.0f / 554.0f  * visibleSize.height);

		auto menu = Menu::create(nextItem, backToLevelItem, NULL);
		menu->setPosition(0, 0);
		this->addChild(menu);

		auto label1 = Label::createWithTTF("CONGRATULATIONS\n \n", "cartoonist_kooky.ttf", 32);
		label1->setAnchorPoint(Vec2(0, 1));
		label1->setPosition(210.0f / 949.0f * visibleSize.width, 190.0f / 554.0f * visibleSize.height);
		label1->setScale(visibleSize.width / 1600.f);
		label1->setColor(Color3B(0x4c, 0x42, 0x34));
		label1->setAlignment(TextHAlignment::CENTER);
		this->addChild(label1);

		char text[20];
		if(sc<=0.8){
		sprintf(text, "Fair drawing!\n \n");
		}
		else if ((sc > 0.8)&&(sc <= 0.9)) {
			sprintf(text, "Good drawing!\n \n");
		}
		else if ((sc > 0.9)&&(sc <= 0.95)) {
			sprintf(text, "Great drawing!\n \n");
		}
		else {
			sprintf(text, "Excellent drawing!\n \n");
		}

		auto label2 = Label::createWithTTF(text, "cartoonist_kooky.ttf", 32);
		label2->setAnchorPoint(Vec2(0, 1));
		label2->setPosition(220.0f / 949.0f * visibleSize.width, 165.0f / 554.0f * visibleSize.height);
		label2->setScale(visibleSize.width / 1600.f);
		label2->setColor(Color3B(0xf4, 0xb2, 0x1e));
		label2->setAlignment(TextHAlignment::CENTER);
		this->addChild(label2);

		auto label3 = Label::createWithTTF("THANK YOU!\nYOU JUST UNLOCK\nONE MORE SHAPE", "cartoonist_kooky.ttf", 32);
		label3->setAnchorPoint(Vec2(0, 1));
		label3->setPosition(210.0f / 949.0f * visibleSize.width, 140.0f / 554.0f * visibleSize.height);
		label3->setScale(visibleSize.width / 1600.f);
		label3->setColor(Color3B(0x4c, 0x42, 0x34));
		label3->setAlignment(TextHAlignment::CENTER);
		this->addChild(label3);
	}
	else {
		if (Util::getInstance()->getMusic()) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			SimpleAudioEngine::getInstance()->playEffect("fail.wav");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			SimpleAudioEngine::getInstance()->playEffect("fail.ogg");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			SimpleAudioEngine::getInstance()->playEffect("fail.caf");
#endif
		}
		auto robert = Sprite::create("LooseRoberto.png");
		robert->setAnchorPoint(Vec2(1, 0));
		robert->setPosition(visibleSize.width, 0);
		robert->setScale(954.0f / 2.0f / 949.0f * visibleSize.width / robert->getContentSize().width);
		this->addChild(robert);

		auto retryItem = MenuItemImage::create("try.png", "tryHover.png", CC_CALLBACK_1(FinishLayer::onRetryCallBack, this));
		retryItem->setScale(144.0f / 949.0f * visibleSize.width / retryItem->getContentSize().width);
		retryItem->setAnchorPoint(Vec2(0, 0));
		retryItem->setPosition(802.0f / 949.0f * visibleSize.width, 440.0f / 554.0f  * visibleSize.height);

		auto menu = Menu::create(retryItem, backToLevelItem, NULL);
		menu->setPosition(0, 0);
		this->addChild(menu);

		auto label1 = Label::createWithTTF("HAHAHA\n \n", "cartoonist_kooky.ttf", 32);
		label1->setAnchorPoint(Vec2(0, 1));
		label1->setPosition(590.0f / 949.0f * visibleSize.width, 175.0f / 554.0f * visibleSize.height);
		label1->setScale(visibleSize.width / 1600.f);
		label1->setColor(Color3B(0x4c, 0x42, 0x34));
		label1->setAlignment(TextHAlignment::CENTER);
		this->addChild(label1);

		char text[20];
		if (sc>0.6) {
			sprintf(text, "Poor drawing!\n \n");
		}
		else {
			sprintf(text, "Bad drawing!\n \n");
		}
		auto label2 = Label::createWithTTF(text, "cartoonist_kooky.ttf", 32);
		label2->setAnchorPoint(Vec2(0, 1));
		label2->setPosition(560.0f / 949.0f * visibleSize.width, 150.0f / 554.0f * visibleSize.height);
		label2->setScale(visibleSize.width / 1600.f);
		label2->setColor(Color3B(0xe5, 0x2b, 0x25));
		label2->setAlignment(TextHAlignment::CENTER);
		this->addChild(label2);

		auto label3 = Label::createWithTTF("YOU MUST TRY AGAIN!", "cartoonist_kooky.ttf", 32);
		label3->setAnchorPoint(Vec2(0, 1));
		label3->setPosition(520.0f / 949.0f * visibleSize.width, 125.0f / 554.0f * visibleSize.height);
		label3->setScale(visibleSize.width / 1600.f);
		label3->setColor(Color3B(0x4c, 0x42, 0x34));
		label3->setAlignment(TextHAlignment::CENTER);
		this->addChild(label3);

	}

	return true;
}

bool FinishLayer::onTouchBegan(Touch * touch, Event * event) {
	auto pos = Director::getInstance()->convertToUI(touch->getLocationInView());
	CCLOG("%.5lf %.5lf", pos.x, pos.y);
	return true;
}

void FinishLayer::onNextCallBack(Ref * ref) {
	Util::getInstance()->playClick();
	container->onNextLevelCallBack();
	this->removeFromParentAndCleanup(true);
}

void FinishLayer::onRetryCallBack(Ref * ref) {
	Util::getInstance()->playClick();
	container->onRetryLevelCallBack();
	this->removeFromParentAndCleanup(true);
}

void FinishLayer::onBackToLevelCallBack(Ref * ref) {
	Util::getInstance()->playClick();
	container->onBackToLevelCallBack();
	this->removeFromParentAndCleanup(true);
}
