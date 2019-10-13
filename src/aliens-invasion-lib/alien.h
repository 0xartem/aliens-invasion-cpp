#ifndef ALIENS_INVASION__ALIEN_H
#define ALIENS_INVASION__ALIEN_H

#include <memory>
#include <cassert>
#include "city.h"

namespace aliens_invasion
{
    class Alien : public std::enable_shared_from_this<Alien>
    {
    public:
        explicit Alien(int id, std::shared_ptr<City> position)
            : m_id(id), m_alive(true)
        {
            m_position = std::move(position);
        }

        [[nodiscard]] int GetId() const
        {
            return m_id;
        }
        [[nodiscard]] std::shared_ptr<City> GetCurrentCity() const
        {
            return m_position;
        }
        bool IsTrapped() const
        {
            return m_position->IsIsolated();
        }
        void Kill()
        {
            m_alive = false;
        }
        bool IsAlive() const
        {
            return m_alive;
        }

        bool Move(FightObserver &fightObserver)
        {
            assert(m_position != nullptr);

            std::shared_ptr<City> moveTo;
            if (!m_position->GetRandomDirection(moveTo))
            {
                /// the alien is trapped, so it cannot move
                return false;
            }
            m_position->LeaveCity(shared_from_this());
            m_position = std::move(moveTo);
            m_position->EnterCity(shared_from_this(), fightObserver);
        }

    private:
        int m_id;
        std::shared_ptr<City> m_position;
        bool m_alive;
    };
}

#endif //ALIENS_INVASION__ALIEN_H
