#include "IntroLayer.h"
#include "Util.h"

const char intro[][100] = {
	"WELCOME TO\nTREASURE KEY.\nLET ME EXPLAIN\nHOW TO PLAY!",
	"I AM MANDY\nAND NEED HELP\nFROM YOU.",
	"LONG TIME AGO,\nROBERTO, A PIRATE,\nHID HIS TREASUER\nIN DIFFERENT\nTHEME PARKS.",
	"THERE ARE FIVE CHESTS\nIN EACH THEME PARK.",
	"TO UNLOCK THE CHESTS,\nWE NEED TO UNLOCK\nTHE SHAPE OF THE KEY\nBY DRAWING IT OUT.",
	"THANKS FOR YOUR HELP."
};

IntroLayer * IntroLayer::createWithTime(BasicScene* fa, float dt) {
	auto ret = IntroLayer::create();
	ret->initWithTime(fa, dt);
	return ret;
}

void IntroLayer::onSettingCallBack(Ref * ref) {
	Util::getInstance()->playClick();
	container->onSettingCallBack(INTRO_LAYER);
	this->removeFromParentAndCleanup(true);
}

bool IntroLayer::initWithTime(BasicScene* fa, float dt) {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto cg = Sprite::create("Backgroundforscene1_2.png");
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
	text->setColor(Color3B(0x4c, 0x42, 0x34));
	this->addChild(text);
	textn = 0;
	totaln = 6;

	duration = dt;

	auto oneTouch = EventListenerTouchOneByOne::create();
	oneTouch->onTouchBegan = CC_CALLBACK_2(IntroLayer::onTouchBegan, this);
	oneTouch->onTouchMoved = CC_CALLBACK_2(IntroLayer::onTouchMoved, this);
	oneTouch->onTouchEnded = CC_CALLBACK_2(IntroLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(oneTouch, this);

	auto settingItem = MenuItemImage::create("Settings.png", "SettingsHover.png", CC_CALLBACK_1(IntroLayer::onSettingCallBack, this));
	settingItem->setScale(103.0f / 2017.0f * visibleSize.width / settingItem->getContentSize().width);
	settingItem->setAnchorPoint(Vec2(0, 0));
	settingItem->setPosition( 1898.0f / 2017.0f * visibleSize.width, 15.0f / 1135.0f  * visibleSize.height);

	auto menu = Menu::create(settingItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

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
	container->onRemoveIntroLayerCallBack();
	this->removeFromParentAndCleanup(true);
}
