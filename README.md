# Ghostbusters Trap (modified Spirit Halloween model)
This is a automated upgrade of the Spirit Halloween ghost trap. 
The original toy-grade mechanism (handle-mounted button) has been replaced with a custom controller, improved mechanics, and atmospheric effects.

- Controller: Arduino Pro Mini
- Door Actuation: Dual servos with custom rod linkages
- Smoke System: Modified e-cigarette atomizer and mini air pump
- Lighting: Salvaged headlamp; Arduino-controlled "three-click" on strobe sequence
- Power: Dual 14650 lithium batteries
- Controls: External sewing machine foot pedal and heavy-duty on/off switch

After looking at the problem for some time, I decided the best approach was to cut the door-opening mechanism in half using a thin hacksaw blade. 
This modification allowed me to add two small servos, bypassing the original button-press mechanism that proved difficult to work with. 
For the smoke effect, I discovered that an e-cigarette atomizer works effectively by blowing from the suction end. 
I kpet the original heating element but removed the flow detection; the Arduino now manages the timing and voltage delivery, triggering the smoke effect automatically.

Sooner or later, I need to get around to designing a custom PCB to replace the existing point-to-point wiring.
A 'how-to' guide, schematics, and PCB designs will all be added to this page.


[![Ghost Trap](https://img.youtube.com/vi/ItBGCm69trw/0.jpg)](https://youtu.be/ItBGCm69trw?si=RgBy6HVHlGO9z1Zm)
[![Ghost Trap](https://img.youtube.com/vi/yX817zeQUPU/0.jpg)](https://www.youtube.com/watch?v=yX817zeQUPU)


<div style="float:left;margin:0 10px 10px 0" markdown="1">
<img src="/Hardware/20260621_103740.jpg" alt="Alt Text" style="width:22%; height:auto;">
<img src="/Hardware/20260621_103825.jpg" alt="Alt Text" style="width:22%; height:auto;"> 
<img src="/Hardware/20260621_103931.jpg" alt="Alt Text" style="width:22%; height:auto;">
<img src="/Hardware/20260621_103937.jpg" alt="Alt Text" style="width:22%; height:auto;">
<div>
<div style="float:left;margin:0 10px 10px 0" markdown="1">
<img src="/Hardware/20260621_103940.jpg" alt="Alt Text" style="width:22%; height:auto;">
<img src="/Hardware/20260621_104024.jpg" alt="Alt Text" style="width:22%; height:auto;">
<img src="/Hardware/20260621_104028.jpg" alt="Alt Text" style="width:22%; height:auto;">
<img src="/Hardware/20260621_104034.jpg" alt="Alt Text" style="width:22%; height:auto;">
<div>
<div style="float:left;margin:0 10px 10px 0" markdown="1">
<img src="/Hardware/20260621_104045.jpg" alt="Alt Text" style="width:22%; height:auto;">
<img src="/Hardware/20260621_104056.jpg" alt="Alt Text" style="width:22%; height:auto;">
<img src="/Hardware/20260621_104110.jpg" alt="Alt Text" style="width:22%; height:auto;">
<img src="/Hardware/20260621_104137.jpg" alt="Alt Text" style="width:22%; height:auto;">
<div>
<div style="float:left;margin:0 10px 10px 0" markdown="1">
<img src="/Hardware/20260621_103915.jpg" alt="Alt Text" style="width:22%; height:auto;">
<img src="/Hardware/20260621_104325.jpg" alt="Alt Text" style="width:22%; height:auto;">
<img src="/Hardware/20260621_104705.jpg" alt="Alt Text" style="width:22%; height:auto;">
<img src="/Hardware/20260621_104712.jpg" alt="Alt Text" style="width:22%; height:auto;">
<div>
