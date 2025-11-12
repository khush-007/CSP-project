# 🖥️ CPU Scheduling Visualizer
## Process Management Simulator

A comprehensive C language project that simulates various CPU scheduling algorithms used in operating systems.

---

## 📋 Features

### ✅ Implemented Algorithms
1. **FCFS** (First Come First Serve)
2. **SJF Non-Preemptive** (Shortest Job First)
3. **SJF Preemptive** (Shortest Remaining Time First - SRTF)
4. **Priority Non-Preemptive**
5. **Priority Preemptive**
6. **Round Robin** (with customizable time quantum)

### 🎯 Key Capabilities
- ✨ Beautiful text-based Gantt chart visualization
- 📊 Detailed performance metrics (TAT, WT, RT)
- 💾 File I/O support (load from/save to files)
- 🆚 Algorithm comparison mode
- 📈 CPU utilization and throughput calculations
- 🎨 Clean, menu-driven interface with emojis
- 🔄 Modular, maintainable code structure

---

## 📁 Project Structure

```
cpu-scheduler/
├── main.c           # Main driver program with menu
├── algorithms.c     # All scheduling algorithm implementations
├── utils.c          # I/O and display utilities
├── process.h        # Process structure and function declarations
├── Makefile         # Build configuration
├── processes.txt    # Input file (sample)
└── result.txt       # Output file (generated)
```

---

## 🚀 How to Compile and Run

### Method 1: Using Makefile (Recommended)
```bash
# Compile the project
make

# Run the program
./scheduler

# Or compile and run together
make run

# Create sample input file
make sample

# Clean build files
make clean
```

### Method 2: Manual Compilation
```bash
gcc -Wall -std=c99 -o scheduler main.c algorithms.c utils.c
./scheduler
```

---

## 📝 Input File Format

### processes.txt
```
5
P1 0 5 2
P2 1 3 1
P3 2 8 3
P4 3 6 2
P5 4 4 1
```

**Format:** `ProcessName ArrivalTime BurstTime Priority`
- First line: Number of processes
- Following lines: Process details
- Priority: Lower number = Higher priority

---

## 🎮 Usage Example

### Main Menu
```
╔═══════════════════════════════════════════════════════════╗
║         CPU SCHEDULING VISUALIZER v1.0                    ║
║         Process Management Simulator                      ║
╚═══════════════════════════════════════════════════════════╝

  1. 📂 Load Processes from File (processes.txt)
  2. ⌨️  Enter Processes Manually
  3. 🔄 Run FCFS (First Come First Serve)
  4. ⚡ Run SJF Non-Preemptive
  5. ⚡ Run SJF Preemptive (SRTF)
  6. 🎯 Run Priority Non-Preemptive
  7. 🎯 Run Priority Preemptive
  8. 🔁 Run Round Robin
  9. 📊 View Current Gantt Chart
 10. 💾 Save Last Results to File
 11. 🆚 Compare All Algorithms
 12. ❌ Exit
```

### Sample Output - Gantt Chart
```
╔════════════════════════════════════════════════════════════╗
║                      GANTT CHART                           ║
╚════════════════════════════════════════════════════════════╝

    P1    P2    P4    P5    P3  
  -------------------------------
 0     5     8    14    18    26
```

### Sample Output - Results Table
```
╔═══════╦══════╦═══════╦══════╦═══════╦════════╦═══════╦════════╦═════════╣
║  PID  ║ Name ║ AT    ║ BT   ║ Prior ║ CT     ║ TAT   ║ WT     ║ RT      ║
╠═══════╬══════╬═══════╬══════╬═══════╬════════╬═══════╬════════╬═════════╣
║   1   ║ P1   ║   0   ║   5  ║    2  ║    5   ║   5   ║    0   ║    0    ║
║   2   ║ P2   ║   1   ║   3  ║    1  ║    8   ║   7   ║    4   ║    4    ║
║   3   ║ P3   ║   2   ║   8  ║    3  ║   26   ║  24   ║   16   ║   16    ║
║   4   ║ P4   ║   3   ║   6  ║    2  ║   14   ║  11   ║    5   ║    5    ║
║   5   ║ P5   ║   4   ║   4  ║    1  ║   18   ║  14   ║   10   ║   10    ║
╚═══════╩══════╩═══════╩══════╩═══════╩════════╩═══════╩════════╩═════════╝

📊 Performance Metrics:
   • Average Turnaround Time : 12.20 units
   • Average Waiting Time    : 7.00 units
   • Average Response Time   : 7.00 units
   • CPU Utilization         : 100.00%
   • Throughput              : 0.19 processes/unit
   • Total Execution Time    : 26 units
```

