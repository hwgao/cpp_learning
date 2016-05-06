#if 0
#include <iostream>
#include <memory>

using namespace std;

class Base
{
public:
//    Base() = default;
//    Base(Base &b) = delete;
//    Base& operator=(Base &b) = delete;
    Base(int a = 0, int b = 0): aa{a}, bb{b}
    {
        cout << __FUNCTION__ << " default " << aa << " " << bb << endl;
    }

    Base(Base &b): aa{b.aa}, bb{b.bb}
    {
        cout << __FUNCTION__ << " copy" << endl;
    }

    Base& operator=(Base &b)
    {
        aa = b.aa;
        bb = b.bb;
        cout << __FUNCTION__ << " copy assignment" <<endl;

        return *this;
    }

    Base(Base &&b): aa{move(b.aa)}, bb{move(b.bb)}
    {
        cout << __FUNCTION__ << " move" <<endl;
    }

    Base& operator=(Base &&b)
    {
        aa = move(b.aa);
        bb = move(b.bb);
        cout << __FUNCTION__ << " move assignment" <<endl;

        return *this;
    }

    void a();
    virtual ~Base()
    {
        cout << __FUNCTION__ << endl;
    }

private:
    int aa = 0;
    int bb = 0;
    virtual void b(int);
    virtual void c(double);
};

void Base::a()
{
    b(aa);
    c(bb);
}

void Base::b(int i)
{
    cout << "Base::b() " << i << endl;
}

void Base::c(double i)
{
    cout << "Base::c() " << i << endl;
}

class Derive : public Base
{
public:
    ~Derive()
    {
        cout << __FUNCTION__ << endl;
    }

private:
    void b(int) override;
    void c(double) override;
};

void Derive::b(int i)
{
    cout << "Derive::b() " << i << endl;
}

void Derive::c(double i)
{
    cout << "Derive::c() " << i << endl;
}

Base createBase(int a, int b)
{
    Base temp(a, b);
    return temp;
}

int main()
{
//    auto v = unique_ptr<Base>(new Derive());
//    v->a();

    auto k = createBase(100, 200);
    k.a();

//    Base c1(20, 30);
//    Base c2 = move(c1);
//    c2 = c1;
    return 0;
}

#endif

#if 0
// bind example
#include <iostream>     // std::cout
#include <functional>   // std::bind

// a function: (also works with function object: std::divides<double> my_divide;)
double my_divide (double x, double y) {return x/y;}

struct MyPair {
  double a,b;
  double multiply() {return a*b;}
};

int main () {
  using namespace std::placeholders;    // adds visibility of _1, _2, _3,...

  // binding functions:
  auto fn_five = std::bind(my_divide,10,2);               // returns 10/2
  std::cout << fn_five() << '\n';                          // 5

  auto fn_half = std::bind(my_divide,_1,2);               // returns x/2
  std::cout << fn_half(10) << '\n';                        // 5

  auto fn_invert = std::bind(my_divide,_2,_1);            // returns y/x
  std::cout << fn_invert(10,2) << '\n';                    // 0.2

  auto fn_rounding = std::bind<int>(my_divide,_1,_2);     // returns int(x/y)
  std::cout << fn_rounding(10,3) << '\n';                  // 3

  MyPair ten_two {10,2};

  // binding members:
  auto bound_member_fn = std::bind(&MyPair::multiply,_1); // returns x.multiply()
  std::cout << bound_member_fn(ten_two) << '\n';           // 20

  auto bound_member_data = std::bind(&MyPair::a,ten_two); // returns ten_two.a
  std::cout << bound_member_data() << '\n';                // 10

  return 0;
}
#endif

#if 0
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    // vector<string> s {"zebra", "elephent", "cat", "dog"};
    vector<string> s;
    s.reserve(4);
    s.push_back("zebra");
    s.push_back("elephant");
    s.push_back("cat");
    s.push_back("dog");
    // cout << std::accumulate(s.cbegin(), s.cend(), string("All animals: "));
    cout << s.capacity() << endl;
    cout << std::accumulate(begin(s), end(s), string("All animals: "),
                            [](string a, string b) { return a + " " + b; });
    cout << endl;
    std::for_each(s.cbegin(), s.cend(), [](string a){ cout << a << " "; });
    cout << endl;

    return 0;
}

#endif

#if 0
#include <iostream>
using namespace std;

class A {
public:
    A(size_t s = 0): mSize(s), mArray(mSize ? new int[s] : nullptr) {
        cout << __FUNCTION__ << " default cntr" << endl;
    }
    A(const A &other) : A(other.mSize) {
        cout << __FUNCTION__ << " copy cntr" << endl;
        std::copy(other.mArray, other.mArray + mSize, mArray);
    }
    A & operator=(A rhs) {
        cout << __FUNCTION__ << " copy/move assignment"<< endl;
        swap(*this, rhs);
        return *this;
    }
    A(A &&other) : A() {
        cout << __FUNCTION__ << " move cntr" << endl;
        swap(*this, other);
    }

    ~A() {
        cout << __FUNCTION__ << " to free the array with " << mSize << " elements" << endl;
        delete[] mArray;
    }
private:
    size_t mSize;
    int *mArray;
    friend void swap(A &first, A &second) {
        std::swap(first.mSize, second.mSize);
        std::swap(first.mArray, second.mArray);
    }
};

A getA(size_t s) {
    A temp(s);
    return temp;
}

A moveA(A a) {
    return a;
}

int main() {
//    A vvv(10);
//    A bbb = std::move(vvv);
    A a1, a2;
    a1 = moveA(A(10));
}

#endif

#if 0
#include <string>
#include <iostream>
#include <utility>

struct A {
    std::string s;
    A() : s("test") {}
    A(const A& o) : s(o.s) { std::cout << "move failed!\n";}
    A(A&& o) : s(std::move(o.s)) {}
    A& operator=(const A& other) {
         s = other.s;
         std::cout << "copy assigned\n";
         return *this;
    }
    A& operator=(A&& other) {
         s = std::move(other.s);
         std::cout << "move assigned\n";
         return *this;
    }
};

A f(A a) { return a; }

struct B : A {
     std::string s2;
     int n;
     // implicit move assignment operator B& B::operator=(B&&)
     // calls A's move assignment operator
     // calls s2's move assignment operator
     // and makes a bitwise copy of n
};

struct C : B {
    ~C() {} // destructor prevents implicit move assignment
};

struct D : B {
    D() {}
    ~D() {} // destructor would prevent implicit move assignment
    D& operator=(D&&) = default; // force a move assignment anyway
};

int main()
{
    A a1, a2;
    std::cout << "Trying to move-assign A from rvalue temporary\n";
    a1 = f(A()); // move-assignment from rvalue temporary
    std::cout << "Trying to move-assign A from xvalue\n";
    a2 = std::move(a1); // move-assignment from xvalue

    std::cout << "Trying to move-assign B\n";
    B b1, b2;
    std::cout << "Before move, b1.s = \"" << b1.s << "\"\n";
    b2 = std::move(b1); // calls implicit move assignment
    std::cout << "After move, b1.s = \"" << b1.s << "\"\n";

    std::cout << "Trying to move-assign C\n";
    C c1, c2;
    c2 = std::move(c1); // calls the copy assignment operator

    std::cout << "Trying to move-assign D\n";
    D d1, d2;
    d2 = std::move(d1);
}
#endif

#if 0
#include <iostream>

struct A {
    bool run() const & { return false; }
    bool run() && { return true; }
};

int main() {
    A a;
    std::cout << a.run() << std::endl;
    std::cout << A().run() << std::endl;
}

#endif

#if 0
#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T>
class A {
    size_t size;
    T *data;
public:
    A(size_t s): size{s}, data{new T[size]} {}
    A(): A(0) {}
    A(const A &other): size{other.size}, data{new T[size]} {
        for (size_t i = 0; i < other.size; ++i) {
            data[i] = other.data[i];
        }
    }

    A(A &&other) = default;

    size_t getSize() { return size; }

