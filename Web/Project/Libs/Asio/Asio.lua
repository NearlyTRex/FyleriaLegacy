-- Configuration
libAsio_extradir = "Libs/Asio/extra/"
libAsio_origdir = "Libs/Asio/orig/"
libAsio_srcdir = libAsio_origdir .. "asio/src/"
libAsio_incdir = libAsio_origdir .. "asio/include/"

-- Includes
libAsio_includedirs = {
    libAsio_incdir
}

-- Defines
libAsio_defines = {
    "ASIO_STANDALONE"
}

-- Sources
libAsio_sources = {
    libAsio_srcdir .. "asio.cpp",
    libAsio_srcdir .. "asio_ssl.cpp"
}
