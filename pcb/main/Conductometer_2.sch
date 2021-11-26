EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 6
Title ""
Date "2021-11-26"
Rev "0.1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L bioreactor:TLV6004PW U2
U 1 1 61A49225
P 6400 5525
F 0 "U2" H 6400 5158 50  0000 C CNN
F 1 "TLV6004PW" H 6400 5249 50  0000 C CNN
F 2 "Package_SO:TSSOP-14_4.4x5mm_P0.65mm" H 6450 5125 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/tlv6004.pdf?ts=1591554967798&ref_url=https://www.ti.com/product/TLV6004" H 6450 5725 50  0001 C CNN
	1    6400 5525
	1    0    0    1   
$EndComp
$Comp
L bioreactor:TLV6004PW U2
U 2 1 61A49A69
P 2050 2875
F 0 "U2" H 2050 3242 50  0000 C CNN
F 1 "TLV6004PW" H 2050 3151 50  0000 C CNN
F 2 "Package_SO:TSSOP-14_4.4x5mm_P0.65mm" H 2100 2475 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/tlv6004.pdf?ts=1591554967798&ref_url=https://www.ti.com/product/TLV6004" H 2100 3075 50  0001 C CNN
	2    2050 2875
	1    0    0    -1  
$EndComp
$Comp
L bioreactor:TLV6004PW U2
U 3 1 61A49F8F
P 3475 2775
F 0 "U2" H 3475 3142 50  0000 C CNN
F 1 "TLV6004PW" H 3475 3051 50  0000 C CNN
F 2 "Package_SO:TSSOP-14_4.4x5mm_P0.65mm" H 3525 2375 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/tlv6004.pdf?ts=1591554967798&ref_url=https://www.ti.com/product/TLV6004" H 3525 2975 50  0001 C CNN
	3    3475 2775
	1    0    0    -1  
$EndComp
$Comp
L bioreactor:TLV6004PW U1
U 4 1 61A4A5C8
P 4750 2675
F 0 "U1" H 4750 2308 50  0000 C CNN
F 1 "TLV6004PW" H 4750 2399 50  0000 C CNN
F 2 "Package_SO:TSSOP-14_4.4x5mm_P0.65mm" H 4800 2275 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/tlv6004.pdf?ts=1591554967798&ref_url=https://www.ti.com/product/TLV6004" H 4800 2875 50  0001 C CNN
	4    4750 2675
	1    0    0    1   
$EndComp
$Comp
L bioreactor:TLV6004PW U2
U 5 1 61A4AB2E
P 3400 875
F 0 "U2" H 3358 921 50  0000 L CNN
F 1 "TLV6004PW" H 3358 830 50  0000 L CNN
F 2 "Package_SO:TSSOP-14_4.4x5mm_P0.65mm" H 3450 475 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/tlv6004.pdf?ts=1591554967798&ref_url=https://www.ti.com/product/TLV6004" H 3450 1075 50  0001 C CNN
	5    3400 875 
	0    -1   -1   0   
$EndComp
NoConn ~ 5425 4825
NoConn ~ 5425 4925
NoConn ~ 5425 5025
NoConn ~ 5425 5125
NoConn ~ 5425 5225
NoConn ~ 5425 5325
$Comp
L CD4060BM:CD4060BM U8
U 1 1 61A4BEA9
P 5425 4825
F 0 "U8" H 6625 5212 60  0000 C CNN
F 1 "CD4060BM" H 6625 5106 60  0000 C CNN
F 2 "CD4060BM:CD4060BM" H 6625 5065 60  0001 C CNN
F 3 "" H 5425 4825 60  0000 C CNN
	1    5425 4825
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2425 4425 2525 4425
Connection ~ 2525 4425
$Comp
L power:+3V3 #PWR0101
U 1 1 61A57A5A
P 2975 4425
F 0 "#PWR0101" H 2975 4275 50  0001 C CNN
F 1 "+3V3" V 2990 4553 50  0000 L CNN
F 2 "" H 2975 4425 50  0001 C CNN
F 3 "" H 2975 4425 50  0001 C CNN
	1    2975 4425
	0    1    1    0   
