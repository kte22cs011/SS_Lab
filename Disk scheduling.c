#include <stdio.h>
#include <stdlib.h>

void fcfs(int requests[], int n, int head) {
    int seek_time = 0;
    printf("FCFS disk scheduling\nDisk traversal order\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
        seek_time += abs(requests[i] - head);
        head = requests[i];
    }
    printf("\nTotal seek time: %d\n", seek_time);
}

void scan(int requests[], int n, int head, int direction, int max_cylinders) {
    int seek_time = 0;
    int *left = (int *)malloc((n + 1) * sizeof(int));
    int *right = (int *)malloc((n + 1) * sizeof(int));
    int left_size = 0, right_size = 0;

    left[left_size++] = 0;
    right[right_size++] = max_cylinders - 1;

    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            left[left_size++] = requests[i];
        } else {
            right[right_size++] = requests[i];
        }
    }

    printf("SCAN disk scheduling\n****Direction of traversal****\n");
    if (direction == 1) {
        printf("Increasing order\nDisk traversal order\n");
        for (int i = 0; i < right_size; i++) {
            for (int j = i + 1; j < right_size; j++) {
                if (right[i] > right[j]) {
                    int temp = right[i];
                    right[i] = right[j];
                    right[j] = temp;
                }
            }
        }
        for (int i = 0; i < left_size; i++) {
            for (int j = i + 1; j < left_size; j++) {
                if (left[i] < left[j]) {
                    int temp = left[i];
                    left[i] = left[j];
                    left[j] = temp;
                }
            }
        }
        for (int i = 0; i < right_size; i++) {
            printf("%d ", right[i]);
            seek_time += abs(right[i] - head);
            head = right[i];
        }
        for (int i = 0; i < left_size; i++) {
            printf("%d ", left[i]);
            seek_time += abs(left[i] - head);
            head = left[i];
        }
    } else {
        printf("Decreasing order\nDisk traversal order\n");
        for (int i = 0; i < left_size; i++) {
            for (int j = i + 1; j < left_size; j++) {
                if (left[i] > left[j]) {
                    int temp = left[i];
                    left[i] = left[j];
                    left[j] = temp;
                }
            }
        }
        for (int i = 0; i < right_size; i++) {
            for (int j = i + 1; j < right_size; j++) {
                if (right[i] < right[j]) {
                    int temp = right[i];
                    right[i] = right[j];
                    right[j] = temp;
                }
            }
        }
        for (int i = 0; i < left_size; i++) {
            printf("%d ", left[i]);
            seek_time += abs(left[i] - head);
            head = left[i];
        }
        for (int i = 0; i < right_size; i++) {
            printf("%d ", right[i]);
            seek_time += abs(right[i] - head);
            head = right[i];
        }
    }
    printf("\nTotal seek time: %d\n", seek_time);
    free(left);
    free(right);
}

void cscan(int requests[], int n, int head, int direction, int max_cylinders) {
    int seek_time = 0;
    int *left = (int *)malloc((n + 1) * sizeof(int));
    int *right = (int *)malloc((n + 1) * sizeof(int));
    int left_size = 0, right_size = 0;

    left[left_size++] = 0;
    right[right_size++] = max_cylinders - 1;

    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            left[left_size++] = requests[i];
        } else {
            right[right_size++] = requests[i];
        }
    }

    printf("C-SCAN disk scheduling\n****Direction of traversal****\n");
    if (direction == 1) {
        printf("Increasing order\nDisk traversal order\n");
        for (int i = 0; i < right_size; i++) {
            for (int j = i + 1; j < right_size; j++) {
                if (right[i] > right[j]) {
                    int temp = right[i];
                    right[i] = right[j];
                    right[j] = temp;
                }
            }
        }
        for (int i = 0; i < left_size; i++) {
            for (int j = i + 1; j < left_size; j++) {
                if (left[i] < left[j]) {
                    int temp = left[i];
                    left[i] = left[j];
                    left[j] = temp;
                }
            }
        }
        for (int i = 0; i < right_size; i++) {
            printf("%d ", right[i]);
            seek_time += abs(right[i] - head);
            head = right[i];
        }
        head = 0;
        for (int i = 0; i < left_size; i++) {
            printf("%d ", left[i]);
            seek_time += abs(left[i] - head);
            head = left[i];
        }
    } else {
        printf("Decreasing order\nDisk traversal order\n");
        for (int i = 0; i < left_size; i++) {
            for (int j = i + 1; j < left_size; j++) {
                if (left[i] > left[j]) {
                    int temp = left[i];
                    left[i] = left[j];
                    left[j] = temp;
                }
            }
        }
        for (int i = 0; i < right_size; i++) {
            for (int j = i + 1; j < right_size; j++) {
                if (right[i] < right[j]) {
                    int temp = right[i];
                    right[i] = right[j];
                    right[j] = temp;
                }
            }
        }
        for (int i = 0; i < left_size; i++) {
            printf("%d ", left[i]);
            seek_time += abs(left[i] - head);
            head = left[i];
        }
        head = max_cylinders - 1;
        for (int i = 0; i < right_size; i++) {
            printf("%d ", right[i]);
            seek_time += abs(right[i] - head);
            head = right[i];
        }
    }
    printf("\nTotal seek time: %d\n", seek_time);
    free(left);
    free(right);
}

int main() {
    int max_cylinders, n, head, choice, direction;
    
    printf("Enter the maximum number of cylinders: ");
    scanf("%d", &max_cylinders);
    
    printf("Enter the number of disk queue elements: ");
    scanf("%d", &n);
    
    int requests[n];
    printf("Enter the disk queue elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    
    printf("Enter the disk start starting position: ");
    scanf("%d", &head);
    
    while (1) {
        printf("------MENU------\n");
        printf("1. FCFS\n");
        printf("2. SCAN\n");
        printf("3. C-SCAN\n");
        printf("4. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            fcfs(requests, n, head);
        } else if (choice == 2 || choice == 3) {
            printf("****Direction of traversal****\n");
            printf("1. Increasing order\n");
            printf("2. Decreasing order\n");
            printf("Enter the direction of traversal: ");
            scanf("%d", &direction);
            
            if (choice == 2) {
                scan(requests, n, head, direction, max_cylinders);
            } else {
                cscan(requests, n, head, direction, max_cylinders);
            }
        } else if (choice == 4) {
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}
