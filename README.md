#   TIMERS lpc1769 Ejemplo
Proyecto ejemplo para controlar el sensor ultranónico HC-SR04 con el micro controlador LPCXpresso lpc1769.
El ejemplo enciende un led cuando se coloca un obstáculo a menos de 5cm de distancia del sensor ultrasónico,

- IDE: [MCUXpresso IDE](https://www.nxp.com/design/software/development-software/mcuxpresso-software-and-tools-/mcuxpresso-integrated-development-environment-ide:MCUXpresso-IDE).
- Lenguaje: C.
- Microcontrolador: [LPCXpresso lpc1769 rev C](https://www.embeddedartists.com/products/lpc1769-lpcxpresso/).
- Sensor Ultrasónico HC-SR04

---
## LPCXpresso LPC1769
![lpc1769](img/lpc1769_lpcxpresso.png "LPCXpresso LPC1769 revC.") 
![lpc1769_pinout](img/lpc1769_pinout.png "LPCXpresso LPC1769 pinout")

### PCONP
![lpc1769_PCONP](img/PCONP.png "LPC1769 PCONP REGISTER")

### PCLKSELx
![lpc1769_PCLKSEL](img/PCLKSEL.png "LPC1769 PCLKSELx REGISTER")

### ISER0
![lpc1769_ISER0](img/ISER0.png "LPC1769 ISER0 REGISTER")

### TIMERx - REGISTROS
![lpc1769_Timer_Regs](img/TIMER_Regs.png "LPC1769 TIMERS REGISTERS")
![lpc1769_Timer_Regs1](img/TIMER_Regs_1.png "LPC1769 TIMERS REGISTERS")
![lpc1769_Timer_Regs2](img/EMR_register.png "LPC1769 TIMERS REGISTERS")

![lpc1769_Timer_Regs3](img/TCTCR_register.png "LPC1769 TIMERS REGISTERS")
![lpc1769_Timer_Regs4](img/TCCR_register.png "LPC1769 TIMERS REGISTERS")

## SENSOR ULTRASONICO HC-SR04
![HC-SR04](img/HCSR04.jpg "Sensor ultrasonico HC-SR04")
![HC-SR04](img/seniales.jpg "Sensor ultrasonico HC-SR04")
![HC-SR04](img/caracteristicas.jpg "Sensor ultrasonico HC-SR04 caracteristicas")
## ESQUEMÁTICO DE PRUEBA
![HC-SR04](img/SCH.png "Circuito esquemático")

---
Espero le sea de útilidad.

Aportes y sugerencias siempre serán bienvenidas.

Autor: @ealegremendoza

E-mail: ealegremendoza@gmail.com
