#include <iostream>
#include <vector>
#include <map>
#include <stack>

using namespace std;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using Adj = map<int, vii>;
using sii = stack<ii>;
using vb = vector<bool>;

Adj adj{};
vi roots{};
auto mx = int{ 0 };
auto mxNode = int{ -1 };
vb isVisited{};

void solve(int v, int root) {
	isVisited = vb(v, false);

	auto st = sii{};
	st.push({ root, 0 });
	isVisited[root - 1] = true;

	while (!st.empty()) {
		auto [t, d] = st.top();
		st.pop();

		auto addedCount = int{ 0 };
		for (const auto& [node, dist] : adj[t]) {
			if (!isVisited[node - 1]) {
				isVisited[node - 1] = true;

				st.push({ node, d + dist });
				addedCount += 1;
			}
		}

		if (0 == addedCount) {
			if (mx < d) {
				mx = d;
				mxNode = t;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int v;
	cin >> v;
	for (int i = 0; i < v; ++i) {
		int node;
		cin >> node;

		int p;
		cin >> p;

		auto count = int{ 0 };
		while (p != -1) {
			int q;
			cin >> q;

			adj[node].push_back({ p, q });
			count += 1;

			cin >> p;
		}

		if (1 == count) {
			roots.push_back(node);
		}
	}

	solve(v, 1);
	solve(v, mxNode);

	cout << mx;

	return 0;
}