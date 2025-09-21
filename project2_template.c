#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void gcd_helper(int *d1, int *d2, int *q) {
    int d3;
    *q = *d1 / *d2;
    d3 = *d1 - (*d2 * *q);
    *d1 = *d2;
    *d2 = d3;
}

void check_d1_greatest(int* d1, int* d2) {
    if (*d1 >= *d2) {
        return;
    } else {
        int d3 = *d1;
        *d1 = *d2;
        *d2 = d3;
    }
}

int gcd(int inE, int inZ)
{
    // TO BE FINISHED
	// Must implement Euclid's algorithm
	// NO brute-forcing; violation will lead to zero points
	// NO recursion; violation will lead to zero points

    int d1 = inE;
    int d2 = inZ;
    int q;
    check_d1_greatest(&d1, &d2);
    while (d2 != 0) {
        gcd_helper(&d1, &d2, &q);
    }
    return d1;
}


void testGcd()
{
    int result1 = gcd (29, 288);
    int result2 = gcd (30, 288);
    int result3 = gcd (149, 288);
    int result4 = gcd (2, 4);
    int result5 = gcd (4, 2);

    printf("GCD (29, 288) = %#X \n", result1 );
    printf("GCD (30, 288) = %#X \n", result2 );
    printf("GCD (149, 288) = %#X \n", result3 );
    printf("GCD (2, 4) = %#X \n", result4 );
    printf("GCD (4, 2) = %#X \n", result5 );
}

//
// We assume that inE < inZ
// This implementation follows our slides
// Return:
//	-1: no inverse
//	inverse of inE mod inZ
//
int xgcd(int inE, int inZ)
{
    // TO BE FINISHED
	// Must implement the extended Euclidean algorithm
	// NO brute-forcing; violation will lead to zero points
	// NO recursion; violation will lead to zero points
    int d1 = inZ;
    int d2 = inE;
    int q;
    // int s;
    int t1 = 0;
    int t2 = 1;
    int t_holder = 0;
    int count = 1;
    while (d2 != 0) {
        gcd_helper(&d1, &d2, &q);
        t_holder = t2;
        t2 = t1 - (t2 * q);
        t1 = t_holder;
    }
    if (d1 != 1) {
        return -1;
    }
    if (t1 < 0) {
        return t1 + inZ;
    }
    return t1;
}


int testXgcd()
{
    int result1 = xgcd (29, 288);
    int result2 = xgcd (30, 288);
    int result3 = xgcd (149, 288);
    int result4 = xgcd (2, 4);
    printf("\n");
    printf("29^-1 mod 288  = %#X \n", result1 );
    // printf("29^-1 mod 288  = %d \n", result1 );
    printf("30^-1 mod 288 = %#X \n", result2 );
    // printf("30^-1 mod 288 = %d \n", result2 );
    printf("149^-1 mod 288  = %#X \n", result3 );
    // printf("149^-1 mod 288  = %d \n", result3 );
    printf("2^-1 mod 4 = %#X \n", result4 );
    // printf("2^-1 mod 4 = %d \n", result4 );
    printf("\n");
    return 0;
}


int * keygen (int inP, int inQ, int inE)
{
    int inN = inP * inQ;
    int inZ = (inP - 1) * (inQ - 1);
    // TO BE FINISHED
    if (inE > 1 && inE < inZ) {
        if (gcd(inZ, inE) != 1) {
            printf("Error: invalid e value\n");
            return NULL;
        }
    }
    if (inE < 1) {
        int min = 2;
        int max = inZ;
        inE = rand() % (max - min + 1) + min;
        while (gcd(inZ, inE) != 1) {
            inE = rand() % (max - min + 1) + min;
        }
    }

    int inD = xgcd(inE, inZ);
    int* arr = (int* )malloc(3 * sizeof(int));
    arr[0] = inE;
    arr[1] = inN;
    arr[2] = inD;
    return arr;

}


