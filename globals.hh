#pragma once
#include <unordered_map>

class c_globals {
public:
	bool active = true;

	bool checkme = false;
	bool checkmeextra = false;
};

inline c_globals globals;