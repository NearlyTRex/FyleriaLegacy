// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_UTILITY_FILESYSTEM_H_
#define _GECKO_UTILITY_FILESYSTEM_H_

// Internal includes
#include "Utility/Types.h"

namespace Gecko
{

// Does path exist
Bool DoesPathExist(const String& sPath);

// Is path a file
Bool IsFile(const String& sPath);

// Is path a directory
Bool IsDirectory(const String& sPath);

// Is path a symbolic link
Bool IsSymbolicLink(const String& sPath);

// Create new directory
Bool CreateNewDirectory(const String& sPath);

// Remove directory and all files
Bool RemoveDirectoryAndFiles(const String& sPath);

// Remove file
Bool RemoveFile(const String& sPath);

// Get file size in bytes
SizeType GetFileSize(const String& sPath);

// Get absolute path
String GetAbsolutePath(const String& sPath);

// Get canonical path
String GetCanonicalPath(const String& sPath);

// Join paths together
String JoinPaths(const String& sPath1, const String& sPath2);

// Join paths together and get canonical result
String JoinPathsCanonical(const String& sPath1, const String& sPath2);

// Get file contents as string
String GetFileContentsAsString(const String& sPath);

// Get file contents as byte array
UByteArray GetFileContentsAsByteArray(const String& sPath);

// Get program directory
String GetProgramDirectory();

// Get data directory
String GetDataDirectory();

// Get save directory
String GetSaveDirectory();

// Get log directory
String GetLogDirectory();

// Get log file
String GetLogFile();

};

#endif
