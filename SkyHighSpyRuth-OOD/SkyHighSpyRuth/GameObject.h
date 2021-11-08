#pragma once

class GameObject
{
public:

    enum Type
    {
        OBJ_NONE = -1,
        OBJ_AGENT8 = 0,
        OBJ_ASTEROID,
        OBJ_ATTACHED,
        OBJ_METEOR,
        OBJ_GEM,
        OBJ_PIECES,
        OBJ_PARTICLES,
        OBJ_UI,
    };

    //Constructors and Destructor
    GameObject();
    GameObject( Point2f pos );
    virtual ~GameObject();

    //Pure Virtual Functions
    virtual void Update( GameState& state ) = 0;
    virtual void Draw( GameState& state ) = 0;

    void LeavingArea();
    void WrapMovement(int width, int height);
    bool IsColliding(GameObject* other);

    //Inherited Getters and Setters
    void SetPosition( Point2f pos ) { m_pos = pos; }
    Point2f GetPosition() const { return m_pos; };

    Point2f GetOldPosition() const { return m_oldPos; };

    void SetVelocity( Vector2f vel ) { m_velocity = vel; }
    Vector2f GetVelocity() const { return m_velocity; };

    void SetRotation(int rot) { m_rotation = rot; };
    int GetRotation() const { return m_rotation; };

    void SetDrawOrder( int drawOrder ) { m_drawOrder = drawOrder; }
    int GetDrawOrder() const { return m_drawOrder; };

    void SetUpdateOrder( int updateOrder ) { m_updateOrder = updateOrder; }
    int GetUpdateOrder() const { return m_updateOrder; };

    int GetId() const { return m_id; };
    void SetInactive() { m_active = { false }; };
    void SetType(GameObject::Type eType) { m_type = eType; };
    int GetRadius() const { return m_radius; };

    //Static methods = general methods, not called on specific objects
    static int GetObjectCount( Type eType );
    static int GetObjectList( GameObject::Type eType, std::vector< GameObject* >& vList );
    static GameObject* GetObjectOfType(GameObject::Type eType);

    static void UpdateAll( GameState& state );
    static void DrawAll( GameState& state );
    static void DestroyAll();

protected:
    //For sorting
    static bool DrawOrder( const GameObject* a, const GameObject* b ) { return a->m_drawOrder > b->m_drawOrder; }
    static bool UpdateOrder( const GameObject* a, const GameObject* b ) { return a->m_updateOrder > b->m_updateOrder; }

    //Inherited variables
    Type m_type{ OBJ_NONE };
    bool m_active{ true };
    Point2f m_pos{ 0, 0 };
    Point2f m_oldPos{ 0,0 };
    Vector2f m_velocity{ 0, 0 };
    int m_speed{ 0 };
    float m_rotation{ 0 };
    float m_rotSpeed{ 0 };
    float m_animSpeed{ 0 };
    float m_framePos{ 0 };
    int m_frame{ 0 };
    int m_radius{ 0 };
    int m_id{ 0 };
    int m_spriteId{ -1 };

    int m_drawOrder{ 0 };
    int m_updateOrder{ 0 };

    static int counter;

    static std::vector< GameObject* > s_vUpdateList;
    static std::vector< GameObject* > s_vDrawList;

};

