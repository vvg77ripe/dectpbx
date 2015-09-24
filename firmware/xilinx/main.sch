VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        BEGIN SIGNAL D0
            BEGIN ATTR LOC "P48"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL D1
            BEGIN ATTR LOC "P47"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL D2
            BEGIN ATTR LOC "P44"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL D3
            BEGIN ATTR LOC "P43"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL D4
            BEGIN ATTR LOC "P35"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL D5
            BEGIN ATTR LOC "P34"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL D6
            BEGIN ATTR LOC "P32"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL D7
            BEGIN ATTR LOC "P30"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        SIGNAL OE
        SIGNAL DIN(7:0)
        SIGNAL DIN(0)
        SIGNAL DIN(1)
        SIGNAL DIN(2)
        SIGNAL DIN(3)
        SIGNAL DIN(4)
        SIGNAL DIN(5)
        SIGNAL DIN(6)
        SIGNAL DIN(7)
        SIGNAL DOUT(7:0)
        SIGNAL DOUT(0)
        SIGNAL DOUT(1)
        SIGNAL DOUT(2)
        SIGNAL DOUT(3)
        SIGNAL DOUT(4)
        SIGNAL DOUT(5)
        SIGNAL DOUT(6)
        SIGNAL DOUT(7)
        BEGIN SIGNAL CS
            BEGIN ATTR LOC "P50"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL WR
            BEGIN ATTR LOC "P27"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        SIGNAL XLXN_48(7:0)
        SIGNAL XLXN_50
        BEGIN SIGNAL A0
            BEGIN ATTR LOC "P23"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL A1
            BEGIN ATTR LOC "P22"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL A2
            BEGIN ATTR LOC "P21"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        SIGNAL IOADDR(7:0)
        SIGNAL REG3
        SIGNAL XLXN_69(7:0)
        BEGIN SIGNAL CLK
            BEGIN ATTR LOC "P38"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL FRAME
            BEGIN ATTR LOC "P1"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        SIGNAL BYTE
        SIGNAL XLXN_75
        SIGNAL RXADDR(7:0)
        SIGNAL RXADDR(10:0)
        SIGNAL RXADDR(8)
        SIGNAL RXADDR(9)
        SIGNAL RXADDR(10)
        SIGNAL RXDATA(7:0)
        SIGNAL XLXN_86
        SIGNAL XLXN_87
        SIGNAL IOADDR(10:0)
        SIGNAL IOADDR(8)
        SIGNAL IOADDR(9)
        SIGNAL IOADDR(10)
        SIGNAL REG6
        SIGNAL XLXN_104(7:0)
        SIGNAL XLXN_106(7:0)
        SIGNAL DIP(0:0)
        SIGNAL XLXN_109
        SIGNAL REG7
        SIGNAL XLXN_115
        SIGNAL XLXN_117(7:0)
        SIGNAL STAT(7:0)
        SIGNAL STAT(7)
        SIGNAL STAT(6)
        SIGNAL STAT(5)
        SIGNAL STAT(4)
        SIGNAL STAT(3)
        SIGNAL STAT(2)
        SIGNAL STAT(1)
        SIGNAL STAT(0)
        SIGNAL XLXN_131
        BEGIN SIGNAL REFCLK
            BEGIN ATTR LOC "P81"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        SIGNAL TXAD(10:0)
        SIGNAL XLXN_245
        SIGNAL XLXN_246
        SIGNAL XLXN_250
        SIGNAL PKTADR(10:0)
        SIGNAL PKTADR(0)
        SIGNAL PKTADR(1)
        SIGNAL PKTADR(2)
        SIGNAL PKTADR(3)
        SIGNAL PKTADR(4)
        SIGNAL PKTADR(5)
        SIGNAL PKTCNT(7:0)
        SIGNAL PKTCNT(0)
        SIGNAL PKTCNT(1)
        SIGNAL PKTCNT(2)
        SIGNAL PKTCNT(3)
        SIGNAL PKTCNT(4)
        SIGNAL PKTCNT(5)
        SIGNAL PRE(7:0)
        SIGNAL XLXN_290
        SIGNAL PKTBASE(7:0)
        SIGNAL PKTADR(10)
        SIGNAL PKTADR(9)
        SIGNAL PKTADR(8)
        SIGNAL PKTADR(7)
        SIGNAL PKTADR(6)
        SIGNAL PKTBASE(0)
        SIGNAL PKTBASE(1)
        SIGNAL PKTBASE(2)
        SIGNAL PKTBASE(3)
        SIGNAL PKTBASE(4)
        SIGNAL WRITE
        SIGNAL XLXN_310
        SIGNAL XLXN_315(7:0)
        SIGNAL XLXN_317(0:0)
        SIGNAL XLXN_324
        SIGNAL PRE(7)
        SIGNAL PRE(6)
        SIGNAL PRE(5)
        SIGNAL PRE(4)
        SIGNAL PRE(3)
        SIGNAL PRE(2)
        SIGNAL PRE(1)
        SIGNAL PRE(0)
        SIGNAL XLXN_342
        SIGNAL XLXN_377(7:0)
        SIGNAL XLXN_378
        SIGNAL XLXN_379
        SIGNAL XLXN_380
        SIGNAL XLXN_381
        SIGNAL XLXN_406
        SIGNAL REG7READ
        BEGIN SIGNAL TXD4
            BEGIN ATTR LOC "P89"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL TXD3
            BEGIN ATTR LOC "P90"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL TXD2
            BEGIN ATTR LOC "P91"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL TXD1
            BEGIN ATTR LOC "P92"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL TXD0
            BEGIN ATTR LOC "P96"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL TXEN
            BEGIN ATTR LOC "P79"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL PLLD
            BEGIN ATTR LOC "P85"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL MCLK
            BEGIN ATTR LOC "P88"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL MDATA
            BEGIN ATTR LOC "P87"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL ML
            BEGIN ATTR LOC "P86"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        BEGIN SIGNAL RXD
            BEGIN ATTR LOC "P80"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        SIGNAL XLXN_458
        BEGIN SIGNAL XLXN_463
            BEGIN ATTR LOC "P75"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        SIGNAL XLXN_464
        SIGNAL XLXN_465
        SIGNAL XLXN_466
        SIGNAL XLXN_467
        SIGNAL SN(7:0)
        SIGNAL SN(0)
        SIGNAL SN(1)
        SIGNAL SN(2)
        SIGNAL SN(3)
        SIGNAL SN(4)
        SIGNAL SN(5)
        SIGNAL SN(6)
        SIGNAL SN(7)
        SIGNAL XLXN_477
        SIGNAL XLXN_485
        SIGNAL XLXN_486
        SIGNAL XLXN_487
        SIGNAL XLXN_490
        SIGNAL XLXN_491
        SIGNAL XLXN_492
        SIGNAL XLXN_495
        BEGIN SIGNAL SNIFF
            BEGIN ATTR LOC "P14"
                VERILOG all:0 wsynth:1
                VHDL all:0 wa:1 wd:1
            END ATTR
        END SIGNAL
        SIGNAL XLXN_499
        PORT BiDirectional D0
        PORT BiDirectional D1
        PORT BiDirectional D2
        PORT BiDirectional D3
        PORT BiDirectional D4
        PORT BiDirectional D5
        PORT BiDirectional D6
        PORT BiDirectional D7
        PORT Input CS
        PORT Input WR
        PORT Input A0
        PORT Input A1
        PORT Input A2
        PORT Input CLK
        PORT Output FRAME
        PORT Output REFCLK
        PORT Output TXD4
        PORT Output TXD3
        PORT Output TXD2
        PORT Output TXD1
        PORT Output TXD0
        PORT Output TXEN
        PORT Output PLLD
        PORT Output MCLK
        PORT Output MDATA
        PORT Output ML
        PORT Input RXD
        PORT Output XLXN_463
        PORT Input SNIFF
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
        BEGIN BLOCKDEF iobuf
            TIMESTAMP 2001 11 14 15 13 3
            LINE N 224 -128 128 -128 
            LINE N 160 -64 128 -64 
            LINE N 160 -128 160 -64 
            LINE N 0 -64 64 -64 
            LINE N 96 -140 96 -192 
            LINE N 0 -192 96 -192 
            LINE N 64 -96 64 -160 
            LINE N 128 -128 64 -96 
            LINE N 64 -160 128 -128 
            LINE N 128 -96 128 -32 
            LINE N 64 -64 128 -96 
            LINE N 128 -32 64 -64 
            LINE N 0 -128 64 -128 
        END BLOCKDEF
        BEGIN BLOCKDEF nand2b1
            TIMESTAMP 2001 2 2 12 38 38
            LINE N 0 -64 40 -64 
            CIRCLE N 40 -76 64 -52 
            LINE N 0 -128 64 -128 
            LINE N 256 -96 216 -96 
            CIRCLE N 192 -108 216 -84 
            LINE N 64 -48 64 -144 
            LINE N 64 -144 144 -144 
            LINE N 144 -48 64 -48 
            ARC N 96 -144 192 -48 144 -48 144 -144 
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
        BEGIN BLOCKDEF BUSAND2
            TIMESTAMP 2005 12 27 17 36 21
            RECTANGLE N 0 20 64 44 
            LINE N 64 32 0 32 
            RECTANGLE N 320 20 384 44 
            LINE N 320 32 384 32 
            LINE N 64 -32 0 -32 
            RECTANGLE N 64 -80 320 80 
            LINE N 384 -32 320 -32 
            RECTANGLE N 320 -44 384 -20 
        END BLOCKDEF
        BEGIN BLOCKDEF d3_8e
            TIMESTAMP 2001 2 2 12 36 51
            LINE N 0 -576 64 -576 
            LINE N 0 -512 64 -512 
            LINE N 0 -448 64 -448 
            LINE N 384 -576 320 -576 
            LINE N 384 -512 320 -512 
            LINE N 384 -448 320 -448 
            LINE N 384 -384 320 -384 
            LINE N 384 -320 320 -320 
            LINE N 384 -256 320 -256 
            LINE N 384 -192 320 -192 
            LINE N 384 -128 320 -128 
            RECTANGLE N 64 -640 320 -64 
            LINE N 0 -128 64 -128 
        END BLOCKDEF
        BEGIN BLOCKDEF busgnd
            TIMESTAMP 2005 12 27 21 45 38
            RECTANGLE N 64 -64 192 0 
            RECTANGLE N 0 -44 64 -20 
            LINE N 64 -32 0 -32 
        END BLOCKDEF
        BEGIN BLOCKDEF dect_rx
            TIMESTAMP 2006 1 7 17 11 52
            RECTANGLE N 64 -320 320 0 
            LINE N 64 -288 0 -288 
            LINE N 64 -224 0 -224 
            LINE N 64 -160 0 -160 
            LINE N 64 -96 0 -96 
            LINE N 320 -288 384 -288 
            RECTANGLE N 320 -300 384 -276 
            LINE N 320 -224 384 -224 
            RECTANGLE N 320 -236 384 -212 
            LINE N 320 -160 384 -160 
            LINE N 320 -96 384 -96 
            LINE N 320 -32 384 -32 
        END BLOCKDEF
        BEGIN BLOCKDEF ramb16_s9_s9
            TIMESTAMP 2001 2 2 12 39 16
            RECTANGLE N 544 -960 608 -928 
            LINE N 64 -1152 64 -640 
            RECTANGLE N 0 -1104 64 -1072 
            RECTANGLE N 544 -880 608 -848 
            LINE N 128 -640 64 -640 
            LINE N 128 -576 128 -640 
            LINE N 64 -576 128 -576 
            LINE N 64 -64 64 -576 
            LINE N 544 -64 64 -64 
            LINE N 544 -576 544 -64 
            LINE N 480 -576 544 -576 
            LINE N 480 -640 480 -576 
            LINE N 544 -640 480 -640 
            LINE N 544 -1152 64 -1152 
            LINE N 544 -640 544 -1152 
            RECTANGLE N 544 -368 608 -336 
            RECTANGLE N 0 -144 64 -112 
            RECTANGLE N 0 -208 64 -176 
            LINE N 80 -832 64 -848 
            LINE N 64 -816 80 -832 
            RECTANGLE N 0 -720 64 -688 
            RECTANGLE N 0 -784 64 -752 
            RECTANGLE N 0 -272 64 -240 
            LINE N 80 -320 64 -336 
            LINE N 64 -304 80 -320 
            RECTANGLE N 544 -432 608 -400 
            LINE N 608 -944 544 -944 
            LINE N 0 -1088 64 -1088 
            LINE N 608 -864 544 -864 
            LINE N 0 -704 64 -704 
            LINE N 0 -768 64 -768 
            LINE N 0 -128 64 -128 
            LINE N 608 -352 544 -352 
            LINE N 608 -416 544 -416 
            LINE N 0 -192 64 -192 
            LINE N 0 -1024 64 -1024 
            LINE N 0 -256 64 -256 
            LINE N 0 -320 64 -320 
            LINE N 0 -384 64 -384 
            LINE N 0 -448 64 -448 
            LINE N 0 -512 64 -512 
            LINE N 0 -832 64 -832 
            LINE N 0 -896 64 -896 
            LINE N 0 -960 64 -960 
        END BLOCKDEF
        BEGIN BLOCKDEF cb8cle
            TIMESTAMP 2001 2 2 12 36 39
            RECTANGLE N 64 -448 320 -64 
            LINE N 0 -192 64 -192 
            LINE N 192 -32 64 -32 
            LINE N 192 -64 192 -32 
            LINE N 80 -128 64 -144 
            LINE N 64 -112 80 -128 
            LINE N 0 -128 64 -128 
            LINE N 0 -32 64 -32 
            LINE N 0 -256 64 -256 
            LINE N 0 -384 64 -384 
            RECTANGLE N 0 -396 64 -372 
            LINE N 384 -384 320 -384 
            LINE N 384 -192 320 -192 
            RECTANGLE N 320 -396 384 -372 
            LINE N 384 -128 320 -128 
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
        BEGIN BLOCKDEF fdc_1
            TIMESTAMP 2001 2 2 12 37 14
            LINE N 0 -128 40 -128 
            CIRCLE N 40 -140 64 -116 
            LINE N 64 -112 80 -128 
            LINE N 80 -128 64 -144 
            LINE N 384 -256 320 -256 
            LINE N 0 -256 64 -256 
            LINE N 0 -32 64 -32 
            RECTANGLE N 64 -320 320 -64 
            LINE N 192 -64 192 -32 
            LINE N 192 -32 64 -32 
        END BLOCKDEF
        BEGIN BLOCKDEF buf
            TIMESTAMP 2001 2 2 12 35 54
            LINE N 0 -32 64 -32 
            LINE N 224 -32 128 -32 
            LINE N 64 0 128 -32 
            LINE N 128 -32 64 -64 
            LINE N 64 -64 64 0 
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
        BEGIN BLOCKDEF dect_sync
            TIMESTAMP 2006 2 27 23 32 47
            RECTANGLE N 64 -768 320 0 
            LINE N 64 -736 0 -736 
            LINE N 320 -736 384 -736 
            LINE N 320 -672 384 -672 
            LINE N 320 -608 384 -608 
            LINE N 320 -544 384 -544 
            RECTANGLE N 320 -556 384 -532 
            LINE N 320 -480 384 -480 
            LINE N 320 -416 384 -416 
            LINE N 320 -352 384 -352 
            LINE N 320 -288 384 -288 
            LINE N 320 -224 384 -224 
            LINE N 320 -160 384 -160 
            LINE N 320 -96 384 -96 
            LINE N 320 -32 384 -32 
        END BLOCKDEF
        BEGIN BLOCKDEF and5b2
            TIMESTAMP 2001 2 2 12 38 38
            LINE N 144 -144 64 -144 
            ARC N 96 -240 192 -144 144 -144 144 -240 
            LINE N 64 -240 144 -240 
            LINE N 64 -64 64 -320 
            LINE N 256 -192 192 -192 
            LINE N 0 -320 64 -320 
            LINE N 0 -256 64 -256 
            LINE N 0 -192 64 -192 
            LINE N 0 -128 40 -128 
            CIRCLE N 40 -140 64 -116 
            LINE N 0 -64 40 -64 
            CIRCLE N 40 -76 64 -52 
        END BLOCKDEF
        BEGIN BLOCKDEF dect_tx
            TIMESTAMP 2006 2 5 20 50 53
            LINE N 320 32 384 32 
            LINE N 64 -672 0 -672 
            LINE N 64 -608 0 -608 
            RECTANGLE N 0 -620 64 -596 
            LINE N 64 -544 0 -544 
            LINE N 64 -480 0 -480 
            LINE N 64 -416 0 -416 
            LINE N 64 -352 0 -352 
            LINE N 64 -288 0 -288 
            LINE N 64 -224 0 -224 
            RECTANGLE N 0 -236 64 -212 
            LINE N 320 -672 384 -672 
            LINE N 320 -608 384 -608 
            LINE N 320 -544 384 -544 
            LINE N 320 -480 384 -480 
            LINE N 320 -416 384 -416 
            LINE N 320 -352 384 -352 
            LINE N 320 -288 384 -288 
            LINE N 320 -224 384 -224 
            LINE N 320 -160 384 -160 
            LINE N 320 -96 384 -96 
            LINE N 320 -32 384 -32 
            RECTANGLE N 64 -704 320 64 
        END BLOCKDEF
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
        BEGIN BLOCKDEF fd
            TIMESTAMP 2001 2 2 12 37 14
            RECTANGLE N 64 -320 320 -64 
            LINE N 0 -128 64 -128 
            LINE N 0 -256 64 -256 
            LINE N 384 -256 320 -256 
            LINE N 80 -128 64 -144 
            LINE N 64 -112 80 -128 
        END BLOCKDEF
        BEGIN BLOCKDEF ftc
            TIMESTAMP 2001 2 2 12 37 14
            RECTANGLE N 64 -320 320 -64 
            LINE N 192 -32 64 -32 
            LINE N 192 -64 192 -32 
            LINE N 80 -128 64 -144 
            LINE N 64 -112 80 -128 
            LINE N 384 -256 320 -256 
            LINE N 0 -256 64 -256 
            LINE N 0 -32 64 -32 
            LINE N 0 -128 64 -128 
        END BLOCKDEF
        BEGIN BLOCKDEF fd_1
            TIMESTAMP 2001 2 2 12 37 14
            LINE N 0 -128 40 -128 
            CIRCLE N 40 -140 64 -116 
            LINE N 0 -256 64 -256 
            LINE N 384 -256 320 -256 
            RECTANGLE N 64 -320 320 -64 
            LINE N 64 -112 80 -128 
            LINE N 80 -128 64 -144 
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
        BEGIN BLOCK XLXI_50 iobuf
            PIN I DOUT(0)
            PIN IO D0
            PIN O DIN(0)
            PIN T OE
        END BLOCK
        BEGIN BLOCK XLXI_51 iobuf
            PIN I DOUT(1)
            PIN IO D1
            PIN O DIN(1)
            PIN T OE
        END BLOCK
        BEGIN BLOCK XLXI_52 iobuf
            PIN I DOUT(2)
            PIN IO D2
            PIN O DIN(2)
            PIN T OE
        END BLOCK
        BEGIN BLOCK XLXI_53 iobuf
            PIN I DOUT(3)
            PIN IO D3
            PIN O DIN(3)
            PIN T OE
        END BLOCK
        BEGIN BLOCK XLXI_54 iobuf
            PIN I DOUT(4)
            PIN IO D4
            PIN O DIN(4)
            PIN T OE
        END BLOCK
        BEGIN BLOCK XLXI_55 iobuf
            PIN I DOUT(5)
            PIN IO D5
            PIN O DIN(5)
            PIN T OE
        END BLOCK
        BEGIN BLOCK XLXI_56 iobuf
            PIN I DOUT(6)
            PIN IO D6
            PIN O DIN(6)
            PIN T OE
        END BLOCK
        BEGIN BLOCK XLXI_57 iobuf
            PIN I DOUT(7)
            PIN IO D7
            PIN O DIN(7)
            PIN T OE
        END BLOCK
        BEGIN BLOCK XLXI_62 nand2b1
            PIN I0 CS
            PIN I1 WR
            PIN O OE
        END BLOCK
        BEGIN BLOCK XLXI_63 fd8ce
            PIN C FRAME
            PIN CE XLXN_477
            PIN CLR XLXN_342
            PIN D(7:0) SN(7:0)
            PIN Q(7:0) XLXN_48(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_64 or2
            PIN I0 WR
            PIN I1 CS
            PIN O WRITE
        END BLOCK
        BEGIN BLOCK XLXI_65 gnd
            PIN G XLXN_342
        END BLOCK
        BEGIN BLOCK XLXI_67 BUSAND2
            PIN BIN(7:0) XLXN_48(7:0)
            PIN E REG3
            PIN BOUT(7:0) XLXN_104(7:0)
            PIN BPREV(7:0) XLXN_69(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_68 d3_8e
            PIN A0 A0
            PIN A1 A1
            PIN A2 A2
            PIN E XLXN_50
            PIN D0
            PIN D1
            PIN D2
            PIN D3 REG3
            PIN D4
            PIN D5
            PIN D6 REG6
            PIN D7 REG7
        END BLOCK
        BEGIN BLOCK XLXI_69 vcc
            PIN P XLXN_50
        END BLOCK
        BEGIN BLOCK XLXI_75 busgnd
            PIN GBUS(7:0) XLXN_69(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_77 vcc
            PIN P XLXN_75
        END BLOCK
        BEGIN BLOCK XLXI_78 dect_rx
            PIN RXD XLXN_458
            PIN CLK CLK
            PIN SFLD XLXN_75
            PIN RFP XLXN_492
            PIN DOUT(7:0) RXDATA(7:0)
            PIN ADDR(7:0) RXADDR(7:0)
            PIN FRAME FRAME
            PIN BS BYTE
            PIN BIT
        END BLOCK
        BEGIN BLOCK XLXI_79 ramb16_s9_s9
            PIN ADDRA(10:0) RXADDR(10:0)
            PIN ADDRB(10:0) IOADDR(10:0)
            PIN CLKA BYTE
            PIN CLKB REG6
            PIN DIA(7:0) RXDATA(7:0)
            PIN DIB(7:0) DIN(7:0)
            PIN DIPA(0:0) DIP(0:0)
            PIN DIPB(0:0) DIP(0:0)
            PIN ENA XLXN_87
            PIN ENB XLXN_87
            PIN SSRA XLXN_86
            PIN SSRB XLXN_86
            PIN WEA XLXN_87
            PIN WEB XLXN_86
            PIN DOA(7:0)
            PIN DOB(7:0) XLXN_106(7:0)
            PIN DOPA(0:0)
            PIN DOPB(0:0)
        END BLOCK
        BEGIN BLOCK XLXI_80 gnd
            PIN G RXADDR(10)
        END BLOCK
        BEGIN BLOCK XLXI_81 gnd
            PIN G RXADDR(9)
        END BLOCK
        BEGIN BLOCK XLXI_82 gnd
            PIN G RXADDR(8)
        END BLOCK
        BEGIN BLOCK XLXI_83 gnd
            PIN G XLXN_86
        END BLOCK
        BEGIN BLOCK XLXI_84 vcc
            PIN P XLXN_87
        END BLOCK
        BEGIN BLOCK XLXI_85 gnd
            PIN G IOADDR(8)
        END BLOCK
        BEGIN BLOCK XLXI_86 gnd
            PIN G IOADDR(9)
        END BLOCK
        BEGIN BLOCK XLXI_87 gnd
            PIN G IOADDR(10)
        END BLOCK
        BEGIN BLOCK XLXI_88 BUSAND2
            PIN BIN(7:0) XLXN_106(7:0)
            PIN E REG6
            PIN BOUT(7:0) XLXN_117(7:0)
            PIN BPREV(7:0) XLXN_104(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_89 gnd
            PIN G DIP(0:0)
        END BLOCK
        BEGIN BLOCK XLXI_90 cb8cle
            PIN C CS
            PIN CE REG6
            PIN CLR XLXN_115
            PIN D(7:0) DIN(7:0)
            PIN L XLXN_109
            PIN CEO
            PIN Q(7:0) IOADDR(7:0)
            PIN TC
        END BLOCK
        BEGIN BLOCK XLXI_92 and2b1
            PIN I0 WR
            PIN I1 REG7
            PIN O XLXN_109
        END BLOCK
        BEGIN BLOCK XLXI_93 gnd
            PIN G XLXN_115
        END BLOCK
        BEGIN BLOCK XLXI_94 BUSAND2
            PIN BIN(7:0) STAT(7:0)
            PIN E REG7
            PIN BOUT(7:0) DOUT(7:0)
            PIN BPREV(7:0) XLXN_117(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_95 vcc
            PIN P STAT(7)
        END BLOCK
        BEGIN BLOCK XLXI_96 gnd
            PIN G STAT(6)
        END BLOCK
        BEGIN BLOCK XLXI_97 gnd
            PIN G STAT(5)
        END BLOCK
        BEGIN BLOCK XLXI_98 gnd
            PIN G STAT(4)
        END BLOCK
        BEGIN BLOCK XLXI_99 gnd
            PIN G STAT(3)
        END BLOCK
        BEGIN BLOCK XLXI_100 gnd
            PIN G STAT(2)
        END BLOCK
        BEGIN BLOCK XLXI_106 fdc_1
            PIN C FRAME
            PIN CLR XLXN_499
            PIN D XLXN_131
            PIN Q STAT(0)
        END BLOCK
        BEGIN BLOCK XLXI_107 vcc
            PIN P XLXN_131
        END BLOCK
        BEGIN BLOCK XLXI_108 buf
            PIN I CLK
            PIN O REFCLK
        END BLOCK
        BEGIN BLOCK XLXI_170 dect_sync
            PIN CLK CLK
            PIN BIT0 XLXN_378
            PIN BIT1 XLXN_379
            PIN BIT2 XLXN_380
            PIN ADDR(10:0) TXAD(10:0)
            PIN CFG XLXN_381
            PIN BCLK XLXN_250
            PIN SFLD XLXN_491
            PIN SL0 XLXN_463
            PIN SL1 XLXN_464
            PIN SL2 XLXN_465
            PIN SL3 XLXN_466
            PIN SL4 XLXN_467
        END BLOCK
        BEGIN BLOCK XLXI_171 ramb16_s9_s9
            PIN ADDRA(10:0) TXAD(10:0)
            PIN ADDRB(10:0) PKTADR(10:0)
            PIN CLKA XLXN_250
            PIN CLKB WRITE
            PIN DIA(7:0) XLXN_315(7:0)
            PIN DIB(7:0) DIN(7:0)
            PIN DIPA(0:0) XLXN_317(0:0)
            PIN DIPB(0:0) XLXN_317(0:0)
            PIN ENA XLXN_246
            PIN ENB REG6
            PIN SSRA XLXN_245
            PIN SSRB XLXN_245
            PIN WEA XLXN_245
            PIN WEB XLXN_246
            PIN DOA(7:0) XLXN_377(7:0)
            PIN DOB(7:0)
            PIN DOPA(0:0)
            PIN DOPB(0:0)
        END BLOCK
        BEGIN BLOCK XLXI_173 vcc
            PIN P XLXN_246
        END BLOCK
        BEGIN BLOCK XLXI_174 gnd
            PIN G XLXN_245
        END BLOCK
        BEGIN BLOCK XLXI_187 buf
            PIN I PKTCNT(0)
            PIN O PKTADR(0)
        END BLOCK
        BEGIN BLOCK XLXI_188 buf
            PIN I PKTCNT(1)
            PIN O PKTADR(1)
        END BLOCK
        BEGIN BLOCK XLXI_189 buf
            PIN I PKTCNT(2)
            PIN O PKTADR(2)
        END BLOCK
        BEGIN BLOCK XLXI_190 buf
            PIN I PKTCNT(3)
            PIN O PKTADR(3)
        END BLOCK
        BEGIN BLOCK XLXI_191 buf
            PIN I PKTCNT(4)
            PIN O PKTADR(4)
        END BLOCK
        BEGIN BLOCK XLXI_192 buf
            PIN I PKTCNT(5)
            PIN O PKTADR(5)
        END BLOCK
        BEGIN BLOCK XLXI_193 cb8cle
            PIN C XLXN_324
            PIN CE REG6
            PIN CLR XLXN_290
            PIN D(7:0) PRE(7:0)
            PIN L XLXN_310
            PIN CEO
            PIN Q(7:0) PKTCNT(7:0)
            PIN TC
        END BLOCK
        BEGIN BLOCK XLXI_195 gnd
            PIN G XLXN_290
        END BLOCK
        BEGIN BLOCK XLXI_196 fd8ce
            PIN C WRITE
            PIN CE REG7
            PIN CLR XLXN_290
            PIN D(7:0) DIN(7:0)
            PIN Q(7:0) PKTBASE(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_197 buf
            PIN I PKTBASE(0)
            PIN O PKTADR(6)
        END BLOCK
        BEGIN BLOCK XLXI_198 buf
            PIN I PKTBASE(1)
            PIN O PKTADR(7)
        END BLOCK
        BEGIN BLOCK XLXI_199 buf
            PIN I PKTBASE(2)
            PIN O PKTADR(8)
        END BLOCK
        BEGIN BLOCK XLXI_200 buf
            PIN I PKTBASE(3)
            PIN O PKTADR(9)
        END BLOCK
        BEGIN BLOCK XLXI_201 buf
            PIN I PKTBASE(4)
            PIN O PKTADR(10)
        END BLOCK
        BEGIN BLOCK XLXI_202 and2b1
            PIN I0 WR
            PIN I1 REG7
            PIN O XLXN_310
        END BLOCK
        BEGIN BLOCK XLXI_204 gnd
            PIN G XLXN_317(0:0)
        END BLOCK
        BEGIN BLOCK XLXI_206 inv
            PIN I CS
            PIN O XLXN_324
        END BLOCK
        BEGIN BLOCK XLXI_207 vcc
            PIN P PRE(7)
        END BLOCK
        BEGIN BLOCK XLXI_208 vcc
            PIN P PRE(6)
        END BLOCK
        BEGIN BLOCK XLXI_209 vcc
            PIN P PRE(5)
        END BLOCK
        BEGIN BLOCK XLXI_210 vcc
            PIN P PRE(4)
        END BLOCK
        BEGIN BLOCK XLXI_211 vcc
            PIN P PRE(3)
        END BLOCK
        BEGIN BLOCK XLXI_212 vcc
            PIN P PRE(2)
        END BLOCK
        BEGIN BLOCK XLXI_213 vcc
            PIN P PRE(1)
        END BLOCK
        BEGIN BLOCK XLXI_214 vcc
            PIN P PRE(0)
        END BLOCK
        BEGIN BLOCK XLXI_238 busgnd
            PIN GBUS(7:0) XLXN_315(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_246 and5b2
            PIN I0 XLXN_467
            PIN I1 XLXN_465
            PIN I2 XLXN_466
            PIN I3 XLXN_464
            PIN I4 XLXN_463
            PIN O XLXN_406
        END BLOCK
        BEGIN BLOCK XLXI_249 and2b1
            PIN I0 OE
            PIN I1 REG7
            PIN O REG7READ
        END BLOCK
        BEGIN BLOCK XLXI_257 dect_tx
            PIN DATA(7:0) XLXN_377(7:0)
            PIN BIT0 XLXN_378
            PIN BIT1 XLXN_379
            PIN BIT2 XLXN_380
            PIN BCLK XLXN_250
            PIN CFG XLXN_381
            PIN ADDR(10:0) TXAD(10:0)
            PIN CLKREF CLK
            PIN TXEN TXEN
            PIN PLLPD PLLD
            PIN MCLK MCLK
            PIN MDATA MDATA
            PIN ML ML
            PIN TXBITS
            PIN TXD4 TXD4
            PIN TXD3 TXD3
            PIN TXD2 TXD2
            PIN TXD1 TXD1
            PIN TXD0 TXD0
            PIN TEST
        END BLOCK
        BEGIN BLOCK XLXI_258 m2_1
            PIN D0 RXD
            PIN D1 XLXN_495
            PIN S0 XLXN_492
            PIN O XLXN_458
        END BLOCK
        BEGIN BLOCK XLXI_260 buf
            PIN I XLXN_463
            PIN O SN(0)
        END BLOCK
        BEGIN BLOCK XLXI_261 buf
            PIN I XLXN_464
            PIN O SN(1)
        END BLOCK
        BEGIN BLOCK XLXI_262 buf
            PIN I XLXN_465
            PIN O SN(2)
        END BLOCK
        BEGIN BLOCK XLXI_263 buf
            PIN I XLXN_466
            PIN O SN(3)
        END BLOCK
        BEGIN BLOCK XLXI_264 buf
            PIN I XLXN_467
            PIN O SN(4)
        END BLOCK
        BEGIN BLOCK XLXI_265 gnd
            PIN G SN(5)
        END BLOCK
        BEGIN BLOCK XLXI_266 gnd
            PIN G SN(6)
        END BLOCK
        BEGIN BLOCK XLXI_267 gnd
            PIN G SN(7)
        END BLOCK
        BEGIN BLOCK XLXI_268 vcc
            PIN P XLXN_477
        END BLOCK
        BEGIN BLOCK XLXI_274 ftc
            PIN C XLXN_487
            PIN CLR XLXN_486
            PIN T XLXN_485
            PIN Q XLXN_490
        END BLOCK
        BEGIN BLOCK XLXI_275 gnd
            PIN G XLXN_486
        END BLOCK
        BEGIN BLOCK XLXI_276 vcc
            PIN P XLXN_485
        END BLOCK
        BEGIN BLOCK XLXI_277 fd
            PIN C REG7READ
            PIN D XLXN_490
            PIN Q STAT(1)
        END BLOCK
        BEGIN BLOCK XLXI_278 fd_1
            PIN C XLXN_491
            PIN D XLXN_406
            PIN Q XLXN_487
        END BLOCK
        BEGIN BLOCK XLXI_280 inv
            PIN I SNIFF
            PIN O XLXN_495
        END BLOCK
        BEGIN BLOCK XLXI_281 gnd
            PIN G XLXN_492
        END BLOCK
        BEGIN BLOCK XLXI_282 and2
            PIN I0 CS
            PIN I1 REG6
            PIN O XLXN_499
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 7040 5440
        INSTANCE XLXI_50 6496 608 R0
        INSTANCE XLXI_51 6496 848 R0
        INSTANCE XLXI_52 6496 1088 R0
        INSTANCE XLXI_53 6496 1328 R0
        INSTANCE XLXI_54 6496 1568 R0
        INSTANCE XLXI_55 6496 1808 R0
        INSTANCE XLXI_56 6496 2048 R0
        INSTANCE XLXI_57 6496 2288 R0
        BEGIN BRANCH D0
            WIRE 6720 480 6800 480
        END BRANCH
        BEGIN BRANCH D1
            WIRE 6720 720 6800 720
        END BRANCH
        BEGIN BRANCH D2
            WIRE 6720 960 6800 960
        END BRANCH
        BEGIN BRANCH D3
            WIRE 6720 1200 6800 1200
        END BRANCH
        BEGIN BRANCH D4
            WIRE 6720 1440 6800 1440
        END BRANCH
        BEGIN BRANCH D5
            WIRE 6720 1680 6800 1680
        END BRANCH
        BEGIN BRANCH D6
            WIRE 6720 1920 6800 1920
        END BRANCH
        BEGIN BRANCH D7
            WIRE 6720 2160 6800 2160
        END BRANCH
        IOMARKER 6800 480 D0 R0 28
        IOMARKER 6800 720 D1 R0 28
        IOMARKER 6800 960 D2 R0 28
        IOMARKER 6800 1200 D3 R0 28
        IOMARKER 6800 1440 D4 R0 28
        IOMARKER 6800 1680 D5 R0 28
        IOMARKER 6800 1920 D6 R0 28
        IOMARKER 6800 2160 D7 R0 28
        BUSTAP 6352 544 6448 544
        BEGIN BRANCH DIN(0)
            WIRE 6448 544 6496 544
        END BRANCH
        BUSTAP 6352 784 6448 784
        BUSTAP 6352 1024 6448 1024
        BUSTAP 6352 1264 6448 1264
        BEGIN BRANCH DIN(1)
            WIRE 6448 784 6496 784
        END BRANCH
        BEGIN BRANCH DIN(2)
            WIRE 6448 1024 6496 1024
        END BRANCH
        BEGIN BRANCH DIN(3)
            WIRE 6448 1264 6496 1264
        END BRANCH
        BUSTAP 6352 1504 6448 1504
        BUSTAP 6352 1744 6448 1744
        BUSTAP 6352 1984 6448 1984
        BUSTAP 6352 2224 6448 2224
        BEGIN BRANCH DIN(4)
            WIRE 6448 1504 6496 1504
        END BRANCH
        BEGIN BRANCH DIN(5)
            WIRE 6448 1744 6496 1744
        END BRANCH
        BEGIN BRANCH DIN(6)
            WIRE 6448 1984 6496 1984
        END BRANCH
        BEGIN BRANCH DIN(7)
            WIRE 6448 2224 6496 2224
        END BRANCH
        BUSTAP 6240 2160 6336 2160
        BUSTAP 6240 1920 6336 1920
        BUSTAP 6240 1680 6336 1680
        BUSTAP 6240 1440 6336 1440
        BUSTAP 6240 1200 6336 1200
        BUSTAP 6240 960 6336 960
        BUSTAP 6240 720 6336 720
        BUSTAP 6240 480 6336 480
        BEGIN BRANCH DOUT(0)
            WIRE 6336 480 6496 480
        END BRANCH
        BEGIN BRANCH DOUT(1)
            WIRE 6336 720 6496 720
        END BRANCH
        BEGIN BRANCH DOUT(2)
            WIRE 6336 960 6496 960
        END BRANCH
        BEGIN BRANCH DOUT(3)
            WIRE 6336 1200 6496 1200
        END BRANCH
        BEGIN BRANCH DOUT(4)
            WIRE 6336 1440 6496 1440
        END BRANCH
        BEGIN BRANCH DOUT(5)
            WIRE 6336 1680 6496 1680
        END BRANCH
        BEGIN BRANCH DOUT(6)
            WIRE 6336 1920 6496 1920
        END BRANCH
        BEGIN BRANCH DOUT(7)
            WIRE 6336 2160 6496 2160
        END BRANCH
        BEGIN BRANCH WR
            WIRE 4832 576 5712 576
            WIRE 5712 576 5824 576
            WIRE 4832 576 4832 1680
            WIRE 4832 1680 4944 1680
            WIRE 4832 1680 4832 2560
            WIRE 4832 2560 5120 2560
            WIRE 5120 2560 5120 4800
            WIRE 5120 4800 5232 4800
            WIRE 5600 320 5712 320
            WIRE 5712 320 5760 320
            WIRE 5712 320 5712 576
            WIRE 5760 304 5840 304
            WIRE 5760 304 5760 320
        END BRANCH
        IOMARKER 5600 240 CS R180 28
        IOMARKER 5600 320 WR R180 28
        INSTANCE XLXI_62 5824 704 R0
        INSTANCE XLXI_64 5840 368 R0
        BEGIN BRANCH XLXN_48(7:0)
            WIRE 5648 960 5696 960
        END BRANCH
        INSTANCE XLXI_68 4000 736 R0
        INSTANCE XLXI_69 3856 544 R0
        BEGIN BRANCH XLXN_50
            WIRE 3920 544 3920 608
            WIRE 3920 608 4000 608
        END BRANCH
        BEGIN BRANCH A0
            WIRE 3840 160 4000 160
        END BRANCH
        BEGIN BRANCH A1
            WIRE 3840 224 4000 224
        END BRANCH
        BEGIN BRANCH A2
            WIRE 3840 288 4000 288
        END BRANCH
        IOMARKER 3840 160 A0 R180 28
        IOMARKER 3840 224 A1 R180 28
        IOMARKER 3840 288 A2 R180 28
        BEGIN BRANCH IOADDR(7:0)
            WIRE 5648 1520 5696 1520
            BEGIN DISPLAY 5696 1520 ATTR Name
                ALIGNMENT SOFT-LEFT
            END DISPLAY
        END BRANCH
        INSTANCE XLXI_65 5168 1344 R0
        BEGIN INSTANCE XLXI_67 5696 928 R0
        END INSTANCE
        BEGIN INSTANCE XLXI_75 6080 512 M0
        END INSTANCE
        BEGIN BRANCH XLXN_69(7:0)
            WIRE 6080 480 6160 480
            WIRE 6160 480 6160 896
            WIRE 6080 896 6160 896
        END BRANCH
        BEGIN BRANCH OE
            WIRE 5392 3200 5392 3424
            WIRE 5392 3424 5440 3424
            WIRE 5392 3200 6464 3200
            WIRE 6080 608 6464 608
            WIRE 6464 608 6464 656
            WIRE 6464 656 6464 896
            WIRE 6464 896 6464 1136
            WIRE 6464 1136 6496 1136
            WIRE 6464 1136 6464 1376
            WIRE 6464 1376 6464 1616
            WIRE 6464 1616 6464 1856
            WIRE 6464 1856 6496 1856
            WIRE 6464 1856 6464 2096
            WIRE 6464 2096 6496 2096
            WIRE 6464 2096 6464 3200
            WIRE 6464 1616 6496 1616
            WIRE 6464 1376 6496 1376
            WIRE 6464 896 6496 896
            WIRE 6464 656 6496 656
            WIRE 6464 416 6496 416
            WIRE 6464 416 6464 608
        END BRANCH
        IOMARKER 320 544 CLK R180 28
        BEGIN BRANCH XLXN_75
            WIRE 400 272 400 608
            WIRE 400 608 480 608
        END BRANCH
        BEGIN INSTANCE XLXI_78 480 768 R0
        END INSTANCE
        INSTANCE XLXI_79 1600 1568 R0
        BEGIN BRANCH RXADDR(7:0)
            WIRE 864 544 960 544
            BEGIN DISPLAY 960 544 ATTR Name
                ALIGNMENT SOFT-LEFT
            END DISPLAY
        END BRANCH
        BEGIN BRANCH RXADDR(8)
            WIRE 1072 816 1152 816
        END BRANCH
        BEGIN BRANCH RXADDR(9)
            WIRE 1072 880 1152 880
        END BRANCH
        BEGIN BRANCH RXADDR(10)
            WIRE 1072 944 1152 944
        END BRANCH
        INSTANCE XLXI_82 944 752 R90
        INSTANCE XLXI_81 944 816 R90
        INSTANCE XLXI_80 944 880 R90
        BUSTAP 1248 944 1152 944
        BUSTAP 1248 880 1152 880
        BUSTAP 1248 816 1152 816
        BEGIN BRANCH RXADDR(10:0)
            WIRE 1248 800 1248 816
            WIRE 1248 816 1248 880
            WIRE 1248 880 1248 944
            WIRE 1248 800 1600 800
            BEGIN DISPLAY 1248 800 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH RXDATA(7:0)
            WIRE 864 480 1360 480
            WIRE 1360 480 1360 864
            WIRE 1360 864 1600 864
        END BRANCH
        INSTANCE XLXI_83 1504 1728 R0
        BEGIN BRANCH XLXN_86
            WIRE 1568 672 1600 672
            WIRE 1568 672 1568 1056
            WIRE 1568 1056 1600 1056
            WIRE 1568 1056 1568 1184
            WIRE 1568 1184 1600 1184
            WIRE 1568 1184 1568 1600
        END BRANCH
        INSTANCE XLXI_84 1456 384 R0
        BEGIN BRANCH XLXN_87
            WIRE 1520 384 1520 544
            WIRE 1520 544 1520 608
            WIRE 1520 608 1600 608
            WIRE 1520 608 1520 1120
            WIRE 1520 1120 1600 1120
            WIRE 1520 544 1600 544
        END BRANCH
        INSTANCE XLXI_63 5264 1216 R0
        BEGIN BRANCH IOADDR(10:0)
            WIRE 1120 1312 1184 1312
            WIRE 1184 1312 1248 1312
            WIRE 1248 1312 1600 1312
        END BRANCH
        BUSTAP 1120 1312 1120 1408
        BUSTAP 1184 1312 1184 1408
        BUSTAP 1248 1312 1248 1408
        INSTANCE XLXI_85 1056 1600 R0
        INSTANCE XLXI_86 1120 1600 R0
        INSTANCE XLXI_87 1184 1600 R0
        BEGIN BRANCH IOADDR(8)
            WIRE 1120 1408 1120 1472
        END BRANCH
        BEGIN BRANCH IOADDR(9)
            WIRE 1184 1408 1184 1472
        END BRANCH
        BEGIN BRANCH IOADDR(10)
            WIRE 1248 1408 1248 1472
        END BRANCH
        BEGIN INSTANCE XLXI_88 5696 1952 R0
        END INSTANCE
        BEGIN BRANCH XLXN_106(7:0)
            WIRE 2208 1216 4352 1216
            WIRE 4352 1216 4352 1984
            WIRE 4352 1984 5696 1984
        END BRANCH
        BEGIN BRANCH DIP(0:0)
            WIRE 1440 1440 1456 1440
            WIRE 1456 1440 1600 1440
            WIRE 1440 1440 1440 1600
            WIRE 1456 480 1456 1440
            WIRE 1456 480 1600 480
        END BRANCH
        INSTANCE XLXI_89 1376 1728 R0
        INSTANCE XLXI_90 5264 1904 R0
        BEGIN BRANCH XLXN_109
            WIRE 5200 1648 5264 1648
        END BRANCH
        INSTANCE XLXI_92 4944 1744 R0
        INSTANCE XLXI_93 5152 2192 R0
        BEGIN BRANCH XLXN_115
            WIRE 5216 1872 5264 1872
            WIRE 5216 1872 5216 2064
        END BRANCH
        BEGIN BRANCH XLXN_104(7:0)
            WIRE 6080 960 6160 960
            WIRE 6160 960 6160 1920
            WIRE 6080 1920 6160 1920
        END BRANCH
        BEGIN INSTANCE XLXI_94 5696 2320 R0
        END INSTANCE
        BEGIN BRANCH DOUT(7:0)
            WIRE 6080 2352 6240 2352
            WIRE 6240 480 6240 720
            WIRE 6240 720 6240 960
            WIRE 6240 960 6240 1200
            WIRE 6240 1200 6240 1440
            WIRE 6240 1440 6240 1680
            WIRE 6240 1680 6240 1920
            WIRE 6240 1920 6240 2160
            WIRE 6240 2160 6240 2352
        END BRANCH
        BEGIN BRANCH XLXN_117(7:0)
            WIRE 6080 1984 6160 1984
            WIRE 6160 1984 6160 2288
            WIRE 6080 2288 6160 2288
        END BRANCH
        BUSTAP 5600 2400 5504 2400
        BUSTAP 5600 2464 5504 2464
        BUSTAP 5600 2528 5504 2528
        BUSTAP 5600 2592 5504 2592
        BUSTAP 5600 2656 5504 2656
        BUSTAP 5600 2720 5504 2720
        BUSTAP 5600 2784 5504 2784
        BUSTAP 5600 2848 5504 2848
        BEGIN BRANCH STAT(7:0)
            WIRE 5600 2352 5696 2352
            WIRE 5600 2352 5600 2400
            WIRE 5600 2400 5600 2464
            WIRE 5600 2464 5600 2528
            WIRE 5600 2528 5600 2592
            WIRE 5600 2592 5600 2656
            WIRE 5600 2656 5600 2720
            WIRE 5600 2720 5600 2784
            WIRE 5600 2784 5600 2848
        END BRANCH
        INSTANCE XLXI_95 5376 2464 R270
        INSTANCE XLXI_96 5248 2400 R90
        INSTANCE XLXI_97 5248 2464 R90
        INSTANCE XLXI_98 5248 2528 R90
        BEGIN BRANCH STAT(7)
            WIRE 5376 2400 5504 2400
        END BRANCH
        BEGIN BRANCH STAT(6)
            WIRE 5376 2464 5504 2464
        END BRANCH
        BEGIN BRANCH STAT(5)
            WIRE 5376 2528 5504 2528
        END BRANCH
        BEGIN BRANCH STAT(4)
            WIRE 5376 2592 5504 2592
        END BRANCH
        INSTANCE XLXI_99 5248 2592 R90
        INSTANCE XLXI_100 5248 2656 R90
        BEGIN BRANCH STAT(3)
            WIRE 5376 2656 5504 2656
        END BRANCH
        BEGIN BRANCH STAT(2)
            WIRE 5376 2720 5504 2720
        END BRANCH
        BEGIN BRANCH STAT(1)
            WIRE 3200 5008 3280 5008
            WIRE 3280 2240 3280 5008
            WIRE 3280 2240 5488 2240
            WIRE 5488 2240 5488 2784
            WIRE 5488 2784 5504 2784
        END BRANCH
        BEGIN DISPLAY 5640 2492 TEXT "STATUS REGISTER"
            FONT 36 "Arial"
        END DISPLAY
        BEGIN BRANCH STAT(0)
            WIRE 5072 2848 5504 2848
        END BRANCH
        BEGIN BRANCH XLXN_131
            WIRE 4640 2784 4640 2848
            WIRE 4640 2848 4688 2848
        END BRANCH
        INSTANCE XLXI_108 400 2112 R0
        BEGIN BRANCH REFCLK
            WIRE 624 2080 800 2080
        END BRANCH
        IOMARKER 800 2080 REFCLK R0 28
        BEGIN BRANCH BYTE
            WIRE 864 672 1040 672
            WIRE 1040 672 1040 736
            WIRE 1040 736 1600 736
        END BRANCH
        INSTANCE XLXI_77 336 272 R0
        BEGIN BRANCH REG3
            WIRE 4384 352 5040 352
            WIRE 5040 352 5040 720
            WIRE 5040 720 5680 720
            WIRE 5680 720 5680 896
            WIRE 5680 896 5696 896
        END BRANCH
        BEGIN INSTANCE XLXI_170 416 4288 R0
        END INSTANCE
        INSTANCE XLXI_171 1440 4512 R0
        INSTANCE XLXI_173 1328 3344 R0
        BEGIN BRANCH XLXN_245
            WIRE 1360 3488 1440 3488
            WIRE 1360 3488 1360 3616
            WIRE 1360 3616 1440 3616
            WIRE 1360 3616 1360 4128
            WIRE 1360 4128 1440 4128
            WIRE 1360 4128 1360 4448
        END BRANCH
        BUSTAP 6960 5120 6864 5120
        BUSTAP 6960 5056 6864 5056
        BUSTAP 6960 4992 6864 4992
        BUSTAP 6960 4928 6864 4928
        BUSTAP 6960 4864 6864 4864
        BUSTAP 6960 4800 6864 4800
        INSTANCE XLXI_187 6496 5152 R0
        INSTANCE XLXI_188 6496 5088 R0
        INSTANCE XLXI_189 6496 5024 R0
        INSTANCE XLXI_190 6496 4960 R0
        INSTANCE XLXI_191 6496 4896 R0
        INSTANCE XLXI_192 6496 4832 R0
        BEGIN BRANCH PKTADR(0)
            WIRE 6720 5120 6864 5120
        END BRANCH
        BEGIN BRANCH PKTADR(1)
            WIRE 6720 5056 6864 5056
        END BRANCH
        BEGIN BRANCH PKTADR(2)
            WIRE 6720 4992 6864 4992
        END BRANCH
        BEGIN BRANCH PKTADR(3)
            WIRE 6720 4928 6864 4928
        END BRANCH
        BEGIN BRANCH PKTADR(4)
            WIRE 6720 4864 6864 4864
        END BRANCH
        BEGIN BRANCH PKTADR(5)
            WIRE 6720 4800 6864 4800
        END BRANCH
        INSTANCE XLXI_193 5600 5024 R0
        BEGIN BRANCH PKTCNT(7:0)
            WIRE 5984 4640 6080 4640
            WIRE 6080 4640 6080 4800
            WIRE 6080 4800 6080 4864
            WIRE 6080 4864 6080 4928
            WIRE 6080 4928 6080 4992
            WIRE 6080 4992 6080 5056
            WIRE 6080 5056 6080 5120
        END BRANCH
        BUSTAP 6080 5120 6176 5120
        BUSTAP 6080 5056 6176 5056
        BUSTAP 6080 4992 6176 4992
        BUSTAP 6080 4928 6176 4928
        BUSTAP 6080 4864 6176 4864
        BUSTAP 6080 4800 6176 4800
        BEGIN BRANCH PKTCNT(0)
            WIRE 6176 5120 6496 5120
        END BRANCH
        BEGIN BRANCH PKTCNT(1)
            WIRE 6176 5056 6496 5056
        END BRANCH
        BEGIN BRANCH PKTCNT(2)
            WIRE 6176 4992 6496 4992
        END BRANCH
        BEGIN BRANCH PKTCNT(3)
            WIRE 6176 4928 6496 4928
        END BRANCH
        BEGIN BRANCH PKTCNT(4)
            WIRE 6176 4864 6496 4864
        END BRANCH
        BEGIN BRANCH PKTCNT(5)
            WIRE 6176 4800 6496 4800
        END BRANCH
        INSTANCE XLXI_195 5472 5168 R0
        INSTANCE XLXI_196 5600 4416 R0
        BEGIN BRANCH XLXN_290
            WIRE 5536 4384 5600 4384
            WIRE 5536 4384 5536 4992
            WIRE 5536 4992 5600 4992
            WIRE 5536 4992 5536 5040
        END BRANCH
        BUSTAP 6960 4480 6864 4480
        BUSTAP 6960 4416 6864 4416
        BUSTAP 6960 4352 6864 4352
        BUSTAP 6960 4288 6864 4288
        BUSTAP 6960 4224 6864 4224
        INSTANCE XLXI_197 6496 4512 R0
        INSTANCE XLXI_198 6496 4448 R0
        INSTANCE XLXI_199 6496 4384 R0
        INSTANCE XLXI_200 6496 4320 R0
        INSTANCE XLXI_201 6496 4256 R0
        BEGIN BRANCH PKTADR(10:0)
            WIRE 1168 4256 1440 4256
            WIRE 1168 4256 1168 5328
            WIRE 1168 5328 6960 5328
            WIRE 6960 4224 6960 4288
            WIRE 6960 4288 6960 4352
            WIRE 6960 4352 6960 4416
            WIRE 6960 4416 6960 4480
            WIRE 6960 4480 6960 4800
            WIRE 6960 4800 6960 4864
            WIRE 6960 4864 6960 4928
            WIRE 6960 4928 6960 4992
            WIRE 6960 4992 6960 5056
            WIRE 6960 5056 6960 5120
            WIRE 6960 5120 6960 5328
        END BRANCH
        BEGIN BRANCH PKTBASE(7:0)
            WIRE 5984 4160 6080 4160
            WIRE 6080 4160 6080 4224
            WIRE 6080 4224 6080 4288
            WIRE 6080 4288 6080 4352
            WIRE 6080 4352 6080 4416
            WIRE 6080 4416 6080 4480
        END BRANCH
        BUSTAP 6080 4480 6176 4480
        BUSTAP 6080 4416 6176 4416
        BUSTAP 6080 4352 6176 4352
        BUSTAP 6080 4288 6176 4288
        BUSTAP 6080 4224 6176 4224
        BEGIN BRANCH PKTADR(10)
            WIRE 6720 4224 6864 4224
        END BRANCH
        BEGIN BRANCH PKTADR(9)
            WIRE 6720 4288 6864 4288
        END BRANCH
        BEGIN BRANCH PKTADR(8)
            WIRE 6720 4352 6864 4352
        END BRANCH
        BEGIN BRANCH PKTADR(7)
            WIRE 6720 4416 6864 4416
        END BRANCH
        BEGIN BRANCH PKTADR(6)
            WIRE 6720 4480 6864 4480
        END BRANCH
        BEGIN BRANCH PKTBASE(0)
            WIRE 6176 4480 6496 4480
        END BRANCH
        BEGIN BRANCH PKTBASE(1)
            WIRE 6176 4416 6496 4416
        END BRANCH
        BEGIN BRANCH PKTBASE(2)
            WIRE 6176 4352 6496 4352
        END BRANCH
        BEGIN BRANCH PKTBASE(3)
            WIRE 6176 4288 6496 4288
        END BRANCH
        BEGIN BRANCH PKTBASE(4)
            WIRE 6176 4224 6496 4224
        END BRANCH
        BEGIN BRANCH WRITE
            WIRE 1312 3088 1312 4192
            WIRE 1312 4192 1440 4192
            WIRE 1312 3088 6192 3088
            WIRE 6192 3088 6192 3840
            WIRE 5504 3840 6192 3840
            WIRE 5504 3840 5504 4288
            WIRE 5504 4288 5600 4288
            WIRE 6096 272 6192 272
            WIRE 6192 272 6192 3088
        END BRANCH
        INSTANCE XLXI_202 5232 4864 R0
        INSTANCE XLXI_107 4576 2784 R0
        INSTANCE XLXI_106 4688 3104 R0
        BEGIN BRANCH XLXN_310
            WIRE 5488 4768 5600 4768
        END BRANCH
        BEGIN BRANCH XLXN_315(7:0)
            WIRE 704 3392 1424 3392
            WIRE 1424 3392 1424 3808
            WIRE 1424 3808 1440 3808
        END BRANCH
        BEGIN BRANCH XLXN_317(0:0)
            WIRE 1168 3360 1328 3360
            WIRE 1328 3360 1328 3424
            WIRE 1328 3424 1440 3424
            WIRE 1328 3424 1328 4384
            WIRE 1328 4384 1440 4384
        END BRANCH
        BEGIN BRANCH XLXN_246
            WIRE 1392 3344 1392 3552
            WIRE 1392 3552 1440 3552
            WIRE 1392 3552 1392 4000
            WIRE 1392 4000 1440 4000
        END BRANCH
        BEGIN BRANCH CS
            WIRE 4336 3232 4384 3232
            WIRE 4336 3232 4336 3360
            WIRE 4336 3360 5136 3360
            WIRE 5136 3360 5136 4896
            WIRE 5136 4896 5216 4896
            WIRE 4864 640 5696 640
            WIRE 5696 640 5824 640
            WIRE 4864 640 4864 1776
            WIRE 4864 1776 5136 1776
            WIRE 5136 1776 5264 1776
            WIRE 5136 1776 5136 3360
            WIRE 5600 240 5696 240
            WIRE 5696 240 5840 240
            WIRE 5696 240 5696 640
        END BRANCH
        INSTANCE XLXI_206 5216 4928 R0
        BEGIN BRANCH XLXN_324
            WIRE 5440 4896 5600 4896
        END BRANCH
        BUSTAP 5040 4656 4944 4656
        BUSTAP 5040 4720 4944 4720
        BUSTAP 5040 4784 4944 4784
        BUSTAP 5040 4848 4944 4848
        BUSTAP 5040 4912 4944 4912
        BUSTAP 5040 4976 4944 4976
        BUSTAP 5040 5040 4944 5040
        BUSTAP 5040 5104 4944 5104
        INSTANCE XLXI_207 4864 4720 R270
        INSTANCE XLXI_208 4864 4784 R270
        INSTANCE XLXI_209 4864 4848 R270
        INSTANCE XLXI_210 4864 4912 R270
        INSTANCE XLXI_211 4864 4976 R270
        INSTANCE XLXI_212 4864 5040 R270
        INSTANCE XLXI_213 4864 5104 R270
        INSTANCE XLXI_214 4864 5168 R270
        BEGIN BRANCH PRE(7)
            WIRE 4864 4656 4944 4656
        END BRANCH
        BEGIN BRANCH PRE(6)
            WIRE 4864 4720 4944 4720
        END BRANCH
        BEGIN BRANCH PRE(5)
            WIRE 4864 4784 4944 4784
        END BRANCH
        BEGIN BRANCH PRE(4)
            WIRE 4864 4848 4944 4848
        END BRANCH
        BEGIN BRANCH PRE(3)
            WIRE 4864 4912 4944 4912
        END BRANCH
        BEGIN BRANCH PRE(2)
            WIRE 4864 4976 4944 4976
        END BRANCH
        BEGIN BRANCH PRE(1)
            WIRE 4864 5040 4944 5040
        END BRANCH
        BEGIN BRANCH PRE(0)
            WIRE 4864 5104 4944 5104
        END BRANCH
        BEGIN BRANCH PRE(7:0)
            WIRE 5040 4640 5600 4640
            WIRE 5040 4640 5040 4656
            WIRE 5040 4656 5040 4720
            WIRE 5040 4720 5040 4784
            WIRE 5040 4784 5040 4848
            WIRE 5040 4848 5040 4912
            WIRE 5040 4912 5040 4976
            WIRE 5040 4976 5040 5040
            WIRE 5040 5040 5040 5104
        END BRANCH
        BEGIN BRANCH TXAD(10:0)
            WIRE 800 3744 1200 3744
            WIRE 1200 3744 1440 3744
            WIRE 1200 3216 1200 3744
            WIRE 1200 3216 2240 3216
            WIRE 2240 3216 2240 4032
            WIRE 2240 4032 2400 4032
        END BRANCH
        BEGIN BRANCH XLXN_377(7:0)
            WIRE 2048 3648 2400 3648
        END BRANCH
        BEGIN BRANCH XLXN_378
            WIRE 800 3808 1088 3808
            WIRE 1088 3808 1088 4656
            WIRE 1088 4656 2128 4656
            WIRE 2128 3712 2400 3712
            WIRE 2128 3712 2128 4656
        END BRANCH
        BEGIN BRANCH XLXN_379
            WIRE 800 3872 1072 3872
            WIRE 1072 3872 1072 4672
            WIRE 1072 4672 2144 4672
            WIRE 2144 3776 2400 3776
            WIRE 2144 3776 2144 4672
        END BRANCH
        BEGIN BRANCH XLXN_380
            WIRE 800 3936 1056 3936
            WIRE 1056 3936 1056 4688
            WIRE 1056 4688 2160 4688
            WIRE 2160 3840 2400 3840
            WIRE 2160 3840 2160 4688
        END BRANCH
        INSTANCE XLXI_174 1296 4576 R0
        BEGIN BRANCH XLXN_381
            WIRE 800 3680 1136 3680
            WIRE 1136 3680 1136 4736
            WIRE 1136 4736 2192 4736
            WIRE 2192 3968 2400 3968
            WIRE 2192 3968 2192 4736
        END BRANCH
        INSTANCE XLXI_246 1280 5264 R0
        INSTANCE XLXI_249 5440 3488 R0
        BEGIN INSTANCE XLXI_257 2400 4256 R0
        END INSTANCE
        BEGIN BRANCH XLXN_250
            WIRE 800 3616 1248 3616
            WIRE 1248 3616 1248 3680
            WIRE 1248 3680 1440 3680
            WIRE 1248 3680 1248 4624
            WIRE 1248 4624 2112 4624
            WIRE 2112 3904 2112 4624
            WIRE 2112 3904 2400 3904
        END BRANCH
        BEGIN BRANCH TXD4
            WIRE 2784 3584 2880 3584
        END BRANCH
        BEGIN BRANCH TXD3
            WIRE 2784 3648 2880 3648
        END BRANCH
        BEGIN BRANCH TXD2
            WIRE 2784 3712 2880 3712
        END BRANCH
        BEGIN BRANCH TXD1
            WIRE 2784 3776 2880 3776
        END BRANCH
        BEGIN BRANCH TXD0
            WIRE 2784 3840 2880 3840
        END BRANCH
        BEGIN BRANCH PLLD
            WIRE 2784 3968 2880 3968
        END BRANCH
        BEGIN BRANCH MCLK
            WIRE 2784 4032 2880 4032
        END BRANCH
        BEGIN BRANCH MDATA
            WIRE 2784 4096 2880 4096
        END BRANCH
        BEGIN BRANCH ML
            WIRE 2784 4160 2880 4160
        END BRANCH
        IOMARKER 2880 3584 TXD4 R0 28
        IOMARKER 2880 3648 TXD3 R0 28
        IOMARKER 2880 3712 TXD2 R0 28
        IOMARKER 2880 3776 TXD1 R0 28
        IOMARKER 2880 3840 TXD0 R0 28
        IOMARKER 2880 3904 TXEN R0 28
        IOMARKER 2880 3968 PLLD R0 28
        IOMARKER 2880 4032 MCLK R0 28
        IOMARKER 2880 4096 MDATA R0 28
        IOMARKER 2880 4160 ML R0 28
        INSTANCE XLXI_258 480 1104 R0
        BEGIN BRANCH RXD
            WIRE 320 944 480 944
        END BRANCH
        IOMARKER 320 944 RXD R180 28
        BEGIN BRANCH XLXN_458
            WIRE 448 480 448 848
            WIRE 448 848 864 848
            WIRE 864 848 864 976
            WIRE 448 480 480 480
            WIRE 800 976 864 976
        END BRANCH
        INSTANCE XLXI_204 1040 3296 R90
        BEGIN INSTANCE XLXI_238 704 3360 R180
        END INSTANCE
        INSTANCE XLXI_260 1216 2992 R0
        INSTANCE XLXI_261 1216 2928 R0
        INSTANCE XLXI_262 1216 2864 R0
        INSTANCE XLXI_263 1216 2800 R0
        INSTANCE XLXI_264 1216 2736 R0
        BEGIN BRANCH XLXN_464
            WIRE 800 4064 976 4064
            WIRE 976 4064 976 5008
            WIRE 976 5008 1280 5008
            WIRE 976 2896 1216 2896
            WIRE 976 2896 976 4064
        END BRANCH
        BEGIN BRANCH XLXN_465
            WIRE 800 4128 944 4128
            WIRE 944 4128 944 5136
            WIRE 944 5136 1280 5136
            WIRE 944 2832 1216 2832
            WIRE 944 2832 944 4128
        END BRANCH
        BEGIN BRANCH XLXN_466
            WIRE 800 4192 912 4192
            WIRE 912 4192 912 5072
            WIRE 912 5072 1280 5072
            WIRE 912 2768 1216 2768
            WIRE 912 2768 912 4192
        END BRANCH
        BEGIN BRANCH SN(7:0)
            WIRE 1600 2480 1600 2512
            WIRE 1600 2512 1600 2576
            WIRE 1600 2576 1600 2640
            WIRE 1600 2640 1600 2704
            WIRE 1600 2704 1600 2768
            WIRE 1600 2768 1600 2832
            WIRE 1600 2832 1600 2896
            WIRE 1600 2896 1600 2960
            WIRE 1600 2480 2480 2480
            WIRE 2480 960 2480 2480
            WIRE 2480 960 5264 960
        END BRANCH
        BUSTAP 1600 2960 1504 2960
        BUSTAP 1600 2896 1504 2896
        BUSTAP 1600 2832 1504 2832
        BUSTAP 1600 2768 1504 2768
        BUSTAP 1600 2704 1504 2704
        BUSTAP 1600 2640 1504 2640
        BUSTAP 1600 2576 1504 2576
        BUSTAP 1600 2512 1504 2512
        BEGIN BRANCH SN(0)
            WIRE 1440 2960 1488 2960
            WIRE 1488 2960 1504 2960
            BEGIN DISPLAY 1488 2960 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH SN(1)
            WIRE 1440 2896 1488 2896
            WIRE 1488 2896 1504 2896
            BEGIN DISPLAY 1488 2896 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH SN(2)
            WIRE 1440 2832 1488 2832
            WIRE 1488 2832 1504 2832
            BEGIN DISPLAY 1488 2832 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH SN(3)
            WIRE 1440 2768 1488 2768
            WIRE 1488 2768 1504 2768
            BEGIN DISPLAY 1488 2768 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH SN(4)
            WIRE 1440 2704 1488 2704
            WIRE 1488 2704 1504 2704
            BEGIN DISPLAY 1488 2704 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH SN(5)
            WIRE 1424 2640 1488 2640
            WIRE 1488 2640 1504 2640
            BEGIN DISPLAY 1488 2640 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH SN(6)
            WIRE 1424 2576 1488 2576
            WIRE 1488 2576 1504 2576
            BEGIN DISPLAY 1488 2576 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH SN(7)
            WIRE 1424 2512 1488 2512
            WIRE 1488 2512 1504 2512
            BEGIN DISPLAY 1488 2512 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        INSTANCE XLXI_265 1296 2576 R90
        INSTANCE XLXI_266 1296 2512 R90
        INSTANCE XLXI_267 1296 2448 R90
        BEGIN BRANCH DIN(7:0)
            WIRE 1216 4320 1440 4320
            WIRE 1216 4320 1216 5280
            WIRE 1216 5280 6352 5280
            WIRE 1520 1376 1600 1376
            WIRE 1520 1376 1520 1520
            WIRE 1520 1520 5120 1520
            WIRE 5120 1520 5264 1520
            WIRE 5120 80 6352 80
            WIRE 6352 80 6352 544
            WIRE 6352 544 6352 784
            WIRE 6352 784 6352 1024
            WIRE 6352 1024 6352 1264
            WIRE 6352 1264 6352 1504
            WIRE 6352 1504 6352 1744
            WIRE 6352 1744 6352 1984
            WIRE 6352 1984 6352 2224
            WIRE 6352 2224 6352 3936
            WIRE 6352 3936 6352 5280
            WIRE 5120 80 5120 1520
            WIRE 5552 3936 5552 4160
            WIRE 5552 4160 5600 4160
            WIRE 5552 3936 6352 3936
        END BRANCH
        BEGIN BRANCH XLXN_342
            WIRE 5232 1184 5264 1184
            WIRE 5232 1184 5232 1216
        END BRANCH
        INSTANCE XLXI_268 5136 896 R0
        BEGIN BRANCH XLXN_477
            WIRE 5200 896 5200 1024
            WIRE 5200 1024 5264 1024
        END BRANCH
        BEGIN BRANCH XLXN_467
            WIRE 800 4256 880 4256
            WIRE 880 4256 880 5200
            WIRE 880 5200 1280 5200
            WIRE 880 2704 1216 2704
            WIRE 880 2704 880 4256
        END BRANCH
        BEGIN BRANCH REG7
            WIRE 4384 608 4928 608
            WIRE 4928 608 4928 1616
            WIRE 4928 1616 4944 1616
            WIRE 4928 1616 4928 2288
            WIRE 4928 2288 5184 2288
            WIRE 5184 2288 5696 2288
            WIRE 5184 2288 5184 3360
            WIRE 5184 3360 5440 3360
            WIRE 5184 3360 5184 4224
            WIRE 5184 4224 5600 4224
            WIRE 5184 4224 5184 4736
            WIRE 5184 4736 5232 4736
        END BRANCH
        BEGIN BRANCH REG7READ
            WIRE 2784 5136 2816 5136
            WIRE 2784 5136 2784 5312
            WIRE 2784 5312 6048 5312
            WIRE 5696 3392 6048 3392
            WIRE 6048 3392 6048 5312
        END BRANCH
        BEGIN BRANCH XLXN_406
            WIRE 1536 5072 1552 5072
            WIRE 1552 5008 1664 5008
            WIRE 1552 5008 1552 5072
        END BRANCH
        INSTANCE XLXI_274 2320 5264 R0
        INSTANCE XLXI_275 2112 5168 R90
        INSTANCE XLXI_276 2192 4960 R0
        BEGIN BRANCH XLXN_485
            WIRE 2256 4960 2256 5008
            WIRE 2256 5008 2320 5008
        END BRANCH
        BEGIN BRANCH XLXN_486
            WIRE 2240 5232 2320 5232
        END BRANCH
        BEGIN BRANCH XLXN_487
            WIRE 2048 5008 2176 5008
            WIRE 2176 5008 2176 5136
            WIRE 2176 5136 2320 5136
        END BRANCH
        INSTANCE XLXI_277 2816 5264 R0
        BEGIN BRANCH XLXN_490
            WIRE 2704 5008 2816 5008
        END BRANCH
        BEGIN BRANCH CLK
            WIRE 320 544 368 544
            WIRE 368 544 480 544
            WIRE 368 544 368 2080
            WIRE 368 2080 400 2080
            WIRE 368 2080 368 3552
            WIRE 368 3552 416 3552
            WIRE 368 3552 368 4880
            WIRE 368 4880 2320 4880
            WIRE 2320 3584 2400 3584
            WIRE 2320 3584 2320 4880
        END BRANCH
        INSTANCE XLXI_278 1664 5264 R0
        BEGIN BRANCH XLXN_491
            WIRE 800 3552 864 3552
            WIRE 864 3552 864 4848
            WIRE 864 4848 1632 4848
            WIRE 1632 4848 1632 5136
            WIRE 1632 5136 1664 5136
        END BRANCH
        BEGIN BRANCH TXEN
            WIRE 2784 3904 2880 3904
        END BRANCH
        BEGIN BRANCH FRAME
            WIRE 864 608 896 608
            WIRE 896 320 960 320
            WIRE 896 320 896 400
            WIRE 896 400 3872 400
            WIRE 3872 400 3872 1088
            WIRE 3872 1088 3872 2976
            WIRE 3872 2976 4688 2976
            WIRE 3872 1088 5264 1088
            WIRE 896 400 896 608
        END BRANCH
        INSTANCE XLXI_280 496 1216 R0
        BEGIN BRANCH XLXN_495
            WIRE 432 1008 480 1008
            WIRE 432 1008 432 1120
            WIRE 432 1120 784 1120
            WIRE 784 1120 784 1184
            WIRE 720 1184 784 1184
        END BRANCH
        BEGIN BRANCH SNIFF
            WIRE 320 1184 496 1184
        END BRANCH
        IOMARKER 320 1184 SNIFF R180 28
        IOMARKER 960 320 FRAME R0 28
        BEGIN BRANCH XLXN_492
            WIRE 160 672 160 1072
            WIRE 160 1072 480 1072
            WIRE 160 1072 160 1152
            WIRE 160 672 480 672
        END BRANCH
        INSTANCE XLXI_281 96 1280 R0
        BEGIN BRANCH REG6
            WIRE 1296 3072 1296 4064
            WIRE 1296 4064 1440 4064
            WIRE 1296 3072 4240 3072
            WIRE 4240 3072 4416 3072
            WIRE 4240 3072 4240 3168
            WIRE 4240 3168 4384 3168
            WIRE 1488 1248 1600 1248
            WIRE 1488 1248 1488 1552
            WIRE 1488 1552 4416 1552
            WIRE 4416 1552 4416 1920
            WIRE 4416 1920 5152 1920
            WIRE 5152 1920 5696 1920
            WIRE 5152 1920 5152 4832
            WIRE 5152 4832 5600 4832
            WIRE 4416 1920 4416 3072
            WIRE 4384 544 4416 544
            WIRE 4416 544 4416 1552
            WIRE 5152 1712 5264 1712
            WIRE 5152 1712 5152 1920
        END BRANCH
        INSTANCE XLXI_282 4384 3296 R0
        BEGIN BRANCH XLXN_499
            WIRE 4640 3200 4688 3200
            WIRE 4688 3072 4688 3200
        END BRANCH
        BEGIN BRANCH XLXN_463
            WIRE 800 4000 1008 4000
            WIRE 1008 4000 1008 4944
            WIRE 1008 4944 1280 4944
            WIRE 1008 2240 1008 2960
            WIRE 1008 2960 1216 2960
            WIRE 1008 2960 1008 4000
            WIRE 1008 2240 1120 2240
        END BRANCH
        IOMARKER 1120 2240 XLXN_463 R0 28
    END SHEET
END SCHEMATIC
