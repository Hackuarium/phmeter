$fn=40;

use <laser-cut-box/pcbbox/pcb.scad>;

3d=false;

showLabels=false;

topToTop=12;
bottomToBottom=20;
padding=1;

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
         [100 - 19.1, 9.12, 8], // rotary push button
         [100 - 7.29, 24.42, 14], // conductivity probe
         [100 - 7.29, 41.2, 14],  // pH probe
    ],
    frontHolesB=[
        [100 - (135.2806 - 50), 1.25, 11.6, 7.5],    // usb connector
        [100 - (120.5992 - 50), 2.25 + 3.5, 14, 16.5],    // RJ12 I2C connector
        //[100 - 55.524, 1.5, 7],    // one-wire 3.5mm plug
        [100 - (38.165 + 6.2 + 8.032 + 3.1), 3.5, 8],    // one-wire 3.5mm plug
        //[100 - 41.275, 1.5, 7],    // one-wire 3.5mm plug
        [100 - (38.165 + 3.1), 3.5, 8],    // one-wire 3.5mm plug
    ],
    leftHoles=[         // holes on the left of the box, over the PCB
        [17,-5,8.2,8.2],
        [28,-5,8.2,8.2],
        [39,-5,8.2,8.2],
        [51,-5,8.2,8.2],
    ],
    showLabels=showLabels,    //should we show the labels
    active=[1,1,1,1,1,1],
    labelsSize=10,      // size of the labels
    3d=3d,            // 3d rendering or just 2d ?,
    show="all"          // used for 3D printing. Possible values:
                        // all (default), top, bottom, fulltop (5 faces), fullbottom (5 faces)
);



