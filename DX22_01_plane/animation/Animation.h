#pragma once
#include "AnimationFunction.h"
#define PI 3.14159265f 
class Animation
{
private:
    float m_animTime = 0.0f;        // アニメーションカウンター
  

public:
    static constexpr float frameTime = 1.0f / 60.0f; //60FPS
    static constexpr float maxAnimTime = 1.0f; //m_frameTime変数が多すぎないようにための変数

    Animation();
   
    void Update();   //Update更新
    float GetAnimTime() const;  // 現アニメーション時間を取る
    float GetNormalizedTime() const; //0.0~から1.0の数値を取得する(ゲームの進行度)

    //上下に揺れるアニメーション（キャラクターやオブジェクトがゆらゆらと浮く動き）
    float GetFloatOffset(float YPos = 10.0f, float speed = 1.0f) const;

    //背景/物体が淡々透明になるアニメーション
    float GetFadeInAlpha() const; //1.0fから0.0f、最初は完全黒っぽい/色付け、淡々透明になる
    bool IsAnimationComplete() const; //アニメーションが完成したかどうかの判断
    void Reset(); //loopする必要があるアニメーションが使う

    //数字が生成し、段々大きくなるアニメーション
    float GetPopScale(float maxScale = 1.2f, float speed = 1.0f) const;

    //プレイ画面をシェークする
    float GetShakeOffset(float amplitude = 1.0f, float speed = 20.0f) const;

    
 
};


