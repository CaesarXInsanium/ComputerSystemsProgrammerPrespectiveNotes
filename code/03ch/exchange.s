	.file	"exchange.c"
	.text
.Ltext0:
	.file 0 "/home/cxi/.CODE/RootProjects/Books/ComputerSystems" "code/03ch/exchange.c"
	.globl	exchange
	.type	exchange, @function
exchange:
.LVL0:
.LFB0:
	.file 1 "code/03ch/exchange.c"
	.loc 1 1 32 view -0
	.cfi_startproc
	.loc 1 2 3 view .LVU1
	.loc 1 2 8 is_stmt 0 view .LVU2
	movq	(%rdi), %rax
.LVL1:
	.loc 1 3 3 is_stmt 1 view .LVU3
	.loc 1 3 7 is_stmt 0 view .LVU4
	movq	%rsi, (%rdi)
	.loc 1 4 3 is_stmt 1 view .LVU5
	.loc 1 5 1 is_stmt 0 view .LVU6
	ret
	.cfi_endproc
.LFE0:
	.size	exchange, .-exchange
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x82
	.value	0x5
	.byte	0x1
	.byte	0x8
	.long	.Ldebug_abbrev0
	.uleb128 0x2
	.long	.LASF2
	.byte	0x1d
	.long	.LASF0
	.long	.LASF1
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x3
	.long	.LASF3
	.byte	0x1
	.byte	0x1
	.byte	0x6
	.long	0x78
	.quad	.LFB0
	.quad	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.long	0x78
	.uleb128 0x1
	.string	"xp"
	.byte	0x15
	.long	0x7f
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x1
	.string	"y"
	.byte	0x1e
	.long	0x78
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x4
	.string	"x"
	.byte	0x1
	.byte	0x2
	.byte	0x8
	.long	0x78
	.long	.LLST0
	.long	.LVUS0
	.byte	0
	.uleb128 0x5
	.byte	0x8
	.byte	0x5
	.long	.LASF4
	.uleb128 0x6
	.byte	0x8
	.long	0x78
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x1f
	.uleb128 0x1b
	.uleb128 0x1f
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.uleb128 0x2137
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loclists,"",@progbits
	.long	.Ldebug_loc3-.Ldebug_loc2
.Ldebug_loc2:
	.value	0x5
	.byte	0x8
	.byte	0
	.long	0
.Ldebug_loc0:
.LVUS0:
	.uleb128 .LVU3
	.uleb128 0
.LLST0:
	.byte	0x4
	.uleb128 .LVL1-.Ltext0
	.uleb128 .LFE0-.Ltext0
	.uleb128 0x1
	.byte	0x50
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF3:
	.string	"exchange"
.LASF4:
	.string	"long int"
.LASF2:
	.string	"GNU C17 12.2.1 20230201 -mtune=generic -march=x86-64 -g -O"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/home/cxi/.CODE/RootProjects/Books/ComputerSystems"
.LASF0:
	.string	"code/03ch/exchange.c"
	.ident	"GCC: (GNU) 12.2.1 20230201"
	.section	.note.GNU-stack,"",@progbits
