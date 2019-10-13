#ifndef ALIENS_INVASION__PARSE_UTILS_H
#define ALIENS_INVASION__PARSE_UTILS_H

#include <vector>
#include <string>
#include <sstream>

namespace utils
{
    class ParseUtils
    {
    public:
        static std::vector<std::string> SplitCityStr(const std::string &rawCity)
        {
            std::vector<std::string> cityParams;
            std::istringstream strm(rawCity);
            std::string token;

            while (std::getline(strm, token, ' '))
            {
                cityParams.emplace_back(token);
            }
            return cityParams;
        }

        static std::pair<std::string, std::string> ParseDirection(const std::string &cityName,
                                                                  const std::string &cityDirection)
        {
            auto equalPos = cityDirection.find('=');
            if (equalPos == std::string::npos || cityDirection.size() <= equalPos + 1)
            {
                std::stringstream strm;
                strm << "Invalid direction: " << cityDirection << " from " << cityName;
                throw std::runtime_error(strm.str());
            }

            return std::make_pair(cityDirection.substr(0, equalPos), cityDirection.substr(equalPos + 1));
        }
    };
}

#endif //ALIENS_INVASION__PARSE_UTILS_H
