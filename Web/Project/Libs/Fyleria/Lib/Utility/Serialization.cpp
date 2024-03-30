// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Utility/Constants.h"
#include "Utility/Serialization.h"
#include "Utility/Logging.h"
#include "Utility/TypesFilesystem.h"

namespace Gecko
{

Bool ReadBinaryFile(const IndexedString& sFilename, FixedUnsigned8List& vBytes)
{
    // Check file existence
    FilesystemPath path(sFilename.Get());
    if(!DoesFileExist(path))
    {
        return false;
    }

    // Open binary file
    InputFile ifile(GetNativeFileLocation(path).c_str(), STDIOSFlagInputOperations | STDIOSFlagBinaryMode);
    if(!ifile.is_open() && ifile.good())
    {
        return false;
    }

    // Read binary data
    SizeType szLength = GetFileSize(path);
    for(SizeType index = 0; index < szLength; index++)
    {
        Byte byte;
        ifile.read(&byte, sizeof(Byte));
        vBytes.push_back(byte);
    }

    // Cleanup
    ifile.close();
    return true;
}

Bool WriteBinaryFile(const IndexedString& sFilename, const FixedUnsigned8List& vBytes)
{
    // Open binary file
    FilesystemPath path(sFilename.Get());
    OutputFile ofile(GetNativeFileLocation(path).c_str(), STDIOSFlagOutputOperations | STDIOSFlagBinaryMode | STDIOSFlagTruncate);
    if(!ofile.is_open() && ofile.good())
    {
        return false;
    }

    // Write binary data
    SizeType szLength = vBytes.size() * sizeof(FixedUnsigned8);
    for(SizeType index = 0; index < szLength; index++)
    {
        Byte byte = vBytes[index];
        ofile.write(&byte, sizeof(Byte));
    }

    // Cleanup
    ofile.close();
    return true;
}

Bool IsCBOR(const FixedUnsigned8List& vBytes)
{
    if(vBytes.size() < s_ksvBinaryMarkerCBR.size())
    {
        return false;
    }

    for(UInt i = 0; i < s_ksvBinaryMarkerCBR[i]; i++)
    {
        if(vBytes[i] != s_ksvBinaryMarkerCBR[i])
        {
            return false;
        }
    }
    return true;
}

Bool IsMsgPack(const FixedUnsigned8List& vBytes)
{
    if(vBytes.size() < s_ksvBinaryMarkerMSG.size())
    {
        return false;
    }

    for(UInt i = 0; i < s_ksvBinaryMarkerMSG[i]; i++)
    {
        if(vBytes[i] != s_ksvBinaryMarkerMSG[i])
        {
            return false;
        }
    }
    return true;
}

Bool RemoveCBORHeader(FixedUnsigned8List& vBytes)
{
    if(vBytes.size() < s_ksvBinaryMarkerCBR.size())
    {
        return false;
    }
    vBytes.erase(vBytes.begin() + s_ksvBinaryMarkerCBR.size());
    return true;
}

Bool RemoveMsgPackHeader(FixedUnsigned8List& vBytes)
{
    if(vBytes.size() < s_ksvBinaryMarkerMSG.size())
    {
        return false;
    }
    vBytes.erase(vBytes.begin() + s_ksvBinaryMarkerMSG.size());
    return true;
}

Bool ReadSerializedFile(const IndexedString& sFilename, const IndexedString& sType, Json& jsonData)
{
    const FileType eFileType = StringToFileType(sType);
    switch (eFileType)
    {
        case FileType::TextJson:
            return ReadJsonFile(sFilename, jsonData);
            break;
        case FileType::BinaryCBOR:
            return ReadCBORFile(sFilename, jsonData);
            break;
        case FileType::BinaryMsgPack:
            return ReadMsgPackFile(sFilename, jsonData);
            break;
        default:
            break;
    }
    return false;
}

Bool ReadJsonFile(const IndexedString& sFilename, Json& jsonData)
{
    InputFile ifile(sFilename.c_str());
    if(!ifile.is_open())
    {
        return false;
    }

    jsonData << ifile;
    ifile.close();
    return true;
}

Bool ReadJsonFile(const IndexedString& sFilename, String& jsonString)
{
    Json jsonData;
    if(!ReadJsonFile(sFilename, jsonData))
    {
        return false;
    }
    jsonString = jsonData.dump();
    return true;
}

Bool ReadCBORFile(const IndexedString& sFilename, Json& jsonData)
{
    FixedUnsigned8List vBytes;
    if(!ReadBinaryFile(sFilename, vBytes))
    {
        return false;
    }

    if(!IsCBOR(vBytes))
    {
        return false;
    }

    if(!RemoveCBORHeader(vBytes))
    {
        return false;
    }

    jsonData = JsonFromCBOR(vBytes);
    return true;
}

Bool ReadMsgPackFile(const IndexedString& sFilename, Json& jsonData)
{
    FixedUnsigned8List vBytes;
    if(!ReadBinaryFile(sFilename, vBytes))
    {
        return false;
    }

    if(!IsMsgPack(vBytes))
    {
        return false;
    }

    if(!RemoveMsgPackHeader(vBytes))
    {
        return false;
    }

    jsonData = JsonFromMsgPack(vBytes);
    return true;
}

Bool WriteSerializedFile(const IndexedString& sFilename, const IndexedString& sType, const Json& jsonData)
{
    const FileType eFileType = StringToFileType(sType);
    switch (eFileType)
    {
        case FileType::TextJson:
            return WriteJsonFile(sFilename, jsonData);
            break;
        case FileType::BinaryCBOR:
            return WriteCBORFile(sFilename, jsonData);
            break;
        case FileType::BinaryMsgPack:
            return WriteMsgPackFile(sFilename, jsonData);
            break;
        default:
            break;
    }
    return false;
}

Bool WriteJsonFile(const IndexedString& sFilename, const Json& jsonData)
{
    OutputFile ofile(sFilename.c_str());
    if(!ofile.is_open())
    {
        return false;
    }

    String stringData = jsonData.dump(4);
    ofile << stringData;
    ofile.close();
    return true;
}

Bool WriteJsonFile(const IndexedString& sFilename, const String& jsonString)
{
    return WriteJsonFile(sFilename, JsonParse(jsonString));
}

Bool WriteCBORFile(const IndexedString& sFilename, const Json& jsonData)
{
    FixedUnsigned8List vFileBytes = s_ksvBinaryMarkerCBR;
    FixedUnsigned8List vJsonBytes = JsonToCBOR(jsonData);
    vFileBytes.insert(vFileBytes.end(), vJsonBytes.begin(), vJsonBytes.end());
    return WriteBinaryFile(sFilename, vFileBytes);
}

Bool WriteMsgPackFile(const IndexedString& sFilename, const Json& jsonData)
{
    FixedUnsigned8List vFileBytes = s_ksvBinaryMarkerMSG;
    FixedUnsigned8List vJsonBytes = JsonToMsgPack(jsonData);
    vFileBytes.insert(vFileBytes.end(), vJsonBytes.begin(), vJsonBytes.end());
    return WriteBinaryFile(sFilename, vFileBytes);
}

};