### Algorithm Comparison Output
```
╔════════════════════════════════╦═══════╦═══════╦═══════╗
║ Algorithm                      ║  TAT  ║  WT   ║  RT   ║
╠════════════════════════════════╬═══════╬═══════╬═══════╣
║ FCFS                           ║ 12.20 ║  7.00 ║  7.00 ║
║ SJF (Non-Preemptive)          ║  9.60 ║  4.40 ║  4.40 ║
║ SJF (Preemptive)              ║  8.80 ║  3.60 ║  1.80 ║
║ Priority (Non-Preemptive)     ║ 11.40 ║  6.20 ║  6.20 ║
║ Priority (Preemptive)         ║  9.20 ║  4.00 ║  1.60 ║
║ Round Robin (Q=2)             ║ 14.80 ║  9.60 ║  2.00 ║
╚════════════════════════════════╩═══════╩═══════╩═══════╝

🏆 Best Algorithm (Lowest Avg. Waiting Time): SJF (Preemptive) (3.60)
```

---

## 🧮 Calculated Metrics

### Process-Level Metrics
- **Completion Time (CT)**: Time when process finishes execution
- **Turnaround Time (TAT)**: CT - Arrival Time
- **Waiting Time (WT)**: TAT - Burst Time
- **Response Time (RT)**: First CPU allocation - Arrival Time

### System-Level Metrics
- **Average Turnaround Time**: Mean TAT of all processes
- **Average Waiting Time**: Mean WT of all processes
- **CPU Utilization**: (Total Burst Time / Total Time) × 100
- **Throughput**: Number of processes / Total Time

---

## 🎓 Educational Value

This project demonstrates:
1. **Data Structures**: Structs, arrays, queues
2. **Algorithms**: Sorting, scheduling, greedy approaches
3. **File I/O**: Reading from and writing to files
4. **Modular Programming**: Separation of concerns, header files
5. **OS Concepts**: Process management, scheduling policies
6. **C Programming**: Pointers, functions, memory management

---

## 🔧 Customization

### Add More Processes
Edit `processes.txt` or use manual input (Option 2)

### Change Time Quantum for Round Robin
Enter desired value when prompted (Option 8)

### Modify Display Format
Edit `utils.c` - Functions: `display_gantt_chart()`, `display_results()`

### Add New Algorithm
1. Declare function in `process.h`
2. Implement in `algorithms.c`
3. Add menu option in `main.c`

---

## 📊 Test Cases

### Test Case 1: Standard Processes
```
5 processes with varied arrival times and burst times
Expected: Proper scheduling and no starvation
```

### Test Case 2: Same Arrival Time
```
All processes arrive at t=0
Tests: Algorithm behavior without arrival time factor
```

### Test Case 3: Priority Inversion
```
High-priority process arrives late
Tests: Preemptive vs non-preemptive behavior
```

---

## 🐛 Known Limitations

1. Maximum 50 processes (can be increased in `process.h`)
2. Text-based output only (no GUI)
3. Single CPU simulation only
4. No I/O burst simulation
5. Assumes integer time units

---

## 🚀 Possible Enhancements

- [ ] Add multilevel queue scheduling
- [ ] Implement aging to prevent starvation
- [ ] Add process states (Ready, Running, Waiting)
- [ ] Support for multiprocessor scheduling
- [ ] GUI using graphics libraries
- [ ] Add pthread support for real-time simulation
- [ ] Context switching overhead simulation
- [ ] Dynamic priority adjustment

---

## 👥 Contributors

Developed as an Operating Systems course project

---

## 📄 License

Free to use for educational purposes

---

## 📞 Support

For issues or questions:
1. Check the comments in source code
2. Review the sample input/output files
3. Verify compilation with correct flags

---

## 🎉 Acknowledgments

Thanks to operating systems concepts from:
- "Operating System Concepts" by Silberschatz, Galvin, and Gagne
- Various OS course materials and tutorials

---

**Happy Scheduling! 🎯**
