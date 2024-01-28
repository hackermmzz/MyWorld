#ifndef VEC_H
#define VEC_H
#include"stdint.h"
#include<math.h>
#include<iostream>
///////////////////////////////////////////
///////////////////////////////////////VecBase
template<class T>struct VecBase;
#define VecBaseData(vecbase,T) ((T*)(vecbase))
#define VecBaseDataIndex(vecbase,T,index) VecBaseData(vecbase,T)[index]
/////////////////////////////////////////
using Uint = unsigned int;
template<class T, Uint Dimensions>struct Vec:VecBase<Vec<T,Dimensions>>
{
private:
    T data[Dimensions];
public:
    using Base = VecBase<Vec<T, Dimensions>>;
    Vec():Base(){};
    Vec(const T& val) :Base(val) {}
    template<class...Arg>
    Vec(const T& val, const Arg&...arg) : Base(val, arg...) {}
    template<Uint N, class...Arg>
    Vec(const Vec<T, N>& v, const Arg&...arg) : Base(v, arg...) {}
    ~Vec() {}
};
/// ///////////////////////////////////////
template<class T, Uint N>struct VecBase<Vec<T, N>>{
    VecBase();
    VecBase(const T& val);
    template<class...Arg>
    VecBase(const T& val, const Arg&...arg);
    template<Uint D,class...Arg>
    VecBase(const Vec<T, D>& vec, const Arg&...arg);
    T* value_ptr();
    T get(Uint index)const;
    T& operator[](Uint i);
    T distance() const;
    Vec <T, N> normalize() const;
    T dot(const Vec <T, N>& v) const;
    bool equal(const Vec <T, N>& v) const;
    Vec <T, N> copy()const;
    Vec <T, N> mix(const Vec <T, N>&v,float factor);
    Vec <T, N> floor()const;
    bool operator==(const Vec <T,N>& v);
    Vec <T, N>& operator=(const Vec <T, N>& v);
    Vec <T, N> operator*(const Vec <T, N>& v) const;
    void operator*=(const Vec <T, N>& v);
    Vec <T, N> operator+(const Vec <T, N>& v) const;
    void operator+=(const Vec <T, N>& v);
    Vec <T, N> operator/(const T& v) const;
    Vec <T, N> operator/(const Vec <T, N>& v) const;
    void operator/=(const Vec <T, N>& v);
    Vec <T, N> operator-(const Vec <T, N>& v) const;
    void operator-=(const Vec <T, N>& v);
    friend std::ostream& operator<<(std::ostream& os, const Vec<T, N>&v) {
        for (int i = 0; i < N; ++i)os<<v.get(i) <<" ";
        return os;
    }
protected:
    template<class...Arg>
    void PUSH(Uint index,const T& val, const Arg&...arg);
    void PUSH(Uint index);
};

template<class T, Uint N>
Vec<T, N> VecBase<Vec<T, N> >::floor()const
{
    Vec<T,N>res;
    for(Uint i=0;i<N;++i)res[i]=::floor(VecBaseDataIndex(this,T,i));
    return res;
}
///////////////////////////////////////////Vec1
template<class T>struct Vec<T,1>:VecBase<Vec<T,1>>
{
    using Base=VecBase<Vec<T, 1>>;
    union {
        T x, r;
    };
    Vec():Base(){};
    Vec(const T& val) :Base(val) {}
    template<Uint N,class...Arg>
    Vec(const Vec<T,N>&v,const Arg&...arg):Base(v,arg...){}
    ~Vec(){}
};
////////Vec2
template<class T>struct Vec<T, 2> :VecBase<Vec<T, 2>>
{
    using Base= VecBase<Vec<T, 2>>;
    union {
        T x, r;
    };
    union
    {
        T y, g;
    };
    Vec():Base(){};
    Vec(const T&val):Base(val){}
    template<class...Arg>
    Vec(const T&val,const Arg&...arg):Base(val,arg...){}
    template<Uint N, class...Arg>
    Vec(const Vec<T, N>& v, const Arg&...arg):Base(v, arg...) {}
    ~Vec() {}
};
///////////////////////////////////////////////Vec3
template<class T>struct Vec<T, 3> :VecBase<Vec<T, 3>>
{
    union 
    {
        T x, r;
    };
    union 
    {
        T y, g;
    };
    union
    {
        T z, b;
    };
    using Base = VecBase<Vec<T, 3>>;
    Vec():Base(){};
    Vec(const T& val) :Base(val) {}
    template<class...Arg>
    Vec(const T& val, const Arg&...arg) : Base(val, arg...) {}
    template<Uint N, class...Arg>
    Vec(const Vec<T, N>& v, const Arg&...arg) : Base(v, arg...) {}
    Vec<T,3> cross(const Vec<T,3>&v);
    Vec<T,3> reflect(const Vec<T,3>&normal);
    Vec<T,3> refract(const Vec<T,3>&normal,double eta);
    ~Vec() {}
};

