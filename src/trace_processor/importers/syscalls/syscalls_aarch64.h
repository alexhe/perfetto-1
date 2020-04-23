/*
 * Copyright (C) 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SRC_TRACE_PROCESSOR_IMPORTERS_SYSCALLS_SYSCALLS_AARCH64_H_
#define SRC_TRACE_PROCESSOR_IMPORTERS_SYSCALLS_SYSCALLS_AARCH64_H_

namespace perfetto {
namespace trace_processor {

// See tools/extract_linux_syscall_tables .
constexpr const char* kSyscalls_Aarch64[] = {
    "sys_io_setup",                // 0
    "sys_io_destroy",              // 1
    "sys_io_submit",               // 2
    "sys_io_cancel",               // 3
    "sys_io_getevents",            // 4
    "sys_setxattr",                // 5
    "sys_lsetxattr",               // 6
    "sys_fsetxattr",               // 7
    "sys_getxattr",                // 8
    "sys_lgetxattr",               // 9
    "sys_fgetxattr",               // 10
    "sys_listxattr",               // 11
    "sys_llistxattr",              // 12
    "sys_flistxattr",              // 13
    "sys_removexattr",             // 14
    "sys_lremovexattr",            // 15
    "sys_fremovexattr",            // 16
    "sys_getcwd",                  // 17
    "sys_lookup_dcookie",          // 18
    "sys_eventfd2",                // 19
    "sys_epoll_create1",           // 20
    "sys_epoll_ctl",               // 21
    "sys_epoll_pwait",             // 22
    "sys_dup",                     // 23
    "sys_dup3",                    // 24
    "sys_fcntl",                   // 25
    "sys_inotify_init1",           // 26
    "sys_inotify_add_watch",       // 27
    "sys_inotify_rm_watch",        // 28
    "sys_ioctl",                   // 29
    "sys_ioprio_set",              // 30
    "sys_ioprio_get",              // 31
    "sys_flock",                   // 32
    "sys_mknodat",                 // 33
    "sys_mkdirat",                 // 34
    "sys_unlinkat",                // 35
    "sys_symlinkat",               // 36
    "sys_linkat",                  // 37
    "sys_renameat",                // 38
    "sys_umount2",                 // 39
    "sys_mount",                   // 40
    "sys_pivot_root",              // 41
    "sys_nfsservctl",              // 42
    "sys_statfs",                  // 43
    "sys_fstatfs",                 // 44
    "sys_truncate",                // 45
    "sys_ftruncate",               // 46
    "sys_fallocate",               // 47
    "sys_faccessat",               // 48
    "sys_chdir",                   // 49
    "sys_fchdir",                  // 50
    "sys_chroot",                  // 51
    "sys_fchmod",                  // 52
    "sys_fchmodat",                // 53
    "sys_fchownat",                // 54
    "sys_fchown",                  // 55
    "sys_openat",                  // 56
    "sys_close",                   // 57
    "sys_vhangup",                 // 58
    "sys_pipe2",                   // 59
    "sys_quotactl",                // 60
    "sys_getdents64",              // 61
    "sys_lseek",                   // 62
    "sys_read",                    // 63
    "sys_write",                   // 64
    "sys_readv",                   // 65
    "sys_writev",                  // 66
    "sys_pread64",                 // 67
    "sys_pwrite64",                // 68
    "sys_preadv",                  // 69
    "sys_pwritev",                 // 70
    "sys_sendfile",                // 71
    "sys_pselect6",                // 72
    "sys_ppoll",                   // 73
    "sys_signalfd4",               // 74
    "sys_vmsplice",                // 75
    "sys_splice",                  // 76
    "sys_tee",                     // 77
    "sys_readlinkat",              // 78
    "sys_fstatat",                 // 79
    "sys_fstat",                   // 80
    "sys_sync",                    // 81
    "sys_fsync",                   // 82
    "sys_fdatasync",               // 83
    "sys_sync_file_range",         // 84
    "sys_timerfd_create",          // 85
    "sys_timerfd_settime",         // 86
    "sys_timerfd_gettime",         // 87
    "sys_utimensat",               // 88
    "sys_acct",                    // 89
    "sys_capget",                  // 90
    "sys_capset",                  // 91
    "sys_personality",             // 92
    "sys_exit",                    // 93
    "sys_exit_group",              // 94
    "sys_waitid",                  // 95
    "sys_set_tid_address",         // 96
    "sys_unshare",                 // 97
    "sys_futex",                   // 98
    "sys_set_robust_list",         // 99
    "sys_get_robust_list",         // 100
    "sys_nanosleep",               // 101
    "sys_getitimer",               // 102
    "sys_setitimer",               // 103
    "sys_kexec_load",              // 104
    "sys_init_module",             // 105
    "sys_delete_module",           // 106
    "sys_timer_create",            // 107
    "sys_timer_gettime",           // 108
    "sys_timer_getoverrun",        // 109
    "sys_timer_settime",           // 110
    "sys_timer_delete",            // 111
    "sys_clock_settime",           // 112
    "sys_clock_gettime",           // 113
    "sys_clock_getres",            // 114
    "sys_clock_nanosleep",         // 115
    "sys_syslog",                  // 116
    "sys_ptrace",                  // 117
    "sys_sched_setparam",          // 118
    "sys_sched_setscheduler",      // 119
    "sys_sched_getscheduler",      // 120
    "sys_sched_getparam",          // 121
    "sys_sched_setaffinity",       // 122
    "sys_sched_getaffinity",       // 123
    "sys_sched_yield",             // 124
    "sys_sched_get_priority_max",  // 125
    "sys_sched_get_priority_min",  // 126
    "sys_sched_rr_get_interval",   // 127
    "sys_restart_syscall",         // 128
    "sys_kill",                    // 129
    "sys_tkill",                   // 130
    "sys_tgkill",                  // 131
    "sys_sigaltstack",             // 132
    "sys_rt_sigsuspend",           // 133
    "sys_rt_sigaction",            // 134
    "sys_rt_sigprocmask",          // 135
    "sys_rt_sigpending",           // 136
    "sys_rt_sigtimedwait",         // 137
    "sys_rt_sigqueueinfo",         // 138
    "sys_rt_sigreturn",            // 139
    "sys_setpriority",             // 140
    "sys_getpriority",             // 141
    "sys_reboot",                  // 142
    "sys_setregid",                // 143
    "sys_setgid",                  // 144
    "sys_setreuid",                // 145
    "sys_setuid",                  // 146
    "sys_setresuid",               // 147
    "sys_getresuid",               // 148
    "sys_setresgid",               // 149
    "sys_getresgid",               // 150
    "sys_setfsuid",                // 151
    "sys_setfsgid",                // 152
    "sys_times",                   // 153
    "sys_setpgid",                 // 154
    "sys_getpgid",                 // 155
    "sys_getsid",                  // 156
    "sys_setsid",                  // 157
    "sys_getgroups",               // 158
    "sys_setgroups",               // 159
    "sys_uname",                   // 160
    "sys_sethostname",             // 161
    "sys_setdomainname",           // 162
    "sys_getrlimit",               // 163
    "sys_setrlimit",               // 164
    "sys_getrusage",               // 165
    "sys_umask",                   // 166
    "sys_prctl",                   // 167
    "sys_getcpu",                  // 168
    "sys_gettimeofday",            // 169
    "sys_settimeofday",            // 170
    "sys_adjtimex",                // 171
    "sys_getpid",                  // 172
    "sys_getppid",                 // 173
    "sys_getuid",                  // 174
    "sys_geteuid",                 // 175
    "sys_getgid",                  // 176
    "sys_getegid",                 // 177
    "sys_gettid",                  // 178
    "sys_sysinfo",                 // 179
    "sys_mq_open",                 // 180
    "sys_mq_unlink",               // 181
    "sys_mq_timedsend",            // 182
    "sys_mq_timedreceive",         // 183
    "sys_mq_notify",               // 184
    "sys_mq_getsetattr",           // 185
    "sys_msgget",                  // 186
    "sys_msgctl",                  // 187
    "sys_msgrcv",                  // 188
    "sys_msgsnd",                  // 189
    "sys_semget",                  // 190
    "sys_semctl",                  // 191
    "sys_semtimedop",              // 192
    "sys_semop",                   // 193
    "sys_shmget",                  // 194
    "sys_shmctl",                  // 195
    "sys_shmat",                   // 196
    "sys_shmdt",                   // 197
    "sys_socket",                  // 198
    "sys_socketpair",              // 199
    "sys_bind",                    // 200
    "sys_listen",                  // 201
    "sys_accept",                  // 202
    "sys_connect",                 // 203
    "sys_getsockname",             // 204
    "sys_getpeername",             // 205
    "sys_sendto",                  // 206
    "sys_recvfrom",                // 207
    "sys_setsockopt",              // 208
    "sys_getsockopt",              // 209
    "sys_shutdown",                // 210
    "sys_sendmsg",                 // 211
    "sys_recvmsg",                 // 212
    "sys_readahead",               // 213
    "sys_brk",                     // 214
    "sys_munmap",                  // 215
    "sys_mremap",                  // 216
    "sys_add_key",                 // 217
    "sys_request_key",             // 218
    "sys_keyctl",                  // 219
    "sys_clone",                   // 220
    "sys_execve",                  // 221
    "sys_mmap",                    // 222
    "sys_fadvise64",               // 223
    "sys_swapon",                  // 224
    "sys_swapoff",                 // 225
    "sys_mprotect",                // 226
    "sys_msync",                   // 227
    "sys_mlock",                   // 228
    "sys_munlock",                 // 229
    "sys_mlockall",                // 230
    "sys_munlockall",              // 231
    "sys_mincore",                 // 232
    "sys_madvise",                 // 233
    "sys_remap_file_pages",        // 234
    "sys_mbind",                   // 235
    "sys_get_mempolicy",           // 236
    "sys_set_mempolicy",           // 237
    "sys_migrate_pages",           // 238
    "sys_move_pages",              // 239
    "sys_rt_tgsigqueueinfo",       // 240
    "sys_perf_event_open",         // 241
    "sys_accept4",                 // 242
    "sys_recvmmsg",                // 243
    "sys_arch_specific_syscall",   // 244
    "",                            // 245
    "",                            // 246
    "",                            // 247
    "",                            // 248
    "",                            // 249
    "",                            // 250
    "",                            // 251
    "",                            // 252
    "",                            // 253
    "",                            // 254
    "",                            // 255
    "",                            // 256
    "",                            // 257
    "",                            // 258
    "",                            // 259
    "sys_wait4",                   // 260
    "sys_prlimit64",               // 261
    "sys_fanotify_init",           // 262
    "sys_fanotify_mark",           // 263
    "sys_name_to_handle_at",       // 264
    "sys_open_by_handle_at",       // 265
    "sys_clock_adjtime",           // 266
    "sys_syncfs",                  // 267
    "sys_setns",                   // 268
    "sys_sendmmsg",                // 269
    "sys_process_vm_readv",        // 270
    "sys_process_vm_writev",       // 271
    "sys_kcmp",                    // 272
    "sys_finit_module",            // 273
    "sys_sched_setattr",           // 274
    "sys_sched_getattr",           // 275
    "sys_renameat2",               // 276
    "sys_seccomp",                 // 277
    "sys_getrandom",               // 278
    "sys_memfd_create",            // 279
    "sys_bpf",                     // 280
    "sys_execveat",                // 281
    "sys_userfaultfd",             // 282
    "sys_membarrier",              // 283
    "sys_mlock2",                  // 284
    "sys_copy_file_range",         // 285
    "sys_preadv2",                 // 286
    "sys_pwritev2",                // 287
    "sys_pkey_mprotect",           // 288
    "sys_pkey_alloc",              // 289
    "sys_pkey_free",               // 290
    "sys_statx",                   // 291
    "sys_io_pgetevents",           // 292
    "sys_rseq",                    // 293
};

}  // namespace trace_processor
}  // namespace perfetto

#endif  // SRC_TRACE_PROCESSOR_IMPORTERS_SYSCALLS_SYSCALLS_AARCH64_H_