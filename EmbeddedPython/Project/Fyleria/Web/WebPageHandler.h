// Fyleria Engine
// Copyright © 2019 Go Go Gecko Productions

#ifndef _GECKO_WEB_PAGE_HANDLER_H_
#define _GECKO_WEB_PAGE_HANDLER_H_

// Internal includes
#include "Utility/Macros.h"
#include "Utility/Tree.h"
#include "Utility/Enum.h"
#include "Utility/Json.h"
#include "Utility/Types.h"

namespace Gecko
{

class WebPageHandler
{
public:

    // Constructors
    WebPageHandler();

    // Destructor
    virtual ~WebPageHandler();

    // Update page content
    virtual void UpdatePageContent(const StringMap& tParams) = 0;

    // Page content
    MAKE_RAW_TYPE_ACCESSORS(PageContent, String);

    // Page template
    MAKE_RAW_TYPE_ACCESSORS(PageTemplate, String);
};

// Typedefs
MAKE_COMMON_TYPEDEFS(WebPageHandler);

// Make default html option list
template <class EnumType>
String MakeDefaultHtmlOptionList()
{
    String sOptionList;
    for(auto& sTypeName : GetEnumNames<EnumType>())
    {
        if(IsNoneTypeForEnum<EnumType>(sTypeName))
        {
            continue;
        }
        sOptionList += "<option value=\"" + sTypeName + "\">" + sTypeName + "</option>";
    }
    return sOptionList;
}

// Make selected html option list
template <class EnumType>
String MakeSelectedHtmlOptionList(const String& sSelection)
{
    String sOptionList;
    for(auto& sTypeName : GetEnumNames<EnumType>())
    {
        if(IsNoneTypeForEnum<EnumType>(sTypeName))
        {
            continue;
        }
        if(sTypeName == sSelection)
        {
            sOptionList += "<option value=\"" + sTypeName + "\" selected=\"selected\">";
            sOptionList += sTypeName + "</option>";
        }
        else
        {
            sOptionList += "<option value=\"" + sTypeName + "\">" + sTypeName + "</option>";
        }
    }
    return sOptionList;
}

};

#endif
