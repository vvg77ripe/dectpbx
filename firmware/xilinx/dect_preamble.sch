VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL XLXN_1
        SIGNAL XLXN_2
        SIGNAL XLXN_3
        SIGNAL XLXN_4
        SIGNAL XLXN_5
        SIGNAL XLXN_6
        SIGNAL XLXN_7
        SIGNAL XLXN_8
        SIGNAL XLXN_9
        SIGNAL XLXN_10
        SIGNAL XLXN_11
        SIGNAL XLXN_12
        SIGNAL XLXN_13
        SIGNAL XLXN_14
        SIGNAL XLXN_15
        SIGNAL XLXN_16
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
        BEGIN BLOCK XLXI_1 xor2
            PIN I0
            PIN I1 XLXN_2
            PIN O
        END BLOCK
        BEGIN BLOCK XLXI_2 xor2
            PIN I0
            PIN I1 XLXN_2
            PIN O
        END BLOCK
        BEGIN BLOCK XLXI_3 xor2
            PIN I0
            PIN I1 XLXN_2
            PIN O
        END BLOCK
        BEGIN BLOCK XLXI_4 xor2
            PIN I0
            PIN I1 XLXN_2
            PIN O
        END BLOCK
        BEGIN BLOCK XLXI_5 xor2
            PIN I0
            PIN I1 XLXN_2
            PIN O
        END BLOCK
        BEGIN BLOCK XLXI_6 xor2
            PIN I0
            PIN I1 XLXN_2
            PIN O
        END BLOCK
        BEGIN BLOCK XLXI_7 xor2
            PIN I0
            PIN I1 XLXN_2
            PIN O
        END BLOCK
        BEGIN BLOCK XLXI_8 xor2
            PIN I0
            PIN I1 XLXN_2
            PIN O
        END BLOCK
        BEGIN BLOCK XLXI_9 xor2
            PIN I0
            PIN I1 XLXN_2
            PIN O
        END BLOCK
        BEGIN BLOCK XLXI_10 xor2
            PIN I0
            PIN I1 XLXN_2
            PIN O
        END BLOCK
        BEGIN BLOCK XLXI_11 xor2
            PIN I0
            PIN I1 XLXN_2
            PIN O
        END BLOCK
        BEGIN BLOCK XLXI_12 xor2
            PIN I0
            PIN I1 XLXN_2
            PIN O
        END BLOCK
        BEGIN BLOCK XLXI_13 xor2
            PIN I0
            PIN I1 XLXN_2
            PIN O
        END BLOCK
        BEGIN BLOCK XLXI_14 xor2
            PIN I0
            PIN I1 XLXN_2
            PIN O
        END BLOCK
        BEGIN BLOCK XLXI_15 xor2
            PIN I0
            PIN I1 XLXN_2
            PIN O
        END BLOCK
        BEGIN BLOCK XLXI_16 xor2
            PIN I0
            PIN I1 XLXN_2
            PIN O
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 3520 2720
        INSTANCE XLXI_1 800 288 R0
        INSTANCE XLXI_2 800 448 R0
        INSTANCE XLXI_3 800 608 R0
        INSTANCE XLXI_4 800 768 R0
        INSTANCE XLXI_5 800 928 R0
        INSTANCE XLXI_6 800 1088 R0
        INSTANCE XLXI_7 800 1248 R0
        INSTANCE XLXI_8 800 1408 R0
        INSTANCE XLXI_9 800 1568 R0
        INSTANCE XLXI_10 800 1728 R0
        INSTANCE XLXI_11 800 1888 R0
        INSTANCE XLXI_12 800 2048 R0
        INSTANCE XLXI_13 800 2208 R0
        INSTANCE XLXI_14 800 2368 R0
        INSTANCE XLXI_15 800 2528 R0
        INSTANCE XLXI_16 800 2688 R0
        BEGIN BRANCH XLXN_2
            WIRE 320 160 720 160
            WIRE 720 160 800 160
            WIRE 720 160 720 320
            WIRE 720 320 800 320
            WIRE 720 320 720 480
            WIRE 720 480 800 480
            WIRE 720 480 720 640
            WIRE 720 640 800 640
            WIRE 720 640 720 800
            WIRE 720 800 800 800
            WIRE 720 800 720 960
            WIRE 720 960 800 960
            WIRE 720 960 720 1120
            WIRE 720 1120 800 1120
            WIRE 720 1120 720 1280
            WIRE 720 1280 800 1280
            WIRE 720 1280 720 1440
            WIRE 720 1440 800 1440
            WIRE 720 1440 720 1600
            WIRE 720 1600 800 1600
            WIRE 720 1600 720 1760
            WIRE 720 1760 800 1760
            WIRE 720 1760 720 1920
            WIRE 720 1920 800 1920
            WIRE 720 1920 720 2080
            WIRE 720 2080 800 2080
            WIRE 720 2080 720 2240
            WIRE 720 2240 800 2240
            WIRE 720 2240 720 2400
            WIRE 720 2400 800 2400
            WIRE 720 2400 720 2560
            WIRE 720 2560 800 2560
        END BRANCH
    END SHEET
END SCHEMATIC
