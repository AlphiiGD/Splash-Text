#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "ScalingLabel.hpp"
#include "SplashRead.hpp"

using namespace geode::prelude;

class $modify(ST_MenuLayer, MenuLayer)
{
	struct Fields
	{
		std::string m_SplashStr;
		static SplashRead* m_SplashRead;
		ScalingLabel* m_SplashText = nullptr;
	};

	bool init()
	{
		if (!MenuLayer::init())
		{
			return false;
		}
		
		if (!m_fields->m_SplashRead)
		{
			m_fields->m_SplashRead = new SplashRead();
			if (!m_fields->m_SplashRead->loadFile(Mod::get()->getResourcesDir() / "splash.splash"))
			{
				log::error("Failed to load file {}", Mod::get()->getResourcesDir() / "splash.splash");
			}

		#ifndef GEODE_IS_IOS
			auto extraPath = Mod::get()->getSettingValue<std::filesystem::path>("extra-splash-file");
			if (!extraPath.empty() && !m_fields->m_SplashRead->loadFile(extraPath))
			{
				log::error("Failed to load file {}", extraPath.string());
			}
		#endif // ifndef GEODE_IS_IOS
		}
		m_fields->m_SplashStr = m_fields->m_SplashRead->getRandomLine();
		auto mainTitle = getChildByIDRecursive("main-title");
		
		m_fields->m_SplashText = ScalingLabel::create(m_fields->m_SplashStr.c_str(), "goldFont.fnt");

		// The scale here is an inverse scaling function for text used pretty often for UI.
		m_fields->m_SplashText->setScale(0.5f / (1.0f + 0.05f * strlen(m_fields->m_SplashText->getLabel()->getString())));
		m_fields->m_SplashText->setPosition(
			// The magic numbers are the percentage offset to get the anchor point at the bottom right
			// of the actual text and not the sprite.
			mainTitle->getContentSize().width - mainTitle->getContentSize().width * 0.0175f,
			mainTitle->getContentSize().height * 0.1923f
		);

		m_fields->m_SplashText->setRotation(Mod::get()->getSettingValue<float>("splash-rotation"));
		mainTitle->addChild(m_fields->m_SplashText);
		
		return true;
	}

	void onEnter()
	{
		MenuLayer::onEnter();
		m_fields->m_SplashText->getLabel()->setString(m_fields->m_SplashStr.c_str());
		m_fields->m_SplashText->setScale(0.5f / (1.0f + 0.05f * strlen(m_fields->m_SplashText->getLabel()->getString())));
	}

	void onExit()
	{
		MenuLayer::onExit();
		m_fields->m_SplashStr = m_fields->m_SplashRead->getRandomLine();
	}
};

SplashRead* ST_MenuLayer::Fields::m_SplashRead = nullptr;
