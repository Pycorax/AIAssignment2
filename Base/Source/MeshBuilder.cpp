#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include "Vertex.h"
#include "MyMath.h"
#include "LoadOBJ.h"
#include "LoadHmap.h"

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	v.pos.Set(-1000, 0, 0);
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(1000, 0, 0);
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, -1000, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 1000, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, -1000);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, 1000);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a crosshair;
Then generate the VBO/IBO and store them in Mesh object
\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2
\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCrossHair(const std::string &meshName, float colour_r, float colour_g, float colour_b, float length)
{
	// Declare the variable to store a vertex and the buffer for storing vertices
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	// Vertex #1
	v.pos.Set(-length, 0, 0);
	v.color.Set(colour_r, colour_g, colour_b);
	vertex_buffer_data.push_back(v);
	// Vertex #2
	v.pos.Set(length, 0, 0);
	v.color.Set(colour_r, colour_g, colour_b);
	vertex_buffer_data.push_back(v);
	// Vertex #3
	v.pos.Set(0, -length, 0);
	v.color.Set(colour_r, colour_g, colour_b);
	vertex_buffer_data.push_back(v);
	// Vertex #4
	v.pos.Set(0, length, 0);
	v.color.Set(colour_r, colour_g, colour_b);
	vertex_buffer_data.push_back(v);
	std::vector<GLuint> index_buffer_data;
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);

	Mesh *mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;
	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, float length/* = 1.f*/, float width/* = 1.f*/)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	
	v.pos.Set(-0.5f * length,-0.5f * width,0);
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length,-0.5f * width,0);
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(1.0f, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length, 0.5f * width,0);
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(1.0f, 1.0f);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * length, 0.5f * width,0);
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(0, 1.0f);
	vertex_buffer_data.push_back(v);
	
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0);
	
	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a ellipse; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - Name of mesh
\param color - Colour of the ellipse
\param heightRadius - Height of ellipse / 2
\param widthRadius - Width of ellipse / 2
\param numSlice - Number of vertex stacks that make up the ellipse; more = smoother curve

