#include "graph.h"

using namespace std;
len_matrix create_matrix(size_t n, len_t val=0)
{
	vector<len_t> row(n, val);
	len_matrix res(n, row);
	return res;
}
len_matrix random_matrix(size_t n, len_t from, len_t to, double gap_p)
{
	len_matrix res = create_matrix(n);
	for (int i=0; i<n; i++)
		for (int j = 1 + i; j < n; j++)
		{
			res[i][j] = rand() % (int)(to-from) + from;
			res[j][i] = res[i][j];
		}
	return res;
}
void print_matrix(const len_matrix& m)
{
	for (size_t i=0; i<m.size(); i++)
	{
		for (auto val : m[i])
			cout << val << "\t";
		cout << endl;
	}
}

path_t all_nodes(const len_matrix& m)
{
	path_t p(m.size(), 0);
	for (size_t i = 0; i < m.size(); i++)	
		p[i] = i;
	return p;
}
len_t path_len(const len_matrix &m, const path_t& p)
{
	len_t len = 0;
	for (size_t i = 1; i < p.size(); i++)
		len += m[p[i]][p[i - 1]];
	return len;
}
void print_path(const path_t& p)
{
	if (!p.size())	return;
	cout << p[0];
	for (size_t i = 1; i < p.size(); i++)
		cout << " -> " << p[i];
	cout << endl;
}

path_t explore_brunch(const len_matrix& m, const path_t& available_nodes, size_t cur_node, len_t& len)
{
	path_t res_path;
	len = -1;

	if (!available_nodes.size())
	{
		if (m[cur_node][0] < 0)
			return res_path;

		len = m[cur_node][0];
		res_path.push_back(0);
	}
	else
	{
		for (size_t i = 0; i < available_nodes.size(); i++)
		{
			size_t next_node = available_nodes[i];
			if (m[cur_node][next_node] < 0)
				continue;

			len_t temp_len = -1;
			path_t temp_nodes = available_nodes;
			temp_nodes.erase(temp_nodes.begin() + i);

			path_t temp_path = explore_brunch(m, temp_nodes, next_node, temp_len);
			if (temp_len < 0)
				continue;
			temp_len += m[cur_node][next_node];

			if (len < 0 || len > temp_len)
			{
				res_path = temp_path;
				len = temp_len;
			}
		}
	}

	res_path.push_back(cur_node);
	return res_path;
}
path_t brute_force(const len_matrix& m, len_t& len)
{
	path_t full_p(all_nodes(m));
	full_p.erase(full_p.begin()); // delete 0 node
	len = -1;
	return explore_brunch(m, full_p, 0, len);
}


using ant_t = struct
{
	size_t pos;
	len_t temp_len;
	path_t path;
	path_t avl_nodes;
};
using ant_arr = vector<ant_t>;
void ant_step(ant_t& ant, size_t node, len_t len)
{
	ant.pos = node;
	ant.temp_len += len;
	ant.avl_nodes.erase(find(ant.avl_nodes.begin(), ant.avl_nodes.end(), node));
	ant.avl_nodes.push_back(node);
}
ant_arr init_colony(const len_matrix& m)
{
	size_t len = m.size();
	path_t pos = all_nodes(m);
	random_shuffle(pos.begin(), pos.end());
	
	ant_arr arr(len);
	for (size_t i = 0; i < len; i++)
	{
		arr[i].pos = pos[i];
		arr[i].temp_len = 0;
		arr[i].path.push_back(pos[i]);

		arr[i].avl_nodes = all_nodes(m);
		arr[i].avl_nodes.erase(arr[i].avl_nodes.begin() + pos[i]);
	}
	
	return arr;
}

int get_next_node(const len_matrix& m, const vector<vector<double>>& tau, const ant_t& ant, double a, double b)
{
	size_t cur = ant.pos;
	vector<double> node_p(ant.avl_nodes.size(), 0);
	double sum_p = 0;

	for (size_t j = 0; j < ant.avl_nodes.size(); j++)
	{
		size_t next = ant.avl_nodes[j];
		if (m[cur][next] < 0)
			continue;

		double val = pow(tau[cur][next], a) / pow(m[cur][next], b);
		sum_p += val;
		node_p[j] = sum_p;
	}
	if (sum_p < 1e-9) { cout << "ZERO\n";  return -1; }

	double rand_f = (double)rand() / sum_p / RAND_MAX;
	for (size_t next = 0; next < node_p.size(); next++)
		if (node_p[next] > rand_f)
			return ant.avl_nodes[next];
	return ant.avl_nodes[node_p.size() - 1];
}
int next_step(ant_t& ant, const len_matrix& m, const vector<vector<double>>& tau, double a, double b)
{
	size_t cur = ant.pos;
	int next = get_next_node(m, tau, ant, a, b);
	if (next == -1)	return 0;

	ant.pos = next;
	ant.temp_len += m[cur][next];
	ant.path.push_back(next);
	ant.avl_nodes.erase(find(ant.avl_nodes.begin(), ant.avl_nodes.end(), next));	

	return 1;
}
path_t ant_search(const len_matrix& m, double a, double b, double ro, size_t max_t, len_t q)
{
	vector<vector<double>> tau = create_matrix(m.size(), q/50);

	path_t min_path;
	len_t min_len = -1;

	for (size_t t = 0; t < max_t; t++)
	{
		/*cout << endl << endl << "Time " << t << " min len " << min_len << endl;
		print_matrix(tau);*/

		ant_arr colony = init_colony(m);
		vector<vector<double>> d_tau = create_matrix(m.size(), 0);
		
		for (size_t i = 0; i < colony.size(); i++)
		{
			ant_t& ant = colony[i];
			size_t init_pos = ant.pos;

			while (ant.avl_nodes.size())
				if (!next_step(ant, m, tau, a, b)) 
					break;

			if (ant.avl_nodes.size())
			{ 
				ant.temp_len = -1;
			}
			else
			{
				ant.avl_nodes.push_back(init_pos);
				if (!next_step(ant, m, tau, a, b)) 
					ant.temp_len = -1;
			}
		}

		for (ant_t ant : colony)
		{
			if (ant.temp_len < 0)
				continue;
			// cout << "Scan ant : " << ant.temp_len << endl;
			if (min_len > ant.temp_len || min_len < 0)
			{
				min_len = ant.temp_len;
				min_path = ant.path;
			}

			double inc = ((double)q) / ant.temp_len;
			for (size_t i = 1; i < ant.path.size(); i++)
			{
				d_tau[ant.path[i]][ant.path[i-1]] += inc;
				d_tau[ant.path[i-1]][ant.path[i]] += inc;
			}
		}

		for (size_t i = 0; i < tau.size(); i++)
			for (size_t j = 0; j < tau.size(); j++)
				tau[i][j] = tau[i][j]*(1 - ro) + d_tau[i][j];
	}

	return min_path;
}