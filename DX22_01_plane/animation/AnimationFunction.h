#pragma once

//アニメーションの流れを管理するコード
//aは始め時間、bは終わり時間、tは現アニメーション何%を表示する時間
inline float Lerp(float a , float b , float t);