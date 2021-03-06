/*
 *
 * Copyright 2018 Asylo authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef ASYLO_PLATFORM_COMMON_BRIDGE_TYPES_H_
#define ASYLO_PLATFORM_COMMON_BRIDGE_TYPES_H_

#include <netdb.h>
#include <netinet/tcp.h>
#include <signal.h>
#include <stdint.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <syslog.h>

#include "absl/base/attributes.h"

// This file provides a set of type definitions used both inside and outside the
// enclave.

#ifdef __cplusplus
extern "C" {
#endif

// Replace size_t, ssize_t, and sigset_t with types of known width for
// transmission across the enclave boundary.
typedef uint64_t bridge_size_t;
typedef int64_t bridge_ssize_t;
typedef int64_t bridge_sigset_t;

// This enum contains all of the sysconf name values supported inside the
// enclave.
enum SysconfConstants { UNKNOWN = 0, NPROCESSORS_ONLN = 1 };

// The wait options that are supported inside the enclave.
enum WaitOptions {
  BRIDGE_WNOHANG = 1,
};

// The code byte of wstatus that are supported inside the enclave. The last 8
// bit of wstatus is the code byte. WIFEXITED returns true if the code byte is
// 0. WIFSTOPPED returns true if the code byte is 0x7f. Otherwise WIFSIGNALED
// returns true.
enum WStatusCode {
  BRIDGE_WCODEBYTE = 0xff,
  BRIDGE_WSTOPPED = 0x7f,
};

struct BridgeWStatus {
  uint8_t code;
  uint8_t info;
};

// The possible actions when calling sigprocmask.
enum SigMaskAction {
  BRIDGE_SIG_SETMASK = 0,
  BRIDGE_SIG_BLOCK = 1,
  BRIDGE_SIG_UNBLOCK = 2,
};

// All the signals that are supported to be registered inside enclave (except
// SIGSTOP and SIGKILL).
enum SignalNumber {
  BRIDGE_SIGHUP = 1,
  BRIDGE_SIGINT = 2,
  BRIDGE_SIGQUIT = 3,
  BRIDGE_SIGILL = 4,
  BRIDGE_SIGTRAP = 5,
  BRIDGE_SIGABRT = 6,
  BRIDGE_SIGBUS = 7,
  BRIDGE_SIGFPE = 8,
  BRIDGE_SIGKILL = 9,
  BRIDGE_SIGUSR1 = 10,
  BRIDGE_SIGSEGV = 11,
  BRIDGE_SIGUSR2 = 12,
  BRIDGE_SIGPIPE = 13,
  BRIDGE_SIGALRM = 14,
  BRIDGE_SIGTERM = 15,
  BRIDGE_SIGCHLD = 16,
  BRIDGE_SIGCONT = 17,
  BRIDGE_SIGSTOP = 18,
  BRIDGE_SIGTSTP = 19,
  BRIDGE_SIGTTIN = 20,
  BRIDGE_SIGTTOU = 21,
  BRIDGE_SIGURG = 22,
  BRIDGE_SIGXCPU = 23,
  BRIDGE_SIGXFSZ = 24,
  BRIDGE_SIGVTALRM = 25,
  BRIDGE_SIGPROF = 26,
  BRIDGE_SIGWINCH = 27,
  BRIDGE_SIGSYS = 28,
  BRIDGE_SIGRTMIN = 32,
  BRIDGE_SIGRTMAX = 64,
};

// The code that describes the cause of a signal.
enum SignalCode {
  BRIDGE_SI_USER = 1,
  BRIDGE_SI_QUEUE = 2,
  BRIDGE_SI_TIMER = 3,
  BRIDGE_SI_ASYNCIO = 4,
  BRIDGE_SI_MESGQ = 5,
};

// The address info flags that specifies options of an addrinfo struct.
enum AddrInfoFlags {
  BRIDGE_AI_CANONNAME = 0x0002,
  BRIDGE_AI_NUMERICHOST = 0x0004,
};

// All of the file operation flags supported inside the enclave.
enum FileStatusFlags {
  RDONLY = 0x00,
  WRONLY = 0x01,
  RDWR = 0x02,
  CREAT = 0x40,
  EXCL = 0x80,
  TRUNC = 0x200,
  APPEND = 0x400,
  NONBLOCK = 0x800,
};

enum FileDescriptorFlags {
  CLOEXEC = 0x01,
};

// All the syslog options supported inside the enclave.
enum SysLogOptions {
  BRIDGE_LOG_PID = 0x01,
  BRIDGE_LOG_CONS = 0x02,
  BRIDGE_LOG_ODELAY = 0x04,
  BRIDGE_LOG_NDELAY = 0x08,
  BRIDGE_LOG_NOWAIT = 0x10,
  BRIDGE_LOG_PERROR = 0x20,
};

// All the syslog facilities supported inside the enclave.
enum SysLogFacilities {
  BRIDGE_LOG_USER = 1 << 3,
  BRIDGE_LOG_LOCAL0 = 16 << 3,
  BRIDGE_LOG_LOCAL1 = 17 << 3,
  BRIDGE_LOG_LOCAL2 = 18 << 3,
  BRIDGE_LOG_LOCAL3 = 19 << 3,
  BRIDGE_LOG_LOCAL4 = 20 << 3,
  BRIDGE_LOG_LOCAL5 = 21 << 3,
  BRIDGE_LOG_LOCAL6 = 22 << 3,
  BRIDGE_LOG_LOCAL7 = 23 << 3,
};

// All the supported syslog level that are allowed to be called outside the
// enclave.
enum SysLogLevel {
  BRIDGE_LOG_EMERG = 0,
  BRIDGE_LOG_ALERT = 1,
  BRIDGE_LOG_CRIT = 2,
  BRIDGE_LOG_ERR = 3,
  BRIDGE_LOG_WARNING = 4,
  BRIDGE_LOG_NOTICE = 5,
  BRIDGE_LOG_INFO = 6,
  BRIDGE_LOG_DEBUG = 7,
};

// All tcp option names supported inside the enclave.
enum TcpOptionNames {
  BRIDGE_TCP_NODELAY = 1,
  BRIDGE_TCP_KEEPIDLE = 4,
  BRIDGE_TCP_KEEPINTVL = 5,
  BRIDGE_TCP_KEEPCNT = 6,
};

// All socket option names supported inside the enclave.
enum SocketOptionNames {
  BRIDGE_SO_DEBUG = 1,
  BRIDGE_SO_REUSEADDR = 2,
  BRIDGE_SO_TYPE = 3,
  BRIDGE_SO_ERROR = 4,
  BRIDGE_SO_DONTROUTE = 5,
  BRIDGE_SO_BROADCAST = 6,
  BRIDGE_SO_SNDBUF = 7,
  BRIDGE_SO_RCVBUF = 8,
  BRIDGE_SO_KEEPALIVE = 9,
  BRIDGE_SO_OOBINLINE = 10,
  BRIDGE_SO_NO_CHECK = 11,
  BRIDGE_SO_PRIORITY = 12,
  BRIDGE_SO_LINGER = 13,
  BRIDGE_SO_BSDCOMPAT = 14,
  BRIDGE_SO_REUSEPORT = 15,
  BRIDGE_SO_RCVTIMEO = 20,
  BRIDGE_SO_SNDTIMEO = 21,
  BRIDGE_SO_SNDBUFFORCE = 32,
  BRIDGE_SO_RCVBUFFORCE = 33,
};

struct bridge_in_addr {
  uint32_t inet_addr;
} ABSL_ATTRIBUTE_PACKED;

struct bridge_in6_addr {
  uint8_t inet6_addr[16];
} ABSL_ATTRIBUTE_PACKED;

struct bridge_sockaddr_in6 {
  uint16_t sin6_port;
  uint32_t sin6_flowinfo;
  struct bridge_in6_addr sin6_addr;
  uint32_t sin6_scope_id;
} ABSL_ATTRIBUTE_PACKED;

struct bridge_sockaddr_in {
  uint16_t sin_port;
  struct bridge_in_addr sin_addr;
  char sin_zero[8];
} ABSL_ATTRIBUTE_PACKED;

struct bridge_sockaddr_un {
  char sun_path[108];
} ABSL_ATTRIBUTE_PACKED;

// This is max(sizeof(struct sockaddr_in), sizeof(struct sockaddr_un)). Struct
// bridge_sockaddr can be converted from/to struct sockaddr in ocalls. Since
// struct sockaddr can be the address of UNIX domain socket (sockaddr_un) in
// socket-related syscalls, struct bridge_sockaddr needs enough space to
// represent it.
struct bridge_sockaddr {
  uint16_t sa_family;
  union {
    struct bridge_sockaddr_in addr_in;
    struct bridge_sockaddr_in6 addr_in6;
    struct bridge_sockaddr_un addr_un;
  } ABSL_ATTRIBUTE_PACKED;
} ABSL_ATTRIBUTE_PACKED;

typedef int64_t bridge_clockid_t;

struct bridge_timeval {
  int64_t tv_sec;
  int64_t tv_usec;
} ABSL_ATTRIBUTE_PACKED;

struct bridge_timespec {
  int64_t tv_sec;
  int64_t tv_nsec;
} ABSL_ATTRIBUTE_PACKED;

struct bridge_stat {
  int64_t st_dev;
  int64_t st_ino;
  int64_t st_mode;
  int64_t st_nlink;
  int64_t st_uid;
  int64_t st_gid;
  int64_t st_rdev;
  int64_t st_size;
  int64_t st_atime_enc;
  int64_t st_mtime_enc;
  int64_t st_ctime_enc;
  int64_t st_blksize;
  int64_t st_blocks;
} ABSL_ATTRIBUTE_PACKED;

struct bridge_pollfd {
  int32_t fd;
  int16_t events;
  int16_t revents;
};

struct bridge_msghdr {
  void *msg_name;
  uint64_t msg_namelen;
  struct bridge_iovec *msg_iov;
  uint64_t msg_iovlen;
  void *msg_control;
  uint64_t msg_controllen;
  int32_t msg_flags;
};

struct bridge_iovec {
  void *iov_base;
  uint64_t iov_len;
};

struct bridge_siginfo_t {
  int32_t si_signo;
  int32_t si_code;
};

struct BridgeSignalHandler {
  void (*sigaction)(int, struct bridge_siginfo_t *, void *);
  bridge_sigset_t mask;
};

struct BridgeRUsage {
  struct bridge_timeval ru_utime;
  struct bridge_timeval ru_stime;
};

// The maximum number of CPUs we support. Chosen to be large enough to represent
// as many CPUs as an enclave-native cpu_set_t.
#define BRIDGE_CPU_SET_MAX_CPUS 1024

typedef uint64_t BridgeCpuSetWord;

#define BRIDGE_CPU_SET_NUM_WORDS                                  \
  ((BRIDGE_CPU_SET_MAX_CPUS / 8 + sizeof(BridgeCpuSetWord) - 1) / \
   sizeof(BridgeCpuSetWord))

// Represents a set of (up to) BRIDGE_CPU_SET_MAX_CPUS CPUs as a bitset. The nth
// bit of words[i] corresponds to CPU no. sizeof(BridgeCpuSetWord) * i + n.
struct BridgeCpuSet {
  BridgeCpuSetWord words[BRIDGE_CPU_SET_NUM_WORDS];
} ABSL_ATTRIBUTE_PACKED;

// Converts |bridge_sysconf_constant| to a runtime sysconf constant. Returns -1
// if unsuccessful.
int FromSysconfConstants(enum SysconfConstants bridge_sysconf_constant);

// Converts |sysconf_constant| to a bridge constant. Returns UNKNOWN if
// unsuccessful.
enum SysconfConstants ToSysconfConstants(int sysconf_constant);

// Converts |bridge_wait_options| to runtime wait options. Returns 0 if no
// supported wait options are provided.
int FromBridgeWaitOptions(int bridge_wait_options);

// Converts |wait_options| to bridge wait options. Returns 0 if no supported
// wait options are provided.
int ToBridgeWaitOptions(int wait_options);

// Converts the sigpromask action |bridge_how| to a runtime signal mask action.
// Returns -1 if unsuccessful.
int FromBridgeSigMaskAction(int bridge_how);

// Converts the sigprocmask action |how| to a bridge signal mask action. Returns
// -1 if unsuccessful.
int ToBridgeSigMaskAction(int how);

// Converts |bridge_set| to a runtime signal mask set. Returns nullptr if
// unsuccessful.
sigset_t *FromBridgeSigSet(const bridge_sigset_t *bridge_set, sigset_t *set);

// Converts |set| to a bridge signal mask set. Returns nullptr if unsuccessful.
bridge_sigset_t *ToBridgeSigSet(const sigset_t *set,
                                bridge_sigset_t *bridge_set);

// Converts |bridge_signum| to a runtime signal number. Returns -1 if
// unsuccessful.
int FromBridgeSignal(int bridge_signum);

// Converts |signum| to a bridge signal number. Returns -1 if unsuccessful.
int ToBridgeSignal(int signum);

// Converts |bridge_si_code| to a runtime signal code. Returns -1 if
// unsuccessful.
int FromBridgeSignalCode(int bridge_si_code);

// Converts |si_code| to a bridge signal code. Returns -1 if unsuccessful.
int ToBridgeSignalCode(int si_code);

// Converts |bridge_siginfo| to a runtime siginfo_t. Returns nullptr if
// unsuccessful.
siginfo_t *FromBridgeSigInfo(const struct bridge_siginfo_t *bridge_siginfo,
                             siginfo_t *siginfo);

// Converts |siginfo| to a bridge siginfo_t. Returns nullptr if unsuccessful.
struct bridge_siginfo_t *ToBridgeSigInfo(
    const siginfo_t *siginfo, struct bridge_siginfo_t *bridge_siginfo);

// Converts |bridge_ai_flag| to a runtime file flag. Returns 0 if no supported
// flags are provided.
int FromBridgeAddressInfoFlags(int bridge_ai_flag);

// Converts |ai_flag| to a bridge address info flag. Returns 0 if no supported
// flags are provided.
int ToBridgeAddressInfoFlags(int ai_flag);

// Converts |bridge_syslog_option| to a runtime syslog option. Returns 0 if
// |bridge_syslog_option| does not contain any supported options.
int FromBridgeSysLogOption(int bridge_syslog_option);

// Converts |syslog_option| to a bridge syslog option. Returns 0 if
// |syslog_option| does not contain any supported options.
int ToBridgeSysLogOption(int syslog_option);

// Converts |bridge_syslog_facility| to a runtime syslog facility. Returns 0 if
// |bridge_syslog_facility| does not map to a supported facility.
int FromBridgeSysLogFacility(int bridge_syslog_facility);

// Converts |syslog_facility| to a bridge syslog facility. Returns 0 if
// |syslog_facility| does not map to a supported facility.
int ToBridgeSysLogFacility(int syslog_facility);

// Converts |bridge_syslog_priority| to a runtime syslog priority. Returns 0 if
// |bridge_syslog_priority| does not contain a supported facility or level.
int FromBridgeSysLogPriority(int bridge_syslog_priority);

// Converts |syslog_priority| to a bridge syslog priority. Returns 0 if
// |syslog_priority| does not contain a supported facility or level.
int ToBridgeSysLogPriority(int syslog_priority);

// Converts |bridge_file_flag| to a runtime file flag.
int FromBridgeFileFlags(int bridge_file_flag);

// Converts |file_flag| to a bridge file flag.
int ToBridgeFileFlags(int file_flag);

// Converts |bridge_fd_flag| to a runtime file flag.
int FromBridgeFDFlags(int bridge_fd_flag);

// Converts |fd_flag| to a bridge FD flag.
int ToBridgeFDFlags(int fd_flag);

// Converts |bridge_option_name| to a runtime option name.
int FromBridgeOptionName(int level, int bridge_option_name);

// Converts |option_name| to a bridge option name.
int ToBridgeOptionName(int level, int option_name);

// Converts |bridge_st| to a runtime stat. Returns nullptr if unsuccessful.
struct stat *FromBridgeStat(const struct bridge_stat *bridge_statbuf,
                            struct stat *statbuf);

// Converts |st| to a bridge stat. Returns nullptr if unsuccessful.
struct bridge_stat *ToBridgeStat(const struct stat *statbuf,
                                 struct bridge_stat *bridge_statbuf);

// Copies |bridge_addr| to a runtime sockaddr up to sizeof(struct
// bridge_sockaddr). Returns nullptr if unsuccessful.
struct sockaddr *FromBridgeSockaddr(const struct bridge_sockaddr *bridge_addr,
                                    struct sockaddr *addr);

// Copies |addr| to a bridge sockaddr up to sizeof(struct bridge_sockaddr).
// Returns nullptr if unsuccessful.
struct bridge_sockaddr *ToBridgeSockaddr(const struct sockaddr *addr,
                                         struct bridge_sockaddr *bridge_addr);

// Converts |bridge_tp| to a runtime timespec.
struct timespec *FromBridgeTimespec(const struct bridge_timespec *bridge_tp,
                                    struct timespec *tp);

// Converts |tp| to a bridge timespec.
struct bridge_timespec *ToBridgeTimespec(const struct timespec *tp,
                                         struct bridge_timespec *bridge_tp);

// Converts |bridge_tv| to a runtime timeval.
struct timeval *FromBridgeTimeVal(const struct bridge_timeval *bridge_tv,
                                  struct timeval *tv);

// Converts |tv| to a bridge timeval.
struct bridge_timeval *ToBridgeTimeVal(const struct timeval *tv,
                                       struct bridge_timeval *bridge_tv);

// Converts |fd| to a bridge pollfd. Returns nullptr if unsuccessful.
struct pollfd *FromBridgePollfd(const struct bridge_pollfd *bridge_fd,
                                struct pollfd *fd);

// Converts |bridge_fd| to a runtime pollfd. Returns nullptr if unsuccessful.
struct bridge_pollfd *ToBridgePollfd(const struct pollfd *fd,
                                     struct bridge_pollfd *bridge_fd);

// Converts |bridge_msg| to a runtime msghdr. This only does a shallow copy of
// the pointers. A deep copy of the |iovec| array is done in a helper class
// |BridgeMsghdrWrapper| in host_calls. Returns nullptr if unsuccessful.
struct msghdr *FromBridgeMsgHdr(const struct bridge_msghdr *bridge_msg,
                                struct msghdr *msg);

// Converts |msg| to a bridge msghdr. This only does a shallow copy of the
// pointers. A deep copy of the |iovec| array is done in a helper class
// |BridgeMsghdrWrapper| in host_calls. Returns nullptr if unsuccessful.
struct bridge_msghdr *ToBridgeMsgHdr(const struct msghdr *msg,
                                     struct bridge_msghdr *bridge_msg);

// Copies all the iovec buffers from |bridge_msg| to |msg|. This conversion does
// not allocate memory, just copies data to already allocated memory. Returns
// nullptr if unsuccessful.
struct msghdr *FromBridgeIovecArray(const struct bridge_msghdr *bridge_msg,
                                    struct msghdr *msg);

// Copies all the iovec buffers from |msg| to |bridge_msg|. This conversion does
// not allocate memory, just copies data to already allocated memory. Returns
// nullptr is unsuccessful.
struct bridge_msghdr *ToBridgeIovecArray(const struct msghdr *msg,
                                         struct bridge_msghdr *bridge_msg);

// Converts |bridge_iov| to a runtime iovec. Returns nullptr if unsuccessful.
struct iovec *FromBridgeIovec(const struct bridge_iovec *bridge_iov,
                              struct iovec *iov);

// Converts |iov| to a bridge iovec. Returns nullptr if unsuccessful.
struct bridge_iovec *ToBridgeIovec(const struct iovec *iov,
                                   struct bridge_iovec *bridge_iov);

// Converts |host_wstatus| to a runtime wstatus.
// This only works when converting into an enclave runtime wstatus, not on host.
int FromBridgeWStatus(struct BridgeWStatus bridge_wstatus);

// Converts |wstatus| to a bridge wstatus.
struct BridgeWStatus ToBridgeWStatus(int wstatus);

// Converts |bridge_rusage| to a runtime rusage. Returns nullptr if
// unsuccessful.
struct rusage *FromBridgeRUsage(const struct BridgeRUsage *bridge_rusage,
                                struct rusage *rusage);

// Converts |rusage| to a bridge rusage. Returns nullptr if unsuccessful.
struct BridgeRUsage *ToBridgeRUsage(const struct rusage *rusage,
                                    struct BridgeRUsage *bridge_rusage);

// These functions follow the standard for the analogous functions in
// http://man7.org/linux/man-pages/man3/CPU_SET.3.html.

void BridgeCpuSetZero(struct BridgeCpuSet *set);

void BridgeCpuSetAddBit(int cpu, struct BridgeCpuSet *set);

int BridgeCpuSetCheckBit(int cpu, struct BridgeCpuSet *set);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // ASYLO_PLATFORM_COMMON_BRIDGE_TYPES_H_
