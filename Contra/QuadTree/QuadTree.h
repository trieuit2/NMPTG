#pragma once
#include "SimpleVector.h"
#include <vector>
#include <unordered_map>
using namespace QTREE;
using namespace std;
typedef class QuadTree QuadTree;
namespace QTREE
{
    bool intersect(int l1, int t1, int r1, int b1,
        int l2, int t2, int r2, int b2);
    struct modified_hash {

        static uint64_t splitmix64(uint64_t x);
        int operator()(uint64_t x) const;
    };
}

class QuadTree
{
    //Quản lý node, root nằm ở nodes đầu
    SimpleVector nodes;
    //Quản lí giá trị đc insert vào( format : left bottom right top ID)
    SimpleVector elts;

    // các nodes của elts
    SimpleVector enodes;
    //Map từ ID -> sang element id
    std::unordered_map<int, int, modified_hash> umap;
    // 
    vector<int> forced_one;
    // Range của root
    int cen_x, cen_y, half_width, half_height;
    //Số lượng element tối đa, 
    //nếu vượt quá thì split trừ khi đạt level tối đa
    int max_elements;
    // Level tối đa
    int max_depth;
    



    void node_split(int index, int depth, int mx, int my, int sx, int sy, int element);
    /*
    Thêm element vào mọi node giao với element
    */
    void node_insert(int index, int depth, int mx, int my, int sx, int sy, int element);
    /*
    Xóa element
    */
    void remove_e(int element);
    /*
    Tìm mọi lá giao với bb
    */
    SimpleVector find_leaves(int node, int depth,
        int mx, int my, int sx, int sy,
        int lft, int top, int rgt, int btm);
    /*
    Thêm element vào lá
    */
    void leaf_insert(int node, int depth, int e_cen_X, int e_cen_Y, int e_half_w, int e_half_h, int element);
    SimpleVector query(int left, int bottom, int right, int top, int omit_element = -1);
public:
    QuadTree(int left, int bottom, int right, int top, int max_elements, int max_depth);
    ~QuadTree();
    /*
    Thêm obj vào 
    */
    int insert(int id, int left, int bottom, int right, int top);
    void update(int id, int left, int bottom, int right, int top);
    void remove(int id);
    std::vector<int> search(int left, int bottom, int right, int top, int omit_element = -1);
    void de_Split_phase();
    void insert_exception(int& value);
};


