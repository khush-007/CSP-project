// main.c - Main driver program for CPU Scheduling Visualizer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"

void display_menu() {
    printf("\n============================================================\n");
    printf("|        CPU SCHEDULING VISUALIZER v1.0                    |\n");
    printf("|        Process Management Simulator                      |\n");
    printf("============================================================\n\n");
    printf("  1. [FILE] Load Processes from File (processes.txt)\n");
    printf("  2. [INPUT] Enter Processes Manually\n");
    printf("  3. [FCFS] Run FCFS (First Come First Serve)\n");
    printf("  4. [SJF] Run SJF Non-Preemptive\n");
    printf("  5. [SRTF] Run SJF Preemptive (SRTF)\n");
    printf("  6. [PRIORITY] Run Priority Non-Preemptive\n");
    printf("  7. [PRIORITY] Run Priority Preemptive\n");
    printf("  8. [RR] Run Round Robin\n");
    printf("  9. [VIEW] View Current Gantt Chart\n");
    printf(" 10. [SAVE] Save Last Results to File\n");
    printf(" 11. [COMPARE] Compare All Algorithms\n");
    printf(" 12. [EXIT] Exit Program\n");
    printf("\n============================================================\n");
    printf("Enter your choice: ");
}

void compare_algorithms() {
    if (process_count == 0) {
        printf("\n[X] No processes loaded. Load processes first!\n");
        return;
    }
    
    printf("\n============================================================\n");
    printf("|             ALGORITHM COMPARISON                         |\n");
    printf("============================================================\n\n");
    
    // Store original process data
    Process backup[MAX_PROCESSES];
    for (int i = 0; i < process_count; i++) {
        backup[i] = processes[i];
    }
    
    typedef struct {
        char name[30];
        float avg_tat;
        float avg_wt;
        float avg_rt;
    } AlgoResult;
    
    AlgoResult results[6];
    int result_count = 0;
    
    // Test each algorithm
    const char* algo_names[] = {
        "FCFS", "SJF (Non-Preemptive)", "SJF (Preemptive)", 
        "Priority (Non-Preemptive)", "Priority (Preemptive)", "Round Robin (Q=2)"
    };
    
    void (*algorithms[])() = {
        fcfs, sjf_non_preemptive, sjf_preemptive,
        priority_non_preemptive, priority_preemptive, NULL
    };
    
    for (int a = 0; a < 6; a++) {
        // Restore original data
        for (int i = 0; i < process_count; i++) {
            processes[i] = backup[i];
        }
        
        if (a == 5) {
            round_robin(2);
        } else {
            algorithms[a]();
        }
        
        // Calculate averages
        float total_tat = 0, total_wt = 0, total_rt = 0;
        for (int i = 0; i < process_count; i++) {
            total_tat += processes[i].turnaround_time;
            total_wt += processes[i].waiting_time;
            total_rt += processes[i].response_time;
        }
        
        strcpy(results[result_count].name, algo_names[a]);
        results[result_count].avg_tat = total_tat / process_count;
        results[result_count].avg_wt = total_wt / process_count;
        results[result_count].avg_rt = total_rt / process_count;
        result_count++;
    }
    
    // Display comparison
    printf("+--------------------------------+-------+-------+-------+\n");
    printf("| Algorithm                      |  TAT  |  WT   |  RT   |\n");
    printf("+--------------------------------+-------+-------+-------+\n");
    
    for (int i = 0; i < result_count; i++) {
        printf("| %-30s | %5.2f | %5.2f | %5.2f |\n",
               results[i].name,
               results[i].avg_tat,
               results[i].avg_wt,
               results[i].avg_rt);
    }
    
    printf("+--------------------------------+-------+-------+-------+\n\n");
    
    // Find best algorithm
    int best_wt = 0;
    for (int i = 1; i < result_count; i++) {
        if (results[i].avg_wt < results[best_wt].avg_wt) {
            best_wt = i;
        }
    }
    
    printf(">>> Best Algorithm (Lowest Avg. Waiting Time): %s (%.2f)\n\n",
           results[best_wt].name, results[best_wt].avg_wt);
    
    // Restore original data
    for (int i = 0; i < process_count; i++) {
        processes[i] = backup[i];
    }
}