\return Pointer to mesh storing VBO/IBO of ellipse
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateEllipse(const std::string &meshName, Color color, float heightRadius, float widthRadius, unsigned int numSlice)
{
	Vertex v;
	vector<Vertex> vertex_buffer_data;
	float degreePerSlice = 360 / static_cast<float>(numSlice);

	v.pos.Set(0.0f, 0.0f, 0.0f);
	v.color = color;
	v.normal.Set(0.0f, 1.0f, 0.0f);
	vertex_buffer_data.push_back(v);

	for (float theta = 0; theta <= 360; theta += degreePerSlice)
	{
		float thetaRad = Math::DegreeToRadian(theta);

		v.pos.Set(heightRadius * cos(thetaRad), 0.0f, widthRadius * sin(thetaRad));
		v.color = color;
		v.normal.Set(0.0f, 1.0f, 0.0f);
		vertex_buffer_data.push_back(v);
	}

	vector<GLuint> index_buffer_data;

	for (size_t theta = 0; theta < vertex_buffer_data.size(); ++theta)
	{
		index_buffer_data.push_back(theta);
		index_buffer_data.push_back(0);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);	// Bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a circle; Use random color for each vertex. Then generate the VBO/IBO and store them in Mesh object

\param meshName - Name of mesh
\param color - Colour of the circle
\param radius - Radius of circle
\param numSlice - Number of slices that make up the circle; more = smoother curve

\return Pointer to mesh storing VBO/IBO of circle
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCircle(const std::string &meshName, Color color, float radius, unsigned int numSlice)
{
	return GenerateEllipse(meshName, color, radius, radius, numSlice);
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color, float length)
{
	const int VERTICES_PER_SIDE = 4;
	Vertex v;
	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;
	float texRepeatX = 1.0f;
	float texRepeatY = 1.0f;

	v.color = color;

	// Front
	v.normal.Set(0, 0, 1);
	// Front bottom left
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);
	// Front bottom right
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);
	v.texCoord.Set(texRepeatX, 0);
	vertex_buffer_data.push_back(v);
	// Front top right
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);
	v.texCoord.Set(texRepeatX, texRepeatY);
	vertex_buffer_data.push_back(v);
	// Front top left
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);
	v.texCoord.Set(0, texRepeatY);
	vertex_buffer_data.push_back(v);

	// Right
	v.normal.Set(1, 0, 0);
	// Bottom Left
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);
	v.texCoord.Set(texRepeatX, 0);
	vertex_buffer_data.push_back(v);
	// Bottom right
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);
	// Top right
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);
	v.texCoord.Set(0, texRepeatY);
	vertex_buffer_data.push_back(v);
	// Top left
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);
	v.texCoord.Set(texRepeatX, texRepeatY);
	vertex_buffer_data.push_back(v);

	// Back
	v.normal.Set(0, 0, 1);
	// Bottom Left
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);
	// Bottom right
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);
	v.texCoord.Set(texRepeatX, 0);
	vertex_buffer_data.push_back(v);
	// Top right
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);
	v.texCoord.Set(texRepeatX, texRepeatY);
	vertex_buffer_data.push_back(v);
	// Top left
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);
	v.texCoord.Set(0, texRepeatY);
	vertex_buffer_data.push_back(v);

	// Left
	v.normal.Set(-1, 0, 0);
	// Bottom Left
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);
	v.texCoord.Set(texRepeatX, 0);
	vertex_buffer_data.push_back(v);
	// Bottom right
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);
	// Top right
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);
	v.texCoord.Set(0, texRepeatY);
	vertex_buffer_data.push_back(v);
	// Top left
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);
	v.texCoord.Set(texRepeatX, texRepeatY);
	vertex_buffer_data.push_back(v);

	// Top
	v.normal.Set(0, 1, 0);
	// Bottom Left
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);
	// Bottom right
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);
	v.texCoord.Set(texRepeatX, 0);
	vertex_buffer_data.push_back(v);
	// Top right
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);
	v.texCoord.Set(texRepeatX, texRepeatY);
	vertex_buffer_data.push_back(v);
	// Top left
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);
	v.texCoord.Set(0, texRepeatY);
	vertex_buffer_data.push_back(v);

	// Bottom
	v.normal.Set(0, -1, 0);
	// Bottom Left
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);
	// Bottom right
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);
	v.texCoord.Set(texRepeatX, 0);
	vertex_buffer_data.push_back(v);
	// Top right
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);
	v.texCoord.Set(texRepeatX, texRepeatY);
	vertex_buffer_data.push_back(v);
	// Top left
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);
	v.texCoord.Set(0, texRepeatY);
	vertex_buffer_data.push_back(v);

	for (size_t i = 0; i < vertex_buffer_data.size() / VERTICES_PER_SIDE; ++i)
	{
		index_buffer_data.push_back(0 + VERTICES_PER_SIDE * i);
		index_buffer_data.push_back(1 + VERTICES_PER_SIDE * i);
		index_buffer_data.push_back(2 + VERTICES_PER_SIDE * i);
		index_buffer_data.push_back(2 + VERTICES_PER_SIDE * i);
		index_buffer_data.push_back(3 + VERTICES_PER_SIDE * i);
		index_buffer_data.push_back(0 + VERTICES_PER_SIDE * i);
	}
	
	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 36;
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateRing(const std::string &meshName, Color color, unsigned numSlice, float outerR, float innerR)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float degreePerSlice = 360.f / numSlice;
	//float radianPerSlice = Math::DegreeToRadian(360.f) / numSlice;
	for(unsigned slice = 0; slice < numSlice + 1; ++slice)
	{
		float theta = slice * degreePerSlice;
		v.color = color;
		v.normal.Set(0, 1, 0);
		v.pos.Set(outerR * cos(Math::DegreeToRadian(theta)), 0, outerR * sin(Math::DegreeToRadian(theta)));
		vertex_buffer_data.push_back(v);
		
		v.color = color;
		v.normal.Set(0, 1, 0);
		v.pos.Set(innerR * cos(Math::DegreeToRadian(theta)), 0, innerR * sin(Math::DegreeToRadian(theta)));
		vertex_buffer_data.push_back(v);
	}
	for(unsigned slice = 0; slice < numSlice + 1; ++slice)
	{
		index_buffer_data.push_back(2 * slice + 0);
		index_buffer_data.push_back(2 * slice + 1);
		//index_buffer_data.push_back(2 * slice + 3);
		//index_buffer_data.push_back(2 * slice + 4);
		//index_buffer_data.push_back(2 * slice + 3);
		//index_buffer_data.push_back(2 * slice + 2);
	}

	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateMeshFromSheet(const std::string &meshName, unsigned numRow, unsigned numCol, unsigned frameRow, unsigned frameCol, float posX, float posY)
{
	Vertex v;
	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;
	// Insert codes to render a quad.
	// Get new tex coord for each frame.

	if (numRow * numCol <= frameRow * numCol + frameCol) // Frame number wrong
	{
		return NULL;
	}

	float width = 1.f / numCol;
	float height = 1.f / numRow;

	//float u1 = frameCol * width;
	//float v1 = 1.f - height - frameRow * height;
	float u1 = frameCol * width;
	float v1 = 1.f - height - frameRow * height;
	v.pos.Set(static_cast<float>(posX), static_cast<float>(posY), 0.f);
	v.texCoord.Set(u1, v1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(static_cast<float>(posX + 1), static_cast<float>(posY), 0.f);
	v.texCoord.Set(u1 + width, v1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(static_cast<float>(posX + 1), static_cast<float>(posY + 1), 0.f);
	v.texCoord.Set(u1 + width, v1 + height);
	vertex_buffer_data.push_back(v);

	v.pos.Set(static_cast<float>(posX), static_cast<float>(posY + 1), 0.f);
	v.texCoord.Set(u1, v1 + height);
	vertex_buffer_data.push_back(v);
			
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0); 

	Mesh *mesh = new Mesh(meshName);    
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);  
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);   
	
	mesh->indexSize = index_buffer_data.size(); 
	mesh->mode = Mesh::DRAW_TRIANGLES;   

	return mesh; 
}

