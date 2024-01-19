#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/pm/device.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main);

/* Get pointer to any device from dts which is `custom_device` compatible */
const struct device *dev = DEVICE_DT_GET_ANY(custom_device);

int main(void)
{
	LOG_INF("App has started");

        if (!device_is_ready(dev)) {
                LOG_ERR("Device is not available");
        }

	while (1) {
                pm_device_action_run(dev, PM_DEVICE_ACTION_TURN_ON);
		k_sleep(K_MSEC(1000));
                pm_device_action_run(dev, PM_DEVICE_ACTION_TURN_OFF);
                k_sleep(K_MSEC(1000));

		LOG_INF("One cycle passed");
	}
}
