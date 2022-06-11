Force = 10;
Mass = 0.0952397;
angle = 35;
theta = deg2rad(angle)
%Accel = Force/Mass;
gAccel = 32.808;
v = 15;

StartZ = 24/12;

vTerm = 9.5;

c = (Mass*gAccel)/vTerm


ToF = 2*v*sin(theta)/gAccel;
vx = cos(theta)*v;
vy = sin(theta)*v;
steps = 100;
perstep = ToF/steps;
y = zeros(steps,1);
x = zeros(steps,1);
z = zeros(steps,1);
yd = zeros(steps,1);
xd = zeros(steps,1);
zd = zeros(steps,1);
why = StartZ;
i = 1;
c = 0.2;
vt = Mass*gAccel/c;

Cd = 0.04;
A = 1.57^2 * pi;
rhoa = 0.0007083333;
c2 =Cd * rhoa* A
%vt = (Mass*gAccel/c2)^1/2
while why > 0
    ex = vx*perstep*i;
    x(i) = ex;
    why = StartZ +ex*tan(theta) - gAccel*ex^2/(2*(v^2)*(cos(theta)^2));
    z(i) = why;
    y(i) = 0;
    


    i =i + 1;
end

for i = 1:201
    t = i/200;
    xd(i) = (v * vt * cos(theta)/gAccel)*(1-exp(-gAccel*t/vt));
    zd(i) = StartZ + (vt/gAccel)*(v*sin(theta)+vt)*(1-exp(-gAccel*t/vt)) - vt * t;
    yd(i) = 0;
end




plot3(x,y,z,"r");
hold on
plot3(xd,yd,zd,"b");
ylim([-4 4]);   
zlim([0 8]);

pointA = [0,-2,0];
pointB = [0,2,0];
pointC = [10,2,0];
pointD = [10,-2,0];


points=[pointA' pointB' pointC' pointD']; % using the data given in the question
fill3(points(1,:),points(2,:),points(3,:),'r')

triWidth = 14.5/12;
triHeight = 13/12;
pointA = [8,-triWidth/2,0.01];
pointB = [8,triWidth/2,0.01];
pointC = [8-triHeight,0,0.01];
points=[pointA' pointB' pointC']; % using the data given in the question
fill3(points(1,:),points(2,:),points(3,:),'g');


grid on;
alpha(0.3);


arm1Length = 10;
arm2Length = 5;
arm1Slist = [[-1;0;0;0;0;arm1Length],[-1;0;0;0;0;arm2Length+arm1Length]];
arm1Start = -pi/2;
arm2Start = -pi/2;
arm1End = 3.1415/4;
arm2End = 0;
 
arm1 = arm1Start:((arm1End-arm1Start)/200):arm1End;
arm2 = arm2Start:((arm2End-arm2Start)/200):arm2End;

time = 1:201;

JointVs = zeros(201,2);

for i = 1:200
    
    thetaList = [arm1(i), arm2(i)];

    Js = JacobianSpace(arm1Slist,thetaList);

    Vtip = [0;0;0;0;14;14];

    JointVs(i,:) = transpose(Js) * Vtip;
end
%List of joint torques = jacobian trans in space as a function of joint
%agnles * force at tip
plot(time,JointVs(:,1),'r')
hold on
plot(time,JointVs(:,2),'b')

