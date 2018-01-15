
#include "Shader.hpp"

#include <d3dcompiler.h>

namespace XE::Graphics::D3D11::TestApp {
    Shader::Shader() {}

    Shader::~Shader() {
        this->Shutdown();
    }

    bool Shader::Initialize(ID3D11Device *device, HWND hWnd) {
        LPCWSTR vertexShaderPath = L"src/XE.Graphics.D3D11.TestApp/XE/Graphics/D3D11/TestApp/Color.vs";
        LPCWSTR pixelShaderPath = L"src/XE.Graphics.D3D11.TestApp/XE/Graphics/D3D11/TestApp/Color.ps";

        return this->InitializeShader(device, hWnd, vertexShaderPath, pixelShaderPath);
    }

    void Shader::Shutdown() {
        this->ShutdownShader();
    }

    bool Shader::Render(ID3D11DeviceContext *context, int indexCount, const XE::Math::Matrix4f &world, const XE::Math::Matrix4f &view, const XE::Math::Matrix4f &projection) {
        if (!this->SetShaderParameters(context, world, view, projection)) {
            return false;
        }

        this->RenderShader(context, indexCount);

        return true;
    }

    bool Shader::InitializeShader(ID3D11Device *device, HWND hWnd, LPCWSTR vertexShaderFile, LPCWSTR pixelShaderFile) {
        ID3D10Blob *vertexShaderBlob;
        ID3D10Blob *pixelShaderBlob;
        ID3D10Blob *errorMessage;

        // Compile Vertex Shader
        if (FAILED(D3DCompileFromFile(vertexShaderFile, nullptr, nullptr, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertexShaderBlob, &errorMessage))) {
            if (errorMessage) {
                this->OutputShaderErrorMessage(errorMessage, hWnd, vertexShaderFile);
                errorMessage->Release();
            } else {
                ::MessageBoxW(hWnd, vertexShaderFile, L"Missing Shader File", MB_OK | MB_ICONERROR);
            }

            return false;
        }

        if (FAILED(device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, &vertexShader))) {
            return false;
        }

        // Compile Pixel Shader
        if (FAILED(D3DCompileFromFile(pixelShaderFile, nullptr, nullptr, "ColorPixelShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixelShaderBlob, &errorMessage))) {
            if (errorMessage) {
                this->OutputShaderErrorMessage(errorMessage, hWnd, pixelShaderFile);
                errorMessage->Release();
            } else {
                ::MessageBoxW(hWnd, pixelShaderFile, L"Missing Shader File", MB_OK | MB_ICONERROR);
            }

            return false;
        }

        if (FAILED(device->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, &pixelShader))) {
            return false;
        }
        

        // create the InputLayout class (that specifies the 
        D3D11_INPUT_ELEMENT_DESC positionInputElement;
        D3D11_INPUT_ELEMENT_DESC colorInputElement;

        positionInputElement.SemanticName = "POSITION";
        positionInputElement.SemanticIndex = 0;
        positionInputElement.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        positionInputElement.InputSlot = 0;
        positionInputElement.AlignedByteOffset = 0;
        positionInputElement.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        positionInputElement.InstanceDataStepRate = 0;

        colorInputElement.SemanticName = "COLOR";
        colorInputElement.SemanticIndex = 0;
        colorInputElement.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        colorInputElement.InputSlot = 0;
        colorInputElement.AlignedByteOffset = 0;
        colorInputElement.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        colorInputElement.InstanceDataStepRate = 0;

        const int LAYOUT_COUNT = 2;

        D3D11_INPUT_ELEMENT_DESC polygonLayout[LAYOUT_COUNT] = {
            positionInputElement, colorInputElement
        };

        if (FAILED(device->CreateInputLayout(polygonLayout, LAYOUT_COUNT, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &layout))) {
            return false;
        }

        // release the compiled shader binaries
        vertexShaderBlob->Release();
        vertexShaderBlob = nullptr;

        pixelShaderBlob->Release();
        pixelShaderBlob = nullptr;

        // setup the definition of the dynamic matrix constant buffer that is in the vertex shader
        D3D11_BUFFER_DESC matrixBufferDesc;

        matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
        matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        matrixBufferDesc.MiscFlags = 0;
        matrixBufferDesc.StructureByteStride = 0;

        if (FAILED(device->CreateBuffer(&matrixBufferDesc, nullptr, &matrixBuffer))) {
            return false;
        }

        return true;
    }

    void Shader::ShutdownShader() {
        if (matrixBuffer) {
            matrixBuffer->Release();
            matrixBuffer = nullptr;
        }

        if (layout) {
            layout->Release();
            layout = nullptr;
        }

        if (pixelShader) {
            pixelShader->Release();
            pixelShader = nullptr;
        }

        if (vertexShader) {
            vertexShader->Release();
            vertexShader = nullptr;
        }
    }

    void Shader::OutputShaderErrorMessage(ID3D10Blob *blob, HWND hWnd, LPCWSTR msg) {
    }

    bool Shader::SetShaderParameters(ID3D11DeviceContext *context, const XE::Math::Matrix4f &world, const XE::Math::Matrix4f &view, const XE::Math::Matrix4f &projection) {
        return false;
    }

    void Shader::RenderShader(ID3D11DeviceContext *context, int indexCount) {

    }
}

