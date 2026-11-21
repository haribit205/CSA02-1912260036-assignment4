#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

struct Date {
    int day;
    int month;
    int year;
};

struct BloodPressure {
    int systolic;
    int diastolic;
};

struct Patient {
    char name[50];
    int age;
    char phone[15];
    struct BloodPressure bp;
    struct Date visitDate;
};

int addPatient(struct Patient registerList[], int *count, const struct Patient *newPatient) {
    if (registerList == NULL || count == NULL || newPatient == NULL) {
        return 0;
    }
    if (*count >= MAX_PATIENTS) {
        printf("Error: Patient register is full (max %d).\n", MAX_PATIENTS);
        return 0;
    }
    if (newPatient->age < 0 || newPatient->age > 130) {
        printf("Error: Invalid age (%d).\n", newPatient->age);
        return 0;
    }
    registerList[*count] = *newPatient;
    (*count)++;
    return 1;
}

void sortPatientsByAge(struct Patient registerList[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < count; j++) {
            if (registerList[j].age < registerList[minIdx].age) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            struct Patient temp = registerList[i];
            registerList[i] = registerList[minIdx];
            registerList[minIdx] = temp;
        }
    }
}

void printPatients(const struct Patient registerList[], int count) {
    printf("%-20s %-5s %-13s %-10s %-12s\n", "Name", "Age", "Phone", "BP (mmHg)", "Visit Date");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-20s %-5d %-13s %3d/%-6d %02d/%02d/%04d\n",
               registerList[i].name,
               registerList[i].age,
               registerList[i].phone,
               registerList[i].bp.systolic,
               registerList[i].bp.diastolic,
               registerList[i].visitDate.day,
               registerList[i].visitDate.month,
               registerList[i].visitDate.year);
    }
}

int main(void) {
    struct Patient patients[MAX_PATIENTS];
    int count = 0;

    struct Patient p1 = {"Arun Kumar", 45, "9876543210", {130, 85}, {12, 10, 2026}};
    struct Patient p2 = {"Meena Devi", 29, "9123456789", {118, 76}, {12, 10, 2026}};
    struct Patient p3 = {"Suresh Babu", 62, "9988776655", {145, 92}, {13, 10, 2026}};

    addPatient(patients, &count, &p1);
    addPatient(patients, &count, &p2);
    addPatient(patients, &count, &p3);

    printf("Registered Patients (Sorted by Age):\n");
    sortPatientsByAge(patients, count);
    printPatients(patients, count);

    printf("\nsizeof(struct Patient) = %zu bytes\n", sizeof(struct Patient));
    return 0;
}
