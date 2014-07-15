#include "chilitagsplugin.h"

#include "chilitagscamera.h"
#include "chilitagsobject.h"

#include <qqml.h>

void ChilitagsPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<ChilitagsCamera>(uri, 1, 0, "ChilitagsCamera");
    qmlRegisterType<ChilitagsObject>(uri, 1, 0, "ChilitagsObject");
}