/******************************************************************************/ 
/*!
\brief Generate a 2D mesh Then generate the VBO/IBO and store them in Mesh object  
\param meshName - name of mesh 
\param lengthX - width of quad 
\param lengthY - height of quad  
\return Pointer to mesh storing VBO/IBO of quad 
*/ 
/******************************************************************************/ 
Mesh* MeshBuilder::Generate2DMesh(const std::string &meshName, Color color, int pos_x, int pos_y, int width, int height) 
{
	Vertex v;  

	std::vector<Vertex> vertex_buffer_data;  
	std::vector<GLuint> index_buffer_data;   
	
	// Vertex #1
	v.pos.Set(static_cast<float>(pos_x), static_cast<float>(pos_y), 0.f);
	v.color = color; 
	v.normal.Set(0.f, 0.f, 1.f);
	v.texCoord.Set(0.f, 0.f);
	vertex_buffer_data.push_back(v);
	
	// Vertex #2 
	v.pos.Set(static_cast<float>(pos_x + width), static_cast<float>(pos_y), 0.f);
	v.color = color; 
	v.normal.Set(0.f, 0.f, 1.f);
	v.texCoord.Set(1.0f, 0); 
	vertex_buffer_data.push_back(v);  

	// Vertex #3  
	v.pos.Set(static_cast<float>(pos_x + width), static_cast<float>(pos_y + height), 0.f);
	v.color = color;  
	v.normal.Set(0.f, 0.f, 1.f);
	v.texCoord.Set(1.0f, 1.0f); 
	vertex_buffer_data.push_back(v);  
	
	// Vertex #4  
	v.pos.Set(static_cast<float>(pos_x), static_cast<float>(pos_y +height), 0.f);
	v.color = color;  v.normal.Set(0.f, 0.f, 1.f);
	v.texCoord.Set(0.f, 1.0f);
	vertex_buffer_data.push_back(v);    
	
	index_buffer_data.push_back(3);  
	index_buffer_data.push_back(0);  
	index_buffer_data.push_back(2);  
	index_buffer_data.push_back(1);  
	index_buffer_data.push_back(2);  
	index_buffer_data.push_back(0);   
	
	Mesh *mesh = new Mesh(meshName);    
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);  
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);   
	
	mesh->indexSize = index_buffer_data.size(); 
	mesh->mode = Mesh::DRAW_TRIANGLES;   

	return mesh; 
} 

