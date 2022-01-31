//*****************************************************************************
// DX21　サンプルソース
// ゲームのメインとなる処理を書いていくソースファイル
//*****************************************************************************

#include "game.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************

// 頂点１つあたりを表す構造体
//struct VERTEX_POSTEX {
//	float x, y, z;  // 頂点の位置
//
//	float u, v;  // テクスチャのUV座標
//};

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//#define MAX_SPRITE  2560 //(結構適当)
//// ポリゴン２つで１つの四角形（スプライト）。ポリゴンは３頂点なので、１スプライトは６頂点。
//#define VERTEX_PER_SPRITE  (3*2)
//#define VERTEX_BUFFER_SIZE  (MAX_SPRITE*sizeof(VERTEX_POSTEX)*VERTEX_PER_SPRITE)

// オブジェクトの発生数 (多かったり少なかったりするとエラーが出る)
#define MAX_OBJECT   304

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//ID3D11Buffer* gpVertexBuffer;  // 頂点バッファ用の変数
//ID3D11ShaderResourceView* gpTexture; // テクスチャ用変数

	//ステージ数[ステージ][高さ][左下][右下]
int MapChip[MAP_STAGE][MAP_HEIGHT][MAP_EDGE][MAP_EDGE];
vector<MapPos> StoneMap;

GameObject gObjects[MAX_OBJECT];  // オブジェクト配列

GameObject* NoHeight = gObjects + 300;
GameObject* NoLeftDown = gObjects + 301;
GameObject* NoRightDown = gObjects + 302;
GameObject* tile = gObjects + 303;

GameObject gPlayer1;
GameObject gPlayer2;
GameObject gEnemy;
vector<GameObject> gEnemyVector;
GameObject gBackGround;				//背景
GameObject gGauge;					//ゲージ
GameObject gGauge2;
GameObject gGaugeframe;
GameObject gCursor1;
GameObject gCursor2;
GameObject gFade;
GameObject gKorokoro;
GameObject Effect;
GameObject gPause;
GameObject gCrystal;

GameObject gTutorial;
bool TutoLeft, TutoRight;

GameObject gEffect[4];
bool GoalFast_1 = false;
bool onceFlag;

FADE GameFade;

//GameObjectを追加するときは必ずMAX_OBJECTの数を合わせないとエラーが出るよ！

//*****************************************************************************
// 関数の定義　ここから　↓
//*****************************************************************************

