#pragma once
#include <cstdint>
#include <array>
#include <random>
#include <atomic>
#include <thread>
#include <sched.h>
#include <unistd.h>
#include <sys/syscall.h>

#define op2_latency_asm_impl16(reg, op) #op " " #reg "16, " #reg "31, " #reg "31;" \
#op " " #reg "17, " #reg "16, " #reg "16;" \
#op " " #reg "18, " #reg "17, " #reg "17;" \
#op " " #reg "19, " #reg "18, " #reg "18;" \
#op " " #reg "20, " #reg "19, " #reg "19;" \
#op " " #reg "21, " #reg "20, " #reg "20;" \
#op " " #reg "22, " #reg "21, " #reg "21;" \
#op " " #reg "23, " #reg "22, " #reg "22;" \
#op " " #reg "24, " #reg "23, " #reg "23;" \
#op " " #reg "25, " #reg "24, " #reg "24;" \
#op " " #reg "26, " #reg "25, " #reg "25;" \
#op " " #reg "27, " #reg "26, " #reg "26;" \
#op " " #reg "28, " #reg "27, " #reg "27;" \
#op " " #reg "29, " #reg "28, " #reg "28;" \
#op " " #reg "30, " #reg "29, " #reg "29;" \
#op " " #reg "31, " #reg "30, " #reg "30;"

#define op2_throughput_asm_impl16(reg, op) #op " " #reg "16, " #reg "16, " #reg "16;" \
#op " " #reg "17, " #reg "17, " #reg "17;" \
#op " " #reg "18, " #reg "18, " #reg "18;" \
#op " " #reg "19, " #reg "19, " #reg "19;" \
#op " " #reg "20, " #reg "20, " #reg "20;" \
#op " " #reg "21, " #reg "21, " #reg "21;" \
#op " " #reg "22, " #reg "22, " #reg "22;" \
#op " " #reg "23, " #reg "23, " #reg "23;" \
#op " " #reg "24, " #reg "24, " #reg "24;" \
#op " " #reg "25, " #reg "25, " #reg "25;" \
#op " " #reg "26, " #reg "26, " #reg "26;" \
#op " " #reg "27, " #reg "27, " #reg "27;" \
#op " " #reg "28, " #reg "28, " #reg "28;" \
#op " " #reg "29, " #reg "29, " #reg "29;" \
#op " " #reg "30, " #reg "30, " #reg "30;" \
#op " " #reg "31, " #reg "31, " #reg "31;"


#define op3_latency_asm_impl16(reg, op) #op " " #reg "16, " #reg "31, " #reg "31, " #reg "31;" \
#op " " #reg "17, " #reg "16, " #reg "16, " #reg "16;" \
#op " " #reg "18, " #reg "17, " #reg "17, " #reg "17;" \
#op " " #reg "19, " #reg "18, " #reg "18, " #reg "18;" \
#op " " #reg "20, " #reg "19, " #reg "19, " #reg "19;" \
#op " " #reg "21, " #reg "20, " #reg "20, " #reg "20;" \
#op " " #reg "22, " #reg "21, " #reg "21, " #reg "21;" \
#op " " #reg "23, " #reg "22, " #reg "22, " #reg "22;" \
#op " " #reg "24, " #reg "23, " #reg "23, " #reg "23;" \
#op " " #reg "25, " #reg "24, " #reg "24, " #reg "24;" \
#op " " #reg "26, " #reg "25, " #reg "25, " #reg "25;" \
#op " " #reg "27, " #reg "26, " #reg "26, " #reg "26;" \
#op " " #reg "28, " #reg "27, " #reg "27, " #reg "27;" \
#op " " #reg "29, " #reg "28, " #reg "28, " #reg "28;" \
#op " " #reg "30, " #reg "29, " #reg "29, " #reg "29;" \
#op " " #reg "31, " #reg "30, " #reg "30, " #reg "30;"

#define op3_throughput_asm_impl16(reg, op) #op " " #reg "16, " #reg "16, " #reg "16, " #reg "16;" \
#op " " #reg "17, " #reg "17, " #reg "17, " #reg "17;" \
#op " " #reg "18, " #reg "18, " #reg "18, " #reg "18;" \
#op " " #reg "19, " #reg "19, " #reg "19, " #reg "19;" \
#op " " #reg "20, " #reg "20, " #reg "20, " #reg "20;" \
#op " " #reg "21, " #reg "21, " #reg "21, " #reg "21;" \
#op " " #reg "22, " #reg "22, " #reg "22, " #reg "22;" \
#op " " #reg "23, " #reg "23, " #reg "23, " #reg "23;" \
#op " " #reg "24, " #reg "24, " #reg "24, " #reg "24;" \
#op " " #reg "25, " #reg "25, " #reg "25, " #reg "25;" \
#op " " #reg "26, " #reg "26, " #reg "26, " #reg "26;" \
#op " " #reg "27, " #reg "27, " #reg "27, " #reg "27;" \
#op " " #reg "28, " #reg "28, " #reg "28, " #reg "28;" \
#op " " #reg "29, " #reg "29, " #reg "29, " #reg "29;" \
#op " " #reg "30, " #reg "30, " #reg "30, " #reg "30;" \
#op " " #reg "31, " #reg "31, " #reg "31, " #reg "31;"


