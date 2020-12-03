//
//  BigInt.hpp
//  BigInt Calculator
//
//  Created by 王宗祥 on 2020/12/3.
//

#ifndef BigInt_hpp
#define BigInt_hpp

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

#define BASE 1000000000         // 10^9 進位
using ll = long long;

class BigInt {
    int sign;
    vector<ll> num;
public:
    // 初始化
    BigInt();
    BigInt(string str);
    BigInt(ll a) ;
    
    bool operator >(const BigInt& x) const;
    bool operator <(const BigInt& x) const;
    bool operator >=(const BigInt& x) const;
    bool operator <=(const BigInt& x) const;
    bool operator !=(const BigInt& x) const;
    bool operator ==(const BigInt& x) const;
    
    BigInt operator -() const;

    void operator =(const BigInt& x);
    BigInt operator +(const BigInt& x) const;
    BigInt operator -(const BigInt& x) const;
    BigInt operator *(const BigInt& x) const;
    BigInt operator /(const BigInt& x) const;
    BigInt operator %(const BigInt& x) const;
    
    BigInt divide(BigInt dividend, BigInt divisor, char symbol) const;
    
    BigInt operator ++();    // 前置，例如 ++x
    BigInt operator ++(int); // 後置，例如 x++
    BigInt operator --();    // 前置，例如 --x
    BigInt operator --(int); // 後置，例如 x--
    
    BigInt operator +=(BigInt &a);
    BigInt operator -=(BigInt &a);
    BigInt operator *=(BigInt &a);
    BigInt operator /=(BigInt &a);
    BigInt operator %=(BigInt &a);
    
    
    friend void print(const BigInt&);
    friend istream& operator >>(istream&, BigInt&);
    friend ostream& operator <<(ostream&, BigInt&);
    friend void swap (BigInt&, BigInt&);
    friend BigInt max(const BigInt&, const BigInt&);
    friend BigInt min(const BigInt&, const BigInt&);
    friend BigInt gcd(const BigInt&, const BigInt&);
    friend BigInt lcm(const BigInt&, const BigInt&);
    friend BigInt sqrt(const BigInt&);
    friend BigInt log(const BigInt&, const BigInt&);
    friend BigInt log2(const BigInt& x);
    friend BigInt log10(const BigInt& x);
    friend BigInt pow(const BigInt& a, int b);
    friend BigInt pow(const BigInt&, const BigInt&);
};

#endif /* BigInt_hpp */
