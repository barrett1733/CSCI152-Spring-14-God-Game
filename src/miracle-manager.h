//
//  File: miracle-manager.h
//  Author: Allen Mills
//  CSci 152
//  Spring 2014
//
// Definition of MiracleManager, a class to manage/create miracle entities
//	simply by using clear methods.
//	Includes function 'string_to_ET' to quickly convert a string to an
//	EntityType for miracle entity types.
//

 #ifndef MIRACLE_MANAGER_H_
#define  MIRACLE_MANAGER_H_

 #include <map>
 #include <string>

 #include "entity.h"
 #include "config.h"

typedef std::map<EntityType, int> MiracleMap;

//miracle manager. go between for player and map
class MiracleManager:public Config
{
	private:
		MiracleMap miracleList;
		bool setProperty(std::string property, int value);

	public:
		MiracleManager( std::string file ); // constructor
		int getCost( EntityType et );
		Entity* createMiracle( EntityType et , Position p, Faction f);
};

// this will convert a string into an EntityType.
// 	only works for Miracle types. may expand later.
EntityType string_to_ET(std::string property);

#endif

