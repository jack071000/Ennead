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
}

bool E_Mummy::Init(Vector2 pos)
{
	Enemy::Init(pos);

	mummy = Sprite::Create(L"Resources/Enemy/E_Mummy.png");
	m_Size = Vector2(296, 296);

	m_Collision = BoxCollider::Create(m_Position, m_Size);

	m_Position = pos;
	m_Tag = Tag::Enemy;
	m_EName = EnemyName::Mummy;

	AddChild(mummy);
	AddChild(m_Collision);

	return true;
}

void E_Mummy::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	m_Collision->SetPosition(m_Position);

	if (m_Health <= 0)
	{
		CollisionMgr::GetInstance()->Destroy(m_Collision);
		Destroy();
	}
	//SetPosition(0.f, 1.f);

}

void E_Mummy::Render()
{
	GameObject::Render();
}

void E_Mummy::OnCollision(GameObject * other)
{
	printf("Mummy collision\n");

	m_Health -= 1;

}