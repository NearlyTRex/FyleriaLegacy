// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#include "Utility/TypesFilesystem.h"

namespace Gecko
{

String GetNativeFileLocation(const FilesystemPath& sPath)
{
    return sPath.fullPath();
}

WString GetNativeFileLocationW(const FilesystemPath& sPath)
{
    return STDConvertStringToWideString(sPath.fullPath());
}

Bool DoesFileExist(const FilesystemPath& sPath)
{
    return FilesystemOpen(sPath.fullPath()).exists();
}

Bool IsFile(const FilesystemPath& sPath)
{
    return FilesystemOpen(sPath.fullPath()).isFile();
}

Bool IsDirectory(const FilesystemPath& sPath)
{
    return FilesystemOpen(sPath.fullPath()).isDirectory();
}

Bool IsSymbolicLink(const FilesystemPath& sPath)
{
    return FilesystemOpen(sPath.fullPath()).isSymbolicLink();
}

STDVector<String> GetListOfFiles(const FilesystemPath& sPath)
{
    return FilesystemOpen(sPath.fullPath()).listFiles();
}

Bool CreateDirectory(const FilesystemPath& sPath)
{
    return FilesystemOpen(sPath.fullPath()).createDirectory();
}

Bool RemoveDirectory(const FilesystemPath& sPath)
{
    return FilesystemOpen(sPath.fullPath()).removeDirectory();
}

void RemoveFile(const FilesystemPath& sPath)
{
    FilesystemOpen(sPath.fullPath()).remove();
}

SizeType GetFileSize(const FilesystemPath& sPath)
{
    return FilesystemOpen(sPath.fullPath()).size();
}

FilesystemPath operator/(const FilesystemPath& path1, const FilesystemPath& path2)
{
    FilesystemPath newPath(path1);
    return newPath.resolve(path2);
}

};
