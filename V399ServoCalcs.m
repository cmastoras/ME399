v = 11;
fprintf("%%%%%%%%%%%%%%%")
mass = 0.0952397;
Arm2Len = 18/12;
ArmLenIn = Arm2Len *12 ;

%Semi WOrking solution: Arm length 16/12, gearing 1.6, Nice Sero with 0.084
%speed and 600 torque but ang change too long?


Torque=56;
CIMrpmEQ = 5310 - Torque*(5310/350);
gearing = 100
CIMgrpm = CIMrpmEQ/ gearing;
speed = 0.17; %Time to move 60 degrees %From JVN
angspeed = (1/(speed* 6)) *2*pi %rotations/second * 2pi = rads/second
%angspeed = (CIMgrpm/60) *2*pi %rotations/secon
circum = (2*Arm2Len)* 3.14159;
linearVel = angspeed/(2*pi) * circum

time = 0.35;
ang_accel = (angspeed)/time
%Torque = aa * MOI
stall_torque = Torque *gearing; %oz-in486
MOI = stall_torque/ang_accel
fprintf(MOI + "OZ IN squared")
CurrentModelMOI = 30.479 * 16


%a = aa
%v = aa*t
%p = aa/2 * t^2
angleChange = (ang_accel/2) * (time^2)

%Just springs?
%Helper springs?
%Double Motors?


endServoWeight = 0.95;
MOIServo = 0.35 * 2^2; %in^2 oz
COM = 0.5;
MOIBall = mass*(ArmLenIn^2);
MOILeft = MOI-MOIServo-MOIBall
%MOI = 1/3m*L^2

armMass = (MOILeft*3)/((ArmLenIn)^2)
walls = 0.03;
outer = 0.5;
volume = 0.7 * ArmLenIn* pi * (outer^2 - (outer-2*walls)^2)
volumeRails = 0.125*ArmLenIn * 0.4 * 2
ShapeVol = volumeRails
neededDen = armMass/(ShapeVol);  %oz/in^3
neededDenMetGcmCubed = neededDen * 1.73 %g/cm^3
neededDenMetLbinCubed = neededDenMetGcmCubed * 0.03612729


%spring stuff. for 7 lb spring:
springMaxLoad = 7*16; %oz

%Const force spring 
neededTorque = 1400; %oz
mountingPoint = 6;%in
springForce = (1400/16)/9;