    void setData(const size_t idx, const T &d) {
        if (idx > size - 1) {
            throw std::out_of_range("index wrong");
        }
        data[idx] = d;
    }

    T getData(const size_t idx) {
        if (idx > size - 1) {
            throw std::out_of_range("index wrong");
        }

        return data[idx];
    }

    ~A() {
        cout << __FUNCTION__ << endl;
        delete[] data;
        data = nullptr;
        size = 0;
    }
};

int main() {
    int c = 5;
    A<unsigned> a{10};
    A<unsigned> b = std::move(a);
    cout << "a size is " << a.getSize() << endl;
    try {
        a.setData(100, 10);
        cout << a.getData(0) << endl;
    } catch (exception &e) {
        cout << e.what() << endl;
    }

}

#endif

#if 0
// const

#include <iostream>
#include <string>

using namespace std;
class Dog {
public:
    Dog(const string &name = "Bob") : m_name{name} {}
    operator string() { return m_name; }
    ~Dog() { cout << m_name << " is destructed." << endl; }
private:
    string m_name;
};

int main() {
    Dog d1{"Henry"};
    Dog d2;
    d2 = d1;

    string a = d1;
    cout << "a = " << a << endl;
}
#endif

#if 0
// ADL

namespace A {
    struct X {};
    void g(X x){ x = x; }
}

int main() {
    A::X a;
    g(a);
}

#endif

#if 0
#include <iostream>
#include <string>

using namespace std;

class OpenFile {
public:
    OpenFile(string name) : m_name(name) {
        cout << "File name is " << name << endl;
    }
    string getName() { return m_name; }
    void destroyMe() { delete this; }
private:
    ~OpenFile() { cout << "OpenFile destructed." << endl; };
    string m_name;
};

int main() {
    OpenFile* f = new OpenFile{"Test file"};
    f->destroyMe();
    cout << "f is " << f->getName() << endl;
}

#endif

#if 0
#include <iostream>

using namespace std;

class B {
public:
    void f(int a) { cout << "f(int a) is called with a = " << a << endl; };
    void f(string a) { cout << "f(string a) is called with a = " << a << endl; };
    void f(int a, int b) { cout << "f(int, int) is called" << endl; }
};

class D : public B {
public:
    using B::f;
    void f() { cout << "f() is called" << endl; }
};

int main() {
    D d;
    d.f(3);
    d.f(3, 5);
    d.f("hello");

}

#endif

#if 0
#include <iostream>
#include <new>

using namespace std;

namespace A {
struct X {};
void g(X a) { a = a; cout << "g is called" << endl; };
}

