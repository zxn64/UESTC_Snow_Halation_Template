#align(center + horizon, text(size: 32pt, heading(level: 1, outlined: false,  `UESTC_SNOW_HALATION's TEMPLATE`)))

#pagebreak()
#outline()
#pagebreak()

#counter(page).update(1)
#set page(numbering: "1 / 1")

== 几何

=== cjj

```cpp
#include <bits/stdc++.h>

using namespace std;

using point_t = long double;  //全局数据类型，可修改为 long long 等

constexpr point_t eps = 1e-8;
constexpr long double PI = 3.1415926535897932384l;

// 点与向量
template<typename T>
struct point {
    T x, y;

    point() = default;

    point(T x, T y) : x(x), y(y) {}

    bool operator==(const point &a) const { return (abs(x - a.x) <= eps && abs(y - a.y) <= eps); }

    bool operator<(const point &a) const {
        if (abs(x - a.x) <= eps) return y < a.y - eps;
        return x < a.x - eps;
    }

    bool operator>(const point &a) const { return !(*this < a || *this == a); }

    point operator+(const point &a) const { return {x + a.x, y + a.y}; }

    point operator-(const point &a) const { return {x - a.x, y - a.y}; }

    point operator-() const { return {-x, -y}; }

    point operator*(const T k) const { return {k * x, k * y}; }

    point operator/(const T k) const { return {x / k, y / k}; }

    T operator*(const point &a) const { return x * a.x + y * a.y; }  // 点积
    T operator^(const point &a) const { return x * a.y - y * a.x; }  // 叉积，注意优先级
    int toleft(const point &a) const {
        const auto t = (*this) ^ a;
        return (t > eps) - (t < -eps);
    }  // to-left 测试
    T len2() const { return (*this) * (*this); }  // 向量长度的平方
    T dis2(const point &a) const { return (a - (*this)).len2(); }  // 两点距离的平方

    // 涉及浮点数
    long double len() const { return hypotl(x, y); }  // 向量长度
    long double dis(const point &a) const { return ((*this) - a).len(); }  // 两点距离
    long double ang(const point &a) const {
        return acosl(max(-1.0l, min(1.0l, ((*this) * a) / (len() * a.len()))));
    }  // 向量夹角
    point rot(const long double rad) const {
        return {x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad)};
    }  // 逆时针旋转（给定角度）
    point rot(const long double cosr, const long double sinr) const {
        return {x * cosr - y * sinr, x * sinr + y * cosr};
    }  // 逆时针旋转（给定角度的正弦与余弦）
};

using Point = point<point_t>;

// 极角排序
struct argcmp {
    bool operator()(const Point &a, const Point &b) const {
        const auto quad = [](const Point &a) {
            if (a.y < -eps) return 1;
            if (a.y > eps) return 4;
            if (a.x < -eps) return 5;
            if (a.x > eps) return 3;
            return 2;
        };
        const int qa = quad(a), qb = quad(b);
        if (qa != qb) return qa < qb;
        const auto t = a ^ b;
        if (abs(t) <= eps) return a.len2() < b.len2() - eps;  // 不同长度的向量需要分开
        return t > eps;
    }
};

// 直线
template<typename T>
struct line {
    point<T> p, v;  // p 为直线上一点，v 为方向向量

    bool operator==(const line &a) const { return v.toleft(a.v) == 0 && v.toleft(p - a.p) == 0; }

    int toleft(const point<T> &a) const { return v.toleft(a - p); }  // to-left 测试
    bool operator<(const line &a) const  // 半平面交算法定义的排序
    {
        if (abs(v ^ a.v) <= eps && v * a.v >= -eps) return toleft(a.p) == -1;
        return argcmp()(v, a.v);
    }

    // 涉及浮点数
    point<T> inter(const line &a) const { return p + v * ((a.v ^ (p - a.p)) / (v ^ a.v)); }  // 直线交点
    long double dis(const point<T> &a) const { return abs(v ^ (a - p)) / v.len(); }  // 点到直线距离
    point<T> proj(const point<T> &a) const { return p + v * ((v * (a - p)) / (v * v)); }  // 点在直线上的投影
};

using Line = line<point_t>;

//线段
template<typename T>
struct segment {
    point<T> a, b;

    bool operator<(const segment &s) const { return make_pair(a, b) < make_pair(s.a, s.b); }

    // 判定性函数建议在整数域使用

    // 判断点是否在线段上
    // -1 点在线段端点 | 0 点不在线段上 | 1 点严格在线段上
    int is_on(const point<T> &p) const {
        if (p == a || p == b) return -1;
        return (p - a).toleft(p - b) == 0 && (p - a) * (p - b) < -eps;
    }

    // 判断线段直线是否相交
    // -1 直线经过线段端点 | 0 线段和直线不相交 | 1 线段和直线严格相交
    int is_inter(const line<T> &l) const {
        if (l.toleft(a) == 0 || l.toleft(b) == 0) return -1;
        return l.toleft(a) != l.toleft(b);
    }

    // 判断两线段是否相交
    // -1 在某一线段端点处相交 | 0 两线段不相交 | 1 两线段严格相交
    int is_inter(const segment<T> &s) const {
        if (is_on(s.a) || is_on(s.b) || s.is_on(a) || s.is_on(b)) return -1;
        const line<T> l{a, b - a}, ls{s.a, s.b - s.a};
        return l.toleft(s.a) * l.toleft(s.b) == -1 && ls.toleft(a) * ls.toleft(b) == -1;
    }

    // 点到线段距离
    long double dis(const point<T> &p) const {
        if ((p - a) * (b - a) < -eps || (p - b) * (a - b) < -eps) return min(p.dis(a), p.dis(b));
        const line<T> l{a, b - a};
        return l.dis(p);
    }

    // 两线段间距离
    long double dis(const segment<T> &s) const {
        if (is_inter(s)) return 0;
        return min({dis(s.a), dis(s.b), s.dis(a), s.dis(b)});
    }
};

using Segment = segment<point_t>;

// 多边形
template<typename T>
struct polygon {
    vector<point<T>> p;  // 以逆时针顺序存储

    size_t nxt(const size_t i) const { return i == p.size() - 1 ? 0 : i + 1; }

    size_t pre(const size_t i) const { return i == 0 ? p.size() - 1 : i - 1; }

    // 回转数
    // 返回值第一项表示点是否在多边形边上
    // 对于狭义多边形，回转数为 0 表示点在多边形外，否则点在多边形内
    pair<bool, int> winding(const point<T> &a) const {
        int cnt = 0;
        for (size_t i = 0; i < p.size(); i++) {
            const point<T> u = p[i], v = p[nxt(i)];
            if (abs((a - u) ^ (a - v)) <= eps && (a - u) * (a - v) <= eps) return {true, 0};
            if (abs(u.y - v.y) <= eps) continue;
            const Line uv = {u, v - u};
            if (u.y < v.y - eps && uv.toleft(a) <= 0) continue;
            if (u.y > v.y + eps && uv.toleft(a) >= 0) continue;
            if (u.y < a.y - eps && v.y >= a.y - eps) cnt++;
            if (u.y >= a.y - eps && v.y < a.y - eps) cnt--;
        }
        return {false, cnt};
    }

    // 多边形面积的两倍
    // 可用于判断点的存储顺序是顺时针或逆时针
    T area() const {
        T sum = 0;
        for (size_t i = 0; i < p.size(); i++) sum += p[i] ^ p[nxt(i)];
        return sum;
    }

    // 多边形的周长
    long double circ() const {
        long double sum = 0;
        for (size_t i = 0; i < p.size(); i++) sum += p[i].dis(p[nxt(i)]);
        return sum;
    }
};

using Polygon = polygon<point_t>;

//凸多边形
template<typename T>
struct convex : polygon<T> {
    // 闵可夫斯基和
    convex operator+(const convex &c) const {
        const auto &p = this->p;
        vector<Segment> e1(p.size()), e2(c.p.size()), edge(p.size() + c.p.size());
        vector<point<T>> res;
        res.reserve(p.size() + c.p.size());
        const auto cmp = [](const Segment &u, const Segment &v) { return argcmp()(u.b - u.a, v.b - v.a); };
        for (size_t i = 0; i < p.size(); i++) e1[i] = {p[i], p[this->nxt(i)]};
        for (size_t i = 0; i < c.p.size(); i++) e2[i] = {c.p[i], c.p[c.nxt(i)]};
        rotate(e1.begin(), min_element(e1.begin(), e1.end(), cmp), e1.end());
        rotate(e2.begin(), min_element(e2.begin(), e2.end(), cmp), e2.end());
        merge(e1.begin(), e1.end(), e2.begin(), e2.end(), edge.begin(), cmp);
        const auto check = [](const vector<point<T>> &res, const point<T> &u) {
            const auto back1 = res.back(), back2 = *prev(res.end(), 2);
            return (back1 - back2).toleft(u - back1) == 0 && (back1 - back2) * (u - back1) >= -eps;
        };
        auto u = e1[0].a + e2[0].a;
        for (const auto &v: edge) {
            while (res.size() > 1 && check(res, u)) res.pop_back();
            res.push_back(u);
            u = u + v.b - v.a;
        }
        if (res.size() > 1 && check(res, res[0])) res.pop_back();
        return {res};
    }

    // 旋转卡壳
    // func 为更新答案的函数，可以根据题目调整位置
    template<typename F>
    void rotcaliper(const F &func) const {
        const auto &p = this->p;
        const auto area = [](const point<T> &u, const point<T> &v, const point<T> &w) { return (w - u) ^ (w - v); };
        for (size_t i = 0, j = 1; i < p.size(); i++) {
            const auto nxti = this->nxt(i);
            func(p[i], p[nxti], p[j]);
            while (area(p[this->nxt(j)], p[i], p[nxti]) >= area(p[j], p[i], p[nxti])) {
                j = this->nxt(j);
                func(p[i], p[nxti], p[j]);
            }
        }
    }

    // 凸多边形的直径的平方
    T diameter2() const {
        const auto &p = this->p;
        if (p.size() == 1) return 0;
        if (p.size() == 2) return p[0].dis2(p[1]);
        T ans = 0;
        auto func = [&](const point<T> &u, const point<T> &v, const point<T> &w) {
            ans = max({ans, w.dis2(u), w.dis2(v)});
        };
        rotcaliper(func);
        return ans;
    }

    // 面积前缀和
    vector<T> sum;

    void get_sum() {
        const auto &p = this->p;
        vector <T> a(p.size());
        for (size_t i = 0; i < p.size(); i++) a[i] = p[this->pre(i)] ^ p[i];
        sum.resize(p.size());
        partial_sum(a.begin(), a.end(), sum.begin());
    }

    T query_sum(const size_t l, const size_t r) const {
        const auto &p = this->p;
        if (l <= r) return sum[r] - sum[l] + (p[r] ^ p[l]);
        return sum[p.size() - 1] - sum[l] + sum[r] + (p[r] ^ p[l]);
    }

    T query_sum() const { return sum.back(); }

    // 判断点是否在凸多边形内
    // 复杂度 O(logn)
    // -1 点在多边形边上 | 0 点在多边形外 | 1 点在多边形内
    int is_in(const point<T> &a) const {
        const auto &p = this->p;
        if (p.size() == 1) return a == p[0] ? -1 : 0;
        if (p.size() == 2) return segment<T>{p[0], p[1]}.is_on(a) ? -1 : 0;
        if (a == p[0]) return -1;
        if ((p[1] - p[0]).toleft(a - p[0]) == -1 || (p.back() - p[0]).toleft(a - p[0]) == 1) return 0;
        const auto cmp = [&](const Point &u, const Point &v) { return (u - p[0]).toleft(v - p[0]) == 1; };
        const size_t i = lower_bound(p.begin() + 1, p.end(), a, cmp) - p.begin();
        if (i == 1) return segment<T>{p[0], p[i]}.is_on(a) ? -1 : 0;
        if (i == p.size() - 1 && segment<T>{p[0], p[i]}.is_on(a)) return -1;
        if (segment<T>{p[i - 1], p[i]}.is_on(a)) return -1;
        return (p[i] - p[i - 1]).toleft(a - p[i - 1]) > 0;
    }

    // 凸多边形关于某一方向的极点
    // 复杂度 O(logn)
    // 参考资料：https://codeforces.com/blog/entry/48868
    template<typename F>
    size_t extreme(const F &dir) const {
        const auto &p = this->p;
        const auto check = [&](const size_t i) { return dir(p[i]).toleft(p[this->nxt(i)] - p[i]) >= 0; };
        const auto dir0 = dir(p[0]);
        const auto check0 = check(0);
        if (!check0 && check(p.size() - 1)) return 0;
        const auto cmp = [&](const Point &v) {
            const size_t vi = &v - p.data();
            if (vi == 0) return 1;
            const auto checkv = check(vi);
            const auto t = dir0.toleft(v - p[0]);
            if (vi == 1 && checkv == check0 && t == 0) return 1;
            return checkv ^ (checkv == check0 && t <= 0);
        };
        return partition_point(p.begin(), p.end(), cmp) - p.begin();
    }

    // 过凸多边形外一点求凸多边形的切线，返回切点下标
    // 复杂度 O(logn)
    // 必须保证点在多边形外
    pair<size_t, size_t> tangent(const point<T> &a) const {
        const size_t i = extreme([&](const point<T> &u) { return u - a; });
        const size_t j = extreme([&](const point<T> &u) { return a - u; });
        return {i, j};
    }

    // 求平行于给定直线的凸多边形的切线，返回切点下标
    // 复杂度 O(logn)
    pair<size_t, size_t> tangent(const line<T> &a) const {
        const size_t i = extreme([&](...) { return a.v; });
        const size_t j = extreme([&](...) { return -a.v; });
        return {i, j};
    }
};

using Convex = convex<point_t>;

// 点集的凸包
// Andrew 算法，复杂度 O(nlogn)
Convex convexhull(vector<Point> p) {
    vector<Point> st;
    if (p.empty()) return Convex{st};
    sort(p.begin(), p.end());
    const auto check = [](const vector<Point> &st, const Point &u) {
        const auto back1 = st.back(), back2 = *prev(st.end(), 2);
        return (back1 - back2).toleft(u - back1) <= 0;
    };
    for (const Point &u: p) {
        while (st.size() > 1 && check(st, u)) st.pop_back();
        st.push_back(u);
    }
    size_t k = st.size();
    p.pop_back();
    reverse(p.begin(), p.end());
    for (const Point &u: p) {
        while (st.size() > k && check(st, u)) st.pop_back();
        st.push_back(u);
    }
    st.pop_back();
    return Convex{st};
}

// 圆
struct Circle {
    Point c;
    long double r;

    bool operator==(const Circle &a) const { return c == a.c && abs(r - a.r) <= eps; }

    long double circ() const { return 2 * PI * r; }  // 周长
    long double area() const { return PI * r * r; }  // 面积

    // 点与圆的关系
    // -1 圆上 | 0 圆外 | 1 圆内
    int is_in(const Point &p) const {
        const long double d = p.dis(c);
        return abs(d - r) <= eps ? -1 : d < r - eps;
    }

    // 直线与圆关系
    // 0 相离 | 1 相切 | 2 相交
    int relation(const Line &l) const {
        const long double d = l.dis(c);
        if (d > r + eps) return 0;
        if (abs(d - r) <= eps) return 1;
        return 2;
    }

    // 圆与圆关系
    // -1 相同 | 0 相离 | 1 外切 | 2 相交 | 3 内切 | 4 内含
    int relation(const Circle &a) const {
        if (*this == a) return -1;
        const long double d = c.dis(a.c);
        if (d > r + a.r + eps) return 0;
        if (abs(d - r - a.r) <= eps) return 1;
        if (abs(d - abs(r - a.r)) <= eps) return 3;
        if (d < abs(r - a.r) - eps) return 4;
        return 2;
    }

    // 直线与圆的交点
    vector<Point> inter(const Line &l) const {
        const long double d = l.dis(c);
        const Point p = l.proj(c);
        const int t = relation(l);
        if (t == 0) return vector<Point>();
        if (t == 1) return vector<Point>{p};
        const long double k = sqrt(r * r - d * d);
        return vector<Point>{p - (l.v / l.v.len()) * k, p + (l.v / l.v.len()) * k};
    }

    // 圆与圆交点
    vector<Point> inter(const Circle &a) const {
        const long double d = c.dis(a.c);
        const int t = relation(a);
        if (t == -1 || t == 0 || t == 4) return vector<Point>();
        Point e = a.c - c;
        e = e / e.len() * r;
        if (t == 1 || t == 3) {
            if (r * r + d * d - a.r * a.r >= -eps) return vector<Point>{c + e};
            return vector<Point>{c - e};
        }
        const long double costh = (r * r + d * d - a.r * a.r) / (2 * r * d), sinth = sqrt(1 - costh * costh);
        return vector<Point>{c + e.rot(costh, -sinth), c + e.rot(costh, sinth)};
    }

    // 圆与圆交面积
    long double inter_area(const Circle &a) const {
        const long double d = c.dis(a.c);
        const int t = relation(a);
        if (t == -1) return area();
        if (t < 2) return 0;
        if (t > 2) return min(area(), a.area());
        const long double costh1 = (r * r + d * d - a.r * a.r) / (2 * r * d), costh2 =
                (a.r * a.r + d * d - r * r) / (2 * a.r * d);
        const long double sinth1 = sqrt(1 - costh1 * costh1), sinth2 = sqrt(1 - costh2 * costh2);
        const long double th1 = acos(costh1), th2 = acos(costh2);
        return r * r * (th1 - costh1 * sinth1) + a.r * a.r * (th2 - costh2 * sinth2);
    }

    // 过圆外一点圆的切线
    vector<Line> tangent(const Point &a) const {
        const int t = is_in(a);
        if (t == 1) return vector<Line>();
        if (t == -1) {
            const Point v = {-(a - c).y, (a - c).x};
            return vector<Line>{{a, v}};
        }
        Point e = a - c;
        e = e / e.len() * r;
        const long double costh = r / c.dis(a), sinth = sqrt(1 - costh * costh);
        const Point t1 = c + e.rot(costh, -sinth), t2 = c + e.rot(costh, sinth);
        return vector<Line>{{a, t1 - a},
                            {a, t2 - a}};
    }

    // 两圆的公切线
    vector<Line> tangent(const Circle &a) const {
        const int t = relation(a);
        vector<Line> lines;
        if (t == -1 || t == 4) return lines;
        if (t == 1 || t == 3) {
            const Point p = inter(a)[0], v = {-(a.c - c).y, (a.c - c).x};
            lines.push_back({p, v});
        }
        const long double d = c.dis(a.c);
        const Point e = (a.c - c) / (a.c - c).len();
        if (t <= 2) {
            const long double costh = (r - a.r) / d, sinth = sqrt(1 - costh * costh);
            const Point d1 = e.rot(costh, -sinth), d2 = e.rot(costh, sinth);
            const Point u1 = c + d1 * r, u2 = c + d2 * r, v1 = a.c + d1 * a.r, v2 = a.c + d2 * a.r;
            lines.push_back({u1, v1 - u1});
            lines.push_back({u2, v2 - u2});
        }
        if (t == 0) {
            const long double costh = (r + a.r) / d, sinth = sqrt(1 - costh * costh);
            const Point d1 = e.rot(costh, -sinth), d2 = e.rot(costh, sinth);
            const Point u1 = c + d1 * r, u2 = c + d2 * r, v1 = a.c - d1 * a.r, v2 = a.c - d2 * a.r;
            lines.push_back({u1, v1 - u1});
            lines.push_back({u2, v2 - u2});
        }
        return lines;
    }

    // 圆的反演
    tuple<int, Circle, Line> inverse(const Line &l) const {
        const Circle null_c = {{0.0, 0.0}, 0.0};
        const Line null_l = {{0.0, 0.0},
                             {0.0, 0.0}};
        if (l.toleft(c) == 0) return {2, null_c, l};
        const Point v = l.toleft(c) == 1 ? Point{l.v.y, -l.v.x} : Point{-l.v.y, l.v.x};
        const long double d = r * r / l.dis(c);
        const Point p = c + v / v.len() * d;
        return {1, {(c + p) / 2, d / 2}, null_l};
    }

    tuple<int, Circle, Line> inverse(const Circle &a) const {
        const Circle null_c = {{0.0, 0.0}, 0.0};
        const Line null_l = {{0.0, 0.0},
                             {0.0, 0.0}};
        const Point v = a.c - c;
        if (a.is_in(c) == -1) {
            const long double d = r * r / (a.r + a.r);
            const Point p = c + v / v.len() * d;
            return {2, null_c, {p, {-v.y, v.x}}};
        }
        if (c == a.c) return {1, {c, r * r / a.r}, null_l};
        const long double d1 = r * r / (c.dis(a.c) - a.r), d2 = r * r / (c.dis(a.c) + a.r);
        const Point p = c + v / v.len() * d1, q = c + v / v.len() * d2;
        return {1, {(p + q) / 2, p.dis(q) / 2}, null_l};
    }
};

// 圆与任意多边形面积交
long double area_inter(const Circle &circ, const Polygon &poly) {
    const auto cal = [](const Circle &circ, const Point &a, const Point &b) {
        if ((a - circ.c).toleft(b - circ.c) == 0) return 0.0l;
        const auto ina = circ.is_in(a), inb = circ.is_in(b);
        const Line ab = {a, b - a};
        if (ina && inb) return ((a - circ.c) ^ (b - circ.c)) / 2;
        if (ina && !inb) {
            const auto t = circ.inter(ab);
            const Point p = t.size() == 1 ? t[0] : t[1];
            const long double ans = ((a - circ.c) ^ (p - circ.c)) / 2;
            const long double th = (p - circ.c).ang(b - circ.c);
            const long double d = circ.r * circ.r * th / 2;
            if ((a - circ.c).toleft(b - circ.c) == 1) return ans + d;
            return ans - d;
        }
        if (!ina && inb) {
            const Point p = circ.inter(ab)[0];
            const long double ans = ((p - circ.c) ^ (b - circ.c)) / 2;
            const long double th = (a - circ.c).ang(p - circ.c);
            const long double d = circ.r * circ.r * th / 2;
            if ((a - circ.c).toleft(b - circ.c) == 1) return ans + d;
            return ans - d;
        }
        const auto p = circ.inter(ab);
        if (p.size() == 2 && Segment{a, b}.dis(circ.c) <= circ.r + eps) {
            const long double ans = ((p[0] - circ.c) ^ (p[1] - circ.c)) / 2;
            const long double th1 = (a - circ.c).ang(p[0] - circ.c), th2 = (b - circ.c).ang(p[1] - circ.c);
            const long double d1 = circ.r * circ.r * th1 / 2, d2 = circ.r * circ.r * th2 / 2;
            if ((a - circ.c).toleft(b - circ.c) == 1) return ans + d1 + d2;
            return ans - d1 - d2;
        }
        const long double th = (a - circ.c).ang(b - circ.c);
        if ((a - circ.c).toleft(b - circ.c) == 1) return circ.r * circ.r * th / 2;
        return -circ.r * circ.r * th / 2;
    };

    long double ans = 0;
    for (size_t i = 0; i < poly.p.size(); i++) {
        const Point a = poly.p[i], b = poly.p[poly.nxt(i)];
        ans += cal(circ, a, b);
    }
    return ans;
}

// 半平面交
vector<Line> _halfinter(vector<Line> l) {
    constexpr double LIM = 1e9;
    const auto check = [](const Line &a, const Line &b, const Line &c) { return a.toleft(b.inter(c)) < 0; };
    // const auto check=[](const Line &a,const Line &b,const Line &c)
    // {
    //     const Point p=a.v*(b.v^c.v),q=b.p*(b.v^c.v)+b.v*(c.v^(b.p-c.p))-a.p*(b.v^c.v);
    //     return p.toleft(q)<0;
    // };
    l.push_back({{-LIM, 0},
                 {0,    -1}});
    l.push_back({{0, -LIM},
                 {1, 0}});
    l.push_back({{LIM, 0},
                 {0,   1}});
    l.push_back({{0,  LIM},
                 {-1, 0}});
    sort(l.begin(), l.end());
    deque <Line> q;
    for (size_t i = 0; i < l.size(); i++) {
        if (i > 0 && l[i - 1].v.toleft(l[i].v) == 0 && l[i - 1].v * l[i].v > eps) continue;
        while (q.size() > 1 && check(l[i], q.back(), q[q.size() - 2])) q.pop_back();
        while (q.size() > 1 && check(l[i], q[0], q[1])) q.pop_front();
        q.push_back(l[i]);
    }
    while (q.size() > 1 && check(q[0], q.back(), q[q.size() - 2])) q.pop_back();
    while (q.size() > 1 && check(q.back(), q[0], q[1])) q.pop_front();
    if (q.size() <= 2) return vector<Line>();
    return vector<Line>(q.begin(), q.end());
}

Convex halfinter(const vector<Line> &l) {
    const auto lines = _halfinter(l);
    Convex poly;
    poly.p.resize(lines.size());
    if (lines.empty()) return poly;
    for (size_t i = 0; i < lines.size(); i++) {
        const size_t j = (i == lines.size() - 1 ? 0 : i + 1);
        poly.p[i] = lines[i].inter(lines[j]);
    }
    poly.p.erase(unique(poly.p.begin(), poly.p.end()), poly.p.end());
    if (poly.p.front() == poly.p.back()) poly.p.pop_back();
    return poly;
}

pair<point_t, point_t> minmax_triangle(const vector<Point> &vec) {
    if (vec.size() <= 2) return {0, 0};
    vector <pair<int, int>> evt;
    evt.reserve(vec.size() * vec.size());
    point_t maxans = 0, minans = numeric_limits<point_t >::max();
    for (size_t i = 0; i < vec.size(); i++) {
        for (size_t j = 0; j < vec.size(); j++) {
            if (i == j) continue;
            if (vec[i] == vec[j]) minans = 0;
            else evt.push_back({i, j});
        }
    }
    sort(evt.begin(), evt.end(), [&](const pair<int, int> &u, const pair<int, int> &v) {
        const Point du = vec[u.second] - vec[u.first], dv = vec[v.second] - vec[v.first];
        return argcmp()({du.y, -du.x}, {dv.y, -dv.x});
    });
    vector <size_t> vx(vec.size()), pos(vec.size());
    for (size_t i = 0; i < vec.size(); i++) vx[i] = i;
    sort(vx.begin(), vx.end(), [&](int x, int y) { return vec[x] < vec[y]; });
    for (size_t i = 0; i < vx.size(); i++) pos[vx[i]] = i;
    for (auto [u, v]: evt) {
        const size_t i = pos[u], j = pos[v];
        const size_t _i = min(i, j), _j = max(i, j);
        const Point vecu = vec[u], vecv = vec[v];
        if (_i > 0) minans = min(minans, abs((vec[vx[_i - 1]] - vecu) ^ (vec[vx[_i - 1]] - vecv)));
        if (_j < vx.size() - 1) minans = min(minans, abs((vec[vx[_j + 1]] - vecu) ^ (vec[vx[_j + 1]] - vecv)));
        maxans = max({maxans, abs((vec[vx[0]] - vecu) ^ (vec[vx[0]] - vecv)),
                      abs((vec[vx.back()] - vecu) ^ (vec[vx.back()] - vecv))});
        if (i < j) swap(vx[i], vx[j]), pos[u] = j, pos[v] = i;
    }
    return {minans, maxans};
}```
