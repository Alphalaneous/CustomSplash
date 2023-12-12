#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include <Geode/loader/SettingNode.hpp>

#include <random>

using namespace geode::prelude;

bool randomBoolean();
std::vector<std::string> splitString(const std::string& str, const std::string& delimiter);
int random(int min, int max);

class $modify(LoadingLayer) {
	
	char const* getLoadingString()
    {

		auto dontReplace = Mod::get()->getSettingValue<bool>("dont-replace");

        ghc::filesystem::path path = Mod::get()->getConfigDir().append("splash.txt");

        std::ifstream input(path.string());
        std::stringstream buffer;
        buffer << input.rdbuf();
        input.close();

		std::string splashText = buffer.str();

		if(dontReplace && randomBoolean()){
			return LoadingLayer::getLoadingString();
		}

		std::vector<std::string> splashSplit = splitString(splashText, "\n");
		std::string newSplash = splashSplit.at(random(0, splashSplit.size()-1));

        return newSplash.c_str();
    } 

};

bool randomBoolean() 
{
	static std::default_random_engine generator(std::random_device{}());
	static std::bernoulli_distribution distribution(0.5);
	return distribution(generator);
}

std::vector<std::string> splitString(const std::string& str, const std::string& delimiter)
{
    std::vector<std::string> strings;

    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != std::string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + delimiter.size();
    }

    strings.push_back(str.substr(prev));

    return strings;
}

int random(int min, int max)
{
	static bool first = true;
	if (first) 
	{  
		srand( time(NULL) );
		first = false;
	}
	return min + rand() % (( max + 1 ) - min);
}

$on_mod(Loaded){

    ghc::filesystem::path path = Mod::get()->getConfigDir().append("splash.txt");

    if(!ghc::filesystem::exists(path)){
        std::ofstream { path };
    }
}
