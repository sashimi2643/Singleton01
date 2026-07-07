#include <iostream>

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

int main()
{
	GameManager::Instance().StartGame();

}