$EndComp
Wire Wire Line
	2925 4425 2975 4425
Connection ~ 2925 4425
Wire Wire Line
	2925 4825 2925 4425
Wire Wire Line
	2875 4825 2925 4825
Wire Wire Line
	2875 4425 2925 4425
$Comp
L Bertha_main-eagle-import:GND #0105
U 1 1 61A56CCE
P 2325 4425
F 0 "#0105" H 2375 4475 50  0001 C CNN
F 1 "GND" V 2183 4462 42  0000 C CNN
F 2 "" H 2325 4425 50  0001 C CNN
F 3 "" H 2325 4425 50  0001 C CNN
	1    2325 4425
	0    1    1    0   
$EndComp
Wire Wire Line
	2525 4825 2575 4825
Wire Wire Line
	2525 4425 2525 4825
Wire Wire Line
	2575 4425 2525 4425
$Comp
L Device:CP1 C10
U 1 1 61A53EF3
P 2725 4425
F 0 "C10" V 2473 4425 50  0000 C CNN
F 1 "10u" V 2564 4425 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 2725 4425 50  0001 C CNN
F 3 "~" H 2725 4425 50  0001 C CNN
	1    2725 4425
	0    1    1    0   
$EndComp
$Comp
L Device:C C12
U 1 1 61A53408
P 2725 4825
F 0 "C12" V 2473 4825 50  0000 C CNN
F 1 "100n" V 2564 4825 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 2763 4675 50  0001 C CNN
F 3 "~" H 2725 4825 50  0001 C CNN
	1    2725 4825
	0    1    1    0   
$EndComp
NoConn ~ 3025 4925
NoConn ~ 3025 5025
NoConn ~ 3025 5125
Connection ~ 2125 5625
$Comp
L power:-3V3 #PWR0102
U 1 1 61A52530
P 1650 5625
F 0 "#PWR0102" H 1650 5725 50  0001 C CNN
F 1 "-3V3" V 1665 5753 50  0000 L CNN
F 2 "" H 1650 5625 50  0001 C CNN
F 3 "" H 1650 5625 50  0001 C CNN
	1    1650 5625
	0    -1   -1   0   
$EndComp
Connection ~ 2125 6050
Wire Wire Line
	2125 6000 2125 6050
Wire Wire Line
	2125 6050 2125 6100
Wire Wire Line
	1750 6050 2125 6050
Wire Wire Line
	1750 6000 1750 6050
$Comp
L Bertha_main-eagle-import:GND #0106
U 1 1 61A50F97
P 2125 6200
F 0 "#0106" H 2175 6250 50  0001 C CNN
F 1 "GND" H 2228 6238 42  0000 L CNN
F 2 "" H 2125 6200 50  0001 C CNN
F 3 "" H 2125 6200 50  0001 C CNN
	1    2125 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 5625 2125 5625
Wire Wire Line
	1750 5700 1750 5625
Wire Wire Line
	2125 5625 2125 5700
$Comp
L Device:CP1 C4
U 1 1 61A4FF46
P 2125 5850
F 0 "C4" H 2010 5804 50  0000 R CNN
F 1 "10u" H 2010 5895 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 2125 5850 50  0001 C CNN
F 3 "~" H 2125 5850 50  0001 C CNN
	1    2125 5850
	-1   0    0    1   
$EndComp
$Comp
L Device:C C2
U 1 1 61A4F974
P 1750 5850
F 0 "C2" H 1865 5896 50  0000 L CNN
F 1 "100n" H 1865 5805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1788 5700 50  0001 C CNN
F 3 "~" H 1750 5850 50  0001 C CNN
	1    1750 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3025 4825 2925 4825
Connection ~ 2925 4825
Wire Wire Line
	2625 5325 3025 5325
Wire Wire Line
	2325 5325 2225 5325
