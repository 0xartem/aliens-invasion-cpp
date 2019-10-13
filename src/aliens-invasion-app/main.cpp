#include <iostream>
#include <fstream>
#include "../aliens-invasion-lib/map-manager.h"
#include "../aliens-invasion-lib/aliens-manager.h"

class ConsoleObserver : public aliens_invasion::OutputObserver
{
public:
    void OnCityDestroyed(const std::string &out) override
    {
        std::cout << out << std::endl;
    }
    void OnCityAlive(const std::string &out) override
    {
        std::cout << out << std::endl;
    }
};

int main(int argc, char **argv)
{
    try
    {
        int argsCount = 3;
        if (argc != argsCount)
        {
            std::cerr << u8"You must provide a path to the world's map and amount of aliens. Usage: aliens-invasion map.txt N";
            return -1;
        }

        std::ifstream mapFile(argv[1], std::ios::in);
        if (!mapFile.is_open())
        {
            std::cerr << u8"Error: unable to open the map file: " << argv[1] << " for reading";
            return -1;
        }

        ConsoleObserver outputObserver;
        aliens_invasion::MapManager mapManager;

        std::string rawCity;
        while (std::getline(mapFile, rawCity))
        {
            mapManager.BuildCity(rawCity);
        }

        int aliensSize = std::stoi(argv[2]);
        aliens_invasion::AliensManager aliensManager(mapManager, outputObserver);

        for (auto i = 0; i < aliensSize; ++i)
        {
            aliensManager.AddNewAlien(i);
        }

        for (auto i = 0; i < 10000; ++i)
        {
            if (aliensManager.AreAllDestroyed())
                break;

            aliensManager.MoveAll();
        }

        if (mapManager.IsMapEmpty())
            std::cout << "The map is empty!" << std::endl;
        else
            mapManager.OutputAll(outputObserver, true);
    }
    catch (const std::exception &ex)
    {
        std::cerr << ex.what();
    }
    catch (...)
    {
        std::cerr << "Unknown error" << std::endl;
    }

    std::cin.get();
    return 0;
}