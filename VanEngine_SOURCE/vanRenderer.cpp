#include "vanRenderer.h"
#include "vanApplication.h"
#include "vanResourceManager.h"

extern van::Application application;



namespace van::renderer
{

	D3D11_INPUT_ELEMENT_DESC InputLayouts[2];
	Mesh* meshStar = nullptr;
	Mesh* meshDeathBlock = nullptr;
	Mesh* meshCircle = nullptr;
	Mesh* meshRectangle = nullptr;
	Mesh* meshTriangle = nullptr;
	Mesh* meshTriangleR = nullptr;
	Mesh* meshTriangleL = nullptr;
	Mesh* meshColRectangle = nullptr;
	Mesh* meshColCircle = nullptr;
	Shader* shaderPlayer = nullptr;
	Shader* shaderCollider = nullptr;
	Shader* shaderFloor = nullptr;
	ConstantBuffer* constantBuffers[(UINT)graphics::eCBType::End];

	void SetUpStates()
	{

	}

	void LoadBuffer()
	{
		// star
		{
			std::vector<Vertex> vertexes;
			vertexes.resize(6);

			vertexes[0].pos = Vector3(0.f, 0.f, 0.f);
			vertexes[0].color = Vector4(1.f, 1.f, 0.f, 1.f);
			for (int i = 0; i < 5; i++)
			{
				vertexes[i + 1].pos = Vector3(cos(Radian(18.f + (72 * i))), sin(Radian(18.f + (72 * i))), 0.f);
				vertexes[i + 1].color = Vector4(1.f, 1.f, 0.f, 1.f);
			}

			std::vector<UINT> indexes;
			indexes.push_back(0);
			indexes.push_back(3);
			indexes.push_back(1);

			indexes.push_back(0);
			indexes.push_back(5);
			indexes.push_back(3);

			indexes.push_back(0);
			indexes.push_back(4);
			indexes.push_back(2);

			indexes.push_back(0);
			indexes.push_back(1);
			indexes.push_back(4);

			indexes.push_back(0);
			indexes.push_back(5);
			indexes.push_back(3);

			indexes.push_back(0);
			indexes.push_back(2);
			indexes.push_back(5);

			// star vertex buffer
			meshStar->CreateVertexBuffer(vertexes.data(), 6);
			meshStar->CreateIndexBuffer(indexes.data(), indexes.size());
			ResourceManager::Insert(L"StarMesh", meshStar);
		}

		// Spike
		{
			std::vector<Vertex> vertexes;
			vertexes.resize(9);

			vertexes[0].pos = Vector3(-0.6f, -0.3f, 0.f);
			vertexes[0].color = Vector4(0.f, 0.f, 0.f, 1.f);

			vertexes[1].pos = Vector3(-0.4f, 0.2f, 0.f);
			vertexes[1].color = Vector4(0.f, 0.f, 0.f, 1.f);

			vertexes[2].pos = Vector3(-0.2f, -0.3f, 0.f);
			vertexes[2].color = Vector4(0.f, 0.f, 0.f, 1.f);

			vertexes[3].pos = Vector3(0.f, 0.2f, 0.f);
			vertexes[3].color = Vector4(0.f, 0.f, 0.f, 1.f);

			vertexes[4].pos = Vector3(0.2f, -0.3f, 0.f);
			vertexes[4].color = Vector4(0.f, 0.f, 0.f, 1.f);

			vertexes[5].pos = Vector3(0.4f, 0.2f, 0.f);
			vertexes[5].color = Vector4(0.f, 0.f, 0.f, 1.f);

			vertexes[6].pos = Vector3(0.6f, -0.3f, 0.f);
			vertexes[6].color = Vector4(0.f, 0.f, 0.f, 1.f);

			vertexes[7].pos = Vector3(0.6f, -0.6f, 0.f);
			vertexes[7].color = Vector4(0.f, 0.f, 0.f, 1.f);

			vertexes[8].pos = Vector3(-0.6f, -0.6f, 0.f);
			vertexes[8].color = Vector4(0.f, 0.f, 0.f, 1.f);

			std::vector<UINT> indexes;
			indexes.push_back(0);
			indexes.push_back(1);
			indexes.push_back(2);
			indexes.push_back(0);
			indexes.push_back(2);

			indexes.push_back(3);
			indexes.push_back(4);
			indexes.push_back(2);
			indexes.push_back(3);

			indexes.push_back(4);
			indexes.push_back(5);
			indexes.push_back(6);
			indexes.push_back(4);

			indexes.push_back(6);
			indexes.push_back(7);
			indexes.push_back(0);
			indexes.push_back(6);
			indexes.push_back(0);

			indexes.push_back(7);
			indexes.push_back(8);
			indexes.push_back(0);

			indexes.push_back(6);
			indexes.push_back(7);
			indexes.push_back(0);

			// Rectangle Vertex Buffer
			meshDeathBlock->CreateVertexBuffer(vertexes.data(), 9);						// 수정
			meshDeathBlock->CreateIndexBuffer(indexes.data(), indexes.size());
			// 사각형 Mesh 생성후 삽입
			ResourceManager::Insert(L"DeathBlockMesh", meshDeathBlock);
		}

		// Circle
		{
			std::vector<Vertex> vertexes;
			vertexes.resize(362);

			float r = 0.5f; // 반지름

			for (int i = 0; i < 361; i++)
			{
				vertexes[i + 1].pos = Vector3(r * cos(Radian(i)) * 9 / 16 /*화면비*/, r * sin(Radian(i)), 0.f);
				vertexes[i + 1].color = Vector4(0.5f, 0.f, 1.f, 1.f);
			}

			std::vector<UINT> indexes;
			for (int i = 0; i <= 360 - 1; i++)
			{
				indexes.push_back(0);
				indexes.push_back(i + 2);
				indexes.push_back(i + 1);
			}

			// Circle Vertex Buffer
			meshCircle->CreateVertexBuffer(vertexes.data(), 362);						// 수정
			meshCircle->CreateIndexBuffer(indexes.data(), indexes.size());
			// 원 Mesh 생성후 삽입
			ResourceManager::Insert(L"CircleMesh", meshCircle);
		}

		// Rectangle
		{
			std::vector<Vertex> vertexes;
			vertexes.resize(4);

			vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.f);
			vertexes[0].color = Vector4(0.f, 0.f, 0.f, 1.f);

			vertexes[1].pos = Vector3(0.5f, 0.5f, 0.f);
			vertexes[1].color = Vector4(0.f, 0.f, 0.f, 1.f);

			vertexes[2].pos = Vector3(0.5f, -0.5f, 0.f);
			vertexes[2].color = Vector4(0.f, 0.f, 0.f, 1.f);

			vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.f);
			vertexes[3].color = Vector4(0.f, 0.f, 0.f, 1.f);