$Comp
L Device:C C5
U 1 1 61A4EA27
P 2475 5525
F 0 "C5" V 2223 5525 50  0000 C CNN
F 1 "1.5n" V 2314 5525 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 2513 5375 50  0001 C CNN
F 3 "~" H 2475 5525 50  0001 C CNN
	1    2475 5525
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 61A4E635
P 2775 5425
F 0 "R6" V 2568 5425 50  0000 C CNN
F 1 "10k" V 2659 5425 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 2705 5425 50  0001 C CNN
F 3 "~" H 2775 5425 50  0001 C CNN
	1    2775 5425
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 61A4D786
P 2475 5325
F 0 "R2" V 2268 5325 50  0000 C CNN
F 1 "100k" V 2359 5325 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 2405 5325 50  0001 C CNN
F 3 "~" H 2475 5325 50  0001 C CNN
	1    2475 5325
	0    1    1    0   
$EndComp
Wire Wire Line
	2225 5325 2225 5425
Wire Wire Line
	2925 5425 3025 5425
Wire Wire Line
	3025 5525 2625 5525
Wire Wire Line
	2625 5425 2225 5425
Connection ~ 2225 5425
Wire Wire Line
	2225 5425 2225 5525
Wire Wire Line
	2225 5525 2325 5525
Wire Wire Line
	1650 5625 1750 5625
Connection ~ 1750 5625
Wire Wire Line
	3025 5225 2125 5225
Wire Wire Line
	2125 5225 2125 5625
$Comp
L power:-3V3 #PWR0103
U 1 1 61A9179D
P 5525 5525
F 0 "#PWR0103" H 5525 5625 50  0001 C CNN
F 1 "-3V3" V 5540 5653 50  0000 L CNN
F 2 "" H 5525 5525 50  0001 C CNN
F 3 "" H 5525 5525 50  0001 C CNN
	1    5525 5525
	0    1    1    0   
$EndComp
Wire Wire Line
	5425 5525 5525 5525
$Comp
L Device:R R17
U 1 1 61A92B15
P 5775 5425
F 0 "R17" V 5568 5425 50  0000 C CNN
F 1 "51k" V 5659 5425 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 5705 5425 50  0001 C CNN
F 3 "~" H 5775 5425 50  0001 C CNN
	1    5775 5425
	0    1    1    0   
$EndComp
Wire Wire Line
	5425 5425 5625 5425
$Comp
L Bertha_main-eagle-import:GND #0107
U 1 1 61A973C8
P 6025 5850
F 0 "#0107" H 6075 5900 50  0001 C CNN
F 1 "GND" H 6128 5888 42  0000 L CNN
F 2 "" H 6025 5850 50  0001 C CNN
F 3 "" H 6025 5850 50  0001 C CNN
	1    6025 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6025 5750 6025 5625
Wire Wire Line
	6025 5625 6100 5625
$Comp
L Device:R R18
U 1 1 61A98488
P 6250 5000
F 0 "R18" V 6457 5000 50  0000 C CNN
F 1 "2k" V 6366 5000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 6180 5000 50  0001 C CNN
F 3 "~" H 6250 5000 50  0001 C CNN
	1    6250 5000
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP1 C30
U 1 1 61A98CCB
P 3000 1225
F 0 "C30" H 3115 1271 50  0000 L CNN
F 1 "10u" H 3115 1180 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 3000 1225 50  0001 C CNN
F 3 "~" H 3000 1225 50  0001 C CNN
	1    3000 1225
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 61A99480
P 2650 1225
F 0 "C8" H 2765 1271 50  0000 L CNN
F 1 "100n" H 2765 1180 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 2688 1075 50  0001 C CNN
F 3 "~" H 2650 1225 50  0001 C CNN
	1    2650 1225
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 1075 2650 975 
Wire Wire Line
	2650 975  3000 975 
Wire Wire Line
	3000 1075 3000 975 
Connection ~ 3000 975 
Wire Wire Line
	3000 975  3100 975 
$Comp
L power:+3V3 #PWR0104
U 1 1 61AA17CA
P 2650 875
F 0 "#PWR0104" H 2650 725 50  0001 C CNN
F 1 "+3V3" H 2665 1048 50  0000 C CNN
F 2 "" H 2650 875 50  0001 C CNN
F 3 "" H 2650 875 50  0001 C CNN
	1    2650 875 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 875  2650 975 
