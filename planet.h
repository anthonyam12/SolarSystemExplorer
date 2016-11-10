#include "global.h"


class Planet 
{
	public:
		Planet( float r, float d, float y, float da, string n );
		Planet();

		// Getters
		float GetRadius();
		float GetDistance();
		float GetYear();
		float GetDay();
		string GetName();

		// Setters
		void SetRadius( float r );
		void SetDistance( float d );
		void SetYear( float y );
		void SetDay( float d );
		void SetName( string n );
	private:
		float radius;
		float distance;
		float year;
		float day;
		string name;
};
