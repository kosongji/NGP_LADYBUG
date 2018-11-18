#pragma once


namespace CS
{
	struct Sync
	{
		PLAYER_OBJ_POS*		players;
		ITEM_OBJ_POS*		items;
		BUG_OBJ_POS*		bugs;
		Sync(
			PLAYER_OBJ_POS*	player = nullptr,
			ITEM_OBJ_POS*	item = nullptr,
			BUG_OBJ_POS*	bug = nullptr
		)
			: players(player), items(item), bugs(bug)
		{
		}
	};



	class ObjectManager
	{
	public:
		ObjectManager( Sync* sync );
		~ObjectManager();
		
		// 패킷을 수정함 재 디자인함.
		inline PLAYER_OBJ_POS*	GetPlayers( );
		inline ITEM_OBJ_POS*	Getitems( );
		inline BUG_OBJ_POS*		GetBugs( );

		inline void SetPlayers(char*);
		inline void SetItems(char*);
		inline void SetBugs(char*);

	private: 
		PLAYER_OBJ_POS*		m_Players;
		ITEM_OBJ_POS*		m_Items;
		BUG_OBJ_POS*		m_Bugs;
	};

}