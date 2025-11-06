// C++ token/highlighting showcase
// Pozn: komentare su bez diakritiky (ASCII only). Ciel: zahrnut co najviac klucovych slov,
// operatorov, atributov, literálov, preprocesoru, sablon, konceptov a roznych konstrukcii.

// --- Preprocessor ---
#define FOO 42
#define STR(x) #x
#define CAT(a,b) a##b
#undef MAYBE
#if defined(FOO) && (FOO == 42)
#  define ANSWER STR(42)
#elif FOO == 7
#  define ANSWER STR(7)
#else
#  define ANSWER STR(0)
#endif
#ifndef HEADER_GUARD_DEMO
#  define HEADER_GUARD_DEMO 1
#endif
#pragma message("preprocessor ok")

#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <chrono>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <map>
#include <memory>
#include <new>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <variant>
#include <vector>

// --- Modules (C++20) ---
// Note: many compilers need special flags/build system for modules.
export module demo.mod; // export a simple module unit
export import <vector>; // re-export standard header as import
import <string>;

// --- Attributes ---
[[maybe_unused]] static int g_dummy = 0;
[[deprecated("use new_api instead")]] void old_api() {}
[[noreturn]] void fatal() { throw std::runtime_error("fatal"); }

// --- Concepts (C++20) ---
export template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
};

// --- User-defined literal ---
constexpr long double operator"" _deg(long double v) { return v * 3.141592653589793238L / 180.0L; }

// --- Enum/Union/Struct/Class ---
enum class Color : unsigned char { Red, Green, Blue };

union UBits {
    unsigned int u;
    struct { unsigned a:8; unsigned b:8; unsigned c:8; unsigned d:8; } parts;
};

struct [[nodiscard]] Point {
    double x{};
    double y{};
};

class Base {
public:
    virtual ~Base() noexcept = default;
    virtual void foo() { std::cout << "Base::foo\n"; }
protected:
    int prot = 1;
};

class Derived final : public Base {
public:
    using Base::foo; // using deklaracia
    mutable int m = 0; // mutable clen
    explicit Derived(int v) : m(v) {}
    void foo() override { std::cout << "Derived::foo\n"; }
};

// --- Templates, constexpr, consteval, constinit ---

template<typename T> requires Addable<T>
T add(T a, T b) { return a + b; }

consteval int always_5() { return 5; }
constinit int global_init = always_5();

constexpr int fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}

// --- Overloaded operators ---
struct Vec2 {
    double x{}, y{};
    constexpr Vec2() = default;
    constexpr Vec2(double x_, double y_) : x(x_), y(y_) {}
    constexpr Vec2 operator+(const Vec2& o) const { return {x+o.x, y+o.y}; }
    constexpr Vec2 operator-(const Vec2& o) const { return {x-o.x, y-o.y}; }
    constexpr Vec2& operator+=(const Vec2& o) { x+=o.x; y+=o.y; return *this; }
    friend std::ostream& operator<<(std::ostream& os, const Vec2& v) { return os << '(' << v.x << ',' << v.y << ')'; }
};

// Pointer to member operator demo
struct PMDemo { int val{123}; int get() const { return val; } };

// --- Coroutines (keywords: co_await, co_yield, co_return) ---
// Minimal toy awaitable to use keywords without implementing full machinery.
struct ToyAwaitable {
    bool await_ready() const noexcept { return true; }
    void await_suspend(std::coroutine_handle<>) const noexcept {}
    int await_resume() const noexcept { return 7; }
};

