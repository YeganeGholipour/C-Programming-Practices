#include <stdio.h>

void split_date(int day_of_year, int year, int *month, int *day);

int main() {
    int day_of_year, year, month, day;

    printf("Enter year: ");
    scanf("%d", &year);
    printf("Enter day of the year (1-366): ");
    scanf("%d", &day_of_year);

    split_date(day_of_year, year, &month, &day);

    printf("Equivalent Date: %02d/%02d/%d\n", month, day, year);

    return 0;
}

void split_date(int day_of_year, int year, int *month, int *day) {
    int days_in_months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (is_leap) {
        days_in_months[1] = 29;  
    }

    int i;
    for (i = 0; i < 12; i++) {
        if (day_of_year <= days_in_months[i]) {
            break;
        }
        day_of_year -= days_in_months[i];
    }

    *month = i + 1;  
    *day = day_of_year;
}
