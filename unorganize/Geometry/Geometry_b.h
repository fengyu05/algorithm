/********************************************************************
* geometry.h
* INFO : COMPUTATIONAL GEOMETRY ROUTINES
********************************************************************/


#include <cmath>

typedef double TYPE;

#define Abs(x)      (((x)>0)?(x):(-(x)))
#define Sgn(x)      (((x)<0)?(-1):(1))
#define Max(a,b)   (((a)>(b))?(a):(b))
#define Min(a,b)   (((a)<(b))?(a):(b))

#define Epsilon      1e-10
#define Infinity   1e+20
#define Pi         3.14159265358979323846

TYPE Deg2Rad(TYPE deg)
{
   return (deg * Pi / 180.0);
}

TYPE Sin(TYPE deg)
{
   return sin(Deg2Rad(deg));
}

TYPE Cos(TYPE deg)
{
   return cos(Deg2Rad(deg));
}

struct POINT
{
   TYPE x,y;
   POINT(TYPE x=0, TYPE y=0) : x(x), y(y){};
};

struct LINE
{
   POINT a,b;
   LINE() {};
   LINE(POINT a, POINT b) : a(a), b(b) {};
};

void Coefficient(const LINE & L, TYPE & A, TYPE & B, TYPE & C)
{
   A = L.b.y - L.a.y;
   B = L.a.x - L.b.x;
   C = L.b.x * L.a.y - L.a.x * L.b.y;
}

void Coefficient(const POINT & p, TYPE a, TYPE & A, TYPE & B, TYPE & C)
{
   TYPE sinA = Sin(a), cosA = Cos(a);
   A = cosA, B = sinA;
   C = - (p.y * sinA + p.x * cosA);
}

// line segment
struct SEG
{
   POINT a,b;
   SEG() {};
   SEG(POINT a, POINT b):a(a),b(b) {};
};

// circle
struct CIRCLE
{
   TYPE x, y, r;
   CIRCLE() {}
   CIRCLE(TYPE x, TYPE y, TYPE r) : x(x), y(y), r(r) {}
};

POINT Center(const CIRCLE & circle)
{
   return POINT(circle.x, circle.y);
}

// polygon
struct POLY
{
   int n;
   TYPE * x;
   TYPE * y;
   POLY() : n(0), x(NULL), y(NULL) {};
   POLY(int _n_, const TYPE * x, const TYPE * y)
   {
      n = _n_;
      
      x = new TYPE[n + 1];
      memcpy(x, x, n*sizeof(TYPE));
      x[n] = x[0];

      y = new TYPE[n + 1];
      memcpy(y, y, n*sizeof(TYPE));
      y[n] = y[0];
   }
};

POINT Vertex(const POLY & poly, int idx)
{
   idx %= poly.n;
   return POINT(poly.x[idx], poly.y[idx]);
}

SEG Edge(const POLY & poly, int idx)
{
   idx %= poly.n;
   return SEG(POINT(poly.x[idx], poly.y[idx]),
            POINT(poly.x[idx + 1], poly.y[idx + 1]));
}

TYPE Perimeter(const POLY & poly)
{
   TYPE p = 0.0;
   for (int i = 0; i < poly.n; i++)
   {
      p = p + Distance(Vertex(poly, i), Vertex(poly, i + 1));
   }
   return p;
}

// cross product of (o->a) and (o->b)
TYPE Cross(const POINT & a, const POINT & b, const POINT & o)
{
   return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}

// planar points' distance
TYPE Distance(const POINT & a, const POINT & b)
{
   return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}


// planar lines' distance
TYPE Distance(const LINE & L, const POINT & p)
{
   TYPE dist = 0.0;
   if (!IsOnline(L, p))
   {
      TYPE X[] = {p.x, L.a.x, L.b.x, p.x};
      TYPE Y[] = {p.y, L.a.y, L.b.y, p.y};
      POLY poly(3, X, Y);
      dist = 2.0 * Abs(Area(poly)) / Distance(L.a, L.b);
      delete [] poly.x;
      delete [] poly.y;
   }
   return dist;
}

bool IsEqual(TYPE a, TYPE b)
{
   return (Abs(a - b) < Epsilon);
}

bool IsEqual(const POINT & a, const POINT & b)
{
   return (IsEqual(a.x, b.x) && IsEqual(a.y, b.y));
}

bool IsEqual(const LINE & A, const LINE & B)
{
   TYPE A1, B1, C1;
   TYPE A2, B2, C2;

   Coefficient(A, A1, B1, C1);
   Coefficient(B, A2, B2, C2);

   return (A1 * B2 == A2 * B1) && (A1 * C2 == A2 * C1);
}

