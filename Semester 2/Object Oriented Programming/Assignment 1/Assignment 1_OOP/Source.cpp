#include <iostream>
#include <stdio.h>
#include <stdbool.h>
/**
* Prints the menu
**/
void menu()
{
    printf("1.Read an array of numbers\n");
    printf("2.Solve 1.a\n");
    printf("3.Solve 1.b\n");
    printf("4.Exit");
    printf("\n");

}
/**
* Reads an array
**/
void read_array(int arr[100], int& n)
{
    printf("The length of the array is:");
    scanf_s("%d", &n);
    int i;
    for (i = 0; i < n; ++i)
    {
        printf("Enter a number to add it into the array:\n");
        scanf_s("%d", &arr[i]);
    }
}
/**
* Prints an array
**/
void print_array(int arr[1001], int& n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

}
/**
* This function gives an answer if the number is prime or not
* Input:a number
* Output:True or False
**/
bool isprime(int n)
{
    int i;
    if (n == 1) {
        return false;
    }
    for (i = 2; i <= n/2; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
/**
* This function prints the prime numbers smaller then n
* Input:A number
* Output:Prime numbers smaller than the number
**/
void prime_numbers_smaller_n() {
    printf("Choose a number:");
    int n;
    scanf_s("%d", &n);
    int i;
    for (i = 2; i <= n; i++) {
        if (isprime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}
/**
This function gives the length of the longest increasing contiguos subsequence,such the sum of that any 2 consecutive 
elements is a prime number.
Input:The array and the length of it
Output:the start of the subsequence and the end
**/
void longest_increasing_contiguous_subsequence(int arr[100], int n,int& min, int& max) {
    if (n <= 1)
        printf("%d ", n);
    int answer = -1, count = 0;
    for (int i = 1; i < n ; i++) {
        if (arr[i] > arr[i - 1]){
            if (isprime(arr[i] + arr[i - 1])) {
                count++;
                if (count > answer) {
                    answer = count;
                    max = i;
                }
            }
            else {
                count = 0;
            }
        }
        else {
            count = 0;
        }
    }
    min = max - answer;
}
int main()
{
    int arr[100];
    int n;
    int min;
    int max;
    while (true) {
        menu();
        int opt;
        scanf_s("%d", &opt);
        if (opt == 1)
        {
            read_array(arr, n);
            print_array(arr, n);
        }if (opt == 2) {
            prime_numbers_smaller_n();
        }if (opt == 3) {
            longest_increasing_contiguous_subsequence(arr, n, min, max);
            int i;
            for (i = min; i <= max; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n");
        }if (opt == 4) {
            return false;
        }
    }
}   