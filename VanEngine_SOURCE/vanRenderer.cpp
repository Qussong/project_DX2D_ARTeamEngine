#include "vanRenderer.h"
#include "vanApplication.h"
#include "vanResources.h"

extern van::Application application;



namespace van::renderer
{

	D3D11_INPUT_ELEMENT_DESC InputLayouts[2];
	Mesh* mesh = nullptr;
	Mesh* mesh2 = nullptr;
	Shader* shader = nullptr;
	ConstantBuffer* constantBuffers[(UINT)graphics::eCBType::End];

	void SetUpStates()
	{

	}

	void LoadBuffer()
	{
		// Circle
		{
			std::vector<Vertex> vertexes;
			vertexes.resize(362);

			float r = 0.5f; // 반지름

			for (int i = 0; i < 361; i++)
			{
				vertexes[i + 1].pos = Vector3(r * cos(Radian(i)) * 9 / 16 /*화면비*/, r * sin(Radian(i)), 0.f);
				vertexes[i + 1].color = Vector4(0.f, 0.f, 1.f, 1.f);
			}

			std::vector<UINT> indexes;
			for (int i = 0; i <= 360 - 1; i++)
			{
				indexes.push_back(0);
				indexes.push_back(i + 2);
				indexes.push_back(i + 1);
			}

			// Circle Vertex Buffer
			mesh->CreateVertexBuffer(vertexes.data(), 362);						// 수정
			mesh->CreateIndexBuffer(indexes.data(), indexes.size());
			// 원 Mesh 생성후 삽입
			Resources::Insert(L"CircleMesh", mesh);
		}

		// Rectangle
		{
			std::vector<Vertex> vertexes;
			vertexes.resize(4);

			vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.f);
			vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
			vertexes[1].pos = Vector3(0.5f, 0.5f, 0.f);
			vertexes[1].color = Vector4(1.f, 0.f, 0.f, 1.f);
			vertexes[2].pos = Vector3(0.5f, -0.5f, 0.f);
			vertexes[2].color = Vector4(0.f, 0.f, 1.f, 1.f);
			vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.f);
			vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);

			std::vector<UINT> indexes;
			indexes.push_back(0);
			indexes.push_back(1);
			indexes.push_back(2);
			
			indexes.push_back(0);
			indexes.push_back(2);
			indexes.push_back(3);

			// Rectangle Vertex Buffer
			mesh2->CreateVertexBuffer(vertexes.data(), 4);						// 수정
			mesh2->CreateIndexBuffer(indexes.data(), indexes.size());
			// 사각형 Mesh 생성후 삽입
			Resources::Insert(L"RectangleMesh", mesh2);
		}

		constantBuffers[(UINT)graphics::eCBType::Transform] = new ConstantBuffer();
		constantBuffers[(UINT)graphics::eCBType::Transform]->Create(sizeof(TransformCB));
		//mesh->CreateConstantBuffer(nullptr, sizeof(Vector4));
	}

	void LoadShader()
	{
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "VS_Test");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "PS_Test");
		Resources::Insert(L"TriangleShader", shader);
		//GetDevice()->CreateShader(eShaderStage::NONE);
		//GetDevice()->CreateVertexShader();`
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

		GetDevice()->CreateInputLayout(InputLayouts, 2,
			shader->GetVSCode()->GetBufferPointer()
			, shader->GetVSCode()->GetBufferSize()
			, shader->GetInputLayoutAddressOf());
	}

	void Initialize()
	{
		mesh = new Mesh();
		mesh2 = new Mesh();
		shader = new Shader();

		LoadShader();
		SetUpStates();
		LoadBuffer();
	}

	void Release()
	{
		delete mesh;
		delete mesh2;
		delete shader;

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