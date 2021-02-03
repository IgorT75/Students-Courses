#include <cstdio>
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_map>

using namespace std;

// https://leetcode.com/discuss/interview-question/647667/Roblox-Karat-Interview
map<pair<string, string>, vector<string>> getPairs(vector<pair<string, string>>& v) {
	unordered_map<string, set<string>> m;
	for (auto& p : v)
		m[p.first].insert(p.second);

	vector<string> uniques;
	std::transform(m.begin(), m.end(), std::back_inserter(uniques), [](auto& item) { return item.first; });

	map<pair<string, string>, vector<string>> ret;
	for (size_t i = 0; i < uniques.size(); ++i) {
		for (size_t j = i + 1; j < uniques.size(); ++j) {
			const auto& s1 = uniques[i];
			const auto& s2 = uniques[j];

			vector<string> common;
			auto it = std::set_intersection(m[s1].begin(), m[s1].end(), m[s2].begin(), m[s2].end(), std::back_inserter(common));
			ret[std::make_pair(s1, s2)] = common;
		}
	}
	return ret;
}

int main()
{
	vector<pair<string, string>> students {
		{ "58", "Linear Algebra" },
		{ "94", "Art History" },
		{ "94", "Operating Systems" },
		{ "17", "Software Design" },
		{ "58", "Mechanics" },
		{ "58", "Economics" },
		{ "17", "Linear Algebra" },
		{ "17", "Political Science" },
		{ "94", "Economics" },
		{ "25", "Economics" },
		{ "58", "Software Design" }
	};

	map<pair<string, string>, vector<string>> pairs = getPairs(students);
	for (auto& p : pairs) {
		printf("[%s, %s] --> %zu: ", p.first.first.c_str(), p.first.second.c_str(), p.second.size());
		std::for_each(p.second.begin(), p.second.end(), [](string& s) { printf("'%s', ", s.c_str()); });
		printf("\n");
	}

	return 0;
}
