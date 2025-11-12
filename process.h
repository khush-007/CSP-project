// process.h - Process structure and constants
#ifndef PROCESS_H
#define PROCESS_H

#define MAX_PROCESSES 50
#define MAX_NAME 10

// Process structure
typedef struct {
    int pid;                // Process ID
    char name[MAX_NAME];    // Process name
    int arrival_time;       // Arrival time
    int burst_time;         // CPU burst time
    int remaining_time;     // Remaining burst time (for preemptive)
    int priority;           // Priority (lower number = higher priority)
    int completion_time;    // Completion time
    int turnaround_time;    // Turnaround time
    int waiting_time;       // Waiting time
    int response_time;      // Response time
    int start_time;         // First time process gets CPU
    int is_completed;       // Completion flag
} Process;

// Gantt chart entry
typedef struct {
    int pid;
    char name[MAX_NAME];
    int start_time;
    int end_time;
} GanttEntry;

// Global variables
extern Process processes[MAX_PROCESSES];
extern GanttEntry gantt[MAX_PROCESSES * 10];
extern int process_count;
extern int gantt_count;

// Function prototypes
void reset_processes();
void calculate_times();
void display_gantt_chart();
void display_results(const char* algorithm);
void save_results(const char* algorithm);
void load_from_file();
void input_manually();
void fcfs();
void sjf_non_preemptive();
void sjf_preemptive();
void priority_non_preemptive();
void priority_preemptive();
void round_robin(int quantum);

#endif