$fn=40;

// pHMeter v1.1.2-b
use <laser-cut-box/pcbbox/pcb.scad>;

3d=false;

showLabels=false;

topToTop=11;    // 8 mm M3, 3 mm thickness
bottomToBottom=21;  // 10 mm M3, 3 mm thickness, 8 mm offset
padding=1;
thickness = 3;

cellInternal=12.6;
cellWall=3.06;
cellFingerWidth=4;
cellX=(34.29+52.975)/2;
cellY=(22.225+2.54)/2;

translation = (3d) ?
    [cellX+padding-cellInternal/2, cellY+padding-cellInternal/2, 0] :
    [-(cellInternal+2*cellWall)*3.5,0];

translate(translation)


pcb(
    length=100,         // length of the PCB (phMeter has more length than spectro)
    width=87,           // width of the PCB (phMeter has more width than spectro)
    padding=padding,          // space around the pcb (between pcb and box)
    thickness=cellWall,        // thickness of the material to create the box
    pcbThickness=1.6,   // thickness of the box
    topToTop=topToTop,        // distance from the top of the PCB to the external top of the box
    bottomToBottom=bottomToBottom,  // distance from the bottom of the PCB to the external bottom of the box
    extend=3,          // should top and bottom 'extend' in order to assemble the box without glue
    screws=[            // position of holes to fix the PCB
        [54.2546 - 50, 54.2672 - 50], // bottom - left
        [145.6946 - 50, 54.2672 - 50],  // top - left
        [54.2546 - 50, 132.7532 - 50],  // bottom - left
        [145.6946 - 50, 132.7532 - 50]  // bottom - right
    ],
    screwDiameter=3.2,    // diameter of the screws to fix the PCB
    topHoles=[          // holes to put on the top of the box
         //[132.2326 - 50.0762 - 71.6/2, 87 - (54.2672 - 50) - 25.1/2, 71.6, 25.1],  // LCD 16x2
         [64.2326 - 50.0 + 72/2, 137.0204 - 82.2672 + 25.3/2, 72, 25.3],  // LCD 16x2
         [100 - 19.1, 9.22, 9.5], // rotary push button
         [100 - 7.39, 24.42, 14], // conductivity probe (v1.1.2b)
         [100 - 7.39, 41.19, 14],  // pH probe (v1.1.2b)
    ],
    frontHolesB=[
        [100 - (135.2806 - 50), 7.5/2, 11.6, 7.5],  // usb connector (v1.1.2)
        [100 - (120.5992 - 50), 16.5/2, 14, 16.5],  // RJ12 I2C connector (v1.1.2)
        [100 - 55.52, 1.6 + 3.5/2, 10],  // one-wire 3.5mm plug (v1.1.2b)
        [100 - 41.28, 1.6 + 3.5/2, 10],  // one-wire 3.5mm plug (v1.1.2b)
        //[100 - 55.52, 10/2, 10],  // one-wire 3.5mm plug (v1.1.2b)
        //[100 - 41.28, 10/2, 10],  // one-wire 3.5mm plug (v1.1.2b)
    ],
    backHolesB=[
        [17, 1.6, 8.2],
        [28, 1.6, 8.2],
        [39, 1.6, 8.2],
        [51, 1.6, 8.2],
    ],
    showLabels=showLabels,    //should we show the labels
    active=[1,1,1,1,1,1],
    labelsSize=10,      // size of the labels
    3d=3d,            // 3d rendering or just 2d ?,
    show="all"          // used for 3D printing. Possible values:
                        // all (default), top, bottom, fulltop (5 faces), fullbottom (5 faces)
);