#define op2_latency_asm(reg, op, cycle_per_rdtime) [](uint64_t c_p_rdtime){\
uint64_t time = 0;\
asm volatile( \
"mv s1, %1;"\
"rdtime s0;" \
"loop%=:" \
"addi s1, s1, -1;" \
op2_latency_asm_impl16(reg, op) \
op2_latency_asm_impl16(reg, op) \
op2_latency_asm_impl16(reg, op) \
op2_latency_asm_impl16(reg, op) \
op2_latency_asm_impl16(reg, op) \
op2_latency_asm_impl16(reg, op) \
op2_latency_asm_impl16(reg, op) \
op2_latency_asm_impl16(reg, op) \
op2_latency_asm_impl16(reg, op) \
op2_latency_asm_impl16(reg, op) \
op2_latency_asm_impl16(reg, op) \
op2_latency_asm_impl16(reg, op) \
op2_latency_asm_impl16(reg, op) \
op2_latency_asm_impl16(reg, op) \
op2_latency_asm_impl16(reg, op) \
op2_latency_asm_impl16(reg, op) /* 16*16 = 256 */ \
"bne s1, zero, loop%=;" \
"rdtime s1;" \
"sub %0, s1, s0;" \
: "=r"(time) \
: "r"(c_p_rdtime) \
: "memory", \
"s0","s1", \
#reg "16",#reg "17",#reg "18",#reg "19",#reg "20",#reg "21",#reg "22",#reg "23",\
#reg "24",#reg "25",#reg "26",#reg "27",#reg "28",#reg "29",#reg "30",#reg "31");\
return time / 256.0;\
}(cycle_per_rdtime)

#define op2_throughput_asm(reg, op, cycle_per_rdtime) [](uint64_t c_p_rdtime){\
uint64_t time = 0;\
asm volatile( \
"mv s1, %1;"\
"rdtime s0;" \
"loop%=:" \
"addi s1, s1, -1;" \
op2_throughput_asm_impl16(reg, op) \
op2_throughput_asm_impl16(reg, op) \
op2_throughput_asm_impl16(reg, op) \
op2_throughput_asm_impl16(reg, op) \
op2_throughput_asm_impl16(reg, op) \
op2_throughput_asm_impl16(reg, op) \
op2_throughput_asm_impl16(reg, op) \
op2_throughput_asm_impl16(reg, op) \
op2_throughput_asm_impl16(reg, op) \
op2_throughput_asm_impl16(reg, op) \
op2_throughput_asm_impl16(reg, op) \
op2_throughput_asm_impl16(reg, op) \
op2_throughput_asm_impl16(reg, op) \
op2_throughput_asm_impl16(reg, op) \
op2_throughput_asm_impl16(reg, op) \
op2_throughput_asm_impl16(reg, op) /* 16*16 = 256 */ \
"bne s1, zero, loop%=;" \
"rdtime s1;" \
"sub %0, s1, s0;" \
: "=r"(time) \
: "r"(c_p_rdtime) \
: "memory", \
"s0","s1", \
#reg "16",#reg "17",#reg "18",#reg "19",#reg "20",#reg "21",#reg "22",#reg "23",\
#reg "24",#reg "25",#reg "26",#reg "27",#reg "28",#reg "29",#reg "30",#reg "31");\
return time / 256.0;\
}(cycle_per_rdtime)



#define op3_latency_asm(reg, op, cycle_per_rdtime) [](uint64_t c_p_rdtime){\
uint64_t time = 0;\
asm volatile( \
"mv s1, %1;"\
"rdtime s0;" \
"loop%=:" \
"addi s1, s1, -1;" \
op3_latency_asm_impl16(reg, op) \
op3_latency_asm_impl16(reg, op) \
op3_latency_asm_impl16(reg, op) \
op3_latency_asm_impl16(reg, op) \
op3_latency_asm_impl16(reg, op) \
op3_latency_asm_impl16(reg, op) \
op3_latency_asm_impl16(reg, op) \
op3_latency_asm_impl16(reg, op) \
op3_latency_asm_impl16(reg, op) \
op3_latency_asm_impl16(reg, op) \
op3_latency_asm_impl16(reg, op) \
op3_latency_asm_impl16(reg, op) \
op3_latency_asm_impl16(reg, op) \
op3_latency_asm_impl16(reg, op) \
op3_latency_asm_impl16(reg, op) \
op3_latency_asm_impl16(reg, op) /* 16*16 = 256 */ \
"bne s1, zero, loop%=;" \
"rdtime s1;" \
"sub %0, s1, s0;" \
: "=r"(time) \
: "r"(c_p_rdtime) \
: "memory", \
"s0","s1", \
#reg "16",#reg "17",#reg "18",#reg "19",#reg "20",#reg "21",#reg "22",#reg "23",\
#reg "24",#reg "25",#reg "26",#reg "27",#reg "28",#reg "29",#reg "30",#reg "31");\
return time / 256.0;\
}(cycle_per_rdtime)


#define op3_throughput_asm(reg, op, cycle_per_rdtime) [](uint64_t c_p_rdtime){\
uint64_t time = 0;\
asm volatile( \
"mv s1, %1;"\
"rdtime s0;" \
"loop%=:" \
"addi s1, s1, -1;" \
op3_throughput_asm_impl16(reg, op) \
op3_throughput_asm_impl16(reg, op) \
op3_throughput_asm_impl16(reg, op) \
op3_throughput_asm_impl16(reg, op) \
op3_throughput_asm_impl16(reg, op) \
op3_throughput_asm_impl16(reg, op) \
op3_throughput_asm_impl16(reg, op) \
op3_throughput_asm_impl16(reg, op) \
op3_throughput_asm_impl16(reg, op) \
op3_throughput_asm_impl16(reg, op) \
op3_throughput_asm_impl16(reg, op) \
op3_throughput_asm_impl16(reg, op) \
op3_throughput_asm_impl16(reg, op) \
op3_throughput_asm_impl16(reg, op) \
op3_throughput_asm_impl16(reg, op) \
op3_throughput_asm_impl16(reg, op) /* 16*16 = 256 */ \
"bne s1, zero, loop%=;" \
"rdtime s1;" \
"sub %0, s1, s0;" \
: "=r"(time) \
: "r"(c_p_rdtime) \
: "memory", \
"s0","s1", \
#reg "16",#reg "17",#reg "18",#reg "19",#reg "20",#reg "21",#reg "22",#reg "23",\
#reg "24",#reg "25",#reg "26",#reg "27",#reg "28",#reg "29",#reg "30",#reg "31");\
return time / 256.0;\
}(cycle_per_rdtime)