int main() {
    A::X x;
    g(x);

    new_handler origianl_handler;
    origianl_handler =std::set_new_handler([](){ cout << "my new handler" << endl; throw std::bad_alloc(); });
    try {
        ::operator new(0x10000000000);
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
}

#endif

#if 0
#include <iostream>
#include <memory>

using namespace std;

struct Hen {
    int id;
    int eggs;

    Hen(int id_, int eggs_) :
        id {id_},
        eggs {eggs_} {}

    string print() {
        return;
    }

    ~Hen() {
        cout << "destruct" << endl;
    }
};

auto main() -> int {
    auto hen = unique_ptr<Hen>{new Hen{3, 4}};

    Hen copy = *hen;
    if (hen) {cout << "hen" << endl;}
    Hen &copy2 = *hen;
    Hen *copy3 = hen.get();
}
#endif

#if 0
#include <memory>
#include <iostream>
#include <assert.h>
#include <string>
#include <vector>

using namespace std;

auto main() -> int {
    auto sp = shared_ptr<int> { new int{5} };
    // auto sp = make_shared<int>(5);
    auto wp = weak_ptr<int> {};
    wp = sp;

    assert(!wp.expired());
    assert(wp.use_count() == 1);

    int i = *sp;
    assert(i == 5);

    int &r = *sp;
    assert(r == 5);

    int *p = sp.get();
    assert(*p == 5);

    shared_ptr<string> pNico{ new string{"nico"}, [](string *p){
                              cout << "delete " << *p << endl;
                              delete p; } };
    shared_ptr<string> pJutta{ new string{"jutta"} };
    (*pNico)[0] = 'N';
    printf("%s\n", pNico->c_str());
    pNico->replace(0, 1, "M");
    printf("%s\n", pNico->c_str());

    vector<shared_ptr<string>> whoMadeCoffee;
    whoMadeCoffee.push_back(pNico);
    whoMadeCoffee.push_back(pJutta);
    whoMadeCoffee.push_back(pNico);
    whoMadeCoffee.push_back(pNico);
    whoMadeCoffee.push_back(pJutta);

    for (auto p : whoMadeCoffee) {
        cout << *p << " ";
    }
    cout << endl;

    *pNico = "tom";

    for (auto p : whoMadeCoffee) {
        cout << *p << " ";
    }
    cout << endl;

    cout << pNico.use_count() << endl;
    // pNico.reset(new string{"Hello"});

    for (auto p : whoMadeCoffee) {
        cout << *p << " ";
    }
    cout << endl;
    cout << pNico.use_count() << endl;
    pNico.reset();
    cout << pNico.use_count() << endl;

    int aa[] = {3, 4, 5};

    shared_ptr<int> a(aa, [](int *p) {
        cout << "delete " << *p << endl;
        delete[] p;
    });
}
#endif

#if 0
#include <memory>
#include <array>
#include <vector>
#include <cstdint>

typedef std::vector<int32_t> int_seq;

auto main() -> int
{
    // @@- Non-Compliant -@@
    std::unique_ptr<int32_t[]> oa_1 (new int32_t[10]);

    // @@- Non-Compliant -@@
    std::shared_ptr<int32_t> ob_1 (new int32_t[10]
            , std::default_delete<int32_t[]>());

    // @@+ Compliant +@@
    std::array<int32_t, 10> oa_2;

    // @@+ Compliant +@@
    std::shared_ptr< int_seq > ob_2 (std::make_shared<int_seq>( 10 , int32_t() ));
}
#endif

#if 0
// util/sharedptr2.cpp

#include <string>
#include <iostream>
#include <fstream>   // for ofstream
#include <memory>    // for shared_ptr
#include <cstdio>    // for remove()

class FileDeleter
{
    private:
      std::string filename;
    public:
      FileDeleter (const std::string& fn)
       : filename(fn) {
      }
      void operator () (std::ofstream* fp) {
          std::cout << "remove " << filename << std::endl;
          fp->close();                   // close.file
          std::remove(filename.c_str()); // delete file
      }
};

int main()
{
    // create and open temporary file:
    std::shared_ptr<std::ofstream> fp(new std::ofstream("tmpfile.txt"),
                                      FileDeleter("tmpfile.txt"));
}
#endif

#if 0
#include <iostream>

class P {
public:
    P(int a, int b) {}
    explicit P(int a, int b, int c) {}
};

void fp(const P& p) {}

auto main() -> int {
    fp({47, 11});
    fp(P{47, 11, 12});

}
#endif

#if 0
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class P {
public:
    explicit P(string &s) : s_{s} {}
    void hello() const { cout << "hello " << s_ << endl; }
private:
    string s_;
};

auto main() -> int {
    vector<string> a {"a", "b", "c"};
    for(const P &p : a) {
        p.hello();
    }
    return 0;
}
#endif

#if 0
// util/sharedptr3.cpp

#include <memory>     // for shared_ptr
#include <sys/mman.h> // for shared memory
#include <fcntl.h>
#include <unistd.h>
#include <cstring>    // for strerror()
#include <cerrno>     // for errno
#include <string>
#include <iostream>

class SharedMemoryDetacher
{
  public:
    void operator () (int* p) {
        std::cout << "unlink /tmp1234" << std::endl;
        if (shm_unlink("/tmp1234") != 0) {
            std::cerr << "OOPS: shm_unlink() failed" << std::endl;
        }
    }
};

std::shared_ptr<int> getSharedIntMemory (int num)
{
    void* mem;
    int shmfd = shm_open("/tmp1234", O_CREAT|O_RDWR, S_IRWXU|S_IRWXG);
    if (shmfd < 0) {
        throw std::string(strerror(errno));
    }
    if (ftruncate(shmfd, num*sizeof(int)) == -1) {
        throw std::string(strerror(errno));
    }
    mem = mmap(nullptr, num*sizeof(int), PROT_READ | PROT_WRITE,
               MAP_SHARED, shmfd, 0);
    if (mem == MAP_FAILED) {
        throw std::string(strerror(errno));
    }
    return std::shared_ptr<int>(static_cast<int*>(mem),
                                SharedMemoryDetacher());
}

int main()
{
    // get and attach shared memory for 100 ints:
    std::shared_ptr<int> smp(getSharedIntMemory(100));

    // init the shared memory
    for (int i=0; i<100; ++i) {
        smp.get()[i] = i*42;
    }

    // deal with shared memory somewhere else:
    // ...
    std::cout << "<return>" << std::endl;
    std::cin.get();

    // release shared memory here:
    smp.reset();
    // ...
}
#endif

#if 0
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Person {
private:
    string name_;
    shared_ptr<Person> mom_;
    shared_ptr<Person> dad_;
    vector<weak_ptr<Person>> kids_;
public:
    Person(const string &name, shared_ptr<Person> m = nullptr, shared_ptr<Person> d = nullptr) :
        name_(name), mom_(m), dad_(d){

    }

    void addKid(shared_ptr<Person> k) {
        kids_.push_back(weak_ptr<Person>{k});
    }

    string getName() {
        return name_;
    }

    string getMomName() {
        return mom_->getName();
    }

    ~Person() {
        cout << "Release " << name_ << endl;
    }
};

shared_ptr<Person> makeFamily(const string &name) {
    auto mom = make_shared<Person>(name +"'s mom");
    auto dad = make_shared<Person>(name +"'s dad");
    auto kid = make_shared<Person>(name, mom, dad);
    mom->addKid(kid);
    dad->addKid(kid);
    return kid;
}

auto main() -> int {
    auto peter = makeFamily("Peter");
    cout << peter.use_count() << endl;
    cout << peter->getName() << endl;
    cout << peter->getMomName() << endl;

    return 0;
}
#endif

#if 0
#include <iostream>
using namespace std;

auto main() -> int {
    int a = 100;
    auto hl = [a] () mutable {
        cout << "hello lamda" << endl;
        a = 10;
        return a;
    };

    cout << hl() << endl;
    cout << a << endl;

    return 0;
}
#endif

#if 0
#include <iostream>
#include <functional>
using namespace std;

std::function<int(int,int)> getLamda() {
    return [] (int a, int b) {
        return a*b;
    };
}

auto main() -> int {
    auto l = getLamda();
    cout << l(3, 4) << endl;

    auto m = [] (int a, int b) { return a + b; };
    cout << m(4, 5) << endl;

    return 0;
}
#endif

#if 0
#include <iostream>
#include <functional>
using namespace std;

auto main() -> int {

    function<int(int, int)> m = [] (int a, int b) { return a + b; };
    cout << m(4, 5) << endl;

    return 0;
}
#endif

#if 0
#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>
using namespace std;

namespace {
class E : public exception {
public:
    E(const string &msg) : msg_(msg) {}
    const char* what() const noexcept override {
        return msg_.c_str();
    }
private:
    string msg_;
};

const E E_OUCH{"ouch!"};
const E E_BAD{"bad code"};
const E E_WORSE{"don't do that"};
}

auto main() -> int {
    vector<int> a;
    a.push_back(2);

    try {
        throw E_WORSE;
    } catch (out_of_range &e) {
        cout << "out of range exception " << e.what() << endl;
    } catch (exception &e) {
        cout << e.what() << endl;
    }

    cout << "final" << endl;

    vector<string> vs = {"aa", "bb", "cc"};

    for (auto &s: vs) {
        cout << s << endl;
    }

    return 0;
}
#endif

#if 0
#include <iostream>
#include <utility>
#include <tuple>
using namespace std;

struct Foo {
    Foo(tuple<int, float>) {
        cout << "Foo::Foo(tuple)" << endl;
    }

    template<typename... Args>
    Foo(Args... args) {
        cout << "Foo::Foo(args...)" << endl;
    }
};

auto main() -> int {
    tuple<int, float> t{1, 2.22};
    pair<int, Foo> p1{42, t};
    pair<int, Foo> p2{piecewise_construct, make_tuple(42), t};

    return 0;
}
#endif

#if 0
#include <iostream>
#include <utility>
#include <functional>
using namespace std;

auto main() -> int {
    int i = 0;
    auto p = make_pair(std::ref(i), std::ref(i));
    ++p.first;
    cout << i << endl;
    ++p.second;
    cout << i << endl;

    return 0;
}
#endif

#if 0
#include <iostream>
#include <functional>
#include <utility>

auto main() -> int {
    int i = 10;
    //auto p = std::make_pair(std::ref(i), std::ref(i));
    std::pair<int&, int&> p{ i, i };
    ++p.first;
    std::cout << i << std::endl;
    ++p.second;
    std::cout << i << std::endl;
    std::cout << std::get<0>(p) << std::endl;

    std::cin.get();
    return 0;
}
#endif

#if 0
#include <iostream>
#include <tuple>
#include <functional>
#include <string>
#include <cassert>
#include "printtuple.hpp"
using namespace std;

auto main() -> int {
#if 0
    tuple<int, float, string> t1{ 4, 4.9f, "hello tuple" };
    cout << tuple_size<decltype(t1)>::value << endl;

    typedef tuple<int, float, string> TT;
    TT t2{ 2, 4.8f, "t1" };
    cout << tuple_size<TT>::value << endl;
    tuple_element<2, TT>::type aa;

    aa = "aa";
    cout << aa << endl;
#endif

#if 0
    //tuple<int, float, string> t1;
    tuple<int, float, string> t1{ 4, 4.9f, "hello tuple" };

    cout << get<0>(t1) << " ";
    cout << get<1>(t1) << " ";
    cout << get<2>(t1) << " ";
    cout << endl;

    int a = 100;
    float b;
    string s;
    make_tuple(ref(a), ref(b), ref(s)) = t1;
    //auto tt = tie(a, b, ignore) = t1;
    //auto tt = tie(a, b, ignore);
    cout << endl;
    cout << a << endl;
    cout << b << endl;
    cout << s << endl;

    cout << t1 << endl;
#endif
}
#endif

#if 0
#include <iostream>
#include <memory>
#include <functional>
#include <cassert>
using namespace std;

typedef void (*DEL)(int *);
void dd(int *p) {
    cout << "dd " << *p << endl;
    delete p;
}

template<typename T>
void foo(const T& val) {
    if (std::is_pointer<T>::value) {
        cout << "foo() called for a pointer" << endl;
    } else {
        cout << "foo() called for a value" << endl;
    }
}

auto main() -> int {
    auto del = [](int *p) { cout << "delete " << *p << endl; delete p; };
    shared_ptr<int> sp = shared_ptr<int>(new int{5}, del);
    auto *deleter = get_deleter<decltype(del)>(sp);
    assert(*deleter == del);
    int *aa = new int(10);
    // * has low priority than (), so must use (*deleter)
    // (*deleter)(aa);

    foo<int>(5);

    function<void(int*)> funp = dd;
    funp(aa);

    return 0;
}
#endif

#if 0
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include "printable.hpp"
using namespace std;

class Widget : public Printable<Widget> {
public:
	Widget(int x = 0, int y = 0) : x_{ x }, y_{ y } {}
	string toString() const override {
#if 01
		// safe c++11
		return "[Widget] x=" + to_string(x_) + ", y=" + to_string(y_);
#else
		// safe slow
		ostringstream sstm;
		sstm << "[Widget] x=" << x_ << ", y=" << y_;
		return sstm.str();
#endif
	}
private:
	int x_;
	int y_;
};

auto main() -> int {
	auto a = new int{ 10 };
	auto b = int{ 20 };
    // Direct list initialization of a variable with a deduced type will change meaning in
    // a future version of Clang; insert an '=' to avoid a change in behavior
    // auto c{20};
	auto c = { 20 };
	// For single parameter, prefer the following one.
	auto d = 20;

	// For multiple parameters, prefer the following one.
	auto aa = new Widget{3, 4};
	cout << *aa << endl;
	auto bb = new Widget{};
	cout << *bb << endl;
	auto cc = Widget{};
	cout << cc << endl;
	auto dd = Widget{10, 30};
	cout << dd << endl;

	vector<int> ee(3, 4);
	assert(ee.size() == 3);

	vector<int> ff{ 3, 4 };
	assert(ff.size() == 2);

	auto gg = vector < int > {4, 5};
	assert(gg.size() == 2);

    constexpr int aaa = 10;
    int bbb[aaa];

	return 0;
}
#endif

#if 0
#include <iostream>
#include <vector>
using namespace std;

auto main() -> int {
	auto val = int{ 10 };
    auto a = {val, 3};
    auto b = {val};
    auto c = float{3.4f};
    cout << c << endl;
    cout << a.size() << endl;

    auto v1 = vector<int>(5);
    v1.at(0) = 10;
    auto v2 = vector<int>{5, 10};

    auto f = [](const vector<int> &x) { return x.size(); };
    cout << f(v1) << endl;

    auto d1 = int{54*3};
    cout << d1 << endl;


    return 0;
}
#endif

#if 0
#include <iostream>
using namespace std;

class B {
public:
    int a;
};

class T {
public:
    int a;
    int b;
    B   sb;
};

struct S {
    int a;
    int b;
};

auto main() -> int {

    //auto t = T{};
    // T t{};
    T t;
    cout << t.a << endl;
    cout << t.sb.a << endl;

    decltype(t) tt{};
    cout << tt.a << endl;


    S s{};
    cout << s.a << endl;
    return 0;
}
#endif

#if 0
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cassert>
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main() {
    vector<std::unique_ptr<int>> v;
    v.push_back(std::unique_ptr<int>{new int{10}});
    v.push_back(std::unique_ptr<int>{new int{9}});
    v.push_back(std::unique_ptr<int>{new int{8}});

    // must use reference
    for (auto &i : v) {
        cout << *i << endl;
    }

    return 0;
}
#endif

#if 0
#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <cassert>
using namespace std;

auto main() -> int {
	int t[] = { 3, 4, 2, 1, 6, 5, 7, 9, 8, 0 };
	auto v = vector < int > {t, t + 10};
	assert(v.size() == sizeof(t) / sizeof(t[0]));
	auto s1 = multiset < int > {v.begin(), v.end()};
	assert(s1.size() == sizeof(t) / sizeof(t[0]));

	array<int, 5> a = {0, 1, 2, 3, 4};
	assert(a.size() == 5);
	vector<int> c = { t, t + 10 };
	vector<int> e = { 4, 5 };
	assert(e.size() == 2);

	const int n = 10;
	double aaa[n];
}
#endif

#if 0
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <set>
#include <cassert>
using namespace std;

auto main() -> int {
	set<int> s{};
	assert(s.size() == 0);
	assert(s.empty());
	s = set<int>{1, 2, 3, 4, 5};
	assert(s.size() == 5);
	assert(!s.empty());

	s.insert(0);
	assert(s.size() == 6);

	auto p = s.emplace(6);
	assert(*p.first == 6);
	assert(p.second);

	p = s.emplace(6);
	assert(*p.first == 6);
	assert(!p.second);
	
	for (auto i : s) {
		cout << i << endl;
	}

	auto next = s.erase(begin(s));
	assert(*next == 1);

	// return the number of the removed elements
	assert(1 == s.erase(6));
	assert(0 == s.erase(16));

	auto i = s.find(3);
	assert(*i == 3);

	string str{};
	cout << str.length() << endl;
}
#endif

#if 0
// A. nested function by lambda
// B. Recursive lambda
#include <iostream>
#include <functional>
using namespace std;

int main() {
	// An enclosing function local variable can't be referenced in a lambda boby unless it is in the capture list
	// std::function<void(int)> f = [](int i) {
	// A variable declared with an auto type specifier can't appear in its own initializer
	// auto f = [&](int i) {
	std::function<void(int)> f = [&](int i) {
		cout << i << "\n";
		if (i > 10)
			return;

		f(i + 1);
	};

	f(3);
}
#endif

#if 0
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <cassert>
#include "make_unique.hpp"

int main() {
    auto first = std::unique_ptr<int>{new int{5}};
    auto second = std::unique_ptr<int>{new int{5}};

    // You don't have to qualify the namespace for functions if one or more argument types are
    // defined in the namespace of the function.
    swap(first, second);

    auto c = std::vector<int>{};
    auto d = new std::vector<int>{};

    std::cout << "=======================\n";
    c = {1, 2, 3, 4 ,5};
    assert(c.size() == 5);
    std::for_each(begin(c), end(c), [&c](int i){ std::cout << i << "\n"; });
    std::cout << "=======================\n";
    for (auto i : c) {
        std::cout << i << "\n";
    }

    std::cout << "=======================\n";
    d->push_back(5);
    d->push_back(4);
    d->push_back(3);
    d->push_back(2);
    d->push_back(1);
    assert(d->size() == 5);
    std::for_each(begin(*d), end(*d), [d](int i){ std::cout << i << "\n"; });
    std::cout << "=======================\n";
    d->emplace_back(6);
    for (auto i : *d) {
        std::cout << i << "\n";
    }
    delete d;

    std::cout << "=======================\n";
    auto e = std::unique_ptr<std::vector<int>> {new std::vector<int>{4, 5, 6, 7}};
    for (auto m : *e) {
        std::cout << m << std::endl;
    }

    std::cout << "=======================\n";
    auto f = pg::make_unique<std::vector<int>>(std::initializer_list<int>{5, 6, 7, 8, 9});
    for (auto &v : *f) {
        std::cout << v << std::endl;
    }

    std::cout << "=======================\n";
    auto l = {5, 6, 7, 8, 9};
    auto n = pg::make_unique<std::vector<int>>(l);
    for (auto &v : *n) {
        std::cout << v << std::endl;
    }

    std::cout << "=======================\n";
    auto nn = pg::make_unique<int[]>(4);


    return 0;
}
#endif

#if 0
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <array>
#include <cassert>
using std::cout;
using std::endl;
using std::string;
using std::vector;

template <typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args) {
   return std::unique_ptr<T>(new T{std::forward<Args>(args)...});
}

