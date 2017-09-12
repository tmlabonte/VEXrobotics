#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  R_Piston,       sensorDigitalOut)
#pragma config(Sensor, dgtl2,  L_Piston,       sensorDigitalOut)
#pragma config(Sensor, dgtl3,  S_Piston,       sensorDigitalOut)
#pragma config(Sensor, dgtl4,  Touch,          sensorTouch)
#pragma config(Sensor, I2C_1,  L_Encoder,      sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  R_Encoder,      sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           L_Intake,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port2,           LB_Shifter,    tmotorVex393, openLoop)
#pragma config(Motor,  port3,           LF_Shifter,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           LF_Drive,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port5,           LB_Drive,      tmotorVex393, openLoop, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port6,           RF_Drive,      tmotorVex393, openLoop)
#pragma config(Motor,  port7,           RB_Drive,      tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port8,           RF_Shifter,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           RB_Shifter,    tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port10,          R_Intake,      tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"

void prep_shoot()
{
	SensorValue[L_Piston] = SensorValue[R_Piston] = SensorValue[S_Piston] = 0;
}

void auton_unload()
{
	while(true)
	{
		if(SensorValue[Touch] == 1)
		{
			motor[LB_Shifter] = motor[LF_Shifter] = motor[RB_Shifter] = motor[RF_Shifter] = 127;
			wait10Msec(1);
			motor[LB_Shifter] = motor[LF_Shifter] = motor[RB_Shifter] = motor[RF_Shifter] = 60;
			wait10Msec(10);
		}
		else if(SensorValue[Touch] == 0)
		{
			motor[L_Intake] = motor[R_Intake] = 127;
			motor[LB_Shifter] = motor[LF_Shifter] = motor[RB_Shifter] = motor[RF_Shifter] = 127;
		}
	}
}

void driver_unload()
{
	while(vexRT[Btn8U] == 1)
	{
		motor[LB_Shifter] = motor[LF_Shifter] = motor[RB_Shifter] = motor[RF_Shifter] = 127;
		wait10Msec(100);
		SensorValue[S_Piston] = 0;
		if(SensorValue[Touch] == 1)
		{
			motor[LB_Shifter] = motor[LF_Shifter] = motor[RB_Shifter] = motor[RF_Shifter] = 45;
			wait10Msec(10);
		}
		else
		{
			motor[L_Intake] = motor[R_Intake] = 127;
			motor[LB_Shifter] = motor[LF_Shifter] = motor[RB_Shifter] = motor[RF_Shifter] = 127;
			wait10Msec(10);
		}
	}
}

void pre_auton()
{
	bStopTasksBetweenModes = true;
}

task autonomous()
{
	SensorValue[L_Encoder] = SensorValue[R_Encoder] = 0;
	while (SensorValue[R_Encoder] < 3000)
	{
		motor[LB_Drive] = motor[RB_Drive] = motor[LF_Drive] = motor[RF_Drive] = 100;
	}
	motor[LB_Drive] = motor[RB_Drive] = motor[LF_Drive] = motor[RF_Drive] = 0;

	motor[LB_Shifter] = motor[LF_Shifter] = motor[RB_Shifter] = motor[RF_Shifter] = 127;
	wait10Msec(100);
	auton_unload();
}

