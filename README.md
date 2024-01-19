# Requirements

Download latest SDK:
```
  $ wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.16.3/zephyr-sdk-0.16.3_linux-x86_64.tar.xz
  $ tar xvf zephyr-sdk-0.16.3_linux-x86_64.tar.xz
```

Run setup and install SDK:
```
  $ cd zephyr-sdk-0.16.3
  $ ./setup.sh
```

Install UDEV rules so board can be flashed:
```
  $ sudo cp ~/zephyr-sdk-0.16.3/sysroots/x86_64-pokysdk-linux/usr/share/openocd/contrib/60-openocd.rules /etc/udev/rules.d
  $ sudo udevadm control --reload
``` 

# Project setup

Clone project and its dependencies:
```
  $ west init -m git@github.com:Qpczyk/zephyr_template.git
  $ west update
```
Build application:
```
  $ west build app
```

Flash:

```
  $ west flash
```
