// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_CHARACTER_ACTION_HANDLER_H_
#define _GECKO_CHARACTER_ACTION_HANDLER_H_

// Internal includes
#include "CharacterAction/CharacterAction.h"

namespace Gecko
{

class CharacterActionHandler
{
public:

    // Constructors
    CharacterActionHandler();

    // Destructor
    virtual ~CharacterActionHandler();

    // Stages for running the action
    virtual Bool Setup(CharacterAction& action) = 0;
    virtual Bool Finish(CharacterAction& action) = 0;
    virtual Bool GenerateResult(CharacterAction& action) = 0;
    virtual Bool ApplyResult(CharacterAction& action) = 0;
};

// Typedef
MAKE_COMMON_TYPEDEFS(CharacterActionHandler);

};

#endif
