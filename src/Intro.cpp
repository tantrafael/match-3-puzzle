#include "Intro.h"

Intro::Intro(std::shared_ptr<King::Engine> engine, std::function<void()> exitCallback)
: State(engine, exitCallback) {
}

Intro::~Intro() {
}

void Intro::Update(const float deltaTime) {
    HandleMouseInput();
    mEngine->Write("Play", 460.0f, 250.0f);
}

void Intro::HandleMouseInput() {
    if (mEngine->GetMouseButtonDown()) {
        mExitCallback();
    }
}
