#include <iostream>
#include <conio.h>   // _kbhit() と _getch() に必要
#include <windows.h> // Sleep() に必要

class GameManager
{
private:
	/// <summary>
	/// オブジェクトを外部から生成するのを防ぐためのprivateコンストラクタ
	/// </summary>
	GameManager() {}

public:
	/// <summary>
	/// 別のオブジェクトのコピーを禁止するためのコピーコンストラクタ
	/// </summary>
	GameManager(const GameManager&) = delete;
	/// <summary>
	/// 別のオブジェクトのコピーを禁止するためのコピーコンストラクタ
	/// </summary>
	GameManager& operator=(const GameManager&) = delete;

	/// <summary>
	/// スレッドセーフな、GameManagerの唯一のオブジェクトを返すことができる
	/// </summary>
	/// <returns></returns>
	static GameManager& Instance()
	{
		static GameManager instance;
		return instance;
	}

	void StartGame()
	{
		std::cout << "Hello World!\n";
	}
};


enum Game
{
	TITLE,
	PLAY,
	CLEAR,
	GAMEOVER,
	RESULT
};
int mode = TITLE;


class GameTitle
{
private:
	GameTitle() {};

public:
	GameTitle(const GameTitle&) = delete;
	GameTitle& operator=(const GameTitle&) = delete;

	static GameTitle& Instance()
	{
		static GameTitle instance;
		return instance;
	}
	void StartTitle()
	{
		std::cout << "クイズでドン！\n";
		std::cout << "Enterキーを押してね♪\n\n";
	}
};

class GamePlay
{
private:
	GamePlay() {};

public:
	GamePlay(const GamePlay&) = delete;
	GamePlay& operator=(const GamePlay&) = delete;

	static GamePlay& Instance()
	{
		static GamePlay instance;
		return instance;
	}

	void Question()  // 問題
	{
		std::cout << "パンはパンでも食べられないパンはな～んだ？\n";
		std::cout << "1, フランスパン　2, 食パン　3, フライパン\n";
		std::cout << "１～３のキーで答えてね♪\n";
	}

	// キー入力を受け取って判定する（引数でキーを渡す）
	void CheckAnswer(int key)
	{
		switch (key) {
		case '1':
			std::cout << "「1」フランスパン\n";
			std::cout << "不正解だよ～\n";
			std::cout << "正解は～？\n";
			mode = GAMEOVER; // ゲームオーバーへ
			break;
		case '2':
			std::cout << "「2」食パン\n";
			std::cout << "正解は～？\n";
			mode = GAMEOVER; // ゲームオーバーへ
			break;
		case '3':
			std::cout << "「3」フライパン\n";
			std::cout << "正解は～？\n";
			mode = CLEAR; // クリアへ
			break;
		}
	}
};



int main()
{
	GameTitle::Instance().StartTitle();

	// ループ
	while (true)
	{
		int key = _getch(); // 押されたキーを取得

		switch (mode) {
		case TITLE:  // タイトル時の処理
			// Enterキー（13）が押されたらプレイ画面へ遷移
			if (key == 13)
			{
				mode = PLAY;
				system("cls"); // 画面を一度クリア（見やすくするため）
				GamePlay::Instance().Question();
			}
			break;
		case PLAY:  // プレイ
			GamePlay::Instance().CheckAnswer(key);
			break;
		case CLEAR:  // クリア
			std::cout << "正解！\n";
			std::cout << "さすがだね！\n\n";
			std::cout << "Enterキーを押すとタイトルに戻るよ～\n";
			mode = RESULT;
			break;
		case GAMEOVER:  // ゲームオーバー
			std::cout << "不正解だよ～\n\n";
			mode = RESULT;
			break;
		case RESULT:  // 結果
			// Enterキー（13）が押されたらタイトル画面へ遷移
			if (key == 13)
			{
				mode = TITLE;
				system("cls"); // 画面を一度クリア（見やすくするため）
				GameTitle::Instance().StartTitle();
			}
			break;
		}
	}
}