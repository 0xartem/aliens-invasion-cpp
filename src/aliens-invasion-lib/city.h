#ifndef ALIENS_INVASION__CITY_H
#define ALIENS_INVASION__CITY_H

#include <memory>
#include <string>
#include <unordered_map>
#include <map>
#include <cassert>
#include <random>
#include "aliens-invasion-interfaces.h"

namespace aliens_invasion
{
    class City : public std::enable_shared_from_this<City>
    {
    public:
        explicit City(std::string name)
            : m_name(std::move(name))
        {
        }

        const std::string &Name() const
        {
            return m_name;
        }
        bool IsIsolated() const
        {
            return m_directions.empty();
        }

        bool DirectionExists(const std::string &direction) const;
        bool GetDirection(const std::string &direction, std::shared_ptr<City> &city) const;
        bool GetRandomDirection(std::shared_ptr<City> &city) const;
        void SetDirection(const std::string &direction, const std::shared_ptr<City> &directionCity);

        bool LeaveCity(const std::shared_ptr<Alien> &alien);
        void EnterCity(const std::shared_ptr<Alien> &alien, FightObserver &fightObserver);

        bool RuinSelf();
        bool RemoveOppositeConnectionIfExists(const std::string &direction, const std::string &cityName);

        std::string ToString(bool showAlienIfExists = true) const;

        static std::string GetOppositeDirection(const std::string & direction)
        {
            return oppositeDirectionsMap[direction];
        }

    public:
        static const std::string NORTH;
        static const std::string SOUTH;
        static const std::string WEST;
        static const std::string EAST;

        static std::map<std::string, std::string> oppositeDirectionsMap;

    private:
        std::string m_name;
        std::map<std::string, std::shared_ptr<City>> m_directions;
        std::pair<std::shared_ptr<Alien>, std::shared_ptr<Alien>> m_alienFighters;
    };
}

#endif //ALIENS_INVASION__CITY_H
