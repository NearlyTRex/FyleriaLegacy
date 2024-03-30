// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_UTILITY_SERIALIZATION_H_
#define _GECKO_UTILITY_SERIALIZATION_H_

// Internal includes
#include "Utility/Types.h"
#include "Utility/Enum.h"
#include "Utility/Json.h"
#include "Utility/Macros.h"

namespace Gecko
{

// Read a binary file into a string
Bool ReadBinaryFile(const String& sFilename, FixedUnsigned8Array& vBytes);

// Write a string to a binary file
Bool WriteBinaryFile(const String& sFilename, const FixedUnsigned8Array& vBytes);

// Determine if bytes represent a CBOR file
Bool IsCBOR(const FixedUnsigned8Array& vBytes);

// Determine if bytes represent a MsgPack file
Bool IsMsgPack(const FixedUnsigned8Array& vBytes);

// Remove CBOR header
Bool RemoveCBORHeader(FixedUnsigned8Array& vBytes);

// Remove MsgPack header
Bool RemoveMsgPackHeader(FixedUnsigned8Array& vBytes);

// Read serialized file
Bool ReadSerializedFile(const String& sFilename, const String& sType, Json& jsonData);

// Read a file into a json object
Bool ReadJsonFile(const String& sFilename, Json& jsonData);
Bool ReadJsonFile(const String& sFilename, String& jsonString);

// Read a CBOR file into a json object
Bool ReadCBORFile(const String& sFilename, Json& jsonData);

// Read a MsgPack file into a json object
Bool ReadMsgPackFile(const String& sFilename, Json& jsonData);

// Write serialized file
Bool WriteSerializedFile(const String& sFilename, const String& sType, const Json& jsonData);

// Write a json object to a file
Bool WriteJsonFile(const String& sFilename, const Json& jsonData);
Bool WriteJsonFile(const String& sFilename, const String& jsonString);

// Write a json object to a CBOR file
Bool WriteCBORFile(const String& sFilename, const Json& jsonData);

// Write a json object to a MsgPack file
Bool WriteMsgPackFile(const String& sFilename, const Json& jsonData);

};

#endif
