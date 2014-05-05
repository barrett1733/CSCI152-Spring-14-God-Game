/******************************
 * Miracle Manager
 *		Takes input data and returns an Entity:Miracle
 */
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

