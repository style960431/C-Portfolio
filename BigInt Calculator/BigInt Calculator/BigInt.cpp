//
//  BigInt.cpp
//  BigInt Calculator
//
//  Created by 王宗祥 on 2020/12/3.
//
#include "BigInt.hpp"

BigInt::BigInt(): sign(1) {};

BigInt::BigInt(string str) {                    // 輸入為字串
    sign = str[0] != '-' ? 1 : -1;              // 判斷正負號
    if (sign == -1)                             // 負號時，將字串中的負號刪除
        str.erase(0, 1);
    ll len = str.size();
    
    // 將字串的數值“反向”放入向量中
    ll i = len - 1;
    
    while (i >= 0) {
        ll temp = 0;
        ll p = 1;
        while (p != BASE && i >= 0) {
            temp += (str[i] - '0') * p;
            p *= 10;
            i--;
        }
        num.push_back(temp);
    }
}

BigInt::BigInt(ll a) {                  // 輸入為整數
    sign = a >= 0 ? 1 : -1;             // 判斷正負號
    a = a >= 0 ? a : -a;                // 將數值變為正數
    if (a == 0) {                       // 若為 0，直接輸入
        num.push_back(0);
    }
    else {
        while (a > 0) {                 // 剩餘情況
            num.push_back(a % BASE);    // 同樣以反向的方式輸入至向量中
            a /= BASE;
        }
    }
}

bool BigInt::operator> (const BigInt& x) const{
    ll len = num.size();
    ll xlen = x.num.size();
    
    if (sign != x.sign)
        return sign > x.sign;                   // 先判斷正負號
    
    if (len != xlen)
        return len * sign > xlen * x.sign;      // 再判斷長度與符號關係
    
    for (ll i = len - 1; i >= 0; i--) {         // 同號時，再判斷大小
        if (num[i] != x.num[i])
            return num[i] * sign > x.num[i] * x.sign;
    }
    
    return false;
}

bool BigInt::operator< (const BigInt& x) const {
    return x > *this;
}

bool BigInt::operator>= (const BigInt& x) const {
    return !(*this < x);
}

bool BigInt::operator<= (const BigInt& x) const {
    return !(*this > x);
}

bool BigInt::operator!= (const BigInt& x) const{
    return *this > x || x > * this;
}

bool BigInt::operator== (const BigInt& x) const {
    return !(*this > x) && !(x > * this);
}

BigInt BigInt::operator- () const { // 負號
    BigInt temp = *this;
    temp.sign = -sign;
    return temp;
}

void BigInt::operator= (const BigInt& x) {
    sign = x.sign;
    num.clear();                                // 儲存數值的向量須先完全清空
    num.resize(x.num.size());                   // 再重新給予空間
    for (int i = 0; i < x.num.size(); i++)      // 最後再重新賦予數值
        num[i] = x.num[i];
}

BigInt BigInt::operator+ (const BigInt& x) const{
    // 不同號時，則以變號和相減的方式處理
    if (sign != x.sign)
        return *this - (-x);
    
    // 同號
    BigInt temp;                                    // 總和暫存用
    BigInt large = *this > x ? *this : x;           // 另存其中較大的 BigInt
    ll len = num.size();
    ll xlen = x.num.size();
    ll min_len = len < xlen ? len : xlen;           // 最小位元數長度
    ll max_len = len > xlen ? len : xlen;           // 最大位元數長度
    ll carry = 0;                                   // 進位數
    temp.num.resize(max_len);                       // 先初始化位元長度
    
    // 先加總兩個 BigInt 有重疊的位元
    for (ll i = 0; i < min_len; i++) {
        ll digit = num[i] + x.num[i] + carry;       // 暫存相加數值
        carry = digit / BASE;                       // 計算進位值
        digit %= BASE;                              // 計算相加後應儲存的數值
        temp.num[i] = digit;                        // 存入
    }
    
    // 再進行未重疊位元的計算
    for (ll i = min_len; i < max_len; i++) {        // 同上
        ll digit = large.num[i] + carry;
        carry = digit / BASE;
        digit %= BASE;
        temp.num[i] = digit;
    }
    
    // 因為有可能還可以進位，因此這裡就以判斷式來判別是否要插入
    if (carry > 0)
        temp.num.push_back(carry);
    
    temp.sign = sign;     // 不論相加或相減，都會在此程式碼中轉成同相，所以直接指定即可
    
    return temp;
}

