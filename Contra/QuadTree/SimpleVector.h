#pragma once
#include <vector>
namespace QTREE
{

    enum
    {
        FIXED_SIZE = 128
    };

    /*
    Nó là 1 cái vector đấy :v
    */
    struct SimpleVector
    {
    private:
        //Như cái tên, là phần data của cái vector này.
        std::vector<int> data;
        //Vector này hỗ trợ lưu 2D như 1 vector 1D
        int value_per_row;

        // Size
        int _size;

        // Giới hạn của SV, hết thì thêm thôi hehe
        int cap;

        // Index cho vị trí bị xóa default=-1
        // Mục đích chính tương tự với cái remove_id
        int free_element;


        
    public:
        int _push_back();
        SimpleVector(int _value_per_row=1,int resize=-1);
        ~SimpleVector();
        void selfDestruc();
        void clear();
        /*
        size chỉ tăng chứ không có giảm nếu không pop_back
        */
        const int size();

        const int get_I_in_Row(int i, int row);
        void set_I_in_Row(int i, int row,int val);

        /*
        * Trong trường hợp sài hết buffer, kiếm thêm với size= size cũ
        */
        
        void pop_back();
        /*
        tương tự như của vector
        */
        void push_back(int val,int row);
        /*
        Trả về loc trống để insert giá trị mới vào.
        Sẽ lấy thêm chỗ mỗi lần chạy nếu thiếu
        */
        int insert_loc();
        void erase_I_Row(int n);
        std::vector<int> toVtr();
    };

}