#define ld_latency_asm_impl16(op) #op " x16, (x31);" \
#op " x17, (x16);" \
#op " x18, (x17);" \
#op " x19, (x18);" \
#op " x20, (x19);" \
#op " x21, (x20);" \
#op " x22, (x21);" \
#op " x23, (x22);" \
#op " x24, (x23);" \
#op " x25, (x24);" \
#op " x26, (x25);" \
#op " x27, (x26);" \
#op " x28, (x27);" \
#op " x29, (x28);" \
#op " x30, (x29);" \
#op " x31, (x30);"

#define ld_throughput_asm_impl16(reg, op) #op " " #reg "16, (x16);" \
#op " " #reg "17, (x16);" \
#op " " #reg "18, (x16);" \
#op " " #reg "19, (x16);" \
#op " " #reg "20, (x16);" \
#op " " #reg "21, (x16);" \
#op " " #reg "22, (x16);" \
#op " " #reg "23, (x16);" \
#op " " #reg "24, (x16);" \
#op " " #reg "25, (x16);" \
#op " " #reg "26, (x16);" \
#op " " #reg "27, (x16);" \
#op " " #reg "28, (x16);" \
#op " " #reg "29, (x16);" \
#op " " #reg "30, (x16);" \
#op " " #reg "31, (x16);"


#define ld_latency_asm(op, cycle_per_rdtime)   [](uint64_t c_p_rdtime){\
uint64_t time = 0;\
asm volatile( \
"mv     s1, %1;" \
"addi   sp,sp,-8;" \
"sd     sp, (sp);" \
"mv     x31, sp;" \
"rdtime s0;" \
"loop%=:" \
"addi   s1, s1, -1;" \
ld_latency_asm_impl16(op) \
ld_latency_asm_impl16(op) \
ld_latency_asm_impl16(op) \
ld_latency_asm_impl16(op) \
ld_latency_asm_impl16(op) \
ld_latency_asm_impl16(op) \
ld_latency_asm_impl16(op) \
ld_latency_asm_impl16(op) \
ld_latency_asm_impl16(op) \
ld_latency_asm_impl16(op) \
ld_latency_asm_impl16(op) \
ld_latency_asm_impl16(op) \
ld_latency_asm_impl16(op) \
ld_latency_asm_impl16(op) \
ld_latency_asm_impl16(op) \
ld_latency_asm_impl16(op) /* 16*16 = 256 */ \
"bne    s1, zero, loop%=;" \
"rdtime s1;" \
"sub    %0, s1, s0;" \
"addi	sp,sp,8;" \
: "=r"(time) \
: "r"(c_p_rdtime) \
: "memory", \
"s0","s1", \
"x16","x17","x18","x19","x20","x21","x22","x23",\
"x24","x25","x26","x27","x28","x29","x30","x31");\
return time / 256.0;\
}(cycle_per_rdtime)


#define ld_throughput_asm(reg, op, cycle_per_rdtime) [](uint64_t c_p_rdtime){\
uint64_t time = 0;\
asm volatile( \
"mv     s1, %1;"\
"addi   sp,sp,-512;"\
"addi   x16, sp, 32;" \
"addi   x17, zero, -1;" \
"slli   x17, x17, 5;"\
"and    x16, x16, x17;"  /* 32byte alignment*/\
"sd     x16, (x16);" \
"rdtime s0;" \
"loop%=:" \
"addi   s1, s1, -1;" \
ld_throughput_asm_impl16(reg, op) \
ld_throughput_asm_impl16(reg, op) \
ld_throughput_asm_impl16(reg, op) \
ld_throughput_asm_impl16(reg, op) \
ld_throughput_asm_impl16(reg, op) \
ld_throughput_asm_impl16(reg, op) \
ld_throughput_asm_impl16(reg, op) \
ld_throughput_asm_impl16(reg, op) \
ld_throughput_asm_impl16(reg, op) \
ld_throughput_asm_impl16(reg, op) \
ld_throughput_asm_impl16(reg, op) \
ld_throughput_asm_impl16(reg, op) \
ld_throughput_asm_impl16(reg, op) \
ld_throughput_asm_impl16(reg, op) \
ld_throughput_asm_impl16(reg, op) \
ld_throughput_asm_impl16(reg, op) /* 16*16 = 256 */ \
"bne    s1, zero, loop%=;" \
"rdtime s1;" \
"sub    %0, s1, s0;" \
"addi	sp,sp,512;"\
: "=r"(time) \
: "r"(c_p_rdtime) \
: "memory", \
"s0","s1", \
#reg "16",#reg "17",#reg "18",#reg "19",#reg "20",#reg "21",#reg "22",#reg "23",\
#reg "24",#reg "25",#reg "26",#reg "27",#reg "28",#reg "29",#reg "30",#reg "31");\
return time / 256.0;\
}(cycle_per_rdtime)

