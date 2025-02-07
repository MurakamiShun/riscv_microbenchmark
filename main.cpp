#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <fstream>

#include "micro_bench.hpp"

inline uint64_t rdtime(){
        uint64_t cycle;
        asm volatile("rdtime %0" : "=r"(cycle) : : );
        return cycle;
}


#define op2_microbench(reg, op, cycle_per_rdtime)  {\
    double latency = op2_latency_asm(reg, op, cycle_per_rdtime); /*warmup*/ \
    latency        = op2_latency_asm(reg, op, cycle_per_rdtime * 100) / 100; \
    double throughput = op2_throughput_asm(reg, op, cycle_per_rdtime); /*warmup*/ \
    throughput        = op2_throughput_asm(reg, op, cycle_per_rdtime * 100) / 100; \
    std::cout << std::setw(10) << #op << " : " << std::fixed << std::setprecision(3) << latency << "   "  << std::fixed << std::setprecision(3) << throughput << std::endl; \
}

#define op2_v_microbench(reg, op, cycle_per_rdtime)  {\
    double latency = op2_v_latency_asm(reg, op, cycle_per_rdtime); /*warmup*/ \
    latency        = op2_v_latency_asm(reg, op, cycle_per_rdtime * 100) / 100; \
    double throughput = op2_v_throughput_asm(reg, op, cycle_per_rdtime); /*warmup*/ \
    throughput        = op2_v_throughput_asm(reg, op, cycle_per_rdtime * 100) / 100; \
    std::cout << std::setw(10) << #op << " : " << std::fixed << std::setprecision(3) << latency << "   "  << std::fixed << std::setprecision(3) << throughput << std::endl; \
}

#define op3_microbench(reg, op, cycle_per_rdtime)  {\
    double latency = op3_latency_asm(reg, op, cycle_per_rdtime); /*warmup*/ \
    latency        = op3_latency_asm(reg, op, cycle_per_rdtime * 100) / 100; \
    double throughput = op3_throughput_asm(reg, op, cycle_per_rdtime); /*warmup*/ \
    throughput        = op3_throughput_asm(reg, op, cycle_per_rdtime * 100) / 100; \
    std::cout << std::setw(10) << #op << " : " << std::fixed << std::setprecision(3) << latency << "   "  << std::fixed << std::setprecision(3) << throughput << std::endl; \
}

// can not benchmark floating point load latency
#define load_microbench(op, cycle_per_rdtime)  {\
    double latency = ld_latency_asm(op, cycle_per_rdtime); /*warmup*/ \
    latency        = ld_latency_asm(op, cycle_per_rdtime * 100) / 100; \
    double throughput = ld_throughput_asm(x, op, cycle_per_rdtime); /*warmup*/ \
    throughput        = ld_throughput_asm(x, op, cycle_per_rdtime * 100) / 100; \
    std::cout << std::setw(10) << #op << " : " << std::fixed << std::setprecision(3) << latency << "   "  << std::fixed << std::setprecision(3) << throughput << std::endl; \
}

#define load_throughput_microbench(reg, op, cycle_per_rdtime)  {\
    double throughput = ld_throughput_asm(reg, op, cycle_per_rdtime); /*warmup*/ \
    throughput        = ld_throughput_asm(reg, op, cycle_per_rdtime * 100) / 100; \
    std::cout << std::setw(10) << #op << " : " << std::fixed << std::setprecision(3) << "  NaN" << "   "  << std::fixed << std::setprecision(3) << throughput << std::endl; \
}

#define op2_op2_issue_microbench(reg1, op1, reg2, op2, cycle_per_rdtime)  {\
    double throughput = op2_op2_issue_check_asm(reg1, op1, reg2, op2, cycle_per_rdtime); /*warmup*/ \
    throughput        = op2_op2_issue_check_asm(reg1, op1, reg2, op2, cycle_per_rdtime * 100) / 100; \
    std::cout << std::setw(8) << #op1 << ", " << std::setw(8) << #op2 << " : " << std::fixed << std::setprecision(3) << throughput << std::endl; \
}

#define op2_op3_issue_microbench(reg1, op1, reg2, op2, cycle_per_rdtime)  {\
    double throughput = op2_op3_issue_check_asm(reg1, op1, reg2, op2, cycle_per_rdtime); /*warmup*/ \
    throughput        = op2_op3_issue_check_asm(reg1, op1, reg2, op2, cycle_per_rdtime * 100) / 100; \
    std::cout << std::setw(8) << #op1 << ", " << std::setw(8) << #op2 << " : " << std::fixed << std::setprecision(3) << throughput << std::endl; \
}

