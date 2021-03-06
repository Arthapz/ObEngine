#include <cmath>

#include <Time/FramerateManager.hpp>
#include <Time/TimeUtils.hpp>

namespace obe
{
    namespace Time
    {
        FramerateManager::FramerateManager(sf::RenderWindow& window, vili::ComplexAttribute& config)
        {
            m_frameLimiterClock = getTickSinceEpoch();
            m_limitFPS = (config.contains(vili::AttributeType::BaseAttribute, "framerateLimit")) ? config.at<vili::BaseAttribute>("framerateLimit") : true;
            m_framerateTarget = (config.contains(vili::AttributeType::BaseAttribute, "framerateTarget")) ? config.at<vili::BaseAttribute>("framerateTarget") : 60;
            m_vsyncEnabled = (config.contains(vili::AttributeType::BaseAttribute, "vsync")) ? config.at<vili::BaseAttribute>("vsync") : true;
            m_reqFramerateInterval = 1.0 / static_cast<double>(m_framerateTarget);
            m_currentFrame = 0;
            m_frameProgression = 0;
            m_needToRender = false;
            window.setVerticalSyncEnabled(m_vsyncEnabled);
        }

        void FramerateManager::update()
        {
            sf::Time timeBuffer = m_deltaClock.restart();
            m_deltaTime = static_cast<double>(timeBuffer.asMicroseconds()) / 1000000.0;
            if (m_limitFPS)
            {
                if (getTickSinceEpoch() - m_frameLimiterClock > 1000)
                {
                    m_frameLimiterClock = getTickSinceEpoch();
                    m_currentFrame = 0;
                }
                m_frameProgression = round((getTickSinceEpoch() - m_frameLimiterClock) / (m_reqFramerateInterval * 1000));
                m_needToRender = false;
                if (m_frameProgression > m_currentFrame)
                {
                    m_currentFrame = m_frameProgression;
                    m_needToRender = true;
                }
            }
        }

        double FramerateManager::getDeltaTime() const
        {
            return m_deltaTime;
        }

        double FramerateManager::getGameSpeed() const
        {
            return m_deltaTime * m_speedCoeff;
        }

        double FramerateManager::getSpeedCoeff() const
        {
            return m_speedCoeff;
        }

        bool FramerateManager::isFramerateLimited() const
        {
            return m_limitFPS;
        }

        unsigned int FramerateManager::getFramerateTarget() const
        {
            return m_framerateTarget;
        }

        bool FramerateManager::isVSyncEnabled() const
        {
            return m_vsyncEnabled;
        }

        void FramerateManager::setSpeedCoeff(double speed)
        {
            m_speedCoeff = speed;
        }

        void FramerateManager::limitFramerate(bool state)
        {
            m_limitFPS = state;
        }

        void FramerateManager::setFramerateTarget(unsigned int limit)
        {
            m_framerateTarget = limit;
        }

        void FramerateManager::setVSyncEnabled(sf::RenderWindow& window, bool vsync)
        {
            m_vsyncEnabled = vsync;
            window.setVerticalSyncEnabled(vsync);
        }

        bool FramerateManager::doRender() const
        {
            return (!m_limitFPS || m_needToRender);
        }
    }
}
