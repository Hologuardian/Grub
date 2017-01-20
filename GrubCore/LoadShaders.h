#include "Constants.h"
#ifdef GRUB_USEOPENGL
//////////////////////////////////////////////////////////////////////////////
//
//  --- LoadShaders.h ---
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __LOAD_SHADERS_H__
#define __LOAD_SHADERS_H__

#include <GL/gl.h>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

//----------------------------------------------------------------------------
//
//  LoadShaders() takes an array of ShaderFile structures, each of which
//    contains the type of the shader, and a pointer a C-style character
//    string (i.e., a NULL-terminated array of characters) containing the
//    entire shader source.
//
//  The array of structures is terminated by a final Shader with the
//    "type" field set to GL_NONE.
//
//  LoadShaders() returns the shader program value (as returned by
//    glCreateProgram()) on success, or zero on failure. 
//

typedef struct {
    GLenum       type;
    const char*  filename;
    GLuint       shader;
} ShaderInfo;

GLuint LoadShaders( ShaderInfo* );

//----------------------------------------------------------------------------

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // __LOAD_SHADERS_H__
#endif

#ifdef GRUB_DX11

#include<d3d11.h>
#include <DirectXMath.h>

#pragma region PipeLine Explanation Stage By Stage

	/** 
	INPUT ASSEMBLER
		The very first stage, it is a fixed function stage, which means we do no programming to implement it.
		The IA reads geometric data, vertices and indices. Then, it uses the data to create geometric 
		primitives like triangles, squares, lines, and points which will be	fed into and used by the other 
		stages. Indices define how the primitives should be put together by the vertices.

	VERTEX SHADER
		The first programable shader, The VS is where ALL VERTICES go through after the primitives have been
		assembles in the IA. Every Vertex drawn will be put through the VS. With the VS, you are able to do 
		things lie transformation, scaling, lightiing, displacement mapping for textures and stuff like that. 
		The VS MUST ALWAYS BE IMPLEMENTED FOR THE PIPELINE TO WORK, even if the vertices in the program
		do not need to be modified.

	HULL SHADER 
		The HS is the first of the three new optional stages added to DirectX11 rendering pipeline. The three 
		new stages, Hull Shader Stage, Tesselator Stage, and Domain shader stage all work together to 
		implement tesselation. Tesselation takes a primitive object such as a triangle, or line, and divides
		it up into many smaller sections to inrease the detail of models extremley fast on the GPU and doesnt 
		store it in memory. 

		The HULL shader calculates how and where to add new vertices to a primitve to make it more detailed.
		It then sends the data into the Tesselator stage and Domain Shader stage.

	TESSELATOR STAGE
		The Tesselator stage is the second stage in the tesselation process. This is a fixed function stage.
		This stage takes the input from the Hull shader, and actually do the dividing of the primitive. It then
		passes the data out to the Domain Shader.

	DOMAIN SHADER STAGE
		The third of the three stages in the tesselation process. This is a programmable function stage. What
		this stage does is take the Positions of the new vertices from the Hull Shader Stage, and transform
		the vertices recieved from the tesselator stage to create the more detail, since just adding more
		vertices in the center of a triangle or line would not increase the detail in any way. Then it passes
		the vertices into the geometry shader stage.

	GEOMETRY SHADER STAGE
		This Shader stage is optional. It's also a progammable function stage. It accepts primitves as input
		such as 3 vertices for triangles, 2 for lines, and one for a point. It can also take data for 
		edge-adjacent primitives as input, like an additional 2 vertices  for a line, or an additional 3 for
		a triangle. An advantage to the GS is that it can create or destroy primitives, where the VS cannot
		(it takes one vertex, and outputs one). We could turn one point into a quad or a triangle with this 
		stage. We are able to pass data from the GS to the rasterizer stage, and/or through the stream Output
		to a vertex buffer in memory.

	STREAM OUTPUT STAGE
		This stage is used to obtain Vertex data from the pipeline, specifically the GS, or VS if there is no
		GS. Vertex data sent to memory from the SO is put into one or more vertex buffers. Vertex data output
		from the SO are always sent out as lists, such as line lists or triangle lists. Incomplete primitives 
		are NEVER sent out, they are silently discarded like in the VS or GS. Incomplete Primitives are 
		primitives such as triangles with only 2 vertices or a line with a single vertex.

	RASTERIZATION STAGE 
		The RS stage takes the vector information (shapes and primitives) sent to it and turns it into pixels
		by interpolating per-vertex values across each primitive. it also handles the clipping, which is 
		basically cutting primitives that are outside the view of the screen. 

	PIXEL SHADER STAGE
		This stage does calculations and modifies each pixel that will be on the screen, such as lighting
		on a per-pixel base. it is another programable function, and optional stage. The RS invokes the pixel
		shader once for each pixel in a primitive. The values and attributes of each vertex in a primitive 
		are interpolated across the entire primitive in the RS. Basicaly it's like the VS, where
		the VS has a 1:1 mapping (it takes one vertex and returns one vertex), the PS also has a 1:1 mapping
		(it takes one pixel and returns one pixel).

		The job of this stage is to calculate the final color of each pixel fragment. a pixel fragment is each
		potential pixel that will be drawn to screen. For example, there is a solid square beind a solid
		circle. The pixels in the square are pixel fragments, as are the pixels in the solid circle. Each has 
		a chance to be written to the screen, but once it gets to the output merger stage, which decides the 
		final pixel to be drawn to screen. it will see the depth value of the circle is less than the value 
		of the square, so only the pixels from the circle will be drawn. the PS outputs a 4D color value.

	OUTPUT MERGER STAGE 
		The final stage of the pipeline, Basically the stage takes the pixel fragments and depth/stencil 
		buffers and determines which pixels are actually written to the render target.
	**/
#pragma endregion 

ID3D11Buffer* triangleVertBuffer;
ID3D11VertexShader* VS;
ID3D11PixelShader* PS;
ID3D10Blob* VS_Buffer = NULL;
ID3D10Blob* PS_Buffer = NULL;

ID3D10Blob* Errors;

ID3D11InputLayout* vertLayout;


struct Vertex //Overload Vertex Structure
{
	Vertex(){}
	Vertex(float x, float y, float z,
		float cr, float cg, float cb, float ca)
		: pos(x, y, z), color(cr, cg, cb, ca) {}

		DirectX::XMFLOAT3 pos;	
		DirectX::XMFLOAT4 color;
};

/**Create the input layout object, this tells Direct3D what our vertex structure consists of, and
what to do with each component in our vertex struct. We provide the information to Direct3D with an 
array of D3D11_INPUT_ELEMENT_DESC elements. Each element in the D3D11_INPUT_ELEMENT_DESC array describes
one element in the vertex structure.
**/
D3D11_INPUT_ELEMENT_DESC layout[] =
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
};
UINT numElements = ARRAYSIZE(layout);



#endif