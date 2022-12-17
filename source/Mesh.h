#pragma once
class Effect;

namespace dae
{
	class Mesh
	{
	public:
		Mesh(ID3D11Device* pDevice);
		~Mesh();

		void Render(ID3D11DeviceContext* pDeviceContext, const Matrix& worldViewProjectionMatrix) const;
		Matrix GetWorldMatrix() { return m_WorldMatrix; };
		Effect* GetEffectPtr() const { return m_pEffect; };

	private:
		Effect* m_pEffect{};
		ID3D11InputLayout* m_pInputLayout{};
		ID3D11Buffer* m_pVertexBuffer{};
		ID3D11Buffer* m_pIndexBuffer{};

		struct Vertex_PosCol
		{
			Vector3 position;
			ColorRGB color;
		};

		struct Vertex_PosTex
		{
			Vector3 position;
			Vector2 uv;
		};

		std::vector<Vertex_PosTex> m_Vertices
		{
			{{0.5f, 0.5f, 0.f}, {1.f, 0.f}},
			{{-0.5f, -0.5f, 0.f}, {0.f, 1.f}},
			{{-0.5f, 0.5f, 0.f}, {0.f, 0.f}},
			{{0.5f, -0.5f, 0.f}, {1.f, 1.f}}
		};
		std::vector<uint32_t> m_Indices{0, 1, 2, 0, 3, 1};
		uint32_t m_AmountOfIndices{};

		Matrix m_WorldMatrix
		{
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
		};
	};
}