Connection ~ 2650 975 
$Comp
L Bertha_main-eagle-import:GND #0108
U 1 1 61AA2750
P 2650 1575
F 0 "#0108" H 2700 1625 50  0001 C CNN
F 1 "GND" H 2753 1613 42  0000 L CNN
F 2 "" H 2650 1575 50  0001 C CNN
F 3 "" H 2650 1575 50  0001 C CNN
	1    2650 1575
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 1475 2650 1425
Wire Wire Line
	3000 1375 3000 1425
Wire Wire Line
	3000 1425 2650 1425
Connection ~ 2650 1425
Wire Wire Line
	2650 1425 2650 1375
$Comp
L Device:CP1 C32
U 1 1 61AA3BF6
P 3800 1225
F 0 "C32" H 3685 1179 50  0000 R CNN
F 1 "10u" H 3685 1270 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 3800 1225 50  0001 C CNN
F 3 "~" H 3800 1225 50  0001 C CNN
	1    3800 1225
	-1   0    0    1   
$EndComp
$Comp
L Device:C C34
U 1 1 61AA464F
P 4200 1225
F 0 "C34" H 4315 1271 50  0000 L CNN
F 1 "100n" H 4315 1180 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 4238 1075 50  0001 C CNN
F 3 "~" H 4200 1225 50  0001 C CNN
	1    4200 1225
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 1075 3800 975 
Wire Wire Line
	3800 975  3700 975 
Wire Wire Line
	3800 975  4200 975 
Wire Wire Line
	4200 975  4200 1075
Connection ~ 3800 975 
$Comp
L power:-3V3 #PWR0105
U 1 1 61AA5BC1
P 4200 875
F 0 "#PWR0105" H 4200 975 50  0001 C CNN
F 1 "-3V3" H 4215 1048 50  0000 C CNN
F 2 "" H 4200 875 50  0001 C CNN
F 3 "" H 4200 875 50  0001 C CNN
	1    4200 875 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 875  4200 975 
Connection ~ 4200 975 
$Comp
L Bertha_main-eagle-import:GND #U0102
U 1 1 61AA730F
P 4200 1575
F 0 "#U0102" H 4250 1625 50  0001 C CNN
F 1 "GND" H 4303 1613 42  0000 L CNN
F 2 "" H 4200 1575 50  0001 C CNN
F 3 "" H 4200 1575 50  0001 C CNN
	1    4200 1575
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 1475 4200 1425
Wire Wire Line
	3800 1375 3800 1425
Wire Wire Line
	3800 1425 4200 1425
Connection ~ 4200 1425
Wire Wire Line
	4200 1425 4200 1375
Wire Wire Line
	6100 5000 6025 5000
Wire Wire Line
	6025 5000 6025 5425
Wire Wire Line
	6025 5425 6100 5425
Wire Wire Line
	5925 5425 6025 5425
Connection ~ 6025 5425
Wire Wire Line
	6400 5000 6800 5000
Wire Wire Line
	6800 5000 6800 5525
Wire Wire Line
	6800 5525 6700 5525
Text GLabel 6900 5525 2    50   Input ~ 0
CT1
Wire Wire Line
	6900 5525 6800 5525
Connection ~ 6800 5525
$Comp
L LM2060M:LM2660M U10
U 1 1 61AB7C4A
P 7675 1275
F 0 "U10" H 8775 1662 60  0000 C CNN
F 1 "LM2660M" H 8775 1556 60  0000 C CNN
F 2 "LM2060M:LM2660M" H 8775 1515 60  0001 C CNN
F 3 "" H 7675 1275 60  0000 C CNN
	1    7675 1275
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0106
U 1 1 61AB96F3
P 9950 1200
F 0 "#PWR0106" H 9950 1050 50  0001 C CNN
F 1 "+3V3" H 9965 1373 50  0000 C CNN
F 2 "" H 9950 1200 50  0001 C CNN
F 3 "" H 9950 1200 50  0001 C CNN
	1    9950 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 1200 9950 1275
