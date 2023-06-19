	#pragma once
#pragma warning(push)
#pragma warning(disable: 4244)

// header file code here


	#include"debug.h"
	using namespace std;
	class Spatial
	{
	protected:
		int _width;
		int	_height;
		int _m;
		int _n;
		int _nearN;
		int _nearM;
		vector<vector<vector<int>>> _indexes;
		void _get_range_n(int n,int&min_n,int&max_n)
		{
			min_n = max(n - _nearN, 0);
			max_n = min(n + _nearN, _n - 1);
		}
		void  _get_range_m(int m, int& min_m, int& max_m)
		{
			min_m= max(m - _nearN, 0);
			max_m = min(m + _nearN, _m - 1);
		}
		void _append(int id, int& n, int& m)
		{
			_indexes[n][m].push_back(id);
		//	DebugOut(L"Moved % d to(% d, % d)\n",id, n, m);
		}
		void _remove(int& id, int& n, int& m)
		{
			_remove(id, _indexes[n][m]);
		}
		virtual void _destroy_spatial()
		{
			_indexes.clear();
		}
		void _remove(int& id, vector<int>& ptr)
		{

			auto it = find(ptr.begin(), ptr.end(), id);
			if (it == ptr.end())
			{
				DebugOut(L"[ERROR] ID %d NOT EXIST \n", id);
			}
			else
			{
				ptr.erase(it);
			}
		}
		unordered_map<int, int> _getNearByID(int n, int m)
		{
			unordered_map<int, int> unquie_id;
			int min_m, min_n,
				max_m, max_n;
			_get_range_n(n, min_n, max_n);
			_get_range_m(m, min_m, max_m);
			for (int i = min_n; i <= max_n; i++)
				for (int j = min_m; j <= max_m; j++)
					for (auto& id : _indexes[i][j])
						unquie_id[id] = 0;
			return unquie_id;

		}
	public:	
		Spatial(int n, int m, int width, int height,int nearN=2,int nearM=2) :_width(width),_height(height), _m(m), _n(n),
																			  _nearM(nearM),_nearN(nearN),
																			  _indexes(n, vector<vector<int>>(m, vector<int>()))
		{
		
			DebugOut(L"Created out Spatial map with(%d,%d)\n", n, m);
		};
		
		vector<int> getNearByID(int n, int m)
		{
			unordered_map<int, int> map= _getNearByID(n, m);
			vector<int> result;

			for (auto& i : map)
			{
				result.push_back(i.first);
			}
			return result;
		}
		vector<int> getNearByIDyx(int y, int x)
		{
			return getNearByID(y / _height, x / _width);
		}

		void init_object(int id, float& left, float& top, float& right, float& bottom)
		{
			int t = min(max(top / _height, 0), _n - 1),
				b=  min(max(bottom/ _height,0),_n-1),
				l= min(max(left/_width,0),_m-1),
				r= min(max(right/_width,0),_m-1);
			for (int i = b; i <= t; i++)
			{
				for (int j = l; j <= r; j++)
					_append(id, i, j);
			}
		}
	virtual	void del_object(int& id, float& left, float& top, float& right, float& bottom)
		{
			int t = min(max(top / _height, 0), _n - 1),
				b = min(max(bottom / _height, 0), _n - 1),
				l = min(max(left / _width, 0), _m - 1),
				r = min(max(right / _width, 0), _m - 1);

			for (int i = b; i <= t; i++)
			{
				for (int j = l; j <= r; j++)
					_remove(id, i, j);
			}
		}
	virtual	void update(int& id, float& old_left, float& old_top, float& old_right, float& old_bottom,
								float& new_left, float& new_top, float& new_right, float& new_bottom)
		{
			int old_l = old_left / _width, old_t=old_top/_height, old_r=old_right/_width, old_b=old_bottom/_height,
				new_l = new_left / _width, new_t = new_top / _height, new_r = new_right / _width, new_b = new_bottom / _height;

			//intersec calculate

			//vector<vector<int>> addLoc, deleteLoc;

			// Check if the squares intersect
			if (old_l > new_r || new_l > old_r || old_t < new_b || new_t > old_b) {
				// No intersection, return all points in each square
				for (int i = old_l; i <= old_r; i++) {
					for (int j = old_b; j <= old_t; j++) {
						//deleteLoc.push_back({ i, j });
						_remove(id, j, i);
					}
				}
				for (int i = new_l; i <= new_r; i++) {
					for (int j = new_b; j <= new_t; j++) {
						//addLoc.push_back({ i, j });
						_append(id, j, i);
					}
				}
			}
			else {
				// Compute points in square 1 but not in square 2
				for (int i = old_l; i <= old_r; i++) {
					for (int j = old_b; j <= old_t; j++) {
						if (i < new_l || i > new_r || j < new_t || j > new_b) {
							//deleteLoc.push_back({ i, j });
							_remove(id, j, i);
						}
					}
				}

				// Compute points in square 2 but not in square 1
				for (int i = new_l; i <= new_r; i++) {
					for (int j = new_b; j <= new_t; j++) {
						if (i < old_l || i > old_r || j < old_t || j > old_b) {
							//addLoc.push_back({ i, j });
							_append(id, j, i);
						}
					}
				}
			}


		}
	~Spatial()
	{
		_destroy_spatial();
	}
	};
/*
* Mainly for Tex Map, supported with cache, but the cache part ehh not implement yet
*/
class SpatialforTex : public Spatial
{
	vector<int> oldLTRB;
	set<int> cached_id;
	vector<vector<int>> loc;
public:
	SpatialforTex(int n, int m, int width, int height, int nearN = 2, int nearM = 2) : Spatial(n, m, width, height, nearN, nearM) { loc = vector<vector<int>>(n*m,vector<int>(2,0)); };
/*
* ONLY USE THIS WHEN U KNOW WHAT ARE U DOING, FOR SPATIAL MAP TEXU or render related thing only
*/
	void init_object_ONLYONCE(int id, int left, int top)
	{
		int t = min(max(top / _height, 0), _n - 1),
			l = min(max(left / _width, 0), _m - 1);
		_append(id, t, l);

		loc[id] = vector<int>(2, 0);
		loc[id][0] = left;
		loc[id][1] = top;
	}
	void getXY(int id, int& left, int& top)
	{
		left = loc[id][0];
		top = loc[id][1];
	}
	void getXYCenter(int id, int& left, int& top)
	{
		left = loc[id][0]+8;
		top = loc[id][1]+4;
	}
	void _destroy_spatial() override
	{
		Spatial::_destroy_spatial();
		oldLTRB.clear();
		cached_id.clear();
		loc.clear();
	}
	~SpatialforTex()
	{
		_destroy_spatial();
	}
};




#pragma warning(pop)