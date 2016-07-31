# kLib

What's this?

	Hi! This repository contain set of C++ libraries initially intended to be used with ARM cortex-m4 microcontrollers ( STM32F4xx with arm-gcc compiler ). It's main goal is to give users comprehensive tool for easly and fast programming without rejecting code efficiency.

To whom addressed?

	Robotics, microcontrollers, C++ programmers enthusiasts

Why this?

	Inspiration came from Qt framework where programs grows in very elegant way and all libraries are at your fingertips. Similarly to Qt all libraries in this repo starts with small letter 'k'. Many tricks have been applied to improve code readability.

What's inside?

	At the moment libraries provides:

	* GPIO functionality
	* basic communication interfaces: UART, I2C
	* system class providing clocks info, system timer, SRAM interrupt vector table,
	  seconds miliseconds and microseconds delaying mechanism
	* real time operating system integration ( FreeRTOS V9.0.0 )
	* strings operations
	* interface to sensors: HMC5883L, MPU6050, BMP085
	* PWM signal generation and receiving including servos handling and RC control
	* control theory based classes: PID, integrator, differentiator, low and high pass filters,
	  first and second order systems implementations
	* math: right-handed quaternions, matrix and vectors
	* quaternion based AHRS implementation

Want to contribute?

	If you are interested in contributing, please send an email to zalewskipawel92@gmail.com
