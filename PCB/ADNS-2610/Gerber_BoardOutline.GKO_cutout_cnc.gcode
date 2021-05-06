(G-CODE GENERATED BY FLATCAM v8.993 - www.flatcam.org - Version Date: 2020/06/05)

(Name: Gerber_BoardOutline.GKO_cutout_cnc)
(Type: G-code from Geometry)
(Units: MM)

(Created on Thursday, 06 May 2021 at 21:45)

(This preprocessor is the default preprocessor used by FlatCAM.)
(It is made to work with MACH3 compatible motion controllers.)

(TOOL DIAMETER: 2.0 mm)
(Feedrate_XY: 80.0 mm/min)
(Feedrate_Z: 60.0 mm/min)
(Feedrate rapids 1500.0 mm/min)

(Z_Cut: -2.0 mm)
(DepthPerCut: 0.7 mm <=>3 passes)
(Z_Move: 2.0 mm)
(Z Start: None mm)
(Z End: 15.0 mm)
(Steps per circle: 64)
(Preprocessor Geometry: default)

(X range:   -1.0636 ...   55.6736  mm)
(Y range:   -1.1271 ...   44.9421  mm)

(Spindle Speed: None RPM)
G21
G90
G94



G01 F80.00
G00 Z2.0000

M03
G00 X-1.0636 Y20.5075
G01 F60.00
G01 Z-0.7000
G01 F80.00
G01 X-1.0636 Y-0.1271
G01 X-1.0587 Y-0.2251
G01 X-1.0443 Y-0.3222
G01 X-1.0205 Y-0.4173
G01 X-0.9874 Y-0.5097
G01 X-0.9455 Y-0.5985
G01 X-0.8950 Y-0.6826
G01 X-0.8366 Y-0.7615
G01 X-0.7707 Y-0.8342
G01 X-0.6980 Y-0.9001
G01 X-0.6191 Y-0.9585
G01 X-0.5350 Y-1.0090
G01 X-0.4462 Y-1.0509
G01 X-0.3538 Y-1.0840
G01 X-0.2587 Y-1.1078
G01 X-0.1616 Y-1.1222
G01 X-0.0636 Y-1.1271
G01 X25.9050 Y-1.1271
G00 X25.9050 Y-1.1271
G01 F60.00
G01 Z-1.4000
G01 F80.00
G01 X-0.0636 Y-1.1271
G01 X-0.1616 Y-1.1222
G01 X-0.2587 Y-1.1078
G01 X-0.3538 Y-1.0840
G01 X-0.4462 Y-1.0509
G01 X-0.5350 Y-1.0090
G01 X-0.6191 Y-0.9585
G01 X-0.6980 Y-0.9001
G01 X-0.7707 Y-0.8342
G01 X-0.8366 Y-0.7615
G01 X-0.8950 Y-0.6826
G01 X-0.9455 Y-0.5985
G01 X-0.9874 Y-0.5097
G01 X-1.0205 Y-0.4173
G01 X-1.0443 Y-0.3222
G01 X-1.0587 Y-0.2251
G01 X-1.0636 Y-0.1271
G01 X-1.0636 Y20.5075
G00 X-1.0636 Y20.5075
G01 F60.00
G01 Z-2.0000
G01 F80.00
G01 X-1.0636 Y-0.1271
G01 X-1.0587 Y-0.2251
G01 X-1.0443 Y-0.3222
G01 X-1.0205 Y-0.4173
G01 X-0.9874 Y-0.5097
G01 X-0.9455 Y-0.5985
G01 X-0.8950 Y-0.6826
G01 X-0.8366 Y-0.7615
G01 X-0.7707 Y-0.8342
G01 X-0.6980 Y-0.9001
G01 X-0.6191 Y-0.9585
G01 X-0.5350 Y-1.0090
G01 X-0.4462 Y-1.0509
G01 X-0.3538 Y-1.0840
G01 X-0.2587 Y-1.1078
G01 X-0.1616 Y-1.1222
G01 X-0.0636 Y-1.1271
G01 X25.9050 Y-1.1271
G00 Z2.0000
G00 X28.7050 Y-1.1271
G01 F60.00
G01 Z-0.7000
G01 F80.00
G01 X54.6736 Y-1.1271
G00 X54.6736 Y-1.1271
G01 F60.00
G01 Z-1.4000
G01 F80.00
G01 X28.7050 Y-1.1271
G00 X28.7050 Y-1.1271
G01 F60.00
G01 Z-2.0000
G01 F80.00
G01 X54.6736 Y-1.1271
G00 Z2.0000
G00 X54.6736 Y-1.1271
G01 F60.00
G01 Z-0.7000
G01 F80.00
G01 X54.7716 Y-1.1222
G01 X54.8687 Y-1.1078
G01 X54.9638 Y-1.0840
G01 X55.0562 Y-1.0509
G01 X55.1450 Y-1.0090
G01 X55.2291 Y-0.9585
G01 X55.3080 Y-0.9001
G01 X55.3807 Y-0.8342
G01 X55.4466 Y-0.7615
G01 X55.5050 Y-0.6826
G01 X55.5555 Y-0.5985
G01 X55.5974 Y-0.5097
G01 X55.6305 Y-0.4173
G01 X55.6543 Y-0.3222
G01 X55.6687 Y-0.2251
G01 X55.6736 Y-0.1271
G01 X55.6736 Y20.5075
G00 X55.6736 Y20.5075
G01 F60.00
G01 Z-1.4000
G01 F80.00
G01 X55.6736 Y-0.1271
G01 X55.6687 Y-0.2251
G01 X55.6543 Y-0.3222
G01 X55.6305 Y-0.4173
G01 X55.5974 Y-0.5097
G01 X55.5555 Y-0.5985
G01 X55.5050 Y-0.6826
G01 X55.4466 Y-0.7615
G01 X55.3807 Y-0.8342
G01 X55.3080 Y-0.9001
G01 X55.2291 Y-0.9585
G01 X55.1450 Y-1.0090
G01 X55.0562 Y-1.0509
G01 X54.9638 Y-1.0840
G01 X54.8687 Y-1.1078
G01 X54.7716 Y-1.1222
G01 X54.6736 Y-1.1271
G00 X54.6736 Y-1.1271
G01 F60.00
G01 Z-2.0000
G01 F80.00
G01 X54.7716 Y-1.1222
G01 X54.8687 Y-1.1078
G01 X54.9638 Y-1.0840
G01 X55.0562 Y-1.0509
G01 X55.1450 Y-1.0090
G01 X55.2291 Y-0.9585
G01 X55.3080 Y-0.9001
G01 X55.3807 Y-0.8342
G01 X55.4466 Y-0.7615
G01 X55.5050 Y-0.6826
G01 X55.5555 Y-0.5985
G01 X55.5974 Y-0.5097
G01 X55.6305 Y-0.4173
G01 X55.6543 Y-0.3222
G01 X55.6687 Y-0.2251
G01 X55.6736 Y-0.1271
G01 X55.6736 Y20.5075
G00 Z2.0000
G00 X55.6736 Y23.3075
G01 F60.00
G01 Z-0.7000
G01 F80.00
G01 X55.6736 Y43.9421
G01 X55.6687 Y44.0401
G01 X55.6543 Y44.1372
G01 X55.6305 Y44.2323
G01 X55.5974 Y44.3247
G01 X55.5555 Y44.4135
G01 X55.5050 Y44.4976
G01 X55.4466 Y44.5765
G01 X55.3807 Y44.6492
G01 X55.3080 Y44.7151
G01 X55.2291 Y44.7735
G01 X55.1450 Y44.8240
G01 X55.0562 Y44.8659
G01 X54.9638 Y44.8990
G01 X54.8687 Y44.9228
G01 X54.7716 Y44.9372
G01 X54.6736 Y44.9421
G01 X28.7050 Y44.9421
G00 X28.7050 Y44.9421
G01 F60.00
G01 Z-1.4000
G01 F80.00
G01 X54.6736 Y44.9421
G01 X54.7716 Y44.9372
G01 X54.8687 Y44.9228
G01 X54.9638 Y44.8990
G01 X55.0562 Y44.8659
G01 X55.1450 Y44.8240
G01 X55.2291 Y44.7735
G01 X55.3080 Y44.7151
G01 X55.3807 Y44.6492
G01 X55.4466 Y44.5765
G01 X55.5050 Y44.4976
G01 X55.5555 Y44.4135
G01 X55.5974 Y44.3247
G01 X55.6305 Y44.2323
G01 X55.6543 Y44.1372
G01 X55.6687 Y44.0401
G01 X55.6736 Y43.9421
G01 X55.6736 Y23.3075
G00 X55.6736 Y23.3075
G01 F60.00
G01 Z-2.0000
G01 F80.00
G01 X55.6736 Y43.9421
G01 X55.6687 Y44.0401
G01 X55.6543 Y44.1372
G01 X55.6305 Y44.2323
G01 X55.5974 Y44.3247
G01 X55.5555 Y44.4135
G01 X55.5050 Y44.4976
G01 X55.4466 Y44.5765
G01 X55.3807 Y44.6492
G01 X55.3080 Y44.7151
G01 X55.2291 Y44.7735
G01 X55.1450 Y44.8240
G01 X55.0562 Y44.8659
G01 X54.9638 Y44.8990
G01 X54.8687 Y44.9228
G01 X54.7716 Y44.9372
G01 X54.6736 Y44.9421
G01 X28.7050 Y44.9421
G00 Z2.0000
G00 X25.9050 Y44.9421
G01 F60.00
G01 Z-0.7000
G01 F80.00
G01 X-0.0636 Y44.9421
G01 X-0.1616 Y44.9372
G01 X-0.2587 Y44.9228
G01 X-0.3538 Y44.8990
G01 X-0.4462 Y44.8659
G01 X-0.5350 Y44.8240
G01 X-0.6191 Y44.7735
G01 X-0.6980 Y44.7151
G01 X-0.7707 Y44.6492
G01 X-0.8366 Y44.5765
G01 X-0.8950 Y44.4976
G01 X-0.9455 Y44.4135
G01 X-0.9874 Y44.3247
G01 X-1.0205 Y44.2323
G01 X-1.0443 Y44.1372
G01 X-1.0587 Y44.0401
G01 X-1.0636 Y43.9421
G01 X-1.0636 Y23.3075
G00 X-1.0636 Y23.3075
G01 F60.00
G01 Z-1.4000
G01 F80.00
G01 X-1.0636 Y43.9421
G01 X-1.0587 Y44.0401
G01 X-1.0443 Y44.1372
G01 X-1.0205 Y44.2323
G01 X-0.9874 Y44.3247
G01 X-0.9455 Y44.4135
G01 X-0.8950 Y44.4976
G01 X-0.8366 Y44.5765
G01 X-0.7707 Y44.6492
G01 X-0.6980 Y44.7151
G01 X-0.6191 Y44.7735
G01 X-0.5350 Y44.8240
G01 X-0.4462 Y44.8659
G01 X-0.3538 Y44.8990
G01 X-0.2587 Y44.9228
G01 X-0.1616 Y44.9372
G01 X-0.0636 Y44.9421
G01 X25.9050 Y44.9421
G00 X25.9050 Y44.9421
G01 F60.00
G01 Z-2.0000
G01 F80.00
G01 X-0.0636 Y44.9421
G01 X-0.1616 Y44.9372
G01 X-0.2587 Y44.9228
G01 X-0.3538 Y44.8990
G01 X-0.4462 Y44.8659
G01 X-0.5350 Y44.8240
G01 X-0.6191 Y44.7735
G01 X-0.6980 Y44.7151
G01 X-0.7707 Y44.6492
G01 X-0.8366 Y44.5765
G01 X-0.8950 Y44.4976
G01 X-0.9455 Y44.4135
G01 X-0.9874 Y44.3247
G01 X-1.0205 Y44.2323
G01 X-1.0443 Y44.1372
G01 X-1.0587 Y44.0401
G01 X-1.0636 Y43.9421
G01 X-1.0636 Y23.3075
G00 Z2.0000
M05
G00 Z2.0000
G00 Z15.00