int main() {
    std::cout << "=======================\n";
    auto f = make_unique<std::vector<int>>(5, 6, 7, 8, 9);
    assert(f->size() == 5);
    std::cout << "=======================\n";
    auto g = make_unique<std::vector<int>>(5, 6);
    assert(g->size() == 2);
    std::cout << "=======================\n";
    auto h = make_unique<std::array<int, 3>>(3, 4, 5);
    assert(h->size() == 3);

    return 0;
}
#endif

#if 0
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <array>
#include <cassert>
#include "optional.hpp"
using std::cout;
using std::endl;
using std::string;
using std::vector;

class Address {
private:
    int a;
    int b;
public:
    Address(int a = 0, int b = 0) : a(a), b(b) {}
    string toString() const {
        return std::to_string(a + b);
    }
};

class Person {
public:
    Person(string firstName, string lastName) : firstName_(firstName), lastName_(lastName) {}
    string firstName_, lastName_;
    pg::optional<string> middleName_;
    pg::optional<vector<string>> childrenNames_;
    pg::optional<Address> adr_;
};

int main() {
    Person p { "Mike", "M" };
    p.middleName_ = "hhh";

    if (p.middleName_) {
        cout << *(p.middleName_) << endl;
    }

    p.middleName_ = "HHH";
    if (p.middleName_.is_initialized()) {
        cout << p.middleName_.get() << endl;
    }

    vector<string> il = { "Yexuan", "Yixuan", "Other"};
    p.childrenNames_ = il;

    if (p.childrenNames_) {
        for (auto v : *(p.childrenNames_)) {
            cout << v << endl;
        }
    }

    auto vv = vector<string>{};
    vv = {"AA", "BB"};
    for (auto v : vv) {
        cout << v << endl;
    }
    vv = {"dd", "bb"};
    for (auto v : vv) {
        cout << v << endl;
    }
// Wrong
//    auto ss = {"bb", "dd"};
//    vv = ss;

    Address adr = {4, 5};
    p.adr_ = adr;

    if (p.adr_) {
        // . has higher priority than *, so "*(p.adr_).toString()" is wrong
        cout << (*p.adr_).toString() << endl;
        cout << (p.adr_)->toString() << endl;
        cout << (p.adr_).get().toString() << endl;
    }

    return 0;
}
#endif