BigInt BigInt::operator- (const BigInt& x) const {
    // 不同號時，則以變號和相加的方式處理
    if (sign != x.sign)
        return *this + (-x);
    
    // 若兩個 BigInt 相同 則回傳0
    if (*this == x) {
        BigInt zero(0);
        return zero;
    }
    
    // 同號
    BigInt temp;                                        // 總和暫存用
    BigInt large = *this > x ? *this : x;               // 另存其中較大的 BigInt
    BigInt small = *this < x ? *this : x;               // 另存其中較小的 BigInt
    ll len = num.size();
    ll xlen = x.num.size();
    ll min_len = len < xlen ? len : xlen;               // 最小位元數長度
    ll max_len = len > xlen ? len : xlen;               // 最大位元數長度
    ll shift = 0;                                       // 借位數
    
    // 先加總兩個 BigInt 有重疊的位元
    for (ll i = 0; i < min_len; i++) {
        ll digit = large.num[i] - small.num[i] - shift;     // 暫存相減數值
        shift = digit < 0 ? 1 : 0;                          // 計算借位數
        digit = digit < 0 ? BASE + digit : digit ;          // 存入
        temp.num.push_back(digit);
    }
    
    // 再進行未重疊位元的計算
    for (ll i = min_len; i < max_len; i++) {
        ll digit = large.num[i] - shift;                    // 暫存相減數值
        shift = digit < 0 ? 1 : 0;                          // 計算借位數
        digit = digit < 0 ? BASE + digit : digit ;          // 存入
        temp.num.push_back(digit);
    }
    
    while (temp.num.back() == 0)    // 若相減最後一位為0，表示總位元數須減少1
        temp.num.pop_back();
    temp.sign = *this > x ? 1 : -1; // 跟加法不同，需依據兩者之間大小指定其最後的正負號

    return temp;
}

BigInt BigInt::operator* (const BigInt& x) const {
    ll len = num.size();
    ll xlen = x.num.size();
    BigInt zero(0);
    
    if (*this == zero || x == zero)     // 將 "其中一個" BigInt 為 0 的狀況特別取出
        return zero;
    
    BigInt ans;                                 // 定義回傳結果變數
    ll carry = 0;                               // 進位數
    ll digit = 0;                               // 暫存相乘數值
    ans.num.resize(len + xlen, 0);              // 初始化總長度
    
    for (ll i = 0; i < xlen; i++) {
        carry = 0;                                      // 歸零
        digit = 0;                                      // 歸零
        for (ll j = 0; j < len; j++) {
            digit = num[j] * x.num[i] + carry;          // 計算兩位元數值總和
            carry = digit / BASE;                       // 計算進位數
            digit %= BASE;                              // 計算儲存的數值
            ans.num[i + j] += digit;                    // 放入 ans 中
            if (ans.num[i + j] >= BASE) {               // 若 >= 10，表示還可以進位
                carry += ans.num[i + j] / BASE;         // 進位數調整
                ans.num[i + j] = ans.num[i + j] % BASE; // 當前位元數值調整
            }
        }
        if (carry > 0)                                  // 若還有剩餘進位數
            ans.num[i + len] += carry;                  // 則先放入下一個位元中
    }
    
    if (ans.num.back() == 0)        // 因為初始化長度的關係，有可能不會用滿空間
        ans.num.pop_back();         // 因此如果最後一格為 0，則將其刪除
    
    ans.sign = sign * x.sign;       // 設定相乘後的正負號
    
    return ans;
}

BigInt BigInt::operator/ (const BigInt& x) const {
    return divide(*this, x, '/');
}

BigInt BigInt::operator% (const BigInt& x) const {
    return divide(*this, x, '%');
}

BigInt BigInt::divide(BigInt dividend, BigInt divisor, char symbol) const {
    // 這裡的 divisor 不用 const 是因為需要讓他一直變化，故以 copy 的方式進入此 function
    BigInt zero(0);
    
    if (divisor == zero) {              // 若除數為 0，則回傳 Error
        BigInt ans("000");
        return ans;
    }

    if (dividend == zero)               // 若被除數為 0，則回傳 zero
        return zero;
    
    int dd_sign = dividend.sign;        // 暫存"被除數"的符號
    int ds_sign = divisor.sign;         // 暫存"除數"的符號
    dividend.sign = 1;                  // 再將其改為正號
    divisor.sign = 1;                   // 同上
    
    BigInt quo(0);                      // 商
    BigInt res;                         // 餘數
    BigInt ten(10);                     // 定義 10
    
    // 想法："以減法的方式計算除法"
    // 首先定義 "temp為除數" 且不斷乘以 10，直到最接近且小於被除數，
    // 並定義 count 計算乘了多少次 10，再將 被除數 不斷減掉 temp，直到 被除數 < temp，
    // 再繼續重複上述步驟，直到 被除數 < 除數為止
    while (dividend >= divisor) {
        BigInt temp = divisor;
        BigInt count(1);
        while (temp <= dividend) {
            if (temp * ten > dividend)
                break;
            temp *= ten;
            count *= ten;
        }
        
        while (dividend >= temp) {
            dividend -= temp;
            quo += count;
        }
    }
    
    quo.sign = dd_sign * ds_sign;           // 商的正負號由被除術和除術決定
    res = dividend;
    res.sign = res == zero ? 1 : dd_sign;   // 依據 C++ 的除法規律，餘數會有負號
                                            // 所以餘數的符號一定為與被除數一樣，
                                            // 但如果整除，則定義為正，避免 print 負號出來
    return symbol == '/' ? quo : res;
}

BigInt BigInt::operator++ () {
    BigInt a(1);
    *this = *this + a;
    return (*this);
}

