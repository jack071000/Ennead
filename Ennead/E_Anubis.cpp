#include "PrevHeader.h"
#include "E_Anubis.h"


E_Anubis::E_Anubis()
	:Frame(0)
	, KeepTime(0)
{
	m_Speed = 1.f;
	m_State = EnemyState::Move;
	m_Direction = EnemyDirection::Left;
}

E_Anubis::~E_Anubis()
{
}

E_Anubis * E_Anubis::Create(Vector2 pos)
{
	auto anubis = new (std::nothrow) E_Anubis();
	if (anubis && anubis->Init(pos))
	{
		return anubis;
	}

	SAFE_DELETE(anubis);
	return nullptr;
}

bool E_Anubis::Init(Vector2 pos)
{
	anubis = Animation::Create(10);
	anubis->AddFrame(L"Resources/Enemy/E_Anubis.png");

	Enemy::Init(pos, anubis, EnemyName::Anubis);
	AddChild(anubis);

	return true;
}

void E_Anubis::Release()
{
	Enemy::Release();
}

void E_Anubis::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	if (Frame / 60  == 2)
	{
		m_State = EnemyState::Attack;
		Frame = 0;
	}

	if(m_State == EnemyState::Move)
		Frame++;
	
}

void E_Anubis::Render()
{
	Enemy::Render();
}

void E_Anubis::OnCollision(GameObject * other)
{
	if (other->GetTag() == Tag::Player)
	{
		EffectFactory::GetInstance()->CreateCollisionEffect(m_Position.x, m_Position.y);
		m_Health -= 1;
	}
}

void E_Anubis::Move()
{
	SetPosition(0.f, 0.1f);
}

void E_Anubis::Attack()
{
	//+90
	radius = 20.f;
	radius = D3DXToRadian(radius);
	++KeepTime;

	if (KeepTime < 60 * 2)
	{
		switch (m_Direction)
		{
		case EnemyDirection::Left:
			if (KeepTime < 60 * 2)
				SetPosition(cos((120)*3.f), sin((120)*3.f));

			break;

		case EnemyDirection::Right:
			if (KeepTime < 60 * 2)
				SetPosition(cos(radius*3.f), sin(radius*3.f));

			break;
		}

	}
	else
	{
		ThrowSpear(Player::GetInstance()->GetPosition(),10.f);
		KeepTime = 0;
	}
}

void E_Anubis::ThrowSpear(Vector2 targetPosition, int throwSpeed)
{
	float angle = GetAngle(m_Position , targetPosition);

	BulletMgr::GetInstance()->CreateRBullet(m_Position + Vector2{ 20.f,30.f } , L"Resources/Bullet.png", Tag::Enemy, -60.f, throwSpeed);
	
	BulletMgr::GetInstance()->CreateRBullet(m_Position + Vector2{ 20.f,30.f }, L"Resources/Bullet.png", Tag::Enemy, -45.f, throwSpeed);
	
	BulletMgr::GetInstance()->CreateBullet(m_Position + Vector2{ 20.f,30.f }, L"Resources/Bullet.png", Tag::Enemy, throwSpeed);

	m_State = EnemyState::Move;
	
	auto direction = (rand() % 2) + 1;

	if (direction == 1)
	{
		m_Direction = EnemyDirection::Right;
	}

	else if(direction == 2)
	{
		m_Direction = EnemyDirection::Left;
	}
}