#define op2_op2_issue_check_asm_impl16(reg1, op1, reg2, op2) #op1 " " #reg1 "16, " #reg1 "16, " #reg1 "16;" \
#op2 " " #reg2 "17, " #reg2 "17, " #reg2 "17;" \
#op1 " " #reg1 "18, " #reg1 "18, " #reg1 "18;" \
#op2 " " #reg2 "19, " #reg2 "19, " #reg2 "19;" \
#op1 " " #reg1 "20, " #reg1 "20, " #reg1 "20;" \
#op2 " " #reg2 "21, " #reg2 "21, " #reg2 "21;" \
#op1 " " #reg1 "22, " #reg1 "22, " #reg1 "22;" \
#op2 " " #reg2 "23, " #reg2 "23, " #reg2 "23;" \
#op1 " " #reg1 "24, " #reg1 "24, " #reg1 "24;" \
#op2 " " #reg2 "25, " #reg2 "25, " #reg2 "25;" \
#op1 " " #reg1 "26, " #reg1 "26, " #reg1 "26;" \
#op2 " " #reg2 "27, " #reg2 "27, " #reg2 "27;" \
#op1 " " #reg1 "28, " #reg1 "28, " #reg1 "28;" \
#op2 " " #reg2 "29, " #reg2 "29, " #reg2 "29;" \
#op1 " " #reg1 "30, " #reg1 "30, " #reg1 "30;" \
#op2 " " #reg2 "31, " #reg2 "31, " #reg2 "31;"

#define op2_op3_issue_check_asm_impl16(reg1, op1, reg2, op2) #op1 " " #reg1 "16, " #reg1 "16, " #reg1 "16;" \
#op2 " " #reg2 "17, " #reg2 "17, " #reg2 "17, " #reg2 "17;" \
#op1 " " #reg1 "18, " #reg1 "18, " #reg1 "18;" \
#op2 " " #reg2 "19, " #reg2 "19, " #reg2 "19, " #reg2 "19;" \
#op1 " " #reg1 "20, " #reg1 "20, " #reg1 "20;" \
#op2 " " #reg2 "21, " #reg2 "21, " #reg2 "21, " #reg2 "21;" \
#op1 " " #reg1 "22, " #reg1 "22, " #reg1 "22;" \
#op2 " " #reg2 "23, " #reg2 "23, " #reg2 "23, " #reg2 "23;" \
#op1 " " #reg1 "24, " #reg1 "24, " #reg1 "24;" \
#op2 " " #reg2 "25, " #reg2 "25, " #reg2 "25, " #reg2 "25;" \
#op1 " " #reg1 "26, " #reg1 "26, " #reg1 "26;" \
#op2 " " #reg2 "27, " #reg2 "27, " #reg2 "27, " #reg2 "27;" \
#op1 " " #reg1 "28, " #reg1 "28, " #reg1 "28;" \
#op2 " " #reg2 "29, " #reg2 "29, " #reg2 "29, " #reg2 "29;" \
#op1 " " #reg1 "30, " #reg1 "30, " #reg1 "30;" \
#op2 " " #reg2 "31, " #reg2 "31, " #reg2 "31, " #reg2 "31;"

#define op2_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) #op1 " " #reg1 "16, " #reg1 "16, " #reg1 "16;" \
#op2 " " #reg2 "17, (x16);" \
#op1 " " #reg1 "18, " #reg1 "18, " #reg1 "18;" \
#op2 " " #reg2 "19, (x16);" \
#op1 " " #reg1 "20, " #reg1 "20, " #reg1 "20;" \
#op2 " " #reg2 "21, (x16);" \
#op1 " " #reg1 "22, " #reg1 "22, " #reg1 "22;" \
#op2 " " #reg2 "23, (x16);" \
#op1 " " #reg1 "24, " #reg1 "24, " #reg1 "24;" \
#op2 " " #reg2 "25, (x16);" \
#op1 " " #reg1 "26, " #reg1 "26, " #reg1 "26;" \
#op2 " " #reg2 "27, (x16);" \
#op1 " " #reg1 "28, " #reg1 "28, " #reg1 "28;" \
#op2 " " #reg2 "29, (x16);" \
#op1 " " #reg1 "30, " #reg1 "30, " #reg1 "30;" \
#op2 " " #reg2 "31, (x16);" \

#define op3_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) #op1 " " #reg1 "16, " #reg1 "16, " #reg1 "16, " #reg1 "16;" \
#op2 " " #reg2 "17, (x16);" \
#op1 " " #reg1 "18, " #reg1 "18, " #reg1 "18, " #reg1 "18;" \
#op2 " " #reg2 "19, (x16);" \
#op1 " " #reg1 "20, " #reg1 "20, " #reg1 "20, " #reg1 "20;" \
#op2 " " #reg2 "21, (x16);" \
#op1 " " #reg1 "22, " #reg1 "22, " #reg1 "22, " #reg1 "22;" \
#op2 " " #reg2 "23, (x16);" \
#op1 " " #reg1 "24, " #reg1 "24, " #reg1 "24, " #reg1 "24;" \
#op2 " " #reg2 "25, (x16);" \
#op1 " " #reg1 "26, " #reg1 "26, " #reg1 "26, " #reg1 "26;" \
#op2 " " #reg2 "27, (x16);" \
#op1 " " #reg1 "28, " #reg1 "28, " #reg1 "28, " #reg1 "28;" \
#op2 " " #reg2 "29, (x16);" \
#op1 " " #reg1 "30, " #reg1 "30, " #reg1 "30, " #reg1 "30;" \
#op2 " " #reg2 "31, (x16);" \

