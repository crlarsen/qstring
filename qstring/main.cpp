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

// This function multiplies two elements of a quaternion.  In some cases
// when multiplying two elements the product has its sign determined
// solely by the signs of the multiplier, and the multiplicand, e.g.,
// the sign of the product of the real component of the multiplier with
// any component of the multiplicand always has its sign determined
// solely by the signs of the real component and the multiplier element.
// When two "i" components are multiplied together the sign of the
// product is always going to be the opposite of what the sign would be
// based solely in the signs of the "i" components.  The bool parameter
// "opposite" controls this behavior.
//
// The product also looks for special cases where either the multiplier
// or the multiplicand is either zero or one and simplifies the product
// accordingly.
void stringProd(string &prod, const string &olhs,
                const string &orhs, const bool opposite)
{
    string  lhs(olhs), rhs(orhs);
    bool    minus=opposite; // If minus is true, product needs a minus
                            // sign.

    if (lhs[0]=='-') {
        lhs = lhs.substr(1);
        minus = !minus;
    }

    if (rhs[0]=='-') {
        rhs = rhs.substr(1);
        minus = !minus;
    }

    if (lhs!="0" && rhs!="0") {
        if (minus) {
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

// Puts parentheses around an expression, and, if there is a leading
// unary minus sign, the function will attempt to move the minus sign
// outside of the parentheses.  Avoids parentheses, all together, if
// possible.
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

// Strip out white space, and split quaternion into components
void extractElements(const string &quat, string &qr, string &qi,
                     string &qj, string &qk)
{
    string squat("");
    int commaCount=0;

    // Strip white space from the string
    for (auto &chr : quat) {
        switch (chr) {
            case ' ':
            case '\t':
                break;

            case ',':
                ++commaCount;
            default:
                squat += chr;
                break;
        }
    }

    if (commaCount != 3) {
        std::cerr << "Wrong number of commas in lhs:  " << commaCount << std::endl;
        exit(1);
    }

    // Split string into components
    int i;
    for (i=0; i!=squat.length() && squat[i]!=','; ++i)
        qr += squat[i];
    ++i;
    for ( ; i!=squat.length() && squat[i]!=','; ++i)
        qi += squat[i];
    ++i;
    for ( ; i!=squat.length() && squat[i]!=','; ++i)
        qj += squat[i];
    ++i;
    for ( ; i!=squat.length(); ++i)
        qk += squat[i];
    
}

// Multiply two quaternions represented as strings.  The output is a
// string representing the product.
string qmul(const string &lhs, const string &rhs)
{
    string lr, li, lj, lk;

    extractElements(lhs, lr, li, lj, lk);

    string rr, ri, rj, rk;

    extractElements(rhs, rr, ri, rj, rk);

    // Begin the actual work of multiplying
    string  product;
    string  pr, pi, pj, pk;

    // Calculate the real portion of the product
    stringProd(pr, lr, rr, false);

    stringProd(pr, li, ri, true);

    stringProd(pr, lj, rj, true);

    stringProd(pr, lk, rk, true);

    if (pr == "") pr = "0";

    product += parenthesize(pr) + ",";

    // Calculate the "i" portion of the product
    stringProd(pi, lr, ri, false);

    stringProd(pi, li, rr, false);

    stringProd(pi, lj, rk, false);

    stringProd(pi, lk, rj, true);

    if (pi == "") pi = "0";

    product += parenthesize(pi) + ",";

    // Calculate the "j" portion of the product
    stringProd(pj, lr, rj, false);

    stringProd(pj, lj, rr, false);

    stringProd(pj, lk, ri, false);

    stringProd(pj, li, rk, true);

    if (pj == "") pj = "0";

    product += parenthesize(pj) + ",";

    // Calculate the "k" portion of the product
    stringProd(pk, lr, rk, false);

    stringProd(pk, lk, rr, false);

    stringProd(pk, li, rj, false);

    stringProd(pk, lj, ri, true);

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

    std::cout << "This program expects to read quaternions as a newline" << std::endl;
    std::cout << "terminated list of 4 components.  The components must" << std::endl;
    std::cout << "be separated by commas." << std::endl << std::endl;

    std::cout << "The program can be exited by sending EOF.  For UNIX" << std::endl;
    std::cout << "machines (including Mac OS X), the default way of" << std::endl;
    std::cout << "doing this is to type ctrl-D; Windows machines treat" <<std::endl;
    std::cout <<"ctrl-Z as EOF, by default." << std::endl << std::endl;

    const string    prompt("Enter first quaternion:  ");
    std::cout << prompt << std::flush;

    // While there are more quaternions to be processed ...
    while (std::getline(std::cin, lhs) && !std::cin.eof()) {
        // If possible, get the second quaternion.
        std::cout << "Enter second quaternion:  " << std::flush;
        std::getline(std::cin, rhs);
        if (std::cin.eof()) exit(0);

        // Calculate and display the product
        std::cout << qmul(lhs, rhs) << std::endl << std::endl;
        std::cout << prompt << std::flush;
    }

    return 0;
}

