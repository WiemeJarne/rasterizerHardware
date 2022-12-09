#pragma once
#include "pch.h"

class Effect final
{
public:
	Effect(ID3D11Device* pDevice, const std::wstring& filePath);
	~Effect();

	Effect(const Effect& other) = delete;
	Effect(Effect&& other) = delete;
	Effect& operator=(const Effect& other) = delete;
	Effect& operator=(Effect&& other) = delete;

private:
	ID3DX11Effect* m_pEffect;
	ID3DX11EffectTechnique* m_pTechnique;

	static ID3DX11Effect* LoadEffect(ID3D11Device* pDevice, const std::wstring& filePath);
};