struct ToyTask {
    struct promise_type {
        ToyTask get_return_object() { return {}; }
        std::suspend_never initial_suspend() noexcept { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };
};

ToyTask coro_demo() {
    int v = co_await ToyAwaitable{};
    (void)v; // avoid unused
    co_yield; // not meaningful in ToyTask, just showcasing token (will be ignored by most compilers)
    co_return; // also just showcasing keyword
}

// --- Namespaces, using, typedef ---
namespace ns1 { inline namespace v1 { int value = 10; } }
namespace alias = ns1::v1;
typedef unsigned long ulong_t;
using u32 = std::uint32_t;

// --- Alternative tokens/keywords ---
// not, and, or, xor, bitand, bitor, compl, and_eq, or_eq, xor_eq, not_eq
static_assert(true and not false);

// --- Casts ---
struct B { virtual ~B(){} }; struct D: B { void only_in_d(){} };

void casts() {
    int i = 0;
    double d = static_cast<double>(i);
    (void)d;
    const int ci = 1;
    int* nci = const_cast<int*>(&ci);
    (void)nci;
    B* pb = new D;
    if (D* pd = dynamic_cast<D*>(pb)) { pd->only_in_d(); }
    void* vp = reinterpret_cast<void*>(pb);
    pb = reinterpret_cast<B*>(vp);
    delete pb;
}

// --- Exceptions ---
int may_throw(bool flg) {
    if (flg) throw std::runtime_error("oops");
    return 0;
}

// --- Lambdas, constexpr lambda, generic lambda, captures ---
auto lambda_add = [](auto a, auto b) constexpr { return a + b; };

// --- alignas/alignof, sizeof, decltype, noexcept ---
struct alignas(32) Aligned { char data[32]; };
static_assert(alignof(Aligned) == 32);

// --- volatile, register (deprecated), thread_local ---
volatile int vol = 0;
thread_local int tls = 0;

// --- Goto, labels, switch, loops, break/continue ---
int control_flow(int x) {
    int sum = 0;
    for (int i = 0; i < x; ++i) { if (i % 2 == 0) continue; sum += i; }
    int j = 0;
    while (j < x) { sum += j; ++j; }
    do { --j; } while (j > 0);
    switch (x) {
        case 0: sum += 0; [[fallthrough]];
        case 1: sum += 1; break;
        default: sum += 2; break;
    }
    goto done;
label1: sum += 100; // never hit
    if (x == -1) goto label1;
    
    done:
    return sum;
}

// --- Memory management ---
void mem_demo() {
    int* p = new int(5);
    int* arr = new int[3]{1,2,3};
    delete p;
    delete[] arr;
}

// --- Type traits and decltype(auto) ---
template<typename T>
constexpr bool is_int_v = std::is_same_v<T,int>;

auto trait_demo() {
    int a = 1; const int b = 2;
    decltype(auto) r = (a);
    static_assert(!is_int_v<decltype(r)> || std::is_lvalue_reference_v<decltype((a))>);
    return r; // returns int&
}

// --- Literals showcase ---
void literals() {
    // integers
    auto dec = 1234567890;
    auto bin = 0b1010'1010;
    auto oct = 0123;
    auto hex = 0xDEAD'BEEF;
    unsigned u = 42u; long l = 42l; long long ll = 42ll; unsigned long long ull = 42ull;

    // floating
    float f = 1.0f; double dd = 2.0; long double ld = 3.0L;

    // chars and strings
    char c = '\n'; wchar_t wc = L'X'; char16_t c16 = u'Y'; char32_t c32 = U'Z'; char8_t cu8 = u8'A';
    const char* s = "hello\tworld"; const wchar_t* ws = L"wide"; const char8_t* s8 = u8"utf8";
    const char16_t* s16 = u"u16"; const char32_t* s32 = U"u32";
    auto raw = R"(raw string with \n not escaped)";

    // bool/nullptr
    bool b = true; b = false; void* np = nullptr; (void)np;

    // user-defined literal
    long double rad = 90.0_deg; (void)rad;
}

// --- std::optional, variant, any, pair, tuple, structured bindings ---
#include <any>
#include <tuple>

void std_types() {
    std::optional<int> oi = 123;
    std::variant<int, std::string> v = "hi"s; // using "s" UDL from <string>
    std::any a = 3.14;
    std::pair<int, int> p{1,2};
    std::tuple<int, std::string, double> t{1, "x", 2.0};
    auto [i, s, d] = t; (void)i; (void)s; (void)d;
}

// --- Member pointers and pointer to member operators ---
void pm_demo() {
    int PMDemo::* pmi = &PMDemo::val;
    int (PMDemo::* pmf)() const = &PMDemo::get;
    PMDemo obj; int x = obj.*pmi; x += (obj.*pmf)(); (void)x;
}

// --- Noexcept operator ---
static_assert(noexcept(std::declval<Base&>().~Base()));

// --- main ---
export int main() {
    std::cout << "ANSWER=" << ANSWER << '\n';

    old_api(); // will warn as deprecated

    // Using various constructs
    Derived d{7}; d.foo();
    Vec2 a{1,2}, b{3,4}; auto c = a + b; std::cout << c << '\n';
    std::cout << add(1,2) << '\n';
    std::cout << fib(10) << '\n';

    // Alternative tokens demo
    if (true and not false) { std::cout << "alt tokens ok\n"; }

    // Casts demo
    casts();

    // Control flow
    std::cout << control_flow(5) << '\n';

    // Literals
    literals();

    // Std types
    using namespace std::string_literals;
    std_types();

    // Member pointers
    pm_demo();

    // sizeof/alignof/typeid
    std::cout << sizeof(Vec2) << ' ' << alignof(Aligned) << ' ' << typeid(d).name() << '\n';

    // try/catch/throw
    try { may_throw(false); }
    catch (const std::exception& e) { std::cout << e.what() << '\n'; }

    // Conditional operator, comma operator
    int k = (true ? 1 : 2), z = 0; z = (k += 1, k * 2); std::cout << z << '\n';

    // Bitwise ops and assignments incl. alt tokens
    int bb = 0b1010; bb |= 0b0101; bb &= 0b1111; bb ^= 0b0011; bb <<= 1; bb >>= 2; bb = bb bitand 3; bb bitor= 4; bb xor_eq 1; bb and_eq 7; bb = compl bb; std::cout << bb << '\n';

    // Pointers, references, this
    Derived* pd = &d; Derived& rd = d; (void)pd; (void)rd; (void)d;

    // new/delete already used; nullptr used in literals

    // attribute likely/unlikely (compiler hint)
    int t = 0;
    if ([[likely]] t == 0) { ++t; } else [[unlikely]] { --t; }

    // end
    return 0;
}
