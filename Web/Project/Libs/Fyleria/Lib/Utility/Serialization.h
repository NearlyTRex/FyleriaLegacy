// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_SERIALIZATION_H_
#define _GECKO_SERIALIZATION_H_

#include "Utility/IndexedString.h"
#include "Utility/TypesSimple.h"
#include "Utility/TypesEnum.h"
#include "Utility/TypesJson.h"
#include "Utility/Macros.h"

namespace Gecko
{

// Read a binary file into a string
Bool ReadBinaryFile(const IndexedString& sFilename, FixedUnsigned8List& vBytes);

// Write a string to a binary file
Bool WriteBinaryFile(const IndexedString& sFilename, const FixedUnsigned8List& vBytes);

// Determine if bytes represent a CBOR file
Bool IsCBOR(const FixedUnsigned8List& vBytes);

// Determine if bytes represent a MsgPack file
Bool IsMsgPack(const FixedUnsigned8List& vBytes);

// Remove CBOR header
Bool RemoveCBORHeader(FixedUnsigned8List& vBytes);

// Remove MsgPack header
Bool RemoveMsgPackHeader(FixedUnsigned8List& vBytes);

// Read serialized file
Bool ReadSerializedFile(const IndexedString& sFilename, const IndexedString& sType, Json& jsonData);

// Read a file into a json object
Bool ReadJsonFile(const IndexedString& sFilename, Json& jsonData);
Bool ReadJsonFile(const IndexedString& sFilename, String& jsonString);

// Read a CBOR file into a json object
Bool ReadCBORFile(const IndexedString& sFilename, Json& jsonData);

// Read a MsgPack file into a json object
Bool ReadMsgPackFile(const IndexedString& sFilename, Json& jsonData);

// Write serialized file
Bool WriteSerializedFile(const IndexedString& sFilename, const IndexedString& sType, const Json& jsonData);

// Write a json object to a file
Bool WriteJsonFile(const IndexedString& sFilename, const Json& jsonData);
Bool WriteJsonFile(const IndexedString& sFilename, const String& jsonString);

// Write a json object to a CBOR file
Bool WriteCBORFile(const IndexedString& sFilename, const Json& jsonData);

// Write a json object to a MsgPack file
Bool WriteMsgPackFile(const IndexedString& sFilename, const Json& jsonData);

};

#endif
