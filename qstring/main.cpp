//
//  main.cpp
//  qstring
//
//  Created by Chris Larsen on 1/7/14.
//  Copyright (c) 2014 Chris Larsen. All rights reserved.
//

#include <iostream>
#include <string>

using std::string;

void stringProd(string &prod, const string &olhs, const string &orhs, const char addSub)
{
    string  lhs(olhs), rhs(orhs);
    int     minusCount=0;

    if (lhs[0]=='-') {
        lhs = lhs.substr(1);
        ++minusCount;
    }

    if (rhs[0]=='-') {
        rhs = rhs.substr(1);
        ++minusCount;
    }

    if (addSub == '-') ++minusCount;

    if (lhs!="0" && rhs!="0") {
        if (minusCount & 1) {
            prod += '-';
        } else if (prod.length()) {
            prod += '+';
        }

        if (lhs=="1") {
            prod += rhs;
        } else if (rhs=="1") {
            prod += lhs;
        } else {
            prod += lhs + "*" + rhs;
        }
    }
}

string parenthesize(const string &prod)
{
    string  sign("");
    string  tmp(prod);

    if (prod[0]=='-') {
        sign = "-";
        tmp = prod.substr(1);
    }
    if (tmp.find("+")==string::npos && tmp.find("-")==string::npos) {
        return sign + tmp;
    } else {
        return "(" + prod + ")";
    }
}

string qmul(const string &lhs, const string &rhs)
{
    string slhs(""), srhs("");
    int commaCount=0;

    for (auto &chr : lhs) {
        switch (chr) {
            case ' ':
            case '\t':
                break;

            case ',':
                ++commaCount;
            default:
                slhs += chr;
                break;
        }
    }

    if (commaCount != 3) {
        std::cerr << "Wrong number of commas in lhs:  " << commaCount << std::endl;
        exit(1);
    }

    string lr, li, lj, lk;
    int i;
    for (i=0; i!=slhs.length() && slhs[i]!=','; ++i)
        lr += slhs[i];
    ++i;
    for ( ; i!=slhs.length() && slhs[i]!=','; ++i)
        li += slhs[i];
    ++i;
    for ( ; i!=slhs.length() && slhs[i]!=','; ++i)
        lj += slhs[i];
    ++i;
    for ( ; i!=slhs.length(); ++i)
        lk += slhs[i];

    commaCount = 0;
    for (auto &chr : rhs) {
        switch (chr) {
            case ' ':
            case '\t':
                break;

            case ',':
                ++commaCount;
            default:
                srhs += chr;
                break;
        }
    }

    if (commaCount != 3) {
        std::cerr << "Wrong number of commas in rhs:  " << commaCount << std::endl;
        exit(1);
    }
    
    string rr, ri, rj, rk;

    for (i=0; i!=srhs.length() && srhs[i]!=','; ++i)
        rr += srhs[i];
    ++i;
    for ( ; i!=srhs.length() && srhs[i]!=','; ++i)
        ri += srhs[i];
    ++i;
    for ( ; i!=srhs.length() && srhs[i]!=','; ++i)
        rj += srhs[i];
    ++i;
    for ( ; i!=srhs.length(); ++i)
        rk += srhs[i];

    string  product;
    string  pr, pi, pj, pk;

    stringProd(pr, lr, rr, '+');

    stringProd(pr, li, ri, '-');

    stringProd(pr, lj, rj, '-');

    stringProd(pr, lk, rk, '-');

    if (pr == "") pr = "0";

    product += parenthesize(pr) + ",";

    stringProd(pi, lr, ri, '+');

    stringProd(pi, li, rr, '+');

    stringProd(pi, lj, rk, '+');

    stringProd(pi, lk, rj, '-');

    if (pi == "") pi = "0";

    product += parenthesize(pi) + ",";

    stringProd(pj, lr, rj, '+');

    stringProd(pj, lj, rr, '+');

    stringProd(pj, lk, ri, '+');

    stringProd(pj, li, rk, '-');

    if (pj == "") pj = "0";

    product += parenthesize(pj) + ",";

    stringProd(pk, lr, rk, '+');

    stringProd(pk, lk, rr, '+');

    stringProd(pk, li, rj, '+');

    stringProd(pk, lj, ri, '-');

    if (pk == "") pk = "0";
    
    product += parenthesize(pk);

    return product;
}

int main(int argc, const char * argv[])
{
//    std::cout << qmul("w,x,y,z", "r,i,j,k") << std::endl;
//    std::cout << qmul("w,0,y,0", "r,i,0,0") << std::endl;
//    std::cout << qmul("1,0,0,0", "1,0,0,0") << std::endl;
//    std::cout << qmul("1,0,0,0", "0,1,0,0") << std::endl;
//    std::cout << qmul("1,0,0,0", "0,0,1,0") << std::endl;
//    std::cout << qmul("1,0,0,0", "0,0,0,1") << std::endl;
//    std::cout << qmul("0,1,0,0", "1,0,0,0") << std::endl;
//    std::cout << qmul("0,1,0,0", "0,1,0,0") << std::endl;
//    std::cout << qmul("0,1,0,0", "0,0,1,0") << std::endl;
//    std::cout << qmul("0,1,0,0", "0,0,0,1") << std::endl;
//    std::cout << qmul("0,0,1,0", "1,0,0,0") << std::endl;
//    std::cout << qmul("0,0,1,0", "0,1,0,0") << std::endl;
//    std::cout << qmul("0,0,1,0", "0,0,1,0") << std::endl;
//    std::cout << qmul("0,0,1,0", "0,0,0,1") << std::endl;
//    std::cout << qmul("0,0,0,1", "1,0,0,0") << std::endl;
//    std::cout << qmul("0,0,0,1", "0,1,0,0") << std::endl;
//    std::cout << qmul("0,0,0,1", "0,0,1,0") << std::endl;
//    std::cout << qmul("0,0,0,1", "0,0,0,1") << std::endl;
//    std::cout << qmul("M_SQRT1_2,-M_SQRT1_2,0,0", "cosAlpha,0,0,sinAlpha") << std::endl << std::endl;
//    std::cout << qmul("cosAlpha,sinAlpha,0,0", "cosBeta,0,0,sinBeta") << std::endl << std::endl;
//    std::cout << qmul("cosBeta,0,sinBeta,0", "cosGamma,sinGamma,0,0") << std::endl << std::endl;
//    std::cout << qmul("cosAlpha,0,0,sinAlpha", qmul("cosBeta,0,sinBeta,0", "cosGamma,sinGamma,0,0")) << std::endl;

    string  lhs, rhs;

    const string    prompt("Enter first quaternion:  ");
    std::cout << prompt << std::flush;

    while (std::getline(std::cin, lhs) && !std::cin.eof()) {
        std::cout << "Enter second quaternion:  " << std::flush;
        std::getline(std::cin, rhs);
        if (std::cin.eof()) exit(0);

        std::cout << qmul(lhs, rhs) << std::endl << std::endl;
        std::cout << prompt << std::flush;
    }

    return 0;
}

