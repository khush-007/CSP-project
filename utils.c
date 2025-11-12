// // utils.c - Utility functions for I/O and display
// #include <stdio.h>
// #include <string.h>
// #include "process.h"

// // Display Gantt Chart
// void display_gantt_chart() {
//     if (gantt_count == 0) {
//         printf("\n❌ No Gantt chart available. Run an algorithm first.\n");
//         return;
//     }
    
//     printf("\n╔════════════════════════════════════════════════════════════╗\n");
//     printf("║                      GANTT CHART                           ║\n");
//     printf("╚════════════════════════════════════════════════════════════╝\n\n");
    
//     // Print process names
//     printf("  ");
//     for (int i = 0; i < gantt_count; i++) {
//         printf("  %s  ", gantt[i].name);
//     }
//     printf("\n");
    
//     // Print top border
//     printf("  ");
//     for (int i = 0; i < gantt_count; i++) {
//         printf("------");
//     }
//     printf("\n");
    
//     // Print timeline
//     printf("%2d", gantt[0].start_time);
//     for (int i = 0; i < gantt_count; i++) {
//         printf("    %2d", gantt[i].end_time);
//     }
//     printf("\n\n");
// }

// // Display results table
// void display_results(const char* algorithm) {
//     printf("\n╔═══════════════════════════════════════════════════════════════════════════╗\n");
//     printf("║                    RESULTS - %s%-30s║\n", algorithm, "");
//     printf("╠═══════╦══════╦═══════╦══════╦═══════╦════════╦═══════╦════════╦═════════╣\n");
//     printf("║  PID  ║ Name ║ AT    ║ BT   ║ Prior ║ CT     ║ TAT   ║ WT     ║ RT      ║\n");
//     printf("╠═══════╬══════╬═══════╬══════╬═══════╬════════╬═══════╬════════╬═════════╣\n");
    
//     float total_tat = 0, total_wt = 0, total_rt = 0;
    
//     for (int i = 0; i < process_count; i++) {
//         printf("║  %2d   ║ %-4s ║  %2d   ║  %2d  ║   %2d  ║   %2d   ║  %2d   ║   %2d   ║   %2d    ║\n",
//                processes[i].pid,
//                processes[i].name,
//                processes[i].arrival_time,
//                processes[i].burst_time,
//                processes[i].priority,
//                processes[i].completion_time,
//                processes[i].turnaround_time,
//                processes[i].waiting_time,
//                processes[i].response_time);
        
//         total_tat += processes[i].turnaround_time;
//         total_wt += processes[i].waiting_time;
//         total_rt += processes[i].response_time;
//     }
    
//     printf("╚═══════╩══════╩═══════╩══════╩═══════╩════════╩═══════╩════════╩═════════╝\n\n");
    
//     // Calculate metrics
//     float avg_tat = total_tat / process_count;
//     float avg_wt = total_wt / process_count;
//     float avg_rt = total_rt / process_count;
    
//     int total_time = gantt[gantt_count - 1].end_time;
//     int total_burst = 0;
//     for (int i = 0; i < process_count; i++) {
//         total_burst += processes[i].burst_time;
//     }
//     float cpu_utilization = (float)total_burst / total_time * 100;
//     float throughput = (float)process_count / total_time;
    
//     printf("📊 Performance Metrics:\n");
//     printf("   • Average Turnaround Time : %.2f units\n", avg_tat);
//     printf("   • Average Waiting Time    : %.2f units\n", avg_wt);
//     printf("   • Average Response Time   : %.2f units\n", avg_rt);
//     printf("   • CPU Utilization         : %.2f%%\n", cpu_utilization);
//     printf("   • Throughput              : %.2f processes/unit\n", throughput);
//     printf("   • Total Execution Time    : %d units\n\n", total_time);
// }

// // Save results to file
// void save_results(const char* algorithm) {
//     FILE *fp = fopen("result.txt", "a");
//     if (fp == NULL) {
//         printf("❌ Error opening result.txt\n");
//         return;
//     }
    
