#include "DisplayNextLayer.h"
#include "AudioEngine.h"
using namespace experimental;

const char clueFileName[][20] = {
	"cluetriangle.png", "cluesquare.png", "cluehexagon.png", "clueoctagon.png"
};
const char winAudioFileName[][30] = {
	"[9]Eng_win_2_triangle.mp3", "[10]Eng_win_2_square.mp3", "[11]Eng_win_2_hexagon.mp3", "[12]Eng_win_2_octagon.mp3"
};
const char clueText[][60] = {
	"It looks like we\nneed to draw a\ntriangle for the\nnext lock!",
	"It looks like we\nneed to draw a\nsquare for the\nnext lock!",
	"It looks like we\nneed to draw a\nhexagon for the\nnext lock!",
	"It looks like we\nneed to draw a\noctagon for the\nnext lock!"
};

DisplayNextLayer * DisplayNextLayer::createWithThemeLevel(BasicScene * fa, int the, int lev) {
	DisplayNextLayer* layer = DisplayNextLayer::create();
	if (layer->initWithThemeLevel(fa, the, lev)) return layer;
	return nullptr;
}

bool DisplayNextLayer::initWithThemeLevel(BasicScene * fa, int the, int lev) {
	themen = the;
	leveln = lev;
	container = fa;
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto cg = Sprite::create("Backgroundforscenepolygon.png");
	cg->setScaleX(visibleSize.width / cg->getContentSize().width);
	cg->setScaleY(visibleSize.height / cg->getContentSize().height);
	cg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(cg, 0);

	auto chestbottom = Sprite::create("chestbottom.png");
	chestbottom->setScale(821.0f / 2017.0f * visibleSize.width / chestbottom->getContentSize().width);
	chestbottom->setAnchorPoint(Vec2(0, 0));
	chestbottom->setPosition(131.0f / 2017.0f * visibleSize.width, 0);
	this->addChild(chestbottom, 2);

	auto chestop1 = Sprite::create("chestop1.png");
	chestop1->setScale(821.0f / 2017.0f * visibleSize.width / chestop1->getContentSize().width);
	chestop1->setAnchorPoint(Vec2(0, 0));
	chestop1->setPosition(131.0f / 2017.0f * visibleSize.width, 492.0f / 1135.0f  * visibleSize.height);
	this->addChild(chestop1, 0);

	auto paper = Sprite::create("paper.png");
	paper->setScale(653.0f / 2017.0f * visibleSize.width / paper->getContentSize().width);
	paper->setAnchorPoint(Vec2(0, 1));
	paper->setPosition(131.0f / 2017.0f * visibleSize.width, 1);
	this->addChild(paper, 1);

	auto moveTo = MoveTo::create(2.0f, Vec2(167.0f / 2017.0f * visibleSize.width, (1 - 35.0f / 1135.0f)  * visibleSize.height));
	auto callBack = CallFunc::create(CC_CALLBACK_0(DisplayNextLayer::displayShape, this));
	paper->runAction(Sequence::create(moveTo, callBack, nullptr));

	menu = Menu::create();

	auto settingItem = MenuItemImage::create("home.png", "homeHover.png", CC_CALLBACK_1(DisplayNextLayer::onSettingCallBack, this));
	settingItem->setScale(122.0f / 2017.0f * visibleSize.width / settingItem->getContentSize().width);
	settingItem->setAnchorPoint(Vec2(0, 1));
	settingItem->setPosition(8.0f / 2017.0f * visibleSize.width, (1 - 5.0f / 1135.0f)  * visibleSize.height);
	menu->addChild(settingItem);

	menu->setPosition(0, 0);
	this->addChild(menu, 5);
	
	return true;
}

void DisplayNextLayer::onSettingCallBack(Ref * ref) {
	Util::getInstance()->playClick();
	Util::getInstance()->stopBackgroudMusic();
	container->onSettingCallBack(LEVEL_LAYER);
	AudioEngine::stopAll();
	this->removeFromParentAndCleanup(true);
}

