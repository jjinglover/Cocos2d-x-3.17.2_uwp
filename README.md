# Cocos2d-x-3.17.2_uwp
支持Win10平台的Cocos2dx-3.17.2版本 

-----新增emscripten支持-----

参考资料：https://github.com/WuJiayiSH/cocos2d-x

In order to build cocos2d-x project into HTML5/wasm, make sure you have installed emsdk

    # Get the emsdk repo
    git clone https://github.com/emscripten-core/emsdk.git

    # Enter that directory
    cd emsdk

    # Download and install the SDK tools, 3.1.10 is recommended.
    ./emsdk install latest

    # Make the SDK "active" for the current user. (writes .emscripten file)
    ./emsdk activate latest

    # Activate PATH and other environment variables in the current terminal
    # ios，linux
    source ./emsdk_env.sh
    # windows
    emsdk_env.bat

On Window 10 or above, install cmake and ninja 1.12.0 or above(https://github.com/ninja-build/ninja) and make sure they can be found from command line:

    # Install cocos2d-x with python2.7
    git clone https://github.com/jjinglover/Cocos2d-x-3.17.2_uwp.git
    cd Cocos2d-x-3.17.2_uwp
    # export EMSDK_ROOT as environment variable
    python setup.py
    cd ..

    # Compile and check build from emscripten-build/bin/MyGame
    cocos new MyGame -p com.your_company.mygame -l cpp
    cd MyGame
    cocos compile -p emscripten -m release

Thread support is enabled by default, you can use Chrome argument --enable-features=SharedArrayBuffer for test or serve the build with addtional headers for it to work, see https://developer.chrome.com/blog/enabling-shared-array-buffer/ 

    Cross-Origin-Embedder-Policy: require-corp
    Cross-Origin-Opener-Policy: same-origin

You can disable thread support in cpp or lua projects by removing "-s USE_PTHREADS" from CmakeLists.txt, in the case most thread-related functions like addImageAsync will not work. But you may have to enable it in js project because SpiderMonkey uses threads.

Thread support uses Javascript SharedArrayBuffer, check https://caniuse.com/sharedarraybuffer for browser compatibility.

TODO: 
1. Files under WritablePath will be lost between game sessions

Backlogs:
1. Implement UIEditBox.cpp
2. Implement WebSocket.cpp
3. Investigate setAccelerometerEnabled, setAccelerometerInterval, getTextureDataForText in CCDevice
4. Compile tiff, webp 
5. Investigate getDuration, getCurrentTime, setCurrentTime in AudioEngine
6. Response header in HttpResponse is missing
