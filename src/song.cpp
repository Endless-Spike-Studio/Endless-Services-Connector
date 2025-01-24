#include <Geode/modify/SongInfoLayer.hpp>

using namespace geode::prelude;

class $modify(ProxySongInfoLayer, SongInfoLayer) {
    bool init(gd::string p0, gd::string p1, gd::string p2, gd::string p3, gd::string p4, gd::string p5, int p6, gd::string p7, int p8) {
        if (!SongInfoLayer::init(p0, p1, p2, p3, p4, p5, p6, p7, p8)) {
            return false;
        }

        if (this->m_songID > 10000000) {
            return true;
        }

        auto sprite = CCSprite::create("button.png"_sprite);

        sprite->setScale(0.3);

        auto button = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(ProxySongInfoLayer::handleProxyButtonClick));
        auto position = ccp(387, -13);

        button->setPosition(position);
        button->setID("proxy"_sprite);

        m_mainLayer->getChildByType<CCMenu>(0)->addChild(button);

        return true;
    }

    void handleProxyButtonClick(CCObject*) {
    	auto command = fmt::format("start https://endless-services.zhazha120.cn/#/endless-proxy/newgrounds/audios/{}", this->m_songID).c_str();
        system(command);
    }
};