int main() {
    int choice, quantum;
    char last_algorithm[50] = "";
    
    while (1) {
        display_menu();
        
        // Clear input buffer and handle invalid input
        if (scanf("%d", &choice) != 1) {
            // Clear invalid input
            while (getchar() != '\n');
            printf("\n[X] Invalid input! Please enter a number.\n");
            continue;
        }
        // Clear newline character
        while (getchar() != '\n');
        
        switch (choice) {
            case 1:
                load_from_file();
                break;
                
            case 2:
                input_manually();
                break;
                
            case 3:
                if (process_count == 0) {
                    printf("\n[X] No processes loaded. Load processes first!\n");
                    break;
                }
                printf("\n>>> Running FCFS...\n");
                fcfs();
                strcpy(last_algorithm, "FCFS");
                display_gantt_chart();
                display_results("FCFS");
                break;
                
            case 4:
                if (process_count == 0) {
                    printf("\n[X] No processes loaded. Load processes first!\n");
                    break;
                }
                printf("\n>>> Running SJF Non-Preemptive...\n");
                sjf_non_preemptive();
                strcpy(last_algorithm, "SJF Non-Preemptive");
                display_gantt_chart();
                display_results("SJF Non-Preemptive");
                break;
                
            case 5:
                if (process_count == 0) {
                    printf("\n[X] No processes loaded. Load processes first!\n");
                    break;
                }
                printf("\n>>> Running SJF Preemptive (SRTF)...\n");
                sjf_preemptive();
                strcpy(last_algorithm, "SJF Preemptive (SRTF)");
                display_gantt_chart();
                display_results("SJF Preemptive");
                break;
                
            case 6:
                if (process_count == 0) {
                    printf("\n[X] No processes loaded. Load processes first!\n");
                    break;
                }
                printf("\n>>> Running Priority Non-Preemptive...\n");
                priority_non_preemptive();
                strcpy(last_algorithm, "Priority Non-Preemptive");
                display_gantt_chart();
                display_results("Priority Non-Preemptive");
                break;
                
            case 7:
                if (process_count == 0) {
                    printf("\n[X] No processes loaded. Load processes first!\n");
                    break;
                }
                printf("\n>>> Running Priority Preemptive...\n");
                priority_preemptive();
                strcpy(last_algorithm, "Priority Preemptive");
                display_gantt_chart();
                display_results("Priority Preemptive");
                break;
                
            case 8:
                if (process_count == 0) {
                    printf("\n[X] No processes loaded. Load processes first!\n");
                    break;
                }
                printf("\n>>> Enter time quantum: ");
                if (scanf("%d", &quantum) != 1 || quantum <= 0) {
                    while (getchar() != '\n');
                    printf("\n[X] Invalid quantum! Please enter a positive number.\n");
                    break;
                }
                while (getchar() != '\n');
                printf("\n>>> Running Round Robin (Quantum=%d)...\n", quantum);
                round_robin(quantum);
                sprintf(last_algorithm, "Round Robin (Q=%d)", quantum);
                display_gantt_chart();
                display_results(last_algorithm);
                break;
                
            case 9:
                display_gantt_chart();
                break;
                
            case 10:
                if (gantt_count == 0) {
                    printf("\n[X] No results to save. Run an algorithm first!\n");
                    break;
                }
                save_results(last_algorithm);
                break;
                
            case 11:
                compare_algorithms();
                break;
                
            case 12:
                printf("\n>>> Thank you for using CPU Scheduling Visualizer!\n");
                printf("    Developed as an OS Project\n\n");
                exit(0);
                
            default:
                printf("\n[X] Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}