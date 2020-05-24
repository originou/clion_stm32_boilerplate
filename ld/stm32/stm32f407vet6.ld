__estack = 0x20020000;

MEMORY
{
  rom (rx) : ORIGIN = 0x08000000, LENGTH = 512K
  ram (xrw)  : ORIGIN = 0x20000000, LENGTH = 128K
}

INCLUDE cortex-m-generic.ld