// test point on line segment
bool IsOnline(const SEG & seg, const POINT & p)
{
   return (IsEqual(p, seg.a) || IsEqual(p, seg.b)) ||
         (((p.x - seg.a.x) * (p.x - seg.b.x) < 0 ||
          (p.y - seg.a.y) * (p.y - seg.b.y) < 0) &&
           (IsEqual(Cross(seg.b, p, seg.a), 0)));
}

bool IsIntersect(const SEG & u, const SEG & v)
{
   return (Cross(v.a, u.b, u.a) * Cross(u.b, v.b, u.a) >= 0) &&
          (Cross(u.a, v.b, v.a) * Cross(v.b, u.b, v.a) >= 0) &&
          (Max(u.a.x, u.b.x) >= Min(v.a.x, v.b.x)) &&
          (Max(v.a.x, v.b.x) >= Min(u.a.x, u.b.x)) &&
          (Max(u.a.y, u.b.y) >= Min(v.a.y, v.b.y)) &&
          (Max(v.a.y, v.b.y) >= Min(u.a.y, u.b.y));
}

bool IsParallel(const LINE & A, const LINE & B)
{
   TYPE A1, B1, C1;
   TYPE A2, B2, C2;

   Coefficient(A, A1, B1, C1);
   Coefficient(B, A2, B2, C2);

   return (A1 * B2 == A2 * B1) &&
         ((A1 * C2 != A2 * C1) || (B1 * C2 != B2 * C1));
}

bool IsIntersect(const LINE & A, const LINE & B)
{
   return !IsParallel(A, B);
}

POINT Intersection(const LINE & A, const LINE & B)
{
   TYPE A1, B1, C1;
   TYPE A2, B2, C2;

   Coefficient(A, A1, B1, C1);
   Coefficient(B, A2, B2, C2);

   POINT I(0, 0);

   I.x = - (B2 * C1 - B1 * C2) / (A1 * B2 - A2 * B1);
   I.y =   (A2 * C1 - A1 * C2) / (A1 * B2 - A2 * B1);

   return I;
}

bool IsSimple(const POLY & poly)
{
   if (poly.n < 3)
   {
      return false;
   }
   SEG L1, L2;
   for (int i = 0; i < poly.n - 1; i++)
   {
      L1 = Edge(poly, i);
      for (int j = i + 1; j < poly.n; j++)
      {
         L2 = Edge(poly, j);
         if (j == i + 1)
         {
            if (IsOnline(L1, L2.b) || IsOnline(L2, L1.a)) {
               return false;
            }
         }
         else if (j == poly.n - i - 1)
         {
            if (IsOnline(L1, L2.a) || IsOnline(L2, L1.b)) {
               return false;
            }
         }
         else
         {
            if (IsIntersect(L1, L2)) {
               return false;
            }
         }
      } // for j
   } // for i
   return true;
}

TYPE Area(const POLY & poly)
{
   if (poly.n < 3) return TYPE(0);
   double s = poly.y[0] * (poly.x[poly.n - 1] - poly.x[1]);
   for (int i = 1; i < poly.n; i++)
   {
      s += poly.y[i] * (poly.x[i - 1] - poly.x[(i + 1) % poly.n]);
   }
   return s/2;
}

bool IsOnPoly(const POLY & poly, const POINT & p)
{
   for (int i = 0; i < poly.n; i++)
   {
      if (IsOnline(Edge(poly, i), p))
      {
         return true;
      }
   }
   return false;
}

bool IsInPoly(const POLY & poly, const POINT & p)
/*
 1. count = 0;
 2. 以P为端点, 作从右向左的射线L;
 3, for 多边形的每条边s
 4.      if P在边s上 then
 5.         return true;
 6.      end if
 7.      if s不是水平的 then
 8.         if s的一个端点在L上且该端点是s两端点中纵坐标较大的端点 then
 9.            count = count + 1
10.         else if s和L相交(两条线段都分布在对方的两侧) then
11.            count = count + 1;
12.      end if
13. next
14. if count % 2 == 1 then
15.      return true;
16.   else
17.      return false;
18. end if
*/
{
   SEG L(p, POINT(Infinity, p.y));

   int count = 0;
   for (int i = 0; i < poly.n; i++)
   {
      SEG S = Edge(poly, i);
      if (IsOnline(S, p))
      {
         return true;
      }
      if (!IsEqual(S.a.y, S.b.y))
      {
         POINT & q = (S.a.y > S.b.y)?(S.a):(S.b);
         if (IsOnline(L, q))
         {
            ++count;
         }
         else if (!IsOnline(L, S.a) && !IsOnline(L, S.b) && IsIntersect(S, L))
         {
            ++count;
         }
      }
   }
   return (count % 2 != 0);
}

// convex hull of point set
POLY ConvexHull(const POINT * set, int n)
{
   POLY poly;

   return poly;
}

#endif