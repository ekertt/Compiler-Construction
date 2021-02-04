gcd (a, b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

fac (n) {
    int factorial;
    for (i = 1; i <= n; i++) {
        factorial = factorial * i;
    }

    return factorial;
}

fib (n) {
    if (n <= 1)
        return n;
    return fib(n-1) + fib(n-2);
}

isprime(n) {
    if (n / n == 1 && n / 1 == n){
        return true;
    } else {
        return 0;
    }
}