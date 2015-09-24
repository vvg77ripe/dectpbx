VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL DATA
        SIGNAL E
        SIGNAL XLXN_5(7:0)
        SIGNAL CLK
        SIGNAL XLXN_24(7:0)
        SIGNAL XLXN_25(7:0)
        SIGNAL XLXN_26(7:0)
        SIGNAL XLXN_27(7:0)
        SIGNAL XLXN_28(7:0)
        SIGNAL XLXN_29(7:0)
        SIGNAL XLXN_30(7:0)
        SIGNAL XLXN_31(7:0)
        SIGNAL XLXN_32(7:0)
        SIGNAL XLXN_42(7:0)
        SIGNAL XLXN_43(7:0)
        SIGNAL LEV1
        SIGNAL LEV0
        SIGNAL DO(7:0)
        SIGNAL DO(7)
        SIGNAL Q(7:0)
        SIGNAL Q(7)
        SIGNAL Q(6)
        SIGNAL Q(5)
        SIGNAL Q(4)
        SIGNAL Q(3)
        SIGNAL Q(2)
        SIGNAL Q(1)
        SIGNAL Q(0)
        SIGNAL DO(6)
        SIGNAL DO(5)
        SIGNAL DO(4)
        SIGNAL DO(3)
        SIGNAL DO(2)
        SIGNAL DO(1)
        PORT Input DATA
        PORT Input E
        PORT Input CLK
        PORT Output Q(7:0)
        BEGIN BLOCKDEF firtap
            TIMESTAMP 2006 1 6 20 11 47
            RECTANGLE N 64 -768 320 0 
            LINE N 64 -736 0 -736 
            LINE N 64 -672 0 -672 
            LINE N 64 -608 0 -608 
            RECTANGLE N 0 -620 64 -596 
            LINE N 64 -544 0 -544 
            LINE N 64 -480 0 -480 
            LINE N 64 -416 0 -416 
            LINE N 64 -352 0 -352 
            LINE N 64 -288 0 -288 
            LINE N 64 -224 0 -224 
            LINE N 64 -160 0 -160 
            LINE N 64 -96 0 -96 
            LINE N 64 -32 0 -32 
            LINE N 320 -736 384 -736 
            RECTANGLE N 320 -748 384 -724 
        END BLOCKDEF
        BEGIN BLOCKDEF busgnd
            TIMESTAMP 2005 12 27 21 45 38
            RECTANGLE N 64 -64 192 0 
            RECTANGLE N 0 -44 64 -20 
            LINE N 64 -32 0 -32 
        END BLOCKDEF
        BEGIN BLOCKDEF gnd
            TIMESTAMP 2001 2 2 12 37 29
            LINE N 64 -64 64 -96 
            LINE N 76 -48 52 -48 
            LINE N 68 -32 60 -32 
            LINE N 88 -64 40 -64 
            LINE N 64 -64 64 -80 
            LINE N 64 -128 64 -96 
        END BLOCKDEF
        BEGIN BLOCKDEF vcc
            TIMESTAMP 2001 2 2 12 37 29
            LINE N 64 -32 64 -64 
            LINE N 64 0 64 -32 
            LINE N 96 -64 32 -64 
        END BLOCKDEF
        BEGIN BLOCKDEF buf
            TIMESTAMP 2001 2 2 12 35 54
            LINE N 0 -32 64 -32 
            LINE N 224 -32 128 -32 
            LINE N 64 0 128 -32 
            LINE N 128 -32 64 -64 
            LINE N 64 -64 64 0 
        END BLOCKDEF
        BEGIN BLOCK XLXI_1 firtap
            PIN DATA DATA
            PIN E E
            PIN DI(7:0) XLXN_43(7:0)
            PIN C0 LEV1
            PIN C1 LEV0
            PIN C2 LEV0
            PIN C3 LEV0
            PIN C4 LEV0
            PIN C5 LEV0
            PIN C6 LEV0
            PIN C7 LEV0
            PIN CLK CLK
            PIN DO(7:0) XLXN_5(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_2 firtap
            PIN DATA DATA
            PIN E E
            PIN DI(7:0) XLXN_5(7:0)
            PIN C0 LEV0
            PIN C1 LEV1
            PIN C2 LEV0
            PIN C3 LEV0
            PIN C4 LEV0
            PIN C5 LEV0
            PIN C6 LEV0
            PIN C7 LEV0
            PIN CLK CLK
            PIN DO(7:0) XLXN_31(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_3 firtap
            PIN DATA DATA
            PIN E E
            PIN DI(7:0) XLXN_31(7:0)
            PIN C0 LEV1
            PIN C1 LEV0
            PIN C2 LEV1
            PIN C3 LEV0
            PIN C4 LEV0
            PIN C5 LEV0
            PIN C6 LEV0
            PIN C7 LEV0
            PIN CLK CLK
            PIN DO(7:0) XLXN_30(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_4 firtap
            PIN DATA DATA
            PIN E E
            PIN DI(7:0) XLXN_30(7:0)
            PIN C0 LEV1
            PIN C1 LEV0
            PIN C2 LEV0
            PIN C3 LEV1
            PIN C4 LEV0
            PIN C5 LEV0
            PIN C6 LEV0
            PIN C7 LEV0
            PIN CLK CLK
            PIN DO(7:0) XLXN_29(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_5 firtap
            PIN DATA DATA
            PIN E E
            PIN DI(7:0) XLXN_29(7:0)
            PIN C0 LEV0
            PIN C1 LEV1
            PIN C2 LEV1
            PIN C3 LEV1
            PIN C4 LEV0
            PIN C5 LEV0
            PIN C6 LEV0
            PIN C7 LEV0
            PIN CLK CLK
            PIN DO(7:0) XLXN_28(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_6 firtap
            PIN DATA DATA
            PIN E E
            PIN DI(7:0) XLXN_28(7:0)
            PIN C0 LEV1
            PIN C1 LEV1
            PIN C2 LEV0
            PIN C3 LEV0
            PIN C4 LEV1
            PIN C5 LEV0
            PIN C6 LEV0
            PIN C7 LEV0
            PIN CLK CLK
            PIN DO(7:0) XLXN_42(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_7 firtap
            PIN DATA DATA
            PIN E E
            PIN DI(7:0) XLXN_42(7:0)
            PIN C0 LEV0
            PIN C1 LEV0
            PIN C2 LEV1
            PIN C3 LEV0
            PIN C4 LEV1
            PIN C5 LEV0
            PIN C6 LEV0
            PIN C7 LEV0
            PIN CLK CLK
            PIN DO(7:0) XLXN_24(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_8 firtap
            PIN DATA DATA
            PIN E E
            PIN DI(7:0) XLXN_24(7:0)
            PIN C0 LEV1
            PIN C1 LEV1
            PIN C2 LEV0
            PIN C3 LEV0
            PIN C4 LEV1
            PIN C5 LEV0
            PIN C6 LEV0
            PIN C7 LEV0
            PIN CLK CLK
            PIN DO(7:0) XLXN_25(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_9 firtap
            PIN DATA DATA
            PIN E E
            PIN DI(7:0) XLXN_25(7:0)
            PIN C0 LEV0
            PIN C1 LEV1
            PIN C2 LEV1
            PIN C3 LEV1
            PIN C4 LEV0
            PIN C5 LEV0
            PIN C6 LEV0
            PIN C7 LEV0
            PIN CLK CLK
            PIN DO(7:0) XLXN_26(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_10 firtap
            PIN DATA DATA
            PIN E E
            PIN DI(7:0) XLXN_26(7:0)
            PIN C0 LEV1
            PIN C1 LEV0
            PIN C2 LEV0
            PIN C3 LEV1
            PIN C4 LEV0
            PIN C5 LEV0
            PIN C6 LEV0
            PIN C7 LEV0
            PIN CLK CLK
            PIN DO(7:0) XLXN_27(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_11 firtap
            PIN DATA DATA
            PIN E E
            PIN DI(7:0) XLXN_27(7:0)
            PIN C0 LEV1
            PIN C1 LEV0
            PIN C2 LEV1
            PIN C3 LEV0
            PIN C4 LEV0
            PIN C5 LEV0
            PIN C6 LEV0
            PIN C7 LEV0
            PIN CLK CLK
            PIN DO(7:0) XLXN_32(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_12 firtap
            PIN DATA DATA
            PIN E E
            PIN DI(7:0) XLXN_32(7:0)
            PIN C0 LEV0
            PIN C1 LEV1
            PIN C2 LEV0
            PIN C3 LEV0
            PIN C4 LEV0
            PIN C5 LEV0
            PIN C6 LEV0
            PIN C7 LEV0
            PIN CLK CLK
            PIN DO(7:0) DO(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_13 busgnd
            PIN GBUS(7:0) XLXN_43(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_29 gnd
            PIN G LEV0
        END BLOCK
        BEGIN BLOCK XLXI_30 vcc
            PIN P LEV1
        END BLOCK
        BEGIN BLOCK XLXI_31 buf
            PIN I DO(7)
            PIN O Q(6)
        END BLOCK
        BEGIN BLOCK XLXI_32 buf
            PIN I DO(6)
            PIN O Q(5)
        END BLOCK
        BEGIN BLOCK XLXI_33 buf
            PIN I DO(5)
            PIN O Q(4)
        END BLOCK
        BEGIN BLOCK XLXI_34 buf
            PIN I DO(4)
            PIN O Q(3)
        END BLOCK
        BEGIN BLOCK XLXI_35 buf
            PIN I DO(3)
            PIN O Q(2)
        END BLOCK
        BEGIN BLOCK XLXI_36 buf
            PIN I DO(2)
            PIN O Q(1)
        END BLOCK
        BEGIN BLOCK XLXI_37 buf
            PIN I DO(1)
            PIN O Q(0)
        END BLOCK
        BEGIN BLOCK XLXI_38 buf
            PIN I DO(7)
            PIN O Q(7)
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 5440 3520
        BEGIN BRANCH DATA
            WIRE 320 480 688 480
            WIRE 688 480 688 672
            WIRE 688 672 736 672
            WIRE 688 672 688 2000
            WIRE 688 2000 1344 2000
            WIRE 1344 2000 1344 2112
            WIRE 1344 2112 1376 2112
            WIRE 1344 2000 1984 2000
            WIRE 1984 2000 1984 2112
            WIRE 1984 2112 2016 2112
            WIRE 1984 2000 2624 2000
            WIRE 2624 2000 2624 2112
            WIRE 2624 2112 2656 2112
            WIRE 2624 2000 3264 2000
            WIRE 3264 2000 3904 2000
            WIRE 3904 2000 3904 2112
            WIRE 3904 2112 3936 2112
            WIRE 3904 2000 4544 2000
            WIRE 4544 2000 4544 2112
            WIRE 4544 2112 4576 2112
            WIRE 3264 2000 3264 2112
            WIRE 3264 2112 3296 2112
            WIRE 688 480 1344 480
            WIRE 1344 480 1344 672
            WIRE 1344 672 1376 672
            WIRE 1344 480 1984 480
            WIRE 1984 480 2624 480
            WIRE 2624 480 3264 480
            WIRE 3264 480 3904 480
            WIRE 3904 480 3904 672
            WIRE 3904 672 3936 672
            WIRE 3264 480 3264 672
            WIRE 3264 672 3296 672
            WIRE 2624 480 2624 672
            WIRE 2624 672 2656 672
            WIRE 1984 480 1984 672
            WIRE 1984 672 2016 672
        END BRANCH
        BEGIN BRANCH E
            WIRE 320 400 640 400
            WIRE 640 400 1280 400
            WIRE 1280 400 1280 736
            WIRE 1280 736 1376 736
            WIRE 1280 400 1920 400
            WIRE 1920 400 2560 400
            WIRE 2560 400 3200 400
            WIRE 3200 400 3840 400
            WIRE 3840 400 3840 736
            WIRE 3840 736 3936 736
            WIRE 3200 400 3200 736
            WIRE 3200 736 3296 736
            WIRE 2560 400 2560 736
            WIRE 2560 736 2656 736
            WIRE 1920 400 1920 736
            WIRE 1920 736 2016 736
            WIRE 640 400 640 736
            WIRE 640 736 736 736
            WIRE 640 736 640 1920
            WIRE 640 1920 1280 1920
            WIRE 1280 1920 1280 2176
            WIRE 1280 2176 1376 2176
            WIRE 1280 1920 1920 1920
            WIRE 1920 1920 1920 2176
            WIRE 1920 2176 2016 2176
            WIRE 1920 1920 2560 1920
            WIRE 2560 1920 2560 2176
            WIRE 2560 2176 2656 2176
            WIRE 2560 1920 3200 1920
            WIRE 3200 1920 3840 1920
            WIRE 3840 1920 3840 2176
            WIRE 3840 2176 3936 2176
            WIRE 3840 1920 4480 1920
            WIRE 4480 1920 4480 2176
            WIRE 4480 2176 4576 2176
            WIRE 3200 1920 3200 2176
            WIRE 3200 2176 3296 2176
        END BRANCH
        BEGIN BRANCH XLXN_5(7:0)
            WIRE 1120 672 1248 672
            WIRE 1248 672 1248 800
            WIRE 1248 800 1376 800
        END BRANCH
        BEGIN BRANCH CLK
            WIRE 320 1520 720 1520
            WIRE 720 1520 1360 1520
            WIRE 1360 1520 2000 1520
            WIRE 2000 1520 2640 1520
            WIRE 2640 1520 3280 1520
            WIRE 3280 1520 3920 1520
            WIRE 720 1520 720 2928
            WIRE 720 2928 1360 2928
            WIRE 1360 2928 2000 2928
            WIRE 2000 2928 2640 2928
            WIRE 2640 2928 3280 2928
            WIRE 3280 2928 3920 2928
            WIRE 3920 2928 4560 2928
            WIRE 720 1376 736 1376
            WIRE 720 1376 720 1520
            WIRE 1360 1376 1376 1376
            WIRE 1360 1376 1360 1520
            WIRE 1360 2816 1376 2816
            WIRE 1360 2816 1360 2928
            WIRE 2000 1376 2016 1376
            WIRE 2000 1376 2000 1520
            WIRE 2000 2816 2016 2816
            WIRE 2000 2816 2000 2928
            WIRE 2640 1376 2656 1376
            WIRE 2640 1376 2640 1520
            WIRE 2640 2816 2656 2816
            WIRE 2640 2816 2640 2928
            WIRE 3280 1376 3296 1376
            WIRE 3280 1376 3280 1520
            WIRE 3280 2816 3296 2816
            WIRE 3280 2816 3280 2928
            WIRE 3920 1376 3936 1376
            WIRE 3920 1376 3920 1520
            WIRE 3920 2816 3936 2816
            WIRE 3920 2816 3920 2928
            WIRE 4560 2816 4576 2816
            WIRE 4560 2816 4560 2928
        END BRANCH
        BEGIN BRANCH XLXN_24(7:0)
            WIRE 1760 2112 1888 2112
            WIRE 1888 2112 1888 2240
            WIRE 1888 2240 2016 2240
        END BRANCH
        BEGIN BRANCH XLXN_25(7:0)
            WIRE 2400 2112 2528 2112
            WIRE 2528 2112 2528 2240
            WIRE 2528 2240 2656 2240
        END BRANCH
        BEGIN BRANCH XLXN_26(7:0)
            WIRE 3040 2112 3168 2112
            WIRE 3168 2112 3168 2240
            WIRE 3168 2240 3296 2240
        END BRANCH
        BEGIN BRANCH XLXN_27(7:0)
            WIRE 3680 2112 3808 2112
            WIRE 3808 2112 3808 2240
            WIRE 3808 2240 3936 2240
        END BRANCH
        BEGIN BRANCH XLXN_28(7:0)
            WIRE 3680 672 3808 672
            WIRE 3808 672 3808 800
            WIRE 3808 800 3936 800
        END BRANCH
        BEGIN BRANCH XLXN_29(7:0)
            WIRE 3040 672 3168 672
            WIRE 3168 672 3168 800
            WIRE 3168 800 3296 800
        END BRANCH
        BEGIN BRANCH XLXN_30(7:0)
            WIRE 2400 672 2528 672
            WIRE 2528 672 2528 800
            WIRE 2528 800 2656 800
        END BRANCH
        BEGIN BRANCH XLXN_31(7:0)
            WIRE 1760 672 1888 672
            WIRE 1888 672 1888 800
            WIRE 1888 800 2016 800
        END BRANCH
        BEGIN BRANCH XLXN_32(7:0)
            WIRE 4320 2112 4448 2112
            WIRE 4448 2112 4448 2240
            WIRE 4448 2240 4576 2240
        END BRANCH
        BEGIN BRANCH XLXN_42(7:0)
            WIRE 1248 1856 1248 2240
            WIRE 1248 2240 1376 2240
            WIRE 1248 1856 4400 1856
            WIRE 4320 672 4400 672
            WIRE 4400 672 4400 1856
        END BRANCH
        BEGIN BRANCH XLXN_43(7:0)
            WIRE 512 800 736 800
        END BRANCH
        BEGIN INSTANCE XLXI_1 736 1408 R0
        END INSTANCE
        BEGIN INSTANCE XLXI_2 1376 1408 R0
        END INSTANCE
        BEGIN INSTANCE XLXI_3 2016 1408 R0
        END INSTANCE
        BEGIN INSTANCE XLXI_4 2656 1408 R0
        END INSTANCE
        BEGIN INSTANCE XLXI_5 3296 1408 R0
        END INSTANCE
        BEGIN INSTANCE XLXI_6 3936 1408 R0
        END INSTANCE
        BEGIN INSTANCE XLXI_7 1376 2848 R0
        END INSTANCE
        BEGIN INSTANCE XLXI_8 2016 2848 R0
        END INSTANCE
        BEGIN INSTANCE XLXI_9 2656 2848 R0
        END INSTANCE
        BEGIN INSTANCE XLXI_10 3296 2848 R0
        END INSTANCE
        BEGIN INSTANCE XLXI_11 3936 2848 R0
        END INSTANCE
        BEGIN INSTANCE XLXI_12 4576 2848 R0
        END INSTANCE
        BEGIN INSTANCE XLXI_13 512 768 R180
        END INSTANCE
        IOMARKER 320 1520 CLK R180 28
        INSTANCE XLXI_29 512 3200 R0
        INSTANCE XLXI_30 352 2944 R0
        IOMARKER 320 480 DATA R180 28
        IOMARKER 320 400 E R180 28
        BUSTAP 4480 976 4576 976
        BEGIN BRANCH DO(7:0)
            WIRE 4480 976 4480 1056
            WIRE 4480 1056 4480 1136
            WIRE 4480 1136 4480 1216
            WIRE 4480 1216 4480 1296
            WIRE 4480 1296 4480 1376
            WIRE 4480 1376 4480 1456
            WIRE 4480 1456 4480 1760
            WIRE 4480 1760 5024 1760
            WIRE 5024 1760 5024 2112
            WIRE 4960 2112 5024 2112
        END BRANCH
        INSTANCE XLXI_31 4736 1008 R0
        INSTANCE XLXI_32 4736 1088 R0
        INSTANCE XLXI_33 4736 1168 R0
        INSTANCE XLXI_34 4736 1248 R0
        INSTANCE XLXI_35 4736 1328 R0
        INSTANCE XLXI_36 4736 1408 R0
        INSTANCE XLXI_37 4736 1488 R0
        INSTANCE XLXI_38 4736 928 R0
        BEGIN BRANCH Q(7:0)
            WIRE 5120 800 5200 800
            WIRE 5120 800 5120 896
            WIRE 5120 896 5120 976
            WIRE 5120 976 5120 1056
            WIRE 5120 1056 5120 1136
            WIRE 5120 1136 5120 1216
            WIRE 5120 1216 5120 1296
            WIRE 5120 1296 5120 1376
            WIRE 5120 1376 5120 1456
        END BRANCH
        IOMARKER 5200 800 Q(7:0) R0 28
        BUSTAP 5120 896 5024 896
        BUSTAP 5120 976 5024 976
        BUSTAP 5120 1056 5024 1056
        BUSTAP 5120 1136 5024 1136
        BUSTAP 5120 1216 5024 1216
        BUSTAP 5120 1296 5024 1296
        BUSTAP 5120 1376 5024 1376
        BUSTAP 5120 1456 5024 1456
        BEGIN BRANCH Q(7)
            WIRE 4960 896 5024 896
        END BRANCH
        BEGIN BRANCH Q(6)
            WIRE 4960 976 5024 976
        END BRANCH
        BEGIN BRANCH Q(5)
            WIRE 4960 1056 5024 1056
        END BRANCH
        BEGIN BRANCH Q(4)
            WIRE 4960 1136 5024 1136
        END BRANCH
        BEGIN BRANCH Q(3)
            WIRE 4960 1216 5024 1216
        END BRANCH
        BEGIN BRANCH Q(2)
            WIRE 4960 1296 5024 1296
        END BRANCH
        BEGIN BRANCH Q(1)
            WIRE 4960 1376 5024 1376
        END BRANCH
        BEGIN BRANCH Q(0)
            WIRE 4960 1456 5024 1456
        END BRANCH
        BEGIN BRANCH LEV1
            WIRE 416 2944 416 3008
            WIRE 416 3008 544 3008
            WIRE 544 3008 1296 3008
            WIRE 1296 3008 1936 3008
            WIRE 1936 3008 2576 3008
            WIRE 2576 3008 3216 3008
            WIRE 3216 3008 3856 3008
            WIRE 3856 3008 4496 3008
            WIRE 544 864 736 864
            WIRE 544 864 544 1632
            WIRE 544 1632 1296 1632
            WIRE 1296 1632 1936 1632
            WIRE 1936 1632 2576 1632
            WIRE 2576 1632 3216 1632
            WIRE 3216 1632 3856 1632
            WIRE 544 1632 544 3008
            WIRE 1296 928 1376 928
            WIRE 1296 928 1296 1632
            WIRE 1296 2432 1376 2432
            WIRE 1296 2432 1296 2560
            WIRE 1296 2560 1376 2560
            WIRE 1296 2560 1296 3008
            WIRE 1936 864 2016 864
            WIRE 1936 864 1936 992
            WIRE 1936 992 2016 992
            WIRE 1936 992 1936 1632
            WIRE 1936 2304 2016 2304
            WIRE 1936 2304 1936 2368
            WIRE 1936 2368 2016 2368
            WIRE 1936 2368 1936 2560
            WIRE 1936 2560 2016 2560
            WIRE 1936 2560 1936 3008
            WIRE 2576 864 2656 864
            WIRE 2576 864 2576 1056
            WIRE 2576 1056 2656 1056
            WIRE 2576 1056 2576 1632
            WIRE 2576 2368 2576 2432
            WIRE 2576 2432 2656 2432
            WIRE 2576 2432 2576 2496
            WIRE 2576 2496 2656 2496
            WIRE 2576 2496 2576 3008
            WIRE 2576 2368 2656 2368
            WIRE 3216 928 3296 928
            WIRE 3216 928 3216 992
            WIRE 3216 992 3296 992
            WIRE 3216 992 3216 1056
            WIRE 3216 1056 3296 1056
            WIRE 3216 1056 3216 1632
            WIRE 3216 2304 3296 2304
            WIRE 3216 2304 3216 2496
            WIRE 3216 2496 3296 2496
            WIRE 3216 2496 3216 3008
            WIRE 3856 864 3936 864
            WIRE 3856 864 3856 928
            WIRE 3856 928 3936 928
            WIRE 3856 928 3856 1120
            WIRE 3856 1120 3936 1120
            WIRE 3856 1120 3856 1632
            WIRE 3856 2304 3936 2304
            WIRE 3856 2304 3856 2432
            WIRE 3856 2432 3936 2432
            WIRE 3856 2432 3856 3008
            WIRE 4496 2368 4576 2368
            WIRE 4496 2368 4496 3008
        END BRANCH
        BEGIN BRANCH LEV0
            WIRE 576 928 736 928
            WIRE 576 928 576 992
            WIRE 576 992 736 992
            WIRE 576 992 576 1056
            WIRE 576 1056 736 1056
            WIRE 576 1056 576 1120
            WIRE 576 1120 736 1120
            WIRE 576 1120 576 1184
            WIRE 576 1184 736 1184
            WIRE 576 1184 576 1248
            WIRE 576 1248 736 1248
            WIRE 576 1248 576 1312
            WIRE 576 1312 736 1312
            WIRE 576 1312 576 1600
            WIRE 576 1600 1328 1600
            WIRE 1328 1600 1968 1600
            WIRE 1968 1600 2608 1600
            WIRE 2608 1600 3248 1600
            WIRE 3248 1600 3888 1600
            WIRE 576 1600 576 2976
            WIRE 576 2976 576 3072
            WIRE 576 2976 1328 2976
            WIRE 1328 2976 1968 2976
            WIRE 1968 2976 2608 2976
            WIRE 2608 2976 3248 2976
            WIRE 3248 2976 3888 2976
            WIRE 3888 2976 4528 2976
            WIRE 1328 864 1376 864
            WIRE 1328 864 1328 992
            WIRE 1328 992 1376 992
            WIRE 1328 992 1328 1056
            WIRE 1328 1056 1376 1056
            WIRE 1328 1056 1328 1120
            WIRE 1328 1120 1376 1120
            WIRE 1328 1120 1328 1184
            WIRE 1328 1184 1376 1184
            WIRE 1328 1184 1328 1248
            WIRE 1328 1248 1376 1248
            WIRE 1328 1248 1328 1312
            WIRE 1328 1312 1376 1312
            WIRE 1328 1312 1328 1600
            WIRE 1328 2304 1376 2304
            WIRE 1328 2304 1328 2368
            WIRE 1328 2368 1376 2368
            WIRE 1328 2368 1328 2496
            WIRE 1328 2496 1376 2496
            WIRE 1328 2496 1328 2624
            WIRE 1328 2624 1376 2624
            WIRE 1328 2624 1328 2688
            WIRE 1328 2688 1376 2688
            WIRE 1328 2688 1328 2752
            WIRE 1328 2752 1376 2752
            WIRE 1328 2752 1328 2976
            WIRE 1968 928 2016 928
            WIRE 1968 928 1968 1056
            WIRE 1968 1056 2016 1056
            WIRE 1968 1056 1968 1120
            WIRE 1968 1120 2016 1120
            WIRE 1968 1120 1968 1184
            WIRE 1968 1184 2016 1184
            WIRE 1968 1184 1968 1248
            WIRE 1968 1248 2016 1248
            WIRE 1968 1248 1968 1312
            WIRE 1968 1312 2016 1312
            WIRE 1968 1312 1968 1600
            WIRE 1968 2432 2016 2432
            WIRE 1968 2432 1968 2496
            WIRE 1968 2496 2016 2496
            WIRE 1968 2496 1968 2624
            WIRE 1968 2624 2016 2624
            WIRE 1968 2624 1968 2688
            WIRE 1968 2688 2016 2688
            WIRE 1968 2688 1968 2752
            WIRE 1968 2752 2016 2752
            WIRE 1968 2752 1968 2976
            WIRE 2608 928 2656 928
            WIRE 2608 928 2608 992
            WIRE 2608 992 2656 992
            WIRE 2608 992 2608 1120
            WIRE 2608 1120 2656 1120
            WIRE 2608 1120 2608 1184
            WIRE 2608 1184 2656 1184
            WIRE 2608 1184 2608 1248
            WIRE 2608 1248 2656 1248
            WIRE 2608 1248 2608 1312
            WIRE 2608 1312 2656 1312
            WIRE 2608 1312 2608 1600
            WIRE 2608 2304 2656 2304
            WIRE 2608 2304 2608 2560
            WIRE 2608 2560 2656 2560
            WIRE 2608 2560 2608 2624
            WIRE 2608 2624 2656 2624
            WIRE 2608 2624 2608 2688
            WIRE 2608 2688 2656 2688
            WIRE 2608 2688 2608 2752
            WIRE 2608 2752 2656 2752
            WIRE 2608 2752 2608 2976
            WIRE 3248 864 3296 864
            WIRE 3248 864 3248 1120
            WIRE 3248 1120 3296 1120
            WIRE 3248 1120 3248 1184
            WIRE 3248 1184 3296 1184
            WIRE 3248 1184 3248 1248
            WIRE 3248 1248 3296 1248
            WIRE 3248 1248 3248 1312
            WIRE 3248 1312 3296 1312
            WIRE 3248 1312 3248 1600
            WIRE 3248 2368 3296 2368
            WIRE 3248 2368 3248 2432
            WIRE 3248 2432 3296 2432
            WIRE 3248 2432 3248 2560
            WIRE 3248 2560 3296 2560
            WIRE 3248 2560 3248 2624
            WIRE 3248 2624 3296 2624
            WIRE 3248 2624 3248 2688
            WIRE 3248 2688 3296 2688
            WIRE 3248 2688 3248 2752
            WIRE 3248 2752 3296 2752
            WIRE 3248 2752 3248 2976
            WIRE 3888 992 3936 992
            WIRE 3888 992 3888 1056
            WIRE 3888 1056 3936 1056
            WIRE 3888 1056 3888 1184
            WIRE 3888 1184 3936 1184
            WIRE 3888 1184 3888 1248
            WIRE 3888 1248 3936 1248
            WIRE 3888 1248 3888 1312
            WIRE 3888 1312 3936 1312
            WIRE 3888 1312 3888 1600
            WIRE 3888 2368 3936 2368
            WIRE 3888 2368 3888 2496
            WIRE 3888 2496 3936 2496
            WIRE 3888 2496 3888 2560
            WIRE 3888 2560 3936 2560
            WIRE 3888 2560 3888 2624
            WIRE 3888 2624 3936 2624
            WIRE 3888 2624 3888 2688
            WIRE 3888 2688 3936 2688
            WIRE 3888 2688 3888 2752
            WIRE 3888 2752 3936 2752
            WIRE 3888 2752 3888 2976
            WIRE 4528 2304 4576 2304
            WIRE 4528 2304 4528 2432
            WIRE 4528 2432 4576 2432
            WIRE 4528 2432 4528 2496
            WIRE 4528 2496 4576 2496
            WIRE 4528 2496 4528 2560
            WIRE 4528 2560 4576 2560
            WIRE 4528 2560 4528 2624
            WIRE 4528 2624 4576 2624
            WIRE 4528 2624 4528 2688
            WIRE 4528 2688 4576 2688
            WIRE 4528 2688 4528 2752
            WIRE 4528 2752 4576 2752
            WIRE 4528 2752 4528 2976
        END BRANCH
        BUSTAP 4480 1136 4576 1136
        BUSTAP 4480 1216 4576 1216
        BUSTAP 4480 1296 4576 1296
        BUSTAP 4480 1376 4576 1376
        BUSTAP 4480 1456 4576 1456
        BEGIN BRANCH DO(7)
            WIRE 4576 976 4704 976
            WIRE 4704 976 4736 976
            WIRE 4704 896 4736 896
            WIRE 4704 896 4704 976
        END BRANCH
        BUSTAP 4480 1056 4576 1056
        BEGIN BRANCH DO(6)
            WIRE 4576 1056 4736 1056
        END BRANCH
        BEGIN BRANCH DO(5)
            WIRE 4576 1136 4736 1136
        END BRANCH
        BEGIN BRANCH DO(4)
            WIRE 4576 1216 4736 1216
        END BRANCH
        BEGIN BRANCH DO(3)
            WIRE 4576 1296 4736 1296
        END BRANCH
        BEGIN BRANCH DO(2)
            WIRE 4576 1376 4736 1376
        END BRANCH
        BEGIN BRANCH DO(1)
            WIRE 4576 1456 4736 1456
        END BRANCH
    END SHEET
END SCHEMATIC
