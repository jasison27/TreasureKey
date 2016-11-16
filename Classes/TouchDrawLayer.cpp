#include "TouchDrawLayer.h"
#include "Util.h"

TouchDrawLayer * TouchDrawLayer::createWithNothing(BasicScene* fa, std::vector<Vec2> &pts) {
	auto layer = TouchDrawLayer::create();
	if (layer->initWithNothing(fa, pts)) return layer;
	return nullptr;
}

bool TouchDrawLayer::initWithNothing(BasicScene* fa, std::vector<Vec2> &pts) {
	container = fa;
	hint = false;
	expoints = pts;

	points.clear();

	auto visibleSize = Director::getInstance()->getVisibleSize();

	cursor = Sprite::create("Cursor.png");
	cursor->setPosition(visibleSize / 2);
	cursor->setAnchorPoint(Vec2(0, 0));
	cursor->setScale(180.0 / 1944 * visibleSize.width / cursor->getContentSize().width);
	this->addChild(cursor, 3);

	pointsTmp.clear();
	pointsVec.clear();

	auto oneTouch = EventListenerTouchOneByOne::create();
	oneTouch->onTouchBegan = CC_CALLBACK_2(TouchDrawLayer::onTouchBegan, this);
	oneTouch->onTouchMoved = CC_CALLBACK_2(TouchDrawLayer::onTouchMoved, this);
	oneTouch->onTouchEnded = CC_CALLBACK_2(TouchDrawLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(oneTouch, this);

	auto cg = Sprite::create("Backgroundforscene4_5_6.png");
	auto sc = std::max(visibleSize.width / cg->getContentSize().width, visibleSize.height / cg->getContentSize().height);
	cg->setScale(sc);
	cg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(cg, 0);

	auto cgbg = LayerColor::create(Color4B::WHITE);
	cgbg->setContentSize(Size(900.0f / 969.0f * visibleSize.width, 490.0f / 554.0f * visibleSize.height));
	cgbg->setPosition(34.5f / 969.0f * visibleSize.width, 32.0f / 554.0f * visibleSize.height);
	this->addChild(cgbg, 0);

	l = 34.5f / 969.0f * visibleSize.width;
	r = 934.5f / 969.0f * visibleSize.width;
	d = 32.0f / 554.0f * visibleSize.height;
	u = 552.0f / 554.0f * visibleSize.height;

	drawNode = DrawNode::create();
	this->addChild(drawNode);
	tmpDrawNode = DrawNode::create();
	this->addChild(tmpDrawNode, 1);
	exDrawNode = DrawNode::create();
	Vec2 *expointer = &expoints[0];
	exDrawNode->drawPoints(expointer, expoints.size(), 3, Color4F(Color3B(0xf4, 0xb2, 0x1e)));
	exDrawNode->setVisible(false);
	this->addChild(exDrawNode, 4);

	box = Sprite::create("chestboxhint.png");
	box->setScale(197.0f / 968.3f * visibleSize.width / box->getContentSize().width);
	box->setAnchorPoint(Vec2::ZERO);
	box->setPosition(0, 0);
	this->addChild(box);

//	doneItem = MenuItemImage::create("Done.png", "DoneHover.png", CC_CALLBACK_1(TouchDrawLayer::onDoneCallback, this));
//	doneItem->setScale(129.0f / 949.0f * visibleSize.width / doneItem->getContentSize().width);
//	doneItem->setAnchorPoint(Vec2(0, 0));
//	doneItem->setPosition( 11.3f / 949.0f * visibleSize.width, 462.0f / 554.0f * visibleSize.height);

	closeItem = MenuItemImage::create("Exit.png", "ExitHover.png", CC_CALLBACK_1(TouchDrawLayer::onCloseCallBack, this));
	closeItem->setScale(103.0f / 2017.0f * visibleSize.width / closeItem->getContentSize().width);
	closeItem->setAnchorPoint(Vec2(0, 0));
	closeItem->setPosition(1898.0f / 2017.0f * visibleSize.width, 1015.0f / 1135.0f  * visibleSize.height);

	settingItem = MenuItemImage::create("Settings.png", "SettingsHover.png", CC_CALLBACK_1(TouchDrawLayer::onSettingCallBack, this));
	settingItem->setScale(103.0f / 2017.0f * visibleSize.width / settingItem->getContentSize().width);
	settingItem->setAnchorPoint(Vec2(0, 0));
	settingItem->setPosition(1898.0f / 2017.0f * visibleSize.width, 15.0f / 1135.0f  * visibleSize.height);

//	auto menu = Menu::create(doneItem, closeItem, settingItem, NULL);
	auto menu = Menu::create(closeItem, settingItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void TouchDrawLayer::calcPoints() {
	points.clear();
	for (size_t i = 0; i < pointsVec.size(); ++i) {
		size_t sz = pointsVec[i].size();
		for (size_t j = 0; j < sz; ++j) {
			points.push_back(pointsVec[i][j]);
		}
	}
}

void TouchDrawLayer::onCloseCallBack(Ref* pSender) {
	Util::getInstance()->playClick();
	container->onSelectThemeCallBack(0);
	this->removeFromParentAndCleanup(true);
}

void TouchDrawLayer::onDone() {
	drawNode->clear();
	calcPoints();
	for (size_t i = 1; i < expoints.size(); ++i) {
		drawNode->drawLine(expoints[i - 1], expoints[i], Color4F(Color3B(0xf4, 0xb2, 0x1e)));
	}
	drawNode->drawLine(expoints.back(), expoints.front(), Color4F(Color3B(0xf4, 0xb2, 0x1e)));
	if (points.size() > 5) {
		for (size_t i = 1; i < points.size(); ++i) {
			drawNode->drawLine(points[i - 1], points[i], Color4F(Color3B(0x4c, 0x42, 0x34)));
		}
		drawNode->drawLine(points.back(), points.front(), Color4F(Color3B(0x4c, 0x42, 0x34)));
	}
	container->onFinishDrawCallBack();
}

void TouchDrawLayer::onSettingCallBack(Ref * sender) {
	Util::getInstance()->playClick();
	container->onSettingCallBack(TOUCHDRAW_LAYER);
}

float TouchDrawLayer::calcSimilarity() {
	float similarity = 0;
	if (points.size() > 5) {
		similarity = Util::getInstance()->calcSimilarity(expoints, points, Director::getInstance()->getVisibleSize());
	}
	return similarity;
}

void TouchDrawLayer::getRetry() {
	points.clear();
	pointsTmp.clear();
	pointsVec.clear();;
	drawNode->clear();;
	tmpDrawNode->clear();
}

bool TouchDrawLayer::onTouchBegan(Touch * touch, Event * event) {
	pointsTmp.clear();
	tmpDrawNode->clear();
	auto pos = Director::getInstance()->convertToUI(touch->getLocationInView());
	if (box->getBoundingBox().containsPoint(pos)) {
		hint = true;
		exDrawNode->setVisible(true);
		return true;
	}
	if (pos.x <= l || pos.x >= r || pos.y <= d || pos.y >= u || closeItem->getBoundingBox().containsPoint(pos) || settingItem->getBoundingBox().containsPoint(pos)) {
		return false;
	}
	cursor->setPosition(pos);
	CCLOG("touch began: %.2lf %.2lf\n", pos.x, pos.y);
	pointsTmp.push_back(pos);
	tmpDrawNode->drawPoint(pos, 3, Color4F(Color3B(0x4c, 0x42, 0x34)));
	return true;
}

void TouchDrawLayer::onTouchMoved(Touch * touch, Event * event) {
	if (hint) return;
	auto pos = Director::getInstance()->convertToUI(touch->getLocationInView());
	if (pos.x <= l || pos.x >= r || pos.y <= d || pos.y >= u || closeItem->getBoundingBox().containsPoint(pos) || settingItem->getBoundingBox().containsPoint(pos)) {
		return;
	}
	cursor->setPosition(pos);
	tmpDrawNode->drawLine(pointsTmp.back(), pos, Color4F(Color3B(0x4c, 0x42, 0x34)));
	pointsTmp.push_back(pos);
}

void TouchDrawLayer::onTouchEnded(Touch * touch, Event * event) {
	if (hint) {
		hint = false;
		exDrawNode->setVisible(false);
		return;
	}
	pointsVec.push_back(Util::getInstance()->smoothify(pointsTmp));
	pointsTmp.clear();
	tmpDrawNode->clear();
	onDone();
//	Vec2 *pts = &pointsVec.back()[0];
//	drawNode->drawPoints(pts, pointsVec.back().size(), 3, Color4F(Color3B(0x4c, 0x42, 0x34)));
//	CCLOG("#last added points: %d", pointsVec.back().size());
}