#define op2_ld_issue_microbench(reg1, op1, reg2, op2, cycle_per_rdtime)  {\
    double throughput = op2_ld_issue_check_asm(reg1, op1, reg2, op2, cycle_per_rdtime); /*warmup*/ \
    throughput        = op2_ld_issue_check_asm(reg1, op1, reg2, op2, cycle_per_rdtime * 100) / 100; \
    std::cout << std::setw(8) << #op1 << ", " << std::setw(8) << #op2 << " : " << std::fixed << std::setprecision(3) << throughput << std::endl; \
}

#define op3_ld_issue_microbench(reg1, op1, reg2, op2, cycle_per_rdtime)  {\
    double throughput = op3_ld_issue_check_asm(reg1, op1, reg2, op2, cycle_per_rdtime); /*warmup*/ \
    throughput        = op3_ld_issue_check_asm(reg1, op1, reg2, op2, cycle_per_rdtime * 100) / 100; \
    std::cout << std::setw(8) << #op1 << ", " << std::setw(8) << #op2 << " : " << std::fixed << std::setprecision(3) << throughput << std::endl; \
}

#define vsetvl_latency_microbench(cycle_per_rdtime)  {\
    double latency = vsetvl_latency_asm(cycle_per_rdtime); /*warmup*/ \
    latency        = vsetvl_latency_asm(cycle_per_rdtime * 100) / 100; \
    std::cout << std::setw(10) << "vsetivli" << " : " << std::fixed << std::setprecision(3) << latency << std::endl; \
}


void cache_latency_microbench(uint64_t size, uint64_t cycle_per_rdtime){
    double latency = 0;
    for(int r = 0; r < 100; ++r){
        latency += cache_latency(size, cycle_per_rdtime);
    }
    std::cout << std::dec << std::setw(8) << std::fixed << std::setprecision(2) << (size / 1024.0) << "KiB : " << std::fixed << std::setprecision(3) << latency/100.0 << std::endl;
}


void tlb_microbench(uint64_t tlbs, uint64_t cycle_per_rdtime){
    double latency = tlb_latency(tlbs, cycle_per_rdtime);
    std::cout << std::dec << std::setw(8) << tlbs << " pages : " << std::fixed << std::setprecision(3) << latency << std::endl;
}

void cache_way_microbench(uint64_t ways, uint64_t cycle_per_rdtime){
    double latency = cache_way_latency(ways, cycle_per_rdtime);
    std::cout << std::dec << std::setw(8) << ways << " Ways : " << std::fixed << std::setprecision(3) << latency << std::endl;
}

void memory_throughput_microbench(uint64_t size, uint64_t cycle_per_rdtime, uint64_t cpu_Hz){
    double bytes_per_sec = memory_throughput(size, cycle_per_rdtime, cpu_Hz);
    std::cout << std::dec << std::setw(8) << size/1024 << " KiB : " << std::fixed << std::setprecision(1) << bytes_per_sec/1024/1024 << " MiB/s" << std::endl;
}


double get_cycle_per_rdtime(uint64_t cpu_Hz){
    using namespace std::chrono;
    std::array<double, 4> timer_per_100ms;
    for(int i = 0; i < 4; ++i){
        uint64_t diff_total = 0;
        for(int r = 0; r < 10; ++r){
            const auto rdtime_start = rdtime();
            std::this_thread::sleep_for(milliseconds(i*100));
            const auto rdtime_end = rdtime();
            diff_total += rdtime_end - rdtime_start;
        }
        timer_per_100ms[i] = diff_total/10.0; 
    }
    uint64_t cycle_per_time = 0;
    for(int i = 1; i < 4; ++i){
        cycle_per_time += timer_per_100ms[i] - timer_per_100ms[i-1];
    }
    return cpu_Hz / (cycle_per_time/3.0 * 10.0);
}

uint64_t get_cpu_clock(){
    std::ifstream ifs("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq");
    if(!ifs){
        std::cout << "Can not get cpu frequency!!" << std::endl;
        exit(1);
    }
    uint64_t cpu_freq;
    ifs >> cpu_freq;
    return cpu_freq;
}

