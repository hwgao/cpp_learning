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
#if 1
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

#if 1
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