Wire Wire Line
	9950 1275 9875 1275
NoConn ~ 9875 1375
$Comp
L Bertha_main-eagle-import:GND #0109
U 1 1 61ABB7DA
P 10075 1475
F 0 "#0109" H 10125 1525 50  0001 C CNN
F 1 "GND" V 10075 1407 42  0000 R CNN
F 2 "" H 10075 1475 50  0001 C CNN
F 3 "" H 10075 1475 50  0001 C CNN
	1    10075 1475
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9875 1475 9975 1475
$Comp
L power:-3V3 #PWR0107
U 1 1 61ABCFCC
P 10075 1575
F 0 "#PWR0107" H 10075 1675 50  0001 C CNN
F 1 "-3V3" V 10090 1703 50  0000 L CNN
F 2 "" H 10075 1575 50  0001 C CNN
F 3 "" H 10075 1575 50  0001 C CNN
	1    10075 1575
	0    1    1    0   
$EndComp
Wire Wire Line
	9875 1575 9975 1575
$Comp
L Device:CP1 C37
U 1 1 61ABEE69
P 9975 1825
F 0 "C37" H 9860 1779 50  0000 R CNN
F 1 "100u" H 9860 1870 50  0000 R CNN
F 2 "Capacitor_SMD:CP_Elec_8x10" H 9975 1825 50  0001 C CNN
F 3 "~" H 9975 1825 50  0001 C CNN
	1    9975 1825
	-1   0    0    1   
$EndComp
Wire Wire Line
	9975 1675 9975 1575
Connection ~ 9975 1575
Wire Wire Line
	9975 1575 10075 1575
$Comp
L Device:CP1 C36
U 1 1 61AC1354
P 7425 1375
F 0 "C36" V 7173 1375 50  0000 C CNN
F 1 "100u" V 7264 1375 50  0000 C CNN
F 2 "Capacitor_SMD:CP_Elec_8x10" H 7425 1375 50  0001 C CNN
F 3 "~" H 7425 1375 50  0001 C CNN
	1    7425 1375
	0    1    1    0   
$EndComp
Wire Wire Line
	7675 1475 7575 1475
Wire Wire Line
	7575 1475 7575 1850
$Comp
L Bertha_main-eagle-import:GND #0110
U 1 1 61AC6F10
P 7575 1950
F 0 "#0110" H 7625 2000 50  0001 C CNN
F 1 "GND" H 7678 1988 42  0000 L CNN
F 2 "" H 7575 1950 50  0001 C CNN
F 3 "" H 7575 1950 50  0001 C CNN
	1    7575 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7575 1375 7675 1375
NoConn ~ 7675 1275
Wire Wire Line
	7275 1375 7200 1375
Wire Wire Line
	7200 1375 7200 1575
Wire Wire Line
	7200 1575 7675 1575
$Comp
L Bertha_main-eagle-import:GND #U0103
U 1 1 61AD0113
P 9975 2175
F 0 "#U0103" H 10025 2225 50  0001 C CNN
F 1 "GND" H 10078 2213 42  0000 L CNN
F 2 "" H 9975 2175 50  0001 C CNN
F 3 "" H 9975 2175 50  0001 C CNN
	1    9975 2175
	1    0    0    -1  
$EndComp
Wire Wire Line
	9975 2075 9975 1975
$Comp
L Connector:Conn_Coaxial_Power J2
U 1 1 61ADDE81
P 9850 4950
F 0 "J2" H 9938 4946 50  0000 L CNN
F 1 "Conn_Coaxial_Power" H 9938 4855 50  0000 L CNN
F 2 "Connector_Coaxial:BNC_TEConnectivity_1478204_Vertical" H 9850 4900 50  0001 C CNN
F 3 "https://www.mouser.com/datasheet/2/18/112404-714699.pdf" H 9850 4900 50  0001 C CNN
	1    9850 4950
	1    0    0    -1  
$EndComp
Text GLabel 9850 4750 1    50   Input ~ 0
CT1
Wire Wire Line
	9850 4850 9850 4750
