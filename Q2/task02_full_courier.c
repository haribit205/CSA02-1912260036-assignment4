#include <stdio.h>
#include <string.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char name[40];
    char city[25];
    int pincode;
} PartyAddress;

typedef enum {
    NORMAL = 0,
    EXPRESS = 1
} ServiceType;

typedef struct {
    int id;
    float weight;
    Date bookingDate;
    PartyAddress sender;
    PartyAddress receiver;
    ServiceType service;
    float charge;
} Parcel;

void sortParcelsByWeight(Parcel list[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (list[j].weight < list[minIdx].weight) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Parcel temp = list[i];
            list[i] = list[minIdx];
            list[minIdx] = temp;
        }
    }
}

void listParcelsByCity(const Parcel list[], int n, const char *targetCity) {
    int found = 0;
    printf("\nParcels destined for city: %s\n", targetCity);
    for (int i = 0; i < n; i++) {
        if (strcmp(list[i].receiver.city, targetCity) == 0) {
            printf("ID: %d | Weight: %.1f kg | Receiver: %s (%s - %d) | Service: %s | Charge: Rs. %.2f\n",
                   list[i].id, list[i].weight, list[i].receiver.name,
                   list[i].receiver.city, list[i].receiver.pincode,
                   list[i].service == EXPRESS ? "Express" : "Normal",
                   list[i].charge);
            found = 1;
        }
    }
    if (!found) {
        printf("No parcels found for %s.\n", targetCity);
    }
}

int main(void) {
    Parcel bookings[3] = {
        {501, 4.5f, {12, 10, 2026}, {"Ravi", "Chennai", 600001}, {"Karthik", "Madurai", 625001}, EXPRESS, 350.0f},
        {502, 1.2f, {12, 10, 2026}, {"Anita", "Salem", 636001}, {"Priya", "Chennai", 600077}, NORMAL, 120.0f},
        {503, 2.8f, {13, 10, 2026}, {"Divya", "Trichy", 620001}, {"Vijay", "Chennai", 600028}, EXPRESS, 240.0f}
    };

    Parcel *ptr = bookings;
    printf("3rd Parcel Receiver PIN (dot operator)  : %d\n", bookings[2].receiver.pincode);
    printf("3rd Parcel Receiver PIN (arrow operator): %d\n", (ptr + 2)->receiver.pincode);

    sortParcelsByWeight(bookings, 3);
    printf("\nAll Parcels Sorted by Weight:\n");
    for (int i = 0; i < 3; i++) {
        printf("ID: %d | Weight: %.1f kg | To: %s (%d) | Date: %02d/%02d/%04d\n",
               bookings[i].id, bookings[i].weight, bookings[i].receiver.city,
               bookings[i].receiver.pincode, bookings[i].bookingDate.day,
               bookings[i].bookingDate.month, bookings[i].bookingDate.year);
    }

    listParcelsByCity(bookings, 3, "Chennai");
    return 0;
}