#define op2_op2_issue_check_asm(reg1, op1, reg2, op2, cycle_per_rdtime) [](uint64_t c_p_rdtime){\
uint64_t time = 0;\
asm volatile( \
"mv     s1, %1;"\
"rdtime s0;" \
"loop%=:" \
"addi   s1, s1, -1;" \
op2_op2_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op2_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op2_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op2_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op2_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op2_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op2_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op2_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op2_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op2_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op2_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op2_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op2_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op2_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op2_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op2_issue_check_asm_impl16(reg1, op1, reg2, op2) /* 16*16 = 256 */ \
"bne    s1, zero, loop%=;" \
"rdtime s1;" \
"sub    %0, s1, s0;" \
: "=r"(time) \
: "r"(c_p_rdtime) \
: "memory", \
"s0","s1", \
#reg1 "16",#reg1 "17",#reg1 "18",#reg1 "19",#reg1 "20",#reg1 "21",#reg1 "22",#reg1 "23",\
#reg1 "24",#reg1 "25",#reg1 "26",#reg1 "27",#reg1 "28",#reg1 "29",#reg1 "30",#reg1 "31",\
#reg2 "16",#reg2 "17",#reg2 "18",#reg2 "19",#reg2 "20",#reg2 "21",#reg2 "22",#reg2 "23",\
#reg2 "24",#reg2 "25",#reg2 "26",#reg2 "27",#reg2 "28",#reg2 "29",#reg2 "30",#reg2 "31");\
return time / 256.0;\
}(cycle_per_rdtime)


#define op2_op3_issue_check_asm(reg1, op1, reg2, op2, cycle_per_rdtime) [](uint64_t c_p_rdtime){\
uint64_t time = 0;\
asm volatile( \
"mv     s1, %1;"\
"rdtime s0;" \
"loop%=:" \
"addi   s1, s1, -1;" \
op2_op3_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op3_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op3_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op3_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op3_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op3_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op3_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op3_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op3_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op3_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op3_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op3_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op3_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op3_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op3_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_op3_issue_check_asm_impl16(reg1, op1, reg2, op2) /* 16*16 = 256 */ \
"bne    s1, zero, loop%=;" \
"rdtime s1;" \
"sub    %0, s1, s0;" \
: "=r"(time) \
: "r"(c_p_rdtime) \
: "memory", \
"s0","s1", \
#reg1 "16",#reg1 "17",#reg1 "18",#reg1 "19",#reg1 "20",#reg1 "21",#reg1 "22",#reg1 "23",\
#reg1 "24",#reg1 "25",#reg1 "26",#reg1 "27",#reg1 "28",#reg1 "29",#reg1 "30",#reg1 "31",\
#reg2 "16",#reg2 "17",#reg2 "18",#reg2 "19",#reg2 "20",#reg2 "21",#reg2 "22",#reg2 "23",\
#reg2 "24",#reg2 "25",#reg2 "26",#reg2 "27",#reg2 "28",#reg2 "29",#reg2 "30",#reg2 "31");\
return time / 256.0;\
}(cycle_per_rdtime)


#define op2_ld_issue_check_asm(reg1, op1, reg2, op2, cycle_per_rdtime) [](uint64_t c_p_rdtime){\
uint64_t time = 0;\
asm volatile( \
"mv     s1, %1;"\
"addi   sp,sp,-64;"\
"addi   x16, sp, 32;" \
"addi   x17, zero, -1;" \
"slli   x17, x17, 5;"\
"and    x16, x16, x17;"  /* 32byte alignment*/\
"sd     x16, (x16);" \
"rdtime s0;" \
"loop%=:" \
"addi   s1, s1, -1;" \
op2_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op2_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) /* 16*16 = 256 */ \
"bne    s1, zero, loop%=;" \
"rdtime s1;" \
"sub    %0, s1, s0;" \
"addi	sp,sp,64;"\
: "=r"(time) \
: "r"(c_p_rdtime) \
: "memory", \
"s0","s1", \
#reg1 "16",#reg1 "17",#reg1 "18",#reg1 "19",#reg1 "20",#reg1 "21",#reg1 "22",#reg1 "23",\
#reg1 "24",#reg1 "25",#reg1 "26",#reg1 "27",#reg1 "28",#reg1 "29",#reg1 "30",#reg1 "31",\
#reg2 "16",#reg2 "17",#reg2 "18",#reg2 "19",#reg2 "20",#reg2 "21",#reg2 "22",#reg2 "23",\
#reg2 "24",#reg2 "25",#reg2 "26",#reg2 "27",#reg2 "28",#reg2 "29",#reg2 "30",#reg2 "31");\
return time / 256.0;\
}(cycle_per_rdtime)