template<class T>
Vec<T, 3> Vec<T, 3>::refract(const Vec<T, 3> &normal, double eta)
{
    double dot_v=this->dot(normal);
    double k = 1.0 - eta * eta * (1.0 - dot_v*dot_v);
    Vec<T,3>res;
    if (k<0.0)
        res = {0.0};
    else
        res =(*this)*eta -normal*(eta*dot_v+sqrt(k));
    return res;
}

template<class T>
Vec<T, 3> Vec<T, 3>::reflect(const Vec<T, 3> &normal)
{
    Vec<T,3> n=normal.normalize();
    return ((*this) - n*2*this->dot(n));
}
/////////////////////////////////
template<class T>struct Vec<T, 4> :VecBase<Vec<T, 4>>
{
    union {
        T x, r;
    };
    union {
        T y, g;
    };
    union {
        T z, b;
    };
    union
    {
        T w, a;
    };
    using Base = VecBase<Vec<T, 4>>;
    Vec():Base(){};
    Vec(const T& val) :Base(val) {}
    template<class...Arg>
    Vec(const T& val, const Arg&...arg) : Base(val, arg...) {}
    template<Uint N, class...Arg>
    Vec(const Vec<T, N>& v, const Arg&...arg) : Base(v, arg...) {}
    ~Vec() {}
};
//////////////////////////////////////////////////////////////////////
template<Uint Dimensions>using vec=Vec<float, Dimensions>;
template<Uint Dimensions>using ivec= Vec<int, Dimensions>;
template<Uint Dimensions>using uvec=Vec<Uint,Dimensions>;
typedef vec<1> vec1;
typedef vec<2> vec2; 
typedef vec<3> vec3;
typedef vec<4> vec4;
typedef ivec<1> ivec1;
typedef ivec<2> ivec2;
typedef ivec<3> ivec3;
typedef ivec<4> ivec4;
typedef uvec<1> uvec1;
typedef uvec<2> uvec2;
typedef uvec<3> uvec3;
typedef uvec<4> uvec4;
//////////////////////////////////////////////////////////////////////// VEC_H

template<class T, Uint N>
inline VecBase<Vec<T, N>>::VecBase()
{
}
template<class T, Uint N>
inline VecBase<Vec<T,N>>::VecBase(const T& val)
{
    if constexpr (N == 1) VecBaseDataIndex(this, T, 0) = val;
    else if (N == 2)
        VecBaseDataIndex(this, T,0) = VecBaseDataIndex(this, T,1) = val;
    else if (N == 3)
        VecBaseDataIndex(this, T,0) = VecBaseDataIndex(this, T,1) = VecBaseDataIndex(this, T,2) = val;
    else if (N == 4)
        VecBaseDataIndex(this, T, 0) = VecBaseDataIndex(this, T, 1) = VecBaseDataIndex(this, T, 2)=VecBaseDataIndex(this,T,3) = val;
    else if (N > 4)
        for (unsigned int i = 0; i < N; ++i)
            VecBaseDataIndex(this, T,i) = val;
}

template<class T, Uint N>
inline T& VecBase<Vec<T, N>>::operator[](Uint i)
{
    return VecBaseDataIndex(this, T, i);
}

template<class T, Uint N>
inline T VecBase<Vec<T, N>>::distance() const
{
    T val = 0;
    for (int i = 0; i < N; i++)
        val += VecBaseDataIndex(this, T, i) * VecBaseDataIndex(this, T, i);
    return (T)(sqrt(val));
}

template<class T, Uint N>
inline Vec<T, N> VecBase<Vec<T, N>>::normalize() const
{
    Vec<T, N>res;
    T pow_2=distance();
    if(pow_2==((T)(0)))return Vec<T, N>{0};
    for (Uint i = 0; i < N; ++i)res[i] =VecBaseDataIndex(this, T, i)/pow_2;
    return res;
}
template<class T, Uint N>
inline T VecBase<Vec<T, N>>::dot(const Vec<T, N>& v) const
{
    T res = 0;
    for (Uint i = 0; i < N; ++i)res += v.get(i) * VecBaseDataIndex(this, T, i);
    return res;
}

template<class T, Uint N>
inline bool VecBase<Vec<T, N>>::equal(const Vec<T, N>& v) const
{
    for (Uint i = 0; i < N; ++i)
    {
        if (v.get(i) != VecBaseDataIndex(this, T, i))return false;
    }
    return true;
}

template<class T, Uint N>
inline Vec<T, N> VecBase<Vec<T, N>>::copy() const
{
    Vec<T, N>res;
    for(Uint i=0;i<N;++i)res[i]=VecBaseDataIndex(this,T,i);
    return res;
}

template<class T, Uint N>
inline T* VecBase<Vec<T, N>>::value_ptr()
{
    return VecBaseData(this,T);
}

template<class T, Uint N>
inline bool VecBase<Vec<T, N>>::operator==(const Vec<T, N>& v)
{
    for (unsigned int i = 0; i < N; ++i)
    {
        if (VecBaseDataIndex(this, T, i) != v.get(i))return false;
    }
    return true;
}