//     fprintf(fp, "\n========================================\n");
//     fprintf(fp, "Algorithm: %s\n", algorithm);
//     fprintf(fp, "========================================\n\n");
    
//     fprintf(fp, "Gantt Chart:\n");
//     for (int i = 0; i < gantt_count; i++) {
//         fprintf(fp, "[%d-%d: %s] ", gantt[i].start_time, gantt[i].end_time, gantt[i].name);
//     }
//     fprintf(fp, "\n\n");
    
//     fprintf(fp, "Process Details:\n");
//     fprintf(fp, "PID\tName\tAT\tBT\tPriority\tCT\tTAT\tWT\tRT\n");
    
//     float total_tat = 0, total_wt = 0, total_rt = 0;
    
//     for (int i = 0; i < process_count; i++) {
//         fprintf(fp, "%d\t%s\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
//                 processes[i].pid,
//                 processes[i].name,
//                 processes[i].arrival_time,
//                 processes[i].burst_time,
//                 processes[i].priority,
//                 processes[i].completion_time,
//                 processes[i].turnaround_time,
//                 processes[i].waiting_time,
//                 processes[i].response_time);
        
//         total_tat += processes[i].turnaround_time;
//         total_wt += processes[i].waiting_time;
//         total_rt += processes[i].response_time;
//     }
    
//     fprintf(fp, "\nAverage Turnaround Time: %.2f\n", total_tat / process_count);
//     fprintf(fp, "Average Waiting Time: %.2f\n", total_wt / process_count);
//     fprintf(fp, "Average Response Time: %.2f\n\n", total_rt / process_count);
    
//     fclose(fp);
//     printf("✅ Results saved to result.txt\n");
// }

// // Load processes from file
// void load_from_file() {
//     FILE *fp = fopen("processes.txt", "r");
//     if (fp == NULL) {
//         printf("❌ Error: processes.txt not found!\n");
//         printf("📝 Sample format:\n");
//         printf("   5\n");
//         printf("   P1 0 5 2\n");
//         printf("   P2 1 3 1\n");
//         printf("   Format: Name ArrivalTime BurstTime Priority\n\n");
//         return;
//     }
    
//     if (fscanf(fp, "%d", &process_count) != 1 || process_count <= 0 || process_count > MAX_PROCESSES) {
//         printf("❌ Error: Invalid process count in file!\n");
//         fclose(fp);
//         process_count = 0;
//         return;
//     }
    
//     for (int i = 0; i < process_count; i++) {
//         processes[i].pid = i + 1;
//         if (fscanf(fp, "%s %d %d %d", 
//                processes[i].name,
//                &processes[i].arrival_time,
//                &processes[i].burst_time,
//                &processes[i].priority) != 4) {
//             printf("❌ Error reading process %d from file!\n", i + 1);
//             fclose(fp);
//             process_count = 0;
//             return;
//         }
//         processes[i].remaining_time = processes[i].burst_time;
//     }
    
//     fclose(fp);
//     printf("✅ Loaded %d processes from processes.txt\n\n", process_count);
// }

// // Input processes manually
// void input_manually() {
//     printf("\n🔢 Enter number of processes: ");
    
//     // Validate input
//     if (scanf("%d", &process_count) != 1 || process_count <= 0 || process_count > MAX_PROCESSES) {
//         while (getchar() != '\n');  // Clear input buffer
//         printf("\n❌ Invalid input! Please enter a number between 1 and %d.\n", MAX_PROCESSES);
//         process_count = 0;
//         return;
//     }
//     while (getchar() != '\n');  // Clear newline
    
//     for (int i = 0; i < process_count; i++) {
//         processes[i].pid = i + 1;
        
//         printf("\n📌 Process %d:\n", i + 1);
//         printf("   Name: ");
//         if (scanf("%9s", processes[i].name) != 1) {
//             while (getchar() != '\n');
//             printf("\n❌ Invalid name! Starting over.\n");
//             process_count = 0;
//             return;
//         }
        
