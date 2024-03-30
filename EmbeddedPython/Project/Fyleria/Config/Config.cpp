// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

// Internal includes
#include "Config/Config.h"

namespace Gecko
{

Config::Config()
{
}

Config::Config(const Json& jsonData)
{
    from_json(jsonData, *this);
}

Config::Config(const String& jsonString)
{
    from_json(JsonParse(jsonString), *this);
}

Config::~Config()
{
}

void to_json(Json& jsonData, const Config& obj)
{
    // Screen dimensions
    SET_JSON_DATA(ScreenWidth);
    SET_JSON_DATA(ScreenHeight);
}

void from_json(const Json& jsonData, Config& obj)
{
    // Screen dimensions
    SET_OBJ_DATA(ScreenWidth, Int);
    SET_OBJ_DATA(ScreenHeight, Int);
}

};
