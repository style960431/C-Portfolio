//
//  main.cpp
//  BigInt Calculator
//
//  Created by 王宗祥 on 2020/12/3.
//

#include <iostream>
#include <vector>
#include <string>
#include "BigInt.hpp"

using namespace std;


int main() {
    
    string str1, str2;
    cout << "Enter two BigInts num1 & num2 = ";
    cin >> str1 >> str2;
    BigInt num1(str1);
    BigInt num2(str2);
    
    printf("The BigInt1 (num1) = ");                print(num1);
    printf("The BigInt2 (num2) = ");                print(num2);
    
    printf("The answer by '+' = ");                 print(num1 + num2);
    printf("The answer by '-' = ");                 print(num1 - num2);
    printf("The answer by '*' = ");                 print(num1 * num2);
    printf("The answer by '/' = ");                 print(num1 / num2);
    printf("The answer by '%%' = ");                print(num1 % num2);
    
    printf("The answer by 'max' = ");               print(max(num1, num2));
    printf("The answer by 'min' = ");               print(min(num1, num2));
    
    printf("The answer by 'gcd' = ");               print(gcd(num1, num2));
    printf("The answer by 'lcm' = ");               print(lcm(num1, num2));
    
    printf("The answer by 'sqrt(num1)' = ");        print(sqrt(num1));
    printf("The answer by 'sqrt(num2)' = ");        print(sqrt(num2));
    
    printf("The answer by 'log' (base : num1, power : num2) = ");   print(log(num1, num2));
    printf("The answer by 'log2' (power : num1) = ");               print(log2(num1));
    printf("The answer by 'log10' (power : num1) = ");              print(log10(num1));
    
    printf("The answer by 'pow(num1, 10)' = ");   print(pow(num1, 10));
    printf("The answer by 'pow(num2, 20)' = ");   print(pow(num2, 20));
    
    cout << endl;
    
    printf("num1++ = ");                            print(num1++);
    printf("++num1 = ");                            print(++num1);
    printf("num1-- = ");                            print(num1--);
    printf("--num1 = ");                            print(--num1);
    
    cout << endl;
    
    printf("(num1 += num2) = ");                    print(num1 += num2);
    printf("num1 = ");                              print(num1);
    printf("num2 = ");                              print(num2);
    
    cout << endl;

    printf("(num1 -= num2) = ");                    print(num1 -= num2);
    printf("num1 = ");                              print(num1);
    printf("num2 = ");                              print(num2);
    
    cout << endl;
    
    printf("(num1 *= num2) = ");                    print(num1 *= num2);
    printf("num1 = ");                              print(num1);
    printf("num2 = ");                              print(num2);
    
    cout << endl;
    
    printf("(num1 /= num2) = ");                    print(num1 /= num2);
    printf("num1 = ");                              print(num1);
    printf("num2 = ");                              print(num2);
    
    cout << endl;
    
    printf("(num1 %%= num2) = ");                   print(num1 %= num2);
    printf("num1 = ");                              print(num1);
    printf("num2 = ");                              print(num2);
    
    cout << endl;
    
    return 0;
}


