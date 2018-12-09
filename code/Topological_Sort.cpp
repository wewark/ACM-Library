void topoDFS(int node, vvi& adj, vb& vis, vi& ret) {
	vis[node] = true;
	for (auto& i : adj[node])
		if (!vis[i])
			topoDFS(i, adj, vis, ret);
	ret.push_back(node);
}

vi topoSort(vvi& adj) {
	int n = adj.size();
	vi ret; // stack
	vb vis(n);

	for (int i = 0; i < n; ++i) {
		if (!vis[i])
			topoDFS(i, adj, vis, ret);
	}
	reverse(all(ret));
	return ret;
}
