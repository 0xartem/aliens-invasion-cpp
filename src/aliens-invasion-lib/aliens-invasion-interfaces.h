
#ifndef ALIENS_INVASION_INTERFACES_H
#define ALIENS_INVASION_INTERFACES_H

#include <memory>

namespace aliens_invasion
{
    class City;
    class Alien;

    class FightObserver
    {
    public:
        virtual void OnAliensFight(const std::shared_ptr<Alien> &alienFirst,
                                   const std::shared_ptr<Alien> &alienSec,
                                   const std::shared_ptr<City> &city) = 0;
        virtual ~FightObserver() = default;
    };

    class CityProvider
    {
    public:
        [[nodiscard]] virtual std::shared_ptr<City> GetRandomCity() = 0;
        virtual void DestroyCity(const std::string &name) = 0;
        virtual ~CityProvider() = default;
    };

    class OutputObserver
    {
    public:
        virtual void OnCityDestroyed(const std::string &out) = 0;
        virtual void OnCityAlive(const std::string &out) = 0;
        virtual ~OutputObserver() = default;
    };
}

#endif //ALIENS_INVASION__ALIENS_INVASION_INTERFACES_H
