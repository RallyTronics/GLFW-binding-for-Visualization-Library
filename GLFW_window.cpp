/**************************************************************************************/
/*                                                                                    */
/*  Visualization Library                                                             */
/*  http://visualizationlibrary.org                                                   */
/*                                                                                    */
/*  Copyright (c) 2005-2016, Michele Bosi, John Lagerquist                            */
/*  All rights reserved.                                                              */
/*                                                                                    */
/*  Redistribution and use in source and binary forms, with or without modification,  */
/*  are permitted provided that the following conditions are met:                     */
/*                                                                                    */
/*  - Redistributions of source code must retain the above copyright notice, this     */
/*  list of conditions and the following disclaimer.                                  */
/*                                                                                    */
/*  - Redistributions in binary form must reproduce the above copyright notice, this  */
/*  list of conditions and the following disclaimer in the documentation and/or       */
/*  other materials provided with the distribution.                                   */
/*                                                                                    */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND   */
/*  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED     */
/*  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE            */
/*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR  */
/*  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES    */
/*  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;      */
/*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON    */
/*  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT           */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS     */
/*  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      */
/*                                                                                    */
/**************************************************************************************/

#include "vlGLFW/GLFW_window.hpp"
#include "vlGraphics/OpenGL.hpp"
#include "vlGraphics/Applet.hpp"
#include "vlCore/VisualizationLibrary.hpp"
#include "vlCore/Log.hpp"
#include "vlCore/Say.hpp"
#include <algorithm>
#include <unordered_map>
#include <vector>

#ifdef WIN32
#include <shellapi.h>
#endif

using namespace vlGLFW;
using namespace vl;