#define op3_ld_issue_check_asm(reg1, op1, reg2, op2, cycle_per_rdtime) [](uint64_t c_p_rdtime){\
uint64_t time = 0;\
asm volatile( \
"mv     s1, %1;"\
"addi   sp,sp,-64;"\
"addi   x16, sp, 32;" \
"addi   x17, zero, -1;" \
"slli   x17, x17, 5;"\
"and    x16, x16, x17;"  /* 32byte alignment*/\
"sd     x16, (x16);" \
"rdtime s0;" \
"loop%=:" \
"addi   s1, s1, -1;" \
op3_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op3_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op3_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op3_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op3_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op3_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op3_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op3_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op3_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op3_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op3_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op3_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op3_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op3_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op3_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) \
op3_ld_issue_check_asm_impl16(reg1, op1, reg2, op2) /* 16*16 = 256 */ \
"bne    s1, zero, loop%=;" \
"rdtime s1;" \
"sub    %0, s1, s0;" \
"addi	sp,sp,64;"\
: "=r"(time) \
: "r"(c_p_rdtime) \
: "memory", \
"s0","s1", \
#reg1 "16",#reg1 "17",#reg1 "18",#reg1 "19",#reg1 "20",#reg1 "21",#reg1 "22",#reg1 "23",\
#reg1 "24",#reg1 "25",#reg1 "26",#reg1 "27",#reg1 "28",#reg1 "29",#reg1 "30",#reg1 "31",\
#reg2 "16",#reg2 "17",#reg2 "18",#reg2 "19",#reg2 "20",#reg2 "21",#reg2 "22",#reg2 "23",\
#reg2 "24",#reg2 "25",#reg2 "26",#reg2 "27",#reg2 "28",#reg2 "29",#reg2 "30",#reg2 "31");\
return time / 256.0;\
}(cycle_per_rdtime)



#define op2_v_latency_asm_impl16(reg, op) #op " " #reg "0, " #reg "24, " #reg "24;" \
#op " " #reg "8, " #reg "0, " #reg "0;" \
#op " " #reg "16, " #reg "8, " #reg "8;" \
#op " " #reg "24, " #reg "16, " #reg "16;" \
#op " " #reg "0, " #reg "24, " #reg "24;" \
#op " " #reg "8, " #reg "0, " #reg "0;" \
#op " " #reg "16, " #reg "8, " #reg "8;" \
#op " " #reg "24, " #reg "16, " #reg "16;" \
#op " " #reg "0, " #reg "24, " #reg "24;" \
#op " " #reg "8, " #reg "0, " #reg "0;" \
#op " " #reg "16, " #reg "8, " #reg "8;" \
#op " " #reg "24, " #reg "16, " #reg "16;" \
#op " " #reg "0, " #reg "24, " #reg "24;" \
#op " " #reg "8, " #reg "0, " #reg "0;" \
#op " " #reg "16, " #reg "8, " #reg "8;" \
#op " " #reg "24, " #reg "16, " #reg "16;"

#define op2_v_throughput_asm_impl16(reg, op) #op " " #reg "0, " #reg "0, " #reg "0;" \
#op " " #reg "8, " #reg "8, " #reg "8;" \
#op " " #reg "16, " #reg "16, " #reg "16;" \
#op " " #reg "24, " #reg "24, " #reg "24;" \
#op " " #reg "0, " #reg "0, " #reg "0;" \
#op " " #reg "8, " #reg "8, " #reg "8;" \
#op " " #reg "16, " #reg "16, " #reg "16;" \
#op " " #reg "24, " #reg "24, " #reg "24;" \
#op " " #reg "0, " #reg "0, " #reg "0;" \
#op " " #reg "8, " #reg "8, " #reg "8;" \
#op " " #reg "16, " #reg "16, " #reg "16;" \
#op " " #reg "24, " #reg "24, " #reg "24;" \
#op " " #reg "0, " #reg "0, " #reg "0;" \
#op " " #reg "8, " #reg "8, " #reg "8;" \
#op " " #reg "16, " #reg "16, " #reg "16;" \
#op " " #reg "24, " #reg "24, " #reg "24;"

#define op2_v_latency_asm(reg, op, cycle_per_rdtime) [](uint64_t c_p_rdtime){\
uint64_t time = 0;\
asm volatile( \
"mv s1, %1;"\
"rdtime s0;" \
"loop%=:" \
"addi s1, s1, -1;" \
op2_v_latency_asm_impl16(reg, op) \
op2_v_latency_asm_impl16(reg, op) \
op2_v_latency_asm_impl16(reg, op) \
op2_v_latency_asm_impl16(reg, op) \
op2_v_latency_asm_impl16(reg, op) \
op2_v_latency_asm_impl16(reg, op) \
op2_v_latency_asm_impl16(reg, op) \
op2_v_latency_asm_impl16(reg, op) \
op2_v_latency_asm_impl16(reg, op) \
op2_v_latency_asm_impl16(reg, op) \
op2_v_latency_asm_impl16(reg, op) \
op2_v_latency_asm_impl16(reg, op) \
op2_v_latency_asm_impl16(reg, op) \
op2_v_latency_asm_impl16(reg, op) \
op2_v_latency_asm_impl16(reg, op) \
op2_v_latency_asm_impl16(reg, op) /* 16*16 = 256 */ \
"bne s1, zero, loop%=;" \
"rdtime s1;" \
"sub %0, s1, s0;" \
: "=r"(time) \
: "r"(c_p_rdtime) \
: "memory", \
"s0","s1", \
#reg "0",#reg "1",#reg "2",#reg "3",#reg "4",#reg "5",#reg "6",#reg "7",\
#reg "8",#reg "9",#reg "10",#reg "11",#reg "12",#reg "13",#reg "14",#reg "15",\
#reg "16",#reg "17",#reg "18",#reg "19",#reg "20",#reg "21",#reg "22",#reg "23",\
#reg "24",#reg "25",#reg "26",#reg "27",#reg "28",#reg "29",#reg "30",#reg "31");\
return time / 256.0;\
}(cycle_per_rdtime)