#if 0
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <cassert>

namespace notstd {
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}
int main() {
    auto u = notstd::make_unique<int>(3);
    std::cout << *u << std::endl;

    auto a = std::vector<std::unique_ptr<int>>{};
    a.push_back(notstd::make_unique<int>(10));
    a.push_back(notstd::make_unique<int>(12));
    a.push_back(notstd::make_unique<int>(14));

    for (auto& v : a) {
        std::cout << *v << std::endl;
    }


    return 0;
}
#endif

#if 0
#include <iostream>
#include <cassert>
#include <cstring>
using std::cout;
using std::endl;

#if 00
class String {
public:
    explicit String(const char *str): m_data(new char[strlen(str) + 1]) {
        strcpy(m_data, str);
    }

    String(const String &other): m_data(new char[strlen(other.m_data) + 1]){
        strcpy(m_data, other.m_data);
    }

    /*
    String &operator=(String &other) {
        String l(other);
        std::swap(l.m_data, m_data);
        return *this;
    }
    */

    String &operator=(String other) {
        std::swap(other.m_data, m_data);
        return *this;
    }

    ~String() {
        delete[] m_data;
    }

    char *str() {
        return m_data;
    }

private:
    char *m_data;
    void copy(const char *str) {
        m_data = new char[strlen(str) + 1];
        strcpy(m_data, str);
    }
};
#endif

int main() {
    String a("test");
    String b("hhh");
    a = String("hello");
    a = b;
    String d = String("ttttt");
    std::cout << a.str() << endl;
    std::cout << b.str() << endl;
    std::cout << d.str() << endl;

    return 0;
}
#endif

#if 0
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main() {
    int a, b, c, d;
    a = 10;
    b =a++;
    c=++a;
    d=10*a++;

    cout << b << endl;
    cout << c << endl;
    cout << d << endl;
    return 0;
}
#endif

#if 0
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
using std::cout;
using std::endl;
using std::string;
using std::vector;

class A {
protected:
    int method1(int a, int b) { return 0; }
};

class B: public A {
public:
    int method1(int a, int b) { cout << "1\n"; return 0; }
    // short method1(int a, int b) { cout << "2\n"; return 0; }
private:
    // int method1(int a, long b) { cout << "3\n"; return 0; }
    // int method1(int a, int b) { return 0; }
protected:
    // static int method1(int a, int b) { return 0; }
};

class C: public B {
public:
    int method2(int a, int b) {
        cout << "2-1\n";
        // return method1(a, b);
        return B::method1(a, b);
    }
};

int main() {
    B b;
    // b.method1(3, 4);
    C c;
    c.method2(4, 5);
    return 0;
}
#endif

#if 0
#include <iostream>
#include <cassert>
#include <future>
#include <chrono>
using std::cout;
using std::endl;

int factorial(std::shared_future<int> f) {
    int res = 1;
    int N = f.get();
    for (int i = N; i > 1; --i) {
        res *= i;
    }

    cout << "Result is " << res << endl;
    return res;
}

int main() {
    int x;
    auto p = std::promise<int>{};
    auto f = p.get_future().share();
    std::future<int> fu = std::async(std::launch::async, factorial, f);
    std::future<int> fu2 = std::async(std::launch::async, factorial, f);
    std::this_thread::sleep_for(std::chrono::microseconds(0));
    p.set_value(4);
    x = fu.get();
    cout << x << endl;

    return 0;
}
#endif

#if 0
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

int main() {
    vector<int> vec1 = {8, 9, 9, 10};
    vector<int> vec2 = {7, 9, 10};
    vector<int> vec_out(10); // **** must be big enough to hold the result. As algorithm just operates
                             // iterator, it doesn't know the underlying container and it can't use push_back.
    cout << vec_out.size() << endl;
    cout << vec_out.capacity() << endl;
    auto it = set_difference(vec1.begin(), vec1.end(),
                   vec2.begin(), vec2.end(),
                   vec_out.begin());
    vec_out.resize(it - vec_out.begin());
    for_each(vec_out.begin(), vec_out.end(), [](int x){ cout << x << " "; });
    cout << "\n";
    cout << vec_out.size() << endl;

    cout << "Test unique: ";
    auto it1 = std::unique(vec1.begin(), vec1.end());
    vec1.resize(it1 - vec1.begin());
    for_each(vec1.begin(), vec1.end(), [](int x){ cout << x << " "; });
    cout << "\n";

    string s1 = "123";
    auto ss = stoi(s1);
    ss += 100;
    cout << ss << endl;

    cout << "test endl" << endl << "tttt" << endl;
    cout << setw(8) << std::right << setfill('_') << 99 << endl;

    istreambuf_iterator<char> i(cin);
    ostreambuf_iterator<char> o(cout);
    while (*i != 'x') {
        *o++ = *i++;
    }

//    copy(istreambuf_iterator<char>(cin), istreambuf_iterator<char>(), ostreambuf_iterator<char>(cout));

    stringstream sss;
    sss << 89 << " hex: " << hex << showbase << 89 << endl;
    cout << sss.str() << endl;

    return 0;
}
#endif

#if 0
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

int main() {
    std::vector<int> v1 {1, 2, 5, 5, 5, 9};
    std::vector<int> v2 {2, 5, 7};
    std::vector<int> diff;

    std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(),
                        std::inserter(diff, diff.begin()));

    for (auto i : v1) std::cout << i << ' ';
    std::cout << "minus ";
    for (auto i : v2) std::cout << i << ' ';
    std::cout << "is: ";

    for (auto i : diff) std::cout << i << ' ';
    std::cout << '\n';


}
#endif

#if 0
// set_difference example
#include <iostream>     // std::cout
#include <algorithm>    // std::set_difference, std::sort
#include <vector>       // std::vector

int main () {
    int first[] = {5,10,15,20,25};
    int second[] = {50,40,30,20,10};
    std::vector<int> v(10);                      // 0  0  0  0  0  0  0  0  0  0
    std::vector<int>::iterator it;

    std::sort (first,first+5);     //  5 10 15 20 25
    std::sort (second,second+5);   // 10 20 30 40 50

    it=std::set_difference (first, first+5, second, second+5, v.begin());
    //  5 15 25  0  0  0  0  0  0  0
    v.resize(it-v.begin());                      //  5 15 25

    std::cout << "The difference has " << (v.size()) << " elements:\n";
    for (it=v.begin(); it!=v.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    return 0;
}
#endif

#if 0
#include <iostream>
#include <string>
#include <deque>
#include <cassert>
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
using std::cout;
using std::endl;

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
//    REQUIRE( Factorial(0) == 1 );
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE( "vectors can be sized and resized", "[vector]" ) {

    std::vector<int> v( 5 );

    REQUIRE( v.size() == 5 );
    REQUIRE( v.capacity() >= 5 );

    SECTION( "resizing bigger changes size and capacity" ) {
        v.resize( 10 );

        REQUIRE( v.size() == 10 );
        REQUIRE( v.capacity() >= 10 );
    }
    SECTION( "resizing smaller changes size but not capacity" ) {
        v.resize( 0 );

        REQUIRE( v.size() == 0 );
        REQUIRE( v.capacity() >= 5 );
    }
    SECTION( "reserving bigger changes capacity but not size" ) {
        v.reserve( 10 );

        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 10 );
    }
    SECTION( "reserving smaller does not change size or capacity" ) {
        v.reserve( 0 );

        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 5 );
    }
}

