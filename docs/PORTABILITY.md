# Portability evidence boundary

## Source contract

The decoder/library uses C99, `<stdint.h>`, `<stddef.h>`, and byte-wise decoding. It has no Linux syscalls, `/proc`, `epoll`, pthread, compiler packing attributes, host-endian casts, dynamic allocation, or shell execution.

The CLI uses only ISO C file/memory functions. On OpenBSD it additionally calls `pledge("stdio rpath", NULL)` before reading the bundle and `pledge("stdio", NULL)` after the read.

## Verification labels

- **host runtime**: compiled and executed on the recorded host.
- **OpenBSD live VM**: compiled and executed after `uname -a` inside the pinned GitHub-hosted `vmactions/openbsd-vm` guest. The Actions log is the receipt.
- **OpenBSD compile/static only**: compilation or analysis using an OpenBSD target/sysroot without execution.
- **MBSD/OpenWrt unknown**: no claim until the actual OpenWrt 23.05.4 MT7981 toolchain builds and, separately, the hardware/runtime path executes.

GitHub's OpenBSD workflow pins `actions/checkout` and `vmactions/openbsd-vm` by full commit SHA and grants only `contents: read`.