BOOL Game_Initialize()
{
	// ゲーム時間の初期化をし、FPSを60に設定した。
	GameTimer_Initialize(60);
	/* 乱数系列の変更 */
	srand((unsigned)time(NULL));
	
	//BGM再生
	XA_Play(SOUND_LABEL(SOUND_LABEL_BGM_GAME));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_BUTTON));

	// CSVを配列に格納
	ifstream ifs("assets/data.csv");
	for (int l = 0; l < MAP_STAGE; l++) {
		string line;
		int j = 0;
		int k = 0;
		bool end = false; //高さのフラグ （CSVでは-9）
		bool stage = false;	//ステージのフラグ (CSVでは-99)
		while (getline(ifs, line)) {

			vector<string> strvec = split(line, ',');

			for (int i = 0; i < strvec.size(); i++) {
				if (-9 == stoi(strvec.at(i))) {
					end = true;
					break;
				}
				if (-99 == stoi(strvec.at(i))) {
					end = true;
					break;
				}
				MapChip[l][k][j][i] = stoi(strvec.at(i));
			}
			j++;
			if (end == true) {
				k++;
				j = 0;
				end = false;
			}
			if (stage == true) {
				l++;
				j = 0;
				k = 0;
				stage = false;
			}
		}
	}

	turn = PLAYER_TURN;

	// マップ生成
	Map_Initialize(gObjects);

	//エフェクト生成
	for (int i = 0; i < 4; i++) {
		Effect_Init(&gEffect[i]);
	}

	//雪玉の初期化
	Player_Initialize(&gPlayer1);
	Player_Initialize(&gPlayer2);

	////雪玉の場所指定
	Player_SetLocation(&gPlayer1, gObjects, 0, 5, 5);
	Player_SetLocation(&gPlayer2, gObjects, 0, 6, 6);

	//ゲージの初期化
	Gauge_Initialize(&gGauge, &gGauge2);

	//カーソルの初期化
	Cursor_Initialize(&gCursor1);
	Cursor_Initialize(&gCursor2);

	//マップ変更
	Map_Update(gObjects, &StoneMap, MapChip);

	//敵の場所指定
	//敵の場所を指定しておくステージごとに
	switch (Map_GetStage())
	{
	case 0:
		//敵の初期化
		//Enemy_Initialize(&gEnemy, FOLLOWING);
		//Enemy_SetLocation(&gEnemy, gObjects, 0, 0, 6);
		//gEnemyVector.emplace_back(gEnemy);

		//雪玉初期化
		Player_SetLocation(&gPlayer1, gObjects, 0, 0, 6);
		Player_SetLocation(&gPlayer2, gObjects, 0, 0, 7);
		break;

	case 1:
		//敵の初期化
		//Enemy_Initialize(&gEnemy, RANDOM);
		//Enemy_SetLocation(&gEnemy, gObjects, 0, 0, 7);
		//gEnemyVector.emplace_back(gEnemy);

		Player_SetLocation(&gPlayer1, gObjects, 0, 7, 2);
		Player_SetLocation(&gPlayer2, gObjects, 0, 2, 7);
	}

	//背景描画
	gBackGround.texture = new Sprite("assets/GameBG.png", 2, 1);
	gBackGround.texture->SetSize(1280 * 2, 720 * 2);
	gBackGround.posX = -1;
	gBackGround.posY = 1;
	gBackGround.texture->SetPart(1, 0);

	//ゲージのフレーム
	gGaugeframe.texture = new Sprite("assets/gaugeframe.png", 1, 1);
	gGaugeframe.texture->SetSize(232 * 4, 64 * 4);
	gGaugeframe.posX = 0.23f;
	gGaugeframe.posY = -0.65f;

	//デバック用
	NoHeight->texture = new Sprite("assets/dotFont.png", 16, 8);
	NoHeight->texture->SetSize(80, 160);
	NoLeftDown->texture = new Sprite("assets/dotFont.png", 16, 8);
	NoLeftDown->texture->SetSize(80, 160);
	NoRightDown->texture = new Sprite("assets/dotFont.png", 16, 8);
	NoRightDown->texture->SetSize(80, 160);
	tile->texture = new Sprite("assets/Mapseat_v2.png", 7, 1);
	tile->texture->SetSize(200, 200);

	//フェード
	gFade.texture = new Sprite("assets/TitleBG.png", 1, 1);
	gFade.texture->SetSize(1280 * 2, 720 * 2);
	gFade.posX = -1;
	gFade.posY = 1;
	gFade.texture->color.r = 0.0f;
	gFade.texture->color.g = 0.0f;
	gFade.texture->color.b = 0.0f;
	gFade.texture->color.a = 0.0f;
	GameFade.framecnt = FADETIME - 0.1f;
	GameFade.fadeout = false;

	//ころころ
	gKorokoro.texture = new Sprite("assets/fadekorokoro.png", 20, 2);
	gKorokoro.texture->SetSize(1280 * 2, 720 * 2);
	gKorokoro.posX = -1;
	gKorokoro.posY = 1;
	onceFlag = true;

	//ポーズ
	gPause.texture = new Sprite("assets/pause.png", 2, 1);
	gPause.texture->SetSize(1280 * 2, 720 * 2);
	gPause.posX = -1;
	gPause.posY = 1;
	gPause.texture->SetPart(1, 0);

	//ポーズ
	gCrystal.texture = new Sprite("assets/crystal.png", 1, 1);
	gCrystal.texture->SetSize(256, 256);
	gCrystal.posX = -1;
	gCrystal.posY = 1;

	//チュートリアル
	gTutorial.texture = new Sprite("assets/tutorial.png", 4, 1);
	gTutorial.texture->SetPart(0, 0);
	gTutorial.texture->SetSize(1280 * 2, 720 * 2);

	Effect.texture = new Sprite("assets/yukiEffect.png", 12, 2);
	Effect.texture->SetPart(0, 0);
	Effect.posX = 10;
	Effect.texture->SetSize(INIT_SNOW_SIZE, INIT_SNOW_SIZE);

	//チュートリアル
	if (stage == 1) {
		gTutorial.posX = -1;
		gTutorial.posY = 1;
		turn = TUTORIAL;
	}
	else {
		gTutorial.posX = -10;
		gTutorial.posY = 10;
	}
	pause = gGAME;

	return TRUE;
}

