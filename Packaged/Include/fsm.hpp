#ifndef MYFSM_H
#define MYFSM_H
#include<map>
#include<vector>
using std::map;
template<class STATE>
class FSM;
///////////////////////////////////////////////状态接口
template<class STATE>
struct FSMAction{
    using FSM_TYPE=FSM<STATE>;
    using FSMACTION_TYPE=FSMAction<STATE>;
    FSM_TYPE*FSM;
    virtual void Enter()=0;
    virtual void Execute()=0;
    virtual void Exit()=0;
    virtual bool AllowSwitchState(const STATE& state);
    virtual void SwitchState(const STATE& state);
};
///////////////////////////////////////////////
///////////////////////////////////////////////
template<class STATE>
class FSM{
protected:
    FSMAction<STATE>*CurrentEvent;
    STATE CurrentState;
    map<STATE,FSMAction<STATE>*>StateTable;
public:
    FSM();
    void AddState(const STATE&state,FSMAction<STATE>*event);
    void SwitchState(const STATE&state);
    STATE GetCurrentState();
    void ReleaseAllState();
    void Run();
    ~FSM();
};
template<class STATE>
bool FSMAction<STATE>::AllowSwitchState(const STATE& state)
{
    return true;
}
///////////////////////////////////////////////
template<class STATE>
void FSMAction<STATE>::SwitchState(const STATE&state)
{
    FSM->SwitchState(state);
}

template<class STATE>
FSM<STATE>::FSM()
{
    CurrentEvent=0;
}

template<class STATE>
void FSM<STATE>::AddState(const STATE &state, FSMAction<STATE> *event)
{
    if(StateTable.find(state)!=StateTable.end())return;
    event->FSM = this;
    StateTable.insert({state,event});
}

template<class STATE>
void FSM<STATE>::SwitchState(const STATE &state)
{
    /////////////////////////////////////先判断当前状态是否允许切换到目标状态
    if (CurrentEvent&&!CurrentEvent->AllowSwitchState(state))return;
    /////////////////////////////////////
    auto itr=StateTable.find(state);
    if(itr==StateTable.end())return;
    /////////////////////////////////////
    if(CurrentEvent)
        CurrentEvent->Exit();
    CurrentState=state;
    CurrentEvent=itr->second;
    CurrentEvent->Enter();
}

template<class STATE>
STATE FSM<STATE>::GetCurrentState()
{
    return CurrentState;
}

template<class STATE>
void FSM<STATE>::ReleaseAllState()
{
    for (auto& state : StateTable)
        delete state.second;
}

template<class STATE>
void FSM<STATE>::Run()
{
    CurrentEvent->Execute();
}

template<class STATE>
FSM<STATE>::~FSM()
{

}
#endif // FSM_H
