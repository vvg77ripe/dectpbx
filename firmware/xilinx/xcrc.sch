VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL D_IN
        SIGNAL TXE_IN
        SIGNAL B_FLD
        SIGNAL BCLK
        SIGNAL TXE_OUT
        SIGNAL D_OUT
        SIGNAL XLXN_11
        SIGNAL XLXN_14
        SIGNAL XLXN_18
        SIGNAL XLXN_19
        SIGNAL XLXN_22
        SIGNAL XLXN_23
        SIGNAL XLXN_25
        SIGNAL XLXN_28
        SIGNAL XLXN_29
        SIGNAL XLXN_33
        SIGNAL XLXN_36
        SIGNAL XLXN_38
        SIGNAL XLXN_41
        SIGNAL XLXN_42
        SIGNAL XLXN_43
        SIGNAL XLXN_45
        SIGNAL TEST
        SIGNAL XLXN_49
        SIGNAL XLXN_50
        PORT Input D_IN
        PORT Input TXE_IN
        PORT Input B_FLD
        PORT Input BCLK
        PORT Output TXE_OUT
        PORT Output D_OUT
        PORT Output TEST
        BEGIN BLOCKDEF m2_1
            TIMESTAMP 2001 2 2 12 39 29
            LINE N 96 -64 96 -192 
            LINE N 256 -96 96 -64 
            LINE N 256 -160 256 -96 
            LINE N 96 -192 256 -160 
            LINE N 176 -32 96 -32 
            LINE N 176 -80 176 -32 
            LINE N 0 -32 96 -32 
            LINE N 320 -128 256 -128 
            LINE N 0 -96 96 -96 
            LINE N 0 -160 96 -160 
        END BLOCKDEF
        BEGIN BLOCKDEF srl16
            TIMESTAMP 2001 2 2 12 39 45
            LINE N 384 -448 320 -448 
            LINE N 0 -512 64 -512 
            LINE N 0 -320 64 -320 
            LINE N 0 -256 64 -256 
            LINE N 0 -192 64 -192 
            LINE N 0 -128 64 -128 
            LINE N 0 -384 64 -384 
            LINE N 64 -368 80 -384 
            LINE N 80 -384 64 -400 
            RECTANGLE N 64 -576 320 -64 
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
        BEGIN BLOCKDEF and2b1
            TIMESTAMP 2001 2 2 12 38 38
            LINE N 64 -48 64 -144 
            LINE N 64 -144 144 -144 
            LINE N 144 -48 64 -48 
            ARC N 96 -144 192 -48 144 -48 144 -144 
            LINE N 256 -96 192 -96 
            LINE N 0 -128 64 -128 
            LINE N 0 -64 40 -64 
            CIRCLE N 40 -76 64 -52 
        END BLOCKDEF
        BEGIN BLOCKDEF srl16e
            TIMESTAMP 2001 2 2 12 39 45
            LINE N 384 -448 320 -448 
            LINE N 0 -448 64 -448 
            LINE N 0 -512 64 -512 
            LINE N 0 -320 64 -320 
            LINE N 0 -256 64 -256 
            LINE N 0 -192 64 -192 
            LINE N 0 -128 64 -128 
            LINE N 0 -384 64 -384 
            LINE N 64 -368 80 -384 
            LINE N 80 -384 64 -400 
            RECTANGLE N 64 -576 320 -64 
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
        BEGIN BLOCKDEF inv
            TIMESTAMP 2001 2 2 12 38 38
            LINE N 0 -32 64 -32 
            LINE N 224 -32 160 -32 
            LINE N 64 -64 128 -32 
            LINE N 128 -32 64 0 
            LINE N 64 0 64 -64 
            CIRCLE N 128 -48 160 -16 
        END BLOCKDEF
        BEGIN BLOCKDEF buf
            TIMESTAMP 2001 2 2 12 35 54
            LINE N 0 -32 64 -32 
            LINE N 224 -32 128 -32 
            LINE N 64 0 128 -32 
            LINE N 128 -32 64 -64 
            LINE N 64 -64 64 0 
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
        BEGIN BLOCKDEF cb4ce
            TIMESTAMP 2001 2 2 12 36 39
            RECTANGLE N 64 -512 320 -64 
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
            LINE N 384 -192 320 -192 
        END BLOCKDEF
        BEGIN BLOCK XLXI_1 m2_1
            PIN D0 D_IN
            PIN D1 XLXN_19
            PIN S0 XLXN_38
            PIN O D_OUT
        END BLOCK
        BEGIN BLOCK XLXI_2 srl16
            PIN A0 XLXN_14
            PIN A1 XLXN_14
            PIN A2 XLXN_14
            PIN A3 XLXN_11
            PIN CLK BCLK
            PIN D TXE_IN
            PIN Q XLXN_18
        END BLOCK
        BEGIN BLOCK XLXI_3 vcc
            PIN P XLXN_11
        END BLOCK
        BEGIN BLOCK XLXI_4 gnd
            PIN G XLXN_14
        END BLOCK
        BEGIN BLOCK XLXI_5 or2
            PIN I0 XLXN_18
            PIN I1 TXE_IN
            PIN O TXE_OUT
        END BLOCK
        BEGIN BLOCK XLXI_6 and2b1
            PIN I0 TXE_IN
            PIN I1 XLXN_18
            PIN O XLXN_38
        END BLOCK
        BEGIN BLOCK XLXI_7 srl16e
            PIN A0 XLXN_22
            PIN A1 XLXN_22
            PIN A2 XLXN_23
            PIN A3 XLXN_23
            PIN CE XLXN_36
            PIN CLK BCLK
            PIN D XLXN_25
            PIN Q XLXN_19
        END BLOCK
        BEGIN BLOCK XLXI_8 vcc
            PIN P XLXN_22
        END BLOCK
        BEGIN BLOCK XLXI_9 gnd
            PIN G XLXN_23
        END BLOCK
        BEGIN BLOCK XLXI_10 xor2
            PIN I0 XLXN_29
            PIN I1 XLXN_28
            PIN O XLXN_25
        END BLOCK
        BEGIN BLOCK XLXI_11 and2
            PIN I0 TXE_OUT
            PIN I1 XLXN_19
            PIN O XLXN_28
        END BLOCK
        BEGIN BLOCK XLXI_12 and2
            PIN I0 B_FLD
            PIN I1 D_IN
            PIN O XLXN_29
        END BLOCK
        BEGIN BLOCK XLXI_14 vcc
            PIN P XLXN_33
        END BLOCK
        BEGIN BLOCK XLXI_18 and2
            PIN I0 XLXN_43
            PIN I1 XLXN_42
            PIN O XLXN_49
        END BLOCK
        BEGIN BLOCK XLXI_19 inv
            PIN I B_FLD
            PIN O XLXN_45
        END BLOCK
        BEGIN BLOCK XLXI_20 buf
            PIN I XLXN_49
            PIN O TEST
        END BLOCK
        BEGIN BLOCK XLXI_26 or3b1
            PIN I0 TXE_OUT
            PIN I1 XLXN_49
            PIN I2 XLXN_38
            PIN O XLXN_36
        END BLOCK
        BEGIN BLOCK XLXI_27 cb4ce
            PIN C BCLK
            PIN CE XLXN_33
            PIN CLR XLXN_45
            PIN CEO XLXN_41
            PIN Q0
            PIN Q1
            PIN Q2
            PIN Q3
            PIN TC
        END BLOCK
        BEGIN BLOCK XLXI_28 cb4ce
            PIN C BCLK
            PIN CE XLXN_41
            PIN CLR XLXN_45
            PIN CEO
            PIN Q0 XLXN_42
            PIN Q1 XLXN_43
            PIN Q2
            PIN Q3
            PIN TC
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 3520 2720
        BEGIN BRANCH D_IN
            WIRE 320 320 1312 320
            WIRE 1312 320 2512 320
            WIRE 2512 320 2512 448
            WIRE 2512 448 2560 448
            WIRE 1312 320 1312 1024
            WIRE 1312 1024 1424 1024
        END BRANCH
        BEGIN BRANCH B_FLD
            WIRE 320 960 480 960
            WIRE 480 960 480 1424
            WIRE 480 1424 608 1424
            WIRE 608 1424 1248 1424
            WIRE 608 1424 608 1472
            WIRE 1248 1088 1424 1088
            WIRE 1248 1088 1248 1424
        END BRANCH
        IOMARKER 320 320 D_IN R180 28
        IOMARKER 320 640 TXE_IN R180 28
        IOMARKER 320 960 B_FLD R180 28
        BEGIN BRANCH BCLK
            WIRE 320 1280 544 1280
            WIRE 544 1280 1328 1280
            WIRE 544 1280 544 1904
            WIRE 544 1904 736 1904
            WIRE 544 1904 544 2544
            WIRE 544 2544 736 2544
            WIRE 544 768 544 1280
            WIRE 544 768 800 768
            WIRE 1328 1152 1328 1280
            WIRE 1328 1152 2112 1152
        END BRANCH
        IOMARKER 320 1280 BCLK R180 28
        IOMARKER 3024 800 TXE_OUT R0 28
        BEGIN BRANCH D_OUT
            WIRE 2880 480 3040 480
        END BRANCH
        IOMARKER 3040 480 D_OUT R0 28
        INSTANCE XLXI_1 2560 608 R0
        INSTANCE XLXI_2 800 1152 R0
        INSTANCE XLXI_3 640 752 R0
        INSTANCE XLXI_4 672 1184 R0
        INSTANCE XLXI_5 2624 896 R0
        INSTANCE XLXI_6 1440 672 R0
        BEGIN BRANCH XLXN_18
            WIRE 1184 704 1232 704
            WIRE 1232 704 1232 832
            WIRE 1232 832 2624 832
            WIRE 1232 544 1440 544
            WIRE 1232 544 1232 704
        END BRANCH
        BEGIN BRANCH XLXN_19
            WIRE 2368 720 2544 720
            WIRE 2544 720 2544 1088
            WIRE 2496 1088 2544 1088
            WIRE 2544 512 2560 512
            WIRE 2544 512 2544 720
        END BRANCH
        BEGIN BRANCH XLXN_25
            WIRE 2048 1024 2112 1024
        END BRANCH
        INSTANCE XLXI_7 2112 1536 R0
        BEGIN BRANCH XLXN_22
            WIRE 2016 1264 2016 1280
            WIRE 2016 1280 2080 1280
            WIRE 2080 1280 2112 1280
            WIRE 2080 1216 2112 1216
            WIRE 2080 1216 2080 1280
        END BRANCH
        BEGIN BRANCH XLXN_23
            WIRE 2016 1344 2080 1344
            WIRE 2080 1344 2112 1344
            WIRE 2080 1344 2080 1408
            WIRE 2080 1408 2112 1408
            WIRE 2016 1344 2016 1360
        END BRANCH
        INSTANCE XLXI_9 1952 1488 R0
        INSTANCE XLXI_8 1952 1264 R0
        INSTANCE XLXI_10 1792 1120 R0
        INSTANCE XLXI_11 2368 592 R180
        BEGIN BRANCH XLXN_28
            WIRE 1712 688 1712 992
            WIRE 1712 992 1792 992
            WIRE 1712 688 2112 688
        END BRANCH
        INSTANCE XLXI_12 1424 1152 R0
        BEGIN BRANCH XLXN_29
            WIRE 1680 1056 1792 1056
        END BRANCH
        INSTANCE XLXI_14 608 1792 R0
        BEGIN BRANCH XLXN_33
            WIRE 672 1792 672 1840
            WIRE 672 1840 736 1840
        END BRANCH
        BEGIN BRANCH XLXN_36
            WIRE 1856 1648 1968 1648
            WIRE 1968 1088 1968 1648
            WIRE 1968 1088 2112 1088
        END BRANCH
        BEGIN BRANCH XLXN_41
            WIRE 656 2080 1200 2080
            WIRE 656 2080 656 2480
            WIRE 656 2480 736 2480
            WIRE 1120 1840 1200 1840
            WIRE 1200 1840 1200 2080
        END BRANCH
        INSTANCE XLXI_18 1280 2352 R0
        BEGIN BRANCH XLXN_42
            WIRE 1120 2224 1280 2224
        END BRANCH
        BEGIN BRANCH XLXN_43
            WIRE 1120 2288 1280 2288
        END BRANCH
        INSTANCE XLXI_19 576 1472 R90
        BEGIN BRANCH XLXN_45
            WIRE 608 1696 608 2000
            WIRE 608 2000 736 2000
            WIRE 608 2000 608 2640
            WIRE 608 2640 736 2640
        END BRANCH
        BEGIN BRANCH TXE_IN
            WIRE 320 640 560 640
            WIRE 560 640 800 640
            WIRE 560 480 1280 480
            WIRE 1280 480 1280 608
            WIRE 1280 608 1280 768
            WIRE 1280 768 2624 768
            WIRE 1280 608 1440 608
            WIRE 560 480 560 640
        END BRANCH
        INSTANCE XLXI_20 2656 1872 R0
        BEGIN BRANCH TEST
            WIRE 2880 1840 3040 1840
        END BRANCH
        IOMARKER 3040 1840 TEST R0 28
        BEGIN BRANCH TXE_OUT
            WIRE 1488 1536 2960 1536
            WIRE 1488 1536 1488 1712
            WIRE 1488 1712 1600 1712
            WIRE 2368 656 2960 656
            WIRE 2960 656 2960 800
            WIRE 2960 800 3024 800
            WIRE 2960 800 2960 1536
            WIRE 2880 800 2960 800
        END BRANCH
        BEGIN BRANCH XLXN_38
            WIRE 1536 1440 1760 1440
            WIRE 1536 1440 1536 1584
            WIRE 1536 1584 1600 1584
            WIRE 1696 576 1760 576
            WIRE 1760 576 2560 576
            WIRE 1760 576 1760 1440
        END BRANCH
        INSTANCE XLXI_26 1600 1776 R0
        BEGIN BRANCH XLXN_49
            WIRE 1536 2256 1568 2256
            WIRE 1568 1648 1600 1648
            WIRE 1568 1648 1568 1840
            WIRE 1568 1840 1568 2256
            WIRE 1568 1840 2656 1840
        END BRANCH
        INSTANCE XLXI_27 736 2032 R0
        INSTANCE XLXI_28 736 2672 R0
        BEGIN BRANCH XLXN_11
            WIRE 704 752 704 1024
            WIRE 704 1024 800 1024
        END BRANCH
        BEGIN BRANCH XLXN_14
            WIRE 736 832 800 832
            WIRE 736 832 736 896
            WIRE 736 896 736 960
            WIRE 736 960 736 1056
            WIRE 736 960 800 960
            WIRE 736 896 800 896
        END BRANCH
    END SHEET
END SCHEMATIC
