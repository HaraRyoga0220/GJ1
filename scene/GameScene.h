#pragma once
#include"Audio.h"
#include <vector>
#include <string>
#include"TextureManager.h"
#include"Sprite.h"
#include"Input.h"
#include"DirectXCommon.h"
#include"Model.h"

// イベントの構造体
struct Event {
    std::string description;
    int wealthChange; //富
    int fameChange;//名声
    int powerChange;//権力
};

class GameScene {
public:
    GameScene();
    ~GameScene();

    // 初期化
    void Initialize();

    // 毎フレーム呼ばれる更新関数
    void Update();

    // 描画処理
    void Draw();

    // ゲームオーバー判定
    bool IsGameOver() const;

private:

    DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	TextureManager* textureManager_;

    // ステータス管理
    int wealth;
    int fame;
    int power;
    int monthsInPower;
    bool isGameOver;

    //画像
	int kingTexture;
	int wealthTexture;
	int fameTexture;
	int powerTexture;
	int gameoverTexture;
	int backScreen;

    Sprite* king_ = nullptr;
	Sprite* back_ = nullptr;
    // イベントリスト
    std::vector<Event> events;

    // イベント処理
    void HandleEvent(Event event, bool accept);

    // ランダムイベントを取得
    Event GetRandomEvent() const;

    // プレイヤーの入力（簡易的な例）
    bool GetPlayerChoice();

    // ゲームオーバー判定関数
    void CheckGameOver();
};
