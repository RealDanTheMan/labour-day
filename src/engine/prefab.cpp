#include "prefab.hpp"
#include "debugging.hpp"

using namespace Engine;

std::unique_ptr<Prefab> Prefab::FromJSON(const std::string &filepath)
{
    bool good = false;
    configuru::Config cfg;

    try
    {
        cfg = configuru::parse_file(filepath, configuru::JSON);
        good = true;
    }
    catch(configuru::ParseError  &err)
    {
        D_ERR("Failed to parse json prefab file !");
        D_ERR(err.what());
    }
    
    if(good)
    {
        auto prf = std::make_unique<Prefab>();
        prf->m_entity = EntitySerialiser::Deserialise (cfg);

        if(prf->m_entity != nullptr)
        {
            return prf;
        }
    }

    return nullptr;
}

void Prefab::Unload()
{

}
