#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class CuShPtr
{
private:
    T* ptr;
    int* count;
    inline void dec_count()
    {
        (*count)--;
    }
  
    inline void inc_count()
    {
        (*count)++;
    }
        
public:
    CuShPtr(T* _ptr)
    {
        ptr = _ptr;
        count = new int(1);
    }

    ~CuShPtr()
    {
        if (count != nullptr)
        {
            dec_count();
            if (*count == 0)
            {
                delete ptr;
                delete count;
            }
        }
    }

    CuShPtr(const CuShPtr<T>& other)
    {
        ptr = other.ptr;
        count = other.count;
        inc_count();
    }

    CuShPtr<T>& operator = (const CuShPtr<T>& other)
    {
        if (count != nullptr)
        {
            dec_count();
            if (*count == 0)
                delete ptr;
        }
        ptr = other.ptr;
        count = other.count;
        inc_count();
        return *this;
    }

    int use_count() const
    {
        if (count != nullptr)
            return *count;
        else
            return 0;
    }

    void reset()
    {
        if (count != nullptr)
        {
            dec_count();
            if (*count == 0)
            {
                delete ptr;
                delete count;
            }

        }
        count = nullptr;
        ptr = nullptr;
    }

    T* operator *()
    {
        return ptr;
    }

    T* operator ->()
    {
        return ptr;
    }
};

class A
{
public:
    int i;
    A(int _i) :i(-i) {}
    ~A() {
        cout << "deleting A" << endl;
    }
};

CuShPtr<A> make_A() {
    CuShPtr<A> a(new A(5));
    return a;
}


int main()
{
    CuShPtr<A> a = make_A();
    CuShPtr<A> b = a;
    CuShPtr<A> c = a;

    cout << a.use_count() << " " << b.use_count() << " " << c.use_count() << endl;

    c.reset();

    cout << a.use_count() << " " << b.use_count() << " " << c.use_count() << endl;
    cout << a->i << endl;
    return 0;
}
