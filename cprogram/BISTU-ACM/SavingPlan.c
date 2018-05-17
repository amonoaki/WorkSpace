//SavingPlan.c
#include <stdio.h>

int main(void)
{
    int i, temp, money = 0, save = 0, budget[12];

    for (i = 0; i < 12; i++) {
        scanf("%d", &budget[i]);
    }

    for (i = 0; i < 12; i++) {
        money += 300;
        if (money < budget[i]) {
            money = -(i+1);
            break;
        } else {
            money -= budget[i];
            if (money >= 100) {
                temp = (money % 100) * 100;
                save += temp;
                money -= temp;
            }
        }
    }

    if (money > 0) {
        money += save * 1.2;
    }

    printf("%d", money);    

    return 0;
}
