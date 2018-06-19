#pragma once
#ifndef CARBON_DEFINE_H
#define CARBON_DEFINE_H
#ifndef NULL
#define NULL 0
#endif // NULL
typedef enum __bool__ {
    TRUE = 1, FALSE = 0
} Bool;
typedef enum __system_rpl__ {
    KERNEL = 0, USER = 3
} SystemRPL;
typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef unsigned int size_t;
#endif // CARBON_DEFINE_H