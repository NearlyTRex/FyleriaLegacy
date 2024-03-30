// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_UTILITY_JSON_H_
#define _GECKO_UTILITY_JSON_H_

// External includes
#include <nlohmann/json.hpp>

// Internal includes
#include "Utility/Types.h"
#include "Utility/Macros.h"

// Json defines
#define JsonParse nlohmann::json::parse
#define JsonToCBOR nlohmann::json::to_cbor
#define JsonToMsgPack nlohmann::json::to_msgpack
#define JsonFromCBOR nlohmann::json::from_cbor
#define JsonFromMsgPack nlohmann::json::from_msgpack

namespace Gecko
{

// Json basic types
typedef nlohmann::json Json;

// Json container types
typedef STDVector<Json> JsonArray;
typedef STDMap<Int, Json> JsonIntMap;
typedef STDMap<String, Json> JsonStringMap;

};

#endif
