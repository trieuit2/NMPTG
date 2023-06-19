#include "SimpleVector.h"
#include <cassert>
#include <algorithm>
namespace QTREE
{ 
    SimpleVector::SimpleVector(int _value_per_row,int resize)
    {
        
        _size = 0;
        if (resize == -1)
        {
            cap = FIXED_SIZE;
            data = std::vector<int>(_value_per_row * FIXED_SIZE, 0);
        }
        else
        {
            cap = resize*_value_per_row;
            data = std::vector<int>(cap, 0);
        }
        value_per_row = _value_per_row;
        free_element = -1;
    }

    SimpleVector::~SimpleVector()
    {
        selfDestruc();
    }

    void SimpleVector::selfDestruc()
    {
        data.clear();

    }

    void SimpleVector::clear()
    {
        _size = 0;
        free_element = -1;
    }

    const int SimpleVector::size()
    {
        return _size;
    }
    const int SimpleVector::get_I_in_Row(int i, int row)
    {
        assert(i >= 0 && i <_size);
        return data[i*value_per_row + row];
    }

    void SimpleVector::set_I_in_Row(int i, int row, int val)
    {
        assert(i >= 0 && i < _size);
        data[i * value_per_row + row] = val;
    }
    int SimpleVector::_push_back()
    {
        const int new_pos = (_size + 1) * value_per_row;

        //Nếu List full thì phải kiếm thêm chỗ.
        if (new_pos > cap)
        {
            // Cap mới sẽ gấp đôi cấp cũ
            const int new_cap = new_pos * 2;
            data.resize(new_cap);

            //Cập nhật lại cap
            cap = new_cap;
        }
        return _size++;
    }
    void SimpleVector::pop_back()
    {
        assert(_size > 0);
        --_size;
    }
    void SimpleVector::push_back(int val,int row)
    {
        set_I_in_Row(_push_back(), row, val);
    }
    int SimpleVector::insert_loc()
    {
        // Nếu như có chỗ trống(do bị xóa thì sao)
        if (free_element != -1)
        {
            const int index = free_element;
            const int pos = index * value_per_row;


            free_element = data[pos];


            return index;
        }

        return _push_back();
    }

    void SimpleVector::erase_I_Row(int i)
    {
        /*
        Giả thích cơ chế : thay vì lưu free element như 1 array, lưu ngay trên data luôn
        nôm na là chỗ bị xóa BÂY GIỜ sẽ lưu chỗ bị xóa TRC ĐÓ
        còn free_element sẽ lưu vị trí của vị trí bị xóa BÂY GIỜ
        */
        const int pos = i * value_per_row;
        data[pos] = free_element;
        free_element = i;
    }
    using namespace std;
    vector<int> SimpleVector::toVtr()
    {
        vector<int> result=data;
        result.resize(_size);
        return result;
    }

}
