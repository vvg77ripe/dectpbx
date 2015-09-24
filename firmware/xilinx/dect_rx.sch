VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL RXD
        SIGNAL CLK
        SIGNAL XLXN_6
        SIGNAL XLXN_9
        SIGNAL XLXN_14
        SIGNAL XLXN_18
        SIGNAL XLXN_19
        SIGNAL XLXN_20
        SIGNAL XLXN_21
        SIGNAL XLXN_24
        SIGNAL XLXN_25
        SIGNAL XLXN_29
        SIGNAL XLXN_30
        SIGNAL SFLD
        SIGNAL XLXN_33
        SIGNAL XLXN_37
        SIGNAL XLXN_38
        SIGNAL XLXN_39
        SIGNAL XLXN_40
        SIGNAL DOUT(7:0)
        SIGNAL DOUT(7)
        SIGNAL XLXN_67
        SIGNAL XLXN_70
        SIGNAL XLXN_71
        SIGNAL XLXN_72
        SIGNAL BS
        SIGNAL XLXN_83
        SIGNAL BIT
        SIGNAL ADDR(7:0)
        SIGNAL FRAME
        SIGNAL SBYTE1(7:0)
        SIGNAL XLXN_93(7:0)
        SIGNAL XLXN_94(7:0)
        SIGNAL XLXN_95(7:0)
        SIGNAL XLXN_96(7:0)
        SIGNAL XLXN_99
        SIGNAL SBYTE1(7)
        SIGNAL XLXN_102
        SIGNAL XLXN_103
        SIGNAL MAXPKT(7:0)
        SIGNAL MAXPKT(0)
        SIGNAL MAXPKT(1)
        SIGNAL MAXPKT(2)
        SIGNAL MAXPKT(3)
        SIGNAL MAXPKT(4)
        SIGNAL MAXPKT(5)
        SIGNAL MAXPKT(6)
        SIGNAL MAXPKT(7)
        SIGNAL RFP
        SIGNAL XLXN_106
        SIGNAL XLXN_107
        PORT Input RXD
        PORT Input CLK
        PORT Input SFLD
        PORT Output DOUT(7:0)
        PORT Output BS
        PORT Output BIT
        PORT Output ADDR(7:0)
        PORT Output FRAME
        PORT Input RFP
        BEGIN BLOCKDEF fd
            TIMESTAMP 2001 2 2 12 37 14
            RECTANGLE N 64 -320 320 -64 
            LINE N 0 -128 64 -128 
            LINE N 0 -256 64 -256 
            LINE N 384 -256 320 -256 
            LINE N 80 -128 64 -144 
            LINE N 64 -112 80 -128 
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
        BEGIN BLOCKDEF vcc
            TIMESTAMP 2001 2 2 12 37 29
            LINE N 64 -32 64 -64 
            LINE N 64 0 64 -32 
            LINE N 96 -64 32 -64 
        END BLOCKDEF
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
        BEGIN BLOCKDEF or2
            TIMESTAMP 2001 2 2 12 38 38
            LINE N 0 -64 64 -64 
            LINE N 0 -128 64 -128 
            LINE N 256 -96 192 -96 
            ARC N 28 -224 204 -48 112 -48 192 -96 
            ARC N -40 -152 72 -40 48 -48 48 -144 
            LINE N 112 -144 48 -144 
            ARC N 28 -144 204 32 192 -96 112 -144 
            LINE N 112 -48 48 -48 
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
        BEGIN BLOCKDEF and3
            TIMESTAMP 2001 2 2 12 38 38
            LINE N 0 -64 64 -64 
            LINE N 0 -128 64 -128 
            LINE N 0 -192 64 -192 
            LINE N 256 -128 192 -128 
            LINE N 64 -176 144 -176 
            LINE N 144 -80 64 -80 
            ARC N 96 -176 192 -80 144 -80 144 -176 
            LINE N 64 -64 64 -192 
        END BLOCKDEF
        BEGIN BLOCKDEF xor2
            TIMESTAMP 2001 2 2 12 38 38
            LINE N 0 -64 64 -64 
            LINE N 0 -128 60 -128 
            LINE N 256 -96 208 -96 
            ARC N -40 -152 72 -40 48 -48 44 -144 
            ARC N -24 -152 88 -40 64 -48 64 -144 
            LINE N 128 -144 64 -144 
            LINE N 128 -48 64 -48 
            ARC N 44 -144 220 32 208 -96 128 -144 
            ARC N 44 -224 220 -48 128 -48 208 -96 
        END BLOCKDEF
        BEGIN BLOCKDEF fdpe
            TIMESTAMP 2001 2 2 12 37 14
            LINE N 64 -112 80 -128 
            LINE N 80 -128 64 -144 
            LINE N 192 -320 192 -352 
            LINE N 192 -352 64 -352 
            RECTANGLE N 64 -320 320 -64 
            LINE N 384 -256 320 -256 
            LINE N 0 -352 64 -352 
            LINE N 0 -256 64 -256 
            LINE N 0 -192 64 -192 
            LINE N 0 -128 64 -128 
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
        BEGIN BLOCKDEF and3b2
            TIMESTAMP 2001 2 2 12 38 38
            LINE N 0 -64 40 -64 
            CIRCLE N 40 -76 64 -52 
            LINE N 0 -128 40 -128 
            CIRCLE N 40 -140 64 -116 
            LINE N 0 -192 64 -192 
            LINE N 256 -128 192 -128 
            LINE N 64 -64 64 -192 
            ARC N 96 -176 192 -80 144 -80 144 -176 
            LINE N 144 -80 64 -80 
            LINE N 64 -176 144 -176 
        END BLOCKDEF
        BEGIN BLOCKDEF sr8re
            TIMESTAMP 2001 2 2 12 39 45
            LINE N 192 -32 64 -32 
            LINE N 192 -64 192 -32 
            LINE N 80 -128 64 -144 
            LINE N 64 -112 80 -128 
            RECTANGLE N 320 -268 384 -244 
            LINE N 0 -320 64 -320 
            LINE N 384 -256 320 -256 
            LINE N 0 -32 64 -32 
            LINE N 0 -192 64 -192 
            LINE N 0 -128 64 -128 
            RECTANGLE N 64 -384 320 -64 
        END BLOCKDEF
        BEGIN BLOCKDEF dect_sfield
            TIMESTAMP 2006 1 2 13 5 23
            RECTANGLE N 64 -192 320 0 
            LINE N 64 -160 0 -160 
            LINE N 320 -96 384 -96 
            RECTANGLE N 320 -108 384 -84 
            LINE N 320 -32 384 -32 
            RECTANGLE N 320 -44 384 -20 
            LINE N 320 -160 384 -160 
            RECTANGLE N 320 -172 384 -148 
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
        BEGIN BLOCKDEF cb8ce
            TIMESTAMP 2001 2 2 12 36 39
            LINE N 384 -128 320 -128 
            RECTANGLE N 320 -268 384 -244 
            LINE N 384 -256 320 -256 
            LINE N 0 -192 64 -192 
            LINE N 192 -32 64 -32 
            LINE N 192 -64 192 -32 
            LINE N 80 -128 64 -144 
            LINE N 64 -112 80 -128 
            LINE N 0 -128 64 -128 
            LINE N 0 -32 64 -32 
            LINE N 384 -192 320 -192 
            RECTANGLE N 64 -320 320 -64 
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
        BEGIN BLOCKDEF compm8
            TIMESTAMP 2001 2 2 12 36 26
            LINE N 0 -128 64 -128 
            RECTANGLE N 0 -140 64 -116 
            LINE N 0 -320 64 -320 
            RECTANGLE N 0 -332 64 -308 
            RECTANGLE N 64 -384 320 -64 
            LINE N 384 -192 320 -192 
            LINE N 384 -256 320 -256 
        END BLOCKDEF
        BEGIN BLOCKDEF or3b1
            TIMESTAMP 2001 2 2 12 25 36
            LINE N 0 -64 28 -64 
            CIRCLE N 28 -72 48 -52 
            LINE N 0 -128 72 -128 
            LINE N 0 -192 48 -192 
            LINE N 256 -128 192 -128 
            LINE N 112 -176 48 -176 
            ARC N 28 -176 204 0 192 -128 112 -176 
            ARC N 28 -256 204 -80 112 -80 192 -128 
            LINE N 112 -80 48 -80 
            LINE N 48 -64 48 -80 
            LINE N 48 -192 48 -176 
            ARC N -40 -184 72 -72 48 -80 48 -176 
        END BLOCKDEF
        BEGIN BLOCK XLXI_1 fd
            PIN C CLK
            PIN D RXD
            PIN Q XLXN_25
        END BLOCK
        BEGIN BLOCK XLXI_2 fd
            PIN C XLXN_6
            PIN D RXD
            PIN Q XLXN_24
        END BLOCK
        BEGIN BLOCK XLXI_3 inv
            PIN I CLK
            PIN O XLXN_6
        END BLOCK
        BEGIN BLOCK XLXI_5 vcc
            PIN P XLXN_9
        END BLOCK
        BEGIN BLOCK XLXI_6 cb4re
            PIN C CLK
            PIN CE XLXN_9
            PIN R XLXN_14
            PIN CEO
            PIN Q0 XLXN_19
            PIN Q1 XLXN_20
            PIN Q2 XLXN_21
            PIN Q3 XLXN_18
            PIN TC
        END BLOCK
        BEGIN BLOCK XLXI_7 or2
            PIN I0 XLXN_37
            PIN I1 XLXN_18
            PIN O XLXN_14
        END BLOCK
        BEGIN BLOCK XLXI_8 nor4
            PIN I0 XLXN_21
            PIN I1 XLXN_20
            PIN I2 XLXN_19
            PIN I3 XLXN_18
            PIN O XLXN_30
        END BLOCK
        BEGIN BLOCK XLXI_9 and3
            PIN I0 XLXN_19
            PIN I1 XLXN_20
            PIN I2 XLXN_21
            PIN O XLXN_29
        END BLOCK
        BEGIN BLOCK XLXI_11 xor2
            PIN I0 XLXN_24
            PIN I1 XLXN_25
            PIN O XLXN_40
        END BLOCK
        BEGIN BLOCK XLXI_13 fdpe
            PIN C CLK
            PIN CE XLXN_14
            PIN D XLXN_33
            PIN PRE XLXN_38
            PIN Q XLXN_37
        END BLOCK
        BEGIN BLOCK XLXI_14 gnd
            PIN G XLXN_33
        END BLOCK
        BEGIN BLOCK XLXI_15 and2
            PIN I0 XLXN_39
            PIN I1 XLXN_40
            PIN O XLXN_38
        END BLOCK
        BEGIN BLOCK XLXI_16 and3b2
            PIN I0 XLXN_19
            PIN I1 XLXN_20
            PIN I2 XLXN_21
            PIN O BIT
        END BLOCK
        BEGIN BLOCK XLXI_20 sr8re
            PIN C CLK
            PIN CE BIT
            PIN R XLXN_99
            PIN SLI RXD
            PIN Q(7:0) DOUT(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_27 sr8re
            PIN C CLK
            PIN CE BIT
            PIN R XLXN_99
            PIN SLI DOUT(7)
            PIN Q(7:0) SBYTE1(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_32 comp8
            PIN A(7:0) DOUT(7:0)
            PIN B(7:0) XLXN_94(7:0)
            PIN EQ XLXN_102
        END BLOCK
        BEGIN BLOCK XLXI_33 comp8
            PIN A(7:0) SBYTE1(7:0)
            PIN B(7:0) XLXN_95(7:0)
            PIN EQ XLXN_103
        END BLOCK
        BEGIN BLOCK XLXI_36 cb4re
            PIN C CLK
            PIN CE BIT
            PIN R XLXN_67
            PIN CEO
            PIN Q0 XLXN_70
            PIN Q1 XLXN_71
            PIN Q2 XLXN_72
            PIN Q3
            PIN TC
        END BLOCK
        BEGIN BLOCK XLXI_37 and3
            PIN I0 XLXN_72
            PIN I1 XLXN_71
            PIN I2 XLXN_70
            PIN O XLXN_83
        END BLOCK
        BEGIN BLOCK XLXI_40 cb8ce
            PIN C CLK
            PIN CE BS
            PIN CLR XLXN_67
            PIN CEO
            PIN Q(7:0) ADDR(7:0)
            PIN TC
        END BLOCK
        BEGIN BLOCK XLXI_43 and3
            PIN I0 XLXN_83
            PIN I1 BIT
            PIN I2 FRAME
            PIN O BS
        END BLOCK
        BEGIN BLOCK XLXI_45 sr8re
            PIN C CLK
            PIN CE BIT
            PIN R XLXN_99
            PIN SLI SBYTE1(7)
            PIN Q(7:0) XLXN_93(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_25 dect_sfield
            PIN RFP RFP
            PIN BYTE1(7:0) XLXN_95(7:0)
            PIN PRE(7:0) XLXN_96(7:0)
            PIN BYTE2(7:0) XLXN_94(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_48 comp8
            PIN A(7:0) XLXN_93(7:0)
            PIN B(7:0) XLXN_96(7:0)
            PIN EQ XLXN_106
        END BLOCK
        BEGIN BLOCK XLXI_49 gnd
            PIN G XLXN_99
        END BLOCK
        BEGIN BLOCK XLXI_50 and4
            PIN I0 XLXN_106
            PIN I1 XLXN_103
            PIN I2 XLXN_102
            PIN I3 SFLD
            PIN O XLXN_67
        END BLOCK
        BEGIN BLOCK XLXI_52 compm8
            PIN A(7:0) MAXPKT(7:0)
            PIN B(7:0) ADDR(7:0)
            PIN GT FRAME
            PIN LT
        END BLOCK
        BEGIN BLOCK XLXI_53 gnd
            PIN G MAXPKT(7)
        END BLOCK
        BEGIN BLOCK XLXI_54 gnd
            PIN G MAXPKT(6)
        END BLOCK
        BEGIN BLOCK XLXI_55 gnd
            PIN G MAXPKT(3)
        END BLOCK
        BEGIN BLOCK XLXI_56 gnd
            PIN G MAXPKT(1)
        END BLOCK
        BEGIN BLOCK XLXI_57 vcc
            PIN P MAXPKT(5)
        END BLOCK
        BEGIN BLOCK XLXI_58 vcc
            PIN P MAXPKT(4)
        END BLOCK
        BEGIN BLOCK XLXI_60 vcc
            PIN P MAXPKT(0)
        END BLOCK
        BEGIN BLOCK XLXI_61 or3b1
            PIN I0 FRAME
            PIN I1 XLXN_30
            PIN I2 XLXN_29
            PIN O XLXN_39
        END BLOCK
        BEGIN BLOCK XLXI_62 gnd
            PIN G MAXPKT(2)
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 5440 3520
        IOMARKER 240 320 RXD R180 28
        IOMARKER 240 640 CLK R180 28
        INSTANCE XLXI_1 960 576 R0
        INSTANCE XLXI_2 960 896 R0
        INSTANCE XLXI_3 656 800 R0
        BEGIN BRANCH XLXN_6
            WIRE 880 768 960 768
        END BRANCH
        INSTANCE XLXI_5 816 1200 R0
        BEGIN BRANCH XLXN_9
            WIRE 880 1200 880 1280
            WIRE 880 1280 960 1280
        END BRANCH
        INSTANCE XLXI_6 960 1472 R0
        INSTANCE XLXI_7 1520 1344 R0
        BEGIN BRANCH XLXN_14
            WIRE 960 1440 960 1520
            WIRE 960 1520 1808 1520
            WIRE 1776 1248 1808 1248
            WIRE 1808 1248 1808 1424
            WIRE 1808 1424 1808 1520
            WIRE 1808 1424 2080 1424
        END BRANCH
        INSTANCE XLXI_9 1504 976 R0
        BEGIN BRANCH XLXN_19
            WIRE 1344 1024 1440 1024
            WIRE 1440 1024 1520 1024
            WIRE 1440 1024 1440 1792
            WIRE 1440 1792 1504 1792
            WIRE 1440 912 1504 912
            WIRE 1440 912 1440 1024
        END BRANCH
        BEGIN BRANCH XLXN_20
            WIRE 1344 1088 1424 1088
            WIRE 1424 1088 1520 1088
            WIRE 1424 1088 1424 1856
            WIRE 1424 1856 1504 1856
            WIRE 1424 848 1504 848
            WIRE 1424 848 1424 1088
        END BRANCH
        BEGIN BRANCH XLXN_21
            WIRE 1344 1152 1408 1152
            WIRE 1408 1152 1520 1152
            WIRE 1408 1152 1408 1920
            WIRE 1408 1920 1504 1920
            WIRE 1408 784 1504 784
            WIRE 1408 784 1408 1152
        END BRANCH
        INSTANCE XLXI_11 1520 704 R0
        BEGIN BRANCH XLXN_24
            WIRE 1344 640 1520 640
        END BRANCH
        BEGIN BRANCH XLXN_25
            WIRE 1344 320 1424 320
            WIRE 1424 320 1424 576
            WIRE 1424 576 1520 576
        END BRANCH
        INSTANCE XLXI_8 1520 1216 R0
        BEGIN BRANCH XLXN_18
            WIRE 1344 1216 1472 1216
            WIRE 1472 1216 1520 1216
            WIRE 1472 960 1520 960
            WIRE 1472 960 1472 1216
        END BRANCH
        BEGIN BRANCH XLXN_29
            WIRE 1760 848 1872 848
            WIRE 1872 848 1872 896
        END BRANCH
        BEGIN BRANCH XLXN_30
            WIRE 1776 1056 1808 1056
            WIRE 1808 960 1808 1056
            WIRE 1808 960 1872 960
        END BRANCH
        IOMARKER 240 1600 SFLD R180 28
        INSTANCE XLXI_13 2080 1616 R0
        INSTANCE XLXI_14 1856 1616 R0
        BEGIN BRANCH XLXN_33
            WIRE 1920 1360 2080 1360
            WIRE 1920 1360 1920 1488
        END BRANCH
        BEGIN BRANCH XLXN_37
            WIRE 1488 1280 1520 1280
            WIRE 1488 1280 1488 1728
            WIRE 1488 1728 2480 1728
            WIRE 2464 1360 2480 1360
            WIRE 2480 1360 2480 1728
        END BRANCH
        BEGIN BRANCH XLXN_38
            WIRE 2048 1120 2048 1264
            WIRE 2048 1264 2080 1264
            WIRE 2048 1120 2496 1120
            WIRE 2416 928 2496 928
            WIRE 2496 928 2496 1120
        END BRANCH
        INSTANCE XLXI_15 2160 1024 R0
        BEGIN BRANCH XLXN_39
            WIRE 2128 960 2160 960
        END BRANCH
        BEGIN BRANCH XLXN_40
            WIRE 1776 608 2144 608
            WIRE 2144 608 2144 896
            WIRE 2144 896 2160 896
        END BRANCH
        INSTANCE XLXI_16 1504 1728 M180
        BEGIN BRANCH RXD
            WIRE 240 320 480 320
            WIRE 480 320 880 320
            WIRE 880 320 960 320
            WIRE 880 320 880 640
            WIRE 880 640 960 640
            WIRE 480 320 480 2016
            WIRE 480 2016 1920 2016
        END BRANCH
        INSTANCE XLXI_20 1920 2336 R0
        BEGIN BRANCH DOUT(7:0)
            WIRE 2304 2080 2400 2080
            WIRE 2400 2080 2880 2080
            WIRE 2880 2080 3040 2080
            WIRE 2880 2080 2880 2240
            WIRE 2880 2240 3104 2240
        END BRANCH
        BUSTAP 2400 2080 2400 2176
        BEGIN BRANCH DOUT(7)
            WIRE 1840 2368 1840 2496
            WIRE 1840 2496 1920 2496
            WIRE 1840 2368 2400 2368
            WIRE 2400 2176 2400 2368
        END BRANCH
        IOMARKER 3040 2080 DOUT(7:0) R0 28
        INSTANCE XLXI_36 3920 3472 R0
        BEGIN BRANCH XLXN_67
            WIRE 3824 2592 3872 2592
            WIRE 3872 2592 3872 3440
            WIRE 3872 3440 3920 3440
            WIRE 3872 2592 3920 2592
        END BRANCH
        INSTANCE XLXI_37 4400 3216 R0
        BEGIN BRANCH XLXN_70
            WIRE 4304 3024 4400 3024
        END BRANCH
        BEGIN BRANCH XLXN_71
            WIRE 4304 3088 4400 3088
        END BRANCH
        BEGIN BRANCH XLXN_72
            WIRE 4304 3152 4400 3152
        END BRANCH
        INSTANCE XLXI_40 3920 2624 R0
        BEGIN BRANCH BS
            WIRE 3904 2224 3904 2432
            WIRE 3904 2432 3920 2432
            WIRE 3904 2224 5120 2224
            WIRE 5120 2224 5120 2464
            WIRE 5120 2464 5200 2464
            WIRE 5056 2464 5120 2464
        END BRANCH
        BEGIN BRANCH XLXN_83
            WIRE 4656 3088 4800 3088
            WIRE 4800 2528 4800 3088
        END BRANCH
        INSTANCE XLXI_43 4800 2592 R0
        IOMARKER 5200 2336 FRAME R0 28
        IOMARKER 5200 2464 BS R0 28
        IOMARKER 4480 2720 BIT R0 28
        BEGIN BRANCH CLK
            WIRE 240 640 640 640
            WIRE 640 640 640 768
            WIRE 640 768 656 768
            WIRE 640 768 640 1344
            WIRE 640 1344 960 1344
            WIRE 640 1344 640 1680
            WIRE 640 1680 2000 1680
            WIRE 640 1680 640 2208
            WIRE 640 2208 1760 2208
            WIRE 1760 2208 1920 2208
            WIRE 1760 2208 1760 2688
            WIRE 1760 2688 1920 2688
            WIRE 1760 2688 1760 3168
            WIRE 1760 3168 1760 3344
            WIRE 1760 3344 3840 3344
            WIRE 3840 3344 3920 3344
            WIRE 1760 3168 1920 3168
            WIRE 640 448 960 448
            WIRE 640 448 640 640
            WIRE 2000 1488 2080 1488
            WIRE 2000 1488 2000 1680
            WIRE 3840 2496 3920 2496
            WIRE 3840 2496 3840 3344
        END BRANCH
        BEGIN BRANCH BIT
            WIRE 1760 1856 1808 1856
            WIRE 1808 1856 1808 2144
            WIRE 1808 2144 1920 2144
            WIRE 1808 2144 1808 2624
            WIRE 1808 2624 1808 3104
            WIRE 1808 3104 1808 3280
            WIRE 1808 3280 3808 3280
            WIRE 3808 3280 3920 3280
            WIRE 1808 3104 1920 3104
            WIRE 1808 2624 1920 2624
            WIRE 3808 2720 4384 2720
            WIRE 4384 2720 4480 2720
            WIRE 3808 2720 3808 3280
            WIRE 4384 2464 4800 2464
            WIRE 4384 2464 4384 2720
        END BRANCH
        INSTANCE XLXI_27 1920 2816 R0
        INSTANCE XLXI_45 1920 3296 R0
        INSTANCE XLXI_32 3104 2560 R0
        BEGIN INSTANCE XLXI_25 2576 2592 R0
        END INSTANCE
        INSTANCE XLXI_48 3104 3328 R0
        INSTANCE XLXI_33 3104 2944 R0
        BEGIN BRANCH SBYTE1(7:0)
            WIRE 2304 2560 2368 2560
            WIRE 2368 2560 2368 2624
            WIRE 2368 2624 2400 2624
            WIRE 2400 2624 3104 2624
        END BRANCH
        BEGIN BRANCH XLXN_93(7:0)
            WIRE 2304 3040 2704 3040
            WIRE 2704 3008 2704 3040
            WIRE 2704 3008 3104 3008
        END BRANCH
        BEGIN BRANCH XLXN_94(7:0)
            WIRE 2960 2432 3104 2432
        END BRANCH
        BEGIN BRANCH XLXN_95(7:0)
            WIRE 2960 2496 3040 2496
            WIRE 3040 2496 3040 2816
            WIRE 3040 2816 3104 2816
        END BRANCH
        BEGIN BRANCH XLXN_96(7:0)
            WIRE 2960 2560 3008 2560
            WIRE 3008 2560 3008 3200
            WIRE 3008 3200 3104 3200
        END BRANCH
        INSTANCE XLXI_49 1616 3456 R0
        BEGIN BRANCH XLXN_99
            WIRE 1680 2304 1920 2304
            WIRE 1680 2304 1680 2784
            WIRE 1680 2784 1920 2784
            WIRE 1680 2784 1680 3264
            WIRE 1680 3264 1920 3264
            WIRE 1680 3264 1680 3328
        END BRANCH
        BUSTAP 2400 2624 2400 2720
        BEGIN BRANCH SBYTE1(7)
            WIRE 1856 2832 1856 2976
            WIRE 1856 2976 1920 2976
            WIRE 1856 2832 2400 2832
            WIRE 2400 2720 2400 2832
        END BRANCH
        INSTANCE XLXI_50 3568 2752 R0
        BEGIN BRANCH XLXN_102
            WIRE 3488 2336 3520 2336
            WIRE 3520 2336 3520 2560
            WIRE 3520 2560 3568 2560
        END BRANCH
        BEGIN BRANCH XLXN_103
            WIRE 3488 2720 3520 2720
            WIRE 3520 2624 3520 2720
            WIRE 3520 2624 3568 2624
        END BRANCH
        IOMARKER 5200 2160 ADDR(7:0) R0 28
        INSTANCE XLXI_52 4416 2144 R0
        BEGIN BRANCH FRAME
            WIRE 1856 1024 1872 1024
            WIRE 1856 1024 1856 1056
            WIRE 1856 1056 4880 1056
            WIRE 4880 1056 4880 1888
            WIRE 4880 1888 4880 2336
            WIRE 4880 2336 5200 2336
            WIRE 4784 2336 4784 2400
            WIRE 4784 2400 4800 2400
            WIRE 4784 2336 4880 2336
            WIRE 4800 1888 4880 1888
        END BRANCH
        BEGIN BRANCH ADDR(7:0)
            WIRE 4304 2368 4384 2368
            WIRE 4384 2016 4416 2016
            WIRE 4384 2016 4384 2160
            WIRE 4384 2160 5200 2160
            WIRE 4384 2160 4384 2368
        END BRANCH
        BUSTAP 4320 1808 4224 1808
        BUSTAP 4320 1744 4224 1744
        BUSTAP 4320 1680 4224 1680
        BUSTAP 4320 1616 4224 1616
        BUSTAP 4320 1552 4224 1552
        BUSTAP 4320 1488 4224 1488
        BUSTAP 4320 1424 4224 1424
        BUSTAP 4320 1360 4224 1360
        BEGIN BRANCH MAXPKT(7:0)
            WIRE 4320 1360 4320 1424
            WIRE 4320 1424 4320 1488
            WIRE 4320 1488 4320 1552
            WIRE 4320 1552 4320 1616
            WIRE 4320 1616 4320 1680
            WIRE 4320 1680 4320 1744
            WIRE 4320 1744 4320 1808
            WIRE 4320 1808 4320 1824
            WIRE 4320 1824 4416 1824
        END BRANCH
        INSTANCE XLXI_53 3952 1744 R90
        INSTANCE XLXI_54 3952 1680 R90
        INSTANCE XLXI_55 3952 1488 R90
        INSTANCE XLXI_56 3952 1360 R90
        INSTANCE XLXI_57 4080 1744 R270
        INSTANCE XLXI_58 4080 1680 R270
        INSTANCE XLXI_60 4080 1424 R270
        BEGIN BRANCH MAXPKT(0)
            WIRE 4080 1360 4224 1360
        END BRANCH
        BEGIN BRANCH MAXPKT(1)
            WIRE 4080 1424 4224 1424
        END BRANCH
        BEGIN BRANCH MAXPKT(2)
            WIRE 4080 1488 4224 1488
        END BRANCH
        BEGIN BRANCH MAXPKT(3)
            WIRE 4080 1552 4224 1552
        END BRANCH
        BEGIN BRANCH MAXPKT(4)
            WIRE 4080 1616 4224 1616
        END BRANCH
        BEGIN BRANCH MAXPKT(5)
            WIRE 4080 1680 4224 1680
        END BRANCH
        BEGIN BRANCH MAXPKT(6)
            WIRE 4080 1744 4224 1744
        END BRANCH
        BEGIN BRANCH MAXPKT(7)
            WIRE 4080 1808 4224 1808
        END BRANCH
        BEGIN BRANCH RFP
            WIRE 240 2352 2480 2352
            WIRE 2480 2352 2480 2432
            WIRE 2480 2432 2576 2432
        END BRANCH
        IOMARKER 240 2352 RFP R180 28
        BEGIN BRANCH XLXN_106
            WIRE 3488 3104 3568 3104
            WIRE 3568 2688 3568 3104
        END BRANCH
        BEGIN BRANCH SFLD
            WIRE 240 1600 1840 1600
            WIRE 1840 1600 3568 1600
            WIRE 3568 1600 3568 2496
        END BRANCH
        INSTANCE XLXI_61 1872 1088 R0
        INSTANCE XLXI_62 3952 1424 R90
    END SHEET
END SCHEMATIC
