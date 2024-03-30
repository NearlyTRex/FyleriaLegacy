// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_APPLICATION_H_
#define _GECKO_APPLICATION_H_

// Internal includes
#include "Utility/Types.h"

namespace Gecko
{

class Application
{
public:

    // Constructor
    Application();

    // Destructor
    virtual ~Application();

    // Run application
    void Run();

private:

    // Initialize
    Bool Initialize();

    // Finalize
    Bool Finalize();
};

};

#endif
