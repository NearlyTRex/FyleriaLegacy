-- Configuration
libPython3_extradir = "Libs/Python3/extra/"
libPython3_origdir = "Libs/Python3/orig/"
libPython3_srcdir = libPython3_origdir
libPython3_incdir = libPython3_origdir .. "Include/"

-- Includes
libPython3_includedirs = {
    libPython3_origdir,
    libPython3_incdir,
    libPython3_extradir
}

-- Defines
libPython3_defines = {
    "Py_NO_ENABLE_SHARED",
    "Py_BUILD_CORE",
    "PYTHONPATH=\"\"",
    "PREFIX=\"\"",
    "EXEC_PREFIX=\"\"",
    "VERSION=\"\"",
    "VPATH=\"\""
}
libPython3_debugdefines = {
    "NDEBUG"
}
libPython3_releasedefines = {
    "NDEBUG"
}
if os.host() == "windows" or _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
    table.insert(libPython3_defines, "HAVE_ROUND")
    table.insert(libPython3_defines, "_CRT_SECURE_NO_WARNINGS")
    table.insert(libPython3_defines, "_CRT_SECURE_NO_DEPRECATE")
    table.insert(libPython3_defines, "_CRT_NONSTDC_NO_DEPRECATE")
end

-- Libs
libPython3_libs = {
    "Zlib"
}
if os.host() == "windows" or _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
    table.insert(libPython3_libs, "version")
    table.insert(libPython3_libs, "ws2_32")
    table.insert(libPython3_libs, "shlwapi")
elseif os.host() == "linux" then
    table.insert(libPython3_libs, "pthread")
    table.insert(libPython3_libs, "util")
end

