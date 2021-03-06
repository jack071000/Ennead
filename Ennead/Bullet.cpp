#include "PrevHeader.h"
#include "Bullet.h"

Bullet::Bullet()
	: m_Speed(5.f)
{	
	IsCollide = 0;
	m_LifeTime = 120;
}

Bullet::~Bullet()
{
}

Bullet * Bullet::Create(Vector2 pos,std::wstring img, Tag tag)
{
	auto bullet = new (std::nothrow) Bullet();
	if (bullet && bullet->Init(pos,img.c_str(), tag))
	{
		return bullet;
	}

	SAFE_DELETE(bullet);
	return nullptr;
}

void Bullet::Release()
{
	GameObject::Release();
}

bool Bullet::Init(Vector2 pos, std::wstring img, Tag tag)
{
	m_Position = pos;
	m_bullet = Sprite::Create(img.c_str());
	m_Tag = tag;
	m_Size = { 50.f,50.f };
	m_Collision = BoxCollider::Create(m_Position, m_Size);

	AddChild(m_Collision);
	AddChild(m_bullet);


	return true;
}

void Bullet::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	m_LifeTime--;

	if (IsCollide || m_LifeTime <= 0)
	{
		CollisionMgr::GetInstance()->Destroy(m_Collision);
		Destroy();
	}

	if (m_Tag == Tag::Player)
	{
		SetPosition(0.f, -5.f);
	}

	if (m_Tag == Tag::Enemy)
	{
		SetPosition(0.f, m_Speed);
	}
}

void Bullet::Render()
{
	GameObject::Render();
}

void Bullet::OnCollision(GameObject * other)
{
	if (other)
	{
		if (other->GetTag() == Tag::Structure)
			return;

		IsCollide = 1;
	}



}
