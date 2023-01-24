/* Entry Point */
ENTRY(Reset_Handler)

MEMORY
{
    FLASH(RX) : ORIGIN = 0x08000000, LENGTH = 0x0807FFFF - 0x08000000 /* 512 KB */
    SRAM(RWX) : ORIGIN = 0x20000000, LENGTH = 0x2001FFFF - 0x20000000 /* 128 KB */
}

SECTIONS
{
    /* The program code and other data into "FLASH" Rom type memory */
    .text :
    {
        KEEP (*(.isr_vector)) /* interrupt vector table */
        *(.text)
        *(.text.*)
        KEEP (*(.init))
        KEEP (*(.fini))
        *(.rodata)
        *(.rodata.*)
        . = ALIGN(4);
        _etext = .; /* define a global symbol at text end */
    } > FLASH

    _la_data = LOADADDR(.data); /* used by the startup to initialize data */

    /* Initialized data sections into "SRAM" Ram type memory */
    .data :
    {
        _sdata = .; /* define a global symbol at data start */
        *(.data)
        *(.data.*)
        . = ALIGN(4);
        _edata = .; /* define a global symbol at data end */
    } > SRAM AT> FLASH

    /* Uninitialized data section into "SRAM" Ram type memory */
    .bss :
    {
        _sbss = .; /* define a global symbol at bss start */
        __bss_start__ = _sbss;
        *(.bss)
        *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .; /* define a global symbol at bss end */
        __bss_end__ = _ebss;
        . = ALIGN(4);
        end = .;
        __end__ = .;
    } > SRAM
}