Text GLabel 1325 2975 0    50   Input ~ 0
CT2
Text GLabel 9850 5250 3    50   Input ~ 0
CT2
Wire Wire Line
	9850 5150 9850 5250
Wire Wire Line
	1325 2975 1450 2975
$Comp
L Bertha_main-eagle-import:GND #0111
U 1 1 61AEC630
P 1550 2775
F 0 "#0111" H 1600 2825 50  0001 C CNN
F 1 "GND" V 1408 2812 42  0000 C CNN
F 2 "" H 1550 2775 50  0001 C CNN
F 3 "" H 1550 2775 50  0001 C CNN
	1    1550 2775
	0    1    1    0   
$EndComp
Wire Wire Line
	1650 2775 1750 2775
Connection ~ 1450 2975
Wire Wire Line
	1450 2975 1750 2975
$Comp
L Device:R R1
U 1 1 61AF294B
P 1900 2375
F 0 "R1" V 1693 2375 50  0000 C CNN
F 1 "820" V 1784 2375 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 1830 2375 50  0001 C CNN
F 3 "~" H 1900 2375 50  0001 C CNN
	1    1900 2375
	0    1    1    0   
$EndComp
Wire Wire Line
	1750 2375 1450 2375
Wire Wire Line
	1450 2375 1450 2975
Wire Wire Line
	2050 2375 2450 2375
Wire Wire Line
	2450 2375 2450 2875
Wire Wire Line
	2450 2875 2350 2875
$Comp
L Device:R R5
U 1 1 61AF6C7A
P 2700 2875
F 0 "R5" V 2493 2875 50  0000 C CNN
F 1 "36k" V 2584 2875 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 2630 2875 50  0001 C CNN
F 3 "~" H 2700 2875 50  0001 C CNN
	1    2700 2875
	0    1    1    0   
$EndComp
Wire Wire Line
	2450 2875 2550 2875
Connection ~ 2450 2875
Wire Wire Line
	2850 2875 2925 2875
$Comp
L Bertha_main-eagle-import:GND #U0104
U 1 1 61B02CDD
P 2975 2675
F 0 "#U0104" H 3025 2725 50  0001 C CNN
F 1 "GND" V 2833 2712 42  0000 C CNN
F 2 "" H 2975 2675 50  0001 C CNN
F 3 "" H 2975 2675 50  0001 C CNN
	1    2975 2675
	0    1    1    0   
$EndComp
Wire Wire Line
	3075 2675 3175 2675
Connection ~ 2925 2875
Wire Wire Line
	2925 2875 3175 2875
$Comp
L Diode:1N4148W D1
U 1 1 61B17889
P 3850 2525
F 0 "D1" V 3896 2445 50  0000 R CNN
F 1 "1N4148W" V 3805 2445 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-123" H 3850 2350 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 3850 2525 50  0001 C CNN
	1    3850 2525
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3775 2775 3850 2775
Wire Wire Line
	3850 2775 3850 2675
$Comp
L Diode:1N4148W D2
U 1 1 61B1AABC
P 4100 2775
F 0 "D2" H 4100 2558 50  0000 C CNN
F 1 "1N4148W" H 4100 2649 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 4100 2600 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 4100 2775 50  0001 C CNN
	1    4100 2775
	-1   0    0    1   
$EndComp
Wire Wire Line
	3950 2775 3850 2775
Connection ~ 3850 2775
$Comp
L Device:R R8
U 1 1 61B20363
P 3600 3250
F 0 "R8" V 3393 3250 50  0000 C CNN
F 1 "36k" V 3484 3250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3530 3250 50  0001 C CNN
F 3 "~" H 3600 3250 50  0001 C CNN
	1    3600 3250
	0    1    1    0   
$EndComp
Wire Wire Line
	3450 3250 2925 3250
Wire Wire Line
	2925 3250 2925 2875
Wire Wire Line
	3750 3250 4350 3250
Wire Wire Line
	4350 3250 4350 2775
Wire Wire Line
	4350 2775 4250 2775
