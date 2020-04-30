#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <utility>

class Helpers {
public:
	template<typename T> static T choose(std::vector<T> &vec) {
		return vec[rand() % vec.size()];
	}
	template<typename T> static T choose(std::vector<T> &&vec) {
		return Helpers::choose(vec);
	}
	template<typename T> static std::pair<std::string, T> choose(std::map<std::string, T> &map) {
		int pos = rand() % map.size();
		auto lt = map.begin();
		for (int i = 0; i != pos; ++i, ++lt) {}
		return *lt;
	}
	template<typename T> static std::pair<std::string, T> choose(std::map<std::string, T> &&map) {
		return Helpers::choose(map);
	}
};

#endif
