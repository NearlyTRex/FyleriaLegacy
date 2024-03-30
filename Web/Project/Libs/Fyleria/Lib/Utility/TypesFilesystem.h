// Fyleria Engine
// Copyright © 2016 Go Go Gecko Productions

#ifndef _GECKO_TYPES_FILESYSTEM_H_
#define _GECKO_TYPES_FILESYSTEM_H_

// External includes
#include <cppfs/fs.h>
#include <cppfs/FilePath.h>
#include <cppfs/FileHandle.h>

// Internal includes
#include "Utility/TypesSimple.h"

// Filesystem defines
#define FilesystemOpen cppfs::fs::open

namespace Gecko
{

// Filesystem types
typedef cppfs::FilePath FilesystemPath;
typedef cppfs::FileHandle FilesystemHandle;

// Get native location
String GetNativeFileLocation(const FilesystemPath& sPath);
WString GetNativeFileLocationW(const FilesystemPath& sPath);

// Does file exist
Bool DoesFileExist(const FilesystemPath& sPath);

// Is path a file
Bool IsFile(const FilesystemPath& sPath);

// Is path a directory
Bool IsDirectory(const FilesystemPath& sPath);

// Is path a symbolic link
Bool IsSymbolicLink(const FilesystemPath& sPath);

// Get list of files
STDVector<String> GetListOfFiles(const FilesystemPath& sPath);

// Create directory
Bool CreateDirectory(const FilesystemPath& sPath);

// Remove directory
Bool RemoveDirectory(const FilesystemPath& sPath);

// Remove file
void RemoveFile(const FilesystemPath& sPath);

// Get file size in bytes
SizeType GetFileSize(const FilesystemPath& sPath);

// Concatenation of paths with dividers
FilesystemPath operator/(const FilesystemPath& path1, const FilesystemPath& path2);

};

#endif
