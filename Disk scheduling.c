#include <stdio.h>
#include <stdlib.h>

int cmp_asc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int cmp_desc(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

void FCFS(int queue[], int n, int head) {
    int seek_time = 0;
    printf("Disk traversal order\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", queue[i]);
        seek_time += abs(queue[i] - head);
        head = queue[i];
    }
    printf("\nTotal seek time = %d\n", seek_time);
}

void SCAN(int queue[], int n, int head, int max_cylinders, int direction) {
    int i, seek_time = 0, current_pos = head;
    int *left = (int *)malloc((n+1) * sizeof(int));  // For elements <= head
    int *right = (int *)malloc((n+1) * sizeof(int)); // For elements > head
    int left_count = 0, right_count = 0;

    // Separate requests into left and right of the head
    for (i = 0; i < n; i++) {
        if (queue[i] <= head) {
            left[left_count++] = queue[i];
        } else {
            right[right_count++] = queue[i];
        }
    }

    // Sort left in descending and right in ascending order
    qsort(left, left_count, sizeof(int), cmp_desc);
    qsort(right, right_count, sizeof(int), cmp_asc);

    // SCAN movement
    printf("Disk traversal order\n");
    if (direction == 1) { // Increasing order
        for (i = 0; i < right_count; i++) {
            printf("%d ", right[i]);
            seek_time += abs(right[i] - current_pos);
            current_pos = right[i];
        }
        if (left_count > 0) {  // Move to the last element on the left if there are any
            seek_time += abs(max_cylinders - current_pos); // Move to the end
            current_pos = max_cylinders;
            seek_time += abs(current_pos - left[0]); // Move to the first element on the left
            current_pos = left[0];
            for (i = 0; i < left_count; i++) {
                printf("%d ", left[i]);
                seek_time += abs(left[i] - current_pos);
                current_pos = left[i];
            }
        }
    } else { // Decreasing order
        for (i = 0; i < left_count; i++) {
            printf("%d ", left[i]);
            seek_time += abs(left[i] - current_pos);
            current_pos = left[i];
        }
        if (right_count > 0) {  // Move to the last element on the right if there are any
            seek_time += abs(current_pos - 0); // Move to the beginning
            current_pos = 0;
            seek_time += abs(current_pos - right[0]); // Move to the first element on the right
            current_pos = right[0];
            for (i = 0; i < right_count; i++) {
                printf("%d ", right[i]);
                seek_time += abs(right[i] - current_pos);
                current_pos = right[i];
            }
        }
    }
    printf("\nTotal seek time = %d\n", (seek_time-2));

    free(left);
    free(right);
}

void C_SCAN(int queue[], int n, int head, int max_cylinders, int direction) {
    int i, seek_time = 0, current_pos = head;
    int *left = (int *)malloc((n+1) * sizeof(int));  // For elements <= head
    int *right = (int *)malloc((n+1) * sizeof(int)); // For elements > head
    int left_count = 0, right_count = 0;

    // Separate requests into left and right of the head
    for (i = 0; i < n; i++) {
        if (queue[i] <= head) {
            left[left_count++] = queue[i];
        } else {
            right[right_count++] = queue[i];
        }
    }

    // Sort left and right in ascending order
    qsort(left, left_count, sizeof(int), cmp_asc);
    qsort(right, right_count, sizeof(int), cmp_asc);

    // C-SCAN movement
    printf("Disk traversal order\n");
    if (direction == 1) { // Increasing order
        for (i = 0; i < right_count; i++) {
            printf("%d ", right[i]);
            seek_time += abs(right[i] - current_pos);
            current_pos = right[i];
        }
        if (left_count > 0) {
            seek_time += abs(max_cylinders - current_pos); // Move to the end
            seek_time += max_cylinders; // Wrap around to 0
            current_pos = 0; // Move to the beginning
            for (i = 0; i < left_count; i++) {
                printf("%d ", left[i]);
                seek_time += abs(left[i] - current_pos);
                current_pos = left[i];
            }
        }
    } else { // Decreasing order
        for (i = left_count - 1; i >= 0; i--) {
            printf("%d ", left[i]);
            seek_time += abs(left[i] - current_pos);
            current_pos = left[i];
        }
        if (right_count > 0) {
            seek_time += abs(current_pos - 0); // Move to the beginning
            seek_time += max_cylinders; // Wrap around to the end
            current_pos = max_cylinders; // Move to the end
            for (i = right_count - 1; i >= 0; i--) {
                printf("%d ", right[i]);
                seek_time += abs(right[i] - current_pos);
                current_pos = right[i];
            }
        }
    }
    printf("\nTotal seek time = %d\n", (seek_time-2));

    free(left);
    free(right);
}

int main() {
    int max_cylinders, n, head, choice, direction;
    printf("Enter the maximum number of cylinders: ");
    scanf("%d", &max_cylinders);
    printf("Enter the number of disk queue elements: ");
    scanf("%d", &n);

    int *queue = (int *)malloc(n * sizeof(int));
    printf("Enter the disk queue elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &queue[i]);
    }

    printf("Enter the disk start starting position: ");
    scanf("%d", &head);

    while (1) {
        printf("-----MENU-----\n");
        printf("1. FCFS\n");
        printf("2. SCAN\n");
        printf("3. C-SCAN\n");
        printf("4. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                FCFS(queue, n, head);
                break;
            case 2:
                printf("****Direction of traversal****\n");
                printf("1. Increasing order\n");
                printf("2. Decreasing order\n");
                printf("Enter the direction of traversal: ");
                scanf("%d", &direction);
                SCAN(queue, n, head, max_cylinders, direction);
                break;
            case 3:
                printf("****Direction of traversal****\n");
                printf("1. Increasing order\n");
                printf("2. Decreasing order\n");
                printf("Enter the direction of traversal: ");
                scanf("%d", &direction);
                C_SCAN(queue, n, head, max_cylinders, direction);
                break;
            case 4:
                free(queue);
                exit(0);
            default:
                printf("Invalid choice!\n");
                break;
        }
    }

    return 0;
}

