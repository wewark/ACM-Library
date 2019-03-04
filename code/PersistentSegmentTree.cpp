struct Node {
	int val = 0;
	Node* left = nullptr;
	Node* right = nullptr;

	Node() = default;
};

const int MAXN = 100;
class PersistentSegmentTree {
	int n;
	vi A;
	vector<Node*> version;

	void build(Node *n, int L, int R) {
		if (L == R) {
			n->val = A[L];
			return;
		}
		int mid = (L + R) / 2;
		n->left = new Node();
		n->right = new Node();
		build(n->left, L, mid);
		build(n->right, mid + 1, R);
		n->val = n->left->val + n->right->val;
	}

	void update(Node *prv, Node *cur, int L, int R, int idx, int val) {
		if (idx > R || idx < L || L > R)
			return;

		if (L == R) {
			cur->val = val;
			return;
		}

		int mid = (L + R) / 2;
		if (idx <= mid) {
			// link to right child of previous version
			cur->right = prv->right;
			// create new node in current version
			cur->left = new Node();
			update(prv->left, cur->left, L, mid, idx, val);
		}
		else {
			cur->left = prv->left;
			cur->right = new Node();
			update(prv->right, cur->right, mid + 1, R, idx, val);
		}

		cur->val = cur->left->val + cur->right->val;
	}

	int query(Node *n, int L, int R, int i, int j) {
		if (i > R || j < L || L > R)
			return 0;
		if (i <= L && R <= j)
			return n->val;
		int mid = (L + R) / 2;
		int p1 = query(n->left, L, mid, i, j);
		int p2 = query(n->right, mid + 1, R, i, j);
		return p1 + p2;
	}

public:
	explicit PersistentSegmentTree(vi& _A) {
		A = _A;
		n = A.size();
		version.push_back(new Node());
		build(version.back(), 0, n - 1);
	}

	void update(int v, int idx, int val) {
		version.push_back(new Node());
		update(version[v], version.back(), 0, n - 1, idx, val);
	}

	int query(int v, int i, int j) {
		return query(version[v], 0, n - 1, i, j);
	}
};


int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr);
#ifndef ONLINE_JUDGE
	 freopen("input.txt", "r", stdin);
#endif

	vi A = {1,2,3,4,5};
	PersistentSegmentTree sgt(A);
	sgt.update(0, 4, 1);
	sgt.update(1, 2, 10);
	cout << sgt.query(1, 0, 4) << endl;
	cout << sgt.query(2, 3, 4) << endl;
	cout << sgt.query(0, 0, 3) << endl;
}