TEST_CASE("deque can be inserted from both directions", "[deque]") {
    std::deque<int> d;
    REQUIRE(d.size() == 0);
    SECTION("insert from the frontend") {
        d.push_front(5);
        REQUIRE(d.front() == 5);
    }
    SECTION("insert from the backend") {
        d.push_back(4);
        REQUIRE(d.back() == 4);

    }
}

SCENARIO("deque can be inserted from the head", "[deque]") {
    GIVEN("A deque") {
        std::deque<int> d;
        WHEN("insert to the head") {
            d.push_front(10);
            THEN("the size should increase 1") {
                REQUIRE(d.size() == 1);
            }
            THEN("the first number is 10") {
                REQUIRE(d.front() == 10);
            }
        }
    }
}

#endif

#if 0
#include <iostream>
#include <cassert>
#include <boost/signals2.hpp>
using std::cout;
using std::endl;

int main() {
    boost::signals2::signal<void()> s;
    s.connect(1, []() { cout << "First" << endl; });
    s.connect(0, []() { cout << "Zero" << endl; });

    s();

    return 0;
}
#endif

#if 0
#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions

int main()
{

    int status;
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.

    // The MAN page of getaddrinfo() states "All  the other fields in the structure pointed
    // to by hints must contain either 0 or a null pointer, as appropriate." When a struct
    // is created in C++, it will be given a block of memory. This memory is not necessary
    // empty. Therefor we use the memset function to make sure all fields are NULL.
    memset(&host_info, 0, sizeof host_info);

    std::cout << "Setting up the structs..."  << std::endl;

    host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
    host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.

    // Now fill up the linked list of host_info structs with google's address information.
    status = getaddrinfo("www.google.com", "80", &host_info, &host_info_list);
    // getaddrinfo returns 0 on succes, or some other value when an error occured.
    // (translated into human readable text by the gai_gai_strerror function).
    if (status != 0)  std::cout << "getaddrinfo error" << gai_strerror(status) ;


    std::cout << "Creating a socket..."  << std::endl;
    int socketfd ; // The socket descripter
    socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
    host_info_list->ai_protocol);
    if (socketfd == -1)  std::cout << "socket error " ;

    std::cout << "Connect()ing..."  << std::endl;
    status = connect(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
    if (status == -1)  std::cout << "connect error" ;


    std::cout << "send()ing message..."  << std::endl;
    char *msg = "GET / HTTP/1.1\nhost: www.google.com\n\n";
    int len;
    ssize_t bytes_sent;
    len = strlen(msg);
    bytes_sent = send(socketfd, msg, len, 0);


    std::cout << "Waiting to recieve data..."  << std::endl;
    ssize_t bytes_recieved;
    char incoming_data_buffer[1000];
    bytes_recieved = recv(socketfd, incoming_data_buffer,1000, 0);
    // If no data arrives, the program will just wait here until some data arrives.
    if (bytes_recieved == 0) std::cout << "host shut down." << std::endl ;
    if (bytes_recieved == -1)std::cout << "recieve error!" << std::endl ;
    std::cout << bytes_recieved << " bytes recieved :" << std::endl ;
    std::cout << incoming_data_buffer << std::endl;

    std::cout << "Receiving complete. Closing socket..." << std::endl;
    freeaddrinfo(host_info_list);
    //close(socketfd);
}
#endif

#if 0
#include <iostream>
#include <cassert>
using std::cout;
using std::endl;

int main() {
    int num = 5;

    int aa[num];
    cout << sizeof(aa)/sizeof(aa[0]) << endl;
    return 0;
}
#endif

#if 0
#include <iostream>
#include <cassert>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Dog {
    int age;
    string name;
public:
    Dog(): age(3), name("dummy") {}
    // 1
    void setAge(const int& a) { cout << "const\n"; age = a; }
    // 2
    void setAge(int& a) { cout << "non-const\n"; age = a; }
};

int main() {
    Dog a{};
    // 1 is called -- "const int& a = 6" is right, "int &a = 6" is wrong
    a.setAge(6);
    int b = 5;
    // 2 is called if it is defined, or 1 is called
    a.setAge(b);
    // Dog() returns a rvalue, and it can be changed too.
    Dog().setAge(40);


    return 0;
}
#endif

#if 0
#include <iostream>
#include <cassert>
using std::cout;
using std::endl;

class MyString {
public:
    MyString() {}
    MyString(const MyString& rhs) {
        cout << "copy constructor\n";
    }

    MyString& operator=(const MyString& rhs) {
        cout << "copy assignment\n";
    }

    MyString& operator=(MyString&& rhs) {
        cout << "move assignment\n";
    }
};

struct Foo {
    MyString name;
};


void foo(const MyString s) {
    cout << "ffff" << endl;
    Foo f;
    // copy assignment is called. As const s can't be moved or casted to rvalue.
    f.name = std::move(s);
}

int main() {
    MyString m;
    foo (m);

    return 0;
}
#endif

#if 0
#include <iostream>
#include <cassert>
using std::cout;
using std::endl;

struct strange {
  size_t count = 0;
  strange() {}
  strange(strange &&o):count(o.count) {
      cout << "move\n";
      o.count = 0;
  }
};

int main() {
    const strange s;
    strange s2 = std::move(s);

    return 0;
}
#endif

#if 0
#include <iostream>
#include <cassert>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;

class Dog {
public:
    ~Dog() { cout << "Dog destroyed\n"; }
    virtual void bark() { cout << "Dog bark\n"; }
};

class YellowDog : public Dog {
public:
    ~YellowDog() { cout << "Yellow dog destroyed\n"; }
    void bark() { cout << "Yellow dog bark\n"; }
};

class DogFactory {
public:
    static shared_ptr<Dog> createYellowDog() {
        return std::make_shared<YellowDog>();
    }
    static void bark(Dog &d) {
        d.bark();
    }
};

int main() {
    {
    // shared_ptr keeps track fo the original destructor to be used in its deleter.
    // unique_ptr doesn't have this ability.
    shared_ptr<Dog> dp = DogFactory::createYellowDog();
    dp->bark();
    }

    {
    cout << "===========================\n";
    YellowDog yd;
    DogFactory::bark(yd);
    }

    return 0;
}
#endif

#if 0
#include <iostream>
#include <cassert>
using std::cout;
using std::endl;

int main() {
    int x = 0;
    auto f1 = [=]() mutable { x = 42; };
    f1();
    cout << "x = " << x << endl;
    auto f2 = [&]() { x = 42; };
    f2();
    cout << "x = " << x << endl;
    // auto f3 = [=]() { x = 42; };

    return 0;
}
#endif

#if 0
#include <iostream>
#include <cassert>
using std::cout;
using std::endl;

template<typename T>                // declaration for TD;
class TD;                           // TD == "Type Displayer"

template<typename T>                // template w/types of interest
void f(T& param) {
    TD<T> tType;                    // cause T to be shown
    TD<decltype(param)> paramType;  // ditto for param's type
}

int main() {
    int x =22;
    const int& rx = x;
    f(rx);

    auto y =rx;
    TD<decltype(y)> yType;
    return 0;
}
#endif

#if 0
#include <iostream>
#include <cassert>
using std::cout;
using std::endl;

template<typename T>
void f(const T& param)
{
    cout << "T =     " << typeid(T).name() << "\n";
    cout << "param = " << typeid(param).name() << "\n";
}

int main() {
    int x =22;
    const int& rx = x;
    f(rx);

    return 0;
}
#endif

#if 0
#include <iostream>
#include <string>
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
using std::string;

