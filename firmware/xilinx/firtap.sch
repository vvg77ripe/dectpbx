VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL XLXN_1(7:0)
        SIGNAL DI(7:0)
        SIGNAL DO(7:0)
        SIGNAL C(7:0)
        SIGNAL C(0)
        SIGNAL C(1)
        SIGNAL C(2)
        SIGNAL C(3)
        SIGNAL C(4)
        SIGNAL C(5)
        SIGNAL C(6)
        SIGNAL C(7)
        SIGNAL E
        SIGNAL C0
        SIGNAL C1
        SIGNAL C2
        SIGNAL C3
        SIGNAL C4
        SIGNAL C5
        SIGNAL C6
        SIGNAL C7
        SIGNAL DATA
        SIGNAL XLXN_30
        SIGNAL XLXN_32
        SIGNAL CLK
        SIGNAL XLXN_33
        PORT Input DI(7:0)
        PORT Output DO(7:0)
        PORT Input E
        PORT Input C0
        PORT Input C1
        PORT Input C2
        PORT Input C3
        PORT Input C4
        PORT Input C5
        PORT Input C6
        PORT Input C7
        PORT Input DATA
        PORT Input CLK
        BEGIN BLOCKDEF adsu8
            TIMESTAMP 2001 2 2 12 35 41
            LINE N 448 -128 384 -128 
            LINE N 448 -64 384 -64 
            LINE N 240 -64 384 -64 
            LINE N 240 -124 240 -64 
            RECTANGLE N 0 -204 64 -180 
            RECTANGLE N 0 -332 64 -308 
            LINE N 0 -320 64 -320 
            LINE N 0 -192 64 -192 
            LINE N 448 -256 384 -256 
            RECTANGLE N 384 -268 448 -244 
            LINE N 0 -448 64 -448 
            LINE N 128 -448 64 -448 
            LINE N 128 -416 128 -448 
            LINE N 128 -64 48 -64 
            LINE N 128 -96 128 -64 
            LINE N 0 -64 64 -64 
            LINE N 64 -288 64 -432 
            LINE N 128 -256 64 -288 
            LINE N 64 -224 128 -256 
            LINE N 64 -80 64 -224 
            LINE N 384 -160 64 -80 
            LINE N 384 -336 384 -160 
            LINE N 384 -352 384 -336 
            LINE N 64 -432 384 -352 
            LINE N 336 -128 336 -148 
            LINE N 384 -128 336 -128 
        END BLOCKDEF
        BEGIN BLOCKDEF fd8ce
            TIMESTAMP 2001 2 2 12 37 14
            LINE N 0 -128 64 -128 
            LINE N 0 -192 64 -192 
            LINE N 0 -32 64 -32 
            LINE N 0 -256 64 -256 
            LINE N 384 -256 320 -256 
            LINE N 192 -32 64 -32 
            LINE N 192 -64 192 -32 
            LINE N 80 -128 64 -144 
            LINE N 64 -112 80 -128 
            RECTANGLE N 320 -268 384 -244 
            RECTANGLE N 0 -268 64 -244 
            RECTANGLE N 64 -320 320 -64 
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
        BEGIN BLOCKDEF inv
            TIMESTAMP 2001 2 2 12 38 38
            LINE N 0 -32 64 -32 
            LINE N 224 -32 160 -32 
            LINE N 64 -64 128 -32 
            LINE N 128 -32 64 0 
            LINE N 64 0 64 -64 
            CIRCLE N 128 -48 160 -16 
        END BLOCKDEF
        BEGIN BLOCK XLXI_1 adsu8
            PIN A(7:0) DI(7:0)
            PIN ADD DATA
            PIN B(7:0) C(7:0)
            PIN CI XLXN_33
            PIN CO
            PIN OFL
            PIN S(7:0) XLXN_1(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_2 fd8ce
            PIN C CLK
            PIN CE XLXN_30
            PIN CLR XLXN_32
            PIN D(7:0) XLXN_1(7:0)
            PIN Q(7:0) DO(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_3 and2
            PIN I0 E
            PIN I1 C0
            PIN O C(0)
        END BLOCK
        BEGIN BLOCK XLXI_4 and2
            PIN I0 E
            PIN I1 C1
            PIN O C(1)
        END BLOCK
        BEGIN BLOCK XLXI_5 and2
            PIN I0 E
            PIN I1 C2
            PIN O C(2)
        END BLOCK
        BEGIN BLOCK XLXI_6 and2
            PIN I0 E
            PIN I1 C3
            PIN O C(3)
        END BLOCK
        BEGIN BLOCK XLXI_7 and2
            PIN I0 E
            PIN I1 C4
            PIN O C(4)
        END BLOCK
        BEGIN BLOCK XLXI_8 and2
            PIN I0 E
            PIN I1 C5
            PIN O C(5)
        END BLOCK
        BEGIN BLOCK XLXI_9 and2
            PIN I0 E
            PIN I1 C6
            PIN O C(6)
        END BLOCK
        BEGIN BLOCK XLXI_10 and2
            PIN I0 E
            PIN I1 C7
            PIN O C(7)
        END BLOCK
        BEGIN BLOCK XLXI_11 vcc
            PIN P XLXN_30
        END BLOCK
        BEGIN BLOCK XLXI_12 gnd
            PIN G XLXN_32
        END BLOCK
        BEGIN BLOCK XLXI_13 inv
            PIN I DATA
            PIN O XLXN_33
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 3520 2720
        INSTANCE XLXI_1 1280 1440 R0
        INSTANCE XLXI_2 2080 1440 R0
        BEGIN BRANCH XLXN_1(7:0)
            WIRE 1728 1184 2080 1184
        END BRANCH
        BEGIN BRANCH DI(7:0)
            WIRE 480 1120 1280 1120
        END BRANCH
        BEGIN BRANCH DO(7:0)
            WIRE 2464 1184 2720 1184
        END BRANCH
        IOMARKER 2720 1184 DO(7:0) R0 28
        BUSTAP 1200 1280 1104 1280
        INSTANCE XLXI_3 704 1376 R0
        INSTANCE XLXI_4 704 1536 R0
        INSTANCE XLXI_5 704 1696 R0
        INSTANCE XLXI_6 704 1856 R0
        INSTANCE XLXI_7 704 2016 R0
        INSTANCE XLXI_8 704 2176 R0
        INSTANCE XLXI_9 704 2336 R0
        INSTANCE XLXI_10 704 2496 R0
        BUSTAP 1200 1440 1104 1440
        BUSTAP 1200 1600 1104 1600
        BUSTAP 1200 1760 1104 1760
        BUSTAP 1200 1920 1104 1920
        BUSTAP 1200 2080 1104 2080
        BUSTAP 1200 2240 1104 2240
        BUSTAP 1200 2400 1104 2400
        BEGIN BRANCH C(7:0)
            WIRE 1200 1248 1280 1248
            WIRE 1200 1248 1200 1280
            WIRE 1200 1280 1200 1440
            WIRE 1200 1440 1200 1600
            WIRE 1200 1600 1200 1760
            WIRE 1200 1760 1200 1920
            WIRE 1200 1920 1200 2080
            WIRE 1200 2080 1200 2240
            WIRE 1200 2240 1200 2400
        END BRANCH
        BEGIN BRANCH C(0)
            WIRE 960 1280 1104 1280
        END BRANCH
        BEGIN BRANCH C(1)
            WIRE 960 1440 1104 1440
        END BRANCH
        BEGIN BRANCH C(2)
            WIRE 960 1600 1104 1600
        END BRANCH
        BEGIN BRANCH C(3)
            WIRE 960 1760 1104 1760
        END BRANCH
        BEGIN BRANCH C(4)
            WIRE 960 1920 1104 1920
        END BRANCH
        BEGIN BRANCH C(5)
            WIRE 960 2080 1104 2080
        END BRANCH
        BEGIN BRANCH C(6)
            WIRE 960 2240 1104 2240
        END BRANCH
        BEGIN BRANCH C(7)
            WIRE 960 2400 1104 2400
        END BRANCH
        BEGIN BRANCH E
            WIRE 480 960 640 960
            WIRE 640 960 640 1312
            WIRE 640 1312 704 1312
            WIRE 640 1312 640 1472
            WIRE 640 1472 704 1472
            WIRE 640 1472 640 1632
            WIRE 640 1632 704 1632
            WIRE 640 1632 640 1792
            WIRE 640 1792 704 1792
            WIRE 640 1792 640 1952
            WIRE 640 1952 704 1952
            WIRE 640 1952 640 2112
            WIRE 640 2112 704 2112
            WIRE 640 2112 640 2272
            WIRE 640 2272 704 2272
            WIRE 640 2272 640 2432
            WIRE 640 2432 704 2432
        END BRANCH
        IOMARKER 480 1120 DI(7:0) R180 28
        BEGIN BRANCH C0
            WIRE 480 1248 704 1248
        END BRANCH
        BEGIN BRANCH C1
            WIRE 480 1408 704 1408
        END BRANCH
        BEGIN BRANCH C2
            WIRE 480 1568 704 1568
        END BRANCH
        BEGIN BRANCH C3
            WIRE 480 1728 704 1728
        END BRANCH
        BEGIN BRANCH C4
            WIRE 480 1888 704 1888
        END BRANCH
        BEGIN BRANCH C5
            WIRE 480 2048 704 2048
        END BRANCH
        BEGIN BRANCH C6
            WIRE 480 2208 704 2208
        END BRANCH
        BEGIN BRANCH C7
            WIRE 480 2368 704 2368
        END BRANCH
        IOMARKER 480 1248 C0 R180 28
        IOMARKER 480 1408 C1 R180 28
        IOMARKER 480 1568 C2 R180 28
        IOMARKER 480 1728 C3 R180 28
        IOMARKER 480 1888 C4 R180 28
        IOMARKER 480 2048 C5 R180 28
        IOMARKER 480 2208 C6 R180 28
        IOMARKER 480 2368 C7 R180 28
        IOMARKER 480 960 E R180 28
        IOMARKER 480 880 DATA R180 28
        INSTANCE XLXI_11 1936 1056 R0
        BEGIN BRANCH XLXN_30
            WIRE 2000 1056 2000 1248
            WIRE 2000 1248 2080 1248
        END BRANCH
        INSTANCE XLXI_12 1856 1680 R0
        BEGIN BRANCH CLK
            WIRE 480 2560 2000 2560
            WIRE 2000 1312 2080 1312
            WIRE 2000 1312 2000 2560
        END BRANCH
        IOMARKER 480 2560 CLK R180 28
        BEGIN BRANCH XLXN_32
            WIRE 1920 1408 2080 1408
            WIRE 1920 1408 1920 1552
        END BRANCH
        BEGIN BRANCH DATA
            WIRE 480 880 992 880
            WIRE 992 880 992 992
            WIRE 992 992 992 1376
            WIRE 992 1376 1280 1376
            WIRE 992 992 1024 992
        END BRANCH
        INSTANCE XLXI_13 1024 1024 R0
        BEGIN BRANCH XLXN_33
            WIRE 1248 992 1280 992
        END BRANCH
    END SHEET
END SCHEMATIC
