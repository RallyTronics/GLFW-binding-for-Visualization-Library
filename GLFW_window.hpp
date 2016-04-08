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

#ifndef GLFWAdapter_INCLUDE_ONCE
#define GLFWAdapter_INCLUDE_ONCE

#include <vlGLFW/link_config.hpp>
#include <vlGraphics/OpenGLContext.hpp>
#include <vlCore/String.hpp>
#include <vlCore/Vector4.hpp>
#include <GLFW/GLFW3.h>
#include <mutex>
#include <list>

namespace vlut
{
class Applet;
}

namespace vlGLFW
{
//-----------------------------------------------------------------------------
// GLFW_window
//-----------------------------------------------------------------------------
/**
 * The GLFW_window class implements an OpenGLContext using the GLFW API.
 * @note
 * GLFW notifies Unicode codes only on key-press events not on release events.
*/
class VLGLFW_EXPORT GLFW_window : public vl::OpenGLContext
{
public:
	GLFW_window();
	GLFW_window(const vl::String& title, const vl::OpenGLContextFormat& info, int x = 0, int y = 0, int width = 640, int height = 480, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
	bool initGLFW_window(const vl::String& title, const vl::OpenGLContextFormat& info, int x = 0, int y = 0, int width = 640, int height = 480, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);

	~GLFW_window();

	void setPosition(int x, int y);

	virtual void swapBuffers();

	//! Quits the event loop
	static void quitApplication();

	void setWindowTitle(const vl::String&);

	void setMouseVisible(bool visible)
	{
		mMouseVisible = visible;
		glfwSetInputMode(window, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
	}

	void setMousePosition(int x, int y)
	{
		glfwSetCursorPos(window, x, y);
	}

	void update() override
	{
	}

	void makeCurrent()
	{
		glfwMakeContextCurrent(window);
	}

	static void setThreadSafe(void)
	{
		mtx = std::make_unique<std::mutex>();
	}

	static void eventLoop(void);

protected:
	// key callback
	static void keyCallback(GLFWwindow *w, int key, int scancode, int action, int mods);
	void keyCallback(int key, int scancode, int action, int mods);

	// mouse button callback
	static void mouseButtonCallback(GLFWwindow *w, int button, int action, int mods);
	void mouseButtonCallback(int button, int action, int mods);

	// mouse wheel callback
	static void mouseWheelCallback(GLFWwindow *w, double xoffset, double yoffset);
	void mouseWheelCallback(double xoffset, double yoffset);

	// mouse position callback
	static void mousePositionCallback(GLFWwindow *w, double x, double y);
	void mousePositionCallback(double x, double y);

	// drop callback
	static void dropCallback(GLFWwindow *w, int fileCount, const char **paths);
	void dropCallback(int fileCount, const char **paths);

	// close callback
	static void closeCallback(GLFWwindow *w);
	void closeCallback(void);

	// resize callback
	static void resizeCallback(GLFWwindow *w, int width, int height);
	void resizeCallback(int width, int height);

	// find the GLFW_window object whose window is w
	static GLFW_window* winFind(GLFWwindow const *w);

	static void lock(void)
	{
		if (mtx)
			mtx->lock();
	}

	static void unlock(void)
	{
		if (mtx)
			mtx->unlock();
	}

protected:
    GLFWwindow* window;
	double mx, my;
	static std::list<GLFW_window *> GLFW_windowList;
	static std::unique_ptr<std::mutex> mtx;
};
}

#endif
