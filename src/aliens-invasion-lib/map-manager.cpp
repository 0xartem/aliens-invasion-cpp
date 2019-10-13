#include <iostream>
#include "map-manager.h"

namespace aliens_invasion
{
    std::shared_ptr<City> MapManager::BuildCity(const std::string &rawCity)
    {
        auto cityParams = utils::ParseUtils::SplitCityStr(rawCity);
        if (cityParams.empty())
            throw std::runtime_error("Invalid city definition");

        auto &newCity = m_citiesMap[cityParams[0]];
        if (newCity == nullptr)
        {
            newCity.reset(new City(cityParams[0]));
        }

        for (auto it = ++cityParams.begin(); it != cityParams.end(); ++it)
        {
            auto cityDirectionParams = utils::ParseUtils::ParseDirection(newCity->Name(), *it);
            auto &directionCity = m_citiesMap[cityDirectionParams.second];
            if (directionCity == nullptr)
            {
                directionCity.reset(new City(cityDirectionParams.second));
            }

            newCity->SetDirection(cityDirectionParams.first, directionCity);

            /// Fix links in case they are not in the input file
            auto oppositeDirection = City::GetOppositeDirection(cityDirectionParams.first);
            if (!directionCity->DirectionExists(oppositeDirection))
            {
                directionCity->SetDirection(oppositeDirection, newCity);
            }
        }
        return newCity;
    }

    bool MapManager::IsMapEmpty() const
    {
        return m_citiesMap.empty();
    }

    void MapManager::OutputAll(OutputObserver &outputObserver, bool outputAliens) const
    {
        for (const auto &element : m_citiesMap)
        {
            outputObserver.OnCityAlive(element.second->ToString(outputAliens));
        }
    }

    std::shared_ptr<City> MapManager::GetRandomCity()
    {
        if (m_citiesMap.empty())
            throw std::runtime_error("The map is empty. All cities have been destroyed.");

        std::mt19937 mt(m_rndDev());
        std::uniform_int_distribution<size_t> dist(0, m_citiesMap.size() - 1);
        auto randomIt = std::next(m_citiesMap.begin(), dist(mt));
        return randomIt->second;
    }

    void MapManager::DestroyCity(const std::string &name)
    {
        auto it = m_citiesMap.find(name);
        if (it == m_citiesMap.end())
            throw std::logic_error("The city is not on the map");

        if (!it->second->RuinSelf())
            throw std::logic_error("There are not enough aliens to ruin the city");
        m_citiesMap.erase(it);
    }
}
