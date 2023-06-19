#include "QuadTree.h"
#include <chrono>
enum
{
    // ----------------------------------------------------------------------------------------
    // Element node fields:
    // ----------------------------------------------------------------------------------------
    enode_num = 2,

    //Trỏ vào enode tiếp theo
    // -1 thì là end
    enode_idx_next = 0,

    // lưu index của e trên elt
    enode_idx_elt = 1,

    // ----------------------------------------------------------------------------------------
    // Element fields:
    // ----------------------------------------------------------------------------------------
    elt_num = 5,

    // Lưu hcn của e
    elt_idx_lft = 0, elt_idx_top = 1, elt_idx_rgt = 2, elt_idx_btm = 3,

    // ID gốc của e
    elt_idx_id = 4,

    // ----------------------------------------------------------------------------------------
    // Node fields:
    // ----------------------------------------------------------------------------------------
    node_num = 2,

  //IDX của first child nếu là cành
  //        của first Element nếu là lá
    node_idx_fc = 0,

    // Lưu số số elt, -1 nếu ko phải lá 
    nodes_elts_count = 1,

    // ----------------------------------------------------------------------------------------
    // Processing Node fields:
    // ----------------------------------------------------------------------------------------
    nd_num = 6,

    // Lưu x,y, half_width, half_height
    nd_idx_cen_x = 0, nd_idx_cen_y = 1, nd_idx_half_width = 2, nd_idx_half_height = 3,

    // Index của node
    nd_idx_index = 4,

    // Lưu chiều sâu của node
    nd_idx_depth = 5,
};
/*
Thêm node vào index của chung nodes
*/
static void push_node(SimpleVector& nodes, int nd_index, int nd_depth, int nd_mx, int nd_my, int nd_sx, int nd_sy)
{
    int back_idx = nodes._push_back();
    nodes.set_I_in_Row(back_idx, nd_idx_cen_x, nd_mx);
    nodes.set_I_in_Row(back_idx, nd_idx_cen_y, nd_my);
    nodes.set_I_in_Row(back_idx, nd_idx_half_width, nd_sx);
    nodes.set_I_in_Row(back_idx, nd_idx_half_height, nd_sy);
    nodes.set_I_in_Row(back_idx, nd_idx_index, nd_index);
    nodes.set_I_in_Row(back_idx, nd_idx_depth, nd_depth);
}

QuadTree::QuadTree(int left, int bottom, int right, int top, int _max_elements, int _max_depth)
{
    max_elements = _max_elements;
    max_depth = _max_depth;
    nodes = SimpleVector(node_num);
    elts= SimpleVector(elt_num);
    enodes = SimpleVector(enode_num);
    nodes.insert_loc();
    nodes.set_I_in_Row(0, node_idx_fc, -1);
    nodes.set_I_in_Row(0, nodes_elts_count, 0);

    int _half_width = (right - left) >> 1;
    int _half_height = (top - bottom) >> 1;
    half_width = _half_width;
    half_height = _half_height;
    cen_x = left + _half_width;
    cen_y = bottom + _half_height;
}

QuadTree::~QuadTree()
{

    nodes.selfDestruc();
    elts.selfDestruc();
    enodes.selfDestruc();
    umap.clear();
    forced_one.clear();
}

int QuadTree::insert(int id, int left, int bottom, int right, int top)
{
    // loc của e mới ở elts
    const int new_element_index =elts.insert_loc();
    umap[id] = new_element_index;

    elts.set_I_in_Row(new_element_index, elt_idx_lft, left);
    elts.set_I_in_Row(new_element_index, elt_idx_top, bottom);
    elts.set_I_in_Row(new_element_index, elt_idx_rgt, right);
    elts.set_I_in_Row(new_element_index, elt_idx_btm, top);
    elts.set_I_in_Row(new_element_index, elt_idx_id, id);

    //add e vào các lá
    node_insert(0, 0, cen_x, cen_y, half_width, half_height, new_element_index);
    return new_element_index;
}

void QuadTree::update(int id, int left, int bottom, int right, int top)
{
    remove(id);
    insert(id, left, bottom, right, top);
}

void QuadTree::remove(int id)
{
    remove_e(umap[id]);
    umap.erase(id);
}

std::vector<int> QuadTree::search(int left, int bottom, int right, int top, int omit_element)
{
    SimpleVector result(query(left, bottom, right, top, omit_element));
    return result.toVtr();
}


