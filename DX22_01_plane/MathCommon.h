#pragma once
#include "SimpleMath.h"
#include <cmath>
#include <DirectXMath.h>
// 基本型のエイリアス
using Vector4 = DirectX::SimpleMath::Vector4;
using Vector3 = DirectX::SimpleMath::Vector3;
using Vector2 = DirectX::SimpleMath::Vector2;

using Float4 = DirectX::XMFLOAT4;
using Float3 = DirectX::XMFLOAT3;
using Float2 = DirectX::XMFLOAT2;

using Matrix4x4 = DirectX::SimpleMath::Matrix;

using Color = DirectX::SimpleMath::Color;

using Quaternion = DirectX::SimpleMath::Quaternion;


//constexpr float PI = static_cast<float>(3.141592653589793);
constexpr float PI = static_cast<float>(3.141592653589793238462643383279502884197169399375105820974944592307816406286);