$Comp
L Device:R R7
U 1 1 61B300E0
P 3350 2200
F 0 "R7" V 3143 2200 50  0000 C CNN
F 1 "36k" V 3234 2200 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3280 2200 50  0001 C CNN
F 3 "~" H 3350 2200 50  0001 C CNN
	1    3350 2200
	0    1    1    0   
$EndComp
$Comp
L Device:R R9
U 1 1 61B368D5
P 4100 2200
F 0 "R9" V 3893 2200 50  0000 C CNN
F 1 "36k" V 3984 2200 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 4030 2200 50  0001 C CNN
F 3 "~" H 4100 2200 50  0001 C CNN
	1    4100 2200
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 2775 4350 2775
Connection ~ 4350 2775
Wire Wire Line
	4450 2575 4350 2575
Wire Wire Line
	3200 2200 2925 2200
Wire Wire Line
	3500 2200 3850 2200
Connection ~ 3850 2200
Wire Wire Line
	3850 2200 3950 2200
Wire Wire Line
	3850 2200 3850 2375
Wire Wire Line
	2925 2200 2925 2875
Wire Wire Line
	4250 2200 4350 2200
$Comp
L Device:R R10
U 1 1 61B64A50
P 4600 2200
F 0 "R10" V 4393 2200 50  0000 C CNN
F 1 "36k" V 4484 2200 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 4530 2200 50  0001 C CNN
F 3 "~" H 4600 2200 50  0001 C CNN
	1    4600 2200
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 2200 4350 2200
Connection ~ 4350 2200
Wire Wire Line
	4350 2200 4350 2575
Wire Wire Line
	4750 2200 5150 2200
Wire Wire Line
	5150 2200 5150 2675
Wire Wire Line
	5150 2675 5050 2675
$Comp
L Device:R R12
U 1 1 61B6BED5
P 5400 2675
F 0 "R12" V 5193 2675 50  0000 C CNN
F 1 "36k" V 5284 2675 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 5330 2675 50  0001 C CNN
F 3 "~" H 5400 2675 50  0001 C CNN
	1    5400 2675
	0    1    1    0   
$EndComp
Wire Wire Line
	5250 2675 5150 2675
Connection ~ 5150 2675
$Comp
L Device:C C35
U 1 1 61B73F75
P 5650 2925
F 0 "C35" H 5765 2971 50  0000 L CNN
F 1 "20p" H 5765 2880 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 5688 2775 50  0001 C CNN
F 3 "~" H 5650 2925 50  0001 C CNN
	1    5650 2925
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 2775 5650 2675
Wire Wire Line
	5650 2675 5550 2675
$Comp
L Diode:1N5819 D6
U 1 1 61B7848C
P 6000 2925
F 0 "D6" V 5954 3005 50  0000 L CNN
F 1 "1N5819" V 6045 3005 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 6000 2750 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88525/1n5817.pdf" H 6000 2925 50  0001 C CNN
	1    6000 2925
	0    1    1    0   
$EndComp
Wire Wire Line
	5650 2675 6000 2675
Wire Wire Line
	6000 2675 6000 2775
Connection ~ 5650 2675
$Comp
L Bertha_main-eagle-import:GND #U0105
U 1 1 61B7CC0D
P 6000 3275
F 0 "#U0105" H 6050 3325 50  0001 C CNN
F 1 "GND" H 6103 3313 42  0000 L CNN
F 2 "" H 6000 3275 50  0001 C CNN
F 3 "" H 6000 3275 50  0001 C CNN
	1    6000 3275
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 3075 5650 3125
Wire Wire Line
	5650 3125 6000 3125
Wire Wire Line
	6000 3125 6000 3175
Wire Wire Line
	6000 3075 6000 3125
Connection ~ 6000 3125
Text HLabel 6100 2675 2    50   Input ~ 0
Vout
Wire Wire Line
	6100 2675 6000 2675
Connection ~ 6000 2675
Text HLabel 2550 975  0    50   Input ~ 0
Vin
Wire Wire Line
	2550 975  2650 975 
$EndSCHEMATC