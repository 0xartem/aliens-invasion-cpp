#include <random>
#include <sstream>
#include "city.h"
#include "alien.h"

namespace aliens_invasion
{
    const std::string City::NORTH = "north";
    const std::string City::SOUTH = "south";
    const std::string City::WEST = "west";
    const std::string City::EAST = "east";

    std::map<std::string, std::string> City::oppositeDirectionsMap = {
        {NORTH, SOUTH},
        {SOUTH, NORTH},
        {WEST, EAST},
        {EAST, WEST}
    };

    void City::SetDirection(const std::string &direction, const std::shared_ptr<City> &directionCity)
    {
        if (direction == NORTH)
        {
            m_directions[NORTH] = directionCity;
        }
        else if (direction == SOUTH)
        {
            m_directions[SOUTH] = directionCity;
        }
        else if (direction == WEST)
        {
            m_directions[WEST] = directionCity;
        }
        else if (direction == EAST)
        {
            m_directions[EAST] = directionCity;
        }
        else
        {
            throw std::runtime_error("Invalid city direction");
        }
    }

    bool City::DirectionExists(const std::string &direction) const
    {
        return m_directions.find(direction) != m_directions.end();
    }

    bool City::GetDirection(const std::string &direction, std::shared_ptr<City> &city) const
    {
        auto it = m_directions.find(direction);
        if (it != m_directions.end())
        {
            city = it->second;
            return true;
        }
        return false;
    }

    bool City::GetRandomDirection(std::shared_ptr<City> &city) const
    {
        if (m_directions.empty())
            return false;

        if (m_directions.size() == 1)
        {
            city = m_directions.begin()->second;
        }
        else
        {
            std::random_device rndDev;
            std::mt19937 mt(rndDev());
            std::uniform_int_distribution<size_t> dist(0, m_directions.size() - 1);
            auto randomIt = std::next(m_directions.begin(), dist(mt));
            city = randomIt->second;
        }
        return true;
    }

    void City::EnterCity(const std::shared_ptr<Alien> &alien, FightObserver &fightObserver)
    {
        /// I suppose that third alien cannot enter the city, as soon as the second alien arrives,
        /// the city must be destroyed. So the second alien must always be null
        assert(m_alienFighters.second == nullptr);

        if (m_alienFighters.first == nullptr)
        {
            m_alienFighters.first = alien;
        }
        else
        {
            m_alienFighters.second = alien;
            fightObserver.OnAliensFight(m_alienFighters.first, m_alienFighters.second, shared_from_this());
        }
    }

    bool City::LeaveCity(const std::shared_ptr<Alien> &alien)
    {
        /// I suppose that third alien cannot enter the city, as soon as the second alien arrives,
        /// the city must be destroyed. So the second alien must always be null
        assert(m_alienFighters.second == nullptr);

        /// The alien that wants to leave the city must be in the city at this moment
        /// He must be the the only one in the city
        assert(m_alienFighters.first == alien);
        m_alienFighters.first.reset();
        return true;
    }

    bool City::RemoveOppositeConnectionIfExists(const std::string &direction, const std::string &cityName)
    {
        auto it = m_directions.find(direction);
        if (it != m_directions.end() && it->second->Name() == cityName)
        {
            m_directions.erase(it);
            return true;
        }
        return false;
    }

    bool City::RuinSelf()
    {
        /// Two aliens must be in the city to ruin it
        if (m_alienFighters.first == nullptr || m_alienFighters.second == nullptr)
            return false;

        for (auto &[direction, city] : m_directions)
        {
            city->RemoveOppositeConnectionIfExists(oppositeDirectionsMap[direction], m_name);
        }
        m_alienFighters.second.reset();
        m_alienFighters.first.reset();
        m_directions.clear();
        return true;
    }

    std::string City::ToString(bool showAlienIfExists) const
    {
        std::stringstream out;
        out << m_name << " ";
        for (auto &[direction, city] : m_directions)
        {
            out << direction << "=" << city->Name() << " ";
        }
        if (showAlienIfExists && m_alienFighters.first != nullptr)
        {
            if (m_alienFighters.first->IsTrapped())
                out << "(Alien " << m_alienFighters.first->GetId() << " is trapped)";
            else
                out << "(Alien " << m_alienFighters.first->GetId() << " is wandering here)";
        }
        return out.str();
    }
}