void DisplayNextLayer::onNextCallBack(Ref * ref) {
	Util::getInstance()->playClick();
	container->onNextLevelCallBack();
	this->removeFromParentAndCleanup(true);
}

void DisplayNextLayer::displayShape() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto clue = Sprite::create(clueFileName[leveln-2]);
	clue->setScale(434.0f / 2017.0f * visibleSize.width / clue->getContentSize().width);
	clue->setAnchorPoint(Vec2(0, 1));
	clue->setPosition(266.0f / 2017.0f * visibleSize.width, (1-170.0f / 1135.0f)  * visibleSize.height);
	clue->setOpacity(0);
	this->addChild(clue,3);
	auto fadeIn = FadeIn::create(1.5f);
	auto callBack = CallFunc::create(CC_CALLBACK_0(DisplayNextLayer::displayMandy, this));
	clue->runAction(Sequence::create(fadeIn, callBack, nullptr));
}

void DisplayNextLayer::displayMandy() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	mandyandbubble = Sprite::create("mandyandbubble.png");
	mandyandbubble->setScale(1406.0f / 2017.0f * visibleSize.width / mandyandbubble->getContentSize().width);
	mandyandbubble->setAnchorPoint(Vec2(0, 1));
	mandyandbubble->setPosition(596.0f / 2017.0f * visibleSize.width, visibleSize.height);
	this->addChild(mandyandbubble, 1);

	text = Label::createWithTTF(clueText[leveln - 2], "cartoonist_kooky.ttf", 32);
	text->setAnchorPoint(Vec2(0, 1));
	text->setPosition(1408.0f / 2017.0f * visibleSize.width, (1 - 95.0f / 1135.0f) * visibleSize.height);
	text->setScale(514.0f / 2017.0f * visibleSize.width / text->getContentSize().width);
	text->setColor(Color3B(0x4c, 0x42, 0x34));
	text->setAlignment(TextHAlignment::CENTER);
	this->addChild(text, 4);

	auto id = AudioEngine::play2d(winAudioFileName[leveln-2]);
	AudioEngine::setFinishCallback(id, [&](int id, const std::string& filePath) {
		displayRobert();
	});
}

void DisplayNextLayer::displayRobert() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->removeChild(mandyandbubble);
	this->removeChild(text);
	
	nextItem = MenuItemImage::create("NextLevel.png", "NextLevelHover.png", CC_CALLBACK_1(DisplayNextLayer::onNextCallBack, this));
	nextItem->setScale(144.0f / 949.0f * visibleSize.width / nextItem->getContentSize().width);
	nextItem->setAnchorPoint(Vec2(0, 0));
	nextItem->setPosition(802.0f / 949.0f * visibleSize.width, 440.0f / 554.0f  * visibleSize.height);
	menu->addChild(nextItem);
	
	robertoandbubble = Sprite::create("robertoandbubble.png");
	robertoandbubble->setScale(1108.0f / 2017.0f * visibleSize.width / robertoandbubble->getContentSize().width);
	robertoandbubble->setAnchorPoint(Vec2(0, 1));
	robertoandbubble->setPosition(743.0f / 2017.0f * visibleSize.width, visibleSize.height);
	this->addChild(robertoandbubble, 1);

	auto label3 = Label::createWithTTF("You'll never find\nmy treasure!", "cartoonist_kooky.ttf", 32);
	label3->setAnchorPoint(Vec2(0, 1));
	label3->setPosition(800.0f / 2017.0f * visibleSize.width, (1 - 122.0f / 1135.0f) * visibleSize.height);
	label3->setScale(516.0f / 2017.0f * visibleSize.width / label3->getContentSize().width);
	label3->setColor(Color3B(0x4c, 0x42, 0x34));
	label3->setAlignment(TextHAlignment::CENTER);
	this->addChild(label3, 4);

	auto idagain = AudioEngine::play2d("[13]Eng_win.mp3");
}