template<class T, Uint N>
inline Vec<T, N>& VecBase<Vec<T, N>>::operator=(const Vec<T, N>& v)
{
    for (unsigned int i = 0; i < N; ++i)
        VecBaseDataIndex(this, T, i) = v.get(i);
}

template<class T, Uint N>
inline T VecBase<Vec<T, N>>::get(Uint index)const
{
   return VecBaseDataIndex(this, T, index);
}

template<class T, Uint N>
Vec<T, N> VecBase<Vec<T, N>>::mix(const Vec<T, N> &v, float factor)
{
    return (v*factor)+((*this)*(1.0f-factor));
}

template<class T, Uint N>
inline Vec<T, N> VecBase<Vec<T, N>>::operator*(const Vec<T, N>& v) const
{
    Vec<T, N>res;
    for (unsigned int i = 0; i < N; ++i)res[i] = v.get(i) * VecBaseDataIndex(this, T, i);
    return res;
}

template<class T, Uint N>
inline void VecBase<Vec<T, N>>::operator*=(const Vec<T, N>& v)
{
    for (unsigned int i = 0; i < N; ++i)VecBaseDataIndex(this,T,i)*=v.get(i);
}

template<class T, Uint N>
inline Vec<T, N> VecBase<Vec<T, N>>::operator+(const Vec<T, N>& v) const
{
    Vec<T, N>res;
    for (unsigned int i = 0; i < N; ++i)res[i] = VecBaseDataIndex(this, T, i) +v.get(i);
    return res;
}

template<class T, Uint N>
inline void VecBase<Vec<T, N>>::operator+=(const Vec<T, N>& v)
{

    for (unsigned int i = 0; i < N; ++i)VecBaseDataIndex(this, T, i) += v.get(i);
}

template<class T, Uint N>
inline Vec<T, N> VecBase<Vec<T, N>>::operator/(const T& v) const
{
    Vec<T, N>res;
    for (unsigned int i = 0; i < N; ++i)res[i] = VecBaseDataIndex(this, T, i)/ v;
    return res;
}


template<class T, Uint N>
inline Vec<T, N> VecBase<Vec<T, N>>::operator/(const Vec<T, N>& v) const
{
    Vec<T, N>res;
    for (unsigned int i = 0; i < N; ++i)res[i] = VecBaseDataIndex(this, T, i) / v.get(i);
    return res;
}

template<class T, Uint N>
inline void VecBase<Vec<T, N>>::operator/=(const Vec<T, N>& v)
{
    for (unsigned int i = 0; i < N; ++i)VecBaseDataIndex(this, T, i)/=v.get(i);
}

template<class T, Uint N>
inline Vec<T, N> VecBase<Vec<T, N>>::operator-(const Vec<T, N>& v) const
{
    Vec<T, N>res;
    for (unsigned int i = 0; i < N; ++i)res[i] = VecBaseDataIndex(this, T, i) -v.get(i);
    return res;
}

template<class T, Uint N>
inline void VecBase<Vec<T, N>>::operator-=(const Vec<T, N>& v)
{
    for (unsigned int i = 0; i < N; ++i)VecBaseDataIndex(this, T, i)-= v.get(i);
}

template<class T, Uint N>
inline void VecBase<Vec<T, N>>::PUSH(Uint index)
{
}

template<class T, Uint N>
template<class ...Arg>
inline VecBase<Vec<T, N>>::VecBase(const T& val, const Arg & ...arg)
{
    PUSH(0, val, arg...);
}

template<class T, Uint N>
template<Uint D, class ...Arg>
inline VecBase<Vec<T, N>>::VecBase(const Vec<T, D>& vec, const Arg & ...arg)
{
    if constexpr (N <= D)
        for (unsigned int i = 0; i < N; ++i)VecBaseDataIndex(this, T, i) = vec.get(i);
    else
    {
        for (unsigned int i = 0; i < D; ++i)VecBaseDataIndex(this, T, i) = vec.get(i);
        PUSH(D, arg...);
    }
}

template<class T, Uint N>
template<class...Arg>
inline void VecBase<Vec<T, N>>::PUSH(Uint index,const T& val, const Arg &...arg)
{
    if (index == N)return;
        VecBaseDataIndex(this, T, index) = val;
        PUSH(index + 1, arg...);
}


template<class T>
inline Vec<T, 3> Vec<T, 3>::cross(const Vec<T, 3>&v)
{
    return Vec<T,3>(y * v.z - z * v.y,
        z * v.x -x * v.z,
        x * v.y - y * v.x);
}

template<class T, Uint N>
inline bool operator<(const Vec<T, N>& v1, const Vec<T, N>& v2)
{
    for (Uint i = 0; i < N; ++i)
    {
        bool flag=1;
       for(Uint j=0;j<i;++j)
           if(v1.get(j)!=v2.get(j)){
               flag=0;
               break;
           }
        if(flag&&v1.get(i)<v2.get(i))return 1;
    }
    return 0;
}
#endif//Vec
