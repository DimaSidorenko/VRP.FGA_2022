#include "Utils.h"


vector<vector<int>> SplitPaths(vector<int>& path, InputData& input) {
	if (path.empty()) {
		return {};
	}
	path.insert(path.begin(), { 0 });
	int n = static_cast<int>(path.size());

	vector<double> prefLen(n, 0);
	for (int i = 1; i < n; i++) {
		prefLen[i] = prefLen[i - 1] + input.Distance(path[i - 1], path[i]);
	}

	vector<double> dp(n, INF);
	vector<int> prev_dp(n, INF);

	dp[0] = 0;

	for (int v = 0; v + 1 < n; ++v) {
		assert(dp[v] != INF);

		double len = 0;
		for (int u = v + 1; u < n; ++u) {
			// relaxing using edge (v, u)
			len = prefLen[u] - prefLen[v + 1] + input.Distance(0, path[v + 1]) + input.Distance(path[u], 0);
			if (dp[v] + len < dp[u]) {
				dp[u] = dp[v] + len;
				prev_dp[u] = v;
			}
		}
	}

	vector<vector<int>> paths;
	// min() to fix warning
	for (size_t i = n - 1; i != 0; i = prev_dp[min((size_t)n - 1, i)]) {
		paths.push_back({});
		for (int j = (int)i; j > max(-1, prev_dp[i]); --j) {
			paths.back().push_back(path[j]);
		}
		reverse(paths.back().begin(), paths.back().end());
	}

	path.erase(path.begin());


	return paths;
}
