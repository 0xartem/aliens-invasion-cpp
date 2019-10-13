#ifndef ALIENS_INVASION__ALIENS_MANAGER_H
#define ALIENS_INVASION__ALIENS_MANAGER_H

#include <unordered_map>
#include "aliens-invasion-interfaces.h"

namespace aliens_invasion
{
    class AliensManager : public FightObserver
    {
    public:
        explicit AliensManager(CityProvider &cityProvider, OutputObserver &outputObserver)
            : m_cityProvider(cityProvider), m_outputObserver(outputObserver)
        {
        }

        void AddNewAlien(size_t id);
        void MoveAll();
        bool AreAllDestroyed() const;

        /// FightObserver
        void OnAliensFight(const std::shared_ptr<Alien> &alienFirst,
                           const std::shared_ptr<Alien> &alienSec,
                           const std::shared_ptr<City> &city) override;

    private:
        CityProvider &m_cityProvider;
        OutputObserver &m_outputObserver;
        std::unordered_map<size_t, std::shared_ptr<Alien>> m_aliensMap;
    };
}

#endif //ALIENS_INVASION__ALIENS_MANAGER_H