//         printf("   Arrival Time: ");
//         if (scanf("%d", &processes[i].arrival_time) != 1 || processes[i].arrival_time < 0) {
//             while (getchar() != '\n');
//             printf("\n❌ Invalid arrival time! Starting over.\n");
//             process_count = 0;
//             return;
//         }
        
//         printf("   Burst Time: ");
//         if (scanf("%d", &processes[i].burst_time) != 1 || processes[i].burst_time <= 0) {
//             while (getchar() != '\n');
//             printf("\n❌ Invalid burst time! Starting over.\n");
//             process_count = 0;
//             return;
//         }
        
//         printf("   Priority (lower = higher priority): ");
//         if (scanf("%d", &processes[i].priority) != 1 || processes[i].priority < 0) {
//             while (getchar() != '\n');
//             printf("\n❌ Invalid priority! Starting over.\n");
//             process_count = 0;
//             return;
//         }
        
//         processes[i].remaining_time = processes[i].burst_time;
//     }
    
//     while (getchar() != '\n');  // Clear final newline
//     printf("\n✅ Successfully entered %d processes!\n\n", process_count);
// }

// utils.c - Utility functions for I/O and display
#include <stdio.h>
#include <string.h>
#include "process.h"

// Display Gantt Chart
void display_gantt_chart() {
    if (gantt_count == 0) {
        printf("\nNo Gantt chart available. Run an algorithm first.\n");
        return;
    }

    printf("\n==================== GANTT CHART ====================\n\n");

    // Print process names
    printf("  ");
    for (int i = 0; i < gantt_count; i++) {
        printf("  %s  ", gantt[i].name);
    }
    printf("\n");

    // Print top border
    printf("  ");
    for (int i = 0; i < gantt_count; i++) {
        printf("------");
    }
    printf("\n");

    // Print timeline
    printf("%2d", gantt[0].start_time);
    for (int i = 0; i < gantt_count; i++) {
        printf("    %2d", gantt[i].end_time);
    }
    printf("\n\n");
}

// Display results table
void display_results(const char* algorithm) {
    printf("\n==================== RESULTS - %s ====================\n", algorithm);
    printf("PID\tName\tAT\tBT\tPrior\tCT\tTAT\tWT\tRT\n");
    printf("-------------------------------------------------------\n");

    float total_tat = 0, total_wt = 0, total_rt = 0;

    for (int i = 0; i < process_count; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].pid,
               processes[i].name,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].priority,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time,
               processes[i].response_time);

        total_tat += processes[i].turnaround_time;
        total_wt += processes[i].waiting_time;
        total_rt += processes[i].response_time;
    }

    printf("-------------------------------------------------------\n");

    // Calculate metrics
    float avg_tat = total_tat / process_count;
    float avg_wt = total_wt / process_count;
    float avg_rt = total_rt / process_count;

    int total_time = gantt[gantt_count - 1].end_time;
    int total_burst = 0;
    for (int i = 0; i < process_count; i++) {
        total_burst += processes[i].burst_time;
    }
    float cpu_utilization = (float)total_burst / total_time * 100;
    float throughput = (float)process_count / total_time;

    printf("Performance Metrics:\n");
    printf("  Average Turnaround Time : %.2f\n", avg_tat);
    printf("  Average Waiting Time    : %.2f\n", avg_wt);
    printf("  Average Response Time   : %.2f\n", avg_rt);
    printf("  CPU Utilization         : %.2f%%\n", cpu_utilization);
    printf("  Throughput              : %.2f processes/unit\n", throughput);
    printf("  Total Execution Time    : %d units\n\n", total_time);
}