BigInt BigInt::operator++ (int) {
    BigInt r = *this;
    BigInt a(1);
    *this = *this + a;
    return r;
}

BigInt BigInt::operator-- () {
    BigInt a(1);
    *this = *this - a;
    return (*this);
}

BigInt BigInt::operator-- (int) {
    BigInt r = *this;
    BigInt a(1);
    *this = *this - a;
    return r;
}

BigInt BigInt::operator+= (BigInt &a) {
    *this = *this + a;
    return *this;
}

BigInt BigInt::operator-= (BigInt &a) {
    *this = *this - a;
    return *this;
}

BigInt BigInt::operator*= (BigInt &a) {
    *this = *this * a;
    return *this;
}

BigInt BigInt::operator/= (BigInt &a) {
    *this = *this / a;
    return *this;
}

BigInt BigInt::operator%= (BigInt &a) {
    *this = *this % a;
    return *this;
}

/*******************                                   *******************/
/****************       以下為 BigInt friend function      ****************/
/*******************                                   *******************/

void print(const BigInt& x) {
    string ans = "";
    string temp = "";
    if (x.sign == -1)
        ans += '-';
    
    for (ll i = x.num.size() - 1; i >= 0; i--) {
        temp = to_string(x.num[i]);
        ans += temp;
    }
    
    cout << ans << endl;
}

istream& operator>> (istream &in, BigInt &x) {
    string s;
    getline(cin, s);
    BigInt t(s);
    x = t;
    return in;
}

ostream& operator<< (ostream &out, BigInt& x) {
    print(x);
    return out;
}

void swap (BigInt& num1, BigInt& num2) {    // 交換
    BigInt temp = num1;
    num1 = num2;
    num2 = temp;
}

BigInt max(const BigInt& a, const BigInt& b) {
    return a > b ? a : b;
}

BigInt min(const BigInt& a, const BigInt& b) {
    return a < b ? a : b;
}

BigInt gcd(const BigInt& num1, const BigInt& num2) {
    BigInt zero(0);                             // 定義 0
    
    if (num1 <= zero || num2 <= zero) {         // 因為 gcd 不能包含 "0"、"負數"
        BigInt ans("000");                      // 一但出現即回傳 "Error"
        return ans;
    }
        
    BigInt max = num1 > num2 ? num1 : num2;     // 找出最大值
    BigInt min = num1 < num2 ? num1 : num2;     // 找出最小值
    
    // 迭代法：歐幾里得演算法
    while (min > zero) {            // 讓兩數不斷互除，當最小值為 0 時，表示整除，
        BigInt res = max % min;     // 那麼最後剩下的 max 即為最大公因數
        max = min;
        min = res;
    }
    
    return max;
}

BigInt lcm(const BigInt& num1, const BigInt& num2) {
    BigInt zero(0);                             // 定義 0
    if (num1 <= zero || num2 <= zero) {         // 因為 gcd 不能包含 "0"、"負數"
        BigInt ans("000");                      // 一但出現即回傳 "Error"
        return ans;
    }
    return (num1 * num2 / gcd(num1, num2));
}

BigInt sqrt(const BigInt& x) {
    BigInt zero(0);                     // 定義 0
    BigInt one(1);
    BigInt two(2);
    if (x < zero) {                     // 因為 sqrt 不能包含 "負數"
        BigInt ans("000");              // 一但出現即回傳 "Error"
        return ans;
    }
    
    BigInt ans = x;
    BigInt temp = (x + one) / two;
    while (temp < ans) {
        ans = temp;
        temp = (temp + x / temp) / two;
    }
    return ans;
}

BigInt log(const BigInt& num1, const BigInt& num2) {
    BigInt zero(0);         // 定義 0
    BigInt one(1);          // 定義 1
    
    // 因為 log 不能包含 "負數"、底數不可為 1 且不考慮虛數
    if (num1 <= zero || num1 == one || num2 <= zero) {
        BigInt ans("000");              // 一但出現即回傳 "Error"
        return ans;
    }
    
    BigInt ans(0);
    BigInt base = num1;
    BigInt temp = num2;
    while (temp > one) {
        ans++;
        temp /= base;
        
    }
    return ans;
}

BigInt log2(const BigInt& x) {
    BigInt two(2);          // 定義 2
    return log(two, x);
}

BigInt log10(const BigInt& x) {
    BigInt ten(10);         // 定義 10
    return log(ten, x);
}

BigInt pow(const BigInt& a, int b) {
    BigInt temp(b);
    return pow(a, temp);
}

BigInt pow(const BigInt& base, const BigInt& power) {
    BigInt zero(0);     // 定義 0 變數
    BigInt one(1);      // 定義 1 變數
    BigInt two(2);      // 定義 2 變數
    if (power == zero)  // 當指數為 0 時，回傳 1
        return one;
    
    BigInt temp = pow(base, power / two);   // 透過遞迴不斷拆成剩餘 "平方次"
    if (power % two == zero)                // 當成為平方次
        return temp * temp;                 // 回傳平方的結果
    
    return temp * temp * base;      // 因為拆成一半計算的關係，所以最後要再乘平方一次
}
