#pragma once
#include "pch.h"
#include "Matrix.h"

class Effect final
{
public:
	Effect(ID3D11Device* pDevice, const std::wstring& filePath);
	~Effect();

	Effect(const Effect& other) = delete;
	Effect(Effect&& other) = delete;
	Effect& operator=(const Effect& other) = delete;
	Effect& operator=(Effect&& other) = delete;

	ID3DX11Effect* GetEffect() const { return m_pEffect; };
	ID3DX11EffectTechnique* GetTechnique() const { return m_pTechnique; };
	void SetMatrix(const dae::Matrix& matrix) { m_pMatWorldViewProjVariable->SetMatrix(reinterpret_cast<const float*>(&matrix)); };

private:
	ID3DX11Effect* m_pEffect;
	ID3DX11EffectTechnique* m_pTechnique;
	ID3DX11EffectMatrixVariable* m_pMatWorldViewProjVariable;

	static ID3DX11Effect* LoadEffect(ID3D11Device* pDevice, const std::wstring& filePath);
};