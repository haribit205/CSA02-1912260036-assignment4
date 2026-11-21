#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 20
#define MAX_COMBO_COMPONENTS 3

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int hour;
    int minute;
} Time;

typedef enum {
    PACKAGED = 0,
    COOKED = 1,
    COMBO = 2
} ItemCategory;

typedef struct {
    int componentIds[MAX_COMBO_COMPONENTS];
    int componentCount;
} ComboDetails;

typedef union {
    Date expiryDate;          /* For PACKAGED items */
    Time preparedTime;        /* For COOKED items */
    ComboDetails combo;       /* For COMBO meals */
} ItemMeta;

typedef struct {
    int id;
    char name[35];
    float price;
    int stock;
    int soldQty;
    float totalRevenue;
    ItemCategory category;
    ItemMeta meta;
} CanteenItem;

/* Global/static daily revenue tracker */
static float g_totalDailyRevenue = 0.0f;

/* Convert Date to serial days for reliable comparison */
long dateToDays(Date d) {
    return (long)d.year * 365L + (long)d.month * 30L + (long)d.day;
}

CanteenItem* findItemById(CanteenItem menu[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (menu[i].id == id) return &menu[i];
    }
    return NULL;
}

int recordSale(CanteenItem menu[], int count, int itemId, int qty) {
    if (qty <= 0) {
        printf("[SALE ERROR] Quantity must be positive.\n");
        return 0;
    }
    CanteenItem *item = findItemById(menu, count, itemId);
    if (item == NULL) {
        printf("[SALE ERROR] Item ID %d not found.\n", itemId);
        return 0;
    }
    if (item->stock < qty) {
        printf("[STOCK WARNING] Cannot sell %d x '%s' (ID %d): Only %d in stock!\n",
               qty, item->name, item->id, item->stock);
        return 0;
    }
    item->stock -= qty;
    item->soldQty += qty;
    float saleAmount = item->price * (float)qty;
    item->totalRevenue += saleAmount;
    g_totalDailyRevenue += saleAmount;
    printf("[SALE OK] Sold %d x %-20s | Amount: Rs. %6.2f | Remaining Stock: %d\n",
           qty, item->name, saleAmount, item->stock);
    return 1;
}

void warnExpiringItems(const CanteenItem menu[], int count, Date today) {
    long todayDays = dateToDays(today);
    printf("\n=== EXPIRY WARNING REPORT (Current Date: %02d/%02d/%04d) ===\n",
           today.day, today.month, today.year);
    int warnings = 0;
    for (int i = 0; i < count; i++) {
        if (menu[i].category == PACKAGED) {
            long diff = dateToDays(menu[i].meta.expiryDate) - todayDays;
            if (diff >= 0 && diff <= 2) {
                printf("[EXPIRY ALERT] ID %d (%s) expires on %02d/%02d/%04d (in %ld day(s))! Stock: %d\n",
                       menu[i].id, menu[i].name,
                       menu[i].meta.expiryDate.day,
                       menu[i].meta.expiryDate.month,
                       menu[i].meta.expiryDate.year,
                       diff, menu[i].stock);
                warnings++;
            }
        }
    }
    if (warnings == 0) {
        printf("No packaged items expiring within 2 days.\n");
    }
}

void sortItemsByRevenueDesc(CanteenItem menu[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < count; j++) {
            if (menu[j].totalRevenue > menu[maxIdx].totalRevenue) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            CanteenItem temp = menu[i];
            menu[i] = menu[maxIdx];
            menu[maxIdx] = temp;
        }
    }
}

void printDailyBillSummary(CanteenItem menu[], int count) {
    sortItemsByRevenueDesc(menu, count);
    printf("\n=== DAILY BILL SUMMARY (SORTED BY REVENUE DESCENDING) ===\n");
    printf("%-5s %-22s %-10s %-8s %-6s %-10s\n", "ID", "Item Name", "Category", "Price", "Sold", "Revenue");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        const char *catStr = (menu[i].category == PACKAGED) ? "Packaged" :
                             (menu[i].category == COOKED)   ? "Cooked"   : "Combo";
        printf("%-5d %-22s %-10s %8.2f %-6d %10.2f\n",
               menu[i].id, menu[i].name, catStr,
               menu[i].price, menu[i].soldQty, menu[i].totalRevenue);
    }
    printf("-------------------------------------------------------------------\n");
    printf("TOTAL CANTEEN REVENUE TODAY: Rs. %.2f\n", g_totalDailyRevenue);
}

int main(void) {
    Date today = {12, 10, 2026};

    CanteenItem menu[4] = {
        {101, "Fruit Juice Tetra", 35.0f, 15, 0, 0.0f, PACKAGED, {.expiryDate = {13, 10, 2026}}},
        {102, "Masala Dosa",       50.0f, 20, 0, 0.0f, COOKED,   {.preparedTime = {8, 30}}},
        {103, "Biscuit Pack",      20.0f, 10, 0, 0.0f, PACKAGED, {.expiryDate = {25, 11, 2026}}},
        {104, "Student Lunch Combo", 80.0f, 8, 0, 0.0f, COMBO,   {.combo = {{101, 102, 103}, 3}}}
    };
    int itemCount = 4;

    printf("=== RECORDING CANTEEN SALES ===\n");
    recordSale(menu, itemCount, 102, 6);   /* Normal sale: 6 Masala Dosas = 300.00 */
    recordSale(menu, itemCount, 104, 4);   /* Normal sale: 4 Combos = 320.00 */
    recordSale(menu, itemCount, 101, 5);   /* Normal sale: 5 Fruit Juices = 175.00 */
    recordSale(menu, itemCount, 104, 10);  /* Exceeds stock (only 4 left) -> Rejected */

    warnExpiringItems(menu, itemCount, today);
    printDailyBillSummary(menu, itemCount);
    return 0;
}