void QuadTree::de_Split_phase()
{
    SimpleVector queue(1);

    // Kiểm tra xem thử root có phải nhánh không
    if (nodes.get_I_in_Row( 0, nodes_elts_count) == -1)
    {

       queue.set_I_in_Row(queue._push_back(), 0, 0);
    }

    while (queue.size()> 0)
    {
        // pop
        const int node =queue.get_I_in_Row( queue.size() - 1, 0);
        const int fc = nodes.get_I_in_Row(node, node_idx_fc);
        int num_empty_leaves = 0;
        int j = 0;
        queue.pop_back();

        // xét các node con
        for (j = 0; j < 4; ++j)
        {
            const int child = fc + j;

            //nếu là lá và trống thì tăng lượng lá trống lên
            if (nodes.get_I_in_Row( child, nodes_elts_count) == 0)
                ++num_empty_leaves;
            //nếu là nhánh thì xử lý trong loop tiếp theo
            else if (nodes.get_I_in_Row( child, nodes_elts_count) == -1)
            {
                queue.set_I_in_Row(queue._push_back(), 0, child);
            }
        }

        //Nếu cả 4 lá đều trống, thì sẽ có được 1 lá mới trống. 
        if (num_empty_leaves == 4)
        {

            //Xóa ngược chiều để lần sau thêm đúng chiều.
            nodes.erase_I_Row( fc + 3);
            nodes.erase_I_Row(fc + 2);
            nodes.erase_I_Row(fc + 1);
            nodes.erase_I_Row(fc + 0);

            // cho nó thành lá trống
            nodes.set_I_in_Row( node, node_idx_fc, -1);
            nodes.set_I_in_Row(node, nodes_elts_count, 0);
        }
    }
}
void QuadTree::insert_exception(int& value)
{
    forced_one.push_back(value);
}
SimpleVector QuadTree::query(int left, int bottom, int right, int top, int omit_element)
{

   
    // B1:tìm mọi lá giao với hcn
    int j = 0;
    const int elt_cap = elts.size();
    SimpleVector out(1, elt_cap);
    std::unordered_map<int, int, modified_hash> temp;
    for (int i = 0; i < forced_one.size(); i++)
    {
        int value = forced_one[i];
        out.set_I_in_Row(out._push_back(), 0, value);
        temp[value] = 1;
    }
    SimpleVector leaves(find_leaves( 0, 0, cen_x, cen_y, half_width,half_height, left, bottom, right, top));
    //b2, tìm mọi object trong các là mà giao với hcm
    for (j = 0; j < leaves.size(); ++j)
    {
        const int nd_index = leaves.get_I_in_Row(j, nd_idx_index);

        //iter qua từng các e node thuộc lá
        int elt_node_index =  nodes.get_I_in_Row(nd_index, node_idx_fc);
        while (elt_node_index != -1)
        {
            const int element = enodes.get_I_in_Row(elt_node_index, enode_idx_elt);
            const int lft = elts.get_I_in_Row(element, elt_idx_lft);
            const int top = elts.get_I_in_Row(element, elt_idx_top);
            const int rgt = elts.get_I_in_Row(element, elt_idx_rgt);
            const int btm = elts.get_I_in_Row(element, elt_idx_btm);
            const int element_id = elts.get_I_in_Row(element, elt_idx_id);
            if (temp[element]==0)
            if(element_id != omit_element)
            if(intersect(left, bottom, right, top, lft, top, rgt, btm))
            {
               out.set_I_in_Row(out._push_back(), 0, element_id);
               temp[element] = 1;
            }
            elt_node_index = enodes.get_I_in_Row( elt_node_index, enode_idx_next);
        }
    }
    return out;
}

