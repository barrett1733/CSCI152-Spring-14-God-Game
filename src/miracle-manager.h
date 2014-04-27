/******************************
 *
 * Miracle Manager
 *		Takes input data and returns an Entity:Miracle
 */
 #include <map>
 #include <string>
 
 #include "entity.cpp"
 #include "config.cpp"
 
typedef std::map<EntityType, std::int> MiracleMap;

//miracle manager. go between for player and map
class MiracleManager : config
{
	private:
		MiracleMap miracleList;
		bool setProperty(std::string property, int value);
		
	public:
		MiracleManager( std::string file ); // constructor
		int getCost( EntityType et );
		Entity* createMiracle( EntityType et , Position p );
}
// this will convert a string into an EntityType.
// 	only works for Miracle types. may expand later.
EntityType string_to_ET(std::string name);