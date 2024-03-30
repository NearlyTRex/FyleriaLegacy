-- Configuration
libAssert_extradir = "Libs/Assert/extra/"
libAssert_origdir = "Libs/Assert/orig/"
libAssert_srcdir = libAssert_origdir .. "src/"
libAssert_incdir = libAssert_origdir .. "src/"

-- Includes
libAssert_includedirs = {
    libAssert_incdir
}

-- Defines
libAssert_debugdefines = {
}
libAssert_releasedefines = {
}

-- Sources
libAssert_sources = {
    libAssert_srcdir .. "**.cpp"
}
