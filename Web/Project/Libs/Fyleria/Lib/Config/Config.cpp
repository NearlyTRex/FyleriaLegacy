// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Config/Config.h"

namespace Gecko
{

Config::Config()
    : SerializableToJson()
{
}

Config::Config(const Json& jsonData)
    : SerializableToJson(jsonData)
{
}

Config::Config(const String& jsonString)
    : SerializableToJson(JsonParse(jsonString))
{
}

MAKE_JSON_BASIC_TYPE_CONVERTERS_IMPL(Config);
MAKE_JSON_GENERIC_TYPE_CONVERTERS_IMPL(Config, Config);

};
