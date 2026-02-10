#pragma once

#include "StateMachine.h"

//すべてのステーマシンの基底クラス
class StateBase
{

public:
    virtual std::string GetStateName() const = 0; //現ステーの名前

    virtual void OnEntry() {} //ステーに入る
    virtual void OnUpdate(float dt) {} //ステーに更新する
    virtual void OnExit() {} //ステーに出る

    void RegisterState(StateMachine& machine); //ステーのクループ化、ステーの情報をまとめて、ステーションとして使える
};
