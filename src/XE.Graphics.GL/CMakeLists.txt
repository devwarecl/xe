
set (target "XE.Graphics.GL")
set (source_base "XE/Graphics/GL")
set (sources_xe_graphics_glcore
	"XE/Graphics/GL.hpp"

	"${source_base}/InputManagerGLFW.hpp"
	"${source_base}/InputManagerGLFW.cpp"

	"${source_base}/WindowGLFW.hpp"
	"${source_base}/WindowGLFW.cpp"

	"${source_base}/GraphicsDeviceGL.hpp"
	"${source_base}/GraphicsDeviceGL.cpp"
	
	"${source_base}/TextureBaseGL.hpp"
	"${source_base}/TextureBaseGL.cpp"
	"${source_base}/Texture2DGL.hpp"
	"${source_base}/Texture2DGL.cpp"
	"${source_base}/Texture2DArrayGL.hpp"
	"${source_base}/Texture2DArrayGL.cpp"
	"${source_base}/Texture3DGL.hpp"
	"${source_base}/Texture3DGL.cpp"
	"${source_base}/TextureCubeMapGL.hpp"
	"${source_base}/TextureCubeMapGL.cpp"
	
	"${source_base}/ShaderGL.hpp"
	"${source_base}/ShaderGL.cpp"
	"${source_base}/ProgramGL.hpp"
	"${source_base}/ProgramGL.cpp"
	
	"${source_base}/ProgramGL.hpp"
	"${source_base}/ProgramGL.cpp"
	
	"${source_base}/BufferGL.hpp"
	"${source_base}/BufferGL.cpp"
	
	"${source_base}/SubsetGL.hpp"
	"${source_base}/SubsetGL.cpp"

	"${source_base}/Conversion.hpp"
	"${source_base}/Conversion.cpp"

	"${source_base}/Util.hpp"
	"${source_base}/Util.cpp"
) 

source_group ("\\XE\\Graphics\\GL" FILES ${sources_xe_graphics_glcore})

add_library (${target} ${sources_xe_graphics_glcore})

target_link_libraries (${target} glad-gl4 glfw XE.Core)