namespace
{
static std::unordered_map<uint32_t, vl::EKey> key_translation_map =
{
    { GLFW_KEY_0, vl::Key_0 },
    { GLFW_KEY_1, vl::Key_1 },
    { GLFW_KEY_2, vl::Key_2 },
    { GLFW_KEY_3, vl::Key_3 },
    { GLFW_KEY_4, vl::Key_4 },
    { GLFW_KEY_5, vl::Key_5 },
    { GLFW_KEY_6, vl::Key_6 },
    { GLFW_KEY_7, vl::Key_7 },
    { GLFW_KEY_8, vl::Key_8 },
    { GLFW_KEY_9, vl::Key_9 },
    { GLFW_KEY_A, vl::Key_A },
    { GLFW_KEY_B, vl::Key_B },
    { GLFW_KEY_C, vl::Key_C },
    { GLFW_KEY_D, vl::Key_D },
    { GLFW_KEY_E, vl::Key_E },
    { GLFW_KEY_F, vl::Key_F },
    { GLFW_KEY_G, vl::Key_G },
    { GLFW_KEY_H, vl::Key_H },
    { GLFW_KEY_I, vl::Key_I },
    { GLFW_KEY_J, vl::Key_J },
    { GLFW_KEY_K, vl::Key_K },
    { GLFW_KEY_L, vl::Key_L },
    { GLFW_KEY_M, vl::Key_M },
    { GLFW_KEY_N, vl::Key_N },
    { GLFW_KEY_O, vl::Key_O },
    { GLFW_KEY_P, vl::Key_P },
    { GLFW_KEY_Q, vl::Key_Q },
    { GLFW_KEY_R, vl::Key_R },
    { GLFW_KEY_S, vl::Key_S },
    { GLFW_KEY_T, vl::Key_T },
    { GLFW_KEY_U, vl::Key_U },
    { GLFW_KEY_V, vl::Key_V },
    { GLFW_KEY_W, vl::Key_W },
    { GLFW_KEY_X, vl::Key_X },
    { GLFW_KEY_Y, vl::Key_Y },
    { GLFW_KEY_Z, vl::Key_Z },
    { GLFW_KEY_ENTER, vl::Key_Return },
    { GLFW_KEY_BACKSPACE, vl::Key_BackSpace },
    { GLFW_KEY_SPACE, vl::Key_Space },
    { GLFW_KEY_TAB, vl::Key_Tab },
    { GLFW_KEY_COMMA, vl::Key_Comma },
    { GLFW_KEY_MINUS, vl::Key_Minus },
    { GLFW_KEY_PERIOD, vl::Key_Period },
    { GLFW_KEY_SLASH, vl::Key_Slash },
    { GLFW_KEY_ESCAPE, vl::Key_Escape },
    { GLFW_KEY_SEMICOLON, vl::Key_Semicolon },
    { GLFW_KEY_BACKSLASH, vl::Key_BackSlash },
    { GLFW_KEY_LEFT, vl::Key_Left },
    { GLFW_KEY_RIGHT, vl::Key_Right },
    { GLFW_KEY_UP, vl::Key_Up },
    { GLFW_KEY_DOWN, vl::Key_Down },
    { GLFW_KEY_INSERT, vl::Key_Insert },
    { GLFW_KEY_DELETE, vl::Key_Delete },
    { GLFW_KEY_HOME, vl::Key_Home },
    { GLFW_KEY_END, vl::Key_End },
    { GLFW_KEY_PAUSE, vl::Key_Pause },
    { GLFW_KEY_F1, vl::Key_F1 },
    { GLFW_KEY_F2, vl::Key_F2 },
    { GLFW_KEY_F3, vl::Key_F3 },
    { GLFW_KEY_F4, vl::Key_F4 },
    { GLFW_KEY_F5, vl::Key_F5 },
    { GLFW_KEY_F6, vl::Key_F6 },
    { GLFW_KEY_F7, vl::Key_F7 },
    { GLFW_KEY_F8, vl::Key_F8 },
    { GLFW_KEY_F9, vl::Key_F9 },
    { GLFW_KEY_F10, vl::Key_F10 },
    { GLFW_KEY_F11, vl::Key_F11 },
    { GLFW_KEY_F12, vl::Key_F12 },
    { GLFW_KEY_LEFT_CONTROL, vl::Key_LeftCtrl },
    { GLFW_KEY_RIGHT_CONTROL, vl::Key_RightCtrl },
    { GLFW_KEY_LEFT_SHIFT, vl::Key_LeftShift },
    { GLFW_KEY_RIGHT_SHIFT, vl::Key_RightShift },
    { GLFW_KEY_LEFT_ALT, vl::Key_LeftAlt },
    { GLFW_KEY_RIGHT_ALT, vl::Key_RightAlt },
    { GLFW_KEY_PAGE_UP, vl::Key_PageUp },
    { GLFW_KEY_PAGE_DOWN, vl::Key_PageDown },
    { GLFW_KEY_PRINT_SCREEN, vl::Key_Print },
    { GLFW_KEY_LEFT_BRACKET, vl::Key_LeftBracket },
    { GLFW_KEY_RIGHT_BRACKET, vl::Key_RightBracket },
    { GLFW_KEY_APOSTROPHE, vl::Key_Quote },
    { GLFW_KEY_EQUAL, vl::Key_Equal },
    { GLFW_KEY_GRAVE_ACCENT, vl::Key_QuoteLeft },
    { (GLFW_MOD_SHIFT << 16) | GLFW_KEY_0, vl::Key_Exclam },
    { (GLFW_MOD_SHIFT << 16) | GLFW_KEY_APOSTROPHE, vl::Key_QuoteDbl },
    { (GLFW_MOD_SHIFT << 16) | GLFW_KEY_3, vl::Key_Hash },
    { (GLFW_MOD_SHIFT << 16) | GLFW_KEY_4, vl::Key_Dollar },
    { (GLFW_MOD_SHIFT << 16) | GLFW_KEY_7, vl::Key_Ampersand },
    { (GLFW_MOD_SHIFT << 16) | GLFW_KEY_9, vl::Key_LeftParen },
    { (GLFW_MOD_SHIFT << 16) | GLFW_KEY_0, vl::Key_RightParen },
    { (GLFW_MOD_SHIFT << 16) | GLFW_KEY_8, vl::Key_Asterisk },
    { (GLFW_MOD_SHIFT << 16) | GLFW_KEY_EQUAL, vl::Key_Plus },
    { (GLFW_MOD_SHIFT << 16) | GLFW_KEY_SEMICOLON, vl::Key_Colon },
    { (GLFW_MOD_SHIFT << 16) | GLFW_KEY_COMMA, vl::Key_Less },
    { (GLFW_MOD_SHIFT << 16) | GLFW_KEY_PERIOD, vl::Key_Greater },
    { (GLFW_MOD_SHIFT << 16) | GLFW_KEY_SLASH, vl::Key_Question },
    { (GLFW_MOD_SHIFT << 16) | GLFW_KEY_2, vl::Key_At },
    { (GLFW_MOD_SHIFT << 16) | GLFW_KEY_6, vl::Key_Caret },
    { (GLFW_MOD_SHIFT << 16) | GLFW_KEY_MINUS, vl::Key_Underscore }
};
}

