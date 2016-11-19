#include "Util.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

static Util *s_SharedUtil = nullptr;

Util* Util::getInstance() {
	if (!s_SharedUtil) {
		s_SharedUtil = new Util();
		s_SharedUtil->music = true;
	}
	return s_SharedUtil;
}
float Util::cross(Vec2 A, Vec2 B, Vec2 C) {
	return (B.x - A.x)*(C.y - A.y) - (C.x - A.x)*(B.y - A.y);
}
void Util::simplify(std::vector<Vec2> &v, Vec2 cen) {
	int sz = v.size();
	Vec2 centroid = Vec2(0,0);
	for (int i = 0; i < sz; ++i) {
		centroid += v[i];
	}
	centroid = centroid / sz;
	for (int i = 0; i < sz; ++i) {
		v[i] += cen - centroid;
	}
	CCLOG("Centroid: %.3lf %.3lf", centroid.x, centroid.y);
	std::sort(v.begin(), v.end());
	std::vector<Vec2> stk;
	for (int i = 0; i < sz; i++) {
		while (stk.size() > 1 && Util::cross(stk[stk.size() - 2], stk[stk.size() - 1], v[i])<=0) stk.pop_back();
		stk.push_back(v[i]);
	}
	int k = stk.size();
	for (int i = sz - 2; i >= 0; i--) {
		while (stk.size() > k && Util::cross(stk[stk.size() - 2], stk[stk.size() - 1], v[i])<=0) stk.pop_back();
		stk.push_back(v[i]);
	}
	if (sz > 1) stk.pop_back();
	v = stk;
}
bool Util::inPolygon(Vec2 p, std::vector<Vec2> &v) {
	int sz = v.size();
	if (sz < 3) return false;
	if (Util::cross(v[0], p, v[1]) > -1e-6) return false;
	if (Util::cross(v[0], p, v[sz - 1]) < 1e-6) return false;

	int i = 2, j = sz - 1;
	int line = -1;

	while (i <= j) {
		int mid = (i + j) >> 1;
		if (Util::cross(v[0], p, v[mid])>-1e-6) {
			line = mid;
			j = mid - 1;
		}
		else i = mid + 1;
	}
	return Util::cross(v[line - 1], p, v[line]) < -1e-6;
}
void Util::minmaxify(std::vector<Vec2> &v, float &minx, float &maxx, float &miny, float &maxy) {
	for (int i = 0; i < v.size(); ++i) {
		minx = std::min(minx, v[i].x);
		maxx = std::max(maxx, v[i].x);
		miny = std::min(miny, v[i].y);
		maxy = std::max(maxy, v[i].y);
	}
}
float Util::randomAB(float a, float b) {
	return rand()*1.0 / RAND_MAX*(b - a) + a;
}
double Util::calcSimilarity(std::vector<Vec2> &a, std::vector<Vec2> &b, Size visibleSize) {
	CCLOG("before calculation: %d %d", a.size(), b.size());
	Util::simplify(a, Vec2(visibleSize.width/2, visibleSize.height/2));
	Util::simplify(b, Vec2(visibleSize.width / 2, visibleSize.height / 2));
	float minx = a[0].x, maxx = a[0].x, miny = a[0].y, maxy = a[0].y;
	Util::minmaxify(a, minx, maxx, miny, maxy);
	Util::minmaxify(b, minx, maxx, miny, maxy);
	int total = 10000, cnt = 0;
	for (int i = 0; i < total; ++i) {
		Vec2 p = Vec2(Util::randomAB(minx, maxx), Util::randomAB(miny, maxy));
		if (Util::inPolygon(p, a) == Util::inPolygon(p, b)) cnt++;
	}
	double similarity = cnt*1.0 / total;
	CCLOG("similarity %d %d %.3lf", a.size(), b.size(), similarity);
	return similarity;
}

std::vector<Vec2> Util::smoothify(std::vector<Vec2>& pts) {
	std::vector<Vec2> ret;
	ret.push_back(pts[0]);
	for (int i = 1; i < pts.size(); ++i) {
		Vec2 p = pts[i - 1];
		Vec2 q = pts[i];
		if (p.distance(q) > 2.0f) {
			Vec2 dir = Vec2(p, q) / p.distance(q);
			while (1) {
				Vec2 r = p + dir;
				ret.push_back(r);
				if (r.distance(q) < 2.0f) {
					break;
				}
				p = r;
			}
		}
		ret.push_back(q);
	}
	return ret;
}

void Util::setMusic(bool flag) {
	s_SharedUtil->music = flag;
}

bool Util::getMusic() {
	return s_SharedUtil->music;
}

void Util::playClick() {
	if (s_SharedUtil->music) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		SimpleAudioEngine::getInstance()->playEffect("click.wav");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		SimpleAudioEngine::getInstance()->playEffect("click.ogg");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		SimpleAudioEngine::getInstance()->playEffect("click.caf");
#endif
	}
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
const char audioName[][20] = {
	"mandysteps.wav", // MANDY_RUN,
	"StartScreen.mp3", // START_SCREEN,
	"ThemePark.mp3", // THEME_PARK,
	"LevelsScreen.mp3" // LEVELS_SCREEN
};
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
const char audioName[][20] = {
	"mandysteps.ogg",
	"StartScreen.mp3", // START_SCREEN,
	"ThemePark.mp3", // THEME_PARK,
	"LevelsScreen.mp3" // LEVELS_SCREEN
};
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
const char audioName[][20] = {
	"mandysteps.caf",
	"StartScreen.mp3", // START_SCREEN,
	"ThemePark.mp3", // THEME_PARK,
	"LevelsScreen.mp3" // LEVELS_SCREEN
};
#endif

int Util::startAudio(AudioEnum a) {
	if (s_SharedUtil->music) {
		return SimpleAudioEngine::getInstance()->playEffect(audioName[a], true);
	}
	return -1;
}

void Util::stopAudio(int id) {
	if (id != -1) {
		SimpleAudioEngine::getInstance()->stopEffect(id);
	}
}

void Util::startBackgroundMusic(AudioEnum a) {
	if (s_SharedUtil->music) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(audioName[a], true);
	}
}

void Util::stopBackgroudMusic() {
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
