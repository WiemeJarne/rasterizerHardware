#include "pch.h"
#include "Effect.h"

Effect::Effect(ID3D11Device* pDevice, const std::wstring& filePath)
{
	m_pEffect = LoadEffect(pDevice, filePath);
	m_pTechnique = m_pEffect->GetTechniqueByName("DefaultTechnique");

	if (!m_pTechnique->IsValid())
	{
		std::wcout << L"Technique not valid\n";
	}
}

Effect::~Effect()
{
	m_pEffect->Release();
}

ID3DX11Effect* Effect::LoadEffect(ID3D11Device* pDevice, const std::wstring& filePath)
{
	ID3D10Blob* pErrorBlob{};
	ID3DX11Effect* pEffect;

	DWORD shaderFlags{ 0 };

#if defined(DEBUG) || defined(_DEBUG)
	shaderFlags |= D3DCOMPILE_DEBUG;
	shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	HRESULT result
	{
		D3DX11CompileEffectFromFile
		(
			filePath.c_str(),
			nullptr,
			nullptr,
			shaderFlags,
			0,
			pDevice,
			&pEffect,
			&pErrorBlob
		)
	};

	if (FAILED(result))
	{
		std::wstringstream stringStream;

		if (pErrorBlob != nullptr)
		{
			const char* pErrors{ static_cast<char*>(pErrorBlob->GetBufferPointer()) };

			for (unsigned int index{}; index < pErrorBlob->GetBufferSize(); ++index)
				stringStream << pErrors[index];

			OutputDebugStringW(stringStream.str().c_str());

			pErrorBlob->Release();
			pErrorBlob = nullptr;

			std::wcout << stringStream.str() << '\n';
		}
		else
		{
			stringStream << "EffectLoader: Failed to CreateEffectFromFile!\nPath: " << filePath << '\n';
			std::wcout << stringStream.str();
			return nullptr;
		}
	}

	return pEffect;
}