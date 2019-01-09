#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> vi;

class SegmentTree {
private: vi st, A;
		 int n;
		 int left(int p) { return p << 1; }
		 int right(int p) { return (p << 1) + 1; }
		 int mid(int a, int b) { return (a + b) / 2; }

		 void build(int p, int L, int R) {
			 if (L == R)
				 st[p] = L;
			 else {
				 build(left(p), L, mid(L, R));
				 build(right(p), mid(L, R) + 1, R);
				 int p1 = st[left(p)], p2 = st[right(p)];
				 st[p] = (A[p1] <= A[p2]) ? p1 : p2;
			 }
		 }

		 int rmq(int p, int L, int R, int i, int j) {
			 if (i > R || j < L) return -1; // current segment outside query range
			 if (L >= i && R <= j) return st[p];    // inside query range

			 int p1 = rmq(left(p), L, mid(L, R), i, j);
			 int p2 = rmq(right(p), mid(L, R) + 1, R, i, j);

			 if (p1 == -1) return p2;   // if we try to access segment outside query
			 if (p2 == -1) return p1;            // same as above
			 return (A[p1] <= A[p2]) ? p1 : p2;
		 }

		 int update_point(int p, int L, int R, int idx, int new_value) {
			 // this update code is still preliminary, i == j
			 // must be able to update range in the future!
			 int i = idx, j = idx;

			 // if the current interval does not intersect 
			 // the update interval, return this st node value!
			 if (i > R || j < L)
				 return st[p];

			 // if the current interval is included in the update range,
			 // update that st[node]
			 if (L == i && R == j) {
				 A[i] = new_value;
				 return st[p] = L;
			 }

			 int p1, p2;
			 p1 = update_point(left(p), L, mid(L, R), idx, new_value);
			 p2 = update_point(right(p), mid(L, R) + 1, R, idx, new_value);

			 return st[p] = (A[p1] <= A[p2]) ? p1 : p2;
		 }

public:
	SegmentTree(const vi &_A) {
		A = _A; n = (int)A.size();
		st.assign(4 * n, 0);
		build(1, 0, n - 1);
	}

	int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }

	int update_point(int idx, int new_value) {
		return update_point(1, 0, n - 1, idx, new_value);
	}
};

int main() {
	int arr[] = { 18, 17, 13, 19, 15, 11, 20 };         // the original array
	vi A(arr, arr + 7);                      // copy the contents to a vector
	SegmentTree st(A);

	printf("              idx    0, 1, 2, 3, 4,  5, 6\n");
	printf("              A is {18,17,13,19,15, 11,20}\n");
	printf("RMQ(1, 3) = %d\n", st.rmq(1, 3));             // answer = index 2
	printf("RMQ(4, 6) = %d\n", st.rmq(4, 6));             // answer = index 5
	printf("RMQ(3, 4) = %d\n", st.rmq(3, 4));             // answer = index 4
	printf("RMQ(0, 0) = %d\n", st.rmq(0, 0));             // answer = index 0
	printf("RMQ(0, 1) = %d\n", st.rmq(0, 1));             // answer = index 1
	printf("RMQ(0, 6) = %d\n", st.rmq(0, 6));             // answer = index 5

	printf("              idx    0, 1, 2, 3, 4,  5, 6\n");
	printf("Now, modify A into {18,17,13,19,15,100,20}\n");
	st.update_point(5, 100);                    // update A[5] from 11 to 100
	printf("These values do not change\n");
	printf("RMQ(1, 3) = %d\n", st.rmq(1, 3));                            // 2
	printf("RMQ(3, 4) = %d\n", st.rmq(3, 4));                            // 4
	printf("RMQ(0, 0) = %d\n", st.rmq(0, 0));                            // 0
	printf("RMQ(0, 1) = %d\n", st.rmq(0, 1));                            // 1
	printf("These values change\n");
	printf("RMQ(0, 6) = %d\n", st.rmq(0, 6));                         // 5->2
	printf("RMQ(4, 6) = %d\n", st.rmq(4, 6));                         // 5->4
	printf("RMQ(4, 5) = %d\n", st.rmq(4, 5));                         // 5->4

	return 0;
}