// ゲームループ中に実行したい、ゲームの処理を書く関数
BOOL Game_Update()
{
	Input_Update();  // このゲームで使うキーの押下状態を調べて保
	XINPUT_STATE state;
	XInputGetState(0, &state);

	//デバック用
	NoHeight->texture->SetPart(gPlayer1.mappos.Height, 0);
	NoHeight->posX = 0.5f;
	NoHeight->posY = 0.5f;
	NoLeftDown->texture->SetPart(gPlayer1.mappos.LeftDown, 1);
	NoLeftDown->posX = 0.6f;
	NoLeftDown->posY = 0.5f;
	NoRightDown->texture->SetPart(gPlayer1.mappos.RightDown, 2);
	NoRightDown->posX = 0.7f;
	NoRightDown->posY = 0.5f;
	tile->texture->SetPart(Map_GetPlayerTile(&gPlayer1, gObjects), 0);
	tile->posX = 0.3;
	tile->posY = 0.6;
	gBackGround.posX = -1;
	gBackGround.posY = 1;
	gCursor1.texture->SetPart(1, 0);
	switch (pause)
	{
	case gGAME:
		gPause.posX = 5.0f;
		gCrystal.posX = 5.0f;
		for (int i = 0; i < 4; i++) {
			Efffect_Move(&gEffect[i]);
		}

		//アニメーション
		//敵アニメーション
		for (int i = 0; i < gEnemyVector.size(); i++)
			Enemy_Update(&gEnemyVector[i], &gPlayer1);

		if (gPlayer1.Goalfrg == false)
			Player_AniUpdate(&gPlayer1);
		if (gPlayer2.Goalfrg == false)
			Player_AniUpdate(&gPlayer2);

		//ゴールの状態変化
		Goal_Update(&gPlayer1, &gPlayer2, &Effect);

		//カーソルの位置変更
		Cursor_Update(&gPlayer1, &gCursor1);
		Cursor_Update(&gPlayer2, &gCursor2);


		if (Input_GetKeyTrigger(VK_UP)) {
			pause = gPAUSE;
		}

		switch (turn)
		{
		case PLAYER_TURN:
			//プレイヤー移動
			gPlayer1.animator.isActive = true;
			gPlayer2.animator.isActive = true;
			Player_Input(&gPlayer1, &gPlayer2);
			Player_Update(&gPlayer1, gObjects);
			Player_Update(&gPlayer2, gObjects);
			Big_SnowBall(&gPlayer1, &gPlayer2);
			Gauge_Update(&gGauge, &gGauge2, &gPlayer1, &gPlayer2);
			if (gPlayer1.animator.isActive == false || gPlayer2.animator.isActive == false)
				turn = ENEMY_TURN;
			break;

		case ENEMY_TURN:
		{
			bool end = false;
			//敵移動
			for (int i = 0; i < gEnemyVector.size(); i++) {
				if (gEnemyVector[i].direction == NULL_WAY && gEnemyVector[i].animator.oneAni == false) {
					//敵の接近
					if (gEnemyVector[i].direction == NULL_WAY) {
						//敵のタイプに合わせて行動変化
						switch (gEnemyVector[i].enemytype) {
						case RANDOM:	//ランダム移動
							Enemy_Move_Random(&gEnemyVector[i]);
							break;

						case FOLLOWING:	//範囲以内を索敵追尾
							Enemy_Move_Chase(&gEnemyVector[i], &gPlayer1, &gPlayer2);
							break;

						case CIRCUMFRENCE:
							//Enemy_Move_Circle(&gEnemyVector[i]);
							break;
						}
					}
					end = true;
				}
				else {
					//敵の移動処理
					MapMove_Update(&gEnemyVector[i], gObjects);
					if (gEnemyVector[i].animator.isActive != false) {
						end = true;
						gEnemyVector[i].animator.oneAni = true;
					}
				}
				//敵のスタン
				Enemy_Stun(&gEnemyVector[i], &gPlayer1, &gPlayer2, gObjects);
				if (gEnemyVector[i].IsStun == Stun || gEnemyVector[i].IsStun == Stun_Release)
					end = false;
			}
			if (end == false) {
				turn = ENV_TURN;
				for (int i = 0; i < gEnemyVector.size(); i++) {
					gEnemyVector[i].animator.oneAni = false;
					if (gEnemyVector[i].IsStun == Stun_) {
						gEnemyVector[i].IsStun = Nothing;
						gEnemyVector[i].direction = NULL_WAY;
					}
					if (gEnemyVector[i].IsStun == Stun)
						gEnemyVector[i].IsStun = Stun_;
					if (gEnemyVector[i].IsStun == Stun_Release)
						gEnemyVector[i].IsStun = Stun;
				}
			}
		}
		break;

		case ENV_TURN:
			//マップを状態に合わせて変更する
			MapUpdate(gObjects, &gPlayer1, &gPlayer2);
			for (int i = 0; i < gEnemyVector.size(); i++)
				Enemy_Player_Hit(&gEnemyVector[i], &gPlayer1, &gPlayer2);
			//どちらの雪玉が早いか
			if (gPlayer1.Goalfrg == true && gPlayer2.Goalfrg == false)
				GoalFast_1 = true;
			//クリア
			if (gPlayer1.Goalfrg == true && gPlayer2.Goalfrg == true)
				turn = CLEAR;
			break;

		case PENGUIN_ATTACK:
			for (int i = 0; i < gEnemyVector.size(); i++) {
				Enemy_Move_Frg(&gEnemyVector[i], &gPlayer1);
				Enemy_Move_Frg(&gEnemyVector[i], &gPlayer2);
				if (gEnemyVector[i].Enemycount < 50) {
					if (gEnemyVector[i].EnemyAttak == true) {
						gEnemyVector[i].posY += 0.2f / 50;
						gEnemyVector[i].Enemycount++;
					}
				}
				else {
					if (gEnemyVector[i].EnemyAttak == true) {
						gEnemyVector[i].animator.isActive = true;
						Enemy_GameOver_Move(&gEnemyVector[i]);
						if (gEnemyVector[i].animator.isActive == false || gEnemyVector[i].direction == NULL_WAY) {
							gEnemyVector[i].Enemycount = 0;
							turn = PENGUIN2;
						}
					}
				}
			}
			break;
		case PENGUIN2:
			for (int i = 0; i < gEnemyVector.size(); i++) {
				Enemy_Move_Frg(&gEnemyVector[i], &gPlayer1);
				Enemy_Move_Frg(&gEnemyVector[i], &gPlayer2);
				if (gEnemyVector[i].Enemycount < 10) {
					gEnemyVector[i].posY -= 0.2f / 10;
					gEnemyVector[i].Enemycount++;
				}
				else {
					turn = GAMEOVER;
				}
			}
			break;

		case GAMEOVER:
			//タイトルへ戻るフラグ
			if (Input_GetKeyTrigger(VK_SPACE) || Input_GetControllerTrigger(XINPUT_GAMEPAD_B))
				return FALSE;

			GameFade.fadeout = true;
			break;

		case CLEAR:
			if (Input_GetKeyTrigger(VK_SPACE) || Input_GetControllerTrigger(XINPUT_GAMEPAD_B))
				//return FALSE;

			if (onceFlag == true) {
				korokoroX = 0;
				onceFlag = false;
			}
			GameFade.fadeout = true;
			break;

		case TUTORIAL:

			int page = gTutorial.texture->GetPart();

			if (Input_GetKeyTrigger(VK_LEFT) || Input_GetControllerTrigger(XINPUT_GAMEPAD_DPAD_LEFT)) {
				page--;
				if (page == -1)
					page = 0;
				TutoLeft = false;
			}

			if (Input_GetKeyTrigger(VK_RIGHT) || Input_GetControllerTrigger(XINPUT_GAMEPAD_DPAD_RIGHT)) {
				page++;
				if (page == 4)
					page = 3;
				TutoRight = false;
			}

			if (Input_GetKeyTrigger(VK_RETURN) || Input_GetControllerTrigger(XINPUT_GAMEPAD_B)) {
				turn = PLAYER_TURN;
				gTutorial.posX = -10;
				gTutorial.posY = 10;
			}



			gTutorial.texture->SetPart(page, 0);
			break;
		}

		break;
		case gPAUSE:
			gPause.posX = -1.0f;
			gCrystal.posX = -0.5f;
			if (Input_GetKeyTrigger(VK_LEFT)) {
				pauseChoice -= 1;
				if (pauseChoice < 0)
					pauseChoice = 2;
			}
			if (Input_GetKeyTrigger(VK_RIGHT)) {
				pauseChoice += 1;
				if (pauseChoice > 2)
					pauseChoice = 0;
			}
			switch (pauseChoice)
			{
			case 0:
				gCrystal.posY = 0.3f;

				if (Input_GetKeyTrigger(VK_RETURN)) {
					pause=gGAME;
				}
				break;
			case 1:
				gCrystal.posY = 0.0f;
				if (Input_GetKeyTrigger(VK_RETURN)) {
					pauseChoice = gRESPAWN;
					if (onceFlag == true) {
						korokoroX = 0;
						onceFlag = false;
					}
					GameFade.fadeout = true;
				}
				break;
			case 2:
				gCrystal.posY = -0.3f;
				if (Input_GetKeyTrigger(VK_RETURN)) {
					pauseChoice = gLEVEL;
					if (onceFlag == true) {
						korokoroX = 0;
						onceFlag = false;
					}
					GameFade.fadeout = true;
				}
				break;
			}
			
		

	}
	

	//if (gEnemy.enemyeye == ENEMYEYE_IN)
	//{
	//	//遮蔽でのヘイトそらし
	//	for (int i = 0; i < StoneMap.size(); i++) {
	//		Shield_Cancel(&StoneMap[i], &gPlayer1, &gPlayer2, &gEnemy);
	//	}
	//}

	// オブジェクト配列のXY計算、UV計算、頂点配列への適用を一括処理
	//GameObjectと画像の座標を合わせる
	gKorokoro.texture->SetPart(korokoroX / 4, 0);
	korokoroX++;
	FadeChange(&GameFade);//フェード関連全てを司ってます触らないで
	gFade.texture->color.a = GameFade.Alpha;
	if (GameFade.Alpha > 1.0f)
		return FALSE;
	for (int i = 0; i < MAX_OBJECT; i++) {
		GameObject_DrowUpdate(&gObjects[i]);
	}
	for (int i = 0; i < MAX_OBJECT; i++) {
		GameObject_DrowUpdate(&gObjects[i]);
	}
	GameObject_DrowUpdate(&gPlayer1);
	GameObject_DrowUpdate(&gPlayer2);
	GameObject_DrowUpdate(&gGauge);
	GameObject_DrowUpdate(&gGauge2);
	GameObject_DrowUpdate(&gCursor1);
	GameObject_DrowUpdate(&gCursor2);
	GameObject_DrowUpdate(&gGaugeframe);
	GameObject_DrowUpdate(&gFade);
	GameObject_DrowUpdate(&gPause);
	GameObject_DrowUpdate(&gCrystal);
	for (int i = 0; i < gEnemyVector.size(); i++)
		GameObject_DrowUpdate(&gEnemyVector[i]);
	GameObject_DrowUpdate(&gBackGround);
	for (int i = 0; i < 4; i++) {
		GameObject_DrowUpdate(&gEffect[i]);
	}
	GameObject_DrowUpdate(&gTutorial);
	GameObject_DrowUpdate(&gKorokoro);
	GameObject_DrowUpdate(&Effect);
	return TRUE;
}

