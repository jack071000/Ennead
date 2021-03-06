#include "PrevHeader.h"
#include "E_Mummy.h"


E_Mummy::E_Mummy()
{
	m_Name = (L"Mummy");
}


E_Mummy::~E_Mummy()
{
}

E_Mummy * E_Mummy::Create(Vector2 pos)
{
	auto mummy = new (std::nothrow) E_Mummy();
	if (mummy && mummy->Init(pos))
	{
		
		return mummy;
	}
	SAFE_DELETE(mummy);
	return nullptr;
}

void E_Mummy::Release()
{
	GameObject::Release();
}

bool E_Mummy::Init(Vector2 pos)
{
	mummy = Animation::Create(10);
	mummy->AddFrame(L"Resources/Enemy/E_Mummy.png");
	Enemy::Init(pos, mummy, EnemyName::Mummy);

	AddChild(mummy);

	return true;
}

void E_Mummy::Update(float deltaTime)
{
	Enemy::Update(deltaTime);
}

void E_Mummy::Render()
{
	GameObject::Render();
}

void E_Mummy::OnCollision(GameObject * other)
{
	m_Health -= 1;
}

void E_Mummy::Move()
{
	SetPosition(0.f, 3.f);
}

void E_Mummy::Attack()
{
}
