#include "Animation.h"
#include <cmath>
using namespace std;
Animation::Animation()
{
	m_animTime = 0.0f; //リセット
}

void Animation::Update()
{

	if (m_animTime < maxAnimTime)
		m_animTime += frameTime;
}

float Animation::GetAnimTime() const
{
	return m_animTime;
}

float Animation::GetNormalizedTime() const
{
	return m_animTime / maxAnimTime;
}

//上下に揺れるアニメーション（キャラクターやオブジェクトがゆらゆらと浮く動き）
float Animation::GetFloatOffset(float YPos, float speed) const
{
	float getFloatOffset = GetNormalizedTime();
	return sin(getFloatOffset * 2.0f * PI * speed) * YPos;
};

//背景/物体が淡々透明になるアニメーション
float Animation::GetFadeInAlpha() const //1.0fから0.0f、最初は完全黒っぽい/色付け、淡々透明になる
{
	return 1.0f - GetNormalizedTime();
};

bool Animation::IsAnimationComplete() const //透明が完成したかどうかの判断
{
	return m_animTime >= maxAnimTime;
}

void Animation::Reset() //loopする必要があるアニメーションが使う
{
	m_animTime = 0.0f;
}

float Animation::GetPopScale(float maxScale, float speed) const //数字が生成し、段々大きくなるアニメーション
{
	float t = GetNormalizedTime();

	return 1.0f + sin(t * PI * speed) * (maxScale - 1.0f);
	/*return 1.0f + sin(t * PI * 0.5f) * (maxScale - 1.0f);*/
}

float Animation::GetShakeOffset(float amplitude, float speed) const
{
	float t = GetNormalizedTime();
	return sin(t * speed * 2.0f * PI) * amplitude * (1.0 - t);
}