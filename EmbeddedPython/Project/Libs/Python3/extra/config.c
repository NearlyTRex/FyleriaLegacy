// Module configuration
#include "Python.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Module externs
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
    extern PyObject* PyInit_msvcrt(void);
    extern PyObject* PyInit_nt(void);
    extern PyObject* PyInit_winreg(void);
    extern PyObject* PyInit__winapi(void);
    extern PyObject* PyInit__locale(void);
#else
    extern PyObject* PyInit_posix(void);
#endif
    extern PyObject* _PyWarnings_Init(void);
    extern PyObject* PyInit__abc(void);
    extern PyObject* PyInit__ast(void);
    extern PyObject* PyInit__bisect(void);
    extern PyObject* PyInit__blake2(void);
    extern PyObject* PyInit__codecs_cn(void);
    extern PyObject* PyInit__codecs_hk(void);
    extern PyObject* PyInit__codecs_iso2022(void);
    extern PyObject* PyInit__codecs_jp(void);
    extern PyObject* PyInit__codecs_kr(void);
    extern PyObject* PyInit__codecs_tw(void);
    extern PyObject* PyInit__codecs(void);
    extern PyObject* PyInit__collections(void);
    extern PyObject* PyInit__contextvars(void);
    extern PyObject* PyInit__csv(void);
    extern PyObject* PyInit__datetime(void);
    extern PyObject* PyInit__functools(void);
    extern PyObject* PyInit__heapq(void);
    extern PyObject* PyInit__imp(void);
    extern PyObject* PyInit__io(void);
    extern PyObject* PyInit__json(void);
    extern PyObject* PyInit__lsprof(void);
    extern PyObject* PyInit__md5(void);
    extern PyObject* PyInit__multibytecodec(void);
    extern PyObject* PyInit__opcode(void);
    extern PyObject* PyInit__operator(void);
    extern PyObject* PyInit__random(void);
    extern PyObject* PyInit__sha1(void);
    extern PyObject* PyInit__sha256(void);
    extern PyObject* PyInit__sha3(void);
    extern PyObject* PyInit__sha512(void);
    extern PyObject* PyInit__signal(void);
    extern PyObject* PyInit__sre(void);
    extern PyObject* PyInit__stat(void);
    extern PyObject* PyInit__string(void);
    extern PyObject* PyInit__struct(void);
    extern PyObject* PyInit__symtable(void);
    extern PyObject* PyInit__thread(void);
    extern PyObject* PyInit__tracemalloc(void);
    extern PyObject* PyInit__weakref(void);
    extern PyObject* PyInit_audioop(void);
    extern PyObject* PyInit_array(void);
    extern PyObject* PyInit_atexit(void);
    extern PyObject* PyInit_binascii(void);
    extern PyObject* PyInit_cmath(void);
    extern PyObject* PyInit_errno(void);
    extern PyObject* PyInit_faulthandler(void);
    extern PyObject* PyInit_gc(void);
    extern PyObject* PyInit_itertools(void);
    extern PyObject* PyInit_math(void);
    extern PyObject* PyInit_mmap(void);
    extern PyObject* PyInit_parser(void);
    extern PyObject* PyInit_time(void);
    extern PyObject* PyInit_xxsubtype(void);
    extern PyObject* PyInit_zlib(void);
    extern PyObject* PyMarshal_Init(void);

    // Builtin modules
    struct _inittab _PyImport_Inittab[] =
    {
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
        {"msvcrt", PyInit_msvcrt},
        {"nt", PyInit_nt},
        {"winreg", PyInit_winreg},
        {"_locale", PyInit__locale},
        {"_winapi", PyInit__winapi},
#else
        {"posix", PyInit_posix},
#endif
        {"_abc", PyInit__abc},
        {"_ast", PyInit__ast},
        {"_bisect", PyInit__bisect},
        {"_blake2", PyInit__blake2},
        {"_codecs_cn", PyInit__codecs_cn},
        {"_codecs_hk", PyInit__codecs_hk},
        {"_codecs_iso2022", PyInit__codecs_iso2022},
        {"_codecs_jp", PyInit__codecs_jp},
        {"_codecs_kr", PyInit__codecs_kr},
        {"_codecs_tw", PyInit__codecs_tw},
        {"_codecs", PyInit__codecs},
        {"_collections", PyInit__collections},
        {"_contextvars", PyInit__contextvars},
        {"_csv", PyInit__csv},
        {"_datetime", PyInit__datetime},
        {"_functools", PyInit__functools},
        {"_heapq", PyInit__heapq},
        {"_imp", PyInit__imp},
        {"_io", PyInit__io},
        {"_json", PyInit__json},
        {"_lsprof", PyInit__lsprof},
        {"_md5", PyInit__md5},
        {"_multibytecodec", PyInit__multibytecodec},
        {"_opcode", PyInit__opcode},
        {"_operator", PyInit__operator},
        {"_random", PyInit__random},
        {"_sha1", PyInit__sha1},
        {"_sha3", PyInit__sha3},
        {"_sha256", PyInit__sha256},
        {"_sha512", PyInit__sha512},
        {"_signal", PyInit__signal},
        {"_sre", PyInit__sre},
        {"_stat", PyInit__stat},
        {"_string", PyInit__string},
        {"_struct", PyInit__struct},
        {"_symtable", PyInit__symtable},
        {"_thread", PyInit__thread},
        {"_tracemalloc", PyInit__tracemalloc},
        {"_warnings", _PyWarnings_Init},
        {"_weakref", PyInit__weakref},
        {"audioop", PyInit_audioop},
        {"array", PyInit_array},
        {"atexit", PyInit_atexit},
        {"binascii", PyInit_binascii},
        {"cmath", PyInit_cmath},
        {"errno", PyInit_errno},
        {"faulthandler", PyInit_faulthandler},
        {"gc", PyInit_gc},
        {"itertools", PyInit_itertools},
        {"marshal", PyMarshal_Init},
        {"math", PyInit_math},
        {"mmap", PyInit_mmap},
        {"parser", PyInit_parser},
        {"time", PyInit_time},
        {"xxsubtype", PyInit_xxsubtype},
        {"zlib", PyInit_zlib},
        {"builtins", NULL},
        {"sys", NULL},
        {0, 0}
    };
#ifdef __cplusplus
}
#endif