void QuadTree::node_split(int index, int depth, int mx, int my, int sx, int sy, int element)
{
}
SimpleVector QuadTree::find_leaves(int node, int depth,
    int mx, int my, int sx, int sy,
    int lft, int btm, int rgt, int top)
{
    SimpleVector queue(nd_num);
    SimpleVector out(nd_num);
    push_node(queue, node, depth, mx, my, sx, sy);

    while (queue.size() > 0)
    {
        const int back_idx = queue.size() - 1;
        const int nd_cen_x = queue.get_I_in_Row(back_idx, nd_idx_cen_x);
        const int nd_cen_y = queue.get_I_in_Row(back_idx, nd_idx_cen_y);
        const int nd_half_w = queue.get_I_in_Row(back_idx, nd_idx_half_width);
        const int nd_half_h = queue.get_I_in_Row(back_idx, nd_idx_half_height);
        const int nd_index = queue.get_I_in_Row(back_idx, nd_idx_index);
        const int nd_depth = queue.get_I_in_Row(back_idx, nd_idx_depth);
        queue.pop_back();

        //Nếu là lá thì thêm vào out
        if (nodes.get_I_in_Row( nd_index, nodes_elts_count) != -1)
            push_node(out, nd_index, nd_depth, nd_cen_x, nd_cen_y, nd_half_w, nd_half_h);
        else
        {
            // Nếu không phải lá thì thêm node con vào queue
            // Node con nào giao với hcn mới đc thêm vào.
            const int fc = nodes.get_I_in_Row( nd_index, node_idx_fc);
            //Quad_w, quad_h nôm na là half_w, half_h của node con thôi
            const int quad_w = nd_half_w >> 1, quad_h = nd_half_h >> 1;
            // l b r t của hcn giao giữa 4 con
            const int l = nd_cen_x - quad_w, b = nd_cen_y - quad_h, r = nd_cen_x + quad_w, t = nd_cen_y + quad_h;

            //Thêm góc phần tư vào queue
            //3 4
            //1 2
            if (btm <= nd_cen_y)
            {
                
                if (lft <= nd_cen_x)
                    push_node(queue, fc + 0, nd_depth + 1, l, b, quad_w, quad_h);
                if (rgt > nd_cen_x)
                    push_node(queue, fc + 1, nd_depth + 1, r, b, quad_w, quad_h);
            }
            if (top > nd_cen_y)
            {
                if (lft <= nd_cen_x)
                    push_node(queue, fc + 2, nd_depth + 1, l, t, quad_w, quad_h);
                if (rgt > nd_cen_x)
                    push_node(queue, fc + 3, nd_depth + 1, r, t, quad_w, quad_h);
            }
        }
    }
    return out;

}

/*
nd_half_h
*/
void QuadTree::leaf_insert(int node, int depth, int e_cen_x, int e_cen_y, int e_half_w, int e_half_h, int element)
{
    // thêm E node vào lá
    
    //Loc của enode cũ của lá
    const int nd_fc = nodes.get_I_in_Row(node, node_idx_fc);
    //Loc trống để đặt node vào enode
    const int ed_dx = enodes.insert_loc();

    //Link lại với node enode mới
    nodes.set_I_in_Row( node, node_idx_fc, ed_dx);
    //Thêm node mới và enode
    //Ở đây là làm node mới liên kết với node trước đó
    enodes.set_I_in_Row(ed_dx, enode_idx_next, nd_fc);
    enodes.set_I_in_Row(ed_dx, enode_idx_elt, element);

    // Lá tới giới hạn, split
    int temp = nodes.get_I_in_Row(node, nodes_elts_count);
    if (nodes.get_I_in_Row(node, nodes_elts_count) == max_elements && depth < max_depth)
    {
        int fc = 0, j = 0;
        SimpleVector elts(1);

        // Lấy cái element trong lá đưa vào list.
        while (nodes.get_I_in_Row( node, node_idx_fc) != -1)
        {
            const int index = nodes.get_I_in_Row(node, node_idx_fc);
            const int next_index = enodes.get_I_in_Row(index, enode_idx_next);
            const int elt = enodes.get_I_in_Row(index, enode_idx_elt);

            // Pop_back
            nodes.set_I_in_Row(node, node_idx_fc, next_index);
            enodes.erase_I_Row(index);

            //add e vào elts
            elts.set_I_in_Row(elts._push_back(), 0, elt);
        }

        // Lấy chỗ cho 4 lá
        fc = nodes.insert_loc();
        nodes.insert_loc();
        nodes.insert_loc();
        nodes.insert_loc();
        nodes.set_I_in_Row(node, node_idx_fc, fc);

        // Khởi tạo 4 lá
        for (j = 0; j < 4; ++j)
        {
            nodes.set_I_in_Row( fc + j, node_idx_fc, -1);
            nodes.set_I_in_Row( fc + j, nodes_elts_count, 0);
        }

        // Gởi các E từ lá cũ sang lá mới
        nodes.set_I_in_Row(node, nodes_elts_count, -1);
        for (j = 0; j < elts.size(); ++j)
            node_insert(node, depth, e_cen_x, e_cen_y, e_half_w, e_half_h, elts.get_I_in_Row( j, 0));
    }
    else
    {
        // Tăng giá trị elts_count của node đc thêm.
        nodes.set_I_in_Row(node, nodes_elts_count, nodes.get_I_in_Row(node, nodes_elts_count) + 1);
    }
}