//-----------------------------------------------------------------------------
vlGLFW::GLFW_window::GLFW_window()
{
}
//-----------------------------------------------------------------------------
vlGLFW::GLFW_window::~GLFW_window()
{
    lock();

    if ( window )
    {
        auto f = std::find(GLFW_windowList.cbegin(), GLFW_windowList.cend(), this);

        if ( f != GLFW_windowList.cend() )
        {
            dispatchDestroyEvent();
            glfwDestroyWindow(window);
            GLFW_windowList.erase(f);
        }
    }

    if ( GLFW_windowList.empty() )
        glfwTerminate();

    unlock();
}
//-----------------------------------------------------------------------------
vlGLFW::GLFW_window::GLFW_window( const vl::String& title, const vl::OpenGLContextFormat& info, int x, int y, int width, int height, GLFWmonitor* monitor, GLFWwindow* share )
{
    initGLFW_window(title, info, x, y, width, height, monitor, share);
}
//-----------------------------------------------------------------------------
bool vlGLFW::GLFW_window::initGLFW_window( const vl::String& title, const vl::OpenGLContextFormat& info, int x, int y, int width, int height, GLFWmonitor* monitor, GLFWwindow* share )
{
    // must protect the list...
    lock();

    // initialize the library if necessary
    if ( GLFW_windowList.empty() )
    {
        if ( !glfwInit() )
        {
            // printf("Unable to init GLFW: %s\n", SDL_GetError());  todo
            unlock();
            return false;
        }
    }

    // to set the position we have to create the window initially as invisible
    glfwWindowHint(GLFW_VISIBLE, 0);

    glfwWindowHint(GLFW_RED_BITS, info.rgbaBits().r());
    glfwWindowHint(GLFW_GREEN_BITS, info.rgbaBits().g());
    glfwWindowHint(GLFW_BLUE_BITS, info.rgbaBits().b());
    glfwWindowHint(GLFW_ALPHA_BITS, info.rgbaBits().a());

    glfwWindowHint(GLFW_ACCUM_RED_BITS, info.accumRGBABits().r());
    glfwWindowHint(GLFW_ACCUM_GREEN_BITS, info.accumRGBABits().g());
    glfwWindowHint(GLFW_ACCUM_BLUE_BITS, info.accumRGBABits().b());
    glfwWindowHint(GLFW_ACCUM_ALPHA_BITS, info.accumRGBABits().a());

    glfwWindowHint(GLFW_DEPTH_BITS, info.depthBufferBits());
    glfwWindowHint(GLFW_STENCIL_BITS, info.stencilBufferBits());

    glfwWindowHint(GLFW_DOUBLEBUFFER, info.doubleBuffer() ? GL_TRUE : GL_FALSE);
    glfwWindowHint(GLFW_STEREO, info.stereo());
    glfwWindowHint(GLFW_SAMPLES, info.multisample() ? info.multisampleSamples() : 0);
    glfwSwapInterval(info.vSync() ? 1 : 0);

    if ( info.fullscreen() )
    {
        // if monitor is null the window will be created in windowed mode
        // if the user requested full screen get the primary monitor
        if ( !monitor )
            monitor = glfwGetPrimaryMonitor();
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(width, height, title.toStdString().c_str(), monitor, share);
    if ( !window )
    {
        if ( GLFW_windowList.empty() )
        {
            glfwTerminate();
            unlock();
            return false;
        }
    }

    glfwSetWindowAspectRatio(window, 1, 1);

    // save it in the list
    GLFW_windowList.push_back(this);

    // list is safe
    unlock();

    // OpenGL extensions initialization
    glfwGetFramebufferSize(window, &width, &height);

    initGLContext();
    dispatchInitEvent();
    dispatchResizeEvent(width, height);

    // set the window position
    glfwSetWindowPos(window, x, y);

    // show the window
    glfwShowWindow(window);

    framebuffer()->setWidth(width);
    framebuffer()->setHeight(height);

    // mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    setWindowTitle(title);

    // install callbacks
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetScrollCallback(window, mouseWheelCallback);
    glfwSetCursorPosCallback(window, mousePositionCallback);
    glfwSetDropCallback(window, dropCallback);
    glfwSetWindowCloseCallback(window, closeCallback);
    glfwSetFramebufferSizeCallback(window, resizeCallback);

    glfwMakeContextCurrent(window);
    resizeCallback(window, width, height);

    return true;
}

//-----------------------------------------------------------------------------
void vlGLFW::GLFW_window::eventLoop( void )
{
    while ( !GLFW_windowList.empty() )
    {
        for ( auto iter = GLFW_windowList.begin(); iter != GLFW_windowList.end(); ++iter )
        {
            glfwPollEvents();

            if ( glfwWindowShouldClose((*iter)->window) )
            {
				(*iter)->dispatchDestroyEvent();
				glfwDestroyWindow((*iter)->window);
				(*iter)->window = 0;
				GLFW_windowList.erase(iter);
                break;
            }
            (*iter)->dispatchRunEvent();
        }
    }
}

// key callback
void vlGLFW::GLFW_window::keyCallback( GLFWwindow* w, int key, int scancode, int action, int mods )
{
    GLFW_window* gw = winFind(w);

    if ( gw )
        gw->keyCallback(key, scancode, action, mods);
}

void vlGLFW::GLFW_window::keyCallback( int key, int scancode, int action, int mods )
{
    uint16_t unicode;
    vl::EKey ekey = vl::Key_None;

    if ( action == GLFW_PRESS || action == GLFW_RELEASE || action == GLFW_REPEAT )
    {
        auto iter = key_translation_map.find(key | (mods << 16));

        if ( iter != key_translation_map.end() )
            ekey = iter->second;
        else
            ekey = vl::Key_Unknown;

        unicode = scancode; // todo

        if ( action == GLFW_PRESS || action == GLFW_REPEAT )
        {
            switch ( key )
            {
            default:
                break;

            case vl::Key_LeftCtrl:
            case vl::Key_RightCtrl:
                dispatchKeyPressEvent(unicode, vl::Key_Ctrl);
                break;

            case vl::Key_LeftShift:
            case vl::Key_RightShift:
                dispatchKeyPressEvent(unicode, vl::Key_Shift);
                break;

            case vl::Key_LeftAlt:
            case vl::Key_RightAlt:
                dispatchKeyPressEvent(unicode, vl::Key_Alt);
                break;
            }
            dispatchKeyPressEvent(unicode, ekey);
        }
        else // if(action == GLFW_RELEASE)
        {
            switch ( ekey )
            {
            default:
                break;

            case vl::Key_LeftCtrl:
            case vl::Key_RightCtrl:
                dispatchKeyReleaseEvent(unicode, vl::Key_Ctrl);
                break;

            case vl::Key_LeftShift:
            case vl::Key_RightShift:
                dispatchKeyReleaseEvent(unicode, vl::Key_Shift);
                break;

            case vl::Key_LeftAlt:
            case vl::Key_RightAlt:
                dispatchKeyReleaseEvent(unicode, vl::Key_Alt);
                break;
            }
            dispatchKeyReleaseEvent(unicode, ekey);
        }
    }
}

// mouse button callback
void vlGLFW::GLFW_window::mouseButtonCallback( GLFWwindow* w, int button, int action, int mods )
{
    GLFW_window* gw = winFind(w);

    if ( gw )
        gw->mouseButtonCallback(button, action, mods);
}

void vlGLFW::GLFW_window::mouseButtonCallback( int button, int action, int mods )
{
    if ( action == GLFW_PRESS )
    {
        if ( button == GLFW_MOUSE_BUTTON_LEFT )
            dispatchMouseDownEvent(vl::LeftButton, int(mx), int(my));
        else if ( button == GLFW_MOUSE_BUTTON_RIGHT )
            dispatchMouseDownEvent(vl::RightButton, int(mx), int(my));
        else if ( button == GLFW_MOUSE_BUTTON_MIDDLE )
            dispatchMouseDownEvent(vl::MiddleButton, int(mx), int(my));
    }
    else if ( action == GLFW_RELEASE )
    {
        if ( button == GLFW_MOUSE_BUTTON_LEFT )
            dispatchMouseUpEvent(vl::LeftButton, int(mx), int(my));
        else if ( button == GLFW_MOUSE_BUTTON_RIGHT )
            dispatchMouseUpEvent(vl::RightButton, int(mx), int(my));
        else if ( button == GLFW_MOUSE_BUTTON_MIDDLE )
            dispatchMouseUpEvent(vl::MiddleButton, int(mx), int(my));
    }
}


// mouse wheel callback
void vlGLFW::GLFW_window::mouseWheelCallback( GLFWwindow* w, double xoffset, double yoffset )
{
    lock();
    GLFW_window* gw = winFind(w);

    if ( gw )
        gw->mouseWheelCallback(xoffset, yoffset);
    unlock();
}

void vlGLFW::GLFW_window::mouseWheelCallback( double xoffset, double yoffset )
{
    dispatchMouseWheelEvent(yoffset);
}

// mouse position callback
void vlGLFW::GLFW_window::mousePositionCallback( GLFWwindow* w, double x, double y )
{
    lock();
    GLFW_window* gw = winFind(w);

    if ( gw )
        gw->mousePositionCallback(x, y);
    unlock();
}

void vlGLFW::GLFW_window::mousePositionCallback( double x, double y )
{
    mx = x;
    my = y;
    dispatchMouseMoveEvent(mx, my);
}

// drop callback
void vlGLFW::GLFW_window::dropCallback( GLFWwindow* w, int fileCount, const char** paths )
{
    lock();
    GLFW_window* gw = winFind(w);

    if ( gw )
        gw->dropCallback(fileCount, paths);
    unlock();
}

void vlGLFW::GLFW_window::dropCallback( int fileCount, const char** paths )
{
    std::vector<String> files;

    for ( int i = 0; i < fileCount; ++i )
        files.emplace_back(paths[i]);

    dispatchFileDroppedEvent(files);
}

// close callback
void vlGLFW::GLFW_window::closeCallback( GLFWwindow* w )
{
    lock();
    GLFW_window* gw = winFind(w);

    if ( gw )
        gw->closeCallback();
    unlock();
}

void vlGLFW::GLFW_window::closeCallback( void )
{
    // can block close request by calling glfwSetWindowShouldClose(window, 0);
}

// resize callback
void vlGLFW::GLFW_window::resizeCallback( GLFWwindow* w, int width, int height )
{
    lock();
    GLFW_window* gw = winFind(w);

    if ( gw )
        gw->resizeCallback(width, height);
    unlock();
}

void vlGLFW::GLFW_window::resizeCallback( int width, int height )
{
    //  resizeEvent(width, height);
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

//-----------------------------------------------------------------------------
void vlGLFW::GLFW_window::quitApplication()
{
    lock();
    while ( !GLFW_windowList.empty() )
    {
        delete GLFW_windowList.front();
        GLFW_windowList.pop_front();
    }
    unlock();
}
//-----------------------------------------------------------------------------
void vlGLFW::GLFW_window::setWindowTitle( const vl::String& title )
{
    glfwSetWindowTitle(window, title.toStdString().c_str());
}
//-----------------------------------------------------------------------------
void vlGLFW::GLFW_window::swapBuffers()
{
    glfwSwapBuffers(window);
}
//-----------------------------------------------------------------------------
void vlGLFW::GLFW_window::setPosition( int x, int y )
{
    glfwSetWindowPos(window, x, y);
}

// find the GLFW_window object whose window is w
vlGLFW::GLFW_window* vlGLFW::GLFW_window::winFind( GLFWwindow const* w )
{
    GLFW_window* gw = nullptr;

    for ( auto iter = GLFW_windowList.cbegin(); iter != GLFW_windowList.cend(); ++iter )
    {
        if ( (*iter)->window == w )
        {
            gw = *iter;
            break;
        }
    }
    return gw;
}

std::unique_ptr<std::mutex> vlGLFW::GLFW_window::mtx;
std::list<vlGLFW::GLFW_window*> vlGLFW::GLFW_window::GLFW_windowList;

//-----------------------------------------------------------------------------
