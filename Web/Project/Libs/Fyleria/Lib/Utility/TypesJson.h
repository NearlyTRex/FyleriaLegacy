// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_TYPES_JSON_H_
#define _GECKO_TYPES_JSON_H_

// External includes
#include <json.hpp>

// Internal includes
#include "Utility/TypesSimple.h"

// Json defines
#define JsonParse nlohmann::json::parse
#define JsonToCBOR nlohmann::json::to_cbor
#define JsonToMsgPack nlohmann::json::to_msgpack
#define JsonFromCBOR nlohmann::json::from_cbor
#define JsonFromMsgPack nlohmann::json::from_msgpack
#define JsonObject nlohmann::json::object
#define JsonArray nlohmann::json::array

namespace Gecko
{

// Json basic types
typedef nlohmann::json Json;

// Json container types
typedef STDVector<Json> JsonList;

};

#endif
