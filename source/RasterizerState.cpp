#include "pch.h"
#include "RasterizerState.h"
#include <cassert>

RasterizerState::RasterizerState(ID3D11Device* pDevice, CullMode cullMode)
	: m_CullMode{ cullMode }
{
	D3D11_RASTERIZER_DESC rasterizerDesc{};

	switch (cullMode)
	{
	case CullMode::backFace:
		rasterizerDesc.CullMode = D3D11_CULL_BACK;
		break;

	case CullMode::frontFace:
		rasterizerDesc.CullMode = D3D11_CULL_FRONT;
		break;

	case CullMode::none:
		rasterizerDesc.CullMode = D3D11_CULL_NONE;
		break;
	}

	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0.f;
	rasterizerDesc.DepthClipEnable = true;
	rasterizerDesc.AntialiasedLineEnable = false;
	rasterizerDesc.MultisampleEnable = false;
	rasterizerDesc.ScissorEnable = false;
	rasterizerDesc.SlopeScaledDepthBias = 0.f;
	rasterizerDesc.FrontCounterClockwise = false;

	HRESULT result{ pDevice->CreateRasterizerState(&rasterizerDesc, &m_pRasterizerState) };

	if (FAILED(result))
		assert("Failed to create rasterizerState");
}

RasterizerState::~RasterizerState()
{
	m_pRasterizerState->Release();
}