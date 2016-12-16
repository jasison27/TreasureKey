#include "FinishLayer.h"
#include "AudioEngine.h"
using namespace experimental;

const char text[][10] = {
	"Circle", "Triangle", "Square", "Hexagon", "Octagon"
};
const AudioEnum exc[] = {
	MANDY_EXC_CIR, MANDY_EXC_TRI, MANDY_EXC_SQU, MANDY_EXC_HEX, MANDY_EXC_OCT
};
const AudioEnum good[] = {
	MANDY_GOOD_CIR, MANDY_GOOD_TRI, MANDY_GOOD_SQU, MANDY_GOOD_HEX, MANDY_GOOD_OCT
};

FinishLayer * FinishLayer::createWithScoreThemeLevel(BasicScene * fa, float sc, int the, int lev) {
	FinishLayer* layer = FinishLayer::create();
	if (layer->initWithScoreThemeLevel(fa, sc, the, lev)) return layer;
	return nullptr;
}

bool FinishLayer::initWithScoreThemeLevel(BasicScene * fa, float sc, int the, int lev) {
	themen = the;
	leveln = lev;
	container = fa;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto oneTouch = EventListenerTouchOneByOne::create();
	oneTouch->onTouchBegan = CC_CALLBACK_2(FinishLayer::onTouchBegan, this);
	oneTouch->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(oneTouch, this);

	firstLayer = Layer::create();
	this->addChild(firstLayer);

	if (sc > 0.7) {
		auto blackscreen = Sprite::create("blackscreen.png");
		blackscreen->setScaleX(visibleSize.width / blackscreen->getContentSize().width);
		blackscreen->setScaleY(visibleSize.height / blackscreen->getContentSize().height);
		blackscreen->setPosition(visibleSize / 2);
		firstLayer->addChild(blackscreen);

		auto bubble = Sprite::create("winbubble.png");
		bubble->setScale(728.0f / 2017.0f * visibleSize.width / bubble->getContentSize().width);
		bubble->setAnchorPoint(Vec2(0, 1));
		bubble->setPosition(0, visibleSize.height);
		firstLayer->addChild(bubble);

		auto label3 = Label::createWithTTF("Congratulations!\nExcellent!\nYou did it.\nIs there a clue?", "cartoonist_kooky.ttf", 32);
		label3->setAnchorPoint(Vec2(0, 1));
		label3->setPosition(83.0f / 2017.0f * visibleSize.width, (1 - 116.0f / 1135.0f) * visibleSize.height);
		label3->setScale(559.0f / 2017.0f * visibleSize.width / label3->getContentSize().width);
		label3->setColor(Color3B(0x4c, 0x42, 0x34));
		label3->setAlignment(TextHAlignment::CENTER);
		this->addChild(label3);

		auto id = AudioEngine::play2d("[8]Eng_win_1.mp3");
		AudioEngine::setFinishCallback(id, [&](int id, const std::string& filePath) {
			removeBubbleThings();
		});

	}
	else {
		auto looseRoberto = Sprite::create("LooseRoberto.png");
		looseRoberto->setScale(1154.0f / 2017.0f * visibleSize.width / looseRoberto->getContentSize().width);
		looseRoberto->setAnchorPoint(Vec2(0, 1));
		looseRoberto->setPosition(872.0f / 2017.0f * visibleSize.width, (1 - 515.0f / 1135.0f)  * visibleSize.height);
		firstLayer->addChild(looseRoberto);

		auto menu = Menu::create();

		auto retryItem = MenuItemImage::create("try.png", "tryHover.png", CC_CALLBACK_1(FinishLayer::onRetryCallBack, this));
		retryItem->setScale(144.0f / 949.0f * visibleSize.width / retryItem->getContentSize().width);
		retryItem->setAnchorPoint(Vec2(0, 0));
		retryItem->setPosition(802.0f / 949.0f * visibleSize.width, 440.0f / 554.0f  * visibleSize.height);
		menu->addChild(retryItem);

		menu->setPosition(0, 0);
		this->addChild(menu);

		auto id = AudioEngine::play2d("[14]Eng_loose_1.mp3");
	}
	//remainingT = 3.0f;
	//this->scheduleUpdate();

//	auto backToLevelItem = MenuItemImage::create("levels.png", "levelsHover.png", CC_CALLBACK_1(FinishLayer::onBackToLevelCallBack, this));
//	backToLevelItem->setScale(687.0f / 2017.0f * visibleSize.width / backToLevelItem->getContentSize().width);
//	backToLevelItem->setAnchorPoint(Vec2(0, 0));
//	backToLevelItem->setPosition(1320.0f / 2017.0f * visibleSize.width, 735.0f / 1135.0f  * visibleSize.height);

	/*
	if (sc > 0.7) {
		char fileName[20];
		if (sc < 0.9) {
			effectn = Util::getInstance()->startAudio(good[leveln - 1], false);
			sprintf(fileName, "MandyGood.png");
		}
		else {
			effectn = Util::getInstance()->startAudio(exc[leveln - 1], false);
			sprintf(fileName, "MandyExcellent.png");
		}
		auto mandy = Sprite::create(fileName);
		mandy->setAnchorPoint(Vec2(0, 0));
		mandy->setPosition(0, 0);
		mandy->setScale(931.0f / 2.0f / 949.0f * visibleSize.width / mandy->getContentSize().width);
		this->addChild(mandy);

		auto nextItem = MenuItemImage::create("NextLevel.png", "NextLevelHover.png", CC_CALLBACK_1(FinishLayer::onNextCallBack, this));
		nextItem->setScale(144.0f / 949.0f * visibleSize.width / nextItem->getContentSize().width);
		nextItem->setAnchorPoint(Vec2(0, 0));
		nextItem->setPosition(802.0f / 949.0f * visibleSize.width, 440.0f / 554.0f  * visibleSize.height);

//		auto menu = Menu::create(nextItem, backToLevelItem, NULL);
		auto menu = Menu::create(nextItem, NULL);
		menu->setPosition(0, 0);
		this->addChild(menu);

		auto label3 = Label::createWithTTF(text[leveln-1], "cartoonist_kooky.ttf", 32);
		label3->setAnchorPoint(Vec2(0.5, 0.5));
		label3->setPosition(310.0f / 949.0f * visibleSize.width, 120.0f / 554.0f * visibleSize.height);
		label3->setScale(visibleSize.width / 1300.f);
		label3->setColor(Color3B(0xf4, 0xb2, 0x1e));
		label3->setAlignment(TextHAlignment::CENTER);
		this->addChild(label3);
	}
	else {
		char fileName[20];
		if (sc < 0.6) {
			effectn = Util::getInstance()->startAudio(ROBERT_BAD, false);
			sprintf(fileName, "RobertoBAD.png");
		}
		else {
			effectn = Util::getInstance()->startAudio(ROBERT_WRONG, false);
			sprintf(fileName, "RobertoWrong.png");
		}

		auto robert = Sprite::create(fileName);
		robert->setAnchorPoint(Vec2(1, 0));
		robert->setPosition(visibleSize.width, 0);
		robert->setScale(954.0f / 2.0f / 949.0f * visibleSize.width / robert->getContentSize().width);
		this->addChild(robert);

		auto retryItem = MenuItemImage::create("try.png", "tryHover.png", CC_CALLBACK_1(FinishLayer::onRetryCallBack, this));
		retryItem->setScale(144.0f / 949.0f * visibleSize.width / retryItem->getContentSize().width);
		retryItem->setAnchorPoint(Vec2(0, 0));
		retryItem->setPosition(802.0f / 949.0f * visibleSize.width, 440.0f / 554.0f  * visibleSize.height);

//		auto menu = Menu::create(retryItem, backToLevelItem, NULL);
		auto menu = Menu::create(retryItem, NULL);
		menu->setPosition(0, 0);
		this->addChild(menu);

//		auto label1 = Label::createWithTTF("HAHAHA\n \n", "cartoonist_kooky.ttf", 32);
//		label1->setAnchorPoint(Vec2(0, 1));
//		label1->setPosition(590.0f / 949.0f * visibleSize.width, 175.0f / 554.0f * visibleSize.height);
//		label1->setScale(visibleSize.width / 1600.f);
//		label1->setColor(Color3B(0x4c, 0x42, 0x34));
//		label1->setAlignment(TextHAlignment::CENTER);
//		this->addChild(label1);
	}
	*/

	return true;
}

bool FinishLayer::onTouchBegan(Touch * touch, Event * event) {
	auto pos = Director::getInstance()->convertToUI(touch->getLocationInView());
	CCLOG("%.5lf %.5lf", pos.x, pos.y);
	return true;
}

void FinishLayer::onNextCallBack(Ref * ref) {
	Util::getInstance()->stopAudio(effectn);
	Util::getInstance()->playClick();
	container->onNextLevelCallBack();
	this->removeFromParentAndCleanup(true);
}

void FinishLayer::onRetryCallBack(Ref * ref) {
	Util::getInstance()->stopAudio(effectn);
	Util::getInstance()->playClick();
	container->onRetryLevelCallBack();
	this->removeFromParentAndCleanup(true);
}

void FinishLayer::onBackToLevelCallBack(Ref * ref) {
	Util::getInstance()->stopAudio(effectn);
	Util::getInstance()->playClick();
	container->onBackToLevelCallBack();
	this->removeFromParentAndCleanup(true);
}

void FinishLayer::removeBubbleThings() {
	container->onDisplayNextLevelCallBack();
	this->removeFromParentAndCleanup(true);
}
