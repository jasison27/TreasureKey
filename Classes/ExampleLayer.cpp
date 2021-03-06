#include "ExampleLayer.h"
#include "BasicScene.h"
#include <algorithm>
#include "Util.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

const double PI = acos(-1);
int num_vertex[] = { 0,3,4,6,8 };
const char text[][10] = {
	"CIRCLE", "TRIANGLE", "SQUARE", "HEXAGON", "OCTAGON"
};
ExampleLayer* ExampleLayer::createWithThemeLevel(BasicScene* fa, int themen, int lev) {
	auto layer = ExampleLayer::create();
	if (layer->initWithThemeLevel(fa, themen, lev)) return layer;
	return nullptr;
}

bool ExampleLayer::initWithThemeLevel(BasicScene* fa, int themen, int lev) {
	container = fa;
	theme = themen;
	level = lev;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	int nv = num_vertex[level-1];
	if (nv == 0) {
		for (int i = 0; i < 1000; ++ i) {
			points.push_back(Vec2(cos(2*PI/1000*i), sin(2*PI/1000*i)));
		}
	} else {
		std::vector <Vec2> v;
		for (int i = 0; i < nv; ++ i) {
			v.push_back(Vec2(cos(PI*(1+2*i)/ nv), sin(PI*(1+2*i)/ nv)) );
		}
		v.push_back(v[0]);
		for (int i = 0; i < nv; ++ i) {
			points.push_back(v[i]);
			int np = 1000 / nv;
			Vec2 dir = (v[i + 1] - v[i]) / np;
			for (int j = 1; j < np; ++ j) {
				points.push_back(v[i] + dir*j );
			}
		}

	}
	npoints = points.size();
	
	float minx = points[0].x, maxx = points[0].x, miny = points[0].y, maxy = points[0].y;
	Util::minmaxify(points, minx, maxx, miny, maxy);
	float resol = std::min( 0.7 * visibleSize.width / (maxx - minx), 0.7 * visibleSize.height / (maxy - miny));
	for (int i = 0; i < npoints; ++i) {
		points[i].x = points[i].x * resol + visibleSize.width / 2;
		points[i].y = points[i].y * resol + visibleSize.height / 2;
	}

	auto cg = Sprite::create("Backgroundforscenepolygon.png");
	cg->setScaleX(visibleSize.width / cg->getContentSize().width);
	cg->setScaleY(visibleSize.height / cg->getContentSize().height);
	cg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(cg);

	drawNode = DrawNode::create();
	this->addChild(drawNode);
	//drawNode->drawPolygon(&points[0], npoints, Color4F::WHITE, 2, Color4F(Color3B(0x4c, 0x42, 0x34)));

	//auto bubble = Sprite::create("Bubble-Text.png");
	//bubble->setScale(311.0 / 968.3f * visibleSize.width / bubble->getContentSize().width);
	//bubble->setAnchorPoint(Vec2(0,1));
	//bubble->setPosition(0, visibleSize.height);
	//this->addChild(bubble);

	auto box = Sprite::create("chestboxclosed.png");
	box->setScale(197.0f / 968.3f * visibleSize.width / box->getContentSize().width);
	box->setAnchorPoint(Vec2::ZERO);
	box->setPosition(0, 0);
	this->addChild(box);

	timer = Sprite::create("timer_00.png");
	timer->setScale(143.0f / 968.3f * visibleSize.width / timer->getContentSize().width);
	timer->setPosition(880.0f / 968.3f * visibleSize.width, 490.0f / 544.65f * visibleSize.height);
	this->addChild(timer);

	tme = Label::createWithTTF("5", "cartoonist_kooky.ttf", 43);
	remainingT = 5.0f;
	totalT = 5.0f;
	drawedpoint = 0;
	tme->setColor(Color3B(0x4c, 0x42, 0x34));
	tme->setPosition(timer->getPosition());
	this->addChild(tme);

	auto shapename = Sprite::create("shapename.png");
	shapename->setScale(411.0f / 2017.0f * visibleSize.width / shapename->getContentSize().width);
	shapename->setPosition(1558.0f / 2017.0f * visibleSize.width, 48.0f / 1135.0f * visibleSize.height);
	shapename->setAnchorPoint(Vec2(0, 0));
	this->addChild(shapename);

	auto label3 = Label::createWithTTF(text[level - 1], "cartoonist_kooky.ttf", 32);
	label3->setAnchorPoint(Vec2(1, 0));
	label3->setPosition(visibleSize.width * 0.99f, 150.0f / 1135.0f  * visibleSize.height);
	label3->setScale(visibleSize.width / 1300.f);
	label3->setColor(Color3B(0x4c, 0x42, 0x34));
	label3->setAlignment(TextHAlignment::CENTER);
	this->addChild(label3);

	auto menu = Menu::create();

	auto skipItem = MenuItemImage::create("Skip.png", "SkipHover.png", CC_CALLBACK_1(ExampleLayer::onSkipCallback, this));
	skipItem->setScale(119.5f / 968.3f * visibleSize.width / skipItem->getContentSize().width);
	skipItem->setAnchorPoint(Vec2(0, 0));
	skipItem->setPosition(834.5f / 968.3f * visibleSize.width, 375.0f / 544.65f * visibleSize.height);
	menu->addChild(skipItem);
	//auto settingItem = MenuItemImage::create("Settings.png", "SettingsHover.png", CC_CALLBACK_1(ExampleLayer::onSettingCallBack, this));
	//settingItem->setScale(103.0f / 2017.0f * visibleSize.width / settingItem->getContentSize().width);
	//settingItem->setAnchorPoint(Vec2(0, 0));
	//settingItem->setPosition(1898.0f / 2017.0f * visibleSize.width, 15.0f / 1135.0f  * visibleSize.height);
	//auto menu = Menu::create(skipItem, settingItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	this->scheduleUpdate();
	if (Util::getInstance()->getMusic()) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		countEffect = SimpleAudioEngine::getInstance()->playEffect("countDown.wav", true);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		countEffect = SimpleAudioEngine::getInstance()->playEffect("countDown.ogg", true);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		countEffect = SimpleAudioEngine::getInstance()->playEffect("countDown.caf", true);
#endif
	}

	auto oneTouch = EventListenerTouchOneByOne::create();
	oneTouch->onTouchBegan = CC_CALLBACK_2(ExampleLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(oneTouch, this);

	return true;
}

