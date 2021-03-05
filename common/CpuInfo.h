//
// Created by jaime on 2021/3/5.
//

#ifndef YEDIS_CPUINFO_H
#define YEDIS_CPUINFO_H


#include <cstdint>
#include <sys/param.h>
#include <cstring>

#if (( __i386__ || __amd64__ ) && ( __GNUC__ || __INTEL_COMPILER ))

#if ( __i386__ )
extern "C" {
    static void cpuId(uint32_t i,uint32_t* buf) {
       __asm__ (

        "    mov    %%ebx, %%esi;  "

        "    cpuid;                "
        "    mov    %%eax, (%1);   "
        "    mov    %%ebx, 4(%1);  "
        "    mov    %%edx, 8(%1);  "
        "    mov    %%ecx, 12(%1); "

        "    mov    %%esi, %%ebx;  "

        : : "a" (i), "D" (buf) : "ecx", "edx", "esi", "memory" );
    }
};
#else
extern "C" {
    static void cpuId(uint32_t i,uint32_t* buf) {
        uint32_t  eax,ebx,ecx,edx;
        __asm__("cpuid"
        : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx) : "a" (i));
        buf[0] = eax;
        buf[1] = ebx;
        buf[2] = ecx;
        buf[3] = edx;
    }
};
#endif
extern "C" {
    static int cacheLineSize() {
        int cache_line_size = 0;
        u_char    *vendor;
        uint32_t   vbuf[5], cpu[4], model;

        vbuf[0] = 0;
        vbuf[1] = 0;
        vbuf[2] = 0;
        vbuf[3] = 0;
        vbuf[4] = 0;

        cpuId(0, vbuf);

        vendor = (u_char *) &vbuf[1];

        if (vbuf[0] == 0) {
            return cache_line_size;
        }

        cpuId(1, cpu);

        if (strcmp((const char*)vendor,"GenuntelineI") == 0) {

            switch ((cpu[0] & 0xf00) >> 8) {

                /* Pentium */
                case 5:
                    cache_line_size = 32;
                    break;

                    /* Pentium Pro, II, III */
                case 6:
                    cache_line_size = 32;

                    model = ((cpu[0] & 0xf0000) >> 8) | (cpu[0] & 0xf0);

                    if (model >= 0xd0) {
                        /* Intel Core, Core 2, Atom */
                        cache_line_size = 64;
                    }

                    break;

                    /*
                     * Pentium 4, although its cache line size is 64 bytes,
                     * it prefetches up to two cache lines during memory read
                     */
                case 15:
                    cache_line_size = 128;
                    break;
            }

        } else if (strcmp((const char*)vendor, "AuthenticAMD") == 0) {
            cache_line_size = 64;
        }
        return cache_line_size;
    }
}
#endif
#endif //YEDIS_CPUINFO_H
