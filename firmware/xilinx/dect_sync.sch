VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL CLK
        SIGNAL XLXN_3
        SIGNAL BITCLK
        SIGNAL BIT0
        SIGNAL BIT1
        SIGNAL BIT2
        SIGNAL XLXN_10
        SIGNAL XLXN_16
        SIGNAL PA(7:0)
        SIGNAL FS(7:0)
        SIGNAL XLXN_35
        SIGNAL FS(7)
        SIGNAL FS(6)
        SIGNAL FS(5)
        SIGNAL FS(4)
        SIGNAL FS(3)
        SIGNAL FS(2)
        SIGNAL FS(1)
        SIGNAL FS(0)
        SIGNAL FA(7:0)
        SIGNAL SS(7:0)
        SIGNAL SS(0)
        SIGNAL SS(1)
        SIGNAL SS(2)
        SIGNAL SS(3)
        SIGNAL SS(4)
        SIGNAL SS(5)
        SIGNAL SS(6)
        SIGNAL SS(7)
        SIGNAL XLXN_57
        SIGNAL XLXN_58
        SIGNAL XLXN_73(7:0)
        SIGNAL SL(0)
        SIGNAL SL(1)
        SIGNAL SL(2)
        SIGNAL SL(3)
        SIGNAL ASL0
        SIGNAL ASL1
        SIGNAL ASL2
        SIGNAL ASL3
        SIGNAL ADDR(10:0)
        SIGNAL ADDR(10)
        SIGNAL ADDR(9)
        SIGNAL ADDR(8)
        SIGNAL ADDR(7)
        SIGNAL ADDR(6)
        SIGNAL ADDR(5)
        SIGNAL ADDR(4)
        SIGNAL ADDR(3)
        SIGNAL ADDR(2)
        SIGNAL ADDR(1)
        SIGNAL ADDR(0)
        SIGNAL SL(4)
        SIGNAL ASL4
        SIGNAL PA(2)
        SIGNAL PA(3)
        SIGNAL PA(4)
        SIGNAL PA(5)
        SIGNAL XLXN_118
        SIGNAL XLXN_119
        SIGNAL PA(0)
        SIGNAL PA(1)
        SIGNAL CFG
        SIGNAL BCLK
        SIGNAL SFLD
        SIGNAL XLXN_120
        SIGNAL XLXN_121
        SIGNAL XLXN_122
        SIGNAL XLXN_123
        SIGNAL XLXN_124
        SIGNAL SL(7:0)
        SIGNAL SL0
        SIGNAL SL1
        SIGNAL SL2
        SIGNAL SL3
        SIGNAL SL4
        SIGNAL XLXN_137
        SIGNAL XLXN_138
        SIGNAL XLXN_139
        SIGNAL XLXN_140
        PORT Input CLK
        PORT Output BIT0
        PORT Output BIT1
        PORT Output BIT2
        PORT Output ADDR(10:0)
        PORT Output CFG
        PORT Output BCLK
        PORT Output SFLD
        PORT Output SL0
        PORT Output SL1
        PORT Output SL2
        PORT Output SL3
        PORT Output SL4
        BEGIN BLOCKDEF cb4re
            TIMESTAMP 2001 2 2 12 36 39
            LINE N 384 -192 320 -192 
            LINE N 0 -32 64 -32 
            LINE N 0 -128 64 -128 
            LINE N 384 -256 320 -256 
            LINE N 384 -320 320 -320 
            LINE N 384 -384 320 -384 
            LINE N 384 -448 320 -448 
            LINE N 80 -128 64 -144 
            LINE N 64 -112 80 -128 
            LINE N 384 -128 320 -128 
            LINE N 192 -32 64 -32 
            LINE N 192 -64 192 -32 
            LINE N 0 -192 64 -192 
            RECTANGLE N 64 -512 320 -64 
        END BLOCKDEF
        BEGIN BLOCKDEF vcc
            TIMESTAMP 2001 2 2 12 37 29
            LINE N 64 -32 64 -64 
            LINE N 64 0 64 -32 
            LINE N 96 -64 32 -64 
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
        BEGIN BLOCKDEF and4
            TIMESTAMP 2001 2 2 12 38 38
            LINE N 144 -112 64 -112 
            ARC N 96 -208 192 -112 144 -112 144 -208 
            LINE N 64 -208 144 -208 
            LINE N 64 -64 64 -256 
            LINE N 256 -160 192 -160 
            LINE N 0 -256 64 -256 
            LINE N 0 -192 64 -192 
            LINE N 0 -128 64 -128 
            LINE N 0 -64 64 -64 
        END BLOCKDEF
        BEGIN BLOCKDEF cb8re
            TIMESTAMP 2001 2 2 12 36 39
            LINE N 384 -192 320 -192 
            LINE N 0 -192 64 -192 
            LINE N 192 -32 64 -32 
            LINE N 192 -64 192 -32 
            LINE N 0 -32 64 -32 
            LINE N 80 -128 64 -144 
            LINE N 64 -112 80 -128 
            LINE N 0 -128 64 -128 
            LINE N 384 -256 320 -256 
            RECTANGLE N 320 -268 384 -244 
            LINE N 384 -128 320 -128 
            RECTANGLE N 64 -320 320 -64 
        END BLOCKDEF
        BEGIN BLOCKDEF comp8
            TIMESTAMP 2001 2 2 12 36 26
            RECTANGLE N 64 -384 320 -64 
            LINE N 384 -224 320 -224 
            RECTANGLE N 0 -332 64 -308 
            LINE N 0 -320 64 -320 
            RECTANGLE N 0 -140 64 -116 
            LINE N 0 -128 64 -128 
        END BLOCKDEF
        BEGIN BLOCKDEF and2
            TIMESTAMP 2001 2 2 12 38 38
            LINE N 0 -64 64 -64 
            LINE N 0 -128 64 -128 
            LINE N 256 -96 192 -96 
            ARC N 96 -144 192 -48 144 -48 144 -144 
            LINE N 144 -48 64 -48 
            LINE N 64 -144 144 -144 
            LINE N 64 -48 64 -144 
        END BLOCKDEF
        BEGIN BLOCKDEF buf
            TIMESTAMP 2001 2 2 12 35 54
            LINE N 0 -32 64 -32 
            LINE N 224 -32 128 -32 
            LINE N 64 0 128 -32 
            LINE N 128 -32 64 -64 
            LINE N 64 -64 64 0 
        END BLOCKDEF
        BEGIN BLOCKDEF add8
            TIMESTAMP 2001 2 2 12 35 41
            LINE N 336 -128 336 -148 
            LINE N 384 -128 336 -128 
            LINE N 64 -288 64 -432 
            LINE N 128 -256 64 -288 
            LINE N 64 -224 128 -256 
            LINE N 64 -80 64 -224 
            LINE N 384 -160 64 -80 
            LINE N 384 -336 384 -160 
            LINE N 384 -352 384 -336 
            LINE N 64 -432 384 -352 
            LINE N 128 -448 64 -448 
            LINE N 128 -416 128 -448 
            LINE N 0 -448 64 -448 
            RECTANGLE N 384 -268 448 -244 
            LINE N 448 -256 384 -256 
            LINE N 0 -192 64 -192 
            LINE N 0 -320 64 -320 
            RECTANGLE N 0 -332 64 -308 
            RECTANGLE N 0 -204 64 -180 
            LINE N 240 -64 384 -64 
            LINE N 240 -124 240 -64 
            LINE N 448 -64 384 -64 
            LINE N 448 -128 384 -128 
        END BLOCKDEF
        BEGIN BLOCKDEF busgnd
            TIMESTAMP 2005 12 27 21 45 38
            RECTANGLE N 64 -64 192 0 
            RECTANGLE N 0 -44 64 -20 
            LINE N 64 -32 0 -32 
        END BLOCKDEF
        BEGIN BLOCKDEF add4
            TIMESTAMP 2001 2 2 12 35 41
            LINE N 112 -832 112 -804 
            LINE N 64 -832 112 -832 
            LINE N 0 -832 64 -832 
            LINE N 0 -192 64 -192 
            LINE N 448 -352 384 -352 
            LINE N 448 -416 384 -416 
            LINE N 448 -480 384 -480 
            LINE N 448 -544 384 -544 
            LINE N 0 -256 64 -256 
            LINE N 0 -320 64 -320 
            LINE N 0 -384 64 -384 
            LINE N 0 -512 64 -512 
            LINE N 0 -576 64 -576 
            LINE N 0 -640 64 -640 
            LINE N 0 -704 64 -704 
            LINE N 240 -64 384 -64 
            LINE N 240 -124 240 -64 
            LINE N 336 -128 336 -148 
            LINE N 384 -128 336 -128 
            LINE N 384 -736 64 -816 
            LINE N 384 -160 384 -736 
            LINE N 64 -80 384 -160 
            LINE N 64 -416 64 -80 
            LINE N 144 -448 64 -416 
            LINE N 64 -480 144 -448 
            LINE N 64 -816 64 -480 
            LINE N 448 -64 384 -64 
            LINE N 448 -128 384 -128 
        END BLOCKDEF
        BEGIN BLOCKDEF and4b1
            TIMESTAMP 2001 2 2 12 38 38
            LINE N 0 -64 40 -64 
            CIRCLE N 40 -76 64 -52 
            LINE N 0 -128 64 -128 
            LINE N 0 -192 64 -192 
            LINE N 0 -256 64 -256 
            LINE N 256 -160 192 -160 
            LINE N 64 -64 64 -256 
            LINE N 144 -112 64 -112 
            ARC N 96 -208 192 -112 144 -112 144 -208 
            LINE N 64 -208 144 -208 
        END BLOCKDEF
        BEGIN BLOCKDEF nor4
            TIMESTAMP 2001 2 2 12 38 38
            LINE N 0 -64 48 -64 
            LINE N 0 -128 64 -128 
            LINE N 0 -192 64 -192 
            LINE N 0 -256 48 -256 
            LINE N 256 -160 216 -160 
            CIRCLE N 192 -172 216 -148 
            LINE N 112 -208 48 -208 
            ARC N 28 -208 204 -32 192 -160 112 -208 
            LINE N 112 -112 48 -112 
            LINE N 48 -256 48 -208 
            LINE N 48 -64 48 -112 
            ARC N -40 -216 72 -104 48 -112 48 -208 
            ARC N 28 -288 204 -112 112 -112 192 -160 
        END BLOCKDEF
        BEGIN BLOCKDEF mod24
            TIMESTAMP 2006 1 9 6 59 20
            RECTANGLE N 64 -320 320 0 
            LINE N 64 -288 0 -288 
            LINE N 64 -224 0 -224 
            LINE N 64 -160 0 -160 
            LINE N 64 -96 0 -96 
            LINE N 64 -32 0 -32 
            LINE N 320 -288 384 -288 
            LINE N 320 -224 384 -224 
            LINE N 320 -160 384 -160 
            LINE N 320 -96 384 -96 
            LINE N 320 -32 384 -32 
        END BLOCKDEF
        BEGIN BLOCKDEF fd4ce
            TIMESTAMP 2001 2 2 12 37 14
            LINE N 384 -448 320 -448 
            LINE N 384 -384 320 -384 
            LINE N 0 -384 64 -384 
            LINE N 0 -448 64 -448 
            LINE N 0 -320 64 -320 
            LINE N 0 -256 64 -256 
            LINE N 384 -256 320 -256 
            LINE N 384 -320 320 -320 
            RECTANGLE N 64 -512 320 -64 
            LINE N 0 -192 64 -192 
            LINE N 0 -32 64 -32 
            LINE N 192 -32 64 -32 
            LINE N 192 -64 192 -32 
            LINE N 80 -128 64 -144 
            LINE N 64 -112 80 -128 
            LINE N 0 -128 64 -128 
        END BLOCKDEF
        BEGIN BLOCKDEF fdce
            TIMESTAMP 2001 2 2 12 37 14
            LINE N 0 -128 64 -128 
            LINE N 0 -192 64 -192 
            LINE N 0 -32 64 -32 
            LINE N 0 -256 64 -256 
            LINE N 384 -256 320 -256 
            LINE N 64 -112 80 -128 
            LINE N 80 -128 64 -144 
            LINE N 192 -64 192 -32 
            LINE N 192 -32 64 -32 
            RECTANGLE N 64 -320 320 -64 
        END BLOCKDEF
        BEGIN BLOCKDEF inv
            TIMESTAMP 2001 2 2 12 38 38
            LINE N 0 -32 64 -32 
            LINE N 224 -32 160 -32 
            LINE N 64 -64 128 -32 
            LINE N 128 -32 64 0 
            LINE N 64 0 64 -64 
            CIRCLE N 128 -48 160 -16 
        END BLOCKDEF
        BEGIN BLOCK XLXI_1 cb4re
            PIN C CLK
            PIN CE XLXN_3
            PIN R BITCLK
            PIN CEO
            PIN Q0
            PIN Q1
            PIN Q2 BCLK
            PIN Q3 BITCLK
            PIN TC
        END BLOCK
        BEGIN BLOCK XLXI_2 vcc
            PIN P XLXN_3
        END BLOCK
        BEGIN BLOCK XLXI_3 cb4re
            PIN C CLK
            PIN CE BITCLK
            PIN R XLXN_10
            PIN CEO
            PIN Q0 BIT0
            PIN Q1 BIT1
            PIN Q2 BIT2
            PIN Q3
            PIN TC
        END BLOCK
        BEGIN BLOCK XLXI_4 gnd
            PIN G XLXN_10
        END BLOCK
        BEGIN BLOCK XLXI_5 and4
            PIN I0 BITCLK
            PIN I1 BIT0
            PIN I2 BIT1
            PIN I3 BIT2
            PIN O XLXN_16
        END BLOCK
        BEGIN BLOCK XLXI_6 cb8re
            PIN C CLK
            PIN CE XLXN_16
            PIN R XLXN_140
            PIN CEO
            PIN Q(7:0) PA(7:0)
            PIN TC
        END BLOCK
        BEGIN BLOCK XLXI_7 comp8
            PIN A(7:0) PA(7:0)
            PIN B(7:0) FS(7:0)
            PIN EQ XLXN_35
        END BLOCK
        BEGIN BLOCK XLXI_15 and2
            PIN I0 XLXN_35
            PIN I1 XLXN_16
            PIN O XLXN_140
        END BLOCK
        BEGIN BLOCK XLXI_16 gnd
            PIN G FS(7)
        END BLOCK
        BEGIN BLOCK XLXI_17 gnd
            PIN G FS(6)
        END BLOCK
        BEGIN BLOCK XLXI_18 gnd
            PIN G FS(2)
        END BLOCK
        BEGIN BLOCK XLXI_19 vcc
            PIN P FS(5)
        END BLOCK
        BEGIN BLOCK XLXI_20 vcc
            PIN P FS(4)
        END BLOCK
        BEGIN BLOCK XLXI_21 vcc
            PIN P FS(3)
        END BLOCK
        BEGIN BLOCK XLXI_22 vcc
            PIN P FS(1)
        END BLOCK
        BEGIN BLOCK XLXI_23 vcc
            PIN P FS(0)
        END BLOCK
        BEGIN BLOCK XLXI_24 cb8re
            PIN C CLK
            PIN CE XLXN_140
            PIN R XLXN_58
            PIN CEO
            PIN Q(7:0) FA(7:0)
            PIN TC
        END BLOCK
        BEGIN BLOCK XLXI_25 comp8
            PIN A(7:0) FA(7:0)
            PIN B(7:0) SS(7:0)
            PIN EQ XLXN_57
        END BLOCK
        BEGIN BLOCK XLXI_26 vcc
            PIN P SS(0)
        END BLOCK
        BEGIN BLOCK XLXI_27 vcc
            PIN P SS(1)
        END BLOCK
        BEGIN BLOCK XLXI_28 vcc
            PIN P SS(2)
        END BLOCK
        BEGIN BLOCK XLXI_29 vcc
            PIN P SS(4)
        END BLOCK
        BEGIN BLOCK XLXI_30 gnd
            PIN G SS(3)
        END BLOCK
        BEGIN BLOCK XLXI_31 gnd
            PIN G SS(5)
        END BLOCK
        BEGIN BLOCK XLXI_32 gnd
            PIN G SS(6)
        END BLOCK
        BEGIN BLOCK XLXI_33 gnd
            PIN G SS(7)
        END BLOCK
        BEGIN BLOCK XLXI_34 and2
            PIN I0 XLXN_57
            PIN I1 XLXN_140
            PIN O XLXN_58
        END BLOCK
        BEGIN BLOCK XLXI_52 add8
            PIN A(7:0) FA(7:0)
            PIN B(7:0) XLXN_73(7:0)
            PIN CI CFG
            PIN CO
            PIN OFL
            PIN S(7:0) SL(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_54 busgnd
            PIN GBUS(7:0) XLXN_73(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_41 buf
            PIN I PA(0)
            PIN O ADDR(0)
        END BLOCK
        BEGIN BLOCK XLXI_42 buf
            PIN I PA(1)
            PIN O ADDR(1)
        END BLOCK
        BEGIN BLOCK XLXI_43 buf
            PIN I XLXN_123
            PIN O ADDR(2)
        END BLOCK
        BEGIN BLOCK XLXI_44 buf
            PIN I XLXN_122
            PIN O ADDR(3)
        END BLOCK
        BEGIN BLOCK XLXI_45 buf
            PIN I XLXN_121
            PIN O ADDR(4)
        END BLOCK
        BEGIN BLOCK XLXI_46 buf
            PIN I XLXN_120
            PIN O ADDR(5)
        END BLOCK
        BEGIN BLOCK XLXI_47 buf
            PIN I ASL0
            PIN O ADDR(6)
        END BLOCK
        BEGIN BLOCK XLXI_48 buf
            PIN I ASL1
            PIN O ADDR(7)
        END BLOCK
        BEGIN BLOCK XLXI_49 buf
            PIN I ASL2
            PIN O ADDR(8)
        END BLOCK
        BEGIN BLOCK XLXI_50 buf
            PIN I ASL3
            PIN O ADDR(9)
        END BLOCK
        BEGIN BLOCK XLXI_51 buf
            PIN I ASL4
            PIN O ADDR(10)
        END BLOCK
        BEGIN BLOCK XLXI_71 add4
            PIN A0 PA(2)
            PIN A1 PA(3)
            PIN A2 PA(4)
            PIN A3 PA(5)
            PIN B0 XLXN_119
            PIN B1 CFG
            PIN B2 XLXN_118
            PIN B3 XLXN_118
            PIN CI XLXN_124
            PIN CO
            PIN OFL
            PIN S0 XLXN_123
            PIN S1 XLXN_122
            PIN S2 XLXN_121
            PIN S3 XLXN_120
        END BLOCK
        BEGIN BLOCK XLXI_72 gnd
            PIN G XLXN_118
        END BLOCK
        BEGIN BLOCK XLXI_73 vcc
            PIN P XLXN_119
        END BLOCK
        BEGIN BLOCK XLXI_74 and4b1
            PIN I0 PA(3)
            PIN I1 PA(2)
            PIN I2 PA(4)
            PIN I3 PA(5)
            PIN O CFG
        END BLOCK
        BEGIN BLOCK XLXI_75 nor4
            PIN I0 PA(5)
            PIN I1 PA(4)
            PIN I2 PA(3)
            PIN I3 PA(2)
            PIN O SFLD
        END BLOCK
        BEGIN BLOCK XLXI_76 mod24
            PIN I0 SL(0)
            PIN I1 SL(1)
            PIN I2 SL(2)
            PIN I3 SL(3)
            PIN I4 SL(4)
            PIN O0 ASL0
            PIN O1 ASL1
            PIN O2 ASL2
            PIN O3 ASL3
            PIN O4 ASL4
        END BLOCK
        BEGIN BLOCK XLXI_77 gnd
            PIN G XLXN_124
        END BLOCK
        BEGIN BLOCK XLXI_78 fd4ce
            PIN C XLXN_139
            PIN CE XLXN_138
            PIN CLR XLXN_137
            PIN D0 ASL0
            PIN D1 ASL1
            PIN D2 ASL2
            PIN D3 ASL3
            PIN Q0 SL0
            PIN Q1 SL1
            PIN Q2 SL2
            PIN Q3 SL3
        END BLOCK
        BEGIN BLOCK XLXI_79 fdce
            PIN C XLXN_139
            PIN CE XLXN_138
            PIN CLR XLXN_137
            PIN D ASL4
            PIN Q SL4
        END BLOCK
        BEGIN BLOCK XLXI_80 vcc
            PIN P XLXN_138
        END BLOCK
        BEGIN BLOCK XLXI_81 gnd
            PIN G XLXN_137
        END BLOCK
        BEGIN BLOCK XLXI_83 inv
            PIN I XLXN_140
            PIN O XLXN_139
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 5440 3520
        BEGIN BRANCH CLK
            WIRE 160 544 320 544
            WIRE 320 544 480 544
            WIRE 320 544 320 1248
            WIRE 320 1248 480 1248
            WIRE 320 1248 320 1888
            WIRE 320 1888 480 1888
            WIRE 320 1888 320 2672
            WIRE 320 2672 2048 2672
            WIRE 2048 1888 2176 1888
            WIRE 2048 1888 2048 2672
        END BRANCH
        BEGIN BRANCH XLXN_3
            WIRE 320 384 320 480
            WIRE 320 480 480 480
        END BRANCH
        BEGIN BRANCH BIT0
            WIRE 864 928 976 928
            WIRE 976 928 1040 928
            WIRE 976 928 976 1360
            WIRE 976 1360 1040 1360
        END BRANCH
        BEGIN BRANCH BIT1
            WIRE 864 992 992 992
            WIRE 992 992 1040 992
            WIRE 992 992 992 1296
            WIRE 992 1296 1040 1296
        END BRANCH
        BEGIN BRANCH BIT2
            WIRE 864 1056 1008 1056
            WIRE 1008 1056 1040 1056
            WIRE 1008 1056 1008 1232
            WIRE 1008 1232 1040 1232
        END BRANCH
        BEGIN BRANCH XLXN_10
            WIRE 400 1344 480 1344
            WIRE 400 1344 400 1424
        END BRANCH
        BEGIN BRANCH XLXN_16
            WIRE 416 1584 1376 1584
            WIRE 1376 1584 1600 1584
            WIRE 1600 1584 1600 1936
            WIRE 1600 1936 1680 1936
            WIRE 416 1584 416 1824
            WIRE 416 1824 480 1824
            WIRE 1296 1328 1376 1328
            WIRE 1376 1328 1376 1584
        END BRANCH
        BEGIN BRANCH FS(7:0)
            WIRE 1120 2096 1200 2096
            WIRE 1120 2096 1120 2112
            WIRE 1120 2112 1120 2176
            WIRE 1120 2176 1120 2240
            WIRE 1120 2240 1120 2304
            WIRE 1120 2304 1120 2368
            WIRE 1120 2368 1120 2432
            WIRE 1120 2432 1120 2496
            WIRE 1120 2496 1120 2560
        END BRANCH
        INSTANCE XLXI_1 480 672 R0
        INSTANCE XLXI_2 256 384 R0
        INSTANCE XLXI_3 480 1376 R0
        INSTANCE XLXI_4 336 1552 R0
        INSTANCE XLXI_5 1040 1488 R0
        INSTANCE XLXI_6 480 2016 R0
        INSTANCE XLXI_7 1200 2224 R0
        BUSTAP 1120 2112 1024 2112
        BUSTAP 1120 2176 1024 2176
        BUSTAP 1120 2240 1024 2240
        BUSTAP 1120 2304 1024 2304
        BUSTAP 1120 2368 1024 2368
        BUSTAP 1120 2432 1024 2432
        BUSTAP 1120 2496 1024 2496
        BUSTAP 1120 2560 1024 2560
        IOMARKER 160 544 CLK R180 28
        IOMARKER 1040 928 BIT0 R0 28
        IOMARKER 1040 992 BIT1 R0 28
        IOMARKER 1040 1056 BIT2 R0 28
        INSTANCE XLXI_15 1680 2064 R0
        BEGIN BRANCH XLXN_35
            WIRE 1584 2000 1680 2000
        END BRANCH
        INSTANCE XLXI_16 816 2048 R90
        INSTANCE XLXI_17 816 2112 R90
        INSTANCE XLXI_18 816 2368 R90
        INSTANCE XLXI_19 944 2304 R270
        INSTANCE XLXI_20 944 2368 R270
        INSTANCE XLXI_21 944 2432 R270
        INSTANCE XLXI_22 944 2560 R270
        INSTANCE XLXI_23 944 2624 R270
        BEGIN BRANCH FS(7)
            WIRE 944 2112 1024 2112
        END BRANCH
        BEGIN BRANCH FS(6)
            WIRE 944 2176 1024 2176
        END BRANCH
        BEGIN BRANCH FS(5)
            WIRE 944 2240 1024 2240
        END BRANCH
        BEGIN BRANCH FS(4)
            WIRE 944 2304 1024 2304
        END BRANCH
        BEGIN BRANCH FS(3)
            WIRE 944 2368 1024 2368
        END BRANCH
        BEGIN BRANCH FS(2)
            WIRE 944 2432 1024 2432
        END BRANCH
        BEGIN BRANCH FS(1)
            WIRE 944 2496 1024 2496
        END BRANCH
        BEGIN BRANCH FS(0)
            WIRE 944 2560 1024 2560
        END BRANCH
        INSTANCE XLXI_24 2176 2016 R0
        BEGIN BRANCH FA(7:0)
            WIRE 2560 1760 2720 1760
            WIRE 2720 1760 2720 1920
            WIRE 2720 1920 2800 1920
            WIRE 2720 1760 3440 1760
        END BRANCH
        INSTANCE XLXI_25 2800 2240 R0
        BEGIN BRANCH SS(7:0)
            WIRE 2720 2112 2800 2112
            WIRE 2720 2112 2720 2176
            WIRE 2720 2176 2720 2240
            WIRE 2720 2240 2720 2304
            WIRE 2720 2304 2720 2368
            WIRE 2720 2368 2720 2432
            WIRE 2720 2432 2720 2496
            WIRE 2720 2496 2720 2560
        END BRANCH
        BUSTAP 2720 2560 2624 2560
        BUSTAP 2720 2496 2624 2496
        BUSTAP 2720 2432 2624 2432
        BUSTAP 2720 2368 2624 2368
        BUSTAP 2720 2304 2624 2304
        BUSTAP 2720 2240 2624 2240
        BUSTAP 2720 2176 2624 2176
        BUSTAP 2720 2112 2624 2112
        INSTANCE XLXI_26 2544 2624 R270
        INSTANCE XLXI_27 2544 2560 R270
        INSTANCE XLXI_28 2544 2496 R270
        INSTANCE XLXI_29 2544 2368 R270
        INSTANCE XLXI_30 2416 2304 R90
        INSTANCE XLXI_31 2416 2176 R90
        INSTANCE XLXI_32 2416 2112 R90
        INSTANCE XLXI_33 2416 2048 R90
        BEGIN BRANCH SS(0)
            WIRE 2544 2560 2624 2560
        END BRANCH
        BEGIN BRANCH SS(1)
            WIRE 2544 2496 2624 2496
        END BRANCH
        BEGIN BRANCH SS(2)
            WIRE 2544 2432 2624 2432
        END BRANCH
        BEGIN BRANCH SS(3)
            WIRE 2544 2368 2624 2368
        END BRANCH
        BEGIN BRANCH SS(4)
            WIRE 2544 2304 2624 2304
        END BRANCH
        BEGIN BRANCH SS(5)
            WIRE 2544 2240 2624 2240
        END BRANCH
        BEGIN BRANCH SS(6)
            WIRE 2544 2176 2624 2176
        END BRANCH
        BEGIN BRANCH SS(7)
            WIRE 2544 2112 2624 2112
        END BRANCH
        BEGIN BRANCH XLXN_57
            WIRE 2192 2336 2192 2656
            WIRE 2192 2656 3200 2656
            WIRE 3184 2016 3200 2016
            WIRE 3200 2016 3200 2656
        END BRANCH
        INSTANCE XLXI_34 2256 2336 R270
        BEGIN BRANCH XLXN_58
            WIRE 2160 1984 2176 1984
            WIRE 2160 1984 2160 2080
        END BRANCH
        BEGIN BRANCH XLXN_73(7:0)
            WIRE 3392 1888 3440 1888
        END BRANCH
        BEGIN BRANCH SL(0)
            WIRE 4032 1840 4112 1840
        END BRANCH
        BEGIN BRANCH SL(1)
            WIRE 4032 1904 4112 1904
        END BRANCH
        BEGIN BRANCH SL(2)
            WIRE 4032 1968 4112 1968
        END BRANCH
        BEGIN BRANCH SL(3)
            WIRE 4032 2032 4112 2032
        END BRANCH
        BEGIN BRANCH ADDR(10:0)
            WIRE 4800 480 4960 480
            WIRE 4800 480 4800 496
            WIRE 4800 496 4800 560
            WIRE 4800 560 4800 624
            WIRE 4800 624 4800 688
            WIRE 4800 688 4800 752
            WIRE 4800 752 4800 816
            WIRE 4800 816 4800 880
            WIRE 4800 880 4800 944
            WIRE 4800 944 4800 1008
            WIRE 4800 1008 4800 1072
            WIRE 4800 1072 4800 1136
        END BRANCH
        BEGIN BRANCH ADDR(10)
            WIRE 4640 496 4704 496
        END BRANCH
        BEGIN BRANCH ADDR(9)
            WIRE 4640 560 4704 560
        END BRANCH
        BEGIN BRANCH ADDR(8)
            WIRE 4640 624 4704 624
        END BRANCH
        BEGIN BRANCH ADDR(7)
            WIRE 4640 688 4704 688
        END BRANCH
        BEGIN BRANCH ADDR(6)
            WIRE 4640 752 4704 752
        END BRANCH
        BEGIN BRANCH ADDR(5)
            WIRE 4640 816 4704 816
        END BRANCH
        BEGIN BRANCH ADDR(4)
            WIRE 4640 880 4704 880
        END BRANCH
        BEGIN BRANCH ADDR(3)
            WIRE 4640 944 4704 944
        END BRANCH
        BEGIN BRANCH ADDR(2)
            WIRE 4640 1008 4704 1008
        END BRANCH
        BEGIN BRANCH ADDR(1)
            WIRE 4640 1072 4704 1072
        END BRANCH
        BEGIN BRANCH ADDR(0)
            WIRE 4640 1136 4704 1136
        END BRANCH
        BUSTAP 4800 496 4704 496
        BUSTAP 4800 560 4704 560
        BUSTAP 4800 624 4704 624
        BUSTAP 4800 688 4704 688
        BUSTAP 4800 752 4704 752
        BUSTAP 4800 816 4704 816
        BUSTAP 4800 880 4704 880
        BUSTAP 4800 944 4704 944
        BUSTAP 4800 1008 4704 1008
        BUSTAP 4800 1072 4704 1072
        BUSTAP 4800 1136 4704 1136
        INSTANCE XLXI_41 4416 1168 R0
        INSTANCE XLXI_42 4416 1104 R0
        INSTANCE XLXI_43 4416 1040 R0
        INSTANCE XLXI_44 4416 976 R0
        INSTANCE XLXI_45 4416 912 R0
        INSTANCE XLXI_46 4416 848 R0
        INSTANCE XLXI_47 4416 784 R0
        INSTANCE XLXI_48 4416 720 R0
        INSTANCE XLXI_49 4416 656 R0
        INSTANCE XLXI_50 4416 592 R0
        INSTANCE XLXI_51 4416 528 R0
        IOMARKER 4960 480 ADDR(10:0) R0 28
        BEGIN BRANCH SL(4)
            WIRE 4032 2096 4112 2096
        END BRANCH
        INSTANCE XLXI_71 3552 1360 R0
        BUSTAP 2560 656 2656 656
        BUSTAP 2560 720 2656 720
        BUSTAP 2560 784 2656 784
        BUSTAP 2560 848 2656 848
        BEGIN BRANCH PA(7:0)
            WIRE 864 1760 1120 1760
            WIRE 1120 1760 1120 1904
            WIRE 1120 1904 1200 1904
            WIRE 1120 1760 1280 1760
            WIRE 1280 1520 1280 1760
            WIRE 1280 1520 2560 1520
            WIRE 2560 656 2560 720
            WIRE 2560 720 2560 784
            WIRE 2560 784 2560 848
            WIRE 2560 848 2560 1440
            WIRE 2560 1440 2560 1504
            WIRE 2560 1504 2560 1520
        END BRANCH
        BEGIN BRANCH PA(4)
            WIRE 2656 784 2816 784
            WIRE 2816 784 3552 784
            WIRE 2816 784 2816 1088
            WIRE 2816 1088 2880 1088
            WIRE 2816 256 2896 256
            WIRE 2816 256 2816 784
        END BRANCH
        BEGIN BRANCH PA(5)
            WIRE 2656 848 2800 848
            WIRE 2800 848 3552 848
            WIRE 2800 848 2800 1152
            WIRE 2800 1152 2880 1152
            WIRE 2800 192 2896 192
            WIRE 2800 192 2800 848
        END BRANCH
        INSTANCE XLXI_72 3424 1360 R0
        INSTANCE XLXI_73 3440 1040 R270
        BEGIN BRANCH XLXN_119
            WIRE 3440 976 3552 976
        END BRANCH
        BUSTAP 2560 1504 2656 1504
        BUSTAP 2560 1440 2656 1440
        BEGIN BRANCH PA(0)
            WIRE 2656 1504 4208 1504
            WIRE 4208 1136 4416 1136
            WIRE 4208 1136 4208 1504
        END BRANCH
        BEGIN BRANCH PA(1)
            WIRE 2656 1440 4160 1440
            WIRE 4160 1072 4416 1072
            WIRE 4160 1072 4160 1440
        END BRANCH
        INSTANCE XLXI_74 2880 896 M180
        IOMARKER 3440 400 CFG R0 28
        BEGIN BRANCH BITCLK
            WIRE 448 640 480 640
            WIRE 448 640 448 720
            WIRE 448 720 448 1184
            WIRE 448 1184 480 1184
            WIRE 448 1184 448 1424
            WIRE 448 1424 1040 1424
            WIRE 448 720 944 720
            WIRE 864 416 944 416
            WIRE 944 416 944 720
        END BRANCH
        BEGIN BRANCH BCLK
            WIRE 864 352 1040 352
        END BRANCH
        IOMARKER 1040 352 BCLK R0 28
        INSTANCE XLXI_75 2896 128 M180
        BEGIN BRANCH SFLD
            WIRE 3152 288 3440 288
        END BRANCH
        IOMARKER 3440 288 SFLD R0 28
        BEGIN BRANCH XLXN_120
            WIRE 4000 1008 4192 1008
            WIRE 4192 816 4192 1008
            WIRE 4192 816 4416 816
        END BRANCH
        BEGIN BRANCH XLXN_121
            WIRE 4000 944 4160 944
            WIRE 4160 880 4160 944
            WIRE 4160 880 4416 880
        END BRANCH
        BEGIN BRANCH XLXN_122
            WIRE 4000 880 4064 880
            WIRE 4064 880 4064 912
            WIRE 4064 912 4256 912
            WIRE 4256 912 4256 944
            WIRE 4256 944 4416 944
        END BRANCH
        BEGIN BRANCH XLXN_123
            WIRE 4000 816 4112 816
            WIRE 4112 816 4112 864
            WIRE 4112 864 4224 864
            WIRE 4224 864 4224 1008
            WIRE 4224 1008 4416 1008
        END BRANCH
        BEGIN BRANCH XLXN_118
            WIRE 3488 1104 3552 1104
            WIRE 3488 1104 3488 1168
            WIRE 3488 1168 3552 1168
            WIRE 3488 1168 3488 1232
        END BRANCH
        BEGIN BRANCH CFG
            WIRE 3136 1056 3280 1056
            WIRE 3280 1056 3440 1056
            WIRE 3440 1056 3440 1632
            WIRE 3280 400 3440 400
            WIRE 3280 400 3280 1040
            WIRE 3280 1040 3280 1056
            WIRE 3280 1040 3552 1040
        END BRANCH
        INSTANCE XLXI_77 3360 464 R90
        BEGIN BRANCH XLXN_124
            WIRE 3488 528 3552 528
        END BRANCH
        BEGIN BRANCH PA(2)
            WIRE 2656 656 2848 656
            WIRE 2848 656 3552 656
            WIRE 2848 656 2848 1024
            WIRE 2848 1024 2880 1024
            WIRE 2848 384 2896 384
            WIRE 2848 384 2848 656
        END BRANCH
        BEGIN BRANCH PA(3)
            WIRE 2656 720 2832 720
            WIRE 2832 720 3552 720
            WIRE 2832 720 2832 928
            WIRE 2832 928 2864 928
            WIRE 2864 928 2864 960
            WIRE 2864 960 2880 960
            WIRE 2832 320 2896 320
            WIRE 2832 320 2832 720
        END BRANCH
        BEGIN INSTANCE XLXI_54 3392 1856 R180
        END INSTANCE
        INSTANCE XLXI_52 3440 2080 R0
        BEGIN BRANCH SL(7:0)
            WIRE 3888 1824 3936 1824
            WIRE 3936 1824 3936 1840
            WIRE 3936 1840 3936 1904
            WIRE 3936 1904 3936 1968
            WIRE 3936 1968 3936 2032
            WIRE 3936 2032 3936 2096
        END BRANCH
        BUSTAP 3936 2096 4032 2096
        BUSTAP 3936 2032 4032 2032
        BUSTAP 3936 1968 4032 1968
        BUSTAP 3936 1904 4032 1904
        BUSTAP 3936 1840 4032 1840
        BEGIN INSTANCE XLXI_76 4112 2128 R0
        END INSTANCE
        BEGIN BRANCH ASL0
            WIRE 4336 752 4416 752
            WIRE 4336 752 4336 1232
            WIRE 4336 1232 4576 1232
            WIRE 4576 1232 4576 1840
            WIRE 4576 1840 4640 1840
            WIRE 4496 1840 4576 1840
        END BRANCH
        BEGIN BRANCH ASL1
            WIRE 4320 688 4416 688
            WIRE 4320 688 4320 1248
            WIRE 4320 1248 4560 1248
            WIRE 4560 1248 4560 1904
            WIRE 4560 1904 4640 1904
            WIRE 4496 1904 4560 1904
        END BRANCH
        BEGIN BRANCH ASL2
            WIRE 4304 624 4416 624
            WIRE 4304 624 4304 1264
            WIRE 4304 1264 4544 1264
            WIRE 4544 1264 4544 1968
            WIRE 4544 1968 4640 1968
            WIRE 4496 1968 4544 1968
        END BRANCH
        BEGIN BRANCH ASL3
            WIRE 4288 560 4416 560
            WIRE 4288 560 4288 1280
            WIRE 4288 1280 4528 1280
            WIRE 4528 1280 4528 2032
            WIRE 4528 2032 4640 2032
            WIRE 4496 2032 4528 2032
        END BRANCH
        BEGIN BRANCH ASL4
            WIRE 4272 496 4416 496
            WIRE 4272 496 4272 1296
            WIRE 4272 1296 4512 1296
            WIRE 4512 1296 4512 2096
            WIRE 4512 2096 4512 2400
            WIRE 4512 2400 4640 2400
            WIRE 4496 2096 4512 2096
        END BRANCH
        INSTANCE XLXI_78 4640 2288 R0
        INSTANCE XLXI_79 4640 2656 R0
        BEGIN BRANCH SL0
            WIRE 5024 1840 5120 1840
        END BRANCH
        BEGIN BRANCH SL1
            WIRE 5024 1904 5120 1904
        END BRANCH
        BEGIN BRANCH SL2
            WIRE 5024 1968 5120 1968
        END BRANCH
        BEGIN BRANCH SL3
            WIRE 5024 2032 5120 2032
        END BRANCH
        BEGIN BRANCH SL4
            WIRE 5024 2400 5120 2400
        END BRANCH
        BEGIN BRANCH XLXN_137
            WIRE 4624 2256 4640 2256
            WIRE 4624 2256 4624 2624
            WIRE 4624 2624 4640 2624
            WIRE 4624 2624 4624 2672
        END BRANCH
        BEGIN BRANCH XLXN_138
            WIRE 4608 1776 4608 2096
            WIRE 4608 2096 4640 2096
            WIRE 4608 2096 4608 2464
            WIRE 4608 2464 4640 2464
        END BRANCH
        INSTANCE XLXI_80 4544 1776 R0
        INSTANCE XLXI_81 4560 2800 R0
        IOMARKER 5120 1840 SL0 R0 28
        IOMARKER 5120 1904 SL1 R0 28
        IOMARKER 5120 1968 SL2 R0 28
        IOMARKER 5120 2032 SL3 R0 28
        IOMARKER 5120 2400 SL4 R0 28
        BEGIN BRANCH XLXN_139
            WIRE 4176 2640 4576 2640
            WIRE 4576 2160 4640 2160
            WIRE 4576 2160 4576 2528
            WIRE 4576 2528 4640 2528
            WIRE 4576 2528 4576 2640
        END BRANCH
        BEGIN BRANCH XLXN_140
            WIRE 480 1984 480 2640
            WIRE 480 2640 2016 2640
            WIRE 2016 2640 3952 2640
            WIRE 1936 1968 2016 1968
            WIRE 2016 1968 2016 2400
            WIRE 2016 2400 2128 2400
            WIRE 2016 2400 2016 2640
            WIRE 2016 1824 2176 1824
            WIRE 2016 1824 2016 1968
            WIRE 2128 2336 2128 2400
        END BRANCH
        INSTANCE XLXI_83 3952 2672 R0
    END SHEET
END SCHEMATIC