float sphereX(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta));
}
float sphereY(float phi, float theta)
{
	return sin(Math::DegreeToRadian(phi));
}
float sphereZ(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta));
}

Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color, unsigned numStack, unsigned numSlice, float radius)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	
	float degreePerStack = 180.f / numStack;
	float degreePerSlice = 360.f / numSlice;
	//float radianPerSlice = Math::DegreeToRadian(360.f) / numSlice;

	for(unsigned stack = 0; stack < numStack + 1; ++stack) //stack //replace with 180 for sphere
	{
		float phi = -90.f + stack * degreePerStack;
		for(unsigned slice = 0; slice < numSlice + 1; ++slice) //slice
		{
			float theta = slice * degreePerSlice;
			Vertex v;
			v.pos.Set(radius * sphereX(phi, theta), radius * sphereY(phi, theta), radius * sphereZ(phi, theta));
			v.color = color;
			v.normal.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
			vertex_buffer_data.push_back(v);
		}
	}
	for(unsigned stack = 0; stack < numStack; ++stack)
	{
		for(unsigned slice = 0; slice < numSlice + 1; ++slice)
		{
			index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
			//index_buffer_data.push_back((numSlice + 1) * stack + slice + 1);
			//index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 1);
			//index_buffer_data.push_back((numSlice + 1) * stack + slice + 1);
			//index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateCone(const std::string &meshName, Color color, unsigned numSlice, float radius, float height)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	
	Vertex v;
	float degreePerSlice = 360.f / numSlice;

	for(unsigned slice = 0; slice < numSlice + 1; ++slice) //slice
	{
		float theta = slice * degreePerSlice;
		Vector3 normal(height * cos(Math::DegreeToRadian(theta)), radius, height * sin(Math::DegreeToRadian(theta)));
		normal.Normalize();

		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), 0, radius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal = normal;
		vertex_buffer_data.push_back(v);
		
		v.pos.Set(0, height, 0);
		v.color = color;
		v.normal = normal;
		vertex_buffer_data.push_back(v);
	}
	for(unsigned slice = 0; slice < numSlice + 1; ++slice)
	{
		index_buffer_data.push_back(slice * 2 + 0);
		index_buffer_data.push_back(slice * 2 + 1);
	}

	Mesh *mesh = new Mesh(meshName);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateOBJ(const std::string &meshName, const std::string &file_path)
{
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
	if(!success)
		return NULL;

	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);

	Mesh *mesh = new Mesh(meshName);
	
	mesh->mode = Mesh::DRAW_TRIANGLES;
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	
	float width = 1.f / numCol;
	float height = 1.f / numRow;
	int offset = 0;
	for(unsigned i = 0; i < numRow; ++i)
	{
		for(unsigned j = 0; j < numCol; ++j)
		{
			float u1 = j * width;
			float v1 = 1.f - height - i * height;
			v.pos.Set(-0.5f, -0.5f, 0);
			v.texCoord.Set(u1, v1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f, -0.5f, 0);
			v.texCoord.Set(u1 + width, v1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f, 0.5f, 0);
			v.texCoord.Set(u1 + width, v1 + height);
			vertex_buffer_data.push_back(v);

			v.pos.Set(-0.5f, 0.5f, 0);
			v.texCoord.Set(u1, v1 + height);
			vertex_buffer_data.push_back(v);
	
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 3);
			offset += 4;
		}
	}
	
	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}
