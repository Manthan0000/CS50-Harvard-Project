#include <cs50.h>
#include <stdio.h>
#include <math.h>

int is_valid(long number);
int get_card_type(long number);
int luhn_checksum(long number);

int main(void) {
    long number = get_long("Number: ");
    if (is_valid(number)) {
        int card_type = get_card_type(number);
        if (card_type == 1) {
            printf("AMEX\n");
        } else if (card_type == 2) {
            printf("MASTERCARD\n");
        } else if (card_type == 3) {
            printf("VISA\n");
        } else {
            printf("INVALID\n");
        }
    } else {
        printf("INVALID\n");
    }
}

int is_valid(long number) {
    return (luhn_checksum(number) % 10 == 0) ? 1 : 0;
}

int luhn_checksum(long number) {
    int sum = 0;
    int alternate = 0;
    while (number > 0) {
        int digit = number % 10;
        if (alternate) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }
        sum += digit;
        alternate = !alternate;
        number /= 10;
    }
    return sum;
}

int get_card_type(long number) {
    int length = 0;
    int start_digits = 0;
    long temp = number;
    while (temp > 0) {
        if (temp >= 10 && temp < 100) {
            start_digits = temp;
        }
        length++;
        temp /= 10;
    }
    if (length == 15 && (start_digits == 34 || start_digits == 37)) {
        return 1;
    }
    if (length == 16 && (start_digits >= 51 && start_digits <= 55)) {
        return 2;
    }
    if ((length == 13 || length == 16) && (number / (long)pow(10, length - 1) == 4)) {
        return 3;
    }
    return 0;
}
