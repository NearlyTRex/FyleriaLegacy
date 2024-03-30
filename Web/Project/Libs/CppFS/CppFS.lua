-- Configuration
libCppFS_extradir = "Libs/CppFS/extra/"
libCppFS_origdir = "Libs/CppFS/orig/"
libCppFS_srcdir = libCppFS_origdir .. "source/cppfs/source/"
libCppFS_incdir = libCppFS_origdir .. "source/cppfs/include/"
libCppFS_incdir_3rdparty = libCppFS_origdir .. "source/cppfs/3rdparty/"

-- Includes
libCppFS_includedirs = {
    libCppFS_incdir,
    libCppFS_extradir,
    libCppFS_incdir_3rdparty
}

-- Libs
libCppFS_libs = {
}

-- Sources
libCppFS_sources = {
    libCppFS_srcdir .. "AbstractFileHandleBackend.cpp",
    libCppFS_srcdir .. "AbstractFileIteratorBackend.cpp",
    libCppFS_srcdir .. "AbstractFileSystem.cpp",
    libCppFS_srcdir .. "Change.cpp",
    libCppFS_srcdir .. "Diff.cpp",
    libCppFS_srcdir .. "FileIterator.cpp",
    libCppFS_srcdir .. "FilePath.cpp",
    libCppFS_srcdir .. "FileVisitor.cpp",
    libCppFS_srcdir .. "FunctionalFileVisitor.cpp",
    libCppFS_srcdir .. "InputStream.cpp",
    libCppFS_srcdir .. "LoginCredentials.cpp",
    libCppFS_srcdir .. "OutputStream.cpp",
    libCppFS_srcdir .. "system.cpp",
    libCppFS_srcdir .. "Tree.cpp",
    libCppFS_srcdir .. "Url.cpp",
    libCppFS_extradir .. "FileHandle.cpp",
    libCppFS_extradir .. "fs.cpp"
}
if os.host() == "windows" or _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
    table.insert(libCppFS_sources, libCppFS_srcdir .. "windows/LocalFileHandle.cpp")
    table.insert(libCppFS_sources, libCppFS_srcdir .. "windows/LocalFileIterator.cpp")
    table.insert(libCppFS_sources, libCppFS_srcdir .. "windows/LocalFileSystem.cpp")
else
    table.insert(libCppFS_sources, libCppFS_srcdir .. "posix/LocalFileHandle.cpp")
    table.insert(libCppFS_sources, libCppFS_srcdir .. "posix/LocalFileIterator.cpp")
    table.insert(libCppFS_sources, libCppFS_srcdir .. "posix/LocalFileSystem.cpp")
end
