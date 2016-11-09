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
	bg->setScale(visibleSize.width / bg->getContentSize().width);
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(0, 0);
	this->addChild(bg);

	auto oneTouch = EventListenerTouchOneByOne::create();
	oneTouch->onTouchBegan = CC_CALLBACK_2(FinishLayer::onTouchBegan, this);
	oneTouch->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(oneTouch, this);

	if (sc > 0.7) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		SimpleAudioEngine::getInstance()->playEffect("success.wav");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		SimpleAudioEngine::getInstance()->playEffect("success.ogg");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		SimpleAudioEngine::getInstance()->playEffect("success.caf");
#endif
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

		auto label1 = Label::createWithTTF("CONGRATULATIONS", "Cartoonist.ttf", 24);
		label1->setAnchorPoint(Vec2(0, 1));
		label1->setPosition(240.0f / 949.0f * visibleSize.width, 175.0f / 554.0f * visibleSize.height);//!!!!to be modified
		label1->setColor(Color3B(0x4c, 0x42, 0x34));
		label1->setAlignment(TextHAlignment::CENTER);
		this->addChild(label1);

		char text[20];
		sprintf(text, "YOUR SCORE %.1lf", sc * 100);
		auto label2 = Label::createWithTTF(text, "Cartoonist.ttf", 24);
		label2->setAnchorPoint(Vec2(0, 1));
		label2->setPosition(240.0f / 949.0f * visibleSize.width, 155.0f / 554.0f * visibleSize.height);//!!!!to be modified
		label2->setColor(Color3B::YELLOW);
		label2->setAlignment(TextHAlignment::CENTER);
		this->addChild(label2);

		auto label3 = Label::createWithTTF("THANK YOU!\nYOU JUST UNLOCK\nONE MORE SHAPE", "Cartoonist.ttf", 24);
		label3->setAnchorPoint(Vec2(0, 1));
		label3->setPosition(240.0f / 949.0f * visibleSize.width, 135.0f / 554.0f * visibleSize.height);//!!!!to be modified
		label3->setColor(Color3B(0x4c, 0x42, 0x34));
		label3->setAlignment(TextHAlignment::CENTER);
		this->addChild(label3);
	}
	else {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		SimpleAudioEngine::getInstance()->playEffect("fail.wav");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		SimpleAudioEngine::getInstance()->playEffect("fail.ogg");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		SimpleAudioEngine::getInstance()->playEffect("fail.caf");
#endif
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

		auto label1 = Label::createWithTTF("HAHAHA", "Cartoonist.ttf", 24);
		label1->setAnchorPoint(Vec2(0, 1));
		label1->setPosition(500.0f / 949.0f * visibleSize.width, 175.0f / 554.0f * visibleSize.height);//!!!!to be modified
		label1->setColor(Color3B(0x4c, 0x42, 0x34));
		label1->setAlignment(TextHAlignment::CENTER);
		this->addChild(label1);

		char text[20];
		sprintf(text, "YOUR SCORE %.1lf", sc * 100);
		auto label2 = Label::createWithTTF(text, "Cartoonist.ttf", 24);
		label2->setAnchorPoint(Vec2(0, 1));
		label2->setPosition(500.0f / 949.0f * visibleSize.width, 155.0f / 554.0f * visibleSize.height);//!!!!to be modified
		label2->setColor(Color3B::YELLOW);
		label2->setAlignment(TextHAlignment::CENTER);
		this->addChild(label2);

		auto label3 = Label::createWithTTF("YOU MUST TRY\nAGAIN!", "Cartoonist.ttf", 24);
		label3->setAnchorPoint(Vec2(0, 1));
		label3->setPosition(500.0f / 949.0f * visibleSize.width, 135.0f / 554.0f * visibleSize.height);//!!!!to be modified
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
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	SimpleAudioEngine::getInstance()->playEffect("click.wav");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SimpleAudioEngine::getInstance()->playEffect("click.ogg");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SimpleAudioEngine::getInstance()->playEffect("click.caf");
#endif
	container->onNextLevelCallBack();
	this->removeFromParentAndCleanup(true);
}

void FinishLayer::onRetryCallBack(Ref * ref) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	SimpleAudioEngine::getInstance()->playEffect("click.wav");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	SimpleAudioEngine::getInstance()->playEffect("click.ogg");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	SimpleAudioEngine::getInstance()->playEffect("click.caf");
#endif
	container->onRetryLevelCallBack();
	this->removeFromParentAndCleanup(true);
}
