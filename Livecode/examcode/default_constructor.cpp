struct typename
{
    int* p; 
    // default constructor
    Type() : // invoke constructors and initialize members after : before {
        p(new int(42))  // construct int* with result of new int(42)
        {
            //after { all members have benn constructed }
        }

        //...
};


// copy constructor is a constructor which first parameter is a reference to the class itself
// T const& is a reference to a constant T
// T is the name of the class, struct or union it is in 

struct Type 
{
    int* p; 
    //...
    Type(Type const& t) :   // inovke constructors and initialize members after : before{
        p(new int(*t.p))   // construct int* with result of new int(*t.p) -> int(42)
        {
            // after { all members have been constructed }
        }

    // Or method 2
    Type(Type const& t) :   // inovke constructors and initialize members after : before{
        p(t.p)   // construct int* with result of new int(*t.p) -> int(42)
        {
            // after { all members have been constructed }
        }
};



// move constructor is a constructor which first parameter is a reference to the class itself
// T&& is a reference to a T
// T is the name of the class, struct or union it is in
struct Type 
{
    int* p; 
    //...
    Type(Type&& t) :  // inovke constructors and initialize members after : before{
        p(t.p)   // construct int* with result of new int(*t.p) -> int(42)
        {
            t.p = nullptr; 
            // after { all members have been constructed }
            // t.p is nullptr, t refers to an object that is no longer valid and needs to be destroyed
        }
}


// copy assignment operator is a function with the signature
// T& T::operator=(T const&)
// T is the name of the class, struct or union it is in

struct Type 
{
    int* p; 
    //...
    Type& operator=(Type const& t) // invoke constructors and initialize members after : before{
    {
        *p = *t.p; // copy the value of *t.p into *p
        return *this;  // return a reference to the object that was assigned to
    }
    // Or method 2
    type& operator = (Type Const& t)    // copy assignment operator 
    {
        Type local(t); //  Create a local copy of t , copy construct a new object from t 
        std::swap(*this, local); // swap the values of *this and local
        // std::swap(p, local.p); // swap the values of p and local.p    same as (*this, local)
        return *this; // return a reference to the object that was assigned to
    }
};

// move assignment operator is a function with the signature
// T& T::operator=(T&&)
// T is the name of the class, struct or union it is in

struct Type 
{
    int* p; 
    //...
    Type& operator=(Type&& t) // invoke constructors and initialize members after : before{
    {
        delete p; // delete the current value of p
        p = t.p;  // copy the value of t.p into p
        t.p = nullptr; // t refers to an object that is no longer valid and needs to be destroyed
        return *this;  // return a reference to the object that was assigned to
    }

    // Or method 2 
    Type& operator=(Type&& t) // invoke constructors and initialize members after : before{
    {
        std::swap(p, t.p); // swap the values of p and t.p
        return *this;  // return a reference to the object that was assigned to
    }

    // Or method 3
    Type& operator=(Type&& t) // invoke constructors and initialize members after : before{
    {
        Type tmp(std::move(t)); // move construct a new object from t
        std::swap(p, tmp.p); // swap the values of p and tmp.p
        return *this;  // return a reference to the object that was assigned to
    }

    // Or method 4
    Type& operator=(Type&& t) // invoke constructors and initialize members after : before{
    {
        Type tmp(std::move(t)); // move construct a new object from t
        std::swap(*this, tmp); // swap the values of *this and tmp
        return *this;  // return a reference to the object that was assigned to
    }

    // Or method 5
    Type& operator=(Type&& t) // invoke constructors and initialize members after : before{
    {
        Type(std::move(t)).swap(*this); // move construct a new object from t and swap it with *this
        return *this;  // return a reference to the object that was assigned to
    }

    // Or method 6
    Type& operator=(Type&& t)
    {
        if(this != &t) // check for self assignment
        {
            delete p; // delete the current value of p
            p = t.p;  // copy the value of t.p into p
            t.p = nullptr; // t refers to an object that is no longer valid and needs to be destroyed
        }
        return *this;  // return a reference to the object that was assigned to
    }
};

//destructor is a function with the signature
// T::~T()
// T is the name of the class, struct or union it is in
// are invoked when an instance goes out of scope or is destroyed: 
// 1. the scope of the object ends
// 2. the object is explicitly destroyed by a call to delete
// 3. the object is a temporary and the end of the full expression is reached
// 4. global variables are destroyed after main() returns
// 5. local static variables are destroyed after the program exits main()
// 6. stack-allocated objects(vaiables) are destroyed when the stack unwinds after an exception

//called on dynamically allocated objects, T* p = new T();

struct Type
{
    int* p; 
    //...
    ~Type() // invoke constructors and initialize members after : before{
    {
        delete p; // delete the current value of p , free memory associated with p
    }
};