void Game_Draw()
{
	// 画面クリア（指定色で塗りつぶし）
	// 塗りつぶし色の指定（小数：0.0f～1.0f）
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
	Direct3D_GetContext()->ClearRenderTargetView(Direct3D_GetRenderTargetView(), clearColor);

	//ゲームオブジェクトを全部描画する
	gBackGround.texture->Draw();
	gEffect[0].texture->Draw();
	gEffect[1].texture->Draw();
	for (int i = 0; i < MAX_OBJECT; i++)
		gObjects[i].texture->Draw();
	if (turn != GAMEOVER || turn != PENGUIN2) {
		for (int i = 0; i < gEnemyVector.size(); i++)
			gEnemyVector[i].texture->Draw();
	}
	if (gPlayer1.Goalfrg == false)
		gPlayer1.texture->Draw();
	if (gPlayer2.Goalfrg == false)
		gPlayer2.texture->Draw();
	if (turn == GAMEOVER || turn == PENGUIN2) {
		for (int i = 0; i < gEnemyVector.size(); i++)
			gEnemyVector[i].texture->Draw();
	}
	if (gPlayer1.Goalfrg == true)
		gPlayer1.texture->Draw();
	if (gPlayer2.Goalfrg == true)
		gPlayer2.texture->Draw();
	gGauge.texture->Draw();
	gGauge2.texture->Draw();
	gCursor1.texture->Draw();
	gCursor2.texture->Draw();
	gGaugeframe.texture->Draw();
	gEffect[2].texture->Draw();
	gEffect[3].texture->Draw();
	Effect.texture->Draw();
	gPause.texture->Draw();
	gCrystal.texture->Draw();
	gFade.texture->Draw();
	gTutorial.texture->Draw();
	gKorokoro.texture->Draw();
	// ダブル・バッファのディスプレイ領域へのコピー命令
	Direct3D_GetSwapChain()->Present(0, 0);
}

