// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_WEB_PAGE_HANDLER_CHARACTER_TOOL_H_
#define _GECKO_WEB_PAGE_HANDLER_CHARACTER_TOOL_H_

// Internal includes
#include "Web/WebPageHandler.h"

namespace Gecko
{

class WebPageHandlerCharacterTool : public WebPageHandler
{
public:

    // Constructors
    WebPageHandlerCharacterTool();

    // Destructor
    virtual ~WebPageHandlerCharacterTool();

    // Update page content
    virtual void UpdatePageContent(const StringMap& tParams) override;
};

// Typedefs
MAKE_COMMON_TYPEDEFS(WebPageHandlerCharacterTool);

};

#endif
