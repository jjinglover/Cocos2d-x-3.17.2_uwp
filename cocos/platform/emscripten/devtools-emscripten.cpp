#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_EMSCRIPTEN

#include "devtools-emscripten.h"
#include <emscripten.h>
#include "base/ccUTF8.h"

using namespace std;
using namespace cocos2d;

DevToolsImpl::DevToolsImpl()
{
    _director = Director::getInstance();
    _scheduler = _director->getScheduler();
    _tick = 0;
}

void DevToolsImpl::update(float /*dt*/)
{
    // tick for 2 frames becuase delta time of the 1st frame after resume is forced to 0
    _tick ++;
    if (_tick >= 2)
    {
        _director->pause();
        _scheduler->unscheduleUpdate(this);
    }
}

void DevToolsImpl::step()
{
    _director->resume();
    _tick = 0;
    _scheduler->scheduleUpdate(this, 0, false);
}

void DevToolsImpl::pause()
{
    _director->pause();
}

void DevToolsImpl::resume()
{
    _director->resume();
}

DevToolsImpl* DevToolsImpl::getInstance()
{
    static DevToolsImpl instance;
    return &instance;
}

extern "C"
{
    void cocos_ccdirector_pause()
    {
        DevToolsImpl::getInstance()->pause();
    }

    void cocos_ccdirector_resume()
    {
        DevToolsImpl::getInstance()->resume();
    }

    void cocos_ccdirector_step()
    {
        DevToolsImpl::getInstance()->step();
    }
}

#endif // CC_PLATFORM_EMSCRIPTEN
