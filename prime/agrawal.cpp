#include "Prime.h"

// https://en.wikipedia.org/wiki/AKS_primality_test
// https://www.cse.iitk.ac.in/users/manindra/algebra/primality_v6.pdf

struct Indeterminate {
    /*
     * Describes coefficient * x^power
     */
    TInteger coefficient;
    TInteger power;
};

class Polynomial {
    /*
     * Holds a polynomial expression
     */
    std::vector<Indeterminate> addends;
public:
    Polynomial() {}

    Polynomial(Indeterminate &one_addend) {
        addends.push_back(one_addend);
    }

    Polynomial(std::vector<Indeterminate> &indeterminates) {
        addends = indeterminates;
    }

    int length() const {
        return addends.size();
    }

    void sort()
    // Uses bubble sort to sort addends by descending their powers
    {
        bool changed;

        do {
            changed = false;
            int i;

            for (i = 1; i < length(); i++) {
                if (addends[i - 1].power < addends[i].power) {
                    Indeterminate tmp = addends[i];
                    addends[i] = addends[i - 1];
                    addends[i - 1] = tmp;
                    changed = true;
                }
            }
        } while (changed);
    }

    void operator+(const Indeterminate &other) {
        int i;

        for (i = 0; i < length(); i++) {
            if (addends[i].power == other.power) {
                addends[i].coefficient = addends[i].coefficient + other.coefficient;
                return;
            }
        }

        addends.push_back(other);
        sort();
    }

    void pop_lead_zeros() {
        while (addends[0].coefficient == I_ZERO) {
            addends.erase(addends.begin());
        }
    }

    void insert_missing_zeros() {
        int i = 1;

        while (true) {
            if (i >= length()) {

                if (length() == 0) {
                    return;
                }
                while (addends[length() - 1].power != I_ZERO) {
//                    append({0, addends[length() - 1].power - I_ONE});
                } return;
            }
            if (addends[i - 1].power - addends[i].power) {
                // TODO
            }
        }
    }

    void operator*(const TInteger &n) {
        int i;

        for (i = 0; i < length(); i++) {
            addends[i].coefficient = addends[i].coefficient * n;
        }
    }

    void operator%(const Polynomial &other) {
        int i;

        // TODO
    }

    bool operator !=(const Polynomial &other) const {
        if (length() != other.length()) {
            return true;
        }
        int i;

        for (i = 0; i < length(); i++) {
            if (addends[i].coefficient != other.addends[i].coefficient) {
                return true;
            }
            if (addends[i].power != other.addends[i].power) {
                return true;
            }
        }

        return false;
    }

    operator std::string() const {
        std::string result = "";
        int i;

        for (i = 0; i < length() - 1; i++) {
            result += (std::string)addends[i].coefficient;
            if (addends[i].power > I_ZERO) {
                result += "*x";
                if (addends[i].power > I_ONE) {
                    result += "^";
                    result += (std::string) addends[i].power;
                }
            }
            result += ", ";
        }
        result += (std::string)addends[i].coefficient;
        if (addends[i].power > I_ZERO) {
            result += "*x";
            if (addends[i].power > I_ONE) {
                result += "^";
                result += (std::string) addends[i].power;
            }
        }

        return result;
    }
};

TInteger factorial(const TInteger &n)
 // Returns n!
 {
    TInteger i, result = 1;

    for (i = I_ONE; i <= n; i = i + I_ONE) {
        result = result * i;
    }

    return result;
}

TInteger combinations(const TInteger &n, const TInteger &k)
/* Returns combinations from n to k
 * Converts dividend into int, that can mess up result
 */ {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

Polynomial binom(const TInteger &a, const TInteger &n)
//  Returns binomial expansion of (x + a)^n
{
    Polynomial result;
    TInteger i;

    for (i = I_ZERO; i <= n; i = i + I_ONE) {
        Indeterminate next_addend;
        next_addend.coefficient = combinations(n, i);
        next_addend.power = n - i;
        result + next_addend;
    }

    return result;
}

Polynomial x_pow_a_plus_b(const TInteger &a, const TInteger &b)
// Returns x^a + b
{
    std::vector<Indeterminate> result_value(2, {1, 0});

    result_value[0].power = a;
    result_value[1].coefficient = b;

    Polynomial result(result_value);
    return result;
}

Polynomial x_pow_a_minus_1(const TInteger &a)
// Returns x^a - 1
{
    return x_pow_a_plus_b(a, TInteger(-1));
}

bool is_perfect_power(const TInteger &n) {
    TInteger a = I_TWO, b = I_TWO;

    while (pow(a, I_TWO) <= n) {
        TInteger value = pow(a, b);

        if (value == n) {
            return true;
        }
        if (value > n) {
            a = a + I_ONE;
            b = I_TWO;
        } else {
            b = b + I_ONE;
        }
    }

    return false;
}

TInteger kinda_log2(const TInteger &n)
// Returns ceil of logarithm of n with base 2
{
    TInteger result = I_ONE;

    while (pow(I_TWO, result) < n) {
        result = result + I_ONE;
    }

    return result;
}

TInteger gcd(const TInteger &a, const TInteger &b) {
    if (a % b == I_ZERO) {
        return b;
    }
    return gcd(b, a % b);
}

bool coprime(const TInteger &a, const TInteger &b) {
    return gcd(a, b) == I_ONE;
}

TInteger ord(const TInteger &a, const TInteger &n)
/* Returns multiplicative order of a modulo n
 * https://en.wikipedia.org/wiki/Multiplicative_order
 *
 * Given integers must be coprime
 */ {
    TInteger result = I_ONE;

    while (pow(a, result, n) != I_ONE) {
        result = result + I_ONE;
    }

    return result;
}

std::string Agrawal::check(const TInteger &a) const {

    Polynomial taste;
    taste + Indeterminate{4, 2};
    taste + Indeterminate{3, 0};
    taste + Indeterminate{2, 1};
    taste + Indeterminate{1, 2};

    return taste;

    std::string fast_result = basic_check(a);
    if (fast_result != "") {
        return fast_result;
    }

    if (is_perfect_power(a)) {
        return NOT_PRIME;
    }

    TInteger r = I_TWO, log2a2 = pow(kinda_log2(a), I_TWO);

    while (true) {
        if (! coprime(a, r)) {
            r = r + I_ONE;
            continue;
        }
        if (ord(a, r) > log2a2) {
            break;
        }
        r = r + I_ONE;
    }

    TInteger j;

    for (j = TInteger(23); // not starts from 2 because we already
        j <= min(r, a - I_ONE);  // checked 2, 3, 5,.. in basic_check()
        j = j + I_TWO // and here too
    ) {
        if (a % j == I_ZERO) {
            return NOT_PRIME;
        }
    }

    if (a <= r) {
        return IS_PRIME;
    }

    for (j = I_ONE; j != (r - I_ONE) * a; j = j + I_ONE) {
        Polynomial left_exp = binom(j, a);
        left_exp % x_pow_a_minus_1(r);
        return left_exp;

        if (left_exp != x_pow_a_plus_b(a, j)) {
            return NOT_PRIME;
        }
    }

    return IS_PRIME;
}