#pragma once
#include "pch.h"

class RasterizerState final
{
public:
	enum class CullMode
	{
		backFace,
		frontFace,
		none
	};

	RasterizerState(ID3D11Device* pDevice, CullMode cullMode);
	~RasterizerState();
	ID3D11RasterizerState* GetRasterizerState() const { return m_pRasterizerState; }
	CullMode GetCullMode() const { return m_CullMode; }

	RasterizerState(const RasterizerState& other) = delete;
	RasterizerState(RasterizerState&& other) = delete;
	RasterizerState& operator=(const RasterizerState& other) = delete;
	RasterizerState& operator=(RasterizerState&& other) = delete;

private:
	ID3D11RasterizerState* m_pRasterizerState{};
	const CullMode m_CullMode{};
};