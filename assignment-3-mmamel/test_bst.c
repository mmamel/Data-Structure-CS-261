/*
 * This file contains executable code for testing your BST implementation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

/*
 * This is the data that's used to test this program.  It forms a tree that
 * looks like this:
 *
 *               64
 *              /  \
 *             /    \
 *            /      \
 *           /        \
 *          32        96
 *         /  \      /  \
 *        /    \    /    \
 *       16    48  80    112
 *      /  \     \   \   /  \
 *     8   24    56  88 104 120
 */
#define NUM_TEST_DATA 13
const int TEST_DATA[NUM_TEST_DATA] =
  {64, 32, 96, 16, 48, 80, 112, 8, 24, 56, 88, 104, 120};

/*
 * This array contains values from the TEST_DATA array above that we'll try
 * to remove from the BST.
 */
#define NUM_DATA_TO_REMOVE 4
const int TEST_DATA_TO_REMOVE[NUM_DATA_TO_REMOVE] = {16, 56, 64, 80};

/*
 * This is a helper function that's used to compare integers when sorting with
 * qsort().
 */
int cmp_ints(const void* a, const void* b) {
  return *(int*)a - *(int*)b;
}

int main(int argc, char** argv) {
  /*
   * Create a new BST and insert the testing data into it.  The testing data
   * is inserted in such a way that the value is equal to the address of the
   * corresponding key (which comes from the TEST_DATA array above).  In other
   * words, for any given key, we'll be able to verify that the tree contains
   * the correct value by comparing key == *value.
   */
  printf("== Creating BST...\n");
  struct bst* bst = bst_create();
  printf("\n== Inserting %d values into BST...\n", NUM_TEST_DATA);
  for (int i = 0; i < NUM_TEST_DATA; i++) {
    bst_insert(bst, TEST_DATA[i], (void*)&TEST_DATA[i]);
  }

  /*
   * Make sure bst_size() returns the correct value.
   */
  printf("\n== Checking correct value from bst_size(): %d (expected %d)\n",
    bst_size(bst), NUM_TEST_DATA);

  /*
   * Test that we can successfully lookup all of the values we know are in the
   * BST.
   */
  printf("\n== Looking up values we know should be in the BST...\n");
  for (int i = 0; i < NUM_TEST_DATA; i++) {
    int* value = bst_get(bst, TEST_DATA[i]);
    if (value) {
      printf("  -- bst_get(%3d): %3d (expected %3d)\n", TEST_DATA[i], *value,
        TEST_DATA[i]);
    } else {
      printf("  -- bst_get(%3d) unexpectedly returned NULL\n", TEST_DATA[i]);
    }
  }

  /*
   * Test that we *can't* successfully find any values we know shouldn't be in
   * the BST.  To do this, create a sorted copy of the test data that will
   * allow us to more easily determine which values shouldn't be in the BST.
   */
  int* sorted = malloc(NUM_TEST_DATA * sizeof(int));
  memcpy(sorted, TEST_DATA, NUM_TEST_DATA * sizeof(int));
  qsort(sorted, NUM_TEST_DATA, sizeof(int), cmp_ints);
  printf("\n== Looking up values we know should NOT be in the BST...\n");
  for (int i = 0, k = 0; i < sorted[NUM_TEST_DATA - 1]; i++) {
    if (i == sorted[k]) {
      /*
       * If i is equal to a key we know is in the BST, skip it.
       */
      k++;
    } else if (bst_get(bst, i) != NULL) {
      printf("  -- bst_get(%3d) unexpectedly returned a non-NULL value\n", i);
    }
  }

  /*
   * Test removing keys from the BST.  After removing each key, make sure
   * it's no longer present in the BST.
   */
  printf("\n== Removing keys from BST...\n");
  for (int i = 0; i < NUM_DATA_TO_REMOVE; i++) {
    bst_remove(bst, TEST_DATA_TO_REMOVE[i]);
    int* value = bst_get(bst, TEST_DATA_TO_REMOVE[i]);
    if (value) {
      printf("  -- key %3d still present in BST after removal, value: %d\n",
        TEST_DATA_TO_REMOVE[i], *value);
    }
  }





//int* value1 = bst_get(bst, 56);
  /*
   * Make sure bst_size() still returns the correct value.
   */
  // printf("\n== Checking correct value from bst_size(): %d (expected %d)\n",
  //   bst_size(bst), NUM_TEST_DATA - NUM_DATA_TO_REMOVE);

  /*
   * Test that all of the values we know should still be in the BST are indeed
   * there.
   */
  printf("\n== Looking up values we know should still be in the BST...\n");
  for (int i = 0, k = 0; i < NUM_TEST_DATA; i++) {
    /*
     * If the current key is one we've already removed, skip over it.
     */
    if (sorted[i] == TEST_DATA_TO_REMOVE[k]) {
      k++;
      continue;
    }

    int* value = bst_get(bst, sorted[i]);
    if (value) {
      printf("  -- bst_get(%3d): %3d (expected %3d)\n", sorted[i], *value,
        sorted[i]);
    } else {
      printf("  -- bst_get(%3d) unexpectedly returned NULL\n", sorted[i]);
    }
  }

  free(sorted);
  bst_free(bst);

  return 0;
}
