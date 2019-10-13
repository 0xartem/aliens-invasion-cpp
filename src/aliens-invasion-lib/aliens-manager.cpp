#include <sstream>
#include "aliens-manager.h"
#include "alien.h"
#include "city.h"

namespace aliens_invasion
{
    void AliensManager::AddNewAlien(size_t id)
    {
        auto cityPosition = m_cityProvider.GetRandomCity();
        auto alien = std::make_shared<Alien>(id, cityPosition);
        m_aliensMap[id] = alien;
        cityPosition->EnterCity(alien, *this);
    }

    void AliensManager::OnAliensFight(const std::shared_ptr<Alien> &alienFirst,
                                      const std::shared_ptr<Alien> &alienSec,
                                      const std::shared_ptr<City> &city)
    {
        std::stringstream strm;
        strm << city->Name() << " has been destroyed by alien " <<
             std::to_string(alienFirst->GetId()) << " and alien " << std::to_string(alienSec->GetId());

        alienFirst->Kill();
        alienSec->Kill();
        m_cityProvider.DestroyCity(city->Name());

        m_outputObserver.OnCityDestroyed(strm.str());
    }

    void AliensManager::MoveAll()
    {
        for (auto it = m_aliensMap.begin(); it != m_aliensMap.end();)
        {
            /// Remove dead aliens from the map. We mark them dead when they fight,
            /// But delete during the next iteration to keep the map consistent during the cycle
            if (!it->second->IsAlive())
            {
                it = m_aliensMap.erase(it);
                continue;
            }

            if (!it->second->IsTrapped())
            {
                it->second->Move(*this);
            }
            ++it;
        }
    }

    bool AliensManager::AreAllDestroyed() const
    {
        return m_aliensMap.empty();
    }
}
