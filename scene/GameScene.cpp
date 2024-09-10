#include "GameScene.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// コンストラクタ
GameScene::GameScene() :
    wealth(100),
    fame(100),
    power(100),
    monthsInPower(0),
    isGameOver(false)
{
    // イベントリストの初期化
    events = {
        { "国民が税金を下げることを求めています", -10, +5, -5 },
        { "隣国が同盟を求めています", +10, -10, +5 },
        { "農民が作物の援助を求めています", -20, +15, -10 },
        { "軍事力を増強する提案があります", -15, -5, +20 }
    };

    // ランダムシードの初期化
    srand(static_cast<unsigned int>(time(nullptr)));
}

// デストラクタ
GameScene::~GameScene() {}

// 初期化処理
void GameScene::Initialize() {
    
    dxCommon_ = DirectXCommon::GetInstance();
	audio_ = Audio::GetInstance();
    input_ = Input::GetInstance();
	textureManager_ = TextureManager::GetInstance();

    wealth = 100;
    fame = 100;
    power = 100;
    monthsInPower = 0;
    isGameOver = false;

    kingTexture = TextureManager::Load("king.png");
	backScreen = TextureManager::Load("kita.png");

    king_=Sprite::Create(kingTexture, {640.0f, 360.0f});
	back_ = Sprite::Create(backScreen, {1280.0f, 720.0f});


}

// 毎フレーム呼ばれる更新関数
void GameScene::Update() {
    if (isGameOver) {
        return;
    }

    monthsInPower++;

    // ランダムにイベントを選択
    Event currentEvent = GetRandomEvent();

    // イベントを表示し、プレイヤーに選択を促す
    std::cout << currentEvent.description << std::endl;
    std::cout << "1: 応じる  2: 応じない" << std::endl;

    // プレイヤーの選択を取得
    bool accept = GetPlayerChoice();

    // 選択に基づいてイベントを処理
    HandleEvent(currentEvent, accept);

    // ゲームオーバー判定
    CheckGameOver();
}


// イベント処理
void GameScene::HandleEvent(Event event, bool accept) {
    if (accept) {
        wealth += event.wealthChange;
        fame += event.fameChange;
        power += event.powerChange;
    } else {
        wealth -= event.wealthChange / 2;
        fame -= event.fameChange / 2;
        power -= event.powerChange / 2;
    }
}

// ランダムにイベントを取得
Event GameScene::GetRandomEvent() const {
    int randomIndex = rand() % events.size();
    return events[randomIndex];
}

// プレイヤーの入力を取得（簡易的な例）
bool GameScene::GetPlayerChoice() {
    int choice;
    std::cin >> choice;
    return (choice == 1);
}

// ゲームオーバー判定
void GameScene::CheckGameOver() {
    if (wealth <= 0 || fame <= 0 || power <= 0) {
        isGameOver = true;
    }
}

// ゲームオーバー判定を取得
bool GameScene::IsGameOver() const {
    return isGameOver;
}



void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
    
   back_->Draw();
       

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
     king_->Draw();                         // 描画


	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}