string findCircuitExist(string commands) {
    string pattern {};
    for (string::size_type i = 0; i < commands.size(); ++i) {
        if (i == 0) continue;
        if (commands[i] != 'G') {
            if ((commands[i] != 'L') && (commands[i] != 'R')) {
                // Wrong commands
                return string("NO");
            }

            if (commands[0] == 'G') {
                pattern = commands.substr(0, i + 1);
            }
            else {
                pattern = commands.substr(0, i);
            }

            break;
        }
    }

    if (pattern.size() == 0) {
        if ((commands[0] == 'L') || (commands[0] == 'R')) {
            return string("YES");
        } else {
            return string("NO");
        }
    }

    for (string::size_type i = 0; i < commands.size(); i += pattern.size()) {
        if (i == 0) continue;
        if (commands.compare(i, pattern.size(), pattern) != 0) {
            return string("NO");
        }
    }

    return string("YES");
}

TEST_CASE("find circuit exist", "[circuit]") {
    SECTION("a") {
        REQUIRE(findCircuitExist("G") == string("NO"));
        REQUIRE(findCircuitExist("GG") == string("NO"));
    };
    SECTION("b") {
        REQUIRE(findCircuitExist("W") == string("NO"));
        REQUIRE(findCircuitExist("WT") == string("NO"));
    };
    SECTION("c") {
        REQUIRE(findCircuitExist("GGL") == string("YES"));
        REQUIRE(findCircuitExist("GGR") == string("YES"));
        REQUIRE(findCircuitExist("LGG") == string("YES"));
        REQUIRE(findCircuitExist("RGG") == string("YES"));
        REQUIRE(findCircuitExist("LGGL") == string("NO"));
        REQUIRE(findCircuitExist("RGGR") == string("NO"));
    };
    SECTION("d") {
        REQUIRE(findCircuitExist("GGLGGL") == string("YES"));
        REQUIRE(findCircuitExist("GGRGGR") == string("YES"));
        REQUIRE(findCircuitExist("LGGLGG") == string("YES"));
        REQUIRE(findCircuitExist("RGGRGG") == string("YES"));
        REQUIRE(findCircuitExist("GGLGGR") == string("NO"));
        REQUIRE(findCircuitExist("GGRGGL") == string("NO"));
        REQUIRE(findCircuitExist("LGGRGG") == string("NO"));
        REQUIRE(findCircuitExist("RGGLGG") == string("NO"));
        REQUIRE(findCircuitExist("RMGLGG") == string("NO"));
    };
}

#endif

#if 0
#include <iostream>
#include <cassert>
using std::cout;
using std::endl;

template <typename T>
class GenericParser {
public:
    void parserPreorder() {
        processNode();
    }
    void processNode() {
        static_cast<T*>(this)->processNode();
    }
};

class TTT {
//    int a;
//    char c;
//    short d;
public:
    virtual void aaa() = 0;
    virtual void bbb() = 0;
    virtual void ccc() = 0;
    virtual void dcc() = 0;
    virtual void ecc() = 0;
    virtual void fcc() = 0;
};

class EmployeeParser : public GenericParser<EmployeeParser> {
public:
    void processNode() {
        cout << "I am employeeParser processNode\n";
    }
};

int main() {
    EmployeeParser ep;
    ep.parserPreorder();

    cout << sizeof(TTT) << endl;

    return 0;
}
#endif

#if 0
#include <iostream>
#include <cassert>
using std::cout;
using std::endl;

class T {
public:
    static void operator delete(void *m) noexcept {
        cout << "Customized delete of T\n";
//        free(m);
        ::operator delete(m);
    }
    virtual ~T();
};

T::~T() {
    cout << "deconstructor\n";
}

class TT final : public T {
public:
    static void operator delete(void *m) noexcept {
        cout << "Customized delete of TT\n";
//        free(m);
        ::operator delete(m);
    }
};

int main() {
    T *t = new TT();

    delete t;

    return 0;
}
#endif

#if 0
#include <iostream>
#include <regex>
#include <cassert>
using std::cout;
using std::endl;

int main() {
    std::string str;
    bool matched;
    while (1) {
        std::cin >> str;
        // std::regex e("[RL]G*|G*[RL]");
        // std::regex e("[RL]G*", std::regex_constants::icase);
        std::regex e{"(abc)de+\\1"};

        matched = std::regex_match(str, e);

        cout << (matched ? "matched":"not matched") << endl << endl;
    }
}
#endif

#if 0
#include <iostream>
#include <cassert>
#include <type_traits>
using std::cout;
using std::endl;

enum class foo : int {
    bar = 42
};

int main() {
    int underlying = static_cast<int>(foo::bar);
    assert(underlying == 42);

    return 0;
}
#endif

// Open-Closed Principle
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

enum class Color {Green, Red, Blue, White, Black, Puple, Yellow, Orange};
enum class Size {Small, Medium, Big};

struct Product {
    string name;
    Color color;
    Size size;
};

template <typename T>
struct ISpecification {
    virtual bool is_satisfied(T* item) = 0;
};

template <typename T>
struct IFilter {
    virtual vector<T*> filter(vector<T*> items, ISpecification<T>& spec) = 0;
};

struct BetterFilter : IFilter<Product> {
    vector<Product*> filter(vector<Product*> items, ISpecification<Product> &spec) override
    {
        vector<Product*> ret{};
        for (auto& a : items) {
            if (spec.is_satisfied(a)) {
                ret.push_back(a);
            }
        }
        return ret;
    }
};

struct ColorSpecification : ISpecification<Product> {
    Color color;
    explicit ColorSpecification(Color c) : color(c) {}
    bool is_satisfied(Product *item) override {
        return (item->color == color);
    }
};

struct SizeSpecification : ISpecification<Product> {
    Size size;
    explicit SizeSpecification(Size c) : size(c) {}
    bool is_satisfied(Product *item) override {
        return (item->size == size);
    }
};

template <typename T>
struct AndSpecification : ISpecification<T> {
    ISpecification<T>& first;
    ISpecification<T>& second;
    AndSpecification(ISpecification<T>& first, ISpecification<T>& second) : first{first}, second{second} {}
    bool is_satisfied(T *item) override {
        return (first.is_satisfied(item) && second.is_satisfied(item));
    }
};

int main() {
    Product apple = {"Apple", Color::Green, Size::Medium};
    Product book = {"Book", Color::Black, Size::Medium};
    Product tv = {"TV", Color::Black, Size::Big};
    Product car = {"Car", Color::Red, Size::Big};
    vector<Product*> all{&apple, &book, &tv, &car};

    BetterFilter bf;
    ColorSpecification red(Color::Red);
    ColorSpecification black(Color::Black);
    SizeSpecification big(Size::Big);
    AndSpecification<Product> black_big = {black, big};

    auto red_things = bf.filter(all, red);
    for_each(red_things.begin(), red_things.end(), [](Product *p){ cout << p->name << " is red\n"; });

    auto black_big_things = bf.filter(all, black_big);
    for_each(black_big_things.begin(), black_big_things.end(), [](Product *p){ cout << p->name << " is black and big\n"; });


    return 0;
}
#endif

#if 0
#include <iostream>
#include <memory>
#include <cassert>
using std::cout;
using std::endl;

class foo {
public:
    void Func1(int n) {
        num = n;
        cout << "Func1 is called with " << n << endl;
    }
    int num;
};

void (foo::*pFunc1)(int n) = &foo::Func1;
int foo::*pNum = &foo::num;

int main() {
    foo f;
    (f.*pFunc1)(5);
    cout << "num is " << (f.*pNum) << endl;

    foo *p = new foo();
    (p->*pFunc1)(1);
    cout << "num is " << (p->*pNum) << endl;
    delete p;

    std::unique_ptr<foo> u(new foo());
    (u.get()->*pFunc1)(10);
    cout << "num is " << (u.get()->*pNum) << endl;

    return 0;
}
#endif

#if 0
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>
#include <cassert>
using namespace std;

