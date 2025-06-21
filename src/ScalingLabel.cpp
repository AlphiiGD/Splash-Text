#include "ScalingLabel.hpp"

using namespace geode::prelude;

ScalingLabel::ScalingLabel(std::string text, std::string fntFile, float scalingFactor)
	: m_Text(text), m_FntFile(fntFile), m_ScalingFactor(scalingFactor)
{
}

bool ScalingLabel::init()
{
	if (!CCNode::init())
	{
		return false;
	}

	m_Label = CCLabelBMFont::create(m_Text.c_str(), m_FntFile.c_str());
	addChild(m_Label);
	scheduleUpdate();
	return true;
}

void ScalingLabel::update(float dt)
{
	if (m_ShouldShrink)
	{
		m_Label->setScale(m_Label->getScale() - m_ScalingFactor * dt);
		if (m_Label->getScale() <= 0.7f)
		{
			m_ShouldShrink = false;
		}
	}
	else
	{
		m_Label->setScale(m_Label->getScale() + m_ScalingFactor * dt);
		if (m_Label->getScale() >= 1.3f)
		{
			m_ShouldShrink = true;
		}
	}
}

ScalingLabel* ScalingLabel::create(std::string text, std::string fntFile, float scalingFactor)
{
	auto ret = new ScalingLabel(text, fntFile, scalingFactor);
	if (ret->init())
	{
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}