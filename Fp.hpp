#pragma once

template<int p>
class Fp {
public:
    Fp(int x = 0) : value(x % p) {}

    int val() const { return value; }

    Fp<p>& operator=(int x) {
        value = x % p;
        return *this;
    }

    Fp<p> operator+(const Fp<p>& other) const {
        return Fp<p>((value + other.value) % p);
    }

    Fp<p> operator-(const Fp<p>& other) const {
        return Fp<p>((value - other.value + p) % p);
    }

    Fp<p> operator*(const Fp<p>& other) const {
        return Fp<p>((value * other.value) % p);
    }

    Fp<p> operator/(const Fp<p>& other) const {
        Fp<p> result;
        for (int i = 0; i < p; ++i) {
            if ((other.value * i) % p == value) {
                result = i;
                break;
            }
        }
        return result;
    }

    Fp<p> operator-() const {
        return Fp<p>((p - value) % p);
    }

    Fp<p>& operator+=(const Fp<p>& other) {
        value = (value + other.value) % p;
        return *this;
    }

    Fp<p>& operator-=(const Fp<p>& other) {
        value = (value - other.value + p) % p;
        return *this;
    }

    Fp<p>& operator*=(const Fp<p>& other) {
        value = (value * other.value) % p;
        return *this;
    }

    Fp<p>& operator/=(const Fp<p>& other) {
        *this = *this / other;
        return *this;
    }

    bool operator==(const Fp<p>& other) const {
        return value == other.value;
    }

    bool operator!=(const Fp<p>& other) const {
        return value != other.value;
    }

private:
    int value;
};
