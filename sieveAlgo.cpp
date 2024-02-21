#include <iostream>
#include <vector>

void sieveOfEratosthenes(int n) {
    std::vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int p = 2; p * p <= n; ++p) {
        if (isPrime[p]) {
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }

    std::cout << "Prime numbers up to " << n << " are:\n";
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) {
            std::cout << i << " ";
        }
    }
    std::cout << "\n";
}

int main() {
    int limit;
    std::cout << "Enter the limit to find prime numbers up to: ";
    std::cin >> limit;

    sieveOfEratosthenes(limit);

    return 0;
}
