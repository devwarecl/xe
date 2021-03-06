
set (target "XE.Graphics")

set (sources
	"include/XE/Graphics/IWindow.h"
	"include/XE/Graphics/GraphicsDevice.h" 
	"include/XE/Graphics/BufferDescriptor.h" 
	"include/XE/Graphics/Subset.h" 
	"include/XE/Graphics/Texture.h" 
	"include/XE/Graphics/Texture2D.h" 
	"include/XE/Graphics/Texture2DArray.h" 
	"include/XE/Graphics/Texture3D.h" 
	"include/XE/Graphics/TextureCubeMap.h" 
	"include/XE/Graphics/PixelFormat.h"
	"include/XE/Graphics/Shader.h"
	"include/XE/Graphics/Program.h"
	"include/XE/Graphics/Vertex.h"
	"include/XE/Graphics/VertexLayout.h"
	"include/XE/Graphics/VertexFormat.h"
	"include/XE/Graphics/Uniform.h"
	"include/XE/Graphics/ImageImpl.h"
	"include/XE/Graphics/Image.h"
	"include/XE/Graphics/ImageLoader.h"
	"include/XE/Graphics/Material.h"
	"include/XE/Graphics/Viewport.h"

	"src/IWindow.cpp"	
	"src/GraphicsDevice.cpp"
	"src/BufferDescriptor.cpp" 
	"src/Subset.cpp" 
	"src/Texture.cpp" 
	"src/Texture2D.cpp" 
	"src/Texture2DArray.cpp" 
	"src/Texture3D.cpp" 
	"src/TextureCubeMap.cpp" 
	"src/PixelFormat.cpp" 
	"src/Shader.cpp" 
	"src/Program.cpp" 
	"src/Vertex.cpp"
	"src/VertexLayout.cpp"
	"src/VertexFormat.cpp"
	"src/Uniform.cpp"
	"src/ImageImpl.cpp"
	"src/Image.cpp"
	"src/ImageLoader.cpp"
	"src/Material.cpp"
	"src/Viewport.cpp"
)

add_library (${target} ${sources})

target_include_directories(${target} PUBLIC "include/")
target_link_libraries(${target} XE.Core XE.Math)
target_compile_options (${target} PUBLIC ${XE_CXX_FLAGS})
