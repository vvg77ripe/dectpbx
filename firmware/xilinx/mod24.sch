VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL O0
        SIGNAL O1
        SIGNAL O2
        SIGNAL O3
        SIGNAL O4
        SIGNAL I0
        SIGNAL I1
        SIGNAL I2
        SIGNAL I3
        SIGNAL I4
        SIGNAL XLXN_11
        SIGNAL XLXN_12
        SIGNAL XLXN_13
        SIGNAL XLXN_14
        SIGNAL XLXN_15
        SIGNAL XLXN_16
        SIGNAL XLXN_17
        SIGNAL XLXN_18
        SIGNAL XLXN_19
        SIGNAL XLXN_20
        SIGNAL XLXN_21
        SIGNAL XLXN_22
        SIGNAL XLXN_23
        SIGNAL XLXN_24
        PORT Output O0
        PORT Output O1
        PORT Output O2
        PORT Output O3
        PORT Output O4
        PORT Input I0
        PORT Input I1
        PORT Input I2
        PORT Input I3
        PORT Input I4
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
        BEGIN BLOCKDEF nand5b3
            TIMESTAMP 2001 2 2 12 38 38
            LINE N 0 -64 40 -64 
            CIRCLE N 40 -76 64 -52 
            LINE N 0 -128 40 -128 
            CIRCLE N 40 -140 64 -116 
            LINE N 0 -192 40 -192 
            CIRCLE N 40 -204 64 -180 
            LINE N 0 -256 64 -256 
            LINE N 0 -320 64 -320 
            LINE N 256 -192 216 -192 
            CIRCLE N 192 -204 216 -180 
            LINE N 144 -144 64 -144 
            LINE N 64 -240 144 -240 
            LINE N 64 -64 64 -320 
            ARC N 96 -240 192 -144 144 -144 144 -240 
        END BLOCKDEF
        BEGIN BLOCK XLXI_1 and2
            PIN I0 XLXN_20
            PIN I1 I0
            PIN O O0
        END BLOCK
        BEGIN BLOCK XLXI_2 and2
            PIN I0 XLXN_20
            PIN I1 I1
            PIN O O1
        END BLOCK
        BEGIN BLOCK XLXI_3 and2
            PIN I0 XLXN_20
            PIN I1 I2
            PIN O O2
        END BLOCK
        BEGIN BLOCK XLXI_4 and2
            PIN I0 XLXN_20
            PIN I1 I3
            PIN O O3
        END BLOCK
        BEGIN BLOCK XLXI_5 and2
            PIN I0 XLXN_20
            PIN I1 I4
            PIN O O4
        END BLOCK
        BEGIN BLOCK XLXI_7 nand5b3
            PIN I0 I0
            PIN I1 I1
            PIN I2 I2
            PIN I3 I3
            PIN I4 I4
            PIN O XLXN_20
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 3520 2720
        INSTANCE XLXI_1 1760 1248 R0
        INSTANCE XLXI_2 1760 1408 R0
        INSTANCE XLXI_3 1760 1568 R0
        INSTANCE XLXI_4 1760 1728 R0
        INSTANCE XLXI_5 1760 1888 R0
        BEGIN BRANCH O0
            WIRE 2016 1152 2240 1152
        END BRANCH
        BEGIN BRANCH O1
            WIRE 2016 1312 2240 1312
        END BRANCH
        BEGIN BRANCH O2
            WIRE 2016 1472 2240 1472
        END BRANCH
        BEGIN BRANCH O3
            WIRE 2016 1632 2240 1632
        END BRANCH
        BEGIN BRANCH O4
            WIRE 2016 1792 2240 1792
        END BRANCH
        IOMARKER 2240 1152 O0 R0 28
        IOMARKER 2240 1312 O1 R0 28
        IOMARKER 2240 1472 O2 R0 28
        IOMARKER 2240 1632 O3 R0 28
        IOMARKER 2240 1792 O4 R0 28
        IOMARKER 1280 1120 I0 R180 28
        IOMARKER 1280 1280 I1 R180 28
        IOMARKER 1280 1440 I2 R180 28
        IOMARKER 1280 1600 I3 R180 28
        IOMARKER 1280 1760 I4 R180 28
        BEGIN BRANCH XLXN_20
            WIRE 1680 1184 1760 1184
            WIRE 1680 1184 1680 1344
            WIRE 1680 1344 1760 1344
            WIRE 1680 1344 1680 1504
            WIRE 1680 1504 1760 1504
            WIRE 1680 1504 1680 1664
            WIRE 1680 1664 1760 1664
            WIRE 1680 1664 1680 1824
            WIRE 1680 1824 1760 1824
            WIRE 1680 1824 1680 1920
            WIRE 1680 1920 2064 1920
            WIRE 2064 1920 2064 2128
            WIRE 1856 2128 2064 2128
        END BRANCH
        INSTANCE XLXI_7 1600 2320 R0
        BEGIN BRANCH I1
            WIRE 1280 1280 1520 1280
            WIRE 1520 1280 1760 1280
            WIRE 1520 1280 1520 1312
            WIRE 1520 1312 1520 2192
            WIRE 1520 2192 1600 2192
        END BRANCH
        BEGIN BRANCH I0
            WIRE 1280 1120 1504 1120
            WIRE 1504 1120 1760 1120
            WIRE 1504 1120 1504 2256
            WIRE 1504 2256 1600 2256
        END BRANCH
        BEGIN BRANCH I4
            WIRE 1280 1760 1568 1760
            WIRE 1568 1760 1760 1760
            WIRE 1568 1760 1568 2000
            WIRE 1568 2000 1600 2000
        END BRANCH
        BEGIN BRANCH I3
            WIRE 1280 1600 1552 1600
            WIRE 1552 1600 1760 1600
            WIRE 1552 1600 1552 2064
            WIRE 1552 2064 1600 2064
        END BRANCH
        BEGIN BRANCH I2
            WIRE 1280 1440 1536 1440
            WIRE 1536 1440 1760 1440
            WIRE 1536 1440 1536 2128
            WIRE 1536 2128 1600 2128
        END BRANCH
    END SHEET
END SCHEMATIC
