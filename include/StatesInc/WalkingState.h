#include <StatesInc/State.h>
#include <MoveStrategyAndInfoInc/MoveInfo.h>

template<typename T>
class WalkingState : public State<T> {
public:
	void enter(T& character) override {};
	void update(T& character, float dt) override;
	virtual std::unique_ptr<State<T>> handleInput(T& entity) = 0;
};

template<typename T>
void WalkingState<T>::update(T& character, float dt)  {
	character.move(dt);
	const MoveInfo& info = character.getLastMoveInfo();
	character.getAnimation().update(info.row, 5, dt, info.faceRight);
}