//
// The following method will return an integer array, with [e, N, d] in this order
//
void testKeygen ()
{
    int * keypair;

    keypair = keygen (17, 19, 29);
    printf("e = %#X \n", *keypair );
    printf("e = %d \n", *keypair );
    printf("N = %#X \n", *( keypair + 1 ) );
    printf("N = %d \n", *( keypair + 1 ) );
    printf("d = %#X \n", *( keypair + 2 ) );
    printf("d = %d \n", *( keypair + 2 ) );

    printf("\n\n\n");
    int* keypair2 = keygen (17, 19, -1);
    printf("e = %#X \n", *keypair2 );
    printf("e = %d \n", *keypair2 );
    printf("N = %#X \n", *( keypair2 + 1 ) );
    printf("N = %d \n", *( keypair2 + 1 ) );
    printf("d = %#X \n", *( keypair2 + 2 ) );
    printf("d = %d \n", *( keypair2 + 2 ) );
}


//
// Calculate c = a^b mod n, with the square-and-multiply algorithm
//
// The following method implements the square-and-multiply algorithm,
//     with Java primitive types
//
// Note that even with primitive types, a^b may well exceed the range of Java int
// For example, 5^20 is too big to be held by a Java primitive integer
//
int modExp (int message, int inE, int inN)
{
    int x = 1;
	int w = message;
	int y = inE;

	while (y > 0) {
		int t = y%2;
		y = y/2;
		if (t == 1) {
			long xLong = x * w;
			x = (int) (xLong % inN);
		}

		long wLong = w * w;
		w = (int) (wLong % inN);
	}

	return x;
}

int encrypt (int message, int inE, int inN)
{
    // TO BE FINISHED
    int x = 1;
    int w = message;
    int y = inE;

    while (y > 0) {
        int bit = y % 2;
        y = y / 2;
        if (bit == 1) {
            long long xLong = (long long) x * (long) (long) w;
            x = (int) (xLong % inN);
        }
        long long wLong = (long long)w * (long long) w;
        w = (int) (wLong % inN);
    }
    return x;
}


int decrypt (int ciphertext, int inD, int inN)
{
    // TO BE FINISHED
    int x = 1;
    int w = ciphertext;
    int y = inD;

    while (y > 0) {
        int bit = y % 2;
        y = y / 2;
        if (bit == 1) {
            long long xLong = (long long) x * (long long) w;
            x = (int) (xLong % inN);
        }

        long long wLong = (long long) w * (long long) w;
        w = (int) (wLong % inN);
    }

    return x;
}


void testRSA ()
{
    int * keypair;

    keypair = keygen (17, 19, 29);

    int m1 = 135;
    int c1 = modExp (m1, *keypair, *( keypair + 1 ) );
    printf("The encryption of (m1=%#X ) is %#X \n", m1, c1 );
    int cleartext1 = modExp (c1, *( keypair + 2), *( keypair + 1 ) );
    printf("The decryption of (c=%#X ) is %#X \n", c1, cleartext1 );

    int m2 = 252;
    int c2 = modExp (m2, *keypair, *( keypair + 1 ) );
    printf ("The encryption of (m2=%#X ) is %#X \n", m2, c2 );
    int cleartext2 = modExp (c2, *( keypair + 2 ), *( keypair + 1 ) );
    printf ("The decryption of (c2=%#X ) is %#X \n", c2, cleartext2 );
}

void testEncyptDecrypt() {
    // keygen returns [E, N, D]
    printf("\n\n");
    int *keypair = keygen (17, 19, 29);
    int message = 1234;
    int encrypted = encrypt(message, *keypair, *(keypair+1));
    int decrypted = decrypt(encrypted, *(keypair+2), *(keypair+1));

    printf("message = %d\nencrypted = %d\ndecrypted = %d", message, encrypted, decrypted);



}

int main()
{
    printf("********** Project 1 output begins **********\n");

    testGcd ();
    testXgcd ();
    testKeygen ();
    testRSA ();
    testEncyptDecrypt();

    return 0;
}