-- Sources
libPython3_sources = {
    libPython3_srcdir .. "Modules/_bisectmodule.c",
    libPython3_srcdir .. "Modules/_blake2/blake2b_impl.c",
    libPython3_srcdir .. "Modules/_blake2/blake2s_impl.c",
    libPython3_srcdir .. "Modules/_blake2/blake2module.c",
    libPython3_srcdir .. "Modules/_codecsmodule.c",
    libPython3_srcdir .. "Modules/_collectionsmodule.c",
    libPython3_srcdir .. "Modules/_csv.c",
    libPython3_srcdir .. "Modules/_datetimemodule.c",
    libPython3_srcdir .. "Modules/_functoolsmodule.c",
    libPython3_srcdir .. "Modules/_heapqmodule.c",
    libPython3_srcdir .. "Modules/_io/bufferedio.c",
    libPython3_srcdir .. "Modules/_io/bytesio.c",
    libPython3_srcdir .. "Modules/_io/fileio.c",
    libPython3_srcdir .. "Modules/_io/iobase.c",
    libPython3_srcdir .. "Modules/_io/stringio.c",
    libPython3_srcdir .. "Modules/_io/textio.c",
    libPython3_srcdir .. "Modules/_json.c",
    libPython3_srcdir .. "Modules/_localemodule.c",
    libPython3_srcdir .. "Modules/_lsprof.c",
    libPython3_srcdir .. "Modules/_math.c",
    libPython3_srcdir .. "Modules/_opcode.c",
    libPython3_srcdir .. "Modules/_operator.c",
    libPython3_srcdir .. "Modules/_randommodule.c",
    libPython3_srcdir .. "Modules/_sha3/sha3module.c",
    libPython3_srcdir .. "Modules/_sre.c",
    libPython3_srcdir .. "Modules/_stat.c",
    libPython3_srcdir .. "Modules/_struct.c",
    libPython3_srcdir .. "Modules/_tracemalloc.c",
    libPython3_srcdir .. "Modules/_weakref.c",
    libPython3_srcdir .. "Modules/arraymodule.c",
    libPython3_srcdir .. "Modules/atexitmodule.c",
    libPython3_srcdir .. "Modules/binascii.c",
    libPython3_srcdir .. "Modules/cjkcodecs/_codecs_cn.c",
    libPython3_srcdir .. "Modules/cjkcodecs/_codecs_hk.c",
    libPython3_srcdir .. "Modules/cjkcodecs/_codecs_iso2022.c",
    libPython3_srcdir .. "Modules/cjkcodecs/_codecs_jp.c",
    libPython3_srcdir .. "Modules/cjkcodecs/_codecs_kr.c",
    libPython3_srcdir .. "Modules/cjkcodecs/_codecs_tw.c",
    libPython3_srcdir .. "Modules/cjkcodecs/multibytecodec.c",
    libPython3_srcdir .. "Modules/cmathmodule.c",
    libPython3_srcdir .. "Modules/errnomodule.c",
    libPython3_srcdir .. "Modules/faulthandler.c",
    libPython3_srcdir .. "Modules/gcmodule.c",
    libPython3_srcdir .. "Modules/getbuildinfo.c",
    libPython3_srcdir .. "Modules/hashtable.c",
    libPython3_srcdir .. "Modules/itertoolsmodule.c",
    libPython3_srcdir .. "Modules/mathmodule.c",
    libPython3_srcdir .. "Modules/md5module.c",
    libPython3_srcdir .. "Modules/mmapmodule.c",
    libPython3_srcdir .. "Modules/parsermodule.c",
    libPython3_srcdir .. "Modules/rotatingtree.c",
    libPython3_srcdir .. "Modules/sha1module.c",
    libPython3_srcdir .. "Modules/sha256module.c",
    libPython3_srcdir .. "Modules/sha512module.c",
    libPython3_srcdir .. "Modules/signalmodule.c",
    libPython3_srcdir .. "Modules/symtablemodule.c",
    libPython3_srcdir .. "Modules/timemodule.c",
    libPython3_srcdir .. "Modules/unicodedata.c",
    libPython3_srcdir .. "Modules/xxmodule.c",
    libPython3_srcdir .. "Modules/xxsubtype.c",
    libPython3_srcdir .. "Modules/zipimport.c",
    libPython3_srcdir .. "Modules/zlibmodule.c",
    libPython3_srcdir .. "Objects/abstract.c",
    libPython3_srcdir .. "Objects/accu.c",
    libPython3_srcdir .. "Objects/boolobject.c",
    libPython3_srcdir .. "Objects/bytearrayobject.c",
    libPython3_srcdir .. "Objects/bytes_methods.c",
    libPython3_srcdir .. "Objects/bytesobject.c",
    libPython3_srcdir .. "Objects/capsule.c",
    libPython3_srcdir .. "Objects/cellobject.c",
    libPython3_srcdir .. "Objects/classobject.c",
    libPython3_srcdir .. "Objects/codeobject.c",
    libPython3_srcdir .. "Objects/complexobject.c",
    libPython3_srcdir .. "Objects/descrobject.c",
    libPython3_srcdir .. "Objects/dictobject.c",
    libPython3_srcdir .. "Objects/enumobject.c",
    libPython3_srcdir .. "Objects/exceptions.c",
    libPython3_srcdir .. "Objects/fileobject.c",
    libPython3_srcdir .. "Objects/floatobject.c",
    libPython3_srcdir .. "Objects/frameobject.c",
    libPython3_srcdir .. "Objects/funcobject.c",
    libPython3_srcdir .. "Objects/genobject.c",
    libPython3_srcdir .. "Objects/iterobject.c",
    libPython3_srcdir .. "Objects/listobject.c",
    libPython3_srcdir .. "Objects/longobject.c",
    libPython3_srcdir .. "Objects/memoryobject.c",
    libPython3_srcdir .. "Objects/methodobject.c",
    libPython3_srcdir .. "Objects/moduleobject.c",
    libPython3_srcdir .. "Objects/namespaceobject.c",
    libPython3_srcdir .. "Objects/object.c",
    libPython3_srcdir .. "Objects/obmalloc.c",
    libPython3_srcdir .. "Objects/odictobject.c",
    libPython3_srcdir .. "Objects/rangeobject.c",
    libPython3_srcdir .. "Objects/setobject.c",
    libPython3_srcdir .. "Objects/sliceobject.c",
    libPython3_srcdir .. "Objects/structseq.c",
    libPython3_srcdir .. "Objects/tupleobject.c",
    libPython3_srcdir .. "Objects/typeobject.c",
    libPython3_srcdir .. "Objects/unicodectype.c",
    libPython3_srcdir .. "Objects/unicodeobject.c",
    libPython3_srcdir .. "Objects/weakrefobject.c",
    libPython3_srcdir .. "Parser/acceler.c",
    libPython3_srcdir .. "Parser/bitset.c",
    libPython3_srcdir .. "Parser/firstsets.c",
    libPython3_srcdir .. "Parser/grammar.c",
    libPython3_srcdir .. "Parser/grammar1.c",
    libPython3_srcdir .. "Parser/listnode.c",
    libPython3_srcdir .. "Parser/metagrammar.c",
    libPython3_srcdir .. "Parser/myreadline.c",
    libPython3_srcdir .. "Parser/node.c",
    libPython3_srcdir .. "Parser/parser.c",
    libPython3_srcdir .. "Parser/parsetok.c",
    libPython3_srcdir .. "Parser/printgrammar.c",
    libPython3_srcdir .. "Parser/tokenizer.c",
    libPython3_srcdir .. "Python/Python-ast.c",
    libPython3_srcdir .. "Python/_warnings.c",
    libPython3_srcdir .. "Python/asdl.c",
    libPython3_srcdir .. "Python/ast.c",
    libPython3_srcdir .. "Python/bltinmodule.c",
    libPython3_srcdir .. "Python/ceval.c",
    libPython3_srcdir .. "Python/codecs.c",
    libPython3_srcdir .. "Python/compile.c",
    libPython3_srcdir .. "Python/dtoa.c",
    libPython3_srcdir .. "Python/errors.c",
    libPython3_srcdir .. "Python/fileutils.c",
    libPython3_srcdir .. "Python/formatter_unicode.c",
    libPython3_srcdir .. "Python/frozen.c",
    libPython3_srcdir .. "Python/future.c",
    libPython3_srcdir .. "Python/getargs.c",
    libPython3_srcdir .. "Python/getcompiler.c",
    libPython3_srcdir .. "Python/getcopyright.c",
    libPython3_srcdir .. "Python/getopt.c",
    libPython3_srcdir .. "Python/getplatform.c",
    libPython3_srcdir .. "Python/getversion.c",
    libPython3_srcdir .. "Python/graminit.c",
    libPython3_srcdir .. "Python/import.c",
    libPython3_srcdir .. "Python/marshal.c",
    libPython3_srcdir .. "Python/modsupport.c",
    libPython3_srcdir .. "Python/mysnprintf.c",
    libPython3_srcdir .. "Python/mystrtoul.c",
    libPython3_srcdir .. "Python/peephole.c",
    libPython3_srcdir .. "Python/pyarena.c",
    libPython3_srcdir .. "Python/pyctype.c",
    libPython3_srcdir .. "Python/pyfpe.c",
    libPython3_srcdir .. "Python/pyhash.c",
    libPython3_srcdir .. "Python/pylifecycle.c",
    libPython3_srcdir .. "Python/pymath.c",
    libPython3_srcdir .. "Python/pystate.c",
    libPython3_srcdir .. "Python/pystrcmp.c",
    libPython3_srcdir .. "Python/pystrhex.c",
    libPython3_srcdir .. "Python/pystrtod.c",
    libPython3_srcdir .. "Python/pythonrun.c",
    libPython3_srcdir .. "Python/pytime.c",
    libPython3_srcdir .. "Python/random.c",
    libPython3_srcdir .. "Python/structmember.c",
    libPython3_srcdir .. "Python/symtable.c",
    libPython3_srcdir .. "Python/sysmodule.c",
    libPython3_srcdir .. "Python/thread.c",
    libPython3_srcdir .. "Python/traceback.c",
    libPython3_extradir .. "config.c"
}
if os.host() == "windows" or _OPTIONS["with-mingw32"] or _OPTIONS["with-mingw64"] then
    table.insert(libPython3_sources, libPython3_srcdir .. "Modules/_io/winconsoleio.c")
    table.insert(libPython3_sources, libPython3_srcdir .. "Modules/_winapi.c")
    table.insert(libPython3_sources, libPython3_extradir .. "windows-getpathp.c")
    table.insert(libPython3_sources, libPython3_extradir .. "windows-invalid_parameter_handler.c")
    table.insert(libPython3_sources, libPython3_extradir .. "windows-iomodule.c")
    table.insert(libPython3_sources, libPython3_extradir .. "windows-posixmodule.c")
else
    table.insert(libPython3_sources, libPython3_srcdir .. "Modules/getpath.c")
    table.insert(libPython3_sources, libPython3_srcdir .. "Modules/_io/_iomodule.c")
    table.insert(libPython3_sources, libPython3_srcdir .. "Modules/posixmodule.c")
end