/******************************************************************************/
// Skyplane - TSL
Mesh* MeshBuilder::GenerateSkyPlane(const std::string &meshName, Color color, int slices, float PlanetRadius, float AtmosphereRadius, float hTile, float vTile)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	const unsigned short MIN_SLICES = 1;			// Char to save memory
	const unsigned short MAX_SLICES = 256;		// Char to save memory

	// Limit the range of slices values
	if (slices < MIN_SLICES)
	{
		slices = MIN_SLICES;
	}
	else if (slices > MAX_SLICES)
	{
		slices = MAX_SLICES;
	}

	// Length of the plane
	float planeSize = 2.0f * (float)sqrtf((AtmosphereRadius * AtmosphereRadius) - (PlanetRadius * PlanetRadius));
	// Length of a slice & divides plane evenly
	float delta = planeSize / (float)slices;
	// Used for tex-coords
	float texDelta = 2.0f / (float)slices;

	// Calculate the vertex
	for ( int z = 0; z <= slices; ++z )
	{
		for ( int x = 0; x <= slices; ++x )
		{
			float xDist = (-0.5f * planeSize) + ( (float)x * delta );
			float zDist = (-0.5f * planeSize) + ( (float)z * delta );
			float xHeight = ( xDist * xDist ) / AtmosphereRadius;
			float zHeight = ( zDist * zDist ) / AtmosphereRadius;
			float height = xHeight + zHeight;
			
			Vertex tv; // temporary vertex
			tv.pos.x = xDist;
			tv.pos.y = 0.0f - height;
			tv.pos.z = zDist;

			// Calculate the texture coordinates
			tv.texCoord.u = hTile * ((float)x * texDelta * 0.5f);
			tv.texCoord.v = vTile * (1.0f - (float)z * texDelta * 0.5f);
			tv.color = color;
			vertex_buffer_data.push_back(tv);
		}
	}

	// Calculate the indices
	int index = 0; // Indices
	for (int i=0; i < slices; ++i)
	{
		for (int j=0; j < slices; ++j)
		{
			int startvert = (i * (slices+1) + j);
			index_buffer_data.push_back(startvert);// tri 1
			index_buffer_data.push_back(startvert + 1);
			index_buffer_data.push_back(startvert + slices + 1);
			index_buffer_data.push_back(startvert + 1); // tri 2
			index_buffer_data.push_back(startvert + slices + 2);
			index_buffer_data.push_back(startvert + slices + 1);
		}
	}

	// Create the mesh
	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh * MeshBuilder::GenerateTerrainLegacy(const std::string & meshName, const std::string & file_path, std::vector<unsigned char>& heightMap)
{
	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;

	const float SCALE_FACTOR = 256.0f;
	if (!LoadHeightMap(file_path.c_str(), heightMap))
		return NULL;

	Vertex v;
	v.normal.Set(0.0f, 1.0f, 0.0f);
	unsigned terrainSize = (unsigned)sqrt((double)heightMap.size());
	for (unsigned z = 0; z < terrainSize; ++z)
	{
		for (unsigned x = 0; x < terrainSize; ++x)
		{
			float scaledHeight = (float)heightMap[z * terrainSize + x] / SCALE_FACTOR;
			v.pos.Set(static_cast<float>(x) / terrainSize - 0.5f, scaledHeight, static_cast<float>(z) / terrainSize - 0.5f);
			v.color.Set(scaledHeight, scaledHeight, scaledHeight); //for rendering height map without texture
			v.texCoord.Set((float)x / terrainSize * 8, 1.f - (float)z / terrainSize * 8);
			vertex_buffer_data.push_back(v);
		}
	}
	for (unsigned z = 0; z < terrainSize - 1; ++z)
	{
		for (unsigned x = 0; x < terrainSize - 1; ++x)
		{
			index_buffer_data.push_back(terrainSize * z + x + 0); //Tri 1
			index_buffer_data.push_back(terrainSize * (z + 1) + x + 0);
			index_buffer_data.push_back(terrainSize * z + x + 1);
			index_buffer_data.push_back(terrainSize * (z + 1) + x + 1); //Tri 2
			index_buffer_data.push_back(terrainSize * z + x + 1);
			index_buffer_data.push_back(terrainSize * (z + 1) + x + 0);
		}
	}

	// Create the mesh
	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh * MeshBuilder::GenerateTerrain(const std::string & meshName, std::vector<unsigned char>& heightMap)
{
	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;

	const float SCALE_FACTOR = 256.0f;

	// For normal calculation
	Vector3 top, bot, left, right;

	Vertex v;
	v.normal.Set(0.0f, 1.0f, 0.0f);
	unsigned terrainSize = (unsigned)sqrt((double)heightMap.size());
	for (unsigned z = 0; z < terrainSize; ++z)
	{
		for (unsigned x = 0; x < terrainSize; ++x)
		{
			float scaledHeight = (float)heightMap[z * terrainSize + x] / SCALE_FACTOR;
			v.pos.Set(static_cast<float>(x) / terrainSize - 0.5f, scaledHeight, static_cast<float>(z) / terrainSize - 0.5f);
			v.color.Set(scaledHeight, scaledHeight, scaledHeight); //for rendering height map without texture
			v.texCoord.Set((float)x / terrainSize * 8, 1.f - (float)z / terrainSize * 8);

			// Calculate Normal
			// -- Calculate the adjacent positions
			right.Set(x < terrainSize - 1 ? x + 1 : x, 0.0f, terrainSize * z);
			left.Set(x < 0 ? x - 1 : x, 0.0f, terrainSize * z);
			bot.Set(x, 0.0f, terrainSize * (z < terrainSize - 1 ? z + 1 : z));
			top.Set(x, 0.0f, terrainSize * (z < 0 ? z - 1 : z));
			// -- Calculate the normal for the x-axis
			float normalX = heightMap[right.x + right.z] - heightMap[left.x + left.z];
			if (x > 0 || x == terrainSize - 1)
			{
				normalX *= 2;
			}
			// -- Calculate the normal in the z-axis		
			float normalZ = heightMap[bot.x + bot.z] - heightMap[top.x + top.z];
			if (z > 0 || x == terrainSize - 1)
			{
				normalZ *= 2;
			}
			// -- Set & Normalize		
			v.normal.Set(-normalX, 2.0, normalZ);
			v.normal.Normalize();

			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned z = 0; z < terrainSize - 1; ++z)
	{
		for (unsigned x = 0; x < terrainSize - 1; ++x)
		{
			index_buffer_data.push_back(terrainSize * z + x + 0); //Tri 1
			index_buffer_data.push_back(terrainSize * (z + 1) + x + 0);
			index_buffer_data.push_back(terrainSize * z + x + 1);
			index_buffer_data.push_back(terrainSize * (z + 1) + x + 1); //Tri 2
			index_buffer_data.push_back(terrainSize * z + x + 1);
			index_buffer_data.push_back(terrainSize * (z + 1) + x + 0);
		}
	}

	// Create the mesh
	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

SpriteAnimation* MeshBuilder::GenerateSpriteAnimation(const std::string &meshName, unsigned numRow, unsigned numCol)
{
	Vertex v;
	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;
	// Insert codes to render a quad.
	// Get new tex coord for each frame.

	float width = 1.f / numCol;
	float height = 1.f / numRow;
	int offset = 0;
	for (unsigned i = 0; i < numRow; ++i)
	{
		for (unsigned j = 0; j < numCol; ++j)
		{
			float u1 = j * width;
			float v1 = 1.f - height - i * height;
			v.pos.Set(-0.5f, -0.5f, 0);
			v.texCoord.Set(u1, v1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f, -0.5f, 0);
			v.texCoord.Set(u1 + width, v1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f, 0.5f, 0);
			v.texCoord.Set(u1 + width, v1 + height);
			vertex_buffer_data.push_back(v);

			v.pos.Set(-0.5f, 0.5f, 0);
			v.texCoord.Set(u1, v1 + height);
			vertex_buffer_data.push_back(v);

			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 3);
			offset += 4;
		}
	}

	SpriteAnimation *anim = new SpriteAnimation(meshName, numRow, numCol);

	glBindBuffer(GL_ARRAY_BUFFER, anim->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, anim->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	anim->indexSize = index_buffer_data.size();
	anim->mode = Mesh::DRAW_TRIANGLES;

	return anim;
}

//The last 2 variables change the size rendered
SpriteAnimation* MeshBuilder::GenerateSpriteAnimation2D(const std::string &meshName, unsigned numRow, unsigned numCol, int posX/* = 0*/, int posY/* = 0*/, int ScaleX, int ScaleY)
{
	Vertex v;
	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;
	// Insert codes to render a quad.
	// Get new tex coord for each frame.

	float width = 1.f / numCol;
	float height = 1.f / numRow;
	int offset = 0;
	for (unsigned i = 0; i < numRow; ++i)
	{
		for (unsigned j = 0; j < numCol; ++j)
		{
			float u1 = j * width;
			float v1 = 1.f - height - i * height;
			v.pos.Set(static_cast<float>(posX), static_cast<float>(posY), 0.f);
			v.texCoord.Set(u1, v1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(static_cast<float>(posX + ScaleX) , static_cast<float>(posY), 0.f);
			v.texCoord.Set(u1 + width, v1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(static_cast<float>(posX  + ScaleX), static_cast<float>(posY + ScaleY), 0.f);
			v.texCoord.Set(u1 + width, v1 + height);
			vertex_buffer_data.push_back(v);

			v.pos.Set(static_cast<float>(posX), static_cast<float>(posY + ScaleY), 0.f);
			v.texCoord.Set(u1, v1 + height);
			vertex_buffer_data.push_back(v);

			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 3);
			offset += 4;
		}
	}

	SpriteAnimation *anim = new SpriteAnimation(meshName, numRow, numCol);

	glBindBuffer(GL_ARRAY_BUFFER, anim->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, anim->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	anim->indexSize = index_buffer_data.size();
	anim->mode = Mesh::DRAW_TRIANGLES;

	return anim;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad for a minimap; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object
\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad
\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateMinimap(const std::string &meshName, Color color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	// Draw the quad which contains the minimap's texture
	v.pos.Set(-0.5f * length, -0.5f * length, 0);
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length, -0.5f * length, 0);
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(1.0f, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length, 0.5f * length, 0);
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(1.0f, 1.0f);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * length, 0.5f * length, 0);
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(0, 1.0f);
	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0);

	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;
	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the borders for a minimap; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object
\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad
\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateMinimapBorder(const std::string &meshName, Color color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	// Draw the border of the minimap
	// Draw the quad which contains the minimap's texture
	v.pos.Set(-0.5f * length, -0.5f * length, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * length, 0.5f * length, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length, 0.5f * length, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length, -0.5f * length, 0);
	v.color = color;
	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;
	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the avatar for a minimap; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object
\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad
\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateMinimapAvatar(const std::string &meshName, Color color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	// Draw the quad which contains the minimap's texture
	v.pos.Set(-0.05f * length, -0.10f * length, 0);
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.05f * length, -0.10f * length, 0);
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(1.0f, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, 0.15f * length, 0);
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(1.0f, 1.0f);
	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	
	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;
	return mesh;
}