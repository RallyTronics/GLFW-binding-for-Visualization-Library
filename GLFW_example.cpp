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

#include <vlCore/VisualizationLibrary.hpp>
#include <vlGLFW/GLFW_window.hpp>
#include "Applets/App_RotatingCube.hpp"

using namespace vl;

const unsigned n_instances = 3;

int main(int argc, char* args[])
{
  /* init Visualization Library */
  VisualizationLibrary::init();

  /* setup the OpenGL context format */
  OpenGLContextFormat format;
  format.setDoubleBuffer(true);
  format.setRGBABits( 8,8,8,8 );
  format.setDepthBufferBits(24);
  format.setStencilBufferBits(8);
  format.setFullscreen(false);
  //format.setMultisampleSamples(16);
  //format.setMultisample(true);

  int x = 100;
  int y = 100;
  int width = 512;
  int height = 512;

  struct instance_t
  {
	  ref<Applet> applet;
	  ref<vlGLFW::GLFW_window> window;
  } instances[n_instances];

  for (int i = 0; i < n_instances; ++i)
  {
		/* create the applet to be run */
		instances[i].applet = new App_RotatingCube;
		instances[i].applet->initialize();

		/* create a native GLFW window */
		instances[i].window = new vlGLFW::GLFW_window;

		/* bind the applet so it receives all the GUI events related to the OpenGLContext */
		instances[i].window->addEventListener(instances[i].applet.get());
		/* target the window so we can render on it */
		instances[i].applet->rendering()->as<Rendering>()->renderer()->setFramebuffer(instances[i].window->framebuffer() );
		/* shades of gray background */
		instances[i].applet->rendering()->as<Rendering>()->camera()->viewport()->setClearColor( vl::fvec4(i * 0.2f, i * 0.2f, i * 0.2f, 1));
		/* define the camera position and orientation */
		vec3 eye    = vec3(0,10,35); // camera position
		vec3 center = vec3(0,0,0);   // point the camera is looking at
		vec3 up     = vec3(0,1,0);   // up direction
		mat4 view_mat = mat4::getLookAt(eye, center, up);
		instances[i].applet->rendering()->as<Rendering>()->camera()->setViewMatrix( view_mat );
		/* Initialize the OpenGL context and window properties */

		instances[i].window->initGLFW_window("Visualization Library on GLFW - Rotating Cube", format, x, y, width, height);
		x += 30;
		y += 30;
  }

  /* run GLFW message loop */
  vlGLFW::GLFW_window::eventLoop();

  /* shutdown Visualization Library */
  VisualizationLibrary::shutdown();

  return 0;
}
// Have fun!