#define op2_v_throughput_asm(reg, op, cycle_per_rdtime) [](uint64_t c_p_rdtime){\
uint64_t time = 0;\
asm volatile( \
"mv s1, %1;"\
"rdtime s0;" \
"loop%=:" \
"addi s1, s1, -1;" \
op2_v_throughput_asm_impl16(reg, op) \
op2_v_throughput_asm_impl16(reg, op) \
op2_v_throughput_asm_impl16(reg, op) \
op2_v_throughput_asm_impl16(reg, op) \
op2_v_throughput_asm_impl16(reg, op) \
op2_v_throughput_asm_impl16(reg, op) \
op2_v_throughput_asm_impl16(reg, op) \
op2_v_throughput_asm_impl16(reg, op) \
op2_v_throughput_asm_impl16(reg, op) \
op2_v_throughput_asm_impl16(reg, op) \
op2_v_throughput_asm_impl16(reg, op) \
op2_v_throughput_asm_impl16(reg, op) \
op2_v_throughput_asm_impl16(reg, op) \
op2_v_throughput_asm_impl16(reg, op) \
op2_v_throughput_asm_impl16(reg, op) \
op2_v_throughput_asm_impl16(reg, op) /* 16*16 = 256 */ \
"bne s1, zero, loop%=;" \
"rdtime s1;" \
"sub %0, s1, s0;" \
: "=r"(time) \
: "r"(c_p_rdtime) \
: "memory", \
"s0","s1", \
#reg "0",#reg "1",#reg "2",#reg "3",#reg "4",#reg "5",#reg "6",#reg "7",\
#reg "8",#reg "9",#reg "10",#reg "11",#reg "12",#reg "13",#reg "14",#reg "15",\
#reg "16",#reg "17",#reg "18",#reg "19",#reg "20",#reg "21",#reg "22",#reg "23",\
#reg "24",#reg "25",#reg "26",#reg "27",#reg "28",#reg "29",#reg "30",#reg "31");\
return time / 256.0;\
}(cycle_per_rdtime)


#define vsetvl_latency_asm_impl16() "vsetivli   zero,4,e64,m1,ta,ma;" \
"vsetivli   zero,4,e64,m1,ta,ma;" \
"vsetivli   zero,4,e64,m1,ta,ma;" \
"vsetivli   zero,4,e64,m1,ta,ma;" \
"vsetivli   zero,4,e64,m1,ta,ma;" \
"vsetivli   zero,4,e64,m1,ta,ma;" \
"vsetivli   zero,4,e64,m1,ta,ma;" \
"vsetivli   zero,4,e64,m1,ta,ma;" \
"vsetivli   zero,4,e64,m1,ta,ma;" \
"vsetivli   zero,4,e64,m1,ta,ma;" \
"vsetivli   zero,4,e64,m1,ta,ma;" \
"vsetivli   zero,4,e64,m1,ta,ma;" \
"vsetivli   zero,4,e64,m1,ta,ma;" \
"vsetivli   zero,4,e64,m1,ta,ma;" \
"vsetivli   zero,4,e64,m1,ta,ma;" \
"vsetivli   zero,4,e64,m1,ta,ma;"


#define vsetvl_latency_asm(cycle_per_rdtime) [](uint64_t c_p_rdtime){\
uint64_t time = 0;\
asm volatile( \
"mv s1, %1;"\
"rdtime s0;" \
"loop%=:" \
"addi s1, s1, -1;" \
vsetvl_latency_asm_impl16() \
vsetvl_latency_asm_impl16() \
vsetvl_latency_asm_impl16() \
vsetvl_latency_asm_impl16() \
vsetvl_latency_asm_impl16() \
vsetvl_latency_asm_impl16() \
vsetvl_latency_asm_impl16() \
vsetvl_latency_asm_impl16() \
vsetvl_latency_asm_impl16() \
vsetvl_latency_asm_impl16() \
vsetvl_latency_asm_impl16() \
vsetvl_latency_asm_impl16() \
vsetvl_latency_asm_impl16() \
vsetvl_latency_asm_impl16() \
vsetvl_latency_asm_impl16() \
vsetvl_latency_asm_impl16() /* 16*16 = 256 */ \
"bne s1, zero, loop%=;" \
"rdtime s1;" \
"sub %0, s1, s0;" \
: "=r"(time) \
: "r"(c_p_rdtime) \
: "memory", \
"s0","s1");\
return time / 256.0;\
}(cycle_per_rdtime)

double cache_latency(uint64_t size, uint64_t cycle_per_rdtime){
    const auto length = size / sizeof(uint64_t);
    uint64_t* addr = (uint64_t*)std::aligned_alloc(2*1024*1024, size);

    std::mt19937_64 rnd_dev(std::random_device{}());
    for(uint64_t i = 0; i < length; ++i){
        addr[i] = *reinterpret_cast<uint64_t*>(&addr) + (rnd_dev() % length) * sizeof(uint64_t);
    }
    uint64_t time;
    asm volatile(
        "mv     s1, %1;"
        "rdtime s0;"
        "mv     t0, %2;"
        "loop%=:"
            "addi   s1, s1, -1;"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
        "bne    s1, zero, loop%=;"
        "rdtime s1;"
        "sub    %0, s1, s0;"
        : "=r"(time)
        : "r"(cycle_per_rdtime*100*16), "r"(addr)
        : "memory",
        "s0","s1","t0"
    );
    std::free(addr);
    return time / 256.0 / 100.0;
}

