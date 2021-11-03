#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"

std::vector< GameObject* > GameObject::s_vUpdateList;
std::vector< GameObject* > GameObject::s_vDrawList;

//Constructors
GameObject::GameObject()
{
	counter++;
	m_id = counter;
	s_vUpdateList.push_back(this);
	s_vDrawList.push_back(this);
}
GameObject::GameObject( Point2f pos )
{
	m_pos = pos;
	counter++;
	m_id = counter;
	s_vUpdateList.push_back( this );
	s_vDrawList.push_back( this );
}

//Destructor
GameObject::~GameObject()
{
	s_vDrawList.erase( std::find( s_vDrawList.begin(), s_vDrawList.end(), this ) );
	s_vUpdateList.erase( std::find( s_vUpdateList.begin(), s_vUpdateList.end(), this ) );
}

void GameObject::WrapMovement()
{
	if (m_pos.x > DISPLAY_WIDTH + 100)
	{
		m_pos.x -= m_oldPos.x;
	}
	if (m_pos.y > DISPLAY_HEIGHT + 100)
	{
		m_pos.y -= m_oldPos.y;
	}
	if (m_pos.x < -100)
	{
		m_pos.x += m_oldPos.x * -1 + DISPLAY_WIDTH;
	}
	if (m_pos.y < -100)
	{
		m_pos.y += m_oldPos.y * -1 + DISPLAY_HEIGHT;
	}
}

void GameObject::UpdateAll( GameState& state )
{
	//Sort from highest update order to lowest
	std::sort( s_vUpdateList.begin(), s_vUpdateList.end(), GameObject::UpdateOrder );

	for( int n = 0; n < s_vUpdateList.size(); n++ )
	{
		//Call individual Update methods unique to each object
		s_vUpdateList[n]->Update( state );
		   
		//If GO inactive, delete pointer at index in vector to free up memory
		if( !s_vUpdateList[n]->m_active )
    		delete s_vUpdateList[n--];
	}
}

void GameObject::DrawAll( GameState& state )
{
	std::sort( s_vDrawList.begin(), s_vDrawList.end(), GameObject::DrawOrder );

	for( int n = 0; n < s_vDrawList.size(); n++ )
		s_vDrawList[n]->Draw( state );
}

//Count objects of specific type
int GameObject::GetObjectCount( GameObject::Type type )
{
	int count = 0;

	for( GameObject* p : s_vUpdateList )
	{
		if( p->m_type == type || type == OBJ_ALL )
			count++;
	}

	return count;
}

//Putting objects of specific type into vector list
int GameObject::GetObjectList( GameObject::Type type, std::vector< GameObject* >& vList )
{
	vList.clear();

	for( GameObject* p : s_vUpdateList )
	{
		if( p->m_type == type || type == OBJ_ALL )
			vList.push_back( p );
	}

	return vList.size();
}

//Finding object of specific type when there is only one
GameObject* GameObject::GetObjectOfType(GameObject::Type type)
{
	for (GameObject* p : s_vUpdateList)
	{
		if (p->m_type == type)
		{
			return p;
		}
	}
}

//Delete pointer in update list to free up memory - completely freeing memory in update list
void GameObject::DestroyAll()
{
	for( int n = 0; n < s_vDrawList.size(); n++ )
		delete s_vUpdateList[n--];
}