void ExampleLayer::update(float dt) {
	remainingT -= dt;
	if (remainingT < 0) {
		tme->setString("0");
		remainingT = 0;
		if (Util::getInstance()->getMusic()) {
			SimpleAudioEngine::getInstance()->stopEffect(countEffect);
		}
		container->onSkipCallBack();
		this->removeFromParentAndCleanup(true);
		return;
	}
	int tempdrawedpoint = (totalT - remainingT) / totalT * npoints;
	for (int i = drawedpoint + 1; i <= tempdrawedpoint; ++i) {
		drawNode->drawLine(points[i - 1], points[i], Color4F(Color3B(0x4c, 0x42, 0x34)));
	}
	drawedpoint = tempdrawedpoint;
	//drawNode->drawPolygon(&points[0], npoints, Color4F::WHITE, 2, Color4F(Color3B(0x4c, 0x42, 0x34)));
	char todisplay[] = "0";
	int rT = ceil(remainingT);
	todisplay[0] = '0' + rT;
	tme->setString(todisplay);
	if (ceil(remainingT) != ceil(remainingT + dt) && rT >= 0 && rT <= 4) {
		char timerName[] = "timer_00.png";
		timerName[7] = '0' + 5 - rT;
		CCLOG("%s", timerName);
		timer->setTexture(timerName);
	}
}

void ExampleLayer::resumeFromHelpLayer() {
	if (Util::getInstance()->getMusic()) {
		SimpleAudioEngine::getInstance()->resumeEffect(countEffect);
	}
	this->scheduleUpdate();
}

bool ExampleLayer::onTouchBegan(Touch * touch, Event * event) {
	auto pos = Director::getInstance()->convertToUI(touch->getLocationInView());
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (pos < visibleSize*3.0f / 4.0f && pos > visibleSize*1.0f / 4.0f) {
		if (Util::getInstance()->getMusic()) {
			SimpleAudioEngine::getInstance()->stopEffect(countEffect);
		}
		container->onSkipCallBack();
		this->removeFromParentAndCleanup(true);
	}
	return true;
}

void ExampleLayer::onSkipCallback(Ref* sender) {
	if (Util::getInstance()->getMusic()) {
		SimpleAudioEngine::getInstance()->stopEffect(countEffect);
	}
	Util::getInstance()->playClick();
	container->onSkipCallBack();
	this->removeFromParentAndCleanup(true);
}

void ExampleLayer::onSettingCallBack(Ref * sender) {
	Util::getInstance()->playClick();
	if (Util::getInstance()->getMusic()) {
		SimpleAudioEngine::getInstance()->pauseEffect(countEffect);
	}
	this->unscheduleUpdate();
	container->onSettingCallBack(EXAMPLE_LAYER);
}

std::vector<Vec2> ExampleLayer::getPoints() {
	return points;
}