class HtmlElement {
private:
    string name;
    string text;
    vector<HtmlElement> children;
    int indent_size = 2;
    string indentString(int indent) {
        return string(indent_size * indent, ' ');
    }

public:
    HtmlElement(const string& name, const string& text = "") : name(name), text(text) {}
    HtmlElement *addChild(const string& name, const string& text) {
        this->children.emplace_back(name, text);
        return this;
    }

    string str(int indent = 0) {
        ostringstream oss;
        oss << indentString(indent) << "<" << name << ">" << endl;
        if (text.size() > 0) {
            oss << indentString(indent + 1) <<  text <<endl;
        }

        for (auto& c : children) {
            oss << c.str(indent + 1);
        }

        oss << indentString(indent) << "</" << name << ">" << endl;

        return oss.str();
    }

    static HtmlElement buildRoot(const string &name) {
        return HtmlElement(name);
    }
};

int main() {
    auto root = HtmlElement::buildRoot("ul");
    root.addChild("li", "aaaa");
    cout << root.str() << endl;
}

#endif

#if 0
#include <iostream>
#include <cassert>
using std::cout;
using std::endl;

#if 00
void print() {}

template<typename First, typename... T>
void print(First&& f, T&&... t) {
    std::cout << "[" << f << "]";
    print(t...);
}

template<typename... T>
void printValues(T&&... t) {
    print(std::forward<T>(t)...);
    std::cout << std::endl;
}
#else
template<typename T>
int print(T& t) {
    std::cout << "[" << t << "]";
    return 0;
}

template<typename... T>
void printValues(T&&... t) {
    (void)std::initializer_list<int>{print(t)...};
    std::cout << "\n";
}

#endif


int main() {
    printValues("aaa", 3.14159, "ccc");

#if 00
    for (const auto &i : "hello world\n") {
        cout << (int)i << endl;
    }
#else
    const char a[] = "hello world";
    for (const auto &i : a) {
        cout << int(i) << endl;
    }
#endif

    return 0;
}
#endif

#if 0
// copy elision
#include <iostream>

struct C {
  C() {}
  C(const C&) { std::cout << "A copy was made.\n"; }
  C(C&&) { std::cout << "A move was made.\n"; }
};

C f() {
  return C();
}

int main() {
  std::cout << "Hello World!\n";
  C obj = f();
}

#endif

#if 0
// lamda instant call
#include <iostream>
#include <string>
#include <cassert>
using std::cout;
using std::endl;

int main(int argc, const char *[]) {
    const std::string s1 = [&]() {
        switch (argc) {
            case 0: return "0 argument";
            case 1: return "1 argument";
            default: return "Many argument";
        }
    }();

    cout << s1 << endl;

    return s1.size();
}
#endif

#if 0
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include "make_unique.hpp"
using namespace pg;
using std::cout;
using std::endl;

int main() {
    std::vector<std::unique_ptr<int>> v;
    v.push_back(make_unique<int>(50));
    v.emplace_back(make_unique<int>(5));
    for (const auto& a : v) {
        cout << *a << endl;
    }
    return 0;
}
#endif

#if 0
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
using std::cout;
using std::endl;

struct Node : std::enable_shared_from_this<Node> {
    std::vector<std::shared_ptr<Node> > children;
    void addChild(const std::shared_ptr<Node> &c) {
        children.push_back(c);
        c->m_parent = this->shared_from_this();
    }

    std::shared_ptr<Node> getParent() {
        return m_parent.lock();
    }

private:
    std::weak_ptr<Node> m_parent;
};

int main() {
    auto node = std::make_shared<Node>();
    node->addChild(std::make_shared<Node>());
    return 0;
}
#endif

#if 0
#include <iostream>
#include <cassert>
using std::cout;
using std::endl;

int main() {
    int *p = new int(10);
    cout << *p << endl;
    return 0;
}
#endif

#if 0
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
using namespace std;

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(string &S) {
    // write your code in C++11 (g++ 4.8.2)
    std::vector<char> stack = {};

    char a, b;
    for (char &c : S) {
        if ((c == '+') && (stack.size() >= 2)) {
            a = stack.back();
            stack.pop_back();
            b = stack.back();
            stack.pop_back();
            stack.push_back(a+b);
        } else if ((c == '*') && (stack.size() >= 2)) {
            a = stack.back();
            stack.pop_back();
            b = stack.back();
            stack.pop_back();
            stack.push_back(a*b);
        } else if ((c >= '0') && (c <= '9')) {
            stack.push_back(c - '0');
        } else {
            return -1;
        }
    }

    if (stack.size() == 1) {
        return stack.back();
    } else {
        return -1;
    }
}

int main() {
    string s = "13+62*7+*";
    cout << solution(s) << endl;
    return 0;
}
#endif

#if 1
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
using std::cout;
using std::endl;
using std::vector;

int solution(vector<int> &A) {
    // write your code in C++11 (g++ 4.8.2)
    long long result = 0;
    long long result2 = 0;
    std::for_each(A.cbegin(), A.cend(), [&result](int a) {result += a;});

    int zeros = 0;
    vector<int>::size_type i, j;
    for (i = A.size() - 1; i != static_cast<vector<int>::size_type>(-1); --i) {
        result2 = result;
        for (j = 0; j <= i; ++j) {
            if (result2 == 0) {
                zeros += 1;
                if (zeros > 1000000000) {
                    return -1;
                }
            }
            result2 -= A[j];
        }
        result -= A[i];
    }

    return zeros;
}

int main() {
    vector<int> a = {2, -2, 3, 0, 4, -7, 20, -20};
    cout << solution(a) << endl;

    return 0;
}
#endif

#if 0
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
using std::cout;
using std::endl;
using std::vector;

int solution(vector<int> &A) {
    // write your code in C++11 (g++ 4.8.2)
    int zeros = 0;
    size_t i, j;
    for (i = 0; i < A.size(); ++i) {
        long long result = 0;
        for (j = i; j < A.size(); ++j) {
            result += A[j];
            if (result == 0) {
                zeros += 1;
                if (zeros > 1000000000) {
                    return -1;
                }
            }
        }
    }

    return zeros;
}

int main() {
    vector<int> a = {2, -2, 3, 0, 4, -7};
    cout << solution(a) << endl;

    return 0;
}
#endif

// c++ 14 make_unique
#if 0
#include<iostream>
#include<memory>
#include<vector>

int main() {
	std::cout << "===================\n";
	auto u = std::make_unique<int>(10);
	std::cout << "===================\n";
	auto m = std::make_unique<int[]>(3);
	m[0] = 10;
	m[1] = 11;
	m[2] = 14;
	for (size_t i = 0; i < 3; ++i) {
		std::cout << m[i] << std::endl;
	}
	std::cout << "===================\n";
	int b[] = { 1, 4, 6 };
	for (auto v : b) {
		std::cout << v << std::endl;
	}
	std::cout << "===================\n";
	auto a = std::vector<std::unique_ptr<int>>{};
	a.push_back(std::make_unique<int>(10));
	a.push_back(std::make_unique<int>(12));
	a.push_back(std::make_unique<int>(14));
	for (auto& v : a) {
		std::cout << *v << std::endl;
	}
	std::cout << "===================\n";
	auto g = std::unique_ptr<std::vector<int>>{ new std::vector<int>{2, 4, 6, 8} };
	for (auto& v : *g) {
		std::cout << v << std::endl;
	}
	std::cout << "===================\n";
	auto h = std::make_unique<std::vector<int>>(10, 3);
	for (auto& v : *h) {
		std::cout << v << std::endl;
	}
	std::cout << "===================\n";
	auto j = std::make_unique<std::vector<int>>(std::initializer_list<int>{4, 5, 6, 7});
	j->push_back(40);
	for (auto& v : *j) {
		std::cout << v << std::endl;
	}
	std::cout << "===================\n";
	auto l = {4, 5, 6, 7};
	auto k = std::make_unique<std::vector<int>>(l);
	k->push_back(40);
	k->emplace_back(50);
	for (auto& v : *k) {
		std::cout << v << std::endl;
	}

}
#endif
