#ifndef ALIENS_INVASION__MAP_MANAGER_H
#define ALIENS_INVASION__MAP_MANAGER_H

#include <vector>
#include <random>
#include "aliens-invasion-interfaces.h"
#include "parse-utils.h"
#include "city.h"

namespace aliens_invasion
{
    class MapManager : public CityProvider
    {
    public:
        MapManager() = default;

        std::shared_ptr<City> BuildCity(const std::string &rawCity);
        void OutputAll(OutputObserver &outputObserver, bool outputAliens = true) const;
        bool IsMapEmpty() const;

        /// CityProvider
        std::shared_ptr<City> GetRandomCity() override;
        void DestroyCity(const std::string &name) override;

    private:
        std::unordered_map<std::string, std::shared_ptr<City>> m_citiesMap;
        std::random_device m_rndDev;
    };
}

#endif //ALIENS_INVASION__MAP_MANAGER_H
