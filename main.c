/*
The code for sending money has a struct called Debt made to be used in an array
to keep track of all debts. The function "transactions", called from the main
function, is used to both print the minimal amount of money needed to settle the
debts and the list of transactions.
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Debt {
  int from;
  int to;
  int amount;
};

int transactions(int n, int m, bool print, struct Debt debts[]) {

  // allocate dynamic size array with zeros
  // size is n+1 to use indices 1 to n for the friends
  int *balance = (int *)calloc(n + 1, sizeof(int));

  int amount = 0;

  for (int i = 0; i < m; i++) { // calculate balances
    balance[debts[i].from] -= debts[i].amount;
    balance[debts[i].to] += debts[i].amount;
  }

  while (true) {
    int max_credit = 0;
    int max_debt = 0;

    for (int i = 1; i <= n; i++) { // find max positive and negative balances
      if (balance[i] > balance[max_credit])
        max_credit = i;
      if (balance[i] < balance[max_debt])
        max_debt = i;
    }
    // if both zero, debts are settled
    if (balance[max_credit] == 0 && balance[max_debt] == 0)
      break;

    // calculate the minimum transfer amount
    int min_transfer = balance[max_credit];
    if (-balance[max_debt] < min_transfer)
      min_transfer = -balance[max_debt];

    // update the balances of the creditor and debtor
    balance[max_credit] -= min_transfer;
    balance[max_debt] += min_transfer;

    amount += min_transfer; // update total amount

    if (print == true) // conditional to print tranactions after total amount
      printf("%d %d %d\n", max_debt, max_credit, min_transfer);
  }

  free(balance);
  return amount;
}

int main(void) {
  int n, m;
  scanf("%d %d", &n, &m);

  struct Debt *debts = (struct Debt *)malloc(m * sizeof(struct Debt));

  for (int i = 0; i < m; i++)
    scanf("%d %d %d", &debts[i].from, &debts[i].to, &debts[i].amount);

  printf("%d\n", transactions(n, m, false, debts)); // print amount of money:

  transactions(n, m, true, debts); // print transactions after
  free(debts);
}
