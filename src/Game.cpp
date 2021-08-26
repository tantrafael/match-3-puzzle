#define GLM_FORCE_RADIANS

#include <map>
#include <string>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Game.h"
#include "Intro.h"
#include "Play.h"
#include "GameOver.h"

static std::map<Game::GameState, Game::GameState> StateFlowChart {
    { Game::STATE_INTRO, Game::STATE_PLAY },
    { Game::STATE_PLAY, Game::STATE_GAME_OVER },
    { Game::STATE_GAME_OVER, Game::STATE_PLAY }
};

Game::Game()
: mEngine(new King::Engine("./bin/assets"))
, mTime(Play::TimeLimit)
, mScore(0) {
}

Game::~Game() {
}

void Game::Start() {
    EnterState(STATE_INTRO);
    mEngine->Start(*this);
}

void Game::RenderBackground() {
    mEngine->Render(King::Engine::TEXTURE_BACKGROUND, 0, 0);
}

void Game::RenderScore() {
    mEngine->Write("Score", 20.0f, 10.0f);

    std::string s = std::to_string(mScore);
    char const *pchar = s.c_str();
    mEngine->Write(pchar, 20.0f, 40.0f);
}

void Game::RenderTime() {
    mEngine->Write("Time", 20.0f, 100.0f);
    
    std::string s = std::to_string(mTime);
    char const *pchar = s.c_str();
    mEngine->Write(pchar, 20.0f, 130.0f);
}

void Game::EnterState(const GameState state) {
    mGameState = state;

    switch (state) {
        case STATE_PLAY:
            mState.reset(new Play(mEngine,
                                  std::bind(&Game::ExitState, this),
                                  std::bind(&Game::SetTime, this, std::placeholders::_1),
                                  std::bind(&Game::SetScore, this, std::placeholders::_1)));
            break;
            
        case STATE_GAME_OVER:
            mState.reset(new GameOver(mEngine, std::bind(&Game::ExitState, this)));
            break;
            
        default:
            mState.reset(new Intro(mEngine, std::bind(&Game::ExitState, this)));
            break;
    }
}

void Game::ExitState() {
    GameState gameState = StateFlowChart[mGameState];
    EnterState(gameState);
}

void Game::SetTime(const int time) {
    mTime = time;
}

void Game::SetScore(const int score) {
    mScore = score;
}
                                  
void Game::Update() {
    float deltaTime = mEngine->GetLastFrameSeconds();

    RenderBackground();
    RenderScore();
    RenderTime();

    if (mState != nullptr) {
        mState->Update(deltaTime);
    }
}
