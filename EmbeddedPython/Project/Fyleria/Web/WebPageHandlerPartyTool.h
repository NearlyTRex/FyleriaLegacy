// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_WEB_PAGE_HANDLER_PARTY_TOOL_H_
#define _GECKO_WEB_PAGE_HANDLER_PARTY_TOOL_H_

// Internal includes
#include "Web/WebPageHandler.h"

namespace Gecko
{

class WebPageHandlerPartyTool : public WebPageHandler
{
public:

    // Constructors
    WebPageHandlerPartyTool();

    // Destructor
    virtual ~WebPageHandlerPartyTool();

    // Update page content
    virtual void UpdatePageContent(const StringMap& tParams) override;
};

// Typedefs
MAKE_COMMON_TYPEDEFS(WebPageHandlerPartyTool);

};

#endif
