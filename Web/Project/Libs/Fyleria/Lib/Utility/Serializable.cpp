// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Utility/Serializable.h"

namespace Gecko
{

SerializableToJson::SerializableToJson()
    : m_Data()
{
}

SerializableToJson::SerializableToJson(const Json& jsonData)
    : m_Data(jsonData)
{
}

void SerializableToJson::FromJson(const Json& jsonData)
{
    m_Data = jsonData;
}

void SerializableToJson::FromJsonString(const String& sJsonString)
{
    m_Data = JsonParse(sJsonString.c_str());
}

const Json& SerializableToJson::ToJson() const
{
    return m_Data;
}

String SerializableToJson::ToJsonString(Int iIndent /*= -1*/) const
{
    return m_Data.dump(iIndent);
}

void SerializableToJson::FromCBOR(const FixedUnsigned8List& vCBOR)
{
    m_Data = JsonFromCBOR(vCBOR);
}

void SerializableToJson::FromMsgPack(const FixedUnsigned8List& vMsgPack)
{
    m_Data = JsonFromMsgPack(vMsgPack);
}

FixedUnsigned8List SerializableToJson::ToCBOR() const
{
    return JsonToCBOR(m_Data);
}

FixedUnsigned8List SerializableToJson::ToMsgPack() const
{
    return JsonToMsgPack(m_Data);
}

Bool SerializableToJson::FromFile(const IndexedString& sFilename)
{
    return ReadJsonFile(sFilename, m_Data);
}

Bool SerializableToJson::FromFilePath(const FilesystemPath& sFilenamePath)
{
    return ReadJsonFile(IndexedString(GetNativeFileLocation(sFilenamePath)), m_Data);
}

Bool SerializableToJson::FromCBORFile(const IndexedString& sFilename)
{
    return ReadCBORFile(sFilename, m_Data);
}

Bool SerializableToJson::FromMsgPackFile(const IndexedString& sFilename)
{
    return ReadMsgPackFile(sFilename, m_Data);
}

Bool SerializableToJson::ToFile(const IndexedString& sFilename) const
{
    return WriteJsonFile(sFilename, m_Data);
}

Bool SerializableToJson::ToFilePath(const FilesystemPath& sFilenamePath) const
{
    return WriteJsonFile(IndexedString(GetNativeFileLocation(sFilenamePath)), m_Data);
}

Bool SerializableToJson::ToCBORFile(const IndexedString& sFilename) const
{
    return WriteCBORFile(sFilename, m_Data);
}

Bool SerializableToJson::ToMsgPackFile(const IndexedString& sFilename) const
{
    return WriteMsgPackFile(sFilename, m_Data);
}

void SerializableToJson::Reset()
{
}

SerializableToJson::operator Json() const
{
    return m_Data;
}

void SerializableToJson::Clear()
{
    m_Data.clear();
}

Bool SerializableToJson::IsEmpty() const
{
    return m_Data.empty();
}

UInt SerializableToJson::GetSize() const
{
    return m_Data.size();
}

};
