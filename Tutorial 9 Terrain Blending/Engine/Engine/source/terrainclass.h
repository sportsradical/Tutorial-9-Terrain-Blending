////////////////////////////////////////////////////////////////////////////////
// Filename: terrainclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TERRAINCLASS_H_
#define _TERRAINCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <stdio.h>
#include <fstream>
#include <DirectXMath.h>
using namespace DirectX;
using namespace std;


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"
#include "terrainshaderclass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: TerrainClass
////////////////////////////////////////////////////////////////////////////////
class TerrainClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
		XMFLOAT4 color;
	};

	struct HeightMapType 
	{ 
		float x, y, z;
		float nx, ny, nz;
		float r, g, b;
		int rIndex, gIndex, bIndex;
	};

	struct VectorType 
	{ 
		float x, y, z;
	};

	struct MaterialGroupType 
	{ 
		int textureIndex1, textureIndex2, alphaIndex;
		int red, green, blue;
		ID3D11Buffer *vertexBuffer, *indexBuffer;
		int vertexCount, indexCount;
		VertexType* vertices;
		unsigned long* indices;
	};

public:
	TerrainClass();
	TerrainClass(const TerrainClass&);
	~TerrainClass();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* heightMapFilename, char* materialsFilename, char* materialMapFilename, char* colorMapFilename);
	void Shutdown();

	bool Render(ID3D11DeviceContext* deviceContext, TerrainShaderClass* shader, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
		XMMATRIX projectionMatrix, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor, XMFLOAT3 lightDirection);

private:
	bool LoadHeightMap(char* filename);
	void NormalizeHeightMap();
	bool CalculateNormals();
	void ShutdownHeightMap();

	bool LoadColorMap(char* filename);

	bool LoadMaterialFile(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename, char* materialMapFilename);
	bool LoadMaterialMap(char* filename);
	bool LoadMaterialBuffers(ID3D11Device* device);
	void ReleaseMaterials();

private:
	int m_terrainWidth, m_terrainHeight;
	HeightMapType* m_heightMap;
	int m_textureCount, m_materialCount;
	TextureClass* m_Textures;
	MaterialGroupType* m_Materials;
};

#endif