void QuadTree::node_insert(int index, int depth, int mx, int my, int sx, int sy, int element)
{
    
    int j = 0;
    //Lấy l t r b của element
    const int lft = elts.get_I_in_Row(element, elt_idx_lft);
    const int top = elts.get_I_in_Row(element, elt_idx_top);
    const int rgt = elts.get_I_in_Row(element, elt_idx_rgt);
    const int btm = elts.get_I_in_Row(element, elt_idx_btm);
    //Tìm các lá giao với Element
    SimpleVector leaves(find_leaves(index, depth, mx, my, sx, sy, lft, top, rgt, btm));
    for (j = 0; j < leaves.size(); ++j)
    {
        const int nd_cen_X = leaves.get_I_in_Row( j, nd_idx_cen_x);
        const int nd_cen_Y = leaves.get_I_in_Row(j, nd_idx_cen_y);
        const int nd_half_w = leaves.get_I_in_Row( j, nd_idx_half_width);
        const int nd_half_h = leaves.get_I_in_Row(j, nd_idx_half_height);
        const int nd_idx = leaves.get_I_in_Row(j, nd_idx_index);
        const int nd_depth = leaves.get_I_in_Row(j, nd_idx_depth);
        leaf_insert(nd_idx, nd_depth, nd_cen_X, nd_cen_Y, nd_half_w, nd_half_h, element);
    }
}


void QuadTree::remove_e(int element)
{


    const int lft = elts.get_I_in_Row( element, elt_idx_lft);
    const int top = elts.get_I_in_Row(element, elt_idx_top);
    const int rgt = elts.get_I_in_Row(element, elt_idx_rgt);
    const int btm = elts.get_I_in_Row(element, elt_idx_btm);

    // Tìm các lá có chứa element
    int j = 0;
    SimpleVector leaves(find_leaves(0, 0, cen_x, cen_y, half_width, half_height, lft, top, rgt, btm));


    for (j = 0; j < leaves.size(); ++j)
    {
        const int nd_index = leaves.get_I_in_Row(j, nd_idx_index);

        // Tìm idx của node của e trên lá
        int node_index = nodes.get_I_in_Row(nd_index, node_idx_fc);
        int prev_index = -1;
        // Ở đây làm hơi ẩu vì đang coi như trong này có element.
        //Cơ mà chắc chắn phải có, ko ra thì chắc thuật toán sai.
        while (node_index != -1 && enodes.get_I_in_Row (node_index, enode_idx_elt) != element)
        {
            prev_index = node_index;
            node_index = enodes.get_I_in_Row(node_index, enode_idx_next);
        }

        //Từ đây xóa node element trong enode
        if (node_index != -1)
        {
            const int next_index = enodes.get_I_in_Row(node_index, enode_idx_next);
            if (prev_index == -1)
               nodes.set_I_in_Row(nd_index, node_idx_fc, next_index);
            else
                enodes.set_I_in_Row(prev_index, enode_idx_next, next_index);
            enodes.erase_I_Row(node_index);

            // Giảm lượng count e của node 
            nodes.set_I_in_Row(nd_index, nodes_elts_count, nodes.get_I_in_Row( nd_index, nodes_elts_count) - 1);
        }
    }


    // Xóa e khỏi elts
    elts.erase_I_Row(element);
}

bool QTREE::intersect(int l1, int t1, int r1, int b1, int l2, int t2, int r2, int b2)
{
    if (l2 > r1)
        return false;
    if (r2 < l1)
        return false;
    if (t2 > b1)
        return false;
    if (b2 < t1)
        return false;
    return true;
}

uint64_t QTREE::modified_hash::splitmix64(uint64_t x)
{
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30))
        * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27))
        * 0x94d049bb133111eb;
    return x ^ (x >> 31);
}

int QTREE::modified_hash::operator()(uint64_t x) const
{
    static const uint64_t random = std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + random);
}
