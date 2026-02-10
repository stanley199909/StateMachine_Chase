#pragma once
#include <string>
#include <iostream>
#include <functional>
#include <map>

// ステート構造体
// 各ステートのEnter/Update/Exit動作を登録しておく
struct State
{
    std::function<void()> onEnter;          // ステートに入る
    std::function<void(float)> onUpdate;    // ステート中の処理
    std::function<void()> onExit;           // ステートを抜ける
    std::string name;                       // ステート名
};

// ステートマシンクラス
class StateMachine
{
protected:
    std::map<std::string, State> stateList; // 登録された全ステート
    State* currentState = nullptr;          // 現在のステート

public:
    StateMachine() = default;
    virtual ~StateMachine() = default;

    // ステートを追加する
    void AddState(
        const std::string& name,
        std::function<void()> enterFunc,
        std::function<void(float)> updateFunc,
        std::function<void()> exitFunc);
 

    // ステートを切り替える
    void ChangeState(const std::string& name);

    // ステートを更新する
    void Update(float dt);

    // 現在のステート名を取得
    std::string GetCurrentStateName() const;
};