int main(){

    op2_latency_asm(x, mul, 1000); /*warmup*/

    const uint64_t cpu_hz = get_cpu_clock() * 1000;
    std::cout << "CPU frequency : " << cpu_hz << " Hz" << std::endl;
    
    const double cycle_per_rdtime = get_cycle_per_rdtime(cpu_hz);
    std::cout << "cycle per RDTIME : " << cycle_per_rdtime << std::endl;

    std::cout << "op     latency    CPI" << std::endl;
    op2_microbench(x, xor, cycle_per_rdtime);
    op2_microbench(x, add, cycle_per_rdtime);
    op2_microbench(x, sll, cycle_per_rdtime);
    op2_microbench(x, slt, cycle_per_rdtime);

    load_microbench(ld, cycle_per_rdtime);
    load_throughput_microbench(x, sd, cycle_per_rdtime);
    load_throughput_microbench(x, sw, cycle_per_rdtime);
    
    // std::cout << "---- RV64Zbs" << std::endl;
    // op2_microbench(x, bset, cycle_per_rdtime);
    
    std::cout << "---- RV64M" << std::endl;
    op2_microbench(x, mul, cycle_per_rdtime);
    op2_microbench(x, mulh, cycle_per_rdtime);
    op2_microbench(x, mulhsu, cycle_per_rdtime);
    op2_microbench(x, mulhu, cycle_per_rdtime);
    op2_microbench(x, mulw, cycle_per_rdtime);
    // floating point
    std::cout << "---- RV64F" << std::endl;
    op2_microbench(f, fmax.s, cycle_per_rdtime);
    op2_microbench(f, fadd.s, cycle_per_rdtime);
    op2_microbench(f, fmul.s, cycle_per_rdtime);
    op3_microbench(f, fmadd.s, cycle_per_rdtime);
    load_throughput_microbench(f, flw, cycle_per_rdtime);
    load_throughput_microbench(f, fsw, cycle_per_rdtime);
    std::cout << "---- RV64D" << std::endl;
    op2_microbench(f, fmax.d, cycle_per_rdtime);
    op2_microbench(f, fadd.d, cycle_per_rdtime);
    op2_microbench(f, fmul.d, cycle_per_rdtime);
    op3_microbench(f, fmadd.d, cycle_per_rdtime);
    load_throughput_microbench(f, fld, cycle_per_rdtime);
    load_throughput_microbench(f, fsd, cycle_per_rdtime);
    // vector

    std::cout << "---- RV64V(e32,m1)" << std::endl;
    vsetvl_latency_microbench(cycle_per_rdtime);
    asm volatile("vsetivli   zero,8,e32,m1,ta,ma;" : : :);
    load_throughput_microbench(v, vle32.v, cycle_per_rdtime);
    asm volatile("vsetivli   zero,8,e32,m1,ta,ma;" : : :);
    op2_microbench(v, vfadd.vv, cycle_per_rdtime);
    asm volatile("vsetivli   zero,8,e32,m1,ta,ma;" : : :);
    op2_microbench(v, vfmul.vv, cycle_per_rdtime);
    asm volatile("vsetivli   zero,8,e32,m1,ta,ma;" : : :);
    op2_microbench(v, vfmacc.vv, cycle_per_rdtime);
    
    std::cout << "---- RV64V(e64,m1)" << std::endl;
    asm volatile("vsetivli   zero,4,e64,m1,ta,ma;" : : :);
    load_throughput_microbench(v, vle64.v, cycle_per_rdtime);
    asm volatile("vsetivli   zero,4,e64,m1,ta,ma;" : : :);
    op2_microbench(v, vfadd.vv, cycle_per_rdtime);
    asm volatile("vsetivli   zero,4,e64,m1,ta,ma;" : : :);
    op2_microbench(v, vfmul.vv, cycle_per_rdtime);
    asm volatile("vsetivli   zero,4,e64,m1,ta,ma;" : : :);
    op2_microbench(v, vfmacc.vv, cycle_per_rdtime);
    
    std::cout << "---- RV64V(e64,m2)" << std::endl;
    asm volatile("vsetivli   zero,8,e64,m2,ta,ma;" : : :);
    op2_v_microbench(v, vfadd.vv, cycle_per_rdtime);
    asm volatile("vsetivli   zero,8,e64,m2,ta,ma;" : : :);
    op2_v_microbench(v, vfmul.vv, cycle_per_rdtime);
    asm volatile("vsetivli   zero,8,e64,m2,ta,ma;" : : :);
    op2_v_microbench(v, vfmacc.vv, cycle_per_rdtime);
    
    std::cout << "---- RV64V(e64,m4)" << std::endl;
    asm volatile("vsetivli   zero,16,e64,m4,ta,ma;" : : :);
    op2_v_microbench(v, vfadd.vv, cycle_per_rdtime);
    asm volatile("vsetivli   zero,16,e64,m4,ta,ma;" : : :);
    op2_v_microbench(v, vfmul.vv, cycle_per_rdtime);
    asm volatile("vsetivli   zero,16,e64,m4,ta,ma;" : : :);
    op2_v_microbench(v, vfmacc.vv, cycle_per_rdtime);

    std::cout << "---- RV64V(e64,m8)" << std::endl;
    asm volatile(
        "addi       t0,zero,32;"
        "vsetvli    zero,t0,e64,m8,ta,ma;"
         : : : "t0"
    );
    op2_v_microbench(v, vfadd.vv, cycle_per_rdtime);
    asm volatile(
        "addi       t0,zero,32;"
        "vsetvli    zero,t0,e64,m8,ta,ma;"
         : : : "t0"
    );
    op2_v_microbench(v, vfmul.vv, cycle_per_rdtime);
    asm volatile(
        "addi       t0,zero,32;"
        "vsetvli    zero,t0,e64,m8,ta,ma;"
         : : : "t0"
    );
    op2_v_microbench(v, vfmacc.vv, cycle_per_rdtime);

    
    std::cout << "---- issue check" << std::endl;
    std::cout << "     op1,      op2 : CPI" << std::endl;
    op2_op2_issue_microbench(x, add, x, xor, cycle_per_rdtime);
    op2_op2_issue_microbench(x, mul, f, fadd.d, cycle_per_rdtime);
    op2_op3_issue_microbench(x, add, f, fmadd.d, cycle_per_rdtime);
    op2_op2_issue_microbench(f, fmul.d, f, fadd.d, cycle_per_rdtime);
    op2_op3_issue_microbench(f, fmul.d, f, fmadd.d, cycle_per_rdtime);
    op3_ld_issue_microbench(f, fmadd.d, f, fld, cycle_per_rdtime);
    std::cout << "---- RV64V(e64,m1)" << std::endl;
    asm volatile("vsetivli   zero,4,e64,m1,ta,ma;" : : :);
    op2_op2_issue_microbench(v, vfadd.vv, v, vfmul.vv, cycle_per_rdtime);
    asm volatile("vsetivli   zero,4,e64,m1,ta,ma;" : : :);
    op2_op2_issue_microbench(v, vfmul.vv, v, vfmul.vv, cycle_per_rdtime);
    asm volatile("vsetivli   zero,4,e64,m1,ta,ma;" : : :);
    op2_op2_issue_microbench(v, vfmacc.vv, v, vfmul.vv, cycle_per_rdtime);
    asm volatile("vsetivli   zero,4,e64,m1,ta,ma;" : : :);
    op2_ld_issue_microbench(v, vfadd.vv, f, fld, cycle_per_rdtime);
    asm volatile("vsetivli   zero,4,e64,m1,ta,ma;" : : :);
    op2_ld_issue_microbench(v, vfmacc.vv, f, fld, cycle_per_rdtime);
    asm volatile("vsetivli   zero,4,e64,m1,ta,ma;" : : :);
    op2_ld_issue_microbench(v, vfmacc.vv, v, vle64.v, cycle_per_rdtime);

    std::cout << "---- RV64V(e64,m2)" << std::endl;
    asm volatile("vsetivli   zero,8,e64,m2,ta,ma;" : : :);
    op2_ld_issue_microbench(v, vfadd.vv, f, fld, cycle_per_rdtime);
    asm volatile("vsetivli   zero,8,e64,m2,ta,ma;" : : :);
    op2_ld_issue_microbench(v, vfmacc.vv, f, fld, cycle_per_rdtime);
    

    std::cout << "cache latency" << std::endl;
    for(double size = 2048; size < 8*1024*1024; size*=2){
        cache_latency_microbench((uint64_t)size, cycle_per_rdtime);
    }

    std::cout << "TLB latency" << std::endl;
    for(double tlbs = 4; tlbs < 2048; tlbs*=1.41421357){
        tlb_microbench((uint64_t)tlbs, cycle_per_rdtime);
    }

    std::cout << "Cache ways" << std::endl;
    for(uint64_t ways = 2; ways <= 40; ways+=2){
        cache_way_microbench(ways, cycle_per_rdtime);
    }

    std::cout << "memory throughput" << std::endl;
    for(uint64_t size = 1024; size <= 64*1024*1024; size*=2){
        memory_throughput_microbench(size, cycle_per_rdtime, cpu_hz);
    }

    std::cout << "core-to-core latency" << std::endl;
    const auto core_num = std::thread::hardware_concurrency();
    std::cout << "    ";
    for(int i = 0; i < core_num; ++i){
        std::cout << std::setw(6) << i;
    }
    std::cout << std::endl;
    for(int i = 0; i < core_num; ++i){
        std::cout << std::setw(2) << i << " : ";
        for(int j = 0; j < core_num; ++j){
            if(i == j) {
                std::cout << " ---  ";
                continue;
            }
            std::cout << std::fixed << std::setprecision(1) << core_latency(i, j, cycle_per_rdtime) << " ";
        }
        std::cout << std::endl;
    }
}

