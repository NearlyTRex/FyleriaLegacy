-- Configuration
libMicroPather_extradir = "Libs/MicroPather/extra/"
libMicroPather_origdir = "Libs/MicroPather/orig/"
libMicroPather_srcdir = libMicroPather_origdir
libMicroPather_incdir = libMicroPather_origdir

-- Includes
libMicroPather_includedirs = {
    libMicroPather_incdir
}

-- Defines
libMicroPather_debugdefines = {
    "DEBUG"
}
libMicroPather_releasedefines = {
}

-- Sources
libMicroPather_sources = {
    libMicroPather_srcdir .. "micropather.cpp"
}
