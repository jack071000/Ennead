#pragma once
enum class PlayerClass
{
	Warrior = 1,
	Thief,
	Archer,
	Magician
};

enum class PlayerDirection
{
	Up = 1,
	Down,
	Left,
	Right
};

enum class PlayerState
{
	Idle = 1,
	Move,
	Attack,
};

class Player : public GameObject
{
private:
	int m_Health;
	int m_Speed;
	bool checkInput;

	Sprite* player;

	Animation* Straight;
	Animation* Left;
	Animation* Right;

public:
	//BoxCollider* m_Collision;

	Player();
	~Player();

	PlayerClass Job;
	PlayerDirection pDirection;
	PlayerState pState;

	void SetAnimWithClass(PlayerClass job);


	bool Init();
	void Update(float deltaTime);
	void Render();
	void Release();

	void OnCollision(GameObject* other);

public:
	void Move(); //�̵�
	void Attack(); //�Ѿ� �߻�

};
