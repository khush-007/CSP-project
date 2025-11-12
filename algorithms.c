// algorithms.c - CPU scheduling algorithm implementations
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "process.h"

Process processes[MAX_PROCESSES];
GanttEntry gantt[MAX_PROCESSES * 10];
int process_count = 0;
int gantt_count = 0;

// Reset process state for new algorithm execution
void reset_processes() {
    gantt_count = 0;
    for (int i = 0; i < process_count; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
        processes[i].response_time = -1;
        processes[i].start_time = -1;
        processes[i].is_completed = 0;
    }
}

// Calculate waiting and turnaround times
void calculate_times() {
    for (int i = 0; i < process_count; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        processes[i].response_time = processes[i].start_time - processes[i].arrival_time;
    }
}

// FCFS Scheduling
void fcfs() {
    reset_processes();
    int current_time = 0;
    
    // Sort by arrival time
    for (int i = 0; i < process_count - 1; i++) {
        for (int j = 0; j < process_count - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    
    for (int i = 0; i < process_count; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        
        processes[i].start_time = current_time;
        gantt[gantt_count].pid = processes[i].pid;
        strcpy(gantt[gantt_count].name, processes[i].name);
        gantt[gantt_count].start_time = current_time;
        current_time += processes[i].burst_time;
        gantt[gantt_count].end_time = current_time;
        gantt_count++;
        
        processes[i].completion_time = current_time;
    }
    
    calculate_times();
}

// SJF Non-Preemptive
void sjf_non_preemptive() {
    reset_processes();
    int current_time = 0;
    int completed = 0;
    
    while (completed < process_count) {
        int shortest = -1;
        int min_burst = INT_MAX;
        
        for (int i = 0; i < process_count; i++) {
            if (processes[i].arrival_time <= current_time && 
                !processes[i].is_completed && 
                processes[i].burst_time < min_burst) {
                min_burst = processes[i].burst_time;
                shortest = i;
            }
        }
        
        if (shortest == -1) {
            current_time++;
            continue;
        }
        
        processes[shortest].start_time = current_time;
        gantt[gantt_count].pid = processes[shortest].pid;
        strcpy(gantt[gantt_count].name, processes[shortest].name);
        gantt[gantt_count].start_time = current_time;
        current_time += processes[shortest].burst_time;
        gantt[gantt_count].end_time = current_time;
        gantt_count++;
        
        processes[shortest].completion_time = current_time;
        processes[shortest].is_completed = 1;
        completed++;
    }
    
    calculate_times();
}

// SJF Preemptive (SRTF)
void sjf_preemptive() {
    reset_processes();
    int current_time = 0;
    int completed = 0;
    int prev_process = -1;
    
    while (completed < process_count) {
        int shortest = -1;
        int min_remaining = INT_MAX;
        
        for (int i = 0; i < process_count; i++) {
            if (processes[i].arrival_time <= current_time && 
                !processes[i].is_completed && 
                processes[i].remaining_time < min_remaining) {
                min_remaining = processes[i].remaining_time;
                shortest = i;
            }
        }
        
        if (shortest == -1) {
            current_time++;
            continue;
        }
        
        if (processes[shortest].start_time == -1) {
            processes[shortest].start_time = current_time;
        }
        
        if (prev_process != shortest) {
            if (gantt_count > 0 && gantt[gantt_count - 1].pid == processes[shortest].pid) {
                gantt[gantt_count - 1].end_time = current_time + 1;
            } else {
                gantt[gantt_count].pid = processes[shortest].pid;
                strcpy(gantt[gantt_count].name, processes[shortest].name);
                gantt[gantt_count].start_time = current_time;
                gantt[gantt_count].end_time = current_time + 1;
                gantt_count++;
            }
            prev_process = shortest;
        } else {
            gantt[gantt_count - 1].end_time = current_time + 1;
        }
        
        processes[shortest].remaining_time--;
        current_time++;
        
        if (processes[shortest].remaining_time == 0) {
            processes[shortest].completion_time = current_time;
            processes[shortest].is_completed = 1;
            completed++;
        }
    }
    
    calculate_times();
}

// Priority Non-Preemptive
void priority_non_preemptive() {
    reset_processes();
    int current_time = 0;
    int completed = 0;
    
    while (completed < process_count) {
        int highest = -1;
        int min_priority = INT_MAX;
        
        for (int i = 0; i < process_count; i++) {
            if (processes[i].arrival_time <= current_time && 
                !processes[i].is_completed && 
                processes[i].priority < min_priority) {
                min_priority = processes[i].priority;
                highest = i;
            }
        }
        
        if (highest == -1) {
            current_time++;
            continue;
        }
        
        processes[highest].start_time = current_time;
        gantt[gantt_count].pid = processes[highest].pid;
        strcpy(gantt[gantt_count].name, processes[highest].name);
        gantt[gantt_count].start_time = current_time;
        current_time += processes[highest].burst_time;
        gantt[gantt_count].end_time = current_time;
        gantt_count++;
        
        processes[highest].completion_time = current_time;
        processes[highest].is_completed = 1;
        completed++;
    }
    
    calculate_times();
}

// Priority Preemptive
void priority_preemptive() {
    reset_processes();
    int current_time = 0;
    int completed = 0;
    int prev_process = -1;
    
    while (completed < process_count) {
        int highest = -1;
        int min_priority = INT_MAX;
        
        for (int i = 0; i < process_count; i++) {
            if (processes[i].arrival_time <= current_time && 
                !processes[i].is_completed && 
                processes[i].priority < min_priority) {
                min_priority = processes[i].priority;
                highest = i;
            }
        }
        
        if (highest == -1) {
            current_time++;
            continue;
        }
        
        if (processes[highest].start_time == -1) {
            processes[highest].start_time = current_time;
        }
        
        if (prev_process != highest) {
            if (gantt_count > 0 && gantt[gantt_count - 1].pid == processes[highest].pid) {
                gantt[gantt_count - 1].end_time = current_time + 1;
            } else {
                gantt[gantt_count].pid = processes[highest].pid;
                strcpy(gantt[gantt_count].name, processes[highest].name);
                gantt[gantt_count].start_time = current_time;
                gantt[gantt_count].end_time = current_time + 1;
                gantt_count++;
            }
            prev_process = highest;
        } else {
            gantt[gantt_count - 1].end_time = current_time + 1;
        }
        
        processes[highest].remaining_time--;
        current_time++;
        
        if (processes[highest].remaining_time == 0) {
            processes[highest].completion_time = current_time;
            processes[highest].is_completed = 1;
            completed++;
        }
    }
    
    calculate_times();
}

// Round Robin
void round_robin(int quantum) {
    reset_processes();
    int current_time = 0;
    int completed = 0;
    int queue[MAX_PROCESSES];
    int front = 0, rear = 0;
    int in_queue[MAX_PROCESSES] = {0};
    
    // Add first arrived process
    for (int i = 0; i < process_count; i++) {
        if (processes[i].arrival_time == 0) {
            queue[rear++] = i;
            in_queue[i] = 1;
        }
    }
    
    while (completed < process_count) {
        if (front == rear) {
            current_time++;
            for (int i = 0; i < process_count; i++) {
                if (!processes[i].is_completed && !in_queue[i] && 
                    processes[i].arrival_time <= current_time) {
                    queue[rear++] = i;
                    in_queue[i] = 1;
                }
            }
            continue;
        }
        
        int idx = queue[front++];
        
        if (processes[idx].start_time == -1) {
            processes[idx].start_time = current_time;
        }
        
        int exec_time = (processes[idx].remaining_time > quantum) ? 
                        quantum : processes[idx].remaining_time;
        
        gantt[gantt_count].pid = processes[idx].pid;
        strcpy(gantt[gantt_count].name, processes[idx].name);
        gantt[gantt_count].start_time = current_time;
        current_time += exec_time;
        gantt[gantt_count].end_time = current_time;
        gantt_count++;
        
        processes[idx].remaining_time -= exec_time;
        
        // Add newly arrived processes
        for (int i = 0; i < process_count; i++) {
            if (!processes[i].is_completed && !in_queue[i] && 
                processes[i].arrival_time <= current_time && i != idx) {
                queue[rear++] = i;
                in_queue[i] = 1;
            }
        }
        
        if (processes[idx].remaining_time == 0) {
            processes[idx].completion_time = current_time;
            processes[idx].is_completed = 1;
            in_queue[idx] = 0;
            completed++;
        } else {
            queue[rear++] = idx;
        }
    }
    
    calculate_times();
}