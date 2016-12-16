#include "IntroLayer.h"
#include "Util.h"
//#include "AudioEngine.h"
//using namespace experimental;

const char intro[][100] = {
	"Welcome to\nTreasure Key.\nlet me explain\nyou how to\nplay!",
	"I am Mandy\nThe Explorer,\nand I need your\nhelp.",
	"A long time\nago Roberto\nThe Pirate, hid\nhis treasure\nfar far away!",
	"The only way\nto find it\nis by unlocking\nthe magic treasure\nchests to find clues.",
	"In the Theme\nParks Map,\nyou will find\nthe locked treasure\nchests!",
	"Each treasure\nchest contains\na clue with\nthe shape of the\nnext lock!",
	"Let's start\nplaying. Thank\nyou for all\nyour help!"
};

IntroLayer * IntroLayer::createWithTime(BasicScene* fa, float dt) {
	auto ret = IntroLayer::create();
	ret->initWithTime(fa, dt);
	return ret;
}

void IntroLayer::onSettingCallBack(Ref * ref) {
	Util::getInstance()->stopBackgroudMusic();
	Util::getInstance()->playClick();
	container->onSettingCallBack(INTRO_LAYER);
	this->removeFromParentAndCleanup(true);
}

bool IntroLayer::initWithTime(BasicScene* fa, float dt) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	totaln = 7;

	auto cg = Sprite::create("Backgroundforscene2.png");
	cg->setScaleX(visibleSize.width / cg->getContentSize().width);
	cg->setScaleY(visibleSize.height / cg->getContentSize().height);
	cg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(cg);

	auto mandy = Sprite::create("mandyintro.png");
	mandy->setAnchorPoint(Vec2(0, 0));
	mandy->setScale(897.0f / 2017.0f * visibleSize.width / mandy->getContentSize().width);
	mandy->setPosition(0, 0);
	this->addChild(mandy);

	auto bubble = Sprite::create("bubleintro.png");
	bubble->setAnchorPoint(Vec2(0, 0));
	bubble->setScale(1316.0f / 2017.0f * visibleSize.width / bubble->getContentSize().width);
	bubble->setPosition(715.5f / 2017.0f * visibleSize.width, 136.0f / 1135.0f * visibleSize.height);
	this->addChild(bubble);

	text = Label::createWithTTF(intro[0], "cartoonist_kooky.ttf", 48);
	text->setAlignment(TextHAlignment::CENTER);
	text->setPosition(1373.0f / 2017.0f * visibleSize.width, 620.f / 1135.0f * visibleSize.height);
	text->setScale(visibleSize.width / 1600.f);
	text->setColor(Color3B(0x4c, 0x42, 0x34));
	this->addChild(text);
	textn = 0;

	duration = dt;

	auto oneTouch = EventListenerTouchOneByOne::create();
	oneTouch->onTouchBegan = CC_CALLBACK_2(IntroLayer::onTouchBegan, this);
	oneTouch->onTouchMoved = CC_CALLBACK_2(IntroLayer::onTouchMoved, this);
	oneTouch->onTouchEnded = CC_CALLBACK_2(IntroLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(oneTouch, this);

//	auto settingItem = MenuItemImage::create("Settings.png", "SettingsHover.png", CC_CALLBACK_1(IntroLayer::onSettingCallBack, this));
//	settingItem->setScale(103.0f / 2017.0f * visibleSize.width / settingItem->getContentSize().width);
//	settingItem->setAnchorPoint(Vec2(0, 0));
//	settingItem->setPosition( 1898.0f / 2017.0f * visibleSize.width, 15.0f / 1135.0f  * visibleSize.height);

	auto menu = Menu::create();

	auto settingItem = MenuItemImage::create("home.png", "homeHover.png", CC_CALLBACK_1(IntroLayer::onSettingCallBack, this));
	settingItem->setScale(122.0f / 2017.0f * visibleSize.width / settingItem->getContentSize().width);
	settingItem->setAnchorPoint(Vec2(0, 1));
	settingItem->setPosition(8.0f / 2017.0f * visibleSize.width, (1 - 5.0f / 1135.0f)  * visibleSize.height);
	menu->addChild(settingItem);

	//auto menu = Menu::create(settingItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	Util::getInstance()->startBackgroundMusic(MANDY_INTRO, false);

	remainingT = duration;
	this->scheduleUpdate();

	container = fa;

	return true;
}

bool IntroLayer::onTouchBegan(Touch * touch, Event * event) {
	return true;
}

void IntroLayer::onTouchEnded(Touch * touch, Event * event) {
	textn++;
	if (textn >= totaln) {
		this->finish();
	}
	else {
		remainingT = duration;
		text->setString(intro[textn]);
	}
}

void IntroLayer::update(float dt) {
	remainingT -= dt;
	if (remainingT < 0) {
		remainingT = duration;
		textn++;
		if (textn >= totaln) {
			this->finish();
		}
		else {
			text->setString(intro[textn]);
		}
	}
}

void IntroLayer::finish() {
	Util::getInstance()->stopBackgroudMusic();
	container->onRemoveIntroLayerCallBack();
	this->removeFromParentAndCleanup(true);
}
