// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_MAIN_WINDOW_H_
#define _GECKO_MAIN_WINDOW_H_

// Internal includes
#include "Window/BrowserEngine.h"
#include "Utility/Types.h"
#include "Utility/Singleton.h"

namespace Gecko
{

// Main window class
class MainWindow : public Singleton<MainWindow>
{
public:

    // Constructor
    MainWindow();

    // Destructor
    virtual ~MainWindow();

    // Browser engine
    MAKE_RAW_TYPE_ACCESSORS(BrowserEngine, BrowserEngineSharedPtr);
};

// Typedefs
MAKE_COMMON_TYPEDEFS(MainWindow);

};

#endif