task usercontrol()
{

	while (true)
	{

		//MODE ONE: EIGHT-MOTOR DRIVE

		while(SensorValue[L_Piston] == 1)
		{
			if(vexRT[Btn8D] == 1)
			{
				SensorValue[L_Piston] = SensorValue[R_Piston] = 1;
			}
			else if(vexRT[Btn8R] == 1)
			{
				SensorValue[L_Piston] = SensorValue[R_Piston] = 0;
			}



			motor[LF_Drive] = vexRT[Ch3];
			motor[LB_Drive] = vexRT[Ch3];
			motor[RF_Drive] = vexRT[Ch2];
			motor[RB_Drive] = vexRT[Ch2];
			motor[LF_Shifter] = -vexRT[Ch3];
			motor[LB_Shifter] = -vexRT[Ch3];
			motor[RF_Shifter] = -vexRT[Ch2];
			motor[RB_Shifter] = -vexRT[Ch2];

			if(vexRT[Btn5U] == 1)
			{
				motor[L_Intake] = motor[R_Intake] = 127;
			}
			else if(vexRT[Btn5D] == 1)
			{
				motor[L_Intake] = motor[R_Intake] = -127;
			}
			else
			{
				motor[L_Intake] = motor[R_Intake] = 0;
			}

			if(vexRT[Btn6U] == 1)
			{
				prep_shoot();
				motor[LB_Shifter] = motor[LF_Shifter] = motor[RB_Shifter] = motor[RF_Shifter] = 65;
			}
			else if(vexRT[Btn6D] == 1)
			{
				prep_shoot();
				motor[LB_Shifter] = motor[LF_Shifter] = motor[RB_Shifter] = motor[RF_Shifter] = 127;
			}
			else if((SensorValue[L_Piston] == SensorValue[R_Piston] == 0) && (vexRT[Btn6U] == 0))
			{
				motor[LB_Shifter] = motor[LF_Shifter] = motor[RB_Shifter] = motor[RF_Shifter] = 0;
				SensorValue[S_Piston] = 1;
			}
			else if((SensorValue[L_Piston] == SensorValue[R_Piston] == 0) && (vexRT[Btn6D] == 0))
			{
				motor[LB_Shifter] = motor[LF_Shifter] = motor[RB_Shifter] = motor[RF_Shifter] = 0;
				SensorValue[S_Piston] = 1;
			}


			if(vexRT[Btn7D] == 1)
			{
				motor[LB_Shifter] = motor[LF_Shifter] = motor[RB_Shifter] = motor[RF_Shifter] = -127;
			}
			else if(vexRT[Btn7R] == 1)
			{
				motor[LB_Shifter] = motor[LF_Shifter] = motor[RB_Shifter] = motor[RF_Shifter] = 0;
			}

			driver_unload();

		}

		//MODE TWO: FOUR-MOTOR DRIVE X FOUR-MOTOR SHOOTER

		while(SensorValue[L_Piston] == 0)
		{

			if(vexRT[Btn8D] == 1)
			{
				SensorValue[L_Piston] = SensorValue[R_Piston] = 1;
			}
			else if(vexRT[Btn8R] == 1)
			{
				SensorValue[L_Piston] = SensorValue[R_Piston] = 0;
			}



			motor[LF_Drive] = vexRT[Ch3];
			motor[LB_Drive] = vexRT[Ch3];
			motor[RF_Drive] = vexRT[Ch2];
			motor[RB_Drive] = vexRT[Ch2];

			if(vexRT[Btn5U] == 1)
			{
				motor[L_Intake] = motor[R_Intake] = 127;
			}
			else if(vexRT[Btn5D] == 1)
			{
				motor[L_Intake] = motor[R_Intake] = -127;
			}
			else
			{
				motor[L_Intake] = motor[R_Intake] = 0;
			}

			if(vexRT[Btn6U] == 1)
			{
				prep_shoot();
				motor[LB_Shifter] = motor[LF_Shifter] = motor[RB_Shifter] = motor[RF_Shifter] = 65;
			}
			else if(vexRT[Btn6D] == 1)
			{
				prep_shoot();
				motor[LB_Shifter] = motor[LF_Shifter] = motor[RB_Shifter] = motor[RF_Shifter] = 127;
			}
			else
			{
				motor[LB_Shifter] = motor[LF_Shifter] = motor[RB_Shifter] = motor[RF_Shifter] = 0;
				SensorValue[S_Piston] = 1;
			}

			if(vexRT[Btn7D] == 1)
			{
				motor[LB_Shifter] = motor[LF_Shifter] = motor[RB_Shifter] = motor[RF_Shifter] = -127;
			}
			else if(vexRT[Btn7R] == 1)
			{
				motor[LB_Shifter] = motor[LF_Shifter] = motor[RB_Shifter] = motor[RF_Shifter] = 0;
			}

			driver_unload();

		}
	}
}