//作ったGameObjectはちゃんとdeleteしよう！
StageScore Game_Relese()
{
	XA_Stop(SOUND_LABEL(SOUND_LABEL_BGM_GAME));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_BUTTON));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_SNOWHUNDA));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_PLAYERGROW));
	XA_Stop(SOUND_LABEL(SOUND_LABEL_SE_MOVE));

	delete gPlayer1.texture;
	delete gPlayer2.texture;
	delete gGauge.texture;
	delete gGauge2.texture;
	delete gCursor1.texture;
	delete gCursor2.texture;
	delete gGaugeframe.texture;
	delete gFade.texture;
	delete gKorokoro.texture;
	delete gPause.texture;
	delete gCrystal.texture;
	for (int i = 0; i < gEnemyVector.size(); i++)
		delete gEnemyVector[i].texture;
	gEnemyVector.clear();
	delete gBackGround.texture;
	for (int i = 0; i < 4; i++)
		delete gEffect[i].texture;
	for (int i = 0; i < MAX_OBJECT; i++) {
		delete gObjects[i].texture;
		gObjects[i].posX = 0;
		gObjects[i].posY = 0;
	}
	delete gTutorial.texture;
	delete Effect.texture;

	//ステージスコアを返す
	StageScore score;
	bool Balance = false;
	bool Face = false;
	bool Arm = false;

	//クリアしているか
	if (turn == CLEAR) {
		//バランスはどうか
		if (GoalFast_1 == true) {
			if (gPlayer1.SnowSize > gPlayer2.SnowSize) {
				Balance = true;
			}
		}
		else {
			if (gPlayer1.SnowSize < gPlayer2.SnowSize) {
				Balance = true;
			}
		}
		//アイテムは獲得してるか
		if (gPlayer1.Item_Face == true || gPlayer2.Item_Face == true)
			Face = true;
		if (gPlayer1.Item_Arm == true || gPlayer2.Item_Arm == true)
			Arm = true;
	}
	else {	//失敗
		score = ZERO;
	}

	//それぞれのクリアごとに分ける
	if (Balance == false && Face == false && Arm == false)
		score = STAGE_CLEAR;
	if (Balance == true && Face == false && Arm == false)
		score = BALANCE_CLEAR;
	if (Balance == false && Face == true && Arm == false)
		score = FACE_CLEAR;
	if (Balance == false && Face == false && Arm == true)
		score = ARM_CLEAR;
	if (Balance == true && Face == true && Arm == false)
		score = BALA_FACE_CLEAR;
	if (Balance == false && Face == true && Arm == true)
		score = FACE_ARM_CLEAR;
	if (Balance == true && Face == false && Arm == true)
		score = ARM_BALA_CLEAR;
	if (Balance == true && Face == true && Arm == true)
		score = ALL_CLEAR;

	return score;
}
