// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_SERIALIZABLE_H_
#define _GECKO_SERIALIZABLE_H_

#include "Utility/Serialization.h"
#include "Utility/TypesFilesystem.h"

namespace Gecko
{

class SerializableToJson
{
public:

    // Constructors
    SerializableToJson();
    SerializableToJson(const Json& jsonData);

    // Serialization from/to json
    virtual void FromJson(const Json& jsonData);
    virtual void FromJsonString(const String& sJsonString);
    virtual const Json& ToJson() const;
    virtual String ToJsonString(Int iIndent = -1) const;

    // Serialization from/to CBOR/MsgPack
    virtual void FromCBOR(const FixedUnsigned8List& vCBOR);
    virtual void FromMsgPack(const FixedUnsigned8List& vMsgPack);
    virtual FixedUnsigned8List ToCBOR() const;
    virtual FixedUnsigned8List ToMsgPack() const;

    // Serialization from/to file
    virtual Bool FromFile(const IndexedString& sFilename);
    virtual Bool FromFilePath(const FilesystemPath& sFilenamePath);
    virtual Bool FromCBORFile(const IndexedString& sFilename);
    virtual Bool FromMsgPackFile(const IndexedString& sFilename);
    virtual Bool ToFile(const IndexedString& sFilename) const;
    virtual Bool ToFilePath(const FilesystemPath& sFilenamePath) const;
    virtual Bool ToCBORFile(const IndexedString& sFilename) const;
    virtual Bool ToMsgPackFile(const IndexedString& sFilename) const;

    // Reseting internal data
    virtual void Reset();

    // Type casts
    virtual operator Json() const;

    // Other information
    virtual void Clear();
    virtual Bool IsEmpty() const;
    virtual UInt GetSize() const;

protected:

    // JSON data
    Json m_Data;
};

};

#endif
