-- Configuration
libPistache_extradir = "Libs/Pistache/extra/"
libPistache_origdir = "Libs/Pistache/orig/"
libPistache_srcdir = libPistache_origdir .. "src/"
libPistache_incdir = libPistache_origdir .. "include/"

-- Includes
libPistache_includedirs = {
    libPistache_incdir
}

-- Libs
libPistache_libs = {
}

-- Sources
libPistache_sources = {
    libPistache_srcdir .. "common/cookie.cc",
    libPistache_srcdir .. "common/description.cc",
    libPistache_srcdir .. "common/http.cc",
    libPistache_srcdir .. "common/http_defs.cc",
    libPistache_srcdir .. "common/http_header.cc",
    libPistache_srcdir .. "common/http_headers.cc",
    libPistache_srcdir .. "common/mime.cc",
    libPistache_srcdir .. "common/net.cc",
    libPistache_srcdir .. "common/os.cc",
    libPistache_srcdir .. "common/peer.cc",
    libPistache_srcdir .. "common/reactor.cc",
    libPistache_srcdir .. "common/stream.cc",
    libPistache_srcdir .. "common/tcp.cc",
    libPistache_srcdir .. "common/timer_pool.cc",
    libPistache_srcdir .. "common/transport.cc",
    libPistache_srcdir .. "server/endpoint.cc",
    libPistache_srcdir .. "server/listener.cc",
    libPistache_srcdir .. "server/router.cc"
}
