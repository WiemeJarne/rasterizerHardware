#include "pch.h"
#include "Mesh.h"
#include "Effect.h"
#include <cassert>

namespace dae
{
	Mesh::Mesh(ID3D11Device* pDevice)
		:m_pEffect{ new Effect(pDevice, L"Resources/PosTex.fx") }
	{
		//Create Vertex Layout
		static constexpr uint32_t amountOfElements{ 2 };
		D3D11_INPUT_ELEMENT_DESC vertexDesc[amountOfElements]{};

		vertexDesc[0].SemanticName = "POSITION";
		vertexDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		vertexDesc[0].AlignedByteOffset = 0;
		vertexDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;

		vertexDesc[1].SemanticName = "TEXTCOORD";
		vertexDesc[1].Format = DXGI_FORMAT_R32G32_FLOAT;
		vertexDesc[1].AlignedByteOffset = 12;
		vertexDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;

		//Create Input Layout
		D3DX11_PASS_DESC passDesc{};
		m_pEffect->GetTechnique()->GetPassByIndex(0)->GetDesc(&passDesc);

		HRESULT result
		{
			pDevice->CreateInputLayout
			(
				vertexDesc,
				amountOfElements,
				passDesc.pIAInputSignature,
				passDesc.IAInputSignatureSize,
				&m_pInputLayout
			)
		};

		if (FAILED(result))
			assert("Failed to create input layout\n");

		//Create vertex buffer
		D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_IMMUTABLE;
		bd.ByteWidth = sizeof(Vertex_PosTex) * static_cast<uint32_t>(m_Vertices.size());
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData{};
		initData.pSysMem = m_Vertices.data();

		result = pDevice->CreateBuffer(&bd, &initData, &m_pVertexBuffer);

		if (FAILED(result))
			assert("Failed to create vertex buffer");

		//Create index buffer
		m_AmountOfIndices = static_cast<uint32_t>(m_Indices.size());
		bd.Usage = D3D11_USAGE_IMMUTABLE;
		bd.ByteWidth = sizeof(Vertex_PosTex) * m_AmountOfIndices;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		initData.pSysMem = m_Indices.data();

		result = pDevice->CreateBuffer(&bd, &initData, &m_pIndexBuffer);

		if (FAILED(result))
			assert("Failed to create index buffer");
	}

	Mesh::~Mesh()
	{
		m_pInputLayout->Release();
		m_pVertexBuffer->Release();
		m_pIndexBuffer->Release();

		delete m_pEffect;
	}

	void Mesh::Render(ID3D11DeviceContext* pDeviceContext, const Matrix& worldViewProjectionMatrix) const
	{
		m_pEffect->SetMatrix(worldViewProjectionMatrix);

		//1. Set Primitive Topology
		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//2. Set Input Layout
		pDeviceContext->IASetInputLayout(m_pInputLayout);

		//3. Set VertexBuffer
		constexpr UINT stride{ sizeof(Vertex_PosTex) };
		constexpr UINT offset{ 0 };
		pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

		//4. Set IndexBuffer
		pDeviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		//5. Draw
		D3DX11_TECHNIQUE_DESC techniqueDesc{};
		m_pEffect->GetTechnique()->GetDesc(&techniqueDesc);

		for (UINT index{}; index < techniqueDesc.Passes; ++index)
		{
			m_pEffect->GetTechnique()->GetPassByIndex(index)->Apply(0, pDeviceContext);
			pDeviceContext->DrawIndexed(m_AmountOfIndices, 0, 0);
		}
	}
}