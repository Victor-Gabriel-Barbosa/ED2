#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct SizeData {
    vector<int> preference_list;
    unordered_map<int, int> rank_map;
    vector<int> current_matches;
};

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        int per_size_capacity = N / 6;
        vector<pair<string, string>> volunteers_prefs(M);
        for (int i = 0; i < M; ++i) {
            cin >> volunteers_prefs[i].first >> volunteers_prefs[i].second;
        }

        vector<string> sizes = {"XXL", "XL", "L", "M", "S", "XS"};
        unordered_map<string, SizeData> size_data;
        for (const auto& s : sizes) {
            vector<int> list1, list2;
            for (int v = 0; v < M; ++v) {
                if (volunteers_prefs[v].first == s) {
                    list1.push_back(v);
                } else if (volunteers_prefs[v].second == s) {
                    list2.push_back(v);
                }
            }
            SizeData sd;
            sd.preference_list = list1;
            sd.preference_list.insert(sd.preference_list.end(), list2.begin(), list2.end());
            for (int i = 0; i < sd.preference_list.size(); ++i) {
                sd.rank_map[sd.preference_list[i]] = i;
            }
            size_data[s] = sd;
        }

        vector<int> next_proposal(M, 0);
        vector<int> current_match(M, -1);
        queue<int> free_volunteers;
        for (int i = 0; i < M; ++i) {
            free_volunteers.push(i);
        }

        while (!free_volunteers.empty()) {
            int v = free_volunteers.front();
            free_volunteers.pop();

            if (next_proposal[v] >= 2) continue;

            string s = (next_proposal[v] == 0) ? volunteers_prefs[v].first : volunteers_prefs[v].second;
            SizeData& sd = size_data[s];

            if (sd.current_matches.size() < per_size_capacity) {
                sd.current_matches.push_back(v);
                current_match[v] = 1;
            } else {
                int worst_volunteer = -1, max_rank = -1;
                for (int ev : sd.current_matches) {
                    int r = sd.rank_map[ev];
                    if (r > max_rank) {
                        max_rank = r;
                        worst_volunteer = ev;
                    }
                }
                int vr = sd.rank_map[v];
                if (vr < max_rank) {
                    sd.current_matches.erase(remove(sd.current_matches.begin(), sd.current_matches.end(), worst_volunteer), sd.current_matches.end());
                    sd.current_matches.push_back(v);
                    current_match[v] = 1;
                    if (current_match[worst_volunteer] != -1) {
                        current_match[worst_volunteer] = -1;
                        free_volunteers.push(worst_volunteer);
                    }
                } else {
                    free_volunteers.push(v);
                }
            }
            next_proposal[v]++;
        }

        bool possible = all_of(current_match.begin(), current_match.end(), [](int x) { return x != -1; });
        cout << (possible ? "YES" : "NO") << endl;
    }
    return 0;
}