// Save results to file
void save_results(const char* algorithm) {
    FILE *fp = fopen("result.txt", "a");
    if (fp == NULL) {
        printf("Error opening result.txt\n");
        return;
    }

    fprintf(fp, "\n========================================\n");
    fprintf(fp, "Algorithm: %s\n", algorithm);
    fprintf(fp, "========================================\n\n");

    fprintf(fp, "Gantt Chart:\n");
    for (int i = 0; i < gantt_count; i++) {
        fprintf(fp, "[%d-%d: %s] ", gantt[i].start_time, gantt[i].end_time, gantt[i].name);
    }
    fprintf(fp, "\n\n");

    fprintf(fp, "Process Details:\n");
    fprintf(fp, "PID\tName\tAT\tBT\tPriority\tCT\tTAT\tWT\tRT\n");

    float total_tat = 0, total_wt = 0, total_rt = 0;

    for (int i = 0; i < process_count; i++) {
        fprintf(fp, "%d\t%s\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
                processes[i].pid,
                processes[i].name,
                processes[i].arrival_time,
                processes[i].burst_time,
                processes[i].priority,
                processes[i].completion_time,
                processes[i].turnaround_time,
                processes[i].waiting_time,
                processes[i].response_time);

        total_tat += processes[i].turnaround_time;
        total_wt += processes[i].waiting_time;
        total_rt += processes[i].response_time;
    }

    fprintf(fp, "\nAverage Turnaround Time: %.2f\n", total_tat / process_count);
    fprintf(fp, "Average Waiting Time: %.2f\n", total_wt / process_count);
    fprintf(fp, "Average Response Time: %.2f\n\n", total_rt / process_count);

    fclose(fp);
    printf("Results saved to result.txt\n");
}

// Load processes from file
void load_from_file() {
    FILE *fp = fopen("processes.txt", "r");
    if (fp == NULL) {
        printf("Error: processes.txt not found!\n");
        printf("Sample format:\n");
        printf("5\n");
        printf("P1 0 5 2\n");
        printf("P2 1 3 1\n");
        printf("Format: Name ArrivalTime BurstTime Priority\n\n");
        return;
    }

    if (fscanf(fp, "%d", &process_count) != 1 || process_count <= 0 || process_count > MAX_PROCESSES) {
        printf("Error: Invalid process count in file!\n");
        fclose(fp);
        process_count = 0;
        return;
    }

    for (int i = 0; i < process_count; i++) {
        processes[i].pid = i + 1;
        if (fscanf(fp, "%s %d %d %d",
               processes[i].name,
               &processes[i].arrival_time,
               &processes[i].burst_time,
               &processes[i].priority) != 4) {
            printf("Error reading process %d from file!\n", i + 1);
            fclose(fp);
            process_count = 0;
            return;
        }
        processes[i].remaining_time = processes[i].burst_time;
    }

    fclose(fp);
    printf("Loaded %d processes from processes.txt\n\n", process_count);
}

// Input processes manually
void input_manually() {
    printf("\nEnter number of processes: ");

    if (scanf("%d", &process_count) != 1 || process_count <= 0 || process_count > MAX_PROCESSES) {
        while (getchar() != '\n');
        printf("Invalid input! Please enter a number between 1 and %d.\n", MAX_PROCESSES);
        process_count = 0;
        return;
    }
    while (getchar() != '\n');

    for (int i = 0; i < process_count; i++) {
        processes[i].pid = i + 1;

        printf("\nProcess %d:\n", i + 1);
        printf("   Name: ");
        if (scanf("%9s", processes[i].name) != 1) {
            while (getchar() != '\n');
            printf("Invalid name! Starting over.\n");
            process_count = 0;
            return;
        }

        printf("   Arrival Time: ");
        if (scanf("%d", &processes[i].arrival_time) != 1 || processes[i].arrival_time < 0) {
            while (getchar() != '\n');
            printf("Invalid arrival time! Starting over.\n");
            process_count = 0;
            return;
        }

        printf("   Burst Time: ");
        if (scanf("%d", &processes[i].burst_time) != 1 || processes[i].burst_time <= 0) {
            while (getchar() != '\n');
            printf("Invalid burst time! Starting over.\n");
            process_count = 0;
            return;
        }

        printf("   Priority (lower = higher priority): ");
        if (scanf("%d", &processes[i].priority) != 1 || processes[i].priority < 0) {
            while (getchar() != '\n');
            printf("Invalid priority! Starting over.\n");
            process_count = 0;
            return;
        }

        processes[i].remaining_time = processes[i].burst_time;
    }

    while (getchar() != '\n');
    printf("\nSuccessfully entered %d processes!\n\n", process_count);
}