double tlb_latency(uint64_t tlbs, uint64_t cycle_per_rdtime){
    using uint64_ptr_t = uint64_t*;
    uint64_ptr_t* addrs = new uint64_ptr_t[tlbs];
    for(int i = 0; i < tlbs; ++i){
        addrs[i] = (uint64_t*)std::aligned_alloc(4*1024, sizeof(uint64_t)*tlbs);
    }

    for(uint64_t i = 0; i < tlbs; ++i){
        uint64_ptr_t addr = addrs[(i+1)%tlbs];
        addrs[i][i] = *reinterpret_cast<uint64_t*>(&addr) + ((i+1)%tlbs)*sizeof(uint64_t);
    }
    uint64_t time;
    asm volatile(
        "mv     s1, %1;"
        "rdtime s0;"
        "mv     t0, %2;"
        "loop%=:"
            "addi   s1, s1, -1;"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
        "bne    s1, zero, loop%=;"
        "rdtime s1;"
        "sub    %0, s1, s0;"
        : "=r"(time)
        : "r"(cycle_per_rdtime*100*16), "r"(addrs[0])
        : "memory",
        "s0","s1","t0"
    );
    for(int i = 0; i < tlbs; ++i){
        std::free(addrs[i]);
    }
    delete[] addrs;
    return time / 256.0 / 100.0;
}


double cache_way_latency(uint64_t ways, uint64_t cycle_per_rdtime){
    using uint64_ptr_t = uint64_t*;
    uint64_ptr_t* addrs = new uint64_ptr_t[ways];
    for(int i = 0; i < ways; ++i){
        addrs[i] = (uint64_t*)std::aligned_alloc(1024*1024, sizeof(uint64_t));
    }

    for(uint64_t i = 0; i < ways; ++i){
        uint64_ptr_t addr = addrs[(i+1)%ways];
        addrs[i][0] = *reinterpret_cast<uint64_t*>(&addr);
    }
    uint64_t time;
    asm volatile(
        "mv     s1, %1;"
        "rdtime s0;"
        "mv     t0, %2;"
        "loop%=:"
            "addi   s1, s1, -1;"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
            "ld     t0, (t0);"
        "bne    s1, zero, loop%=;"
        "rdtime s1;"
        "sub    %0, s1, s0;"
        : "=r"(time)
        : "r"(cycle_per_rdtime*100*16), "r"(addrs[0])
        : "memory",
        "s0","s1","t0"
    );
    for(int i = 0; i < ways; ++i){
        std::free(addrs[i]);
    }
    delete[] addrs;
    return time / 256.0 / 100.0;
}


double memory_throughput(uint64_t size, uint64_t cycle_per_rdtime, uint64_t cpu_Hz){
    uint64_t size_align = size - size % 128;
    uint64_t* addr = (uint64_t*)std::aligned_alloc(2*1024*1024, size_align);

    double bytes_per_sec = 0;
    for(int i = 0; i < 1000; ++i){
        uint64_t time;
        asm volatile(
            "mv     s1, %1;"
            "rdtime s0;"
            "mv     t0, %2;"
            "li     t1, 2048;"
            "add    t1, %2, t1;"
            "vsetivli   zero,4,e64,m1,ta,ma;"
            "loop%=:"
                "addi   s1, s1, -1;"
                "vle64.v  v0, (t0); addi t0, t0, 32;"
                "vle64.v  v0, (t0); addi t0, t0, 32;"
                "vle64.v  v0, (t0); addi t0, t0, 32;"
                "vle64.v  v0, (t0); addi t0, t0, 32;"
                "vle64.v  v0, (t0); addi t0, t0, 32;"
                "vle64.v  v0, (t0); addi t0, t0, 32;"
                "vle64.v  v0, (t0); addi t0, t0, 32;"
                "vle64.v  v0, (t0); addi t0, t0, 32;" // 32*8bytes
            "bne    s1, zero, loop%=;"
            "rdtime s1;"
            "sub    %0, s1, s0;"
            : "=r"(time)
            : "r"(size_align/(8*32)), "r"(addr)
            : "memory",
            "s0","s1","t0","t1","v0"
        );
        bytes_per_sec += ((double)size_align*cpu_Hz)/((double)time*cycle_per_rdtime);
    }
    std::free(addr);
    return bytes_per_sec/1000.0;
}


double core_latency(uint64_t core1, uint64_t core2, uint64_t cycle_per_rdtime){
    volatile uint64_t* shared = (uint64_t*)std::aligned_alloc(4*1024, sizeof(uint64_t));
    *shared = 3;
    std::atomic<double> times[2];

    const auto pingpong = [](uint64_t cycle_per_rdtime, volatile uint64_t* shared, uint64_t id, bool odd, std::atomic<double>* time_ref){
        cpu_set_t cpu_set;
        CPU_ZERO(&cpu_set);
        CPU_SET(id, &cpu_set);
        sched_setaffinity(syscall(SYS_gettid), sizeof(cpu_set), &cpu_set);

        while(*shared == 3);
        uint64_t time;
        asm volatile(
            "mv     s1, %1;"
            "rdtime s0;"
            "loop%=:"
                "addi   s1, s1, -1;"
                "busy_loop%=:"
                    "ld  t0, (%2);"
                    "beq t0, %3, busy_loop%=;"
                "sd %3, (%2);"
            "bne    s1, zero, loop%=;"
            "rdtime s1;"
            "sub    %0, s1, s0;"
            : "=r"(time)
            : "r"(cycle_per_rdtime*100), "r"(shared), "r"((uint64_t)odd)
            : "memory",
            "s0","s1","t0"
        );
        *time_ref = time / 100.0;
    };

    std::thread th0(pingpong, cycle_per_rdtime, shared, core1, 0, &times[0]);
    std::thread th1(pingpong, cycle_per_rdtime, shared, core2, 1, &times[1]);
    *shared = 0;
    th0.join();
    th1.join();

    std::free((void*)shared);
    return std::min(times[0], times[1])/ 2.0;
}