			std::vector<UINT> indexes;
			indexes.push_back(0);
			indexes.push_back(1);
			indexes.push_back(2);
			
			indexes.push_back(0);
			indexes.push_back(2);
			indexes.push_back(3);

			// Rectangle Vertex Buffer
			meshRectangle->CreateVertexBuffer(vertexes.data(), 4);						// 수정
			meshRectangle->CreateIndexBuffer(indexes.data(), indexes.size());
			// 사각형 Mesh 생성후 삽입
			ResourceManager::Insert(L"RectangleMesh", meshRectangle);
		}

		// Triangle
		{
			std::vector<Vertex> vertexes;
			vertexes.resize(3);

			vertexes[0].pos = Vector3(-0.5f, -0.5f, 0.f);
			vertexes[0].color = Vector4(0.f, 0.f, 0.f, 1.f);

			vertexes[1].pos = Vector3(0.0f, 0.5f * 9 / 16, 0.0f);
			vertexes[1].color = Vector4(0.f, 0.f, 0.f, 1.f);

			vertexes[2].pos = Vector3(0.5f, -0.5f, 0.f);
			vertexes[2].color = Vector4(0.f, 0.f, 0.f, 1.f);

			std::vector<UINT> indexes;
			indexes.push_back(0);
			indexes.push_back(1);
			indexes.push_back(2);

			indexes.push_back(0);
			indexes.push_back(2);
			indexes.push_back(3);

			// Triangle Vertex Buffer
			meshTriangle->CreateVertexBuffer(vertexes.data(), 3);						// 수정
			meshTriangle->CreateIndexBuffer(indexes.data(), indexes.size());
			// 삼각형 Mesh 생성후 삽입
			ResourceManager::Insert(L"TriangleMesh", meshTriangle);
		}

		// Triangle_Right
		{
			std::vector<Vertex> vertexes;
			vertexes.resize(3);

			vertexes[0].pos = Vector3(-0.5f, -0.5f, 0.f);
			vertexes[0].color = Vector4(0.f, 0.f, 0.f, 1.f);

			vertexes[1].pos = Vector3(-0.5f, 0.5f, 0.0f);
			vertexes[1].color = Vector4(0.f, 0.f, 0.f, 1.f);

			vertexes[2].pos = Vector3(0.5f, 0.0f,  0.f);
			vertexes[2].color = Vector4(0.f, 0.f, 0.f, 1.f);

			std::vector<UINT> indexes;
			indexes.push_back(0);
			indexes.push_back(2);
			indexes.push_back(3);

			indexes.push_back(0);
			indexes.push_back(1);
			indexes.push_back(2);


			// Triangle Vertex Buffer
			meshTriangleR->CreateVertexBuffer(vertexes.data(), 3);						// 수정
			meshTriangleR->CreateIndexBuffer(indexes.data(), indexes.size());
			// 삼각형 Mesh 생성후 삽입
			ResourceManager::Insert(L"TriangleMeshR", meshTriangleR);
		}

		// Triangle_Left
		{
			std::vector<Vertex> vertexes;
			vertexes.resize(3);

			vertexes[0].pos = Vector3(0.5f, 0.5f, 0.f);
			vertexes[0].color = Vector4(0.f, 0.f, 0.f, 1.f);

			vertexes[1].pos = Vector3(0.5f, -0.5f, 0.0f);
			vertexes[1].color = Vector4(0.f, 0.f, 0.f, 1.f);

			vertexes[2].pos = Vector3(-0.5f, 0.0f, 0.f);
			vertexes[2].color = Vector4(0.f, 0.f, 0.f, 1.f);

			std::vector<UINT> indexes;
			indexes.push_back(0);
			indexes.push_back(1);
			indexes.push_back(2);

			indexes.push_back(0);
			indexes.push_back(2);
			indexes.push_back(3);

			// Triangle Vertex Buffer
			meshTriangleL->CreateVertexBuffer(vertexes.data(), 3);						// 수정
			meshTriangleL->CreateIndexBuffer(indexes.data(), indexes.size());
			// 삼각형 Mesh 생성후 삽입
			ResourceManager::Insert(L"TriangleMeshL", meshTriangleL);
		}

		// Collider Rectangle
		{
			std::vector<Vertex> vertexes;
			vertexes.resize(4);

			vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.f);
			vertexes[0].color = Vector4(1.f, 0.f, 0.f, 1.f);
			vertexes[1].pos = Vector3(0.5f, 0.5f, 0.f);
			vertexes[1].color = Vector4(1.f, 0.f, 0.f, 1.f);
			vertexes[2].pos = Vector3(0.5f, -0.5f, 0.f);
			vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
			vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.f);
			vertexes[3].color = Vector4(1.f, 0.f, 0.f, 1.f);

			std::vector<UINT> indexes;
			indexes.push_back(0);
			indexes.push_back(1);
			
			indexes.push_back(0);
			indexes.push_back(3);
			
			indexes.push_back(3);
			indexes.push_back(2);

			indexes.push_back(2);
			indexes.push_back(1);

			// Collider Vertex Buffer
			meshColRectangle->CreateVertexBuffer(vertexes.data(), 4);						// 수정
			meshColRectangle->CreateIndexBuffer(indexes.data(), indexes.size());
			// 사각형 Mesh 생성후 삽입
			ResourceManager::Insert(L"RectangleColliderMesh", meshColRectangle);
		}

		// Collider Circle
		{
			std::vector<Vertex> vertexes;
			vertexes.resize(362);

			float r = 0.5f; // 반지름

			for (int i = 0; i < 361; i++)
			{
				vertexes[i + 1].pos = Vector3(r * cos(Radian(i)) * 9 / 16 /*화면비*/, r * sin(Radian(i)), 0.f);
				vertexes[i + 1].color = Vector4(1.f, 0.f, 0.f, 1.f);
			}

			std::vector<UINT> indexes;
			for (int i = 0; i <= 360 - 2; i++)
			{
				indexes.push_back(i + 1);
			}
				indexes.push_back(1); // 원점

			// Circle Vertex Buffer
			meshColCircle->CreateVertexBuffer(vertexes.data(), 362);						// 수정
			meshColCircle->CreateIndexBuffer(indexes.data(), indexes.size());
			// 원 Mesh 생성후 삽입
			ResourceManager::Insert(L"CircleColliderMesh", meshColCircle);
		}

		constantBuffers[(UINT)graphics::eCBType::Transform] = new ConstantBuffer();
		constantBuffers[(UINT)graphics::eCBType::Transform]->Create(sizeof(TransformCB));
		//mesh->CreateConstantBuffer(nullptr, sizeof(Vector4));
	}

	void LoadShader()
	{
		// player
		shaderPlayer->Create(eShaderStage::VS, L"TriangleVS.hlsl", "VS_Player");
		shaderPlayer->Create(eShaderStage::PS, L"TrianglePS.hlsl", "PS_Test");
		ResourceManager::Insert(L"PlayerShader", shaderPlayer);

		// floor
		shaderFloor->Create(eShaderStage::VS, L"TriangleVS.hlsl", "VS_Test");
		shaderFloor->Create(eShaderStage::PS, L"TrianglePS.hlsl", "PS_Test");
		ResourceManager::Insert(L"FloorShader", shaderFloor);

		// collider
		shaderCollider->Create(eShaderStage::VS, L"TriangleVS.hlsl", "VS_Test");
		shaderCollider->Create(eShaderStage::PS, L"TrianglePS.hlsl", "PS_Test");
		ResourceManager::Insert(L"TriangleColShader", shaderCollider);
		//GetDevice()->CreateShader(eShaderStage::NONE);
		//GetDevice()->CreateVertexShader();
		
		// Input layout 정점 구조 정보
		InputLayouts[0].AlignedByteOffset = 0;
		InputLayouts[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		InputLayouts[0].InputSlot = 0;
		InputLayouts[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		InputLayouts[0].SemanticName = "POSITION";
		InputLayouts[0].SemanticIndex = 0;

		InputLayouts[1].AlignedByteOffset = 12;
		InputLayouts[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		InputLayouts[1].InputSlot = 0;
		InputLayouts[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		InputLayouts[1].SemanticName = "COLOR";
		InputLayouts[1].SemanticIndex = 0;

		// Player
		GetDevice()->CreateInputLayout(InputLayouts, 2,
			shaderPlayer->GetVSCode()->GetBufferPointer()
			, shaderPlayer->GetVSCode()->GetBufferSize()
			, shaderPlayer->GetInputLayoutAddressOf());

		// Floor
		GetDevice()->CreateInputLayout(InputLayouts, 2,
			shaderFloor->GetVSCode()->GetBufferPointer()
			, shaderFloor->GetVSCode()->GetBufferSize()
			, shaderFloor->GetInputLayoutAddressOf());

		// Collider
		GetDevice()->CreateInputLayout(InputLayouts, 2,
			shaderCollider->GetVSCode()->GetBufferPointer()
			, shaderCollider->GetVSCode()->GetBufferSize()
			, shaderCollider->GetInputLayoutAddressOf());
	}

	void Initialize()
	{
		meshStar = new Mesh();
		meshDeathBlock = new Mesh();
		meshCircle = new Mesh();
		meshRectangle = new Mesh();
		meshTriangle = new Mesh();
		meshTriangleR = new Mesh();
		meshTriangleL = new Mesh();
		meshColRectangle = new Mesh();
		meshColCircle = new Mesh();
		shaderPlayer = new Shader();
		shaderCollider = new Shader();
		shaderFloor = new Shader();

		LoadShader();
		SetUpStates();
		LoadBuffer();
	}

	void Release()
	{
		delete meshStar;
		delete meshDeathBlock;
		delete meshCircle;
		delete meshRectangle;
		delete meshColRectangle;
		delete shaderPlayer;

		delete constantBuffers[(UINT)graphics::eCBType::Transform];
		//triangleVertexBuffer->Release();
		//errorBlob->Release();
		//triangleVSBlob->Release();
		//triangleVSShader->Release();
		//trianglePSBlob->Release();
		//trianglePSShader->Release();
		//triangleLayout->Release();
	}
}