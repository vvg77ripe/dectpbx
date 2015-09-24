VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL DATA(7:0)
        SIGNAL BIT0
        SIGNAL BIT1
        SIGNAL BIT2
        SIGNAL DATA(7)
        SIGNAL DATA(6)
        SIGNAL DATA(5)
        SIGNAL DATA(4)
        SIGNAL DATA(3)
        SIGNAL DATA(2)
        SIGNAL DATA(1)
        SIGNAL DATA(0)
        SIGNAL XLXN_187
        SIGNAL BCLK
        SIGNAL XLXN_189
        SIGNAL TXEN
        SIGNAL BYTE
        SIGNAL CFG
        SIGNAL ADDR(10:0)
        SIGNAL ADDR(0)
        SIGNAL ADDR(1)
        SIGNAL XLXN_206
        SIGNAL XLXN_208
        SIGNAL PLLPD
        SIGNAL CLKREF
        SIGNAL SP(7:0)
        SIGNAL LP(7:0)
        SIGNAL SP(7)
        SIGNAL SP(6)
        SIGNAL SP(5)
        SIGNAL SP(4)
        SIGNAL SP(3)
        SIGNAL SP(2)
        SIGNAL SP(1)
        SIGNAL SP(0)
        SIGNAL LP(7)
        SIGNAL LP(6)
        SIGNAL LP(5)
        SIGNAL LP(4)
        SIGNAL LP(3)
        SIGNAL LP(2)
        SIGNAL LP(1)
        SIGNAL LP(0)
        SIGNAL ADDR(6)
        SIGNAL ADDR(7)
        SIGNAL ADDR(2)
        SIGNAL ADDR(3)
        SIGNAL ADDR(4)
        SIGNAL ADDR(5)
        SIGNAL XLXN_253
        SIGNAL XLXN_257
        SIGNAL XLXN_266
        SIGNAL XLXN_272
        SIGNAL XLXN_274
        SIGNAL XLXN_275
        SIGNAL XLXN_276
        SIGNAL XLXN_277
        SIGNAL XLXN_278
        SIGNAL ADDR(7:0)
        SIGNAL CTL_FULL
        SIGNAL CTL_TX
        SIGNAL XLXN_289
        SIGNAL CTL_BLIND
        SIGNAL XLXN_292
        SIGNAL XLXN_294
        SIGNAL XLXN_297
        SIGNAL XLXN_298
        SIGNAL ML
        SIGNAL XLXN_305
        SIGNAL ADDR(5:0)
        SIGNAL XLXN_317
        SIGNAL XLXN_319
        SIGNAL XLXN_324
        SIGNAL XLXN_326
        SIGNAL XLXN_330
        SIGNAL XLXN_334
        SIGNAL XLXN_335
        SIGNAL XLXN_339
        SIGNAL TXBITS
        SIGNAL XLXN_344
        SIGNAL XLXN_350
        SIGNAL XLXN_354
        SIGNAL XLXN_355
        SIGNAL XLXN_356
        SIGNAL XLXN_357
        SIGNAL XLXN_358
        SIGNAL XLXN_359
        SIGNAL XLXN_360
        SIGNAL XLXN_361
        SIGNAL XLXN_364
        SIGNAL XLXN_365
        SIGNAL XLXN_366
        SIGNAL XLXN_368
        SIGNAL XLXN_132(7:0)
        SIGNAL TXL(7:0)
        SIGNAL TXL(7)
        SIGNAL TXL(6)
        SIGNAL TXL(5)
        SIGNAL TXL(4)
        SIGNAL TXL(3)
        SIGNAL TXL(2)
        SIGNAL TXL(1)
        SIGNAL TXL(0)
        SIGNAL XLXN_142
        SIGNAL TXD(7)
        SIGNAL TXD(6)
        SIGNAL TXD(5)
        SIGNAL TXD(4)
        SIGNAL TXD(3)
        SIGNAL TXD(7:0)
        SIGNAL TXD4
        SIGNAL TXD3
        SIGNAL TXD2
        SIGNAL TXD1
        SIGNAL TXD0
        SIGNAL BCLKI
        SIGNAL XLXN_316
        SIGNAL XLXN_409
        SIGNAL XLXN_417
        SIGNAL XLXN_418
        SIGNAL BFLD
        SIGNAL XLXN_430
        SIGNAL XLXN_433
        SIGNAL XLXN_434
        SIGNAL TEST
        SIGNAL XLXN_439
        SIGNAL XLXN_440
        SIGNAL MCLK
        SIGNAL MDATA
        PORT Input DATA(7:0)
        PORT Input BIT0
        PORT Input BIT1
        PORT Input BIT2
        PORT Input BCLK
        PORT Output TXEN
        PORT Input CFG
        PORT Input ADDR(10:0)
        PORT Output PLLPD
        PORT Input CLKREF
        PORT Output ML
        PORT Output TXBITS
        PORT Output TXD4
        PORT Output TXD3
        PORT Output TXD2
        PORT Output TXD1
        PORT Output TXD0
        PORT Output TEST
        PORT Output MCLK
        PORT Output MDATA
        BEGIN BLOCKDEF m8_1e
            TIMESTAMP 2001 2 2 12 39 29
            LINE N 0 -224 96 -224 
            LINE N 0 -160 96 -160 
            LINE N 0 -96 96 -96 
            LINE N 0 -288 96 -288 
            LINE N 0 -352 96 -352 
            LINE N 0 -416 96 -416 
            LINE N 0 -544 96 -544 
            LINE N 0 -608 96 -608 
            LINE N 0 -672 96 -672 
            LINE N 0 -736 96 -736 
            LINE N 160 -160 96 -160 
            LINE N 160 -268 160 -160 
            LINE N 128 -224 96 -224 
            LINE N 128 -264 128 -224 
            LINE N 192 -96 96 -96 
            LINE N 192 -276 192 -96 
            LINE N 224 -32 96 -32 
            LINE N 224 -280 224 -32 
            LINE N 320 -512 256 -512 
            LINE N 96 -768 96 -256 
            LINE N 256 -704 96 -768 
            LINE N 256 -288 256 -704 
            LINE N 96 -256 256 -288 
            LINE N 0 -32 96 -32 
            LINE N 0 -480 96 -480 
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
        BEGIN BLOCKDEF gnd
            TIMESTAMP 2001 2 2 12 37 29
            LINE N 64 -64 64 -96 
            LINE N 76 -48 52 -48 
            LINE N 68 -32 60 -32 
            LINE N 88 -64 40 -64 
            LINE N 64 -64 64 -80 
            LINE N 64 -128 64 -96 
        END BLOCKDEF
        BEGIN BLOCKDEF buf
            TIMESTAMP 2001 2 2 12 35 54
            LINE N 0 -32 64 -32 
            LINE N 224 -32 128 -32 
            LINE N 64 0 128 -32 
            LINE N 128 -32 64 -64 
            LINE N 64 -64 64 0 
        END BLOCKDEF
        BEGIN BLOCKDEF vcc
            TIMESTAMP 2001 2 2 12 37 29
            LINE N 64 -32 64 -64 
            LINE N 64 0 64 -32 
            LINE N 96 -64 32 -64 
        END BLOCKDEF
        BEGIN BLOCKDEF firgauss
            TIMESTAMP 2006 1 6 21 18 13
            RECTANGLE N 64 -192 320 0 
            LINE N 64 -160 0 -160 
            LINE N 64 -96 0 -96 
            LINE N 64 -32 0 -32 
            RECTANGLE N 320 -172 384 -148 
            LINE N 320 -160 384 -160 
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
        BEGIN BLOCKDEF fd
            TIMESTAMP 2001 2 2 12 37 14
            RECTANGLE N 64 -320 320 -64 
            LINE N 0 -128 64 -128 
            LINE N 0 -256 64 -256 
            LINE N 384 -256 320 -256 
            LINE N 80 -128 64 -144 
            LINE N 64 -112 80 -128 
        END BLOCKDEF
        BEGIN BLOCKDEF nor3
            TIMESTAMP 2001 2 2 12 38 38
            LINE N 0 -64 48 -64 
            LINE N 0 -128 72 -128 
            LINE N 0 -192 48 -192 
            LINE N 256 -128 216 -128 
            CIRCLE N 192 -140 216 -116 
            LINE N 48 -64 48 -80 
            LINE N 48 -192 48 -176 
            LINE N 112 -80 48 -80 
            LINE N 112 -176 48 -176 
            ARC N -40 -184 72 -72 48 -80 48 -176 
            ARC N 28 -256 204 -80 112 -80 192 -128 
            ARC N 28 -176 204 0 192 -128 112 -176 
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
        BEGIN BLOCKDEF d2_4e
            TIMESTAMP 2001 2 2 12 36 51
            RECTANGLE N 64 -384 320 -64 
            LINE N 0 -128 64 -128 
            LINE N 0 -256 64 -256 
            LINE N 0 -320 64 -320 
            LINE N 384 -128 320 -128 
            LINE N 384 -192 320 -192 
            LINE N 384 -256 320 -256 
            LINE N 384 -320 320 -320 
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
        BEGIN BLOCKDEF or4
            TIMESTAMP 2001 4 25 16 50 36
            LINE N 0 -64 48 -64 
            LINE N 0 -128 64 -128 
            LINE N 0 -192 64 -192 
            LINE N 0 -256 48 -256 
            LINE N 256 -160 192 -160 
            ARC N 28 -208 204 -32 192 -160 112 -208 
            LINE N 112 -208 48 -208 
            LINE N 112 -112 48 -112 
            LINE N 48 -256 48 -208 
            LINE N 48 -64 48 -112 
            ARC N -40 -216 72 -104 48 -112 48 -208 
            ARC N 28 -288 204 -112 112 -112 192 -160 
        END BLOCKDEF
        BEGIN BLOCKDEF cb4cle
            TIMESTAMP 2001 2 2 12 36 39
            RECTANGLE N 64 -640 320 -64 
            LINE N 0 -256 64 -256 
            LINE N 0 -192 64 -192 
            LINE N 0 -576 64 -576 
            LINE N 0 -512 64 -512 
            LINE N 0 -448 64 -448 
            LINE N 192 -32 64 -32 
            LINE N 192 -64 192 -32 
            LINE N 80 -128 64 -144 
            LINE N 64 -112 80 -128 
            LINE N 0 -128 64 -128 
            LINE N 0 -32 64 -32 
            LINE N 0 -384 64 -384 
            LINE N 384 -576 320 -576 
            LINE N 384 -512 320 -512 
            LINE N 384 -448 320 -448 
            LINE N 384 -384 320 -384 
            LINE N 384 -192 320 -192 
            LINE N 384 -128 320 -128 
        END BLOCKDEF
        BEGIN BLOCKDEF cb2cle
            TIMESTAMP 2001 2 2 12 36 39
            RECTANGLE N 64 -512 320 -64 
            LINE N 0 -256 64 -256 
            LINE N 0 -32 64 -32 
            LINE N 0 -128 64 -128 
            LINE N 80 -128 64 -144 
            LINE N 64 -112 80 -128 
            LINE N 192 -32 64 -32 
            LINE N 192 -64 192 -32 
            LINE N 0 -192 64 -192 
            LINE N 0 -448 64 -448 
            LINE N 0 -384 64 -384 
            LINE N 384 -448 320 -448 
            LINE N 384 -384 320 -384 
            LINE N 384 -192 320 -192 
            LINE N 384 -128 320 -128 
        END BLOCKDEF
        BEGIN BLOCKDEF or3
            TIMESTAMP 2001 2 2 12 38 38
            LINE N 0 -64 48 -64 
            LINE N 0 -128 72 -128 
            LINE N 0 -192 48 -192 
            LINE N 256 -128 192 -128 
            ARC N 28 -256 204 -80 112 -80 192 -128 
            ARC N -40 -184 72 -72 48 -80 48 -176 
            LINE N 48 -64 48 -80 
            LINE N 48 -192 48 -176 
            LINE N 112 -80 48 -80 
            ARC N 28 -176 204 0 192 -128 112 -176 
            LINE N 112 -176 48 -176 
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
        BEGIN BLOCKDEF nor6
            TIMESTAMP 2001 2 2 12 25 36
            LINE N 52 -176 48 -176 
            LINE N 52 -176 68 -176 
            LINE N 48 -272 68 -272 
            LINE N 32 -256 64 -256 
            LINE N 128 -272 64 -272 
            LINE N 48 -64 48 -176 
            LINE N 0 -192 64 -192 
            LINE N 0 -128 48 -128 
            LINE N 0 -64 48 -64 
            LINE N 256 -224 228 -224 
            CIRCLE N 208 -236 228 -216 
            LINE N 0 -384 48 -384 
            LINE N 0 -320 48 -320 
            LINE N 0 -256 64 -256 
            LINE N 48 -272 48 -384 
            ARC N 44 -352 220 -176 128 -176 208 -224 
            LINE N 128 -176 64 -176 
            ARC N 44 -272 220 -96 208 -224 128 -272 
            ARC N -40 -280 72 -168 48 -176 48 -272 
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
        BEGIN BLOCKDEF and5
            TIMESTAMP 2001 2 2 12 38 38
            ARC N 96 -240 192 -144 144 -144 144 -240 
            LINE N 144 -144 64 -144 
            LINE N 64 -240 144 -240 
            LINE N 64 -64 64 -320 
            LINE N 256 -192 192 -192 
            LINE N 0 -320 64 -320 
            LINE N 0 -256 64 -256 
            LINE N 0 -192 64 -192 
            LINE N 0 -128 64 -128 
            LINE N 0 -64 64 -64 
        END BLOCKDEF
        BEGIN BLOCKDEF xcrc
            TIMESTAMP 2006 2 5 20 50 1
            LINE N 320 32 384 32 
            LINE N 64 -224 0 -224 
            LINE N 64 -160 0 -160 
            LINE N 64 -96 0 -96 
            LINE N 64 -32 0 -32 
            LINE N 320 -224 384 -224 
            LINE N 320 -32 384 -32 
            RECTANGLE N 64 -256 320 64 
        END BLOCKDEF
        BEGIN BLOCK XLXI_1 m8_1e
            PIN D0 DATA(7)
            PIN D1 DATA(6)
            PIN D2 DATA(5)
            PIN D3 DATA(4)
            PIN D4 DATA(3)
            PIN D5 DATA(2)
            PIN D6 DATA(1)
            PIN D7 DATA(0)
            PIN E XLXN_187
            PIN S0 BIT0
            PIN S1 BIT1
            PIN S2 BIT2
            PIN O XLXN_189
        END BLOCK
        BEGIN BLOCK XLXI_111 firgauss
            PIN DATA XLXN_433
            PIN E XLXN_434
            PIN CLK CLKREF
            PIN Q(7:0) XLXN_132(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_186 vcc
            PIN P XLXN_187
        END BLOCK
        BEGIN BLOCK XLXI_187 inv
            PIN I BCLK
            PIN O BCLKI
        END BLOCK
        BEGIN BLOCK XLXI_188 fd
            PIN C BCLKI
            PIN D XLXN_189
            PIN Q TXBITS
        END BLOCK
        BEGIN BLOCK XLXI_189 buf
            PIN I XLXN_434
            PIN O TXEN
        END BLOCK
        BEGIN BLOCK XLXI_190 nor3
            PIN I0 BIT0
            PIN I1 BIT1
            PIN I2 BIT2
            PIN O BYTE
        END BLOCK
        BEGIN BLOCK XLXI_191 fd4ce
            PIN C BCLKI
            PIN CE XLXN_208
            PIN CLR XLXN_257
            PIN D0 DATA(7)
            PIN D1 DATA(6)
            PIN D2 DATA(5)
            PIN D3 XLXN_257
            PIN Q0 CTL_TX
            PIN Q1 CTL_FULL
            PIN Q2 CTL_BLIND
            PIN Q3
        END BLOCK
        BEGIN BLOCK XLXI_193 d2_4e
            PIN A0 ADDR(0)
            PIN A1 ADDR(1)
            PIN E CFG
            PIN D0 XLXN_206
            PIN D1 XLXN_275
            PIN D2 XLXN_274
            PIN D3
        END BLOCK
        BEGIN BLOCK XLXI_194 and2
            PIN I0 XLXN_206
            PIN I1 BYTE
            PIN O XLXN_208
        END BLOCK
        BEGIN BLOCK XLXI_195 or2
            PIN I0 XLXN_409
            PIN I1 XLXN_434
            PIN O PLLPD
        END BLOCK
        BEGIN BLOCK XLXI_198 compm8
            PIN A(7:0) ADDR(7:0)
            PIN B(7:0) SP(7:0)
            PIN GT
            PIN LT XLXN_356
        END BLOCK
        BEGIN BLOCK XLXI_201 compm8
            PIN A(7:0) ADDR(7:0)
            PIN B(7:0) LP(7:0)
            PIN GT
            PIN LT XLXN_357
        END BLOCK
        BEGIN BLOCK XLXI_204 gnd
            PIN G SP(5)
        END BLOCK
        BEGIN BLOCK XLXI_210 vcc
            PIN P LP(5)
        END BLOCK
        BEGIN BLOCK XLXI_211 vcc
            PIN P LP(4)
        END BLOCK
        BEGIN BLOCK XLXI_212 vcc
            PIN P LP(3)
        END BLOCK
        BEGIN BLOCK XLXI_213 gnd
            PIN G LP(2)
        END BLOCK
        BEGIN BLOCK XLXI_214 gnd
            PIN G LP(1)
        END BLOCK
        BEGIN BLOCK XLXI_215 gnd
            PIN G LP(0)
        END BLOCK
        BEGIN BLOCK XLXI_216 buf
            PIN I ADDR(7)
            PIN O SP(7)
        END BLOCK
        BEGIN BLOCK XLXI_217 buf
            PIN I ADDR(6)
            PIN O SP(6)
        END BLOCK
        BEGIN BLOCK XLXI_218 buf
            PIN I ADDR(7)
            PIN O LP(7)
        END BLOCK
        BEGIN BLOCK XLXI_219 buf
            PIN I ADDR(6)
            PIN O LP(6)
        END BLOCK
        BEGIN BLOCK XLXI_221 or4
            PIN I0 ADDR(5)
            PIN I1 ADDR(4)
            PIN I2 ADDR(3)
            PIN I3 ADDR(2)
            PIN O XLXN_253
        END BLOCK
        BEGIN BLOCK XLXI_222 and2
            PIN I0 XLXN_354
            PIN I1 XLXN_253
            PIN O XLXN_277
        END BLOCK
        BEGIN BLOCK XLXI_223 and2
            PIN I0 XLXN_355
            PIN I1 XLXN_253
            PIN O XLXN_278
        END BLOCK
        BEGIN BLOCK XLXI_224 cb4cle
            PIN C BCLKI
            PIN CE XLXN_272
            PIN CLR XLXN_257
            PIN D0 DATA(0)
            PIN D1 DATA(1)
            PIN D2 DATA(2)
            PIN D3 DATA(3)
            PIN L XLXN_208
            PIN CEO XLXN_266
            PIN Q0
            PIN Q1
            PIN Q2
            PIN Q3 XLXN_366
            PIN TC
        END BLOCK
        BEGIN BLOCK XLXI_225 cb2cle
            PIN C BCLKI
            PIN CE XLXN_266
            PIN CLR XLXN_257
            PIN D0 DATA(4)
            PIN D1 XLXN_257
            PIN L XLXN_208
            PIN CEO
            PIN Q0 XLXN_365
            PIN Q1
            PIN TC
        END BLOCK
        BEGIN BLOCK XLXI_227 or3
            PIN I0 XLXN_368
            PIN I1 XLXN_274
            PIN I2 XLXN_275
            PIN O XLXN_276
        END BLOCK
        BEGIN BLOCK XLXI_228 fd
            PIN C BCLKI
            PIN D XLXN_278
            PIN Q XLXN_417
        END BLOCK
        BEGIN BLOCK XLXI_229 fd
            PIN C BCLKI
            PIN D XLXN_277
            PIN Q XLXN_418
        END BLOCK
        BEGIN BLOCK XLXI_230 fd
            PIN C BCLKI
            PIN D XLXN_276
            PIN Q XLXN_305
        END BLOCK
        BEGIN BLOCK XLXI_232 m2_1
            PIN D0 XLXN_418
            PIN D1 XLXN_417
            PIN S0 CTL_FULL
            PIN O XLXN_289
        END BLOCK
        BEGIN BLOCK XLXI_233 and2
            PIN I0 CTL_TX
            PIN I1 XLXN_289
            PIN O XLXN_430
        END BLOCK
        BEGIN BLOCK XLXI_235 or3
            PIN I0 CTL_TX
            PIN I1 CTL_FULL
            PIN I2 CTL_BLIND
            PIN O XLXN_316
        END BLOCK
        BEGIN BLOCK XLXI_236 m2_1
            PIN D0 BCLKI
            PIN D1 XLXN_294
            PIN S0 XLXN_292
            PIN O XLXN_297
        END BLOCK
        BEGIN BLOCK XLXI_237 m2_1
            PIN D0 TXBITS
            PIN D1 XLXN_294
            PIN S0 XLXN_292
            PIN O XLXN_298
        END BLOCK
        BEGIN BLOCK XLXI_239 and2
            PIN I0 XLXN_297
            PIN I1 XLXN_316
            PIN O XLXN_439
        END BLOCK
        BEGIN BLOCK XLXI_240 and2
            PIN I0 XLXN_298
            PIN I1 XLXN_316
            PIN O XLXN_440
        END BLOCK
        BEGIN BLOCK XLXI_241 and2
            PIN I0 XLXN_305
            PIN I1 XLXN_316
            PIN O ML
        END BLOCK
        BEGIN BLOCK XLXI_242 nand2b1
            PIN I0 XLXN_272
            PIN I1 XLXN_305
            PIN O XLXN_292
        END BLOCK
        BEGIN BLOCK XLXI_245 inv
            PIN I XLXN_364
            PIN O XLXN_272
        END BLOCK
        BEGIN BLOCK XLXI_246 gnd
            PIN G XLXN_257
        END BLOCK
        BEGIN BLOCK XLXI_247 nor6
            PIN I0 ADDR(5)
            PIN I1 ADDR(4)
            PIN I2 ADDR(3)
            PIN I3 XLXN_361
            PIN I4 ADDR(1)
            PIN I5 XLXN_344
            PIN O XLXN_359
        END BLOCK
        BEGIN BLOCK XLXI_249 and2
            PIN I0 XLXN_317
            PIN I1 XLXN_360
            PIN O XLXN_409
        END BLOCK
        BEGIN BLOCK XLXI_250 and2b1
            PIN I0 CTL_TX
            PIN I1 CTL_FULL
            PIN O XLXN_317
        END BLOCK
        BEGIN BLOCK XLXI_251 srl16
            PIN A0 XLXN_319
            PIN A1 XLXN_319
            PIN A2 XLXN_319
            PIN A3 XLXN_319
            PIN CLK BCLKI
            PIN D CFG
            PIN Q XLXN_324
        END BLOCK
        BEGIN BLOCK XLXI_252 vcc
            PIN P XLXN_319
        END BLOCK
        BEGIN BLOCK XLXI_253 or4
            PIN I0 XLXN_289
            PIN I1 CTL_BLIND
            PIN I2 CFG
            PIN I3 XLXN_334
            PIN O XLXN_294
        END BLOCK
        BEGIN BLOCK XLXI_254 srl16
            PIN A0 XLXN_326
            PIN A1 XLXN_326
            PIN A2 XLXN_326
            PIN A3 XLXN_326
            PIN CLK BCLKI
            PIN D XLXN_324
            PIN Q XLXN_330
        END BLOCK
        BEGIN BLOCK XLXI_255 vcc
            PIN P XLXN_326
        END BLOCK
        BEGIN BLOCK XLXI_256 srl16
            PIN A0 XLXN_339
            PIN A1 XLXN_339
            PIN A2 XLXN_339
            PIN A3 XLXN_339
            PIN CLK BCLKI
            PIN D XLXN_330
            PIN Q XLXN_335
        END BLOCK
        BEGIN BLOCK XLXI_258 gnd
            PIN G XLXN_339
        END BLOCK
        BEGIN BLOCK XLXI_259 vcc
            PIN P SP(4)
        END BLOCK
        BEGIN BLOCK XLXI_260 gnd
            PIN G SP(3)
        END BLOCK
        BEGIN BLOCK XLXI_261 gnd
            PIN G SP(2)
        END BLOCK
        BEGIN BLOCK XLXI_266 gnd
            PIN G XLXN_344
        END BLOCK
        BEGIN BLOCK XLXI_269 and2
            PIN I0 XLXN_350
            PIN I1 CTL_TX
            PIN O XLXN_358
        END BLOCK
        BEGIN BLOCK XLXI_270 or2
            PIN I0 XLXN_358
            PIN I1 XLXN_356
            PIN O XLXN_354
        END BLOCK
        BEGIN BLOCK XLXI_271 or2
            PIN I0 XLXN_358
            PIN I1 XLXN_357
            PIN O XLXN_355
        END BLOCK
        BEGIN BLOCK XLXI_272 and5
            PIN I0 ADDR(2)
            PIN I1 ADDR(1)
            PIN I2 ADDR(3)
            PIN I3 ADDR(4)
            PIN I4 ADDR(5)
            PIN O XLXN_350
        END BLOCK
        BEGIN BLOCK XLXI_273 or2
            PIN I0 XLXN_350
            PIN I1 XLXN_359
            PIN O XLXN_360
        END BLOCK
        BEGIN BLOCK XLXI_274 inv
            PIN I ADDR(2)
            PIN O XLXN_361
        END BLOCK
        BEGIN BLOCK XLXI_278 gnd
            PIN G SP(1)
        END BLOCK
        BEGIN BLOCK XLXI_280 and2
            PIN I0 XLXN_365
            PIN I1 XLXN_366
            PIN O XLXN_364
        END BLOCK
        BEGIN BLOCK XLXI_281 and2b1
            PIN I0 BYTE
            PIN I1 XLXN_206
            PIN O XLXN_368
        END BLOCK
        BEGIN BLOCK XLXI_112 add8
            PIN A(7:0) XLXN_132(7:0)
            PIN B(7:0) TXL(7:0)
            PIN CI XLXN_142
            PIN CO
            PIN OFL
            PIN S(7:0) TXD(7:0)
        END BLOCK
        BEGIN BLOCK XLXI_117 gnd
            PIN G TXL(3)
        END BLOCK
        BEGIN BLOCK XLXI_118 gnd
            PIN G TXL(2)
        END BLOCK
        BEGIN BLOCK XLXI_119 gnd
            PIN G TXL(1)
        END BLOCK
        BEGIN BLOCK XLXI_120 gnd
            PIN G TXL(0)
        END BLOCK
        BEGIN BLOCK XLXI_121 gnd
            PIN G XLXN_142
        END BLOCK
        BEGIN BLOCK XLXI_122 buf
            PIN I TXD(7)
            PIN O TXD4
        END BLOCK
        BEGIN BLOCK XLXI_123 buf
            PIN I TXD(6)
            PIN O TXD3
        END BLOCK
        BEGIN BLOCK XLXI_124 buf
            PIN I TXD(5)
            PIN O TXD2
        END BLOCK
        BEGIN BLOCK XLXI_125 buf
            PIN I TXD(4)
            PIN O TXD1
        END BLOCK
        BEGIN BLOCK XLXI_126 buf
            PIN I TXD(3)
            PIN O TXD0
        END BLOCK
        BEGIN BLOCK XLXI_153 vcc
            PIN P TXL(7)
        END BLOCK
        BEGIN BLOCK XLXI_306 gnd
            PIN G SP(0)
        END BLOCK
        BEGIN BLOCK XLXI_307 and2b1
            PIN I0 XLXN_418
            PIN I1 XLXN_417
            PIN O BFLD
        END BLOCK
        BEGIN BLOCK XLXI_311 or3
            PIN I0 XLXN_434
            PIN I1 XLXN_335
            PIN I2 XLXN_330
            PIN O XLXN_334
        END BLOCK
        BEGIN BLOCK XLXI_313 xcrc
            PIN D_IN TXBITS
            PIN TXE_IN XLXN_430
            PIN B_FLD BFLD
            PIN BCLK BCLKI
            PIN TXE_OUT XLXN_434
            PIN D_OUT XLXN_433
            PIN TEST TEST
        END BLOCK
        BEGIN BLOCK XLXI_314 or2
            PIN I0 XLXN_434
            PIN I1 XLXN_439
            PIN O MCLK
        END BLOCK
        BEGIN BLOCK XLXI_315 or2
            PIN I0 XLXN_434
            PIN I1 XLXN_440
            PIN O MDATA
        END BLOCK
        BEGIN BLOCK XLXI_316 gnd
            PIN G TXL(6)
        END BLOCK
        BEGIN BLOCK XLXI_317 vcc
            PIN P TXL(5)
        END BLOCK
        BEGIN BLOCK XLXI_319 gnd
            PIN G TXL(4)
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 7040 5440
        IOMARKER 320 320 DATA(7:0) R180 28
        BUSTAP 480 960 576 960
        BUSTAP 480 896 576 896
        INSTANCE XLXI_1 720 1248 R0
        BUSTAP 480 832 576 832
        BUSTAP 480 768 576 768
        BUSTAP 480 704 576 704
        BUSTAP 480 640 576 640
        BUSTAP 480 576 576 576
        BUSTAP 480 512 576 512
        BEGIN BRANCH BIT0
            WIRE 320 1024 496 1024
            WIRE 496 1024 720 1024
            WIRE 496 1024 496 1584
            WIRE 496 1584 624 1584
        END BRANCH
        BEGIN BRANCH BIT1
            WIRE 320 1088 512 1088
            WIRE 512 1088 720 1088
            WIRE 512 1088 512 1520
            WIRE 512 1520 624 1520
        END BRANCH
        BEGIN BRANCH BIT2
            WIRE 320 1152 528 1152
            WIRE 528 1152 720 1152
            WIRE 528 1152 528 1456
            WIRE 528 1456 624 1456
        END BRANCH
        IOMARKER 320 1024 BIT0 R180 28
        IOMARKER 320 1088 BIT1 R180 28
        IOMARKER 320 1152 BIT2 R180 28
        BEGIN BRANCH DATA(7)
            WIRE 576 512 720 512
        END BRANCH
        BEGIN BRANCH DATA(6)
            WIRE 576 576 720 576
        END BRANCH
        BEGIN BRANCH DATA(5)
            WIRE 576 640 720 640
        END BRANCH
        BEGIN BRANCH DATA(4)
            WIRE 576 704 720 704
        END BRANCH
        BEGIN BRANCH DATA(3)
            WIRE 576 768 720 768
        END BRANCH
        BEGIN BRANCH DATA(2)
            WIRE 576 832 720 832
        END BRANCH
        BEGIN BRANCH DATA(1)
            WIRE 576 896 720 896
        END BRANCH
        BEGIN BRANCH DATA(0)
            WIRE 576 960 720 960
        END BRANCH
        BEGIN BRANCH XLXN_187
            WIRE 688 1216 720 1216
        END BRANCH
        BEGIN BRANCH BCLK
            WIRE 320 1360 816 1360
        END BRANCH
        IOMARKER 320 1360 BCLK R180 28
        INSTANCE XLXI_188 1120 992 R0
        BEGIN BRANCH XLXN_189
            WIRE 1040 736 1120 736
        END BRANCH
        BEGIN BRANCH TXEN
            WIRE 5088 1248 5120 1248
        END BRANCH
        INSTANCE XLXI_187 816 1392 R0
        INSTANCE XLXI_186 688 1280 R270
        INSTANCE XLXI_190 624 1648 R0
        INSTANCE XLXI_191 2000 864 R0
        BUSTAP 1760 416 1856 416
        BUSTAP 1760 480 1856 480
        BUSTAP 1760 544 1856 544
        BEGIN BRANCH DATA(7:0)
            WIRE 320 320 480 320
            WIRE 480 320 480 512
            WIRE 480 512 480 576
            WIRE 480 576 480 640
            WIRE 480 640 480 704
            WIRE 480 704 480 768
            WIRE 480 768 480 832
            WIRE 480 832 480 896
            WIRE 480 896 480 960
            WIRE 480 320 1760 320
            WIRE 1760 320 1760 416
            WIRE 1760 416 1760 480
            WIRE 1760 480 1760 544
            WIRE 1760 544 1760 976
            WIRE 1760 976 1760 1040
            WIRE 1760 1040 1760 1104
            WIRE 1760 1104 1760 1168
            WIRE 1760 1168 1760 1680
        END BRANCH
        BEGIN BRANCH DATA(7)
            WIRE 1856 416 1888 416
            WIRE 1888 416 2000 416
            BEGIN DISPLAY 1888 416 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH DATA(6)
            WIRE 1856 480 1888 480
            WIRE 1888 480 2000 480
            BEGIN DISPLAY 1888 480 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH DATA(5)
            WIRE 1856 544 1888 544
            WIRE 1888 544 2000 544
            BEGIN DISPLAY 1888 544 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH BYTE
            WIRE 880 1520 1120 1520
            WIRE 1120 1520 1120 1664
            WIRE 1120 1664 1248 1664
            WIRE 1120 1664 1120 1888
            WIRE 1120 1888 1248 1888
        END BRANCH
        BEGIN BRANCH CFG
            WIRE 320 1760 672 1760
            WIRE 672 1760 672 2176
            WIRE 672 2176 736 2176
            WIRE 672 2176 672 2320
            WIRE 672 2320 3360 2320
            WIRE 3360 2320 3360 2752
            WIRE 3360 2752 3472 2752
            WIRE 3360 2752 3360 3040
            WIRE 3360 3040 3424 3040
        END BRANCH
        IOMARKER 320 1760 CFG R180 28
        IOMARKER 320 1920 ADDR(10:0) R180 28
        INSTANCE XLXI_193 736 2304 R0
        BUSTAP 480 1984 576 1984
        BUSTAP 480 2048 576 2048
        BEGIN BRANCH ADDR(0)
            WIRE 576 1984 592 1984
            WIRE 592 1984 736 1984
            BEGIN DISPLAY 592 1984 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH ADDR(1)
            WIRE 576 2048 592 2048
            WIRE 592 2048 736 2048
            BEGIN DISPLAY 592 2048 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        INSTANCE XLXI_194 1248 1792 R0
        BEGIN BRANCH XLXN_206
            WIRE 1120 1984 1184 1984
            WIRE 1184 1728 1248 1728
            WIRE 1184 1728 1184 1824
            WIRE 1184 1824 1184 1984
            WIRE 1184 1824 1248 1824
        END BRANCH
        BEGIN BRANCH XLXN_208
            WIRE 1504 1696 1680 1696
            WIRE 1680 1696 1680 1872
            WIRE 1680 1872 2000 1872
            WIRE 1680 672 2000 672
            WIRE 1680 672 1680 1296
            WIRE 1680 1296 1680 1696
            WIRE 1680 1296 2000 1296
        END BRANCH
        BEGIN BRANCH PLLPD
            WIRE 4960 1456 5120 1456
        END BRANCH
        BEGIN BRANCH CLKREF
            WIRE 320 160 4960 160
            WIRE 4960 160 4960 528
            WIRE 4960 528 5008 528
        END BRANCH
        IOMARKER 320 160 CLKREF R180 28
        BUSTAP 928 2672 928 2768
        BUSTAP 864 2672 864 2768
        BUSTAP 800 2672 800 2768
        BUSTAP 736 2672 736 2768
        BUSTAP 672 2672 672 2768
        BUSTAP 608 2672 608 2768
        BUSTAP 544 2672 544 2768
        INSTANCE XLXI_198 1040 2800 R0
        BEGIN BRANCH SP(7:0)
            WIRE 544 2672 608 2672
            WIRE 608 2672 672 2672
            WIRE 672 2672 736 2672
            WIRE 736 2672 800 2672
            WIRE 800 2672 864 2672
            WIRE 864 2672 928 2672
            WIRE 928 2672 992 2672
            WIRE 992 2672 1040 2672
        END BRANCH
        BUSTAP 992 2672 992 2768
        INSTANCE XLXI_201 1040 3360 R0
        BEGIN BRANCH LP(7:0)
            WIRE 544 3232 608 3232
            WIRE 608 3232 672 3232
            WIRE 672 3232 736 3232
            WIRE 736 3232 800 3232
            WIRE 800 3232 864 3232
            WIRE 864 3232 928 3232
            WIRE 928 3232 992 3232
            WIRE 992 3232 1040 3232
        END BRANCH
        BUSTAP 544 3232 544 3328
        BUSTAP 608 3232 608 3328
        BUSTAP 672 3232 672 3328
        BUSTAP 736 3232 736 3328
        BUSTAP 800 3232 800 3328
        BUSTAP 864 3232 864 3328
        BUSTAP 928 3232 928 3328
        BUSTAP 992 3232 992 3328
        INSTANCE XLXI_204 608 2944 R0
        BEGIN BRANCH SP(7)
            WIRE 400 2816 400 2832
            WIRE 400 2832 544 2832
            WIRE 544 2768 544 2832
        END BRANCH
        BEGIN BRANCH SP(6)
            WIRE 336 2816 336 2848
            WIRE 336 2848 608 2848
            WIRE 608 2768 608 2848
        END BRANCH
        BEGIN BRANCH SP(5)
            WIRE 672 2768 672 2816
        END BRANCH
        BEGIN BRANCH SP(4)
            WIRE 736 2768 736 2816
        END BRANCH
        BEGIN BRANCH SP(3)
            WIRE 800 2768 800 2816
        END BRANCH
        BEGIN BRANCH SP(2)
            WIRE 864 2768 864 2816
        END BRANCH
        BEGIN BRANCH SP(1)
            WIRE 928 2768 928 2816
        END BRANCH
        BEGIN BRANCH SP(0)
            WIRE 992 2768 992 2816
        END BRANCH
        BEGIN DISPLAY 544 2644 TEXT "Short Packet Length"
            FONT 32 "Arial"
        END DISPLAY
        BEGIN DISPLAY 544 3200 TEXT "Long Packet Length"
            FONT 32 "Arial"
        END DISPLAY
        INSTANCE XLXI_210 736 3376 R180
        INSTANCE XLXI_211 800 3376 R180
        INSTANCE XLXI_212 864 3376 R180
        INSTANCE XLXI_213 800 3504 R0
        INSTANCE XLXI_214 864 3504 R0
        INSTANCE XLXI_215 928 3504 R0
        BEGIN BRANCH LP(7)
            WIRE 240 3360 240 3376
            WIRE 240 3376 544 3376
            WIRE 544 3328 544 3376
        END BRANCH
        BEGIN BRANCH LP(6)
            WIRE 176 3360 176 3392
            WIRE 176 3392 608 3392
            WIRE 608 3328 608 3392
        END BRANCH
        BEGIN BRANCH LP(5)
            WIRE 672 3328 672 3376
        END BRANCH
        BEGIN BRANCH LP(4)
            WIRE 736 3328 736 3376
        END BRANCH
        BEGIN BRANCH LP(3)
            WIRE 800 3328 800 3376
        END BRANCH
        BEGIN BRANCH LP(2)
            WIRE 864 3328 864 3376
        END BRANCH
        BEGIN BRANCH LP(1)
            WIRE 928 3328 928 3376
        END BRANCH
        BEGIN BRANCH LP(0)
            WIRE 992 3328 992 3376
        END BRANCH
        INSTANCE XLXI_216 368 2592 R90
        INSTANCE XLXI_217 304 2592 R90
        INSTANCE XLXI_218 208 3136 R90
        INSTANCE XLXI_219 144 3136 R90
        BUSTAP 480 2320 384 2320
        BUSTAP 480 2256 384 2256
        BEGIN BRANCH ADDR(6)
            WIRE 176 2256 176 2528
            WIRE 176 2528 176 3136
            WIRE 176 2528 336 2528
            WIRE 336 2528 336 2592
            WIRE 176 2256 368 2256
            WIRE 368 2256 384 2256
            BEGIN DISPLAY 368 2256 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH ADDR(7)
            WIRE 240 2320 240 2496
            WIRE 240 2496 240 3136
            WIRE 240 2496 400 2496
            WIRE 400 2496 400 2592
            WIRE 240 2320 368 2320
            WIRE 368 2320 384 2320
            BEGIN DISPLAY 368 2320 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BUSTAP 1600 2352 1696 2352
        BUSTAP 1600 2416 1696 2416
        BUSTAP 1600 2480 1696 2480
        BUSTAP 1600 2544 1696 2544
        BEGIN BRANCH ADDR(2)
            WIRE 1696 2352 1712 2352
            WIRE 1712 2352 1760 2352
            BEGIN DISPLAY 1712 2352 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH ADDR(3)
            WIRE 1696 2416 1712 2416
            WIRE 1712 2416 1760 2416
            BEGIN DISPLAY 1712 2416 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH ADDR(4)
            WIRE 1696 2480 1712 2480
            WIRE 1712 2480 1760 2480
            BEGIN DISPLAY 1712 2480 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH ADDR(5)
            WIRE 1696 2544 1712 2544
            WIRE 1712 2544 1760 2544
            BEGIN DISPLAY 1712 2544 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        INSTANCE XLXI_221 1760 2608 R0
        BEGIN BRANCH XLXN_253
            WIRE 1824 2736 2096 2736
            WIRE 1824 2736 1824 2816
            WIRE 1824 2816 1856 2816
            WIRE 1824 2816 1824 3104
            WIRE 1824 3104 1856 3104
            WIRE 2016 2448 2096 2448
            WIRE 2096 2448 2096 2736
        END BRANCH
        INSTANCE XLXI_224 2000 1552 R0
        INSTANCE XLXI_225 2000 2128 R0
        BUSTAP 1760 1680 1856 1680
        BUSTAP 1760 1168 1856 1168
        BUSTAP 1760 1104 1856 1104
        BUSTAP 1760 1040 1856 1040
        BUSTAP 1760 976 1856 976
        BEGIN BRANCH DATA(0)
            WIRE 1856 976 1872 976
            WIRE 1872 976 2000 976
            BEGIN DISPLAY 1872 976 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH DATA(1)
            WIRE 1856 1040 1872 1040
            WIRE 1872 1040 2000 1040
            BEGIN DISPLAY 1872 1040 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH DATA(2)
            WIRE 1856 1104 1872 1104
            WIRE 1872 1104 2000 1104
            BEGIN DISPLAY 1872 1104 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH DATA(3)
            WIRE 1856 1168 1872 1168
            WIRE 1872 1168 2000 1168
            BEGIN DISPLAY 1872 1168 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH DATA(4)
            WIRE 1856 1680 1872 1680
            WIRE 1872 1680 2000 1680
            BEGIN DISPLAY 1872 1680 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH XLXN_266
            WIRE 1984 1552 1984 1936
            WIRE 1984 1936 2000 1936
            WIRE 1984 1552 2416 1552
            WIRE 2384 1360 2416 1360
            WIRE 2416 1360 2416 1552
        END BRANCH
        BEGIN BRANCH XLXN_272
            WIRE 1952 1360 2000 1360
            WIRE 1952 1360 1952 2160
            WIRE 1952 2160 2608 2160
            WIRE 2608 2160 2608 2400
            WIRE 2608 2400 2800 2400
            WIRE 2608 2016 2608 2160
        END BRANCH
        INSTANCE XLXI_227 1200 2240 R0
        BEGIN BRANCH XLXN_274
            WIRE 1120 2112 1200 2112
        END BRANCH
        BEGIN BRANCH XLXN_275
            WIRE 1120 2048 1200 2048
        END BRANCH
        INSTANCE XLXI_229 2240 3104 R0
        INSTANCE XLXI_230 2240 2784 R0
        INSTANCE XLXI_228 2240 3424 R0
        BEGIN BRANCH XLXN_276
            WIRE 1456 2112 1520 2112
            WIRE 1520 2112 1520 2240
            WIRE 1520 2240 2128 2240
            WIRE 2128 2240 2128 2528
            WIRE 2128 2528 2240 2528
        END BRANCH
        BEGIN BRANCH XLXN_277
            WIRE 2112 2848 2240 2848
        END BRANCH
        BEGIN BRANCH XLXN_278
            WIRE 2112 3136 2224 3136
            WIRE 2224 3136 2224 3168
            WIRE 2224 3168 2240 3168
        END BRANCH
        BEGIN BRANCH ADDR(10:0)
            WIRE 320 1920 480 1920
            WIRE 480 1920 480 1984
            WIRE 480 1984 480 2048
            WIRE 480 2048 480 2256
            WIRE 480 2256 480 2320
            WIRE 480 2320 480 2336
            WIRE 480 2336 1600 2336
            WIRE 1600 2336 1600 2352
            WIRE 1600 2352 1600 2416
            WIRE 1600 2416 1600 2480
            WIRE 1600 2480 1600 2544
        END BRANCH
        INSTANCE XLXI_232 2880 3008 R0
        BEGIN BRANCH CTL_FULL
            WIRE 2384 480 2560 480
            WIRE 2560 480 2784 480
            WIRE 2784 480 2784 1584
            WIRE 2784 1584 2784 2976
            WIRE 2784 2976 2880 2976
            WIRE 2784 1584 2912 1584
            WIRE 2560 480 2560 592
        END BRANCH
        INSTANCE XLXI_233 2944 544 M180
        BEGIN BRANCH CTL_TX
            WIRE 976 3664 976 3744
            WIRE 976 3744 1040 3744
            WIRE 976 3664 1504 3664
            WIRE 1504 2256 1504 3664
            WIRE 1504 2256 2832 2256
            WIRE 2384 416 2624 416
            WIRE 2624 416 2832 416
            WIRE 2832 416 2832 608
            WIRE 2832 608 2832 1520
            WIRE 2832 1520 2912 1520
            WIRE 2832 1520 2832 2256
            WIRE 2832 608 2944 608
            WIRE 2624 416 2624 592
        END BRANCH
        BEGIN BRANCH XLXN_289
            WIRE 2864 672 2944 672
            WIRE 2864 672 2864 752
            WIRE 2864 752 3264 752
            WIRE 3264 752 3264 2880
            WIRE 3264 2880 3472 2880
            WIRE 3200 2880 3264 2880
        END BRANCH
        BEGIN BRANCH CTL_BLIND
            WIRE 2384 544 2496 544
            WIRE 2496 544 3248 544
            WIRE 3248 544 3248 2816
            WIRE 3248 2816 3472 2816
            WIRE 2496 544 2496 592
        END BRANCH
        INSTANCE XLXI_236 4160 1888 R0
        INSTANCE XLXI_237 4160 2208 R0
        BEGIN BRANCH XLXN_292
            WIRE 3056 2432 4128 2432
            WIRE 4128 1856 4160 1856
            WIRE 4128 1856 4128 2176
            WIRE 4128 2176 4128 2432
            WIRE 4128 2176 4160 2176
        END BRANCH
        BEGIN BRANCH XLXN_294
            WIRE 3728 2784 4080 2784
            WIRE 4080 1792 4160 1792
            WIRE 4080 1792 4080 2112
            WIRE 4080 2112 4160 2112
            WIRE 4080 2112 4080 2784
        END BRANCH
        BEGIN BRANCH XLXN_297
            WIRE 4480 1760 4640 1760
        END BRANCH
        BEGIN BRANCH XLXN_298
            WIRE 4480 2080 4640 2080
        END BRANCH
        BEGIN BRANCH ML
            WIRE 4896 2496 5120 2496
        END BRANCH
        IOMARKER 5120 2496 ML R0 28
        INSTANCE XLXI_242 2800 2336 M180
        INSTANCE XLXI_245 2640 1792 M90
        BEGIN BRANCH XLXN_305
            WIRE 2624 2528 2704 2528
            WIRE 2704 2528 4640 2528
            WIRE 2704 2464 2800 2464
            WIRE 2704 2464 2704 2528
        END BRANCH
        BEGIN BRANCH XLXN_257
            WIRE 1904 2096 1968 2096
            WIRE 1968 2096 2000 2096
            WIRE 1968 608 2000 608
            WIRE 1968 608 1968 832
            WIRE 1968 832 2000 832
            WIRE 1968 832 1968 1520
            WIRE 1968 1520 2000 1520
            WIRE 1968 1520 1968 1744
            WIRE 1968 1744 2000 1744
            WIRE 1968 1744 1968 2096
        END BRANCH
        INSTANCE XLXI_246 1776 2160 M270
        INSTANCE XLXI_247 3760 1296 M180
        BUSTAP 3360 1552 3456 1552
        BUSTAP 3360 1488 3456 1488
        BUSTAP 3360 1424 3456 1424
        BUSTAP 3360 1360 3456 1360
        BEGIN BRANCH ADDR(3)
            WIRE 3456 1488 3472 1488
            WIRE 3472 1488 3760 1488
            BEGIN DISPLAY 3472 1488 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH ADDR(4)
            WIRE 3456 1424 3472 1424
            WIRE 3472 1424 3760 1424
            BEGIN DISPLAY 3472 1424 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH ADDR(5)
            WIRE 3456 1360 3472 1360
            WIRE 3472 1360 3760 1360
            BEGIN DISPLAY 3472 1360 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        INSTANCE XLXI_250 2912 1456 M180
        BEGIN BRANCH XLXN_317
            WIRE 3168 1552 3184 1552
            WIRE 3184 1552 3184 1760
            WIRE 3184 1760 4032 1760
            WIRE 4032 1456 4032 1760
            WIRE 4032 1456 4352 1456
        END BRANCH
        INSTANCE XLXI_251 3424 3552 R0
        INSTANCE XLXI_252 3216 3120 R0
        BEGIN BRANCH XLXN_319
            WIRE 3280 3120 3280 3232
            WIRE 3280 3232 3424 3232
            WIRE 3280 3232 3280 3296
            WIRE 3280 3296 3424 3296
            WIRE 3280 3296 3280 3360
            WIRE 3280 3360 3424 3360
            WIRE 3280 3360 3280 3424
            WIRE 3280 3424 3424 3424
        END BRANCH
        INSTANCE XLXI_253 3472 2944 R0
        BEGIN BRANCH XLXN_324
            WIRE 3808 3104 3968 3104
            WIRE 3968 3040 3968 3104
            WIRE 3968 3040 4000 3040
        END BRANCH
        INSTANCE XLXI_255 3856 3056 R0
        BEGIN BRANCH XLXN_326
            WIRE 3920 3056 3920 3232
            WIRE 3920 3232 4000 3232
            WIRE 3920 3232 3920 3296
            WIRE 3920 3296 4000 3296
            WIRE 3920 3296 3920 3360
            WIRE 3920 3360 4000 3360
            WIRE 3920 3360 3920 3424
            WIRE 3920 3424 4000 3424
        END BRANCH
        INSTANCE XLXI_254 4000 3552 R0
        INSTANCE XLXI_256 4640 3552 R0
        BEGIN BRANCH XLXN_330
            WIRE 4384 3104 4400 3104
            WIRE 4400 2880 4976 2880
            WIRE 4400 2880 4400 3040
            WIRE 4400 3040 4640 3040
            WIRE 4400 3040 4400 3104
            WIRE 4896 2752 4976 2752
            WIRE 4976 2752 4976 2880
        END BRANCH
        BEGIN BRANCH XLXN_334
            WIRE 3472 2624 3472 2688
            WIRE 3472 2624 4448 2624
            WIRE 4448 2624 4448 2688
            WIRE 4448 2688 4640 2688
        END BRANCH
        BEGIN BRANCH XLXN_335
            WIRE 4896 2688 5040 2688
            WIRE 5040 2688 5040 3104
            WIRE 5024 3104 5040 3104
        END BRANCH
        INSTANCE XLXI_258 4448 3360 R90
        BEGIN BRANCH XLXN_339
            WIRE 4576 3424 4608 3424
            WIRE 4608 3424 4640 3424
            WIRE 4608 3232 4640 3232
            WIRE 4608 3232 4608 3296
            WIRE 4608 3296 4640 3296
            WIRE 4608 3296 4608 3360
            WIRE 4608 3360 4640 3360
            WIRE 4608 3360 4608 3424
        END BRANCH
        INSTANCE XLXI_259 800 2816 R180
        INSTANCE XLXI_260 736 2944 R0
        INSTANCE XLXI_261 800 2944 R0
        IOMARKER 5120 2816 TXBITS R0 28
        BEGIN BRANCH ADDR(5:0)
            WIRE 3200 1360 3360 1360
            WIRE 3360 1360 3360 1424
            WIRE 3360 1424 3360 1488
            WIRE 3360 1488 3360 1552
            WIRE 3360 1552 3360 1616
            BEGIN DISPLAY 3200 1360 ATTR Name
                ALIGNMENT SOFT-RIGHT
            END DISPLAY
        END BRANCH
        INSTANCE XLXI_266 3648 1936 R0
        BUSTAP 480 3680 576 3680
        BUSTAP 480 3744 576 3744
        BUSTAP 480 3808 576 3808
        BUSTAP 480 3872 576 3872
        BUSTAP 480 3936 576 3936
        BEGIN BRANCH ADDR(7:0)
            WIRE 480 2400 480 2480
            WIRE 480 2480 544 2480
            WIRE 544 2480 1040 2480
            WIRE 480 2480 480 3040
            WIRE 480 3040 1040 3040
            WIRE 480 3040 480 3680
            WIRE 480 3680 480 3744
            WIRE 480 3744 480 3808
            WIRE 480 3808 480 3872
            WIRE 480 3872 480 3936
            BEGIN DISPLAY 544 2480 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH ADDR(5)
            WIRE 576 3680 592 3680
            WIRE 592 3680 672 3680
            BEGIN DISPLAY 592 3680 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH ADDR(4)
            WIRE 576 3744 592 3744
            WIRE 592 3744 672 3744
            BEGIN DISPLAY 592 3744 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH ADDR(3)
            WIRE 576 3808 592 3808
            WIRE 592 3808 672 3808
            BEGIN DISPLAY 592 3808 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH ADDR(1)
            WIRE 576 3872 592 3872
            WIRE 592 3872 672 3872
            BEGIN DISPLAY 592 3872 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH ADDR(2)
            WIRE 576 3936 592 3936
            WIRE 592 3936 672 3936
            BEGIN DISPLAY 592 3936 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        INSTANCE XLXI_269 1040 3872 R0
        BEGIN BRANCH XLXN_350
            WIRE 928 3808 992 3808
            WIRE 992 3808 1040 3808
            WIRE 992 3808 992 3888
            WIRE 992 3888 1472 3888
            WIRE 1472 2272 1472 3888
            WIRE 1472 2272 4048 2272
            WIRE 4048 1584 4048 2272
            WIRE 4048 1584 4064 1584
        END BRANCH
        INSTANCE XLXI_223 1856 3232 R0
        INSTANCE XLXI_222 1856 2944 R0
        INSTANCE XLXI_270 1552 2976 R0
        INSTANCE XLXI_271 1552 3264 R0
        BEGIN BRANCH XLXN_354
            WIRE 1808 2880 1856 2880
        END BRANCH
        BEGIN BRANCH XLXN_355
            WIRE 1808 3168 1856 3168
        END BRANCH
        BEGIN BRANCH XLXN_356
            WIRE 1424 2608 1488 2608
            WIRE 1488 2608 1488 2848
            WIRE 1488 2848 1552 2848
        END BRANCH
        BEGIN BRANCH XLXN_357
            WIRE 1424 3168 1488 3168
            WIRE 1488 3136 1488 3168
            WIRE 1488 3136 1552 3136
        END BRANCH
        BEGIN BRANCH XLXN_358
            WIRE 1296 3776 1536 3776
            WIRE 1536 2912 1552 2912
            WIRE 1536 2912 1536 3200
            WIRE 1536 3200 1552 3200
            WIRE 1536 3200 1536 3776
        END BRANCH
        INSTANCE XLXI_272 672 4000 R0
        INSTANCE XLXI_273 4064 1648 R0
        BEGIN BRANCH XLXN_359
            WIRE 4016 1520 4064 1520
        END BRANCH
        BEGIN BRANCH XLXN_360
            WIRE 4320 1552 4336 1552
            WIRE 4336 1520 4336 1552
            WIRE 4336 1520 4352 1520
        END BRANCH
        BEGIN BRANCH ADDR(2)
            WIRE 3456 1552 3472 1552
            WIRE 3472 1552 3520 1552
            BEGIN DISPLAY 3472 1552 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        INSTANCE XLXI_274 3520 1584 R0
        BEGIN BRANCH XLXN_361
            WIRE 3744 1552 3760 1552
        END BRANCH
        BUSTAP 3360 1616 3456 1616
        BEGIN BRANCH XLXN_344
            WIRE 3712 1680 3760 1680
            WIRE 3712 1680 3712 1808
        END BRANCH
        BEGIN BRANCH ADDR(1)
            WIRE 3456 1616 3472 1616
            WIRE 3472 1616 3760 1616
            BEGIN DISPLAY 3472 1616 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        INSTANCE XLXI_278 864 2944 R0
        INSTANCE XLXI_280 2512 1488 R90
        BEGIN BRANCH XLXN_364
            WIRE 2608 1744 2608 1792
        END BRANCH
        BEGIN BRANCH XLXN_365
            WIRE 2384 1680 2448 1680
            WIRE 2448 1424 2448 1680
            WIRE 2448 1424 2576 1424
            WIRE 2576 1424 2576 1488
        END BRANCH
        BEGIN BRANCH XLXN_366
            WIRE 2384 1168 2640 1168
            WIRE 2640 1168 2640 1488
        END BRANCH
        INSTANCE XLXI_281 1248 1952 R0
        BEGIN BRANCH XLXN_368
            WIRE 1200 2176 1200 2192
            WIRE 1200 2192 1584 2192
            WIRE 1504 1856 1584 1856
            WIRE 1584 1856 1584 2192
        END BRANCH
        INSTANCE XLXI_195 4704 1552 R0
        IOMARKER 5120 1456 PLLPD R0 28
        IOMARKER 5120 1248 TXEN R0 28
        BEGIN BRANCH XLXN_132(7:0)
            WIRE 5392 400 5600 400
        END BRANCH
        BEGIN BRANCH TXL(7:0)
            WIRE 5552 528 5600 528
            WIRE 5552 528 5552 720
            WIRE 5552 720 5552 784
            WIRE 5552 784 5552 848
            WIRE 5552 848 5552 912
            WIRE 5552 912 5552 976
            WIRE 5552 976 5552 1040
            WIRE 5552 1040 5552 1104
            WIRE 5552 1104 5552 1168
        END BRANCH
        BEGIN BRANCH TXL(7)
            WIRE 5344 720 5456 720
        END BRANCH
        BEGIN BRANCH TXL(6)
            WIRE 5344 784 5456 784
        END BRANCH
        BEGIN BRANCH TXL(5)
            WIRE 5344 848 5456 848
        END BRANCH
        BEGIN BRANCH TXL(4)
            WIRE 5344 912 5456 912
        END BRANCH
        BEGIN BRANCH TXL(3)
            WIRE 5344 976 5456 976
        END BRANCH
        BEGIN BRANCH TXL(2)
            WIRE 5344 1040 5456 1040
        END BRANCH
        BEGIN BRANCH TXL(1)
            WIRE 5344 1104 5456 1104
        END BRANCH
        BEGIN BRANCH TXL(0)
            WIRE 5344 1168 5456 1168
        END BRANCH
        BEGIN BRANCH XLXN_142
            WIRE 5536 272 5600 272
        END BRANCH
        BEGIN BRANCH TXD(7)
            WIRE 6336 480 6400 480
        END BRANCH
        BEGIN BRANCH TXD(6)
            WIRE 6336 544 6400 544
        END BRANCH
        BEGIN BRANCH TXD(5)
            WIRE 6336 608 6400 608
        END BRANCH
        BEGIN BRANCH TXD(4)
            WIRE 6336 672 6400 672
        END BRANCH
        BEGIN BRANCH TXD(3)
            WIRE 6336 736 6400 736
        END BRANCH
        BEGIN BRANCH TXD(7:0)
            WIRE 6048 464 6240 464
            WIRE 6240 464 6240 480
            WIRE 6240 480 6240 544
            WIRE 6240 544 6240 608
            WIRE 6240 608 6240 672
            WIRE 6240 672 6240 736
        END BRANCH
        BEGIN BRANCH TXD4
            WIRE 6624 480 6720 480
        END BRANCH
        BEGIN BRANCH TXD3
            WIRE 6624 544 6720 544
        END BRANCH
        BEGIN BRANCH TXD2
            WIRE 6624 608 6720 608
        END BRANCH
        BEGIN BRANCH TXD1
            WIRE 6624 672 6720 672
        END BRANCH
        BEGIN BRANCH TXD0
            WIRE 6624 736 6720 736
        END BRANCH
        INSTANCE XLXI_112 5600 720 R0
        BUSTAP 5552 720 5456 720
        BUSTAP 5552 784 5456 784
        BUSTAP 5552 848 5456 848
        BUSTAP 5552 912 5456 912
        BUSTAP 5552 976 5456 976
        BUSTAP 5552 1040 5456 1040
        BUSTAP 5552 1104 5456 1104
        BUSTAP 5552 1168 5456 1168
        INSTANCE XLXI_117 5216 912 R90
        INSTANCE XLXI_118 5216 976 R90
        INSTANCE XLXI_119 5216 1040 R90
        INSTANCE XLXI_120 5216 1104 R90
        INSTANCE XLXI_121 5408 208 R90
        BUSTAP 6240 480 6336 480
        BUSTAP 6240 544 6336 544
        BUSTAP 6240 608 6336 608
        BUSTAP 6240 672 6336 672
        BUSTAP 6240 736 6336 736
        INSTANCE XLXI_122 6400 512 R0
        INSTANCE XLXI_123 6400 576 R0
        INSTANCE XLXI_124 6400 640 R0
        INSTANCE XLXI_125 6400 704 R0
        INSTANCE XLXI_126 6400 768 R0
        INSTANCE XLXI_153 5344 784 R270
        IOMARKER 6720 480 TXD4 R0 28
        IOMARKER 6720 544 TXD3 R0 28
        IOMARKER 6720 608 TXD2 R0 28
        IOMARKER 6720 672 TXD1 R0 28
        IOMARKER 6720 736 TXD0 R0 28
        BEGIN INSTANCE XLXI_111 5008 560 R0
        END INSTANCE
        INSTANCE XLXI_189 4864 1280 R0
        INSTANCE XLXI_249 4352 1392 M180
        INSTANCE XLXI_235 2688 592 M90
        BEGIN BRANCH XLXN_316
            WIRE 2560 848 2560 1280
            WIRE 2560 1280 4624 1280
            WIRE 4624 1280 4624 1696
            WIRE 4624 1696 4624 2016
            WIRE 4624 2016 4640 2016
            WIRE 4624 2016 4624 2464
            WIRE 4624 2464 4640 2464
            WIRE 4624 1696 4640 1696
        END BRANCH
        BEGIN BRANCH XLXN_409
            WIRE 4608 1488 4704 1488
        END BRANCH
        INSTANCE XLXI_239 4640 1824 R0
        INSTANCE XLXI_240 4640 2144 R0
        INSTANCE XLXI_241 4640 2592 R0
        INSTANCE XLXI_306 928 2944 R0
        INSTANCE XLXI_307 2880 2784 R0
        BEGIN BRANCH XLXN_417
            WIRE 2624 3168 2752 3168
            WIRE 2752 2656 2880 2656
            WIRE 2752 2656 2752 2912
            WIRE 2752 2912 2752 3168
            WIRE 2752 2912 2880 2912
        END BRANCH
        BEGIN BRANCH XLXN_418
            WIRE 2624 2848 2720 2848
            WIRE 2720 2848 2880 2848
            WIRE 2720 2720 2880 2720
            WIRE 2720 2720 2720 2848
        END BRANCH
        INSTANCE XLXI_311 4896 2560 R180
        BEGIN BRANCH BCLKI
            WIRE 1040 1360 1104 1360
            WIRE 1104 1360 1712 1360
            WIRE 1712 1360 1712 1424
            WIRE 1712 1424 2000 1424
            WIRE 1712 1424 1712 2000
            WIRE 1712 2000 2000 2000
            WIRE 1712 2000 1712 2208
            WIRE 1712 2208 2160 2208
            WIRE 2160 2208 2160 2656
            WIRE 2160 2656 2240 2656
            WIRE 2160 2656 2160 2976
            WIRE 2160 2976 2240 2976
            WIRE 2160 2976 2160 3296
            WIRE 2160 3296 2240 3296
            WIRE 2160 3296 2160 3424
            WIRE 2160 3424 2832 3424
            WIRE 2160 2208 2880 2208
            WIRE 1104 864 1120 864
            WIRE 1104 864 1104 1360
            WIRE 1712 736 2000 736
            WIRE 1712 736 1712 1360
            WIRE 2832 3168 3248 3168
            WIRE 3248 3168 3424 3168
            WIRE 3248 3168 3248 3504
            WIRE 3248 3504 3872 3504
            WIRE 3872 3504 4448 3504
            WIRE 2832 3168 2832 3424
            WIRE 2880 896 2880 1728
            WIRE 2880 1728 2880 2208
            WIRE 2880 1728 4160 1728
            WIRE 2880 896 3424 896
            WIRE 3424 592 3424 896
            WIRE 3424 592 4256 592
            WIRE 3872 3168 4000 3168
            WIRE 3872 3168 3872 3504
            WIRE 4448 3168 4640 3168
            WIRE 4448 3168 4448 3504
        END BRANCH
        BEGIN BRANCH BFLD
            WIRE 3136 2688 3216 2688
            WIRE 3216 1296 3216 2688
            WIRE 3216 1296 3360 1296
            WIRE 3360 528 3360 1296
            WIRE 3360 528 4256 528
        END BRANCH
        BEGIN BRANCH TXBITS
            WIRE 1504 736 1600 736
            WIRE 1600 240 1600 736
            WIRE 1600 240 3232 240
            WIRE 3232 240 3232 400
            WIRE 3232 400 3232 2048
            WIRE 3232 2048 3920 2048
            WIRE 3920 2048 4160 2048
            WIRE 3920 2048 3920 2816
            WIRE 3920 2816 5120 2816
            WIRE 3232 400 4256 400
        END BRANCH
        BEGIN INSTANCE XLXI_313 4256 624 R0
        END INSTANCE
        BEGIN BRANCH XLXN_430
            WIRE 3200 640 3312 640
            WIRE 3312 464 4256 464
            WIRE 3312 464 3312 640
        END BRANCH
        BEGIN BRANCH XLXN_433
            WIRE 4640 592 4816 592
            WIRE 4816 400 4816 592
            WIRE 4816 400 5008 400
        END BRANCH
        BEGIN BRANCH XLXN_434
            WIRE 4608 1248 4608 1424
            WIRE 4608 1424 4704 1424
            WIRE 4608 1248 4832 1248
            WIRE 4832 1248 4864 1248
            WIRE 4832 1248 4832 1360
            WIRE 4832 1360 5008 1360
            WIRE 5008 1360 5008 1792
            WIRE 5008 1792 5072 1792
            WIRE 5008 1792 5008 2112
            WIRE 5008 2112 5008 2624
            WIRE 5008 2112 5072 2112
            WIRE 4640 400 4736 400
            WIRE 4736 400 4736 464
            WIRE 4736 464 4832 464
            WIRE 4832 464 5008 464
            WIRE 4832 464 4832 1248
            WIRE 4896 2624 5008 2624
        END BRANCH
        BEGIN BRANCH TEST
            WIRE 4640 656 5440 656
            WIRE 5440 656 5440 3200
            WIRE 5440 3200 5600 3200
        END BRANCH
        IOMARKER 5600 3200 TEST R0 28
        INSTANCE XLXI_314 5072 1856 R0
        INSTANCE XLXI_315 5072 2176 R0
        BEGIN BRANCH XLXN_439
            WIRE 4896 1728 5072 1728
        END BRANCH
        BEGIN BRANCH XLXN_440
            WIRE 4896 2048 5072 2048
        END BRANCH
        BEGIN BRANCH MCLK
            WIRE 5328 1760 5600 1760
        END BRANCH
        IOMARKER 5600 1760 MCLK R0 28
        BEGIN BRANCH MDATA
            WIRE 5328 2080 5600 2080
        END BRANCH
        IOMARKER 5600 2080 MDATA R0 28
        INSTANCE XLXI_316 5216 720 R90
        INSTANCE XLXI_317 5344 912 R270
        INSTANCE XLXI_319 5216 848 R90
    END SHEET
